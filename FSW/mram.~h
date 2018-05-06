#ifndef _MRAM_H
#define _MRAM_H

#include "includes.h"

#define MRAM_CODE   0
#define MRAM_DATA   1
#define MRAM_CHIP0  0
#define MRAM_CHIP1  1

void MRAM_WriteCode(int nChip, uint32 unAddr, uint8 *pWriteBuf, int nLen);
void MRAM_WriteData(int nChip, uint32 unAddr, uint8 *pWriteBuf, int nLen);
void MRAM_ReadCode(int nChip, uint32 unAddr, uint8 *pReadBuf, int nLen);
void MRAM_ReadData(int nChip, uint32 unAddr, uint8 *pReadBuf, int nLen);
void MRAM_Write(int yCode_Data, int nChip, uint32 unAddr, uint8 *pWriteBuf, int nLen);
void MRAM_Read(int yCode_Data, int nChip, uint32 unAddr, uint8 *pReadBuf, int nLen);

#endif