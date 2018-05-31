#include "includes.h"

extern CDH_IO_t *cdhio;

BEACON_t TLM_BeaconData;
uint16 uwBeaconCount=0;

int nACKTXEnable = 0;

void SetACKTXEnable(uint8 yEnable)
{
  nACKTXEnable = yEnable;
}

void TLM_AddChecksum(uint8 *pPkt, int nOffset)
{
  int i;
  uint16 wCS=0;

  for(i=0;i<nOffset;i++)
  {
    wCS+=pPkt[i];
  }

  pPkt[nOffset] = wCS >> 8;
  pPkt[nOffset+1] = wCS & 0xFF;
}

void TLM_SendPktToTestPort(uint8 *pData, int nLen)
{
int i;

  //Send it out the test port
  for (i=0;i<nLen;i++)
  {
    cdhio->TEST_TLM = pData[i];
  }
}

void TLM_SendPktToRadio(uint8 *pData, int nLen)
{
  LI1_Transmit(pData,nLen);
}

int TLM_MakePkt(uint8 *pData, uint8 yType, int nLen, uint8 *payPacket)
{
  int i;
  int nTotal;
  uint8 ui8Pkt[256];

  ui8Pkt[0] = 0xFA;
  ui8Pkt[1] = 0xF3;
  ui8Pkt[2] = 0x20;
  ui8Pkt[3] = yType;
  ui8Pkt[4] = nLen >> 8;
  ui8Pkt[5] = nLen & 0xFF;

  for(i=0;i<nLen;i++)
  {
    ui8Pkt[i+6] = pData[i];
  }

  TLM_AddChecksum(ui8Pkt,nLen+6);

  nTotal = nLen + 8;

  memcpy(payPacket,ui8Pkt,nTotal);

  return(nTotal);
}

void TLM_SendACKPacket(uint8 yID, uint8 yAck)
{
uint8 ayPktData[2];
uint8 ayPkt[10];
int   nLen;

  ayPktData[0] = yID;
  ayPktData[1] = yAck;

  nLen = TLM_MakePkt(ayPktData,ACK_PKT_TYPE,2,ayPkt);

  TLM_SendPktToTestPort(ayPkt,nLen);

  if (nACKTXEnable == 1)
  {
    TLM_SendPktToRadio(ayPkt,nLen);
  }
}

void TLM_CollectBeaconData(void)
{
  ADC_ReadAllADCs();
  Mag_ReadAllMags();
  IMU1_ReadData(NULL);
  // Mbarc Mag is collected periodically in main loop
  // IMU2 data is collected periodically in main loop
  LI1_QueryTLM();
}

