#include "includes.h"

extern CDH_IO_t *cdhio;

uint8 yTXEnable = 1;
uint8 Buffer[1000];
uint8 ayCmdPkt[1000];
int LI1_Test_Mode = 0;
uint16 wTestPktCount = 0;
int nLastBeaconValue = 4;  //Ten seconds

//Packet Receive Stats
CommStats_t LI1_CommStats;

//Queried Data from Radio
TELEMETRY_STRUCTURE_t    tsLastTelem;
RADIO_RF_CONFIGURATION_t rfLastRFConfig;
RADIO_CONFIGURATION_t    rcLastConfig;
float                    fRadioFirmwareRev=0.0;

#define PKTFIFO_SIZE 1000
uint8 ayPktFIFO[PKTFIFO_SIZE];
int nPktFIFOReadPtr = 0;
int nPktFIFOWritePtr= 0;
int nPktFIFOPeekPtr = 0;

void LI1_TX_Enable(uint yByte)
{
int nBeaconSave;
  yTXEnable = yByte;
  
  if (yByte == 0)
  {
    nBeaconSave = nLastBeaconValue;
    LI1_BeaconConfig(0);
    nLastBeaconValue = nBeaconSave;
  }
  else
  {
    LI1_BeaconConfig(nLastBeaconValue);
  }
}

void LI1_Enqueue(uint8 yByte)
{
  ayPktFIFO[nPktFIFOWritePtr++] = yByte;
  if (nPktFIFOWritePtr >= PKTFIFO_SIZE)
  {
    nPktFIFOWritePtr = 0;
  }
}

uint8 LI1_Dequeue(void)
{
  uint8 yByte = ayPktFIFO[nPktFIFOReadPtr++];
  if (nPktFIFOReadPtr >= PKTFIFO_SIZE)
  {
    nPktFIFOReadPtr = 0;
  }
  nPktFIFOPeekPtr = nPktFIFOReadPtr;
  return(yByte);
}

uint8 LI1_Peek(void)
{
  uint8 yByte = ayPktFIFO[nPktFIFOPeekPtr++];
  if (nPktFIFOPeekPtr >= PKTFIFO_SIZE)
  {
    nPktFIFOPeekPtr = 0;
  }
  
  return(yByte);
}

int LI1_BytesInQueue(void)
{
  int nCount = nPktFIFOWritePtr - nPktFIFOReadPtr;
  
  if (nCount < 0)
  {
    nCount+=PKTFIFO_SIZE;
  }
  return(nCount);
}

void SendBytes(uint8 *pBuf, int nLen)
{
  int i;
  
  for (i=0;i<nLen;i++)
  {
    cdhio->LI1_TX = pBuf[i];
  }
}

void CalcChecksum(uint8 *pBuf, int nLen, uint8 *pyChkA, uint8 *pyChkB)
{  
  int i;
  
  *pyChkA = 0;
  *pyChkB = 0;
  
  for (i=0;i<nLen;i++)
  {
    *pyChkA = *pyChkA + pBuf[i];
    *pyChkB = *pyChkB + *pyChkA;
  }
}

void AppendChecksum(uint8 *pBuf, int nLen)
{
  uint8 yChkA=0;
  uint8 yChkB=0;
  
  CalcChecksum(pBuf, nLen, &yChkA, &yChkB);
  
  pBuf[nLen] = yChkA;
  pBuf[nLen+1] = yChkB;  
}

void PrependSync(uint8 *pBuf)
{
  pBuf[0] = 'H';
  pBuf[1] = 'e';
}

void SendPkt(uint8 yOpCode, uint8 *pyPayload, int nLen)
{
  PrependSync(Buffer);
  Buffer[2] = MSG_TYPE;
  Buffer[3] = yOpCode;
  Buffer[4] = 0x00;
  Buffer[5] = nLen & 0xFF;
    
  AppendChecksum(&Buffer[2],4);
  
  if (nLen > 0)  //Add payload and checksum
  {
    memcpy(&Buffer[8],pyPayload,nLen); 
    AppendChecksum(&Buffer[2],nLen+6);
    SendBytes(Buffer,8+nLen+2);
  }
  else
  {
    SendBytes(Buffer,8);  //No payload
  }
}

