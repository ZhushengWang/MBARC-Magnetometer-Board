/* 
main.c
This application will execute on the ColdFire MCF51AC256A/B and MCF51AC128A
See pe_crt0_MCF51ACxA_MCF51ACxB.S for startup code
See pe_hooks.c for processor initialization routines
See pe_vectors_MCF51ACx.c for vector table and interrupt service routines
See linker script pe_MCF51ACxA_MCF51ACxB.ld for variables to control memory map
(C)opyright 2008, P&E Microcomputer Systems, Inc.
Visit us at http://www.pemicro.com 
*/

#include "includes.h"

#define BOOTLOADER_VERSION 141

CDH_IO_t *cdhio;
uint8 buf[1024];

int main ()
{
int i;
int nLen;
int nCount = 0;
uint32 time_code;
uint32 boot_time_code=0;
uint32 nStepTime=0;
uint8 mission_phase;
int nSkipBoot = 0;
int nWaitTime = 0;
int nAbortDeploy = 0;

  cdhio = (CDH_IO_t *)CDH_IO_ADDR;

  //Turn off devices
  PWR_AllDevicesOff();
  
  //Turn on PPT DAC
  pwr_ctl(CDH_DAC,PWR_ON);
    
  //Turn on BD4 Mag to power test port interface
  pwr_ctl(BD4_MAG,PWR_ON);  
  
  //Delay to make sure serial port diff driver is on (powered with BD4 mag)
  for (i=0;i<1000000;i++)  
  {
   ;
  }
  
  print_uart_msg("\nQB50 Columbia/Atlantis BootLoader\n");
  print_uart_msg("V%5.2f -- 09-20-2016, Ryan P. Miller, Michael Burton, Madelyn Rycenga\n",(float)BOOTLOADER_VERSION/100.0);
  print_uart_msg("University of Michigan\n");
  print_uart_msg("Space Physics Research Laboratory\n\n");
  
  //Get NV status
  OP_InitStatus();
  time_code = OP_GetTimeCode();
  set_time(time_code);
  OP_SetBootVer(BOOTLOADER_VERSION);
  LI1_TX_Enable(OP_GetTXEnable());
  
  mission_phase = OP_GetMissionPhase();
  
  OP_IncrementBootCount();
  
  print_uart_msg("Bootloader Startup - Phase: %d  Time: %d\n",mission_phase,time_code);
  print_uart_msg("CDH FPGA Version:  %d\n",cdhio->CDH_FPGA_VER);
  
  print_uart_msg("\nStructure sizes:\n");
  print_uart_msg("LI Telemetry:       %d\n",sizeof(TELEMETRY_STRUCTURE_t));
  print_uart_msg("LI RF:              %d\n",sizeof(RADIO_RF_CONFIGURATION_t));
  print_uart_msg("LI Beacon Interval: %d\n",sizeof(RADIO_BEACON_CONFIGURATION_t));
  print_uart_msg("LI Config:          %d\n",sizeof(RADIO_CONFIGURATION_t));
  print_uart_msg("LI Beacon Data:     %d\n\n",sizeof(BEACON_t));
  
  //Program timer for 250 millisecond interrupts
  cdhio->TIMER1_DAT3 = 0x00;
  cdhio->TIMER1_DAT2 = 0x5F;
  cdhio->TIMER1_DAT1 = 0x5E;
  cdhio->TIMER1_DAT0 = 0x10;
  
  cdhio->TIMER1_CTL = 0x01;
  cdhio->INT_CTL = 0x01;
  
  cdhio->INT_MASK = 0xFE;
  
  enable_ints();

  while (1)
  { 

    if ( (Get250msFlag() && (mission_phase == BL_COMMAND2)) || 
         (GetOneHzFlag() && (mission_phase != BL_COMMAND2)) )
    {
      
      //Blink the LED
      disable_ints();
      cdhio->CONTROL1 = cdhio->CONTROL1 ^ 0x01;
      enable_ints();
      
      switch (mission_phase)
      {
        case BL_FIRST_TURNON:
          mission_phase = BL_INITIAL_WAIT;
          OP_SetMissionPhase(mission_phase);
          boot_time_code=get_time(); //Get Start Time
          OP_SetBootTime(time_code);
          print_uart_msg("Boot:  First Turn-on\n");
          nWaitTime = OP_GetInitialWait();
          break;
          
        case BL_INITIAL_WAIT:
          time_code = get_time();         
          if ((nWaitTime % 10) == 0)
          {
            print_uart_msg("Boot:  Initial Wait (%d)\n",nWaitTime);
          }
          
          if (nWaitTime <= 0)  //Wait for Initial Wait time (30 minutes the first time)
          {
            if (OP_GetEnableDeploy() == 1)
            {
              mission_phase = BL_DEPLOY;
              OP_SetMissionPhase(BL_FIRST_TURNON);
              OP_SetInitialWait(60); //Set up for short wait time on next boot
              PWR_AllADCsOn(); //Ready for deployment phase
              init_deploy(time_code);
            }
            else
            {
              print_uart_msg("Boot:  Deploy Disabled. Skipping.\n");
              mission_phase = BL_NORMAL_BOOT1;
              OP_SetMissionPhase(BL_FIRST_TURNON); //Save for next boot
            }
          }
          else
          {
            //A test port or radio command can stop the initial wait and start bootup
            
            if (test_port_bytes_avail())  //Check for go_boot_command command
            {
              nLen = get_test_port_command(buf);
              if ((nLen > 0) && (IsCommand_go_boot_cmd(buf,nLen)))
              {
                mission_phase = BL_NORMAL_BOOT1;
                nSkipBoot = 1;
                OP_SetMissionPhase(BL_FIRST_TURNON); //Save for next boot
              }
            }
            
            if (LI1_RadioBytesAvail())
            {
              nLen = LI1_GetCommand(buf);
              if ((nLen > 0) && (LI1_IsCommand_go_boot_cmd(buf,nLen)))
              {
                mission_phase = BL_NORMAL_BOOT1;
                nSkipBoot = 1;
                OP_SetMissionPhase(BL_FIRST_TURNON); //Save for next boot
              }
            }  
          }
          
          nWaitTime--;
          
          break;
         
        case BL_DEPLOY: 
          //A test port command can stop the deploy sequence and start bootup
          
          if (test_port_bytes_avail())  //Check for go_boot_command command
          {
            nLen = get_test_port_command(buf);
            if ((nLen > 0) && (IsCommand_go_boot_cmd(buf,nLen)))
            {
              mission_phase = BL_NORMAL_BOOT1;
              nSkipBoot = 1;
              OP_SetMissionPhase(BL_FIRST_TURNON); //Save for next boot
              nAbortDeploy = 1;
            }
          }
         
          if (run_deploy_sequence(nAbortDeploy))
          {
            if (nAbortDeploy == 0)
            {
              //Successful deploy sequence, don't run next time
              mission_phase = BL_NORMAL_BOOT1;
              OP_SetMissionPhase(BL_NORMAL_TURNON);  //For next boot
            }
            nAbortDeploy = 0;
          } 
          break;
        
        case BL_NORMAL_BOOT1:
          PWR_RadioOn(PWR_ON);           //Turn on the radio
          //PWR_IMU2On(PWR_ON);            //Turn on IMU2 (Epson)
          PWR_IMU1On(PWR_ON);
          PWR_AllMagsOn();
          mission_phase = BL_NORMAL_BOOT2;
          LI1_AssertReset();
          //IMU2_AssertReset();
          
          DAC_SetDACVolts(1.316);
          break;
            
        case BL_NORMAL_BOOT2:
          mission_phase = BL_NORMAL_BOOT3;
          
          LI1_DeassertReset();
          //IMU2_DeassertReset();
          break;
        
        case BL_NORMAL_BOOT3:
          mission_phase = BL_NORMAL_BOOT4;
          
          LI1_RadioConfig();
          //IMU2_Init();
          IMU1_Init();
          Mag_InitMag(SELECT_SP1_MAG);
          Mag_InitMag(SELECT_SP2_MAG);
          Mag_InitMag(SELECT_SP3_MAG);
          Mag_InitMag(SELECT_BD4_MAG);
          
          PWR_AllADCsOn();
          break;
          
        case BL_NORMAL_BOOT4:
          mission_phase = BL_NORMAL_BOOT5;
          
          //IMU2_DoTasks();
          TLM_CollectBeaconData();         
          break;
          
        case BL_NORMAL_BOOT5:
          //IMU2_DoTasks();
          TLM_UpdateBeaconData(mission_phase);
          
          //Check if skipping boot from initial wait phase
          if (nSkipBoot)
          {
            mission_phase = BL_COMMAND1;
            nSkipBoot = 0;
          }
          else
          {
            mission_phase = BL_NORMAL_BOOT6;
            print_uart_msg("Boot:  FSW Boot Countdown\n");
          }
          nStepTime = get_time(); 
          nCount=0; 
          
          LI1_BeaconConfig(4); //Set Beacon for 10 seconds       
          break;
           
        case BL_NORMAL_BOOT6:
          nCount++;
          //IMU2_DoTasks();
          time_code = get_time();
          
          if (nCount % 2)  //Odds
          {
            TLM_UpdateBeaconData(mission_phase);
            TLM_CollectBeaconData();  //Start collection for next time
          }
                    
          print_uart_msg(".");
          if ((time_code-nStepTime) >= BOOT_WAIT_SECS)  //Wait for 60 seconds
          {
            mission_phase = BL_LOAD_FSW;
            OP_SetMissionPhase(BL_NORMAL_TURNON);
            print_uart_msg("\n");
          }
          else
          {
            if (test_port_bytes_avail())  //Check for go_boot_command command
            {
              nLen = get_test_port_command(buf);
              if ((nLen > 0) && (IsCommand_go_boot_cmd(buf,nLen)))
              {
                mission_phase = BL_COMMAND1;
                OP_SetMissionPhase(BL_NORMAL_TURNON); //Save for next boot
              }
            }
            
            if (LI1_RadioBytesAvail())
            {
              nLen = LI1_GetCommand(buf);
              if ((nLen > 0) && (LI1_IsCommand_go_boot_cmd(buf,nLen)))
              {
                mission_phase = BL_COMMAND1;
                OP_SetMissionPhase(BL_NORMAL_TURNON); //Save for next boot
              }
            }  
          }
          break;
          
        case BL_COMMAND1:
          print_uart_msg("\nBoot:  Entering Boot Command Mode.\n");
          PWR_PrintStatus();
          mission_phase = BL_COMMAND2;
          break;
          
        case BL_COMMAND2:       
          nCount++;
          
          //IMU2_DoTasks();
          
          if ((nCount % 4) == 0)  
          {
            TLM_UpdateBeaconData(mission_phase);
            TLM_CollectBeaconData();
          }
          
          //Process any test port commands
          while (!(cdhio->STATUS1 & STS1_CDH_CPU_FIFO_EF))
          {
            nLen = get_test_port_command(buf);
            if (nLen > 0)
            {
              ProcessTelecommand(buf,nLen);
            }
            else
            {
              print_uart_msg("Test Port Command Timeout...\n");
            }
          } 
          
          //Process any radio commands
          while (LI1_RadioBytesAvail())
          {
            nLen = LI1_GetCommand(buf);
            if (nLen > 0)
            {
              LI1_ProcessCommand(buf,nLen);
            }
          }  
          
          //For testing radios        
          if (LI1_GetTestMode() && ((nCount % 4) == 0))
          {
            LI1_SendTestPacket();
          }
                  
          break;
          
        case BL_NORMAL_TURNON:
          print_uart_msg("Boot:  Normal Turn-on.\n");
          mission_phase = BL_NORMAL_BOOT1;
          boot_time_code=get_time(); //Get Start Time
          OP_SetBootTime(time_code);
          break;
          
        case BL_LOAD_FSW:
          print_uart_msg("Boot:  Loading FSW.\n");
          FSW_BootPartition(OP_GetActiveFSWPartition());
          
          //If this returns, we couldn't load FSW, so go to boot command mode
          mission_phase = BL_COMMAND1;
          break;
        
        default:
          print_uart_msg("Illegal Mission Phase: %d\n",mission_phase);
          mission_phase=BL_NORMAL_BOOT1;
          break;
      }
    }
  }
}

//These routines cannot be moved before main
//I don't know why - everything crashes if you 
//put them there.
inline void enable_ints(void)
{
  volatile uint16 __level = 0x2000;
	 
	__asm__ __volatile__ 
  (
	  "move.w %0,%%sr"
	    : "=d" (__level)
  );
}

inline void disable_ints(void)
{
  volatile uint16 __level = 0x2700;
	 
  __asm__ __volatile__
  (
    "move.w %0,%%sr"
	    : "=d" (__level)
  );
}
