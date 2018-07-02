#ifndef _UTIL_H
#define _UTIL_H

#include "includes.h"

uint16 CRC16_CCITT(uint8 *pyBuf, int nLen);
uint16 CRC16_CCITT_Partial(uint8 *pyBuf, int nLen, int nInit);
uint32 makeui32_be(uint8 *pBuf, int nOffset);
uint32 makeui32_le(uint8 *pBuf, int nOffset);
uint16 makeui16_be(uint8 *pBuf, int nOffset);
uint16 makeui16_le(uint8 *pBuf, int nOffset);
void PrintBytes(uint8 *pBuf, int nLen);

#endif