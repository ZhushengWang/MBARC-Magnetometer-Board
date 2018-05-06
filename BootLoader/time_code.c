#include "includes.h"

volatile uint32 nTimeSeconds;
volatile uint32 nOneHzFlag = 0;
volatile uint32 n250msFlag = 0;

void set_time(uint32 nTimeCode)
{
  nTimeSeconds = nTimeCode;
}

uint32 get_time(void)
{
  return(nTimeSeconds);
}

void increment_time(void)
{
  nTimeSeconds++;
}

void SetOneHzFlag(void)
{
  nOneHzFlag = 1;
}

uint32 GetOneHzFlag(void)
{
  uint32 nFlagCopy = nOneHzFlag;
  
  if (nFlagCopy)
  {
    nOneHzFlag = 0;
  }
    
  return(nFlagCopy);
}

void Set250msFlag(void)
{
  n250msFlag = 1;
}

uint32 Get250msFlag(void)
{
  uint32 nFlagCopy = n250msFlag;
  
  if (nFlagCopy)
  {
    n250msFlag = 0;
  }
    
  return(nFlagCopy);
}