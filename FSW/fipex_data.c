#include "includes.h"

#define FIP_DATAFIFO_SIZE 512*1024

static uint32 FIPData_RetrievalPtr1 = 0;
static uint32 FIPData_RetrievalPtr2 = 0;

static void FIPData_Enqueue1(uint8 *pPkt, int nLen, uint8 yType);
static void FIPData_Enqueue2(uint8 *pPkt, int nLen, uint8 yType);
static int FIPData_Dequeue1(uint8 *pPkt, int *nLen);
static int FIPData_Dequeue2(uint8 *pPkt, int *nLen);
static int FIPData_BytesInQueue1(void);
static int FIPData_BytesInQueue2(void);
static int FIPData_ReadNoDequeue1(uint8 *pPkt, int *nLen, uint32 unRdPtrIn, uint8 *pyPktType);
static int FIPData_ReadNoDequeue2(uint8 *pPkt, int *nLen, uint32 unRdPtrIn, uint8 *pyPktType);

static void FIPData_Enqueue1(uint8 *pPkt, int nLen, uint8 yType)
{
uint32 unWPtr = OP_GetFIPM1WPtr();
int nPktLen = nLen + 2;
uint32 unWriteEnd = (unWPtr + nPktLen) & 0x0007FFFF; //Limit to 19 bits
uint8 ayPktHdr[2];

  while ((FIPData_BytesInQueue1() + nPktLen) >= FIP_DATAFIFO_SIZE)
  {
    FIPData_Dequeue1(NULL,&nPktLen);  //Dequeue and throw away oldest data
  }
  
  ayPktHdr[0] = yType;
  ayPktHdr[1] = (nPktLen-2) & 0xFF;
  
  MRAM_WriteData(0,unWPtr,ayPktHdr,2);  //Write Header
  MRAM_WriteData(0,unWPtr+2,pPkt,nLen);
  
  OP_SetFIPM1WPtr(unWriteEnd);
  
  if (yType == FIP_SDP_PKTTYPE)
  {
    OP_IncrementM1SDPCount();
  }
  else
  {
    OP_IncrementM1HKCount();
  }
}

static void FIPData_Enqueue2(uint8 *pPkt, int nLen, uint8 yType)
{
uint32 unWPtr = OP_GetFIPM2WPtr();
int nPktLen = nLen + 2;
uint32 unWriteEnd = (unWPtr + nPktLen) & 0x0007FFFF; //Limit to 19 bits
uint8 ayPktHdr[2];

  while ((FIPData_BytesInQueue2() + nPktLen) >= FIP_DATAFIFO_SIZE)
  {
    FIPData_Dequeue2(NULL,&nPktLen);  //Dequeue and throw away oldest data
  }
  
  ayPktHdr[0] = yType;
  ayPktHdr[1] = (nPktLen-2) & 0xFF;
  
  MRAM_WriteData(1,unWPtr,ayPktHdr,2);  //Write Header
  MRAM_WriteData(1,unWPtr+2,pPkt,nLen);
  
  OP_SetFIPM2WPtr(unWriteEnd);
  
  if (yType == FIP_SDP_PKTTYPE)
  {
    OP_IncrementM2SDPCount();
  }
  else
  {
    OP_IncrementM2HKCount();
  }
}

static int FIPData_Dequeue1(uint8 *pPkt, int *nLen)
{
uint32 unWPtr = OP_GetFIPM1WPtr();
uint32 unRPtr = OP_GetFIPM1RPtr();
uint8 ayHdr[2];
uint8 yPktLen;

  if (unWPtr == unRPtr)  //Queue is empty
  {
    *nLen = 0;
    return 0;
  }
  else
  {
    MRAM_ReadData(0,unRPtr,ayHdr,2);  //Get ID + Len
   
    yPktLen = ayHdr[1];
     
    if (pPkt != NULL)
    {
      MRAM_ReadData(0,unRPtr+2,pPkt,yPktLen);
    }

    *nLen = yPktLen;
    unRPtr = (unRPtr + yPktLen + 2) & 0x0007FFFF;
      
    OP_SetFIPM1RPtr(unRPtr);
    
    if (ayHdr[0] == FIP_SDP_PKTTYPE)
    {
      OP_DecrementM1SDPCount();
    }
    else
    {
      OP_DecrementM1HKCount();
    }
      
    return(ayHdr[0]);
  }
}

