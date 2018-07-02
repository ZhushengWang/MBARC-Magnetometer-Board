#include "includes.h"

#define NVSTAT_ADDR1  0x00BFE000
#define NVSTAT_ADDR2  0x00BFF000

#define OPSTAT_SYNC 0x5AA51234

nv_status_struct_t *op_status1;
nv_status_struct_t *op_status2;

void OP_AddCRC(nv_status_struct_t *op_status)
{
  op_status->crc = CRC16_CCITT((uint8 *)op_status, sizeof(nv_status_struct_t)-2);
}

void OP_FormatStatus(int nStruct)
{
  nv_status_struct_t *op_status = NULL;
  
  if (nStruct == 1)
  {
    op_status = op_status1;
  }
  else
  {
    if (nStruct == 2)
    {
      op_status = op_status2;
    }
  }
  
  if (op_status != NULL)
  {
    op_status->sync = OPSTAT_SYNC;
    op_status->mission_phase = BL_FIRST_TURNON;
    op_status->time_code = 0;
    op_status->last_boot = 0;
    op_status->bootloader_ver = 0;
    op_status->fsw_ver = 0;
    op_status->fsw_active_partition = 0;
    op_status->boot_count = 0;
    op_status->comm_count = 0;
    op_status->deploy_count = 0;
    op_status->fip_active_script = 0;
    op_status->fip_script_count = 0;
    op_status->radio_tx_enable = 1;
    op_status->initial_wait = INITIAL_WAIT_SECS;
    op_status->enable_deploy = 1;
    op_status->spare2 = 0;
    op_status->spare3 = 0;
    op_status->spare4 = 0;
    op_status->spare5 = 0;
    op_status->spare6 = 0;
    op_status->spare7 = 0;
    op_status->spare8 = 0;
    op_status->spare9 = 0;
    op_status->spare10 = 0;
    
    OP_AddCRC(op_status);
  }
}

void OP_InitStatus(void)
{
  int op1_good = 0;
  int op2_good = 0;
  
  op_status1 = (nv_status_struct_t *)NVSTAT_ADDR1;
  op_status2 = (nv_status_struct_t *)NVSTAT_ADDR2;
    
  //Check 1
  if ((op_status1->sync == OPSTAT_SYNC) &&
      (op_status1->crc == CRC16_CCITT((uint8 *)op_status1, sizeof(nv_status_struct_t)-2)))
  {
    op1_good = 1;
    print_uart_msg("Good NV Status (1) found at %p, %d bytes\n",(void *)op_status1,sizeof(*op_status1));
  }
  else
  {
    op1_good = 0;
    print_uart_msg("Bad NV Status (1) found at %p\n",op_status1);
  }
  //Check 2
  if ((op_status2->sync == OPSTAT_SYNC) &&
      (op_status2->crc == CRC16_CCITT((uint8 *)op_status2, sizeof(nv_status_struct_t)-2)))
  {
    op2_good = 1;
    print_uart_msg("Good NV Status (2) found at %p, %d bytes\n",(void *)op_status2, sizeof(*op_status2));
  }
  else
  {
    op2_good = 0;
    print_uart_msg("Bad NV Status (2) found at %p\n",op_status2);
  }
  
  if ((op1_good == 1) && (op2_good == 0))
  {
    memcpy((void *)op_status2,(void *)op_status1,sizeof(nv_status_struct_t));
    print_uart_msg("Copying NV Status (1) to NV Status (2)\n");
  }
  else
  {
    if ((op1_good == 0) && (op2_good == 1))
    {
      memcpy((void *)op_status1,(void *)op_status2,sizeof(nv_status_struct_t));
      print_uart_msg("Copying NV Status (2) to NV Status (1)\n");
    }
    else
    {
      if ((op1_good == 0) && (op2_good == 0))
      {
        print_uart_msg("No good NV status found.  Formatting...\n");
        disable_ints();
        set_time(0);
        OP_FormatStatus(1);
        OP_FormatStatus(2);
        enable_ints();
      }
      else
      {
        //Both structures are good, but differ, pick latest
        if ((op1_good == 1) && (op2_good == 1) && 
            (op_status1->crc != op_status2->crc)  )
        {
          if (op_status1->time_code > op_status2->time_code)
          {
            memcpy((void *)op_status2,(void *)op_status1,sizeof(nv_status_struct_t));
          }
          else
          {
            if (op_status2->time_code > op_status1->time_code)
            {
              memcpy((void *)op_status1,(void *)op_status2,sizeof(nv_status_struct_t));
            }
          }
        }
      }
    }
  }      
}


uint32 OP_GetTimeCode(void)
{
  return(op_status1->time_code);
}

void OP_SetTimecodeFromISR(uint32 time_code)
{
  op_status1->time_code = time_code;
  OP_AddCRC(op_status1);
  op_status2->time_code = time_code;
  OP_AddCRC(op_status2);
}

