#include "includes.h"

extern CDH_IO_t *cdhio;

#define MBARC_MAG_DATA_SIZE 28
#define MBARC_MAG_PKTFIFO_SIZE 1400

int nMbarcMagStep = 0;
int nMbarcMagPktFIFOReadPtr = 0;
int nMbarcMagPktFIFOWritePtr= 0;
int nMbarcMagPktFIFOPeekPtr = 0;
uint8 MbarcMagPktFIFO[MBARC_MAG_PKTFIFO_SIZE];
MBARC_MAG_DATA_t MbarcMagData;

void Mbarc_Mag_AssertReset(void)
{
  cdhio->CONTROL2 &= ~CTL2_CDH_MBARC_MAG_NRESET;  //Assert reset for Mbarc Mag
}

void Mbarc_Mag_DeassertReset(void)
{
  cdhio->CONTROL2 |= CTL2_CDH_MBARC_MAG_NRESET;  //De-assert reset for Mbarc Mag
}

void Mbarc_Mag_SetCycleCount(void)
{
  int i;
  cdhio->MBARC_MAG_TX = 0x01;
  cdhio->MBARC_MAG_TX = 0x03;
  cdhio->MBARC_MAG_TX = 0x20;
  for(i=3;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_ReadCycleCount(void)
{
  int i;
  cdhio->MBARC_MAG_TX = 0x02;
  for(i=1;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_StartMeasurement(uint8 freqSet)
{
  int i;
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
  int i;
  cdhio->MBARC_MAG_TX = 0x05;
  cdhio->MBARC_MAG_TX = retrieveMode;
  for(i=2;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_Stop(void)
{
  int i;
  cdhio->MBARC_MAG_TX = 0x06;
  for(i=1;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

void Mbarc_Mag_Reset(void)
{
  int i;
  cdhio->MBARC_MAG_TX = 0x07;
  for(i=1;i<=8;i++)
  {
    cdhio->MBARC_MAG_TX = 0x00;
  }
}

int Mbarc_Mag_DataAvail(void)
{
  if (!(cdhio->STATUS1 & STS1_MBARC_MAG_RX_EMPTY))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void Mbarc_Mag_EmptyFIFO(void) 
{
  while (Mbarc_Mag_DataAvail())
  {
    // If cdhio->MBARC_MAG_RX = 0，the remaining FIFO data will be transmitted
    cdhio->MBARC_MAG_RX = 0;
  }
}

int Mbarc_Mag_WaitForData(void) // Wait for data to enter FIFO
{
  int nLoopCount = 0;
  
  while ((!Mbarc_Mag_DataAvail()) && (nLoopCount < 100))
  {
    nLoopCount++;
  }
  
  if (nLoopCount >= 100)
  {
    return(-1);  // Timeout
  }
  else
  {
    return(0);
  }
}

int Mbarc_Mag_ReadCycleCountData(uint8 *mmBuf) // mmBuf: Mbarc Mag Buffer
{
  int i;
  int nRC = 0;
  
  if (Mbarc_Mag_DataAvail())
  {
    for(i = 0; i < 2; i++)
    {
      if (Mbarc_Mag_WaitForData() == 0)
      {
        cdhio->MBARC_MAG_RX = 0;
        mmBuf[i] = cdhio->MBARC_MAG_TX;
      }
      else
      {
        print_uart_msg("MBARC MAG: Cycle Count Read Timeout.\n");
        nRC = -1;
        break;         
      }     
    }
  }
  else
  {
    nRC = -1;
  }
  
  return nRC; 
}

void Mbarc_Mag_Enqueue(uint8 mmByte)
{
  MbarcMagPktFIFO[nMbarcMagPktFIFOWritePtr++] = mmByte;
  if (nMbarcMagPktFIFOWritePtr >= MBARC_MAG_PKTFIFO_SIZE)
  {
    nMbarcMagPktFIFOWritePtr = 0;
  }
}

uint8 Mbarc_Mag_Dequeue(void)
{
  uint8 mmByte = MbarcMagPktFIFO[nMbarcMagPktFIFOReadPtr++];
  if (nMbarcMagPktFIFOReadPtr >= MBARC_MAG_PKTFIFO_SIZE)
  {
    nMbarcMagPktFIFOReadPtr = 0;
  }
  nMbarcMagPktFIFOPeekPtr = nMbarcMagPktFIFOReadPtr;
  return(mmByte);
}

uint8 Mbarc_Mag_Peek(void)
{
  return(nMbarcMagPktFIFOPeekPtr);
}

int Mbarc_Mag_BytesInQueue(void)
{
  int nCount = nMbarcMagPktFIFOWritePtr - nMbarcMagPktFIFOReadPtr;  
  if (nCount < 0)
  {
    nCount += MBARC_MAG_PKTFIFO_SIZE;
  }
  return(nCount);
}

int Mbarc_Mag_ReadMeasurementData(void)
{
  int i; 
  int nRC = 0; 
  uint8 Buf[MBARC_MAG_DATA_SIZE];
  uint8 mmByte;
  
  // When data is available, read the data from FIFO and add it to the queue
  while (Mbarc_Mag_DataAvail())
  {
    if (Mbarc_Mag_WaitForData() == 0)
    {
      cdhio->MBARC_MAG_RX = 0;
      mmByte = cdhio->MBARC_MAG_TX;
      Mbarc_Mag_Enqueue(mmByte);
    }
    else
    {
      print_uart_msg("MBARC MAG: Measurement Data Read Timeout.\n");
      nRC = -1;
      break; 
    }
  }

  // When the queue is not empty, read the data from queue and every 28 bytes form a complete sequence
  while ( (Mbarc_Mag_BytesInQueue() > 0) && (nRC == 0) )
  {
    i = Mbarc_Mag_Peek() % MBARC_MAG_DATA_SIZE;
    Buf[i] = Mbarc_Mag_Dequeue(); 
    if ( i == (MBARC_MAG_DATA_SIZE-1) )
    {
      memcpy(&MbarcMagData,Buf,MBARC_MAG_DATA_SIZE);
    }   
  }

  return nRC; 
}

void Mbarc_Mag_Init(void)
{
  nMbarcMagStep = 0;
  Mbarc_Mag_EmptyFIFO(); //Make sure FIFO is empty
  memset(&MbarcMagData,0,MBARC_MAG_DATA_SIZE);
}

void Mbarc_Mag_Dotasks(void)
{
  uint8 Buf[2];

  switch (nMbarcMagStep)
  {
    case 0:
      Mbarc_Mag_SetCycleCount();
      nMbarcMagStep = 1;      
      break;

    case 1:
      Mbarc_Mag_ReadCycleCount();
      nMbarcMagStep = 2;
      break;

    case 2:
      if (Mbarc_Mag_ReadCycleCountData(Buf) >= 0)
      {
        if ( (Buf[0] == 0x03) && (Buf[1] == 0x20) )
        {
          nMbarcMagStep = 3;
          print_uart_msg("MBARC MAG: Successful Cycle Count Set.\n");
        }
        else
        {
          Mbarc_Mag_Init();
          print_uart_msg("MBARC MAG: Bad Ready Response.\n");
        }
      }
      else
      {
        Mbarc_Mag_Init();
        print_uart_msg("MBARC MAG: Ready Read Timeout.\n");
      }
      break;

    case 3:
      Mbarc_Mag_RetrieveData(0x01);
      nMbarcMagStep = 4;
      break;

    case 4:
      Mbarc_Mag_StartMeasurement(0x1E);
      nMbarcMagStep = 5;
      break;

    case 5:
      if (Mbarc_Mag_ReadMeasurementData() >= 0)
      {
        nMbarcMagStep = 5;
      }
      else
      {
        Mbarc_Mag_Init();
        print_uart_msg("MBARC MAG: Error Reading Measurement data\n");
      }
      break;

    // For the new version, it should be something like the following
    // case 3:
    //   Mbarc_Mag_StartMeasurement(0x1E);
    //   nMbarcMagStep = 4;
    //   break;

    // case 4:
    //   Mbarc_Mag_RetrieveData(0x00);
    //   nMbarcMagStep = 5;
    //   break;

    // case 5:
    // if (Mbarc_Mag_ReadMeasurementData() >= 0)
    // {
    //   nMbarcMagStep = 3;
    // }
    
    default:
      Mbarc_Mag_Init();
      break;
  }
}

void Mbarc_Mag_GetLastData(MBARC_MAG_DATA_t *mmData) // mmData: Mbarc Mag Data
{
  memcpy(mmData,&MbarcMagData,MBARC_MAG_DATA_SIZE);
}