static int FIPData_Dequeue2(uint8 *pPkt, int *nLen)
{
uint32 unWPtr = OP_GetFIPM2WPtr();
uint32 unRPtr = OP_GetFIPM2RPtr();
uint8 ayHdr[2];
uint8 yPktLen;

  if (unWPtr == unRPtr)
  {
    *nLen = 0;
    return 0;
  }
  else
  {
    MRAM_ReadData(1,unRPtr,ayHdr,2);  //Get 0xEE sync + Len
    
    yPktLen = ayHdr[1];
     
    if (pPkt != NULL)
    {
      MRAM_ReadData(1,unRPtr+2,pPkt,yPktLen);
    }

    *nLen = yPktLen;
    unRPtr = (unRPtr + yPktLen + 2) & 0x0007FFFF;
      
    OP_SetFIPM2RPtr(unRPtr);
     
    if (ayHdr[0] == FIP_SDP_PKTTYPE)
    {
      OP_DecrementM2SDPCount();
    }
    else
    {
      OP_DecrementM2HKCount();
    }
     
    return(ayHdr[0]);
  }
}

static int FIPData_BytesInQueue1(void)
{
uint32 unWPtr = OP_GetFIPM1WPtr();
uint32 unRPtr = OP_GetFIPM1RPtr();
int    nCount = unWPtr - unRPtr;
  
  if (nCount < 0)
  {
    nCount+=FIP_DATAFIFO_SIZE;
  }
  return(nCount);
}

static int FIPData_BytesInQueue2(void)
{
uint32 unWPtr = OP_GetFIPM2WPtr();
uint32 unRPtr = OP_GetFIPM2RPtr();
int    nCount = unWPtr - unRPtr;
  
  if (nCount < 0)
  {
    nCount+=FIP_DATAFIFO_SIZE;
  }
  return(nCount);
}

static uint32 FIPGet_ReadPtr1(void)
{
  return(OP_GetFIPM1RPtr());
}

static uint32 FIPGet_ReadPtr2(void)
{
  return(OP_GetFIPM2RPtr());
}

static int FIPData_ReadNoDequeue1(uint8 *pPkt, int *nLen, uint32 unRdPtrIn, uint8 *pyPktType)
{
uint32 unWPtr = OP_GetFIPM1WPtr();
uint32 unRPtr = unRdPtrIn;
uint8 ayHdr[2];
uint8 yPktLen;

  if (unWPtr == unRPtr)
  {
    *nLen = 0;
    return unRPtr;
  }
  else
  {
    MRAM_ReadData(0,unRPtr,ayHdr,2);  //Get  sync + Len
    
    yPktLen = ayHdr[1];
     
    if (pPkt != NULL)
    {
      MRAM_ReadData(0,unRPtr+2,pPkt,yPktLen);
    }

    *nLen = yPktLen;
    unRPtr = (unRPtr + yPktLen + 2) & 0x0007FFFF;
    *pyPktType = ayHdr[0];
     
    return unRPtr;
  }
}

static int FIPData_ReadNoDequeue2(uint8 *pPkt, int *nLen, uint32 unRdPtrIn, uint8 *pyPktType)
{
uint32 unWPtr = OP_GetFIPM2WPtr();
uint32 unRPtr = unRdPtrIn;
uint8 ayHdr[2];
uint8 yPktLen;

  if (unWPtr == unRPtr)
  {
    *nLen = 0;
    return unRPtr;
  }
  else
  {
    MRAM_ReadData(1,unRPtr,ayHdr,2);  //Get 0xEE sync + Len
    
    yPktLen = ayHdr[1];
     
    if (pPkt != NULL)
    {
      MRAM_ReadData(1,unRPtr+2,pPkt,yPktLen);
    }

    *nLen = yPktLen;
    unRPtr = (unRPtr + yPktLen + 2) & 0x0007FFFF;
    *pyPktType = ayHdr[0];
     
    return unRPtr;
  }
}

