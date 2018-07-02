/*#include "includes.h"

extern CDH_IO_t *cdhio;

uint16 wDivisor;

void MTQ_SetFreq(int nFreq)
{
  wDivisor = (uint16)(25e6/nFreq) & 0xFFFF;
  
  cdhio->PWM_PER_L = wDivisor & 0xFF;
  cdhio->PWM_PER_H = (wDivisor >> 8) & 0xFF;
}

void MTQ_EnableX(uint8 yEnable)
{
  if (yEnable == 1)
  {
    cdhio->PWM_CTL_REG |= PWM_X_ENABLE;
  }
  else
  {
    cdhio->PWM_CTL_REG &= ~PWM_X_ENABLE;
  }
}

void MTQ_EnableY(uint8 yEnable)
{
  if (yEnable == 1)
  {
    cdhio->PWM_CTL_REG |= PWM_Y_ENABLE;
  }
  else
  {
    cdhio->PWM_CTL_REG &= ~PWM_Y_ENABLE;
  }
}

void MTQ_EnableZ(uint8 yEnable)
{
  if (yEnable == 1)
  {
    cdhio->PWM_CTL_REG |= PWM_Z_ENABLE;
  }
  else
  {
    cdhio->PWM_CTL_REG &= ~PWM_Z_ENABLE;
  }
}

void MTQ_SetSignX(uint8 yPositive)
{
  if (yPositive == 1)
  {
    cdhio->PWM_CTL_REG |= PWM_X_PLUS;
  }
  else
  {
    cdhio->PWM_CTL_REG &= ~PWM_X_PLUS;
  }
}

void MTQ_SetSignY(uint8 yPositive)
{
  if (yPositive == 1)
  {
    cdhio->PWM_CTL_REG |= PWM_Y_PLUS;
  }
  else
  {
    cdhio->PWM_CTL_REG &= ~PWM_Y_PLUS;
  }
}

void MTQ_SetSignZ(uint8 yPositive)
{
  if (yPositive == 1)
  {
    cdhio->PWM_CTL_REG |= PWM_Z_PLUS;
  }
  else
  {
    cdhio->PWM_CTL_REG &= ~PWM_Z_PLUS;
  }
}

//nValue = -1024 to +1024
void MTQ_SetXPercent(int nValue)
{
  uint16 wPulse;
  int nVal;
  
  if (nValue == 0)
  {
    MTQ_EnableX(0);
  }
  else
  {
    MTQ_EnableX(1);
  }
  
  if (nValue >= 0)
  {
    nVal = 1024-nValue;
    MTQ_SetSignX(1);
  }
  else
  {
    nVal = 1024+nValue;
    MTQ_SetSignX(0);
  }
  
  wPulse = (nVal * wDivisor) >> 10;
  
  cdhio->PWM_PULSE_XL = wPulse & 0xFF;
  cdhio->PWM_PULSE_XH = (wPulse >> 8) & 0xFF;
}

//nValue = 0 to 1024
void MTQ_SetYPercent(int nValue)
{
  uint16 wPulse;
  int nVal;
 
  if (nValue == 0)
  {
    MTQ_EnableY(0);
  }
  else
  {
    MTQ_EnableY(1);
  } 
  
  if (nValue >= 0)
  {
    nVal = 1024-nValue;
    MTQ_SetSignY(1);
  }
  else
  {
    nVal = 1024+nValue;
    MTQ_SetSignY(0);
  }
  
  wPulse = (nVal * wDivisor) >> 10;
  
  cdhio->PWM_PULSE_YL = wPulse & 0xFF;
  cdhio->PWM_PULSE_YH = (wPulse >> 8) & 0xFF;
}
  
//nValue = 0 to 1024
void MTQ_SetZPercent(int nValue)
{
  uint16 wPulse;
  int nVal;

  if (nValue == 0)
  {
    MTQ_EnableZ(0);
  }
  else
  {
    MTQ_EnableZ(1);
  }
  
  if (nValue >= 0)
  {
    nVal = 1024-nValue;
    MTQ_SetSignZ(1);
  }
  else
  {
    nVal = 1024+nValue;
    MTQ_SetSignZ(0);
  }
  
  wPulse = (nVal * wDivisor) >> 10;
  
  cdhio->PWM_PULSE_ZL = wPulse & 0xFF;
  cdhio->PWM_PULSE_ZH = (wPulse >> 8) & 0xFF;
}*/
  
  