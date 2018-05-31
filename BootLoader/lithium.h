#ifndef _LITHIUM_H
#define _LITHIUM_H

#include "includes.h"

#define MSG_TYPE 0x10

//Configuration Commands
#define NO_OP_COMMAND 0x01
#define RESET_SYSTEM 0x02
#define TRANSMIT_DATA 0x03
#define RECEIVE_DATA 0x04
#define GET_TRANSCEIVER_CONFIG 0x05
#define SET_TRANSCEIVER_CONFIG 0x06
#define TELEMETRY_QUERY 0x07
#define WRITE_FLASH 0x08
#define RF_CONFIG 0x09
#define BEACON_DATA 0x10
#define BEACON_CONFIG 0x11
#define READ_FIRMWARE_REVISION 0x12
#define WRITE_OVER_AIR_KEY 0x13
#define FIRMWARE_UPDATE 0x14
#define FIRMWARE_PACKET 0x15
#define FAST_PA_SET 0x20
#define BAUD_RATE_9600 0
#define BAUD_RATE_19200 1
#define BAUD_RATE_38400 2
#define BAUD_RATE_76800 3
#define BAUD_RATE_115200 4
#define RF_BAUD_RATE_1200 0
#define RF_BAUD_RATE_9600 1
#define RF_BAUD_RATE_19200 2
#define RF_BAUD_RATE_38400 3
#define RF_MODULATION_GFSK 0
#define RF_MODULATION_AFSK 1
#define RF_MODULATION_BPSK 2
#define TELEMETRY_DUMP_COMMAND 0x30
#define PING_RETURN_COMMAND 0x31
#define CODE_UPLOAD_COMMAND 0x32
#define RADIO_RESET_COMMAND 0x33
#define PIN_TOGGLE_COMMAND 0x34

#pragma pack(1)

typedef struct telem_type
{
  uint16 op_counter;
  int16  msp430_temp;
  uint8  time_count[3];
  uint8  rssi;
  uint32 bytes_received;
  uint32 bytes_transmitted;
} TELEMETRY_STRUCTURE_t ;

typedef struct
{
  uint8  front_end_level; //0 to 63 Value
  uint8  tx_power_amp_level; //0 to 255 value, non-linear
  uint8  tx_frequency_offset; //Up to 20 kHz
  uint32 rx_frequency_offset; //Up to 20 kHz
} RADIO_RF_CONFIGURATION_t ;

typedef struct
{
  uint8 beacon_interval; //value of 0 is off, 2.5 sec delay per LSB
} RADIO_BEACON_CONFIGURATION_t ;

typedef struct
{
  uint8 interface_baud_rate; //Radio Interface Baud Rate (9600=0x00)
  uint8 tx_power_amp_level;  //Tx Power Amp level (min = 0x00 max = 0xFF)
  uint8 rx_rf_baud_rate;     //Radio RX RF Baud Rate (9600=0x00)
  uint8 tx_rf_baud_rate;     //Radio TX RF Baud Rate (9600=0x00)
  uint8 rx_modulation;       //(0x00 = GFSK);
  uint8 tx_modulation;       //(0x00 = GFSK);
  uint32 rx_freq;             //Channel Rx Frequency (ex: 45000000)
  uint32 tx_freq;             //Channel Tx Frequency (ex: 45000000)
  unsigned char dest[6];       //AX25 Mode Source Call Sign (default NOCALL)
  unsigned char src[6];       //AX25 Mode Destination Call Sign (default CQ)
  uint16 tx_preamble;         //AX25 Mode Tx Preamble Byte Length (0x00 = 20 flags)
  uint16 tx_postamble;        //AX25 Mode Tx Postamble Byte Length (0x00 = 20 flags)
  uint16 function_config;     //Radio Configuration Discrete Behaviors
  uint16 function_config2;   //Radio Configuration Discrete Behaviors #2
} RADIO_CONFIGURATION_t ;

typedef struct
{
  uint16 wPacketsReceived;
  uint16 wRadioPktsReceived;
  uint16 wRadioPktsTransmitted;
  uint16 wFSWLoadPktsReceived;
  uint16 wAcksReceived;
  uint16 wNacksReceived;
  uint16 wHeaderCSErrors;
  uint16 wPacketCSErrors;
  uint16 wPacketTypeErrors;
  uint16 wPayloadSizeErrors;
  uint16 wSyncErrors;
} CommStats_t;

#pragma pack()

void LI1_SendNOP(void);
void LI1_ReadAllBytes(void);
void LI1_GetTransConfig(void);
void LI1_SetTransConfig(uint8 *pyFreq, uint8 *pyCall, uint8 *pyPwr, uint8 *pyConfig, uint8 *pyConfig2);
int LI1_RadioBytesAvail(void);
void LI1_DeassertReset(void);
void LI1_AssertReset(void);
void LI1_RadioConfig(void);
void LI1_BeaconConfig(uint8 yInterval);
void LI1_SetBeaconData(uint8 *pyBuf, int nLen);
void LI1_QueryTLM(void);
void LI1_Transmit(uint8 *pyBuf, int nLen);
void LI1_SetPower(uint8 yPwr);
void LI1_SendTestPacket(void);
void LI1_SetTestMode(int nMode);
int LI1_GetTestMode(void);
int LI1_GetCommand(uint8 *pBuf);
void LI1_ProcessCommand(uint8 *pBuf,int nLen);
int LI1_IsCommand_go_boot_cmd(uint8 *pBuf, int nLen);
void LI1_ReadFWRev(void);
void LI1_Init(void);
void LI1_GetCommStats(CommStats_t *pStats);
void LI1_GetLastTLM(TELEMETRY_STRUCTURE_t *pTLM);
void LI1_TX_Enable(uint8 yByte);
void LI1_IncrementFSWLoadPkts(void);

#endif