#include "includes.h"

int nMessage_TX_Enable = 0;

extern CDH_IO_t *cdhio;
  
void SetMessageTXEnable(uint8 yVal)
{
  nMessage_TX_Enable = yVal;
}

void send_uart_str(char *pcStr)
{
int nLen;
int nTotal;
uint8 ayPacket[256];
  
  nLen = strlen(pcStr);
  nTotal = TLM_MakePkt(pcStr, MSG_PKT_TYPE, nLen, ayPacket);
  TLM_SendPktToTestPort(ayPacket,nTotal);
  
  if (nMessage_TX_Enable == 1)
  {
    TLM_SendPktToRadio(ayPacket,nTotal);
  }
}

void print_uart_msg(const char *template, ...)
{
  va_list ap;
  static char msg[500];
  
  va_start (ap, template);
  vsprintf (msg, template, ap);
  va_end (ap);
  
  send_uart_str(msg);
}

int wait_for_tp_fifo(void)
{
int nLoopCount = 0;

  while ((cdhio->STATUS1 & STS1_CDH_CPU_FIFO_EF) && (nLoopCount < 100))
  {
    nLoopCount++;
  }
  
  if (nLoopCount >= 100)
  {
    return(-1);
  }
  else
  {
    return(0);
  }
}

int get_bytes_from_tp(int nNum, uint8 *pBuf)
{
  int nNumReceived = 0;
  
  while (nNumReceived < nNum)
  {
    if (wait_for_tp_fifo() == 0)
    {
      cdhio->TEST_CMD = 0;
      pBuf[nNumReceived++] = cdhio->TEST_CMD;
    }
    else
    {
      return(-1);
    }
  }
  return(nNumReceived);
}
 
int get_test_port_command(uint8 *pBuf)
{
  int nCount=0;
  int nCmdLen = 0;
  
  nCount = get_bytes_from_tp(3, pBuf);  //Get ID + 2 length bytes
  
  if (nCount == 3)
  {
    nCmdLen = (pBuf[1] << 8) + pBuf[2];
     
    nCount = get_bytes_from_tp(nCmdLen,pBuf+3);
    if (nCount == nCmdLen)
    {
      return(nCmdLen+3);  //Got a good command
    }
    else
    {
      return(-1);
    }
  }
  else
  {
    return(-1);
  }
}

int test_port_bytes_avail(void)
{
  if (!(cdhio->STATUS1 & STS1_CDH_CPU_FIFO_EF))
  {
    return(1);
  }
  else
  {
    return(0);
  }
}