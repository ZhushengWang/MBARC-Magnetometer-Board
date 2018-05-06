#include "includes.h"

extern CDH_IO_t *cdhio;

#define FIP_SYNC_BYTE  0x7E

#define FIP_PKTFIFO_SIZE 1000
static uint8 ayPktFIFO[FIP_PKTFIFO_SIZE];
static int nPktFIFOReadPtr = 0;
static int nPktFIFOWritePtr= 0;
static int nPktFIFOPeekPtr = 0;

static uint8 ayDataPkt[1000];

int nFIP_ACK_Count = 0;
int nFIP_NAK_Count = 0;
int nFIP_SDP_Count = 0;
int nFIP_HK_Count  = 0;

//Packet Receive Stats
CommStats_t FIP_CommStats;

int nFIPPacketProcessingEnable = 1;

void FIP_SetFIPPacketProcEnable(int nEnable)
{
  nFIPPacketProcessingEnable = nEnable;
}

void FIP_PowerOn(void)
{
  pwr_ctl(FIPEX,PWR_ON);
}

void FIP_PowerOff(void)
{
  pwr_ctl(FIPEX,PWR_OFF);
}

uint8 FIP_CalcXOR(uint8 *pBuf, int nLen)
{
uint8 yXOR = 0;
int  i;

  for (i=0;i<nLen;i++)
  {
    yXOR ^= pBuf[i];
  }
  
  return(yXOR);
}

void FIP_SendCmd(uint8 *pBuf, int nLen)
{
int i;

  for (i=0;i<nLen;i++)
  {
    cdhio->FIP_TX = pBuf[i];
  }
}

