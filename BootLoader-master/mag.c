#include "includes.h"

extern CDH_IO_t *cdhio;

#define SP1_MAG_SLAVE_ADDR  (0x1C << 1)
#define SP2_MAG_SLAVE_ADDR  (0x1C << 1)
#define SP3_MAG_SLAVE_ADDR  (0x1C << 1)
#define BD4_MAG_SLAVE_ADDR  (0x1C << 1)

#define I2C_WRITE           0
#define I2C_READ            1

uint16 Mag_LastMagData[NUM_MAGS][NUM_MAG_SAMPLES];

int WaitForMagReady(uint8 yMask)
{
  int nCount = 0;
  
  while ((!(cdhio->STATUS3 & yMask)) && (nCount <= 100))
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

void GetMagAddresses(uint8 yMagSelect,
                     volatile uint8 **pyWrite, 
                     volatile uint8 **pyStart, 
                     volatile uint8 **pyStop, 
                     volatile uint8 **pyReadInit, 
                     uint8 *yReadyMask,
                     uint8 *ySlaveAddr)
{
  switch(yMagSelect)
  {     
    case SELECT_SP1_MAG:
      *pyWrite    = &(cdhio->SP1_MAG_WRITE);
      *pyStart    = &(cdhio->SP1_MAG_START);
      *pyStop     = &(cdhio->SP1_MAG_STOP);
      *pyReadInit = &(cdhio->SP1_MAG_RD_INIT);
      *yReadyMask = STS3_SP1_MAG_READY;
      *ySlaveAddr = SP1_MAG_SLAVE_ADDR;      
      break;
      
    case SELECT_SP2_MAG:
      *pyWrite    = &(cdhio->SP2_MAG_WRITE);
      *pyStart    = &(cdhio->SP2_MAG_START);
      *pyStop     = &(cdhio->SP2_MAG_STOP);
      *pyReadInit = &(cdhio->SP2_MAG_RD_INIT);
      *yReadyMask = STS3_SP2_MAG_READY;
      *ySlaveAddr = SP2_MAG_SLAVE_ADDR;      
      break;
     
    case SELECT_SP3_MAG:
      *pyWrite    = &(cdhio->SP3_MAG_WRITE);
      *pyStart    = &(cdhio->SP3_MAG_START);
      *pyStop     = &(cdhio->SP3_MAG_STOP);
      *pyReadInit = &(cdhio->SP3_MAG_RD_INIT);
      *yReadyMask = STS3_SP3_MAG_READY;
      *ySlaveAddr = SP3_MAG_SLAVE_ADDR;      
      break;
      
    case SELECT_BD4_MAG:
      *pyWrite    = &(cdhio->BD4_MAG_WRITE);
      *pyStart    = &(cdhio->BD4_MAG_START);
      *pyStop     = &(cdhio->BD4_MAG_STOP);
      *pyReadInit = &(cdhio->BD4_MAG_RD_INIT);
      *yReadyMask = STS3_BD4_MAG_READY;
      *ySlaveAddr = BD4_MAG_SLAVE_ADDR;      
      break;
      
    default:
      *pyWrite    = &(cdhio->SP1_MAG_WRITE);
      *pyStart    = &(cdhio->SP1_MAG_START);
      *pyStop     = &(cdhio->SP1_MAG_STOP);
      *pyReadInit = &(cdhio->SP1_MAG_RD_INIT);
      *yReadyMask = STS3_SP1_MAG_READY;
      *ySlaveAddr = SP1_MAG_SLAVE_ADDR;       
      break; 
  }
}

int Mag_InitMag(uint8 ySelectMag)
{
volatile uint8 *pyWrite;
volatile uint8 *pyStart; 
volatile uint8 *pyStop; 
volatile uint8 *pyReadInit; 
uint8 yReadyMask;
uint8 ySlaveAddr;

  GetMagAddresses(ySelectMag,&pyWrite,&pyStart,&pyStop,&pyReadInit,&yReadyMask,&ySlaveAddr);
  
  WaitForMagReady(yReadyMask);
  *pyStart = 0;
  WaitForMagReady(yReadyMask);
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x20 | 0x80;  //Address Control Reg. 1, multi-write
  WaitForMagReady(yReadyMask); 
  *pyWrite = 0xEC;  //CREG1 Ultra High performace x,y/5 Hz
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x00;  //CREG2  +/-4G full scale
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x00;  //CREG3  Continuous sampling
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x0C;  //CREG4  Z Axis Ultra
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x40;  //CREG5  Block update
  WaitForMagReady(yReadyMask);
  *pyStop = 0; 
  
  return 0;
}
                     
int Mag_ReadData(uint16 *pwData, uint8 ySelectMag)
{
uint8 ayDataBuf[9];
int i;
int nChannel;
uint16 wData;
volatile uint8 *pyWrite;
volatile uint8 *pyStart; 
volatile uint8 *pyStop; 
volatile uint8 *pyReadInit; 
uint8 yReadyMask;
uint8 ySlaveAddr;

  GetMagAddresses(ySelectMag,&pyWrite,&pyStart,&pyStop,&pyReadInit,&yReadyMask,&ySlaveAddr);
  
  WaitForMagReady(yReadyMask);
  *pyStart = 0;
  WaitForMagReady(yReadyMask);
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x27 | 0x80;  //Address of Status Reg, multi-read
  WaitForMagReady(yReadyMask); 
  *pyStop = 0;
  WaitForMagReady(yReadyMask);
  *pyStart = 0; 
  WaitForMagReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_READ;  
  
  //Read 6 values
  for (i=0;i<=5;i++)
  {
    WaitForMagReady(yReadyMask); 
    *pyReadInit = 0;
    WaitForMagReady(yReadyMask); 
    ayDataBuf[i] = *pyWrite;
  }
    
  //Read the final value
  WaitForMagReady(yReadyMask);  
  *pyReadInit = 1;  //NAK the last write
  WaitForMagReady(yReadyMask); 
  ayDataBuf[6] = *pyWrite; 

  WaitForMagReady(yReadyMask); 
  *pyStop = 0;

  //Read the temperature
  //For some reason it doesn't
  //come with the multi-read
  WaitForMagReady(yReadyMask);
  *pyStart = 0;
  WaitForMagReady(yReadyMask);
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x2E | 0x80;  //Address of Status Reg, multi-read
  WaitForMagReady(yReadyMask); 
  *pyStop = 0;
  WaitForMagReady(yReadyMask);
  *pyStart = 0; 
  WaitForMagReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_READ;   
  
  //Get LSB
  WaitForMagReady(yReadyMask); 
  *pyReadInit = 0;
  WaitForMagReady(yReadyMask); 
  ayDataBuf[7] = *pyWrite;
    
  //Read the final value
  WaitForMagReady(yReadyMask);  
  *pyReadInit = 1;  //NAK the last write
  WaitForMagReady(yReadyMask); 
  ayDataBuf[8] = *pyWrite; 

  WaitForMagReady(yReadyMask); 
  *pyStop = 0;  
  
  //Convert to 16 bit values
  
  pwData[0] = ayDataBuf[0];  //Status Register
  nChannel=1;
  
  //X,Y,Z readings plus temperature
  for (i=1; i<=8; i+=2)
  {
    wData = (ayDataBuf[i+1] << 8) + ayDataBuf[i];
    
    pwData[nChannel++] = wData;
  }   
  return(0);    
}

int Mag_ReadID(uint8 *pyData, uint8 ySelectMag)
{
volatile uint8 *pyWrite;
volatile uint8 *pyStart; 
volatile uint8 *pyStop; 
volatile uint8 *pyReadInit; 
uint8 yReadyMask;
uint8 ySlaveAddr;

  GetMagAddresses(ySelectMag,&pyWrite,&pyStart,&pyStop,&pyReadInit,&yReadyMask,&ySlaveAddr);

  WaitForMagReady(yReadyMask);
  *pyStart = 0;
  WaitForMagReady(yReadyMask);
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForMagReady(yReadyMask);
  *pyWrite = 0x0F;  //Address of Status Reg, single-read
  WaitForMagReady(yReadyMask); 
  *pyStop = 0;
  WaitForMagReady(yReadyMask);
  *pyStart = 0; 
  WaitForMagReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_READ;  
  
  WaitForMagReady(yReadyMask);  
  *pyReadInit = 1;  //NAK the last write
  WaitForMagReady(yReadyMask); 
  *pyData = *pyWrite; 

  WaitForMagReady(yReadyMask); 
  *pyStop = 0; 

  return(0);
}

float Mag_GetMag(int16 swMag)
{
  return((float)swMag/6842.0);
}

float Mag_GetTemp(int16 swTemp)
{
  return((float)swTemp/8.0);
}

void Mag_ReadAllMags(void)
{
int i;

  for (i=0;i<4;i++)
  {
    Mag_ReadData(Mag_LastMagData[i],i);
  }
}

void Mag_GetLastData(uint16 **pwData, uint8 ySelectMag)
{
  *pwData = Mag_LastMagData[ySelectMag];
}