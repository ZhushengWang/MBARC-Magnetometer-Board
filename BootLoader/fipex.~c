#include "includes.h"

extern CDH_IO_t *cdhio;

void FIP_SendCmd(uint8 *pBuf, int nLen)
{
int i;

  for (i=0;i<nLen;i++)
  {
    cdhio->FIP_TX = pBuf[i];
  }
}

void FIP_ReadAllBytes(void)
{
uint8 yByte;
int   nBytes=1;
char  szLine[100];
char  szVal[4];

  strcpy(szLine,"");
  while (!(cdhio->STATUS1 & STS1_FIP_RX_EMPTY))
  {
    cdhio->FIP_RX = 0;  //Initiate the Read
    yByte = cdhio->FIP_TX;  //Read the byte
    
    sprintf(szVal,"%02X ",yByte);
    
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

void FIP_SendNoParmCmd(uint8 yID)
{
uint8 yCMD[FIP_MAX_CMD_SIZE];

  yCMD[0] = 0x7E;
  yCMD[1] = yID;
  yCMD[2] = 0;
  yCMD[3] = yID;  //XOR of 1 and 2
  
  FIP_SendCmd(yCMD,4);
}