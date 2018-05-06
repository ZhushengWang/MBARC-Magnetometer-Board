#ifndef _ST_IMU1_H
#define _ST_IMU1_H

#include "includes.h"

#pragma pack(1)

typedef struct
{
  int32 nTemp;
  int32 nStatus;
  int32 nXGyroOut;
  int32 nYGyroOut;
  int32 nZGyroOut;
  uint32 unTime;
} ST_IMU1_DATA_t;

#pragma pack()

int IMU1_Init(void);
int IMU1_ReadData(ST_IMU1_DATA_t *pData);
int IMU1_GetTemp(int32 nTemp);
float IMU1_GetGyro(int32 nGyro);
void IMU1_GetLastData(ST_IMU1_DATA_t *pData);

#endif
