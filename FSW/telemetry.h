#ifndef _TELEMETRY_H
#define _TELEMETRY_H

#include "includes.h"

#pragma pack(1)

typedef struct
{
  uint16 uwPhase;
  uint32 unTime;
  uint16 uwBeaconCount;
  uint16 uwTXCount;
  uint16 uwRXCount;
  uint16 awCDHADCData[NUM_ADC_SAMPLES-1];
  uint16 awEPS1ADCData[NUM_ADC_SAMPLES-1];
  uint16 awEPS2ADCData[NUM_ADC_SAMPLES-1];
  uint16 awSP1ADCData[NUM_ADC_SAMPLES-1];
  uint16 awSP2ADCData[NUM_ADC_SAMPLES-1];
  uint16 awSP3ADCData[NUM_ADC_SAMPLES-1];
  // uint16 awBD4ADCData[NUM_ADC_SAMPLES-1];
  uint16 awSP1MagData[NUM_MAG_SAMPLES-1];
  uint16 awSP2MagData[NUM_MAG_SAMPLES-1];
  uint16 awSP3MagData[NUM_MAG_SAMPLES-1];
  uint16 awBD4MagData[NUM_MAG_SAMPLES-1];
  // uint32 unIMU2Temp;
  // uint32 unIMU2Gyro[3];
  // uint32 unIMU2Accl[3];
  uint8  uwIMU1Temp;
  uint16 uwIMU1Gyro[3];
  uint16 uwFSWLoadPkts;
  TELEMETRY_STRUCTURE_t LI_TLM_Data;
} BEACON_t;

typedef struct
{
  uint32 unTime;
  uint16 uwHKCount;
  CommStats_t commStats;   //22
  uint32 aunScripts[FIP_MAX_SCRIPTS];  //28
  uint32 aunOpStatus[25];  //100
  uint8 yPowerControl1;
  uint8 yPowerControl2;
  uint8 yStatusReg1;
  uint8 yStatusReg2;
  uint8 yStatusReg3;
  uint8 yStatusReg4;
  uint8 yControlReg1;
  uint8 yControlReg2;
  uint8 yFPGA_Ver;
  uint8 yDAC_H;
  uint8 yDAC_L;
  uint8 yBurnPwrStatus;
  RADIO_CONFIGURATION_t rcRadioConfig;  //34
  uint16 uwFIPScriptState;
  uint16 uwFIPScriptStep;
  uint16 uwFIPACKCnt;
  uint16 uwFIPNAKCnt;
  uint16 uwFIPSDPCnt;
  uint16 uwFIPHKCnt;
} QB50HK_t;  //214

#pragma pack()

#define  MSG_PKT_TYPE    9
#define  BEACON_PKT_TYPE 8
#define  HK_PKT_TYPE     7
#define  TEST_PKT_TYPE   6
#define  ACK_PKT_TYPE    1
#define  SU_SDP_PKT_TYPE 2
#define  SU_HK_PKT_TYPE  3
#define  SU_STORED_PKT_TYPE 4

#define  ACK_ACK         0
#define  ACK_NACK_BADID  1
#define  ACK_NACK_BADLEN 2
#define  ACK_NACK_BADCS  3
#define  ACK_NACK_BADSYNC 4
#define  ACK_NACK_BADPARM 5
#define  ACK_NACK_BADCNT  6
#define  ACK_NACK_BADMODE 7
#define  ACK_NACK_TIMEOUT 8
#define  ACK_NACK_NACK    9
#define  ACK_NACK_LI1     10

int TLM_MakePkt(uint8 *pData, uint8 yType, int nLen, uint8 *payPacket);
void TLM_SendPktToTestPort(uint8 *pData, int nLen);
void TLM_SendPktToRadio(uint8 *pData, int nLen);
void TLM_CollectBeaconData(void);
void TLM_UpdateBeaconData(uint8 yMissionPhase, uint8 yTransmitState);
void TLM_UpdateHKData(int nTransmit);
void TLM_SendACKPacket(uint8 yID, uint8 yAck);
void SetACKTXEnable(uint8 yEnable);
void SetHKTXEnable(uint8 yEnable);
void TLM_SendFIPPacket(uint8 yMem);


#endif
