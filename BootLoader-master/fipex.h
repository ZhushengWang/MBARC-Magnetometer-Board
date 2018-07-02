/*#ifndef _FIPEX_H
#define _FIPEX_H

#include "includes.h"

#define FIP_MAX_CMD_SIZE  32
#define FIP_TLM_SIZE     205

#define FIP_PING          0x00
#define FIP_INIT          0x01
#define FIP_ID            0x04
#define FIP_RSP           0x10
#define FIP_SP            0x11
#define FIP_HK            0x20
#define FIP_DP            0x21
#define FIP_STDBY         0x0A
#define FIP_SC            0x0B
#define FIP_SM            0x0C
#define FIP_CAL           0x33

void FIP_SendNoParmCmd(uint8 yID);
void FIP_ReadAllBytes(void);

#endif*/