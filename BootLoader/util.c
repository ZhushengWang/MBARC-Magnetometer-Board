#include "includes.h"

const uint16 POLY = 0x1021;

uint16 CRC16_CCITT(uint8 *pyBuf, int nLen)
{
  int j = 0;
  int i;
  int sz;
  uint16 crc = 0;

  sz = nLen;
  while (--sz >= 0)
  {
    crc ^= (uint16)((uint16)pyBuf[j++] << 8);
    for (i = 0; i < 8; i++)
    {
      if ((crc & 0x8000) != 0)
      {
        crc = (uint16)((crc << 1) ^ POLY);
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc;
}  

uint16 CRC16_CCITT_Partial(uint8 *pyBuf, int nLen, int nInit)
{
  int j = 0;
  int i;
  int sz;
  static uint16 crc;

  if (nInit)
  {
    crc = 0;
  }
  
  sz = nLen;
  while (--sz >= 0)
  {
    crc ^= (uint16)((uint16)pyBuf[j++] << 8);
    for (i = 0; i < 8; i++)
    {
      if ((crc & 0x8000) != 0)
      {
        crc = (uint16)((crc << 1) ^ POLY);
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc;
} 

uint32 makeui32_be(uint8 *pBuf, int nOffset)
{
  uint32 nVal;
  uint8 *pnVal = (uint8 *)&nVal;
  
  pnVal[0] = pBuf[nOffset];
  pnVal[1] = pBuf[nOffset+1];
  pnVal[2] = pBuf[nOffset+2];
  pnVal[3] = pBuf[nOffset+3];
    
  return(nVal); 
}

uint32 makeui32_le(uint8 *pBuf, int nOffset)
{
  uint32 nVal;
  uint8 *pnVal = (uint8 *)&nVal;
  
  pnVal[3] = pBuf[nOffset];
  pnVal[2] = pBuf[nOffset+1];
  pnVal[1] = pBuf[nOffset+2];
  pnVal[0] = pBuf[nOffset+3];
    
  return(nVal); 
}

uint16 makeui16_be(uint8 *pBuf, int nOffset)
{
  uint16 wVal;
  uint8 *pwVal = (uint8 *)&wVal;
  
  pwVal[0] = pBuf[nOffset];
  pwVal[1] = pBuf[nOffset+1];

  return(wVal); 
}

uint16 makeui16_le(uint8 *pBuf, int nOffset)
{
  uint16 wVal;
  uint8 *pwVal = (uint8 *)&wVal;
  
  pwVal[1] = pBuf[nOffset];
  pwVal[0] = pBuf[nOffset+1];

  return(wVal); 
}

void PrintBytes(uint8 *pBuf, int nLen)
{
int   nBytes=1;
char  szLine[100];
char  szVal[4];
int   i;

  strcpy(szLine,"");
  for (i=0;i<nLen;i++)
  {    
    sprintf(szVal,"%02X ",pBuf[i]);
    
    strcat(szLine,szVal);
    if ((nBytes % 8) == 0)
    {
      strcat(szLine,"\n");
      print_uart_msg(szLine);
      strcpy(szLine,"");
    }
    nBytes++;
  }
  strcat(szLine,"\n");
  print_uart_msg(szLine);
}