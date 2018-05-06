#ifndef _TELECOMMAND_H
#define _TELECOMMAND_H

#include "includes.h"

//Telecommand IDs
//Must be >= 0x80
#define TEST_PORT_WRITE      0x80
#define TEST_PORT_READ       0x81
#define CDH_ADC_READ         0x82
#define CDH_TEMP_READ        0x83
#define LI1_SEND_NOP         0x84
#define LI1_READ_BYTES       0x85
#define LI1_READ_CONFIG      0x86
#define LI1_SET_CONFIG       0x87
#define GO_BOOT_CMD          0x88
#define RESET_NV             0x89
#define RESET_CDH            0x8A
#define LI1_BEACON_CONFIG    0x8B
#define LI1_BEACON_DATA      0x8C
#define LI1_QUERY_TLM        0x8D
#define LI1_TRANSMIT         0x8E
#define LI1_SET_POWER        0x8F
#define LI1_SET_TEST_MODE    0x90
#define LI1_TEST_PACKET      0x91
#define LI1_READ_FW_REV      0x92
#define ADC_READ             0x93
#define MAG_READ             0x94
#define MAG_READ_ID          0x95
#define READ_ADC_TEMP        0x96
#define CDH_SET_DAC          0x97
#define MTQ_SETX             0x98
#define MTQ_SETY             0x99
#define MTQ_SETZ             0x9A
#define MTQ_SET_FREQ         0x9B
#define IMU2_READ_DATA       0x9C
#define IMU1_READ_DATA       0x9D
#define MRAM_WRITE_DATA      0x9E
#define MRAM_READ_DATA       0x9F
#define FSW_VERIFY_CODE      0xA0
#define FSW_COPY_CODE        0xA1
#define FSW_BOOT             0xA2
#define OP_SET_BOOT_PART     0xA3
#define FIPEX_READ_BYTES     0xA4
#define FIPEX_PING           0xA5
#define FIPEX_SC             0xA6
#define FIPEX_HK             0xA7
#define FIPEX_STDBY          0xA8
#define LI1_TX_ENABLE        0xA9
#define MSG_TX_ENABLE        0xAA
#define ACK_TX_ENABLE        0xAB
#define SET_INIT_WAIT        0xAC
#define READ_OP_STATUS       0xAD
#define SET_TIME             0xAE
#define SET_LAUNCH           0xAF
#define SET_ENABLE_DEPLOY    0xB0
#define SET_PHASE            0xB1

#define FSW_SYNC0            0x1A
#define FSW_SYNC1            0xCF
#define FSW_SYNC2            0xFC
#define FSW_SYNC3            0x1D

void ProcessTelecommand(uint8 *pBuf, int nLen);
int IsCommand_go_boot_cmd(uint8 *pBuf, int nLen);
int TC_VerifyTC(uint8 *pCmd, int nLen);

#endif