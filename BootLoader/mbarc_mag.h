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

void Mbarc_Mag_Init(void);
void Mbarc_Mag_Dotasks(void);
void Mbarc_Mag_GetLastData(MBARC_MAG_DATA_t *mmData);
void Mbarc_Mag_AssertReset(void);
void Mbarc_Mag_DeassertReset(void);
void Mbarc_Mag_SetCycleCount(void);
void Mbarc_Mag_ReadCycleCount(void);
void Mbarc_Mag_StartMeasurement(uint8 freqSet);
void Mbarc_Mag_RetrieveData(uint8 retrieveMode);
void Mbarc_Mag_Stop(void);
void Mbarc_Mag_Reset(void);

#endif