void LI1_SetTestMode(int nMode)
{
  LI1_Test_Mode = nMode;
}

int LI1_GetTestMode(void)
{
  return(LI1_Test_Mode);
}
  
void LI1_GetTransConfig(void)
{
  SendPkt(GET_TRANSCEIVER_CONFIG,NULL,0);
}

void LI1_Transmit(uint8 *pyBuf, int nLen)
{
  if (yTXEnable)
  {
    SendPkt(TRANSMIT_DATA, pyBuf, nLen);
  }
}

void LI1_QueryTLM(void)
{
  if (nLastBeaconValue > 0)
  {
    SendPkt(TELEMETRY_QUERY, NULL, 0);
  }
}

void LI1_SetBeaconData(uint8 *pyBuf, int nLen)
{
  if (nLastBeaconValue > 0)
  {
    SendPkt(BEACON_DATA, pyBuf, nLen);
  }
}

void LI1_BeaconConfig(uint8 yInterval)
{
  RADIO_BEACON_CONFIGURATION_t rbcBeaconConfig;
  
  if (yTXEnable)
  {
    rbcBeaconConfig.beacon_interval = yInterval;
  }
  else
  {
     rbcBeaconConfig.beacon_interval = 0;
  }
  
  SendPkt(BEACON_CONFIG, (uint8 *)&rbcBeaconConfig, sizeof(rbcBeaconConfig));
  
  nLastBeaconValue = yInterval;
}
  
void LI1_SetTransConfig(uint8 *pyFreq, uint8 *pyCall, uint8 *pyPwr, uint8 *pyConfig, uint8 *pyConfig2)
{
  RADIO_CONFIGURATION_t rcRadConfig;
  uint32 nFreq = makeui32_le(pyFreq,0);
  uint16 wConfig = makeui16_le(pyConfig,0);
  uint16 wConfig2= makeui16_le(pyConfig2,0);
  
  rcRadConfig.interface_baud_rate = BAUD_RATE_9600;
  rcRadConfig.tx_power_amp_level  = *pyPwr;
  rcRadConfig.rx_rf_baud_rate     = RF_BAUD_RATE_9600;
  rcRadConfig.tx_rf_baud_rate     = RF_BAUD_RATE_9600;
  rcRadConfig.rx_modulation       = RF_MODULATION_GFSK;
  rcRadConfig.tx_modulation       = RF_MODULATION_GFSK;
  rcRadConfig.rx_freq             = nFreq;
  rcRadConfig.tx_freq             = nFreq;
  strncpy(rcRadConfig.src,(char *)pyCall,6);
  strncpy(rcRadConfig.dest,"CQ    ",6);
  rcRadConfig.tx_preamble         = 0x0500;  //Little Endian 5
  rcRadConfig.tx_postamble        = 0x0000;
  rcRadConfig.function_config     = wConfig;
  rcRadConfig.function_config2    = wConfig2;
  
  SendPkt(SET_TRANSCEIVER_CONFIG,(uint8 *)&rcRadConfig,sizeof(rcRadConfig));
}

void LI1_SendNOP(void)
{
  SendPkt(NO_OP_COMMAND,NULL,0);
}

void LI1_SetPower(uint8 yPwr)
{
  SendPkt(FAST_PA_SET, &yPwr, 1);
}

void LI1_ReadFWRev(void)
{
  SendPkt(READ_FIRMWARE_REVISION,NULL,0);
}

