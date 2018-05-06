#include "includes.h"

extern CDH_IO_t *cdhio;

#define nHEADERLEN     12
#define nMAXBYTES      1000
#define FSW_START_ADDR 0x800420
#define FSW_LOAD_ADDR  0x800000

uint8 ayCodeBuf[nMAXBYTES];


int FSW_VerifyCodeParms(uint8 yCode_Data, uint8 yChip, uint32 unAddr)
{
uint8 ayHeader[nHEADERLEN];
uint32 unVer;
uint32 unLen;
uint32 nOffset;
uint32 nBytesRemaining;
uint32 nBytesToRead=0;
int    nCRCInit=1;
uint16 wCRC=0;
uint16 wStoredCRC;

  MRAM_Read(yCode_Data,yChip,unAddr,ayHeader,nHEADERLEN);
  
  if ( (ayHeader[0] == FSW_SYNC0) &&
       (ayHeader[1] == FSW_SYNC1) &&
       (ayHeader[2] == FSW_SYNC2) &&
       (ayHeader[3] == FSW_SYNC3)  )
  {
    unVer = makeui32_be(ayHeader,4);
    unLen = makeui32_be(ayHeader,8);
    
    nBytesRemaining = unLen;
    
    nOffset=nHEADERLEN;
    while (nBytesRemaining > 0)
    {
      WD_KickOBWatchdog();  //This takes a while
      
      if (nBytesRemaining > nMAXBYTES)
      {
        nBytesToRead = nMAXBYTES;
      }
      else
      {
        nBytesToRead = nBytesRemaining;
      }
      MRAM_Read(yCode_Data,yChip,unAddr+nOffset,ayCodeBuf,nBytesToRead);
      wCRC = CRC16_CCITT_Partial(ayCodeBuf,nBytesToRead,nCRCInit);
      nCRCInit=0;
      nBytesRemaining-=nBytesToRead;
      nOffset+=nBytesToRead;
    }
    
    MRAM_Read(yCode_Data,yChip,unAddr+nOffset,ayHeader,2);
    wStoredCRC = makeui16_be(ayHeader,0);
    if (wStoredCRC == wCRC)
    {
      print_uart_msg("FSW Verified Successfully: Ver:%04X  Len:%d  CRC:%04X\n",unVer,unLen,wStoredCRC);
      return(1);
    }
    else
    {
      print_uart_msg("Sync Code Verified, but CRC failed: %04X/%04X\n",wCRC,wStoredCRC);
      return(0);
    }    
  }
  else
  {
    print_uart_msg("Bad sync code in MRAM.\n");
    print_uart_msg("nHeaderLen = %d  %02X %02X %02X %02X\n",nHEADERLEN,ayHeader[0],ayHeader[1],ayHeader[2],ayHeader[3]);
    return(0);
  }
}

int FSW_VerifyCode(uint8 *pBuf)
{
uint8 yCode_Data;
uint8 yChip;
uint32 unAddr;

  yCode_Data = pBuf[3];
  yChip = pBuf[4];
  unAddr = (pBuf[5] << 16) + (pBuf[6] << 8) + pBuf[7];
  
  return(FSW_VerifyCodeParms(yCode_Data,yChip,unAddr));
}


void FSW_CopyCode(uint8 *pBuf)
{
uint8 yDestCode_Data;
uint8 yDestChip;
uint32 unDestAddr;
uint8 ySrcCode_Data;
uint8 ySrcChip;
uint32 unSrcAddr;
uint8 ayHeader[nHEADERLEN];
uint32 unLen;
uint32 nOffset;
uint32 nBytesRemaining;
uint32 nBytesToRead=0;

  yDestCode_Data = pBuf[3];
  yDestChip      = pBuf[4];
  unDestAddr     = (pBuf[5] << 16) + (pBuf[6] << 8) + pBuf[7];
  ySrcCode_Data  = pBuf[8];
  ySrcChip       = pBuf[9];
  unSrcAddr      = (pBuf[10] << 16) + (pBuf[11] << 8) + pBuf[12];

  MRAM_Read(ySrcCode_Data,ySrcChip,unSrcAddr,ayHeader,nHEADERLEN);
  
  if ( (ayHeader[0] == FSW_SYNC0) &&
       (ayHeader[1] == FSW_SYNC1) &&
       (ayHeader[2] == FSW_SYNC2) &&
       (ayHeader[3] == FSW_SYNC3)  )
  {
    unLen = makeui32_be(ayHeader,8);

    MRAM_Write(yDestCode_Data, yDestChip, unDestAddr, ayHeader, nHEADERLEN);
    
    nBytesRemaining = unLen + 2;
    
    nOffset=nHEADERLEN;
    while (nBytesRemaining > 0)
    {
      if (nBytesRemaining > nMAXBYTES)
      {
        nBytesToRead = nMAXBYTES;
      }
      else
      {
        nBytesToRead = nBytesRemaining;
      }
      MRAM_Read(ySrcCode_Data,ySrcChip,unSrcAddr+nOffset,ayCodeBuf,nBytesToRead);
      MRAM_Write(yDestCode_Data,yDestChip,unDestAddr+nOffset,ayCodeBuf,nBytesToRead);
      nBytesRemaining-=nBytesToRead;
      nOffset+=nBytesToRead;
    }
    print_uart_msg("FSW copy complete.  Verifying...\n");
    
    FSW_VerifyCodeParms(yDestCode_Data,yDestChip,unDestAddr);
  }
  else
  {
    print_uart_msg("Copy Error:  Bad source sync code.\n");
  }     
}  

