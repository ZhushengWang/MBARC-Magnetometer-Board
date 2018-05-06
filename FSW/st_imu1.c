#include "includes.h"

extern CDH_IO_t *cdhio;

#define IMU1_SLAVE_ADDR  0xD4

#define I2C_WRITE           0
#define I2C_READ            1

ST_IMU1_DATA_t IMU1_LastData;

int WaitForIMU1Ready(uint8 yMask)
{
  int nCount = 0;

  while ((!(cdhio->STATUS1 & yMask)) && (nCount <= 100))
  {
    nCount++;
  }

  if (nCount < 100)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int IMU1_Init(void)
{
const uint8 yReadyMask = STS1_CDH_IMU1_READY;

  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_WRITE;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x20 | 0x80;  //Address Control Reg. 1, multi-write
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x0F;  //CREG1 100sps, 12.5Hz Fc, Normal, X,Y,Z enabled
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x00;  //CREG2
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x00;  //CREG3  No ints
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0xC0;  //CREG4  continuous update,Big endian, 245dps
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x02;  //CREG5  LPF2
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_STOP = 0;
  WaitForIMU1Ready(yReadyMask);

  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_WRITE;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x2E;  //FIFO_CTRL
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x00;  //
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_STOP = 0;
  WaitForIMU1Ready(yReadyMask);
/*
  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_WRITE;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x39;  //LOW_ODR
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x01;  //
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_STOP = 0;
  WaitForIMU1Ready(yReadyMask);
*/
  return 0;
}

int IMU1_ReadData(ST_IMU1_DATA_t *pData)
{
int i;
uint8 ayDataBuf[8];
const uint8 yReadyMask = STS1_CDH_IMU1_READY;
int8 syTemp;
int16 swGyro;

  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_WRITE;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x26 | 0x80;  //Address OUT_TEMP, multi-read
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_STOP = 0;
  WaitForIMU1Ready(yReadyMask);

  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_READ;

  for (i=0;i<=6;i++)
  {
    WaitForIMU1Ready(yReadyMask);
    cdhio->IMU1_RD_INIT = 0;
    WaitForIMU1Ready(yReadyMask);
    ayDataBuf[i] = cdhio->IMU1_WRITE;
  }

  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_RD_INIT = 1;
  WaitForIMU1Ready(yReadyMask);
  ayDataBuf[7] = cdhio->IMU1_WRITE;

  WaitForIMU1Ready(yReadyMask);

  cdhio->IMU1_STOP = 0;

  syTemp =ayDataBuf[0];
  IMU1_LastData.nTemp = syTemp;

  IMU1_LastData.nStatus = ayDataBuf[1];

  swGyro = (ayDataBuf[2] << 8) + ayDataBuf[3];
  IMU1_LastData.nXGyroOut = swGyro;

  swGyro = (ayDataBuf[4] << 8) + ayDataBuf[5];
  IMU1_LastData.nYGyroOut = swGyro;

  swGyro = (ayDataBuf[6] << 8) + ayDataBuf[7];
  IMU1_LastData.nZGyroOut = swGyro;

  IMU1_LastData.unTime = get_time();

  if (pData != NULL)
  {
    memcpy(pData,&IMU1_LastData,sizeof(ST_IMU1_DATA_t));
  }

  return 0;
}

void IMU1_ReadID(uint8 *pyID)
{
const uint8 yReadyMask = STS1_CDH_IMU1_READY;

  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_WRITE;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = 0x0F;  //Address WHO_AM_I
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_STOP;
  WaitForIMU1Ready(yReadyMask);

  cdhio->IMU1_START = 0;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_WRITE = IMU1_SLAVE_ADDR + I2C_READ;

  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_RD_INIT = 1;
  WaitForIMU1Ready(yReadyMask);
  *pyID = cdhio->IMU1_WRITE;
  WaitForIMU1Ready(yReadyMask);
  cdhio->IMU1_STOP = 0;
}

int IMU1_GetTemp(int32 nTemp)
{
  return(25 + nTemp);
}

float IMU1_GetGyro(int32 nGyro)
{
  return(nGyro * 0.00875);
}

void IMU1_GetLastData(ST_IMU1_DATA_t *pData)
{
  memcpy(pData,&IMU1_LastData,sizeof(ST_IMU1_DATA_t));
}