void OP_SetBootTime(uint32 time_code)
{
  disable_ints();
  op_status1->last_boot = time_code;
  OP_AddCRC(op_status1);
  op_status2->last_boot = time_code;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint8 OP_GetMissionPhase(void)
{
  return(op_status1->mission_phase);
}

void OP_SetMissionPhase(uint8 phase)
{
  disable_ints();
  op_status1->mission_phase = phase;
  OP_AddCRC(op_status1);
  op_status2->mission_phase = phase;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_GetNVStatus(nv_status_struct_t *op_status)
{
  op_status = op_status1;
}

void OP_SetNVStatus(nv_status_struct_t *op_status)
{
  disable_ints();
  op_status1 = op_status;
  OP_AddCRC(op_status1);
  op_status2 = op_status;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_PrintStatus1Bytes(void)
{
  int i;
  uint8 *pStatus = (uint8 *)op_status1;
  
  for (i=0;i<sizeof(nv_status_struct_t);i++)
  {
    print_uart_msg("OS: %02X\n",pStatus[i]);
  }
}

void OP_IncrementBootCount(void)
{
  disable_ints();
  op_status1->boot_count++;
  OP_AddCRC(op_status1);
  op_status2->boot_count++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_IncrementCommCount(void)
{
  disable_ints();
  op_status1->comm_count++;
  OP_AddCRC(op_status1);
  op_status2->comm_count++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_IncrementDeployCount(void)
{
  disable_ints();
  op_status1->deploy_count++;
  OP_AddCRC(op_status1);
  op_status2->deploy_count++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_InitDeployCount(void)
{
  op_status1->deploy_count = 0;  //No int disable/enable
  OP_AddCRC(op_status1);
  op_status2->deploy_count = 0;
  OP_AddCRC(op_status2);
}

void OP_SetFSWVer(uint32 nVer)
{
  disable_ints();
  op_status1->fsw_ver = nVer;
  OP_AddCRC(op_status1);
  op_status2->fsw_ver = nVer;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_SetBootVer(uint32 nVer)
{
  disable_ints();
  op_status1->bootloader_ver = nVer;
  OP_AddCRC(op_status1);
  op_status2->bootloader_ver = nVer;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetBootVer(void)
{
  return(op_status1->bootloader_ver);
}

void OP_SetEnableDeploy(uint8 unEnableDeploy)
{
  disable_ints();
  op_status1->enable_deploy = unEnableDeploy;
  OP_AddCRC(op_status1);
  op_status2->enable_deploy = unEnableDeploy;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetEnableDeploy(void)
{
  return(op_status1->enable_deploy);
}

void OP_SetActiveFSWPartition(uint8 yPart)
{
  disable_ints();
  op_status1->fsw_active_partition = yPart;
  OP_AddCRC(op_status1);
  op_status2->fsw_active_partition = yPart;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint8 OP_GetActiveFSWPartition(void)
{
  return(op_status1->fsw_active_partition);
}

void OP_SetTXEnable(uint8 yEnable)
{
  disable_ints();
  op_status1->radio_tx_enable = yEnable;
  OP_AddCRC(op_status1);
  op_status2->radio_tx_enable = yEnable;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint8 OP_GetTXEnable(void)
{
  return(op_status1->radio_tx_enable);
}

void OP_SetInitialWait(uint32 unInitialWait)
{  
  disable_ints();
  op_status1->initial_wait = unInitialWait;
  OP_AddCRC(op_status1);
  op_status2->initial_wait = unInitialWait;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetInitialWait(void)
{
  return(op_status1->initial_wait);
}

void OP_PrintStatus(uint8 yStat)
{
char sMsg[256];

  nv_status_struct_t *op_status = NULL;
  int nStat = yStat;
  
  if (yStat == 1)
  {
    op_status = op_status1;
  }
  else
  {
    if (yStat == 2)
    {
      op_status = op_status2;
    }
    else
    {
      op_status = op_status1;
      nStat = 1;
    }
  }
  
  if (op_status != NULL)
  {
    sprintf(sMsg,"OpStatus Data %d:\n\n"
                 "  Sync:          %08lX\n"
                 "  Mission Phase: %lu\n"
                 "  Time Code:     %lu\n"
                 "  Last Boot:     %lu\n"
                 "  BootLoader Ver:%lu\n"
                 "  FSW Ver:       %lu\n",
                 yStat,
                 op_status->sync,
                 op_status->mission_phase,
                 op_status->time_code,
                 op_status->last_boot,
                 op_status->bootloader_ver,
                 op_status->fsw_ver);
                 
    send_uart_str(sMsg);
     
    sprintf(sMsg,"  FSW Act. Part: %lu\n"
                 "  Boot Count:    %lu\n"
                 "  Comm Count:    %lu\n"
                 "  Deploy Count:  %lu\n"
                 "  FIP Script:    %lu\n"
                 "  FIP Script Cnt:%lu\n",
                 op_status->fsw_active_partition,
                 op_status->boot_count,
                 op_status->comm_count,
                 op_status->deploy_count,
                 op_status->fip_active_script,
                 op_status->fip_script_count);
                 
    send_uart_str(sMsg);
    
    sprintf(sMsg,"  Radio TX Ena:  %lu\n"
                 "  Initial Wait:  %lu\n"
                 "  Enable Deploy: %lu\n"
                 "  Spare2:        %lu\n"
                 "  Spare3:        %lu\n"
                 "  Spare4:        %lu\n",
                 op_status->radio_tx_enable,
                 op_status->initial_wait,
                 op_status->enable_deploy,
                 op_status->spare2,
                 op_status->spare3,
                 op_status->spare4);
                 
    send_uart_str(sMsg);
    
    sprintf(sMsg,"  Spare5:        %lu\n"
                 "  Spare6:        %lu\n"
                 "  Spare7:        %lu\n"
                 "  Spare8:        %lu\n"
                 "  Spare9:        %lu\n"
                 "  Spare10        %lu\n"
                 "  CRC            %08lX\n",
                 op_status->spare5,
                 op_status->spare6,
                 op_status->spare7,
                 op_status->spare8,
                 op_status->spare9,
                 op_status->spare10,
                 op_status->crc);
                 
    send_uart_str(sMsg);                                   
  }
  else
  {
    print_uart_msg("Error:  Op_status is NULL\n");
  }
 } 
 
