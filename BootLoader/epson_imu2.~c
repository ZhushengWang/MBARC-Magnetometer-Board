#include "includes.h"

extern CDH_IO_t *cdhio;

#define BURST_SIZE 36

int nIMUStep = 0;
EPSON_IMU2_DATA_t EpsonData;

void IMU2_AssertReset(void)
{
  cdhio->CONTROL2 &= ~CTL2_CDH_IMU2_NRESET;  //Assert reset for radio
}

void IMU2_DeassertReset(void)
{
  cdhio->CONTROL2 |= CTL2_CDH_IMU2_NRESET;  //De-assert reset for radio
}

void IMU2_WriteReg(uint8 yAddr, uint8 yData)
{
  cdhio->IMU2_TX = yAddr | 0x80;
  cdhio->IMU2_TX = yData;
  cdhio->IMU2_TX = 0x0d;
}

void IMU2_ReadReg(uint8 yAddr)
{
  cdhio->IMU2_TX = yAddr;
  cdhio->IMU2_TX = 0x00;
  cdhio->IMU2_TX = 0x0d;
}

int IMU2_DataAvail(void)
{
  if (!(cdhio->STATUS1 & STS1_EPSON_RX_EMPTY))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void IMU2_EmptyFIFO(void)
{
  while (IMU2_DataAvail())
  {
    cdhio->IMU2_RX = 0;
  }
}

int IMU2_WaitForData(void)
{
  int nLoopCount = 0;
  
  while ((!IMU2_DataAvail()) && (nLoopCount < 1000))
  {
    nLoopCount++;
  }
  
  if (nLoopCount >= 100)
  {
    return(-1);  //Timeout
  }
  else
  {
    return(0);
  }
}

int IMU2_ReadRegData(uint8 *pBuf)
{
  int i;
  int nRC = 0;
  
  if (IMU2_DataAvail())
  {
    for(i=0;i<4;i++)
    {
      if (IMU2_WaitForData() == 0)
      {
        cdhio->IMU2_RX = 0;
        pBuf[i] = cdhio->IMU2_TX;
      }
      else
      {
        print_uart_msg("IMU2: Read Timeout.\n");
        nRC = -1;
        break;         
      }     
    }
  }
  else
  {
    nRC = -1;
  }
  
  return (nRC);   
}

int IMU2_ReadBurstData(void)
{
  uint8 Buf[BURST_SIZE];
  int i;
  uint8 yFirstByte;
  int nRC = 0;
  
  if (IMU2_DataAvail())
  {
    cdhio->IMU2_RX = 0;
    yFirstByte = cdhio->IMU2_TX;
  
    if (yFirstByte == 0x80)
    {
      Buf[0] = yFirstByte;
      
      for(i=1;i<BURST_SIZE;i++)
      {
        if (IMU2_WaitForData() == 0)
        {
          cdhio->IMU2_RX = 0;
          Buf[i] = cdhio->IMU2_TX;
        }
        else
        {
          print_uart_msg("IMU2-Burst: Read Timeout.\n");
          nRC = -1;
          break;         
        }
      }
      EpsonData.nAddr = Buf[0];
      EpsonData.nND = Buf[1];
      EpsonData.nEA = Buf[2];
      memcpy(&(EpsonData.nTempOut),&Buf[3],28);
      EpsonData.nGPIO = (Buf[31] << 8) + Buf[32];
      EpsonData.nCount = (Buf[33] << 8) + Buf[34];
      EpsonData.nCR = Buf[35];
      EpsonData.unTime = get_time();
    }
    else
    {
      //FIFO out of sync, empty it
      while (IMU2_DataAvail())
      {
        cdhio->IMU2_RX;
      }
      print_uart_msg("IMU2-Burst: Bad Data.\n");
      nRC = -1;
    }
  }
  else
  {
    nRC = -1;
  }
  
  return (nRC);   
}

void IMU2_Init(void)
{
  nIMUStep = 0;
  IMU2_EmptyFIFO(); //Make sure FIFO is empty
  memset(&EpsonData,0,sizeof(EPSON_IMU2_DATA_t));
}

void IMU2_DoTasks(void)
{
  uint8 Buf[4];
  
  switch (nIMUStep)
  {
    case 0:
      nIMUStep = 1;  //Wait for 800ms startup
      break;
      
    case 1:
      nIMUStep = 2;
      break;
      
    case 2:
      nIMUStep = 3;
      break;
      
    case 3:
      nIMUStep = 4;
      break;
    
    case 4:
      IMU2_WriteReg(0x7e,1);  //Window 1
      nIMUStep = 5;
      break;
     
    case 5:
      IMU2_ReadReg(0x0A);  //Check for ready
      nIMUStep = 6;
      break;
      
    case 6:
      if (IMU2_ReadRegData(Buf) >= 0)
      {
        if (Buf[0] == 0x0A)
        {
          if ((Buf[1] & 0x04) == 0)
          {
            nIMUStep = 7;  //Ready
            print_uart_msg("IMU2: Ready.\n");
          }
          else
          {
            nIMUStep = 5;  // Not ready
            print_uart_msg("IMU2: Not Ready.\n");
          }
        }
        else
        {
          IMU2_Init();
          print_uart_msg("IMU2: Bad Ready Response.\n");
        }
      }
      else
      {
        IMU2_Init();
        print_uart_msg("IMU2: Ready Read Timeout.\n");
      }
      break;
      
    case 7:
      IMU2_WriteReg(0x7e,0);  //Window 0
      nIMUStep = 8;
      break;
      
    case 8:  //IMU2 is ready, Check hard error
      IMU2_ReadReg(0x04);  //Check for ready
      nIMUStep = 9;
      break;
    
    case 9:  
      if (IMU2_ReadRegData(Buf) >= 0)
      {
        if (Buf[0] == 0x04)
        {
          if ((Buf[2] & 0x60) == 0)
          {
            nIMUStep = 10;
          }
          else
          {
            IMU2_Init();
            print_uart_msg("IMU2:  Hard Error.\n");
          }
        }
        else
        {
          IMU2_Init();
          print_uart_msg("IMU2: Bad Diag Response.\n");
        }
      }
      else
      {
        IMU2_Init();
        print_uart_msg("IMU2: Diag Read Timeout.\n");
      }
      break;      
      
    case 10:     //Set up registers
      IMU2_WriteReg(0x7E,0x01); //Window 1
      nIMUStep++;
      break;
      
    case 11:     //Set up registers
      IMU2_WriteReg(0x05,0x07); //31.25sps
      nIMUStep++;
      break;

    case 12:     //Set up registers
      IMU2_WriteReg(0x06,0x08); //FIR Kaiser Filter, Fc=50Hz
      nIMUStep++;
      break;
      
    case 13:     //Set up registers
      IMU2_WriteReg(0x08,0x00); //Manual Mode
      nIMUStep++;
      break;

    case 14:     //Set up registers
      IMU2_WriteReg(0x0C,0x06); //GPIO/Count no CSum
      nIMUStep++;
      break;
 
    case 15:     //Set up registers
      IMU2_WriteReg(0x0D,0xF0); //Flag,Temp,Gyro,Accl
      nIMUStep++;
      break;
 
    case 16:     //Set up registers
      IMU2_WriteReg(0x0F,0x70); //32-bit
      nIMUStep++;
      break;
 
    case 17:     //Set up registers
      IMU2_WriteReg(0x7E,0x00); //Window 0
      nIMUStep++;
      break;
   
    case 18:     //Set up registers
      IMU2_WriteReg(0x03,0x01); //Sample Mode
      nIMUStep++;
      break;
      
    case 19:
      IMU2_WriteReg(0x00,0x00); //Get Burst Data
      nIMUStep++;
      break;
      
    case 20:
      if (IMU2_ReadBurstData() >= 0)
      {
        nIMUStep = 19;
      }
      else
      {
        IMU2_Init();
        print_uart_msg("IMU2: Error reading burst data\n");
      }
      break;
    
    default:
      IMU2_Init();
      break;
  }
}  
  
void IMU2_GetLastData(EPSON_IMU2_DATA_t *pData)
{
  memcpy(pData,&EpsonData,sizeof(EpsonData));
}

float IMU2_GetTemp(int32 nTemp)
{
  return ((0.0042725 * (nTemp + 997064704.0)/65536.0)+25);
}

float IMU2_GetGyro(int32 nGyro)
{
  return((0.005 * nGyro)/65536.0);
}

float IMU2_GetAccel(int32 nAccel)
{
  return ((0.125 * nAccel)/65536.0);
}