void FIP_ClearHWFIFO(void)
{
uint8 yByte;

  //Empty the hardware FIFO
  while (!(cdhio->STATUS1 & STS1_FIP_RX_EMPTY))
  {
    cdhio->FIP_RX = 0;  //Initiate the Read
    yByte = cdhio->FIP_TX;  //Read the byte
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

static void FIP_Enqueue(uint8 yByte)
{
  ayPktFIFO[nPktFIFOWritePtr++] = yByte;
  if (nPktFIFOWritePtr >= FIP_PKTFIFO_SIZE)
  {
    nPktFIFOWritePtr = 0;
  }
}

static uint8 FIP_Dequeue(void)
{
  uint8 yByte = ayPktFIFO[nPktFIFOReadPtr++];
  if (nPktFIFOReadPtr >= FIP_PKTFIFO_SIZE)
  {
    nPktFIFOReadPtr = 0;
  }
  nPktFIFOPeekPtr = nPktFIFOReadPtr;
  return(yByte);
}

static uint8 FIP_Peek(void)
{
  uint8 yByte = ayPktFIFO[nPktFIFOPeekPtr++];
  if (nPktFIFOPeekPtr >= FIP_PKTFIFO_SIZE)
  {
    nPktFIFOPeekPtr = 0;
  }
  
  return(yByte);
}

static int FIP_BytesInQueue(void)
{
  int nCount = nPktFIFOWritePtr - nPktFIFOReadPtr;
  
  if (nCount < 0)
  {
    nCount+=FIP_PKTFIFO_SIZE;
  }
  return(nCount);
}

int FIP_GetPacket(uint8 *pBuf)
{
  uint8 yByte;
  static int nDecodeStep = 0;
  static int nPktOffset = 0;
  static uint16 wPayloadSize;
  uint8 yXOR;
  int nRC = -1;
  
  if (nFIPPacketProcessingEnable == 0)
  {
    return nRC;
  }
  
  //Read available bytes and queue them
  while (!(cdhio->STATUS1 & STS1_FIP_RX_EMPTY))
  {
    cdhio->FIP_RX = 0;  //Command the read
    yByte = cdhio->FIP_TX;
    FIP_Enqueue(yByte);
  }
    
  //Look for sync code
  while ((FIP_BytesInQueue() > 0) && (nRC < 0))
  {
    switch (nDecodeStep)
    {
      case 0:  //Sync 1
        if (FIP_Peek() == FIP_SYNC_BYTE)
        {
          nDecodeStep = 1;
          ayDataPkt[nPktOffset++] = FIP_Dequeue();
        }
        else
        {
          yByte = FIP_Dequeue();  //Throw away non sync byte
          nDecodeStep = 0;
          nPktOffset = 0;
          
          if (yByte != 0x00)
          {
            FIP_CommStats.wSyncErrors++;
            nRC=-2;
            print_uart_msg("FIP: Error, non-sync byte. (%lu)\n",get_time());
          }
        }
        break;
        
      case 1:  //Header Bytes
        ayDataPkt[nPktOffset++] = FIP_Dequeue();
        if (nPktOffset == 4)
        {
          wPayloadSize = ayDataPkt[2];
            
          if (wPayloadSize <= 200)
          {
            nDecodeStep = 2;
          }
          else
          {
            nDecodeStep = 0;
            nPktOffset  = 0;
            FIP_CommStats.wPayloadSizeErrors++;
          }
        }
        else
        {
          nDecodeStep = 1;
        }
        break;
        
      case 2:
        ayDataPkt[nPktOffset++] = FIP_Dequeue();
        
        if (nPktOffset == (wPayloadSize+5))
        {
          //Got complete packet
          //Verify XOR
          yXOR = FIP_CalcXOR(&ayDataPkt[1], wPayloadSize+3);
          if (yXOR == ayDataPkt[wPayloadSize+4])
          {
            nRC = nPktOffset;
            memcpy(pBuf,ayDataPkt,nPktOffset);
            nDecodeStep = 0;
            nPktOffset = 0;   
            FIP_CommStats.wPacketsReceived++;        
          }
          else
          {
            nDecodeStep = 0;
            nPktOffset  = 0;
            FIP_CommStats.wPacketCSErrors++;
            nRC=-2;  //Signal XOR Error
            print_uart_msg("FIP:  Bad packet XOR. (%lu)\n",get_time());
          }          
        }
        else
        {
          nDecodeStep = 2;
        }        
        break;
        
      default:
        print_uart_msg("FIP:  Bad Packet Decode Step. (%lu)\n",get_time());
        nDecodeStep = 0;
        break;
    }   
  }  
  return(nRC); 
}

void FIP_ProcessPacket(uint8 *pPkt, int nLen)
{
  switch (pPkt[1])
  {
    case 0x02:
      print_uart_msg("SU_R_ACK  %d (%lu)\n",nLen,get_time());
      nFIP_ACK_Count++;
      break;

    case 0x03:
      print_uart_msg("SU_R_NACK  %d (%lu)\n",nLen,get_time());
      nFIP_NAK_Count++;
      break;

    case 0x04:
      print_uart_msg("SU_R_ID  %d (%lu)\n",nLen,get_time());
      break;

    case 0x20:
      print_uart_msg("SU_R_HK  %d (%lu)\n",nLen,get_time());
      nFIP_HK_Count++;
      FIPData_StoreData(pPkt,nLen,FIP_HK_PKTTYPE);
      break;

    case 0x30:
      print_uart_msg("SU_R_SDP  %d (%lu)\n",nLen,get_time());
      nFIP_SDP_Count++;
      FIPData_StoreData(pPkt,nLen,FIP_SDP_PKTTYPE);
      break;

    case 0x33:
      print_uart_msg("SU_R_CAL  %d (%lu)\n",nLen,get_time());
      break;
      
    default:
      print_uart_msg("Bad SU ID:  %02X  Len=%d (%lu)\n",pPkt[1],nLen,get_time());
      break;      
  }
}

void FIP_DoTasks(void)
{
int nLen;
uint8 ayBuf[256];
int nInitScript;

  //Check for data
  nLen = FIP_GetPacket(ayBuf);
  if (nLen > 0)
  {
    FIP_ProcessPacket(ayBuf,nLen);
  }
  
  nInitScript = FIP_SetNextActive();  //Check for script to activate
  
  FIP_RunScript(nInitScript);
}

int FIP_GetAckCount(void)
{
  return(nFIP_ACK_Count);
}

int FIP_GetNakCount(void)
{
  return(nFIP_NAK_Count);
}

int FIP_GetSDPCount(void)
{
  return(nFIP_SDP_Count);
}

int FIP_GetHKCount(void)
{
  return(nFIP_HK_Count);
}