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
    op_status->fip_script_proc_enable = 1;
    op_status->FIP_M1WPtr = 0;
    op_status->FIP_M1RPtr = 0;
    op_status->FIP_M2WPtr = 0;
    op_status->FIP_M2WPtr = 0;
    op_status->FIP_M1SDPCount = 0;
    op_status->FIP_M1HKCount = 0;
    op_status->FIP_M2SDPCount = 0;
    op_status->FIP_M2HKCount = 0;
    
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

uint32 OP_GetBootTime(void)
{
  return(op_status1->last_boot);
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

uint32 OP_GetBootCount(void)
{
  return(op_status1->boot_count);
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

uint32 OP_GetCommCount(void)
{
  return(op_status1->comm_count);
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

uint32 OP_GetDeployCount(void)
{
  return(op_status1->deploy_count);
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

uint32 OP_GetFSWVer(void)
{
  return(op_status1->fsw_ver);
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

uint8 OP_GetActiveFIPScript(void)
{
  return(op_status1->fip_active_script);
}

void OP_SetActiveFIPScript(uint8 yScript)
{
  disable_ints();
  op_status1->fip_active_script = yScript;
  OP_AddCRC(op_status1);
  op_status2->fip_active_script = yScript;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint8 OP_GetFIPScriptCount(void)
{
  return(op_status1->fip_script_count);
}

void OP_SetFIPScriptCount(uint8 yCount)
{
  disable_ints();
  op_status1->fip_script_count = yCount;
  OP_AddCRC(op_status1);
  op_status2->fip_script_count = yCount;
  OP_AddCRC(op_status2);
  enable_ints();
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
                 "  FIP_Script_En: %lu\n"
                 "  FIP_M1WPtr:    %lu\n"
                 "  FIP_M1RPtr:    %lu\n",
                 op_status->radio_tx_enable,
                 op_status->initial_wait,
                 op_status->enable_deploy,
                 op_status->fip_script_proc_enable,
                 op_status->FIP_M1WPtr,
                 op_status->FIP_M1RPtr);
                 
    send_uart_str(sMsg);
    
    sprintf(sMsg,"  FIP_M2WPtr:    %lu\n"
                 "  FIP_M2RPtr:    %lu\n"
                 "  FIP_M1SDPCnt:  %lu\n"
                 "  FIP_M1HKCnt:   %lu\n"
                 "  FIP_M2SDPCnt:  %lu\n"
                 "  FIP_M2HKCnt    %lu\n"
                 "  CRC            %08lX\n",
                 op_status->FIP_M2WPtr,
                 op_status->FIP_M2RPtr,
                 op_status->FIP_M1SDPCount,
                 op_status->FIP_M1HKCount,
                 op_status->FIP_M2SDPCount,
                 op_status->FIP_M2HKCount,
                 op_status->crc);
                 
    send_uart_str(sMsg);                                   
  }
  else
  {
    print_uart_msg("Error:  Op_status is NULL\n");
  }
 } 
 
uint32 OP_GetFIPScriptProcEnable(void)
{
  return(op_status1->fip_script_proc_enable);
}

void OP_SetFIPScriptProcEnable(uint32 unEnable)
{
  disable_ints();
  op_status1->fip_script_proc_enable = unEnable;
  OP_AddCRC(op_status1);
  op_status2->fip_script_proc_enable = unEnable;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM1WPtr(void)
{
  return(op_status1->FIP_M1WPtr);
}

void OP_SetFIPM1WPtr(uint32 unPtr)
{
  disable_ints();
  op_status1->FIP_M1WPtr = unPtr;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1WPtr = unPtr;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM1RPtr(void)
{
  return(op_status1->FIP_M1RPtr);
}

void OP_SetFIPM1RPtr(uint32 unPtr)
{
  disable_ints();
  op_status1->FIP_M1RPtr = unPtr;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1RPtr = unPtr;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM2WPtr(void)
{
  return(op_status1->FIP_M2WPtr);
}

void OP_SetFIPM2WPtr(uint32 unPtr)
{
  disable_ints();
  op_status1->FIP_M2WPtr = unPtr;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2WPtr = unPtr;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM2RPtr(void)
{
  return(op_status1->FIP_M2RPtr);
}

void OP_SetFIPM2RPtr(uint32 unPtr)
{
  disable_ints();
  op_status1->FIP_M2RPtr = unPtr;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2RPtr = unPtr;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM1SDPCount(void)
{
  return(op_status1->FIP_M1SDPCount);
}

void OP_SetFIPM1SDPCount(uint32 unCnt)
{
  disable_ints();
  op_status1->FIP_M1SDPCount = unCnt;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1SDPCount = unCnt;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM1HKCount(void)
{
  return(op_status1->FIP_M1HKCount);
}

void OP_SetFIPM1HKCount(uint32 unCnt)
{
  disable_ints();
  op_status1->FIP_M1HKCount = unCnt;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1HKCount = unCnt;
  OP_AddCRC(op_status2);
  enable_ints();
}
 
uint32 OP_GetFIPM2SDPCount(void)
{
  return(op_status1->FIP_M2SDPCount);
}

void OP_SetFIPM2SDPCount(uint32 unCnt)
{
  disable_ints();
  op_status1->FIP_M2SDPCount = unCnt;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2SDPCount = unCnt;
  OP_AddCRC(op_status2);
  enable_ints();
}

uint32 OP_GetFIPM2HKCount(void)
{
  return(op_status1->FIP_M2HKCount);
}

void OP_SetFIPM2HKCount(uint32 unCnt)
{
  disable_ints();
  op_status1->FIP_M2HKCount = unCnt;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2HKCount = unCnt;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_IncrementM1SDPCount(void)
{
  disable_ints();
  op_status1->FIP_M1SDPCount++;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1SDPCount++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_IncrementM1HKCount(void)
{
  disable_ints();
  op_status1->FIP_M1HKCount++;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1HKCount++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_DecrementM1SDPCount(void)
{
  disable_ints();
  op_status1->FIP_M1SDPCount--;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1SDPCount--;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_DecrementM1HKCount(void)
{
  disable_ints();
  op_status1->FIP_M1HKCount--;
  OP_AddCRC(op_status1);
  op_status2->FIP_M1HKCount--;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_IncrementM2SDPCount(void)
{
  disable_ints();
  op_status1->FIP_M2SDPCount++;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2SDPCount++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_IncrementM2HKCount(void)
{
  disable_ints();
  op_status1->FIP_M2HKCount++;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2HKCount++;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_DecrementM2SDPCount(void)
{
  disable_ints();
  op_status1->FIP_M2SDPCount--;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2SDPCount--;
  OP_AddCRC(op_status2);
  enable_ints();
}

void OP_DecrementM2HKCount(void)
{
  disable_ints();
  op_status1->FIP_M2HKCount--;
  OP_AddCRC(op_status1);
  op_status2->FIP_M2HKCount--;
  OP_AddCRC(op_status2);
  enable_ints();
}