int FSW_Load(uint8 yCode_Data, uint8 yChip, uint32 unAddr)
{
uint8 ayHeader[nHEADERLEN];
uint32 unVer;
uint32 unLen;
uint32 nOffset = 0;
uint32 nBytesRemaining;
uint16 wCRC=0;
uint16 wStoredCRC;
uint8  *pFSWLocation = (uint8 *)FSW_LOAD_ADDR;

  MRAM_Read(yCode_Data,yChip,unAddr,ayHeader,nHEADERLEN);
  
  if ( (ayHeader[0] == FSW_SYNC0) &&
       (ayHeader[1] == FSW_SYNC1) &&
       (ayHeader[2] == FSW_SYNC2) &&
       (ayHeader[3] == FSW_SYNC3)  )
  {
    unVer = makeui32_be(ayHeader,4);
    unLen = makeui32_be(ayHeader,8);
    
    nBytesRemaining = unLen;
    
    nOffset=nHEADERLEN;
    
    print_uart_msg("Loading %d bytes to location %p\n",unLen,pFSWLocation);
    
    MRAM_Read(yCode_Data,yChip,unAddr+nOffset,pFSWLocation,nBytesRemaining);
    wCRC = CRC16_CCITT(pFSWLocation,nBytesRemaining);
    
    nOffset+=nBytesRemaining;
    
    MRAM_Read(yCode_Data,yChip,unAddr+nOffset,ayHeader,2);
    wStoredCRC = makeui16_be(ayHeader,0);
    if (wStoredCRC == wCRC)
    {
      print_uart_msg("FSW Verified Successfully: Ver:%04X  Len:%d  CRC:%04X\n",unVer,unLen,wCRC);
      return(1);
    }
    else
    {
      print_uart_msg("Sync Code Verified, but CRC failed: %04X/%04X\n",wCRC,wStoredCRC);
      return(0);
    }    
  }
  else
  {
    print_uart_msg("Bad sync code in MRAM.\n");
    print_uart_msg("nHeaderLen = %d  %02X %02X %02X %02X\n",nHEADERLEN,ayHeader[0],ayHeader[1],ayHeader[2],ayHeader[3]);
    return(0);
  }
}

void FSW_BootParams(uint8 yCode_Data, uint8 yChip, uint32 unAddr)
{
typedef void FSW_Start(void);

  if (FSW_Load(yCode_Data, yChip, unAddr))
  {
    disable_ints();
    
    cdhio->INT_MASK = 0xFF;  
    cdhio->TIMER1_CTL = 0x00;
    cdhio->INT_CTL = 0x01;
    
    ((FSW_Start *)FSW_START_ADDR)();
   
  }
}

void FSW_Boot(uint8 *pBuf)
{
uint8 yCode_Data;
uint8 yChip;
uint32 unAddr;

  yCode_Data = pBuf[3];
  yChip      = pBuf[4];
  unAddr     = (pBuf[5] << 16) + (pBuf[6] << 8) + pBuf[7];
  
  FSW_BootParams(yCode_Data,yChip,unAddr);
}

void FSW_BootPartition(uint8 yPartition)
{
uint8 yCode_Data;
uint8 yChip;
uint32 unAddr;

  switch (yPartition)
  {
    case 0:
      yCode_Data = 0;
      yChip = 0;
      unAddr = 0;
      break;

    case 1:
      yCode_Data = 0;
      yChip = 1;
      unAddr = 0;
      break;

    case 2:
      yCode_Data = 1;
      yChip = 0;
      unAddr = 0;
      break;      

    case 3:
      yCode_Data = 1;
      yChip = 1;
      unAddr = 0;
      break;      

    default:
      print_uart_msg("Error:  Invalid Partition (%d)\n",yPartition);
      return;
      break;      
  }
  
  FSW_BootParams(yCode_Data,yChip,unAddr);
}
  
  
               