void LI1_ReadAllBytes(void)
{
uint8 yByte;
int   nBytes=1;
char  szLine[100];
char  szVal[4];
  
  strcpy(szLine,"");
  while (!(cdhio->STATUS1 & STS1_LI1_RX_EMPTY))
  {
    cdhio->LI1_RX = 0;  //Command the read
    yByte = cdhio->LI1_TX;
    
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

void LI1_PrintPacket(uint8 *pBuf)
{
int   nBytes=1;
char  szLine[100];
char  szVal[4];
uint16 wLen = (pBuf[4] << 8) + pBuf[5];
int i;  

  strcpy(szLine,"");
  for (i=0;i<(wLen+10);i++)
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

int LI1_RadioBytesAvail(void)
{
  if ( (!(cdhio->STATUS1 & STS1_LI1_RX_EMPTY)) ||
       (LI1_BytesInQueue() > 0))
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

void LI1_SendTestPacket(void)
{
  uint8 ayTestPkt[256];
  uint8 ayOutPkt[256];
  int i;
  int nTotal;
  
  ayTestPkt[0] = wTestPktCount >> 8;
  ayTestPkt[1] = wTestPktCount & 0xFF;
  
  
  for (i=2;i<200;i++)
  {
    ayTestPkt[i] = i & 0xFF;
  }
  
  nTotal = TLM_MakePkt(ayTestPkt,TEST_PKT_TYPE, 200, ayOutPkt);
  
  LI1_Transmit(ayOutPkt, nTotal);
  
  wTestPktCount++;  
}

void LI1_AssertReset(void)
{
  cdhio->CONTROL2 &= ~CTL2_CDH_LI1_NRESET;  //Assert reset for radio
}

void LI1_DeassertReset(void)
{
  cdhio->CONTROL2 |= CTL2_CDH_LI1_NRESET;  //De-assert reset for radio
}

void LI1_RadioConfig(void)
{
  memset(&LI1_CommStats,0, sizeof(LI1_CommStats));
  memset(&tsLastTelem,0,sizeof(tsLastTelem));
  memset(&rfLastRFConfig,0,sizeof(rfLastRFConfig));
  memset(&rcLastConfig,0,sizeof(rcLastConfig));
}

int LI1_GetCommand(uint8 *pBuf)
{
  uint8 yByte;
  static int nDecodeStep = 0;
  static int nPktOffset = 0;
  static uint16 wPayloadSize;
  uint8 yCSA;
  uint8 yCSB;
  int nRC = -1;
  
  //Read available bytes and queue them
  while (!(cdhio->STATUS1 & STS1_LI1_RX_EMPTY))
  {
    cdhio->LI1_RX = 0;  //Command the read
    yByte = cdhio->LI1_TX;
    LI1_Enqueue(yByte);
  }
    
  //Look for sync code
  while ((LI1_BytesInQueue() > 0) && (nRC < 0))
  {
    switch (nDecodeStep)
    {
      case 0:  //Sync 1
        if (LI1_Peek() == 'H')
        {
          nDecodeStep = 1;
          ayCmdPkt[nPktOffset++] = LI1_Dequeue();
        }
        else
        {
          LI1_Dequeue();  //Throw away non sync byte
          nDecodeStep = 0;
          nPktOffset = 0;
          LI1_CommStats.wSyncErrors++;
        }
        break;
        
      case 1:  //Sync 2
        if (LI1_Peek() == 'e')
        {
          nDecodeStep = 2;
          ayCmdPkt[nPktOffset++] = LI1_Dequeue();
        }
        else
        {
          LI1_Dequeue();  //Throw away non sync byte
          nDecodeStep = 0;
          nPktOffset = 0;
          LI1_CommStats.wSyncErrors++;
        }
        break;
        
      case 2:  //Header Bytes
        ayCmdPkt[nPktOffset++] = LI1_Dequeue();
        if (nPktOffset == 8)
        {
          //Verify Checksum
          CalcChecksum(&ayCmdPkt[2], 4, &yCSA, &yCSB);
          if ((yCSA == ayCmdPkt[6]) && (yCSB == ayCmdPkt[7]))
          {
            wPayloadSize = (ayCmdPkt[4] << 8) + ayCmdPkt[5];
            
            if (wPayloadSize <= 255)
            {
              nDecodeStep = 3;
            }
            else
            {
              //It's an ACK/NAK packet
              if ((wPayloadSize == 0x0A0A) || (wPayloadSize = 0xFFFF))
              {
                nRC = nPktOffset;
                memcpy(pBuf,ayCmdPkt,nPktOffset);
                nDecodeStep = 0;
                nPktOffset = 0;     
                LI1_CommStats.wRadioPktsReceived++; 
              }
              else
              {
                nDecodeStep = 0;
                nPktOffset  = 0;
                LI1_CommStats.wPayloadSizeErrors++;
              }
            }
          }
          else
          {
            nDecodeStep = 0;
            nPktOffset = 0;
            LI1_CommStats.wHeaderCSErrors++;
            print_uart_msg("LI1:  Bad packet header checksum.\n");
          }
        }
        else
        {
          nDecodeStep = 2;
        }
        break;
        
      case 3:
        ayCmdPkt[nPktOffset++] = LI1_Dequeue();
        
        if (nPktOffset == (wPayloadSize+10))
        {
          //Got complete packet
          //Verify Checksum
          CalcChecksum(&ayCmdPkt[2], wPayloadSize+6, &yCSA, &yCSB);
          if ((yCSA == ayCmdPkt[wPayloadSize+8]) &&
              (yCSB == ayCmdPkt[wPayloadSize+9]))
          {
            nRC = nPktOffset;
            memcpy(pBuf,ayCmdPkt,nPktOffset);
            nDecodeStep = 0;
            nPktOffset = 0;   
            LI1_CommStats.wPacketsReceived++;        
          }
          else
          {
            nDecodeStep = 0;
            nPktOffset  = 0;
            LI1_CommStats.wPacketCSErrors++;
            print_uart_msg("LI1:  Bad packet checksum.\n");
          }          
        }
        else
        {
          nDecodeStep = 3;
        }
        
        break;
        
      default:
        print_uart_msg("LI1:  Bad Step.\n");
        nDecodeStep = 0;
        break;
    }   
  }  
  return(nRC); 
}

void LI1_ProcessCommand(uint8 *pBuf,int nLen)
{
  uint16 wPayloadLen = (pBuf[4] << 8) + pBuf[5];
  const uint16 wTCOffset = 24;  //8 bytes for LI header, 16 bytes for AX.25 header
  uint16 wTCLen;
  int nTCVerify;
    
  switch (pBuf[3])
  {
    case NO_OP_COMMAND:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: NOP Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: NOP NAK.\n");
      }
      break;
      
    case RESET_SYSTEM:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: RESET Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: RESET NAK.\n");
      }      
      break;
      
    case TRANSMIT_DATA:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        LI1_CommStats.wRadioPktsTransmitted++;
        //print_uart_msg("LI1: TX Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        //print_uart_msg("LI1: TX NAK.\n");
      }
      break;
    
    case GET_TRANSCEIVER_CONFIG:
      if (wPayloadLen == sizeof(RADIO_CONFIGURATION_t))
      {
        memcpy((uint8 *)&rcLastConfig, &pBuf[8], wPayloadLen);
      }
      break;
      
    case SET_TRANSCEIVER_CONFIG:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: SET_CONFIG Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: SET_CONFIG NAK.\n");
      }
      break;
      
    case TELEMETRY_QUERY:
      if (wPayloadLen == sizeof(TELEMETRY_STRUCTURE_t))
      {
        memcpy((uint8 *)&tsLastTelem, &pBuf[8], wPayloadLen);
      }
      break;
      
    case WRITE_FLASH:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: WRITE_FLASH Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: WRITE_FLASH NAK.\n");
      }
      break;
      
    case RF_CONFIG:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: RF_CONFIG Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: RF_CONFIG NAK.\n");
      }
      break;
      
    case BEACON_DATA:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: BEACON_DATA NAK.\n");
      }
      break;
      
    case BEACON_CONFIG:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: BEACON_CONFIG Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: BEACON_CONFIG NAK.\n");
      }
      break;
      
    case READ_FIRMWARE_REVISION:
      if ((pBuf[4] == 0) && (pBuf[5] == 4))
      {
        fRadioFirmwareRev = pBuf[8]          +
                            (pBuf[9] << 8)   +
                            (pBuf[10] << 16) +
                            (pBuf[11] << 24);
        print_uart_msg("LI1: Firmware Rev = %f\n",fRadioFirmwareRev);
      }
      else
      {
        print_uart_msg("LI1: Bad Firmware Rev. Length.\n");
      }                            
      break;
      
    case WRITE_OVER_AIR_KEY:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: DIO_KEY Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: DIO_KEY NAK.\n");
      }
      break;
      
    case FAST_PA_SET:
      if ((pBuf[4] == 0x0A) && (pBuf[5] == 0x0A))
      {
        LI1_CommStats.wAcksReceived++;
        print_uart_msg("LI1: FAST_PA Ack.\n");
      }
      else
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: FAST_PA NAK.\n");
      }
      break;
      
    case RECEIVE_DATA:
      if ((pBuf[4] == 0xFF) && (pBuf[5] == 0xFF))
      {
        LI1_CommStats.wNacksReceived++;
        print_uart_msg("LI1: RX Data NAK.\n");
        TLM_SendACKPacket(pBuf[3], ACK_NACK_LI1);
      }
      else
      {
        //LI packet containing AX.25 packet containing QB50 packet
        wTCLen = (pBuf[wTCOffset+4] << 8) + pBuf[wTCOffset+5] + 3; //Plus 3 for header
        nTCVerify = TC_VerifyTC(&pBuf[wTCOffset], wTCLen+5); //Plus 5 for sync and cs
        if (nTCVerify == 1)
        {                         
          ProcessTelecommand(&pBuf[wTCOffset+3],wTCLen);
          OP_IncrementCommCount();
        }
        else
        {
          if (nTCVerify == 0)
          {
            TLM_SendACKPacket(pBuf[3], ACK_NACK_BADSYNC);
          }
          else
          {
            TLM_SendACKPacket(pBuf[3], ACK_NACK_BADCS);
          }
        }       
      }
      break;
      
    default:
      print_uart_msg("LI1:  Bad Opcode=%02X\n",pBuf[3]);
      TLM_SendACKPacket(pBuf[3], ACK_NACK_LI1);     
      break;
  }
}

int LI1_IsCommand_go_boot_cmd(uint8 *pBuf, int nLen)
{
  const uint16 wTCOffset = 24;  //8 bytes for LI header, 16 bytes for AX.25 header
  uint16 wTCLen;

  if (pBuf[3] == RECEIVE_DATA)
  {
    wTCLen = (pBuf[wTCOffset+4] << 8) + pBuf[wTCOffset+5];

    return(IsCommand_go_boot_cmd(&pBuf[wTCOffset+3],wTCLen));
  }
  else
  {
    return(0);
  }
}

void LI1_GetCommStats(CommStats_t *pStats)
{
  memcpy(pStats,&LI1_CommStats,sizeof(CommStats_t));
}

void LI1_Init(void)
{
  LI1_RadioConfig();
  
  LI1_SetPower(141);  //Set 1 W output
}
  
void LI1_GetLastTLM(TELEMETRY_STRUCTURE_t *pTLM)
{
  memcpy(pTLM,&tsLastTelem,sizeof(TELEMETRY_STRUCTURE_t));
}

void LI1_IncrementFSWLoadPkts(void)
{
  LI1_CommStats.wFSWLoadPktsReceived++;
}