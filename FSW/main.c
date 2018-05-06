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

#define FSW_VERSION 120
#define FSW_DATE    "08-17-2017"


CDH_IO_t *cdhio;
uint8 buf[1024];

int main ()
{

  int i;
  int nLen;
  int nCount = 0;
  uint32 time_code;
  uint8 yMissionPhase = FSW_PHASE_IDLE;
  char szDate[]=FSW_DATE;

  cdhio = (CDH_IO_t *)CDH_IO_ADDR;

  //Turn on BD4 Mag to power test port interface
  pwr_ctl(BD4_MAG,PWR_ON);

  for (i=0;i<1000000;i++)
  {
   ;
  }

  print_uart_msg("\nQB50 Columbia/Atlantis Flight Software\n");
  print_uart_msg("V%5.2f -- %s, Ryan P. Miller, Dennis Kanarsky\n",(float)FSW_VERSION/100.0,szDate);
  print_uart_msg("University of Michigan\n");
  print_uart_msg("Space Physics Research Laboratory\n\n");

  //Get NV status
  OP_InitStatus();
  time_code = OP_GetTimeCode();
  set_time(time_code);
  FIP_InitScripts();

  OP_SetFSWVer(FSW_VERSION);

  cdhio->CONTROL1 &= 0xF0;  //Turn off all LEDs

  //print_uart_msg("Bootloader Startup - Phase: %d  Time: %d\n",mission_phase,time_code);
  print_uart_msg("CDH FPGA Version:  %d\n",cdhio->CDH_FPGA_VER);

  //Program timer for 250 millisecond interrupts
  cdhio->TIMER1_DAT3 = 0x00;
  cdhio->TIMER1_DAT2 = 0x5F;
  cdhio->TIMER1_DAT1 = 0x5E;
  cdhio->TIMER1_DAT0 = 0x10;

  cdhio->TIMER1_CTL = 0x01;
  cdhio->INT_CTL = 0x01;

  cdhio->INT_MASK = 0xFE;

  LI1_GetTransConfig();

  //Turn off automatic Beacon Transmission
  LI1_BeaconConfig(0);
  enable_ints();

  WD_DisableOBAutoKick(); //Disable auto-kick

  while (1)
  {
    if  (Get250msFlag())
    {
      //Kick the watchdog
      WD_KickOBWatchdog();

      //Blink the LED
      disable_ints();
      cdhio->CONTROL1 = cdhio->CONTROL1 ^ CTL1_CDH_LED0;
      enable_ints();

      nCount++;

      // IMU2_DoTasks(); //Collect IMU2 data

      // FIP_DoTasks(); //Perform FIPEX Activities

      if ((nCount % 4) == 0)  //Update once per second
      {
        WD_CheckCommandTimeout();//Check telecommand timeout once per second

        TLM_CollectBeaconData();
        ADCS_UpdateAttitude();
        //Send out Beacon data over test port every second
        TLM_UpdateBeaconData(yMissionPhase, TEST_MODE);
        //Send out House Keeping data over test port every second
        TLM_UpdateHKData(TEST_MODE);

        if ((nCount % 40) == 0)
        {
          //transmit once every other 5 seconds
          TLM_UpdateHKData(RADIO_MODE);
        }
        else if ((nCount % 20) == 0)
        {
          //Transmit over radio every 5 seconds
          TLM_UpdateBeaconData(yMissionPhase, RADIO_MODE); //transmit every
        }
        if((nCount % 240) == 0)
        {
         //Store to memory every 60 seconds
         TLM_UpdateBeaconData(yMissionPhase, MEMORY_MODE);
         //store HK to memory...
        }
       }

      //Process any test port commands
      while (!(cdhio->STATUS1 & STS1_CDH_CPU_FIFO_EF))
      {
        nLen = get_test_port_command(buf);
        if (nLen > 0)
        {
          ProcessTelecommand(buf,nLen);
          WD_ResetCommandTimeout();
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
          WD_ResetCommandTimeout();
        }
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
