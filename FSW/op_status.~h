#ifndef _OP_STATUS_H
#define _OP_STATUS_H

#include "includes.h"

#pragma pack(1)

//Keep this struct the same length for boot loader and fsw
typedef volatile struct
{
  uint32 sync;
  uint32 mission_phase;
  uint32 time_code;
  uint32 last_boot;
  uint32 bootloader_ver;
  uint32 fsw_ver;
  uint32 fsw_active_partition;
  uint32 boot_count;
  uint32 comm_count;
  uint32 deploy_count;
  uint32 fip_active_script;
  uint32 fip_script_count;
  uint32 radio_tx_enable;
  uint32 initial_wait;
  uint32 enable_deploy;
  uint32 fip_script_proc_enable;
  uint32 FIP_M1WPtr;
  uint32 FIP_M1RPtr;
  uint32 FIP_M2WPtr;
  uint32 FIP_M2RPtr;
  uint32 FIP_M1SDPCount;
  uint32 FIP_M1HKCount;
  uint32 FIP_M2SDPCount;
  uint32 FIP_M2HKCount;
  uint32 spare_array[100];
  uint32 crc;
} nv_status_struct_t;

#pragma pack()

// Boot Loader Phases
#define BL_FIRST_TURNON  1
#define BL_INITIAL_WAIT  2
#define BL_DEPLOY        3
#define BL_NORMAL_BOOT1  4
#define BL_NORMAL_BOOT2  5
#define BL_NORMAL_BOOT3  6
#define BL_NORMAL_BOOT4  7
#define BL_NORMAL_BOOT5  8
#define BL_NORMAL_BOOT6  9
#define BL_COMMAND1      10
#define BL_COMMAND2      11
#define BL_NORMAL_TURNON 12
#define BL_LOAD_FSW      13

void OP_InitStatus(void);
void OP_SetTimecodeFromISR(uint32 time_code);
void OP_SetBootTime(uint32 time_code);
uint32 OP_GetBootTime(void);
uint32 OP_GetTimeCode(void);
uint8 OP_GetMissionPhase(void);
void OP_SetMissionPhase(uint8 phase);
void OP_GetNVStatus(nv_status_struct_t *op_status);
void OP_SetNVStatus(nv_status_struct_t *op_status);
void OP_PrintStatus1Bytes(void);
void OP_FormatStatus(int nStruct);
void OP_IncrementBootCount(void);
uint32 OP_GetBootCount(void);
void OP_IncrementCommCount(void);
uint32 OP_GetCommCount(void);
void OP_IncrementDeployCount(void);
uint32 OP_GetDeployCount(void);
void OP_InitDeployCount(void);
void OP_SetFSWVer(uint32 nVer);
uint32 OP_GetFSWVer(void);
void OP_SetBootVer(uint32 nVer);
uint32 OP_GetBootVer(void);
void OP_SetActiveFSWPartition(uint8 yPart);
uint8 OP_GetActiveFSWPartition(void);
void OP_SetTXEnable(uint8 yEnable);
uint8 OP_GetTXEnable(void);
void OP_SetInitialWait(uint32 unInitialWait);
uint32 OP_GetInitialWait(void);
void OP_PrintStatus(uint8 yStat);
void OP_SetEnableDeploy(uint8 unEnableDeploy);
uint32 OP_GetEnableDeploy(void);
void OP_SetFIPScriptCount(uint8 yCount);
uint8 OP_GetFIPScriptCount(void);
uint8 OP_GetActiveFIPScript(void);
void OP_SetActiveFIPScript(uint8 yScript);
uint32 OP_GetFIPScriptProcEnable(void);
void OP_SetFIPScriptProcEnable(uint32 unEnable);
uint32 OP_GetFIPM1WPtr(void);
void OP_SetFIPM1WPtr(uint32 unPtr);
uint32 OP_GetFIPM1RPtr(void);
void OP_SetFIPM1RPtr(uint32 unPtr);
uint32 OP_GetFIPM2WPtr(void);
void OP_SetFIPM2WPtr(uint32 unPtr);
uint32 OP_GetFIPM2RPtr(void);
void OP_SetFIPM2RPtr(uint32 unPtr);
uint32 OP_GetFIPM1SDPCount(void);
void OP_SetFIPM1SDPCount(uint32 unCnt);
uint32 OP_GetFIPM1HKCount(void);
void OP_SetFIPM1HKCount(uint32 unCnt);
uint32 OP_GetFIPM2SDPCount(void);
void OP_SetFIPM2SDPCount(uint32 unCnt);
uint32 OP_GetFIPM2HKCount(void);
void OP_SetFIPM2HKCount(uint32 unCnt);
void OP_IncrementM1SDPCount(void);
void OP_IncrementM1HKCount(void);
void OP_DecrementM1SDPCount(void);
void OP_DecrementM1HKCount(void);
void OP_IncrementM2SDPCount(void);
void OP_IncrementM2HKCount(void);
void OP_DecrementM2SDPCount(void);
void OP_DecrementM2HKCount(void);
#endif