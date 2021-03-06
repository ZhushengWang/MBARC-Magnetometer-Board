#include "includes.h"

extern CDH_IO_t *cdhio;

void VerifyTestPacket(uint8 *pBuf, uint16 wLen)
{
static uint16 wLastTestPktIndex=0;
uint16 wTestPktIndex;
int i;
int nErr=0;

  wTestPktIndex = (pBuf[0] << 8) + pBuf[1];

  if ((wLastTestPktIndex+1) == wTestPktIndex)
  {
    for (i=0;i<(wLen-2);i++)
    {
      if (pBuf[i+2] != i)
      {
        print_uart_msg("Test Packet:  Error in pattern.\n");
        nErr=1;
        break;
      }
    }
  }
  else
  {
    print_uart_msg("Test Packet:  Bad Index (%04X)\n",wTestPktIndex);
    nErr=1;
  }

  if (nErr==0)
  {
    print_uart_msg("Test Packet:  Verified.\n");
  }

  wLastTestPktIndex = wTestPktIndex;
}

int IsCommand_go_boot_cmd(uint8 *pBuf, int nLen)
{
  if (pBuf[0] == GO_BOOT_CMD)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

void ProcessMRAMWrite(uint8 *pBuf, uint16 wLen)
{
uint8 yCode_Data;
uint8 yChip;
uint32 unAddr;
uint8 yLen;
uint8 *pData;

  yCode_Data = pBuf[3];
  yChip = pBuf[4];
  unAddr = (pBuf[5] << 16) + (pBuf[6] << 8) + pBuf[7];

  print_uart_msg("Writing to address %08X\n",unAddr);

  yLen = wLen-5;
  pData = &pBuf[8];

  if (yCode_Data == 0)
  {
    MRAM_WriteCode(yChip, unAddr, pData, yLen);
  }
  else
  {
    MRAM_WriteData(yChip, unAddr, pData, yLen);
  }
}

void ProcessMRAMRead(uint8 *pBuf)
{
uint8 yCode_Data;
uint8 yChip;
uint32 unAddr;
uint8 yLen;
uint8 ayData[256];

  yCode_Data = pBuf[3];
  yChip = pBuf[4];
  unAddr = (pBuf[5] << 16) + (pBuf[6] << 8) + pBuf[7];
  yLen = pBuf[8];

  if (yCode_Data == 0)
  {
    MRAM_ReadCode(yChip, unAddr, ayData, yLen);
  }
  else
  {
    MRAM_ReadData(yChip, unAddr, ayData, yLen);
  }

  PrintBytes(ayData, yLen);
}

void ProcessTelecommand(uint8 *pBuf, int nLen)
{
uint8 yCmdID;
uint16 wLen;
uint8 yAddr;
uint8 yData;
int i;
uint16 awADCBuf[10];
uint16 awMagBuf[5];
float fVolts;
float fTemp;
int16 swTempData;
uint8 yMagID;
uint16 wDacData;
int16 swMTQVal;
int   nMTQ_Freq;
EPSON_IMU2_DATA_t IMU2_Data;
ST_IMU1_DATA_t IMU1_Data;
uint32 unTime;
uint32 unInitialWait;

  //Cmd ID is in 0
  //Payload length is big-endian 16-bits in 1,2
  //Payload, if any, starts at 3
  yCmdID = pBuf[0];
  wLen = (pBuf[1] << 8) + pBuf[2];  //Data Length

  if (wLen == (nLen-3))
  {
    switch (yCmdID)
    {
      case TEST_PORT_WRITE:
        yAddr = pBuf[3];
        yData = pBuf[4];
        print_uart_msg("Write:  Addr=%02X  Data=%02X\n",yAddr,yData);
        *((uint8 *)cdhio + yAddr) = yData;
        break;

      case TEST_PORT_READ:
        yAddr = pBuf[3];
        yData = *((uint8 *)cdhio + yAddr);
        print_uart_msg("Read:  Addr %02X = %02X\n",yAddr, yData);
        break;

      case CDH_SET_DAC:
        wDacData = (pBuf[3] << 8) + pBuf[4];
        DAC_SetDACRaw(wDacData);
        break;

      case CDH_ADC_READ:
        ReadCDHADC(awADCBuf);
        for (i=0;i<8;i++)
        {
          fVolts = awADCBuf[i] * 2.5/4096.0;
          print_uart_msg("CDH ADC:: Ch: %d  Val: %04X  Volts=%6.3f\n",i,awADCBuf[i],fVolts);
        }
        print_uart_msg("\n");
        break;

      case ADC_READ:
        ReadADC(awADCBuf,pBuf[3]);
        for (i=0;i<8;i++)
        {
          fVolts = awADCBuf[i] * 2.5/4096.0;
          print_uart_msg("ADC %d:: Ch: %d  Val: %04X  Volts=%6.3f\n",pBuf[3],i,awADCBuf[i],fVolts);
        }
        print_uart_msg("\n");
        break;

      case CDH_TEMP_READ:
        ReadCDHADCTemp(awADCBuf);
        for (i=8;i<=9;i++)
        {
          swTempData = awADCBuf[i];
          if (swTempData & 0x0800)
          {
            swTempData |= 0xF000;
          }
          fTemp = swTempData / 4.0;
          print_uart_msg("CDH ADC T:: Ch: %d  Val: %6.3f\n",i,fTemp);
        }
        break;

      case READ_ADC_TEMP:
        ReadADCTemp(awADCBuf, pBuf[3]);
        for (i=8;i<=9;i++)
        {
          swTempData = awADCBuf[i];
          if (swTempData & 0x0800)
          {
            swTempData |= 0xF000;
          }
          fTemp = swTempData / 4.0;
          print_uart_msg("ADC %d T:: Ch: %d  Val: %6.3f\n",pBuf[3],i,fTemp);
        }
        break;

      case MAG_READ:
        Mag_InitMag(pBuf[3]);
        Mag_ReadData(awMagBuf,pBuf[3]);

        print_uart_msg("Mag %d:: Status Reg: %04X\n",pBuf[3],awMagBuf[0]);

        for (i=1;i<=3;i++)
        {
          print_uart_msg("Mag %d:: Ch: %d  Val: %6.3f\n",pBuf[3],i,Mag_GetMag(awMagBuf[i]));
        }

        print_uart_msg("Mag %d::  Temp: %6.3f\n",pBuf[3],Mag_GetTemp(awMagBuf[4]));
        break;

      case MAG_READ_ID:
        Mag_InitMag(pBuf[3]);
        Mag_ReadID(&yMagID,pBuf[3]);
        print_uart_msg("Mag %d:: ID: %02X\n",pBuf[3],yMagID);
        break;

      case MBARC_MAG_STOP:
        Mbarc_Mag_Stop();
        print_uart_msg("Stop Mbarc Mag Measurement\n");
        break;

      case MBARC_MAG_RESET:
        Mbarc_Mag_Reset();
        print_uart_msg("Reset Mbarc Mag Measurement\n");
        break;

      case LI1_SEND_NOP:
        LI1_SendNOP();
        print_uart_msg("Sending NOP\n");
        break;

      case LI1_READ_BYTES:
        print_uart_msg("LI1 Bytes in FIFO:\n");
        LI1_ReadAllBytes();
        break;

      case LI1_READ_CONFIG:
        print_uart_msg("Reading LI1 Config.\n");
        LI1_GetTransConfig();
        break;

      case LI1_READ_FW_REV:
        LI1_ReadFWRev();
        break;

      case LI1_SET_CONFIG:
        if (wLen == 15)
        {
          LI1_SetTransConfig(&pBuf[3], &pBuf[7], &pBuf[13], &pBuf[14], &pBuf[16]);
        }
        else
        {
          print_uart_msg("Incorrect LI1 Config Length.\n");
        }
        break;

      case LI1_BEACON_CONFIG:
        if (wLen == 1)
        {
          LI1_BeaconConfig(pBuf[3]);
        }
        else
        {
          print_uart_msg("Incorrect LI1 Beacon Config Length.\n");
        }
        break;

      case LI1_BEACON_DATA:
        if ((wLen > 0) && (wLen < 256))
        {
          LI1_SetBeaconData(&pBuf[3],wLen);
        }
        else
        {
          print_uart_msg("Incorrect LI1 Beacon Data Length.\n");
        }
        break;

      case LI1_QUERY_TLM:
        print_uart_msg("Querying LI1 Internal Telemetry\n");
        LI1_QueryTLM();
        break;

      case LI1_TRANSMIT:
        break;

      case LI1_SET_POWER:
        print_uart_msg("Setting LI1 Power.\n");
        LI1_SetPower(pBuf[3]);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        break;

      case RESET_NV:
        disable_ints();
        OP_FormatStatus(1);
        OP_FormatStatus(2);
        set_time(0);
        enable_ints();
        print_uart_msg("NV Status Reset\n");
        break;

      case RESET_CDH:
        print_uart_msg("Reset CDH via Watchdog.\n");
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        cdhio->CONTROL1 |= CTL1_CDH_OB_WD_KICK_DISABLE; //Disable auto-kick
        break;

      case LI1_SET_TEST_MODE:
        if (wLen == 1)
        {
          if (pBuf[3] == 1)
          {
            print_uart_msg("Enabling LI1 Test Mode.\n");
            LI1_SetTestMode(1);
          }
          else
          {
            print_uart_msg("Disabling LI1 Test Mode.\n");
            LI1_SetTestMode(0);
          }
        }
        else
        {
          print_uart_msg("LI1_SET_TEST_MODE:  Bad Length\n");
        }
        break;

      case LI1_TEST_PACKET:
        //Verify contents of test packet
        VerifyTestPacket(&pBuf[3],wLen);
        break;

      case MTQ_SET_FREQ:
        if (wLen == 2)
        {
          nMTQ_Freq = (pBuf[3] << 8) + pBuf[4];
          MTQ_SetFreq(nMTQ_Freq);
        }
        else
        {
          print_uart_msg("MTQ_SET_FREQ: Bad Length.\n");
        }
        break;

      case MTQ_SETX:
        if (wLen == 2)
        {
          swMTQVal = (pBuf[3] << 8) + pBuf[4];
          MTQ_SetXPercent(swMTQVal);
        }
        else
        {
          print_uart_msg("MTQ_SETX: Bad Length.\n");
        }
        break;

      case MTQ_SETY:
        if (wLen == 2)
        {
          swMTQVal = (pBuf[3] << 8) + pBuf[4];
          MTQ_SetYPercent(swMTQVal);
        }
        else
        {
          print_uart_msg("MTQ_SETY: Bad Length.\n");
        }
        break;

      case MTQ_SETZ:
        if (wLen == 2)
        {
          swMTQVal = (pBuf[3] << 8) + pBuf[4];
          MTQ_SetZPercent(swMTQVal);
        }
        else
        {
          print_uart_msg("MTQ_SETZ: Bad Length.\n");
        }
        break;

      case IMU2_READ_DATA:
        IMU2_GetLastData(&IMU2_Data);

        print_uart_msg("IMU2  Addr: %02X\n",IMU2_Data.nAddr);
        print_uart_msg("        ND: %02X\n",IMU2_Data.nND);
        print_uart_msg("        EA: %02X\n",IMU2_Data.nEA);
        print_uart_msg("      Temp: %6.3f\n",IMU2_GetTemp(IMU2_Data.nTempOut));
        print_uart_msg("     XGyro: %6.3f\n",IMU2_GetGyro(IMU2_Data.nXGyroOut));
        print_uart_msg("     YGyro: %6.3f\n",IMU2_GetGyro(IMU2_Data.nYGyroOut));
        print_uart_msg("     ZGyro: %6.3f\n",IMU2_GetGyro(IMU2_Data.nZGyroOut));
        print_uart_msg("     XAccl: %6.3f\n",IMU2_GetAccel(IMU2_Data.nXAcclOut));
        print_uart_msg("     YAccl: %6.3f\n",IMU2_GetAccel(IMU2_Data.nYAcclOut));
        print_uart_msg("     ZAccl: %6.3f\n",IMU2_GetAccel(IMU2_Data.nZAcclOut));
        print_uart_msg("      GPIO: %04X\n",IMU2_Data.nGPIO);
        print_uart_msg("     Count: %04X\n",IMU2_Data.nCount);
        print_uart_msg("        CR: %02X\n",IMU2_Data.nCR);
        print_uart_msg("      Time: %d\n\n",IMU2_Data.unTime);
        break;

      case IMU1_READ_DATA:
        IMU1_ReadData(&IMU1_Data);

        print_uart_msg("IMU1  Temp: %d\n",IMU1_GetTemp(IMU1_Data.nTemp));
        // print_uart_msg("IMU1  Temp: %02X\n",IMU1_Data.nTemp);
        print_uart_msg("      Stat: %02X\n",IMU1_Data.nStatus);
        print_uart_msg("     XGyro: %6.3f\n",IMU1_GetGyro(IMU1_Data.nXGyroOut));
        print_uart_msg("     YGyro: %6.3f\n",IMU1_GetGyro(IMU1_Data.nYGyroOut));
        print_uart_msg("     ZGyro: %6.3f\n",IMU1_GetGyro(IMU1_Data.nZGyroOut));
        print_uart_msg("      Time: %d\n\n",IMU1_Data.unTime);
        break;

      case MRAM_WRITE_DATA:
        ProcessMRAMWrite(pBuf,wLen);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        LI1_IncrementFSWLoadPkts();
        break;

      case MRAM_READ_DATA:
        ProcessMRAMRead(pBuf);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        break;

      case FSW_VERIFY_CODE:
        FSW_VerifyCode(pBuf);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        break;

      case FSW_COPY_CODE:
        FSW_CopyCode(pBuf);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        break;

      case FSW_BOOT:
        FSW_Boot(pBuf);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        break;

      case OP_SET_BOOT_PART:
        OP_SetActiveFSWPartition(pBuf[3]);
        TLM_SendACKPacket(yCmdID, ACK_ACK);
        break;

      case LI1_TX_ENABLE:
        LI1_TX_Enable(pBuf[3]);
        OP_SetTXEnable(pBuf[3]);
        break;

      case MSG_TX_ENABLE:
        SetMessageTXEnable(pBuf[3]);
        break;

      case ACK_TX_ENABLE:
        SetACKTXEnable(pBuf[3]);
        break;

      case SET_INIT_WAIT:
        unInitialWait = makeui32_be(pBuf,3);
        OP_SetInitialWait(unInitialWait);
        break;

      case READ_OP_STATUS:
        OP_PrintStatus(pBuf[3]);
        break;

      case SET_TIME:
        unTime = makeui32_be(pBuf,3);
        disable_ints();
        set_time(unTime);
        enable_ints();
        break;

      case SET_LAUNCH:
        disable_ints();
        set_time(0);
        OP_SetTimecodeFromISR(0);
        OP_SetTXEnable(1);
        OP_SetInitialWait(INITIAL_WAIT_SECS);
        OP_SetMissionPhase(BL_FIRST_TURNON);
        OP_InitDeployCount();
        print_uart_msg("Reset CDH via Watchdog.\n");
        cdhio->CONTROL1 |= CTL1_CDH_OB_WD_KICK_DISABLE; //Disable auto-kick
        break;

      case SET_ENABLE_DEPLOY:
        OP_SetEnableDeploy(pBuf[3]);
        if (pBuf[3] == 0)
        {
          print_uart_msg("Deploy disabled.\n");
        }
        else
        {
          print_uart_msg("Deploy enabled.\n");
        }
        break;

      case SET_PHASE:
        OP_SetMissionPhase(pBuf[3]);
        print_uart_msg("Mission phase set to %d on next boot.\n",pBuf[3]);
        break;

      default:
        print_uart_msg("Bad ID: %d\n",yCmdID);
        TLM_SendACKPacket(yCmdID, ACK_NACK_BADID);
        break;
    }
  }
  else
  {
    print_uart_msg("Bad Length: %d\n",wLen);
    TLM_SendACKPacket(yCmdID, ACK_NACK_BADLEN);
  }
}

int TC_VerifyTC(uint8 *pCmd, int nLen)
{
uint16 wCSum = 0;
uint16 wStoredCSum = (pCmd[nLen-2] << 8) + pCmd[nLen-1];
int i;

  if ((pCmd[0] == 0xFA) &&
      (pCmd[1] == 0xF3) &&
      (pCmd[2] == 0x20)  )
  {
    for (i=0;i<(nLen-2);i++)
    {
      wCSum += pCmd[i];
    }

    if (wStoredCSum == wCSum)
    {
      return(1);
    }
    else
    {
      return(0);  //Bad csum
    }
  }
  else
  {
    return(-1); //Bad sync
  }
}