void FIPData_StoreData(uint8 *pData, int unLen, uint8 yDataType)
{
  uint8 ayPkt[256];
  ATTITUDE_STRUCT_t attData;

  ADCS_GetLastAttitude(&attData);
  
  memcpy(ayPkt,&attData,sizeof(ATTITUDE_STRUCT_t));  //Attitude Data first
  memcpy(ayPkt+sizeof(ATTITUDE_STRUCT_t),pData,unLen); //Then Pkt
  
  
  FIPData_Enqueue1(ayPkt,unLen+sizeof(ATTITUDE_STRUCT_t),yDataType);
  FIPData_Enqueue2(ayPkt,unLen+sizeof(ATTITUDE_STRUCT_t),yDataType);
}

void FIPData_InitRetrieval(void)
{
  FIPData_RetrievalPtr1 = OP_GetFIPM1RPtr();
  FIPData_RetrievalPtr2 = OP_GetFIPM2RPtr();
}

void FIPData_RetrieveData(uint8 *pData, int *punLen, uint8 yMem, uint8 *pPktType)
{
uint32 unRdPtr;

  if (yMem == 1) //Memory 1
  {
    unRdPtr = FIPData_RetrievalPtr1;
    FIPData_RetrievalPtr1 = FIPData_ReadNoDequeue1(pData, punLen, unRdPtr, pPktType);
  }
  else  //Memory 2 (yChip == 2)
  {
    unRdPtr = FIPData_RetrievalPtr2;
    FIPData_RetrievalPtr2 = FIPData_ReadNoDequeue2(pData, punLen, unRdPtr, pPktType);
  }
}

void FIPData_EmptyFIFO(uint8 yMem)
{
  if (yMem == 1)
  {
    OP_SetFIPM1WPtr(FIP_DATAFIFO_SIZE-256);  //Near max for testing
    OP_SetFIPM1RPtr(FIP_DATAFIFO_SIZE-256);
    OP_SetFIPM1SDPCount(0);
    OP_SetFIPM1HKCount(0);
  }
  else
  {
    OP_SetFIPM2WPtr(FIP_DATAFIFO_SIZE-256);
    OP_SetFIPM2RPtr(FIP_DATAFIFO_SIZE-256);
    OP_SetFIPM2SDPCount(0);
    OP_SetFIPM2HKCount(0);
  }
}

void FIPData_EraseData(uint8 yMem, uint32 unEndTime)
{
uint8 ayPkt[256];
int   nLen;
uint8 yPktType;
uint32 unRdPtr;
uint32 unPktTime;
int nCount = 0;
  
  if (unEndTime == 0)
  {
    FIPData_EmptyFIFO(yMem);
  }
  else
  {
    if (yMem == 1) //Memory 1
    {
      do
      {
        unRdPtr = OP_GetFIPM1RPtr();
        FIPData_ReadNoDequeue1(ayPkt, &nLen, unRdPtr, &yPktType);
        unPktTime = makeui32_be(ayPkt,0);
        
        if (unPktTime <= unEndTime)
        {
          FIPData_Dequeue1(NULL,&nLen);
          nCount++;
        }
      } while ((unPktTime <= unEndTime) && (FIPData_BytesInQueue1() > 0));
      
      print_uart_msg("Deleted %d packets from FIPEX Memory 1. (%lu)\n",nCount,get_time());
    }
    else  //Memory 2 (yChip == 2)
    {
      do
      {
        unRdPtr = OP_GetFIPM2RPtr();
        FIPData_ReadNoDequeue2(ayPkt, &nLen, unRdPtr, &yPktType);
        unPktTime = makeui32_be(ayPkt,0);
        
        if (unPktTime <= unEndTime)
        {
          FIPData_Dequeue2(NULL,&nLen);
          nCount++;
        }
      } while ((unPktTime <= unEndTime) && (FIPData_BytesInQueue2() > 0));
      
      print_uart_msg("Deleted %d packets from FIPEX Memory 2. (%lu)\n",nCount,get_time());
    }
  }
}
