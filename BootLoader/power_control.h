#ifndef _POWER_CONTROL_H
#define _POWER_CONTROL_H

#include "includes.h"

#define CDH_ADC  1
#define CDH_IMU1 2
#define CDH_IMU2 3
#define CDH_DAC  4
#define RADIO    5
#define SP1_ADC  6
#define SP1_MAG  7
#define SP2_ADC  8
#define SP2_MAG  9
#define SP3_ADC  10
#define SP3_MAG  11
#define BD4_ADC  12
#define BD4_MAG  13
#define EPS_ADC  14
#define MBARC_MAG  15

#define PWR_ON   1
#define PWR_OFF  0

void pwr_ctl(int nDevice, int nState);
void PWR_AllDevicesOff(void);
void PWR_AllADCsOn(void);
void PWR_PrintStatus(void);
void PWR_MbarcMagOn(uint8 yOn);
void PWR_RadioOn(uint8 yOn);
void PWR_IMU2On(uint8 yOn);
void PWR_IMU1On(uint8 yOn);
void PWR_AllMagsOn(void);
void PWR_PrintStatus(void);

#endif