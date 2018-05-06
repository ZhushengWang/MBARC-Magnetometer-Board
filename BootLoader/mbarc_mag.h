#ifndef _MBARC_MAG_H
#define _MBARC_MAG_H

#include "includes.h"

#pragma pack(1)

typedef struct
{
  uint16 sciArrayIndex;
  int32 xCycleCount;
  int32 yCycleCount;
  int32 zCycleCount;
  int32 measureStartTime1;
  uint16 mag1ReportTime;
  uint16 mag2ReportTime;
  uint16 mag3ReportTime;
  uint16 mag4ReportTime;
  uint16 measureStartTime2;
} MBARC_MAG_DATA_t;

#pragma pack()

void Mbarc_Mag_SetCycleCount();
void Mbarc_Mag_ReadCycleCount();
void Mbarc_Mag_StartMeasurement();
void Mbarc_Mag_RetrieveData();
void Mbarc_Mag_Stop();
void Mbarc_Mag_Reset();

#endif