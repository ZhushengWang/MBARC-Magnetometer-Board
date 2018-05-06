#ifndef _ADC_H
#define _ADC_H

#include "includes.h"

#define SELECT_CDH_ADC  0
#define SELECT_EPS_ADC1 1
#define SELECT_EPS_ADC2 2
#define SELECT_SP1_ADC  3
#define SELECT_SP2_ADC  4
#define SELECT_SP3_ADC  5
#define SELECT_BD4_ADC  6

#define NUM_ADC_SAMPLES     10   //8 Channels + 2 temps
#define NUM_ADCS             7   

int ReadCDHADC(uint16 *pwData);
int ReadCDHADCTemp(uint16 *pwTemp);
int ReadADC(uint16 *pwData, uint8 ySelectADC);
int ReadADCTemp(uint16 *pwTemp, uint8 ySelectADC);
void ADC_ReadAllADCs(void);
void ADC_GetLastADCData(uint16 **pwData, uint8 yADC);

#endif