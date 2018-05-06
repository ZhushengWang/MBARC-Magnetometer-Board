#include "includes.h"

extern CDH_IO_t *cdhio;

void Mbarc_Mag_Init(void)
{
  nIMUStep = 0;
  IMU2_EmptyFIFO(); //Make sure FIFO is empty
  memset(&EpsonData,0,sizeof(EPSON_IMU2_DATA_t));
}

void Mbarc_Mag_SetCycleCount()
{
  cdhio->MBARC_MAG_TX = 0x01;
  cdhio->MBARC_MAG_TX = 0x03;
  cdhio->MBARC_MAG_TX = 0x20;
  for(i=3;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_ReadCycleCount()
{
  cdhio->MBARC_MAG_TX = 0x02;
  for(i=1;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_StartMeasurement(uint8 freqSet)
{
  cdhio->MBARC_MAG_TX = 0x03;
  for(i=1;i<=4;i++)
  {
    cdhio->MBARC_MAG_TX = 0xFF;
  }
  cdhio->MBARC_MAG_TX = freqSet;
  for(i=6;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_RetrieveData(uint8 retrieveMode)
{
  cdhio->MBARC_MAG_TX = 0x05;
  dhio->MBARC_MAG_TX = retrieveMode;
  for(i=2;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_Stop()
{
  cdhio->MBARC_MAG_TX = 0x06;
  for(i=1;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_Reset()
{
  cdhio->MBARC_MAG_TX = 0x07;
  for(i=1;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}