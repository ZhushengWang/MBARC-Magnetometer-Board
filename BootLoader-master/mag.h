#ifndef _MAG_H
#define _MAG_H

#include "includes.h"

#define SELECT_SP1_MAG      0
#define SELECT_SP2_MAG      1
#define SELECT_SP3_MAG      2
#define SELECT_BD4_MAG      3

#define NUM_MAGS            4
#define NUM_MAG_SAMPLES     5

void Mag_ReadAllMags(void);
void Mag_GetLastData(uint16 **pwData, uint8 ySelectMag);
int Mag_ReadData(uint16 *pwData, uint8 ySelectMag);
int Mag_InitMag(uint8 ySelectMag);
int Mag_ReadID(uint8 *pyData, uint8 ySelectMag);
float Mag_GetMag(int16 swMag);
float Mag_GetTemp(int16 swTemp);

#endif