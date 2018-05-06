#include "includes.h"

ATTITUDE_STRUCT_t asLastAttitude;
EPSON_IMU2_DATA_t imu2Data;

void ADCS_GetLastAttitude(ATTITUDE_STRUCT_t *pAtt)
{
  memcpy(pAtt,&asLastAttitude,sizeof(ATTITUDE_STRUCT_t));
}

void ADCS_UpdateAttitude(void)
{
  asLastAttitude.unTime = get_time();
  asLastAttitude.wQ1 = 0;
  asLastAttitude.wQ2 = 0;
  asLastAttitude.wQ3 = 0;
  asLastAttitude.wQ4 = 0;  
  
  IMU2_GetLastData(&imu2Data);
  
  asLastAttitude.wXDot = imu2Data.nXGyroOut >> 16;
  asLastAttitude.wYDot = imu2Data.nYGyroOut >> 16;
  asLastAttitude.wZDot = imu2Data.nZGyroOut >> 16;
  
  asLastAttitude.wX_ECEF = 0;
  asLastAttitude.wY_ECEF = 0;
  asLastAttitude.wZ_ECEF = 0;
}

void _ADCS_UpdateAttitude_Test(void)
{
  asLastAttitude.unTime = 0x12345678;
  asLastAttitude.wQ1 = 0x9ABC;
  asLastAttitude.wQ2 = 0xDEF0;
  asLastAttitude.wQ3 = 0x1234;
  asLastAttitude.wQ4 = 0x5678; 
  
  asLastAttitude.wXDot = 0xABCD;
  asLastAttitude.wYDot = 0xEF01;
  asLastAttitude.wZDot = 0x2345;
  
  asLastAttitude.wX_ECEF = 0x6789;
  asLastAttitude.wY_ECEF = 0xBCDE;
  asLastAttitude.wZ_ECEF = 0xF012;
}

