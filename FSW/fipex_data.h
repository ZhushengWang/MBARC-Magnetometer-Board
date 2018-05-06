#ifndef _FIPEX_DATA_H
#define _FIPEX_DATA_H

#include "includes.h"

#define FIP_SDP_PKTTYPE  0xEE
#define FIP_HK_PKTTYPE   0xDD

void FIPData_StoreData(uint8 *pData, int unLen, uint8 yDataType);
void FIPData_RetrieveData(uint8 *pData, int *pnLen, uint8 yMem, uint8 *pPktType);
void FIPData_EraseData(uint8 yMem, uint32 unEndTime);
void FIPData_InitRetrieval(void);

#endif