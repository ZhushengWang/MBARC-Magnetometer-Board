#include "includes.h"

extern CDH_IO_t *cdhio;

#define CDH_ADC_SLAVE_ADDR  (0x2F << 1)
#define EPS1_ADC_SLAVE_ADDR (0x2F << 1)
#define EPS2_ADC_SLAVE_ADDR (0x2C << 1)
#define SP1_ADC_SLAVE_ADDR  (0x2F << 1)
#define SP2_ADC_SLAVE_ADDR  (0x2F << 1)
#define SP3_ADC_SLAVE_ADDR  (0x2F << 1)
#define BD4_ADC_SLAVE_ADDR  (0x2F << 1)

#define I2C_WRITE           0
#define I2C_READ            1

uint16 awLastADCData[NUM_ADCS][NUM_ADC_SAMPLES];

int WaitForReady(uint8 yMask)
{
  int nCount = 0;
  
  while ((!(cdhio->STATUS2 & yMask)) && (nCount <= 100))
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

int ReadCDHADC(uint16 *pwData)
{
uint8 ayDataBuf[16];
int i;
int nChannel;
uint16 wData;

  WaitForReady(STS2_CDH_ADC_READY);
  cdhio->CDH_ADC_START = 0;
  WaitForReady(STS2_CDH_ADC_READY);
  cdhio->CDH_ADC_WRITE = CDH_ADC_SLAVE_ADDR + I2C_WRITE;
  WaitForReady(STS2_CDH_ADC_READY);
  cdhio->CDH_ADC_WRITE = 0x00;  //Address Control Reg.
  WaitForReady(STS2_CDH_ADC_READY);  
  cdhio->CDH_ADC_WRITE = 0xFF;  //Select all channels
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0xA0;  //Second byte of Control Reg.
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0x01;  //Address Data Reg
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_STOP = 0;
  WaitForReady(STS2_CDH_ADC_READY);
  cdhio->CDH_ADC_START = 0; 
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = CDH_ADC_SLAVE_ADDR + I2C_READ;  
  
  for (i=0;i<=14;i++)
  {
    WaitForReady(STS2_CDH_ADC_READY); 
    cdhio->CDH_ADC_RD_INIT = 0;
    WaitForReady(STS2_CDH_ADC_READY); 
    ayDataBuf[i] = cdhio->CDH_ADC_WRITE;
  }
    
  WaitForReady(STS2_CDH_ADC_READY);  
  cdhio->CDH_ADC_RD_INIT = 1;  //NAK the last write
  WaitForReady(STS2_CDH_ADC_READY); 
  ayDataBuf[15] = cdhio->CDH_ADC_WRITE; 

  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_STOP = 0;
  
  for (i=0; i<=14; i+=2)
  {
    wData = ((ayDataBuf[i] & 0x0F) << 8) + ayDataBuf[i+1];
    nChannel = (ayDataBuf[i] >> 4) & 0x0F;
    
    pwData[nChannel] = wData;
    //*((uint16 *)(pwData + nChannel)) = wData;
  }   
  return(0);    
}

int ReadCDHADCTemp(uint16 *pwTemp)
{
uint8 ayDataBuf[4];
int i;
int nChannel;
uint16 wData;

  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_START = 0;
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = CDH_ADC_SLAVE_ADDR + I2C_WRITE;
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0x00;  //Address Control Reg.
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0xFF;  //Select all channels
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0xA0;  //Second byte of Control Reg.
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0x02;  //T Sense Data Reg
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_STOP = 0;
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_START = 0; 
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = CDH_ADC_SLAVE_ADDR + I2C_READ;  
  
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_RD_INIT = 0;
  WaitForReady(STS2_CDH_ADC_READY); 
  ayDataBuf[0] = cdhio->CDH_ADC_WRITE;
     
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_RD_INIT = 1;  //NAK the last write
  WaitForReady(STS2_CDH_ADC_READY); 
  ayDataBuf[1] = cdhio->CDH_ADC_WRITE; 

  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_STOP = 0;

  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_START = 0;
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = CDH_ADC_SLAVE_ADDR + I2C_WRITE;
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = 0x03;  //T Sense Average Reg
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_STOP = 0;
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_START = 0; 
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_WRITE = CDH_ADC_SLAVE_ADDR + I2C_READ;  

  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_RD_INIT = 0;
  WaitForReady(STS2_CDH_ADC_READY); 
  ayDataBuf[2] = cdhio->CDH_ADC_WRITE;
     
  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_RD_INIT = 1;  //NAK the last write
  WaitForReady(STS2_CDH_ADC_READY); 
  ayDataBuf[3] = cdhio->CDH_ADC_WRITE; 

  WaitForReady(STS2_CDH_ADC_READY); 
  cdhio->CDH_ADC_STOP = 0;  

  for (i=0; i<=2; i+=2)
  {
    wData = ((ayDataBuf[i] & 0x0F) << 8) + ayDataBuf[i+1];
    nChannel = (ayDataBuf[i] >> 4) & 0x0F;
    
    pwTemp[nChannel] = wData;
    //*((uint16 *)(pwTemp + nChannel)) = wData;
  }
  return(0);       
}

void GetADCAddresses(uint8 yADCSelect,
                     volatile uint8 **pyWrite, 
                     volatile uint8 **pyStart, 
                     volatile uint8 **pyStop, 
                     volatile uint8 **pyReadInit, 
                     uint8 *yReadyMask,
                     uint8 *ySlaveAddr)
{
  switch(yADCSelect)
  {
    case SELECT_CDH_ADC:
      *pyWrite    = &(cdhio->CDH_ADC_WRITE);
      *pyStart    = &(cdhio->CDH_ADC_START);
      *pyStop     = &(cdhio->CDH_ADC_STOP);
      *pyReadInit = &(cdhio->CDH_ADC_RD_INIT);
      *yReadyMask = STS2_CDH_ADC_READY;
      *ySlaveAddr = CDH_ADC_SLAVE_ADDR;      
      break;
      
    case SELECT_EPS_ADC1:
      *pyWrite    = &(cdhio->EPS_ADC_WRITE);
      *pyStart    = &(cdhio->EPS_ADC_START);
      *pyStop     = &(cdhio->EPS_ADC_STOP);
      *pyReadInit = &(cdhio->EPS_ADC_RD_INIT);
      *yReadyMask = STS2_EPS_ADC_READY;
      *ySlaveAddr = EPS1_ADC_SLAVE_ADDR;      
      break;
      
    case SELECT_EPS_ADC2:
      *pyWrite    = &(cdhio->EPS_ADC_WRITE);
      *pyStart    = &(cdhio->EPS_ADC_START);
      *pyStop     = &(cdhio->EPS_ADC_STOP);
      *pyReadInit = &(cdhio->EPS_ADC_RD_INIT);
      *yReadyMask = STS2_EPS_ADC_READY;
      *ySlaveAddr = EPS2_ADC_SLAVE_ADDR;      
      break;
      
    case SELECT_SP1_ADC:
      *pyWrite    = &(cdhio->SP1_ADC_WRITE);
      *pyStart    = &(cdhio->SP1_ADC_START);
      *pyStop     = &(cdhio->SP1_ADC_STOP);
      *pyReadInit = &(cdhio->SP1_ADC_RD_INIT);
      *yReadyMask = STS2_SP1_ADC_READY;
      *ySlaveAddr = SP1_ADC_SLAVE_ADDR;      
      break;
      
    case SELECT_SP2_ADC:
      *pyWrite    = &(cdhio->SP2_ADC_WRITE);
      *pyStart    = &(cdhio->SP2_ADC_START);
      *pyStop     = &(cdhio->SP2_ADC_STOP);
      *pyReadInit = &(cdhio->SP2_ADC_RD_INIT);
      *yReadyMask = STS2_SP2_ADC_READY;
      *ySlaveAddr = SP2_ADC_SLAVE_ADDR;      
      break;
     
    case SELECT_SP3_ADC:
      *pyWrite    = &(cdhio->SP3_ADC_WRITE);
      *pyStart    = &(cdhio->SP3_ADC_START);
      *pyStop     = &(cdhio->SP3_ADC_STOP);
      *pyReadInit = &(cdhio->SP3_ADC_RD_INIT);
      *yReadyMask = STS2_SP3_ADC_READY;
      *ySlaveAddr = SP3_ADC_SLAVE_ADDR;      
      break;
      
    case SELECT_BD4_ADC:
      *pyWrite    = &(cdhio->BD4_ADC_WRITE);
      *pyStart    = &(cdhio->BD4_ADC_START);
      *pyStop     = &(cdhio->BD4_ADC_STOP);
      *pyReadInit = &(cdhio->BD4_ADC_RD_INIT);
      *yReadyMask = STS2_BD4_ADC_READY;
      *ySlaveAddr = BD4_ADC_SLAVE_ADDR;      
      break;
      
    default:
      *pyWrite    = &(cdhio->CDH_ADC_WRITE);
      *pyStart    = &(cdhio->CDH_ADC_START);
      *pyStop     = &(cdhio->CDH_ADC_STOP);
      *pyReadInit = &(cdhio->CDH_ADC_RD_INIT);
      *yReadyMask = STS2_CDH_ADC_READY;
      *ySlaveAddr = CDH_ADC_SLAVE_ADDR;      
      break; 
  }
}
                     
int ReadADC(uint16 *pwData, uint8 ySelectADC)
{
uint8 ayDataBuf[16];
int i;
int nChannel;
uint16 wData;
volatile uint8 *pyWrite;
volatile uint8 *pyStart; 
volatile uint8 *pyStop; 
volatile uint8 *pyReadInit; 
uint8 yReadyMask;
uint8 ySlaveAddr;

  GetADCAddresses(ySelectADC,&pyWrite,&pyStart,&pyStop,&pyReadInit,&yReadyMask,&ySlaveAddr);
  
  WaitForReady(yReadyMask);
  *pyStart = 0;
  WaitForReady(yReadyMask);
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForReady(yReadyMask);
  *pyWrite = 0x00;  //Address Control Reg.
  WaitForReady(yReadyMask);  
  *pyWrite = 0xFF;  //Select all channels
  WaitForReady(yReadyMask); 
  *pyWrite = 0xA0;  //Second byte of Control Reg.
  WaitForReady(yReadyMask); 
  *pyWrite = 0x01;  //Address Data Reg
  WaitForReady(yReadyMask); 
  *pyStop = 0;
  WaitForReady(yReadyMask);
  *pyStart = 0; 
  WaitForReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_READ;  
  
  for (i=0;i<=14;i++)
  {
    WaitForReady(yReadyMask); 
    *pyReadInit = 0;
    WaitForReady(yReadyMask); 
    ayDataBuf[i] = *pyWrite;
  }
    
  WaitForReady(yReadyMask);  
  *pyReadInit = 1;  //NAK the last write
  WaitForReady(yReadyMask); 
  ayDataBuf[15] = *pyWrite; 

  WaitForReady(yReadyMask); 
  *pyStop = 0;
  
  for (i=0; i<=14; i+=2)
  {
    wData = ((ayDataBuf[i] & 0x0F) << 8) + ayDataBuf[i+1];
    nChannel = (ayDataBuf[i] >> 4) & 0x0F;
    
    pwData[nChannel] = wData;
    //*((uint16 *)(pwData + nChannel)) = wData;
  }   
  return(0);    
}

int ReadADCTemp(uint16 *pwTemp, uint8 ySelectADC)
{
uint8 ayDataBuf[4];
int i;
int nChannel;
uint16 wData;
volatile uint8 *pyWrite;
volatile uint8 *pyStart; 
volatile uint8 *pyStop; 
volatile uint8 *pyReadInit; 
uint8 yReadyMask;
uint8 ySlaveAddr;

  GetADCAddresses(ySelectADC,&pyWrite,&pyStart,&pyStop,&pyReadInit,&yReadyMask,&ySlaveAddr);
  
  WaitForReady(yReadyMask); 
  *pyStart = 0;
  WaitForReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForReady(yReadyMask); 
  *pyWrite = 0x00;  //Address Control Reg.
  WaitForReady(yReadyMask); 
  *pyWrite = 0xFF;  //Select all channels
  WaitForReady(yReadyMask); 
  *pyWrite = 0xA0;  //Second byte of Control Reg.
  WaitForReady(yReadyMask); 
  *pyWrite = 0x02;  //T Sense Data Reg
  WaitForReady(yReadyMask); 
  *pyStop = 0;
  WaitForReady(yReadyMask); 
  *pyStart = 0; 
  WaitForReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_READ;  
  
  WaitForReady(yReadyMask); 
  *pyReadInit = 0;
  WaitForReady(yReadyMask); 
  ayDataBuf[0] = *pyWrite;
     
  WaitForReady(yReadyMask); 
  *pyReadInit = 1;  //NAK the last read
  WaitForReady(yReadyMask); 
  ayDataBuf[1] = *pyWrite; 

  WaitForReady(yReadyMask); 
  *pyStop = 0;

  WaitForReady(yReadyMask); 
  *pyStart = 0;
  WaitForReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_WRITE;
  WaitForReady(yReadyMask); 
  *pyWrite = 0x03;  //T Sense Average Reg
  WaitForReady(yReadyMask); 
  *pyStop = 0;
  WaitForReady(yReadyMask); 
  *pyStart = 0; 
  WaitForReady(yReadyMask); 
  *pyWrite = ySlaveAddr + I2C_READ;  

  WaitForReady(yReadyMask); 
  *pyReadInit = 0;
  WaitForReady(yReadyMask); 
  ayDataBuf[2] = *pyWrite;
     
  WaitForReady(yReadyMask); 
  *pyReadInit = 1;  //NAK the last read
  WaitForReady(yReadyMask); 
  ayDataBuf[3] = *pyWrite; 

  WaitForReady(yReadyMask); 
  *pyStop = 0;  

  for (i=0; i<=2; i+=2)
  {
    wData = ((ayDataBuf[i] & 0x0F) << 8) + ayDataBuf[i+1];
    nChannel = (ayDataBuf[i] >> 4) & 0x0F;
    
    pwTemp[nChannel] = wData;
  }
  return(0);       
}

void ADC_ReadAllADCs(void)
{
int i;

  for(i=0;i<=6;i++)
  {
    ReadADC(awLastADCData[i],i);
    ReadADCTemp(awLastADCData[i],i);
  }
}

void ADC_GetLastADCData(uint16 **pwData, uint8 yADC)
{
  *pwData = awLastADCData[yADC];
}
