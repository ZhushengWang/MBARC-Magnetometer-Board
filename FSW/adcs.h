#ifndef _ADCS_H
#define _ADCS_H

#include "includes.h"

#pragma pack(1)

typedef struct 
{
  uint32 unTime;
  int16  wQ1;
  int16  wQ2;
  int16  wQ3;
  int16  wQ4;
  int16  wXDot;
  int16  wYDot;
  int16  wZDot;
  int16  wX_ECEF;
  int16  wY_ECEF;
  int16  wZ_ECEF;
} ATTITUDE_STRUCT_t;

#pragma pack()

void ADCS_GetLastAttitude(ATTITUDE_STRUCT_t *pAtt);
void ADCS_UpdateAttitude(void);
void ADCS_UpdateAttitude_Test(void);

#endif