void TLM_UpdateBeaconData(uint8 yMissionPhase)
{
CommStats_t LI1_CommStats;
uint16 *pwADCData=NULL;
uint16 *pwMagData=NULL;
MBARC_MAG_DATA_t MbarcMagData;
//EPSON_IMU2_DATA_t IMU2Data;
ST_IMU1_DATA_t IMU1Data;
TELEMETRY_STRUCTURE_t LI1_TLM;
uint8 ayPacket[256];
int nTotalSize;

  TLM_BeaconData.unTime = get_time();
  TLM_BeaconData.uwPhase = yMissionPhase;
  TLM_BeaconData.uwBeaconCount = uwBeaconCount++;

  LI1_GetCommStats(&LI1_CommStats);

  TLM_BeaconData.uwTXCount = LI1_CommStats.wRadioPktsTransmitted;
  TLM_BeaconData.uwRXCount = LI1_CommStats.wRadioPktsReceived;
  TLM_BeaconData.uwFSWLoadPkts = LI1_CommStats.wFSWLoadPktsReceived;

  ADC_GetLastADCData(&pwADCData,SELECT_CDH_ADC);
  memcpy(TLM_BeaconData.awCDHADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);
  ADC_GetLastADCData(&pwADCData,SELECT_EPS_ADC1);
  memcpy(TLM_BeaconData.awEPS1ADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);
  ADC_GetLastADCData(&pwADCData,SELECT_EPS_ADC2);
  memcpy(TLM_BeaconData.awEPS2ADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);
  ADC_GetLastADCData(&pwADCData,SELECT_SP1_ADC);
  memcpy(TLM_BeaconData.awSP1ADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);
  ADC_GetLastADCData(&pwADCData,SELECT_SP2_ADC);
  memcpy(TLM_BeaconData.awSP2ADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);
  ADC_GetLastADCData(&pwADCData,SELECT_SP3_ADC);
  memcpy(TLM_BeaconData.awSP3ADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);
  // ADC_GetLastADCData(&pwADCData,SELECT_BD4_ADC);
  // memcpy(TLM_BeaconData.awBD4ADCData,pwADCData,(NUM_ADC_SAMPLES-1)*2);  

  Mag_GetLastData(&pwMagData,SELECT_SP1_MAG);
  memcpy(TLM_BeaconData.awSP1MagData,&pwMagData[1],(NUM_MAG_SAMPLES-1)*2);
  Mag_GetLastData(&pwMagData,SELECT_SP2_MAG);
  memcpy(TLM_BeaconData.awSP2MagData,&pwMagData[1],(NUM_MAG_SAMPLES-1)*2);
  Mag_GetLastData(&pwMagData,SELECT_SP3_MAG);
  memcpy(TLM_BeaconData.awSP3MagData,&pwMagData[1],(NUM_MAG_SAMPLES-1)*2);
  Mag_GetLastData(&pwMagData,SELECT_BD4_MAG);
  memcpy(TLM_BeaconData.awBD4MagData,&pwMagData[1],(NUM_MAG_SAMPLES-1)*2);

  Mbarc_Mag_GetLastData(&MbarcMagData);
  TLM_BeaconData.unMbarcMagCycleCount[0] = MbarcMagData.xCycleCount;
  TLM_BeaconData.unMbarcMagCycleCount[1] = MbarcMagData.yCycleCount;
  TLM_BeaconData.unMbarcMagCycleCount[2] = MbarcMagData.zCycleCount;

  /*
  IMU2_GetLastData(&IMU2Data);
  TLM_BeaconData.unIMU2Temp = IMU2Data.nTempOut;
  TLM_BeaconData.unIMU2Gyro[0] = IMU2Data.nXGyroOut;
  TLM_BeaconData.unIMU2Gyro[1] = IMU2Data.nYGyroOut;
  TLM_BeaconData.unIMU2Gyro[2] = IMU2Data.nZGyroOut;
  TLM_BeaconData.unIMU2Accl[0] = IMU2Data.nXAcclOut;
  TLM_BeaconData.unIMU2Accl[1] = IMU2Data.nYAcclOut;
  TLM_BeaconData.unIMU2Accl[2] = IMU2Data.nZAcclOut;
  */

  IMU1_GetLastData(&IMU1Data);
  TLM_BeaconData.uwIMU1Temp = IMU1Data.nTemp;
  TLM_BeaconData.uwIMU1Gyro[0] = IMU1Data.nXGyroOut;
  TLM_BeaconData.uwIMU1Gyro[1] = IMU1Data.nYGyroOut;
  TLM_BeaconData.uwIMU1Gyro[2] = IMU1Data.nZGyroOut;

  LI1_GetLastTLM(&LI1_TLM);
  memcpy(&TLM_BeaconData.LI_TLM_Data,&LI1_TLM,sizeof(TELEMETRY_STRUCTURE_t));

  //Make a TLM packet
  nTotalSize = TLM_MakePkt((uint8 *)&TLM_BeaconData,
                           BEACON_PKT_TYPE,
                           sizeof(BEACON_t),
                           ayPacket);

  //Send it out the test port
  TLM_SendPktToTestPort(ayPacket,nTotalSize);

  //Update Beacon Data in Radio
  LI1_SetBeaconData(ayPacket,nTotalSize);
}
