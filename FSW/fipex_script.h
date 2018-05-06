#ifndef _FIPEX_SCRIPT_H
#define _FIPEX_SCRIPT_H

#include "includes.h"

#pragma pack(1)

typedef struct 
{
  uint8 yLen;
  uint32 unStartTime;
  uint16 uwRepeatTime;
  uint8 yCmdCnt;
  uint8 ayCmdBytes[256];
} SUSCRIPT_STRUCT_t;
  
typedef struct 
{
  uint32 unSync;
  uint16 uwLen;
  SUSCRIPT_STRUCT_t suScript;
  uint16 uwCRC;
} SCRIPT_STRUCTURE_t;


#pragma pack()

#define FIP_SCRIPT_ADDRESS  0xBFF800
#define FIP_MAX_SCRIPTS     7
#define FIP_SCRIPT_SYNC     0x5AA51234

#define FIP_SCRIPT_START      0
#define FIP_SCRIPT_WAIT1      1
#define FIP_SCRIPT_GETCMD     2
#define FIP_SCRIPT_EXEC_OBC   3
#define FIP_SCRIPT_EXEC_ONOFF 4
#define FIP_SCRIPT_EXEC_END1  5
#define FIP_SCRIPT_EXEC_END   6
#define FIP_SCRIPT_EXEC_SU    7
#define FIP_SCRIPT_EXEC_DELAY 8
#define FIP_SCRIPT_POWER_ON1  9
#define FIP_SCRIPT_POWER_ON2  10
#define FIP_SCRIPT_ERROR1     11
#define FIP_SCRIPT_ERROR2     12
#define FIP_SCRIPT_ERROR3     13
#define FIP_SCRIPT_ERROR4     14


void FIP_InitScripts(void);
void FIP_PrintScript(uint8 yScript);
void FIP_StoreScript(uint8 yScript, SCRIPT_STRUCTURE_t *pScript);

int FIP_StoreScriptBytes(uint8 yScript, 
                         uint8 nOffset, 
                         uint8 yLen, 
                         uint8 *pScriptBytes);
                         
void FIP_ReadScript(uint8 yScript, SCRIPT_STRUCTURE_t *pScript);
int FIP_VerifyScript(uint8 yScript);
uint8 FIP_GetScriptLen(uint8 yScript);
uint32 FIP_GetScriptStartTime(uint8 yScript);
uint16 FIP_GetScriptRepeatTime(uint8 yScript);
uint8 FIP_GetScriptCmdCount(uint8 yScript);
void FIP_EraseScript(uint8 yScript);
uint8 FIP_GetCmdLen(uint8 yScript, uint8 yCmdNum);
void FIP_SendScriptCmd(uint8 yScript, uint8 yCmdNum);
uint16 FIP_GetCmdDelay(uint8 yScript, uint8 yCmdNum);
uint8 FIP_GetCmdID(uint8 yScript, uint8 yCmdNum);
int FIP_SetNextActive(void);
void FIP_ListScripts(void);
void FIP_SetScriptProcEnable(uint8 yEnable);
void FIP_RunScript(int nStart);
uint16 FIP_GetScriptState(void);
uint16 FIP_GetScriptStep(void);


#endif