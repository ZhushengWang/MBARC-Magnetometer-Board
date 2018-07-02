#include "includes.h"

#define WP_ON    1
#define WP_OFF   0

#define CS_ON    1
#define CS_OFF   0

#define WREN_CMD  0x06
#define WRDI_CMD  0x04
#define RDSR_CMD  0x05
#define WRSR_CMD  0x01
#define READ_CMD  0x03
#define WRITE_CMD 0x02
#define SLEEP_CMD 0xB9
#define WAKE_CMD  0xAB

extern CDH_IO_t *cdhio;

int MRAM_WaitForReady(void)
{
  int nCount = 0;
  
  while ((!(cdhio->STATUS1 & STS1_CDH_MRAM_READY)) && (nCount <= 100))
  {
    nCount++;
  }
  
  if (nCount < 100)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

void MRAM_SetCodeWP(int nWP_On)
{
  if (nWP_On == WP_ON)
  {
    cdhio->MRAM_CTL_REG &= ~MRAM_CTL_REG_CODE_NWP;
  }
  else
  {
    cdhio->MRAM_CTL_REG |= MRAM_CTL_REG_CODE_NWP;
  }
}

void MRAM_SetDataWP(int nWP_On)
{
  if (nWP_On == WP_ON)
  {
    cdhio->MRAM_CTL_REG &= ~MRAM_CTL_REG_DATA_NWP;
  }
  else
  {
    cdhio->MRAM_CTL_REG |= MRAM_CTL_REG_DATA_NWP;
  }
}

void MRAM_SetCodeCS(int nCodeChip, int nCS_Active)
{
  switch (nCodeChip)
  {
    case 0:
      if (nCS_Active == CS_ON)
      {
        cdhio->MRAM_CTL_REG |= MRAM_CTL_REG_C0_CS;
      }
      else
      {
        cdhio->MRAM_CTL_REG &= ~MRAM_CTL_REG_C0_CS;
      }
      break;
      
    case 1:
      if (nCS_Active == CS_ON)
      {
        cdhio->MRAM_CTL_REG |= MRAM_CTL_REG_C1_CS;
      }
      else
      {
        cdhio->MRAM_CTL_REG &= ~MRAM_CTL_REG_C1_CS;
      }
      break;
    
    default:
      print_uart_msg("MRAM:  Error, bad code chip specified.\n");
      break;
  }
}

void MRAM_SetDataCS(int nDataChip, int nCS_Active)
{
  switch (nDataChip)
  {
    case 0:
      if (nCS_Active == CS_ON)
      {
        cdhio->MRAM_CTL_REG |= MRAM_CTL_REG_D0_CS;
      }
      else
      {
        cdhio->MRAM_CTL_REG &= ~MRAM_CTL_REG_D0_CS;
      }
      break;
      
    case 1:
      if (nCS_Active == CS_ON)
      {
        cdhio->MRAM_CTL_REG |= MRAM_CTL_REG_D1_CS;
      }
      else
      {
        cdhio->MRAM_CTL_REG &= ~MRAM_CTL_REG_D1_CS;
      }
      break;
    
    default:
      print_uart_msg("MRAM:  Error, bad code chip specified.\n");
      break;
  }
}

void MRAM_SetCodeWriteable(int nChip)
{
  MRAM_SetCodeWP(WP_OFF);
  MRAM_SetCodeCS(nChip,CS_ON);
  
  cdhio->MRAM_CTL = WREN_CMD;
  
  MRAM_WaitForReady();
  
  MRAM_SetCodeCS(nChip,CS_OFF);
}

void MRAM_SetCodeProtected(int nChip)
{
  MRAM_SetCodeWP(WP_OFF);
  MRAM_SetCodeCS(nChip,CS_ON);
  
  cdhio->MRAM_CTL = WRDI_CMD;
  
  MRAM_WaitForReady();
  
  MRAM_SetCodeCS(nChip,CS_OFF);
  MRAM_SetCodeWP(WP_ON);
}

void MRAM_SetDataWriteable(int nChip)
{
  MRAM_SetDataWP(WP_OFF);
  MRAM_SetDataCS(nChip,CS_ON);
  
  cdhio->MRAM_CTL = WREN_CMD;
  
  MRAM_WaitForReady();
  
  MRAM_SetDataCS(nChip,CS_OFF);
}

void MRAM_SetDataProtected(int nChip)
{
  MRAM_SetDataWP(WP_OFF);
  MRAM_SetDataCS(nChip,CS_ON);
  
  cdhio->MRAM_CTL = WRDI_CMD;
  
  MRAM_WaitForReady();
  
  MRAM_SetDataCS(nChip,CS_OFF);
  MRAM_SetDataWP(WP_ON);
}

void MRAM_WriteAddress(uint32 unAddr)
{
  MRAM_WaitForReady();
  
  cdhio->MRAM_CTL = (unAddr >> 16) & 0xFF;
  MRAM_WaitForReady();
  cdhio->MRAM_CTL = (unAddr >> 8) & 0xFF;
  MRAM_WaitForReady();
  cdhio->MRAM_CTL = unAddr & 0xFF;
  MRAM_WaitForReady();
}

void MRAM_WriteCode(int nChip, uint32 unAddr, uint8 *pWriteBuf, int nLen)
{
int i;

  MRAM_SetCodeWriteable(nChip);
  MRAM_SetCodeCS(nChip, CS_ON);
  
  cdhio->MRAM_CTL = WRITE_CMD;
  MRAM_WaitForReady();
  
  MRAM_WriteAddress(unAddr);
  
  for (i=0;i<nLen;i++)
  {
    cdhio->MRAM_CTL = pWriteBuf[i];
    MRAM_WaitForReady();
  }
  
  MRAM_SetCodeCS(nChip, CS_OFF);
  MRAM_SetCodeProtected(nChip);    
}

void MRAM_WriteData(int nChip, uint32 unAddr, uint8 *pWriteBuf, int nLen)
{
int i;

  MRAM_SetDataWriteable(nChip);
  MRAM_SetDataCS(nChip, CS_ON);
 
  cdhio->MRAM_CTL = WRITE_CMD;
  MRAM_WaitForReady();
   
  MRAM_WriteAddress(unAddr);
  
  for (i=0;i<nLen;i++)
  {
    cdhio->MRAM_CTL = pWriteBuf[i];
    MRAM_WaitForReady();
  }
  
  MRAM_SetDataCS(nChip, CS_OFF);
  MRAM_SetDataProtected(nChip);      
}

void MRAM_ReadCode(int nChip, uint32 unAddr, uint8 *pReadBuf, int nLen)
{
int i;

  MRAM_SetCodeCS(nChip, CS_ON);
  
  cdhio->MRAM_CTL = READ_CMD;
  MRAM_WaitForReady();
  
  MRAM_WriteAddress(unAddr);
  
  for (i=0;i<nLen;i++)
  {
    cdhio->MRAM_RD_INIT = 0;
    MRAM_WaitForReady();
    pReadBuf[i] = cdhio->MRAM_CTL;
  }
  
  MRAM_SetCodeCS(nChip, CS_OFF); 
}

void MRAM_ReadData(int nChip, uint32 unAddr, uint8 *pReadBuf, int nLen)
{
int i;

  MRAM_SetDataCS(nChip, CS_ON);
  
  cdhio->MRAM_CTL = READ_CMD;
  MRAM_WaitForReady();
  
  MRAM_WriteAddress(unAddr);
  
  for (i=0;i<nLen;i++)
  {
    cdhio->MRAM_RD_INIT = 0;
    MRAM_WaitForReady();
    pReadBuf[i] = cdhio->MRAM_CTL;
  }
  
  MRAM_SetDataCS(nChip, CS_OFF); 
}

void MRAM_Write(int yCode_Data, int nChip, uint32 unAddr, uint8 *pWriteBuf, int nLen)
{
  if (yCode_Data == MRAM_CODE)
  {
    MRAM_WriteCode(nChip,unAddr,pWriteBuf,nLen);
  }
  else
  {
    MRAM_WriteData(nChip,unAddr,pWriteBuf,nLen);
  }
}

void MRAM_Read(int yCode_Data, int nChip, uint32 unAddr, uint8 *pReadBuf, int nLen)
{
  if (yCode_Data == MRAM_CODE)
  {
    MRAM_ReadCode(nChip,unAddr,pReadBuf,nLen);
  }
  else
  {
    MRAM_ReadData(nChip,unAddr,pReadBuf,nLen);
  }
}
