#include "includes.h"

extern CDH_IO_t *cdhio;

void set_bit(volatile uint8 *pReg, uint8 yMask)
{
  *pReg = *pReg | yMask;
}

void reset_bit(volatile uint8 *pReg, uint8 yMask)
{
  *pReg = *pReg & (~yMask);
}

void set_reset_bit(volatile uint8 *pReg, uint8 yMask, int nState)
{
  if (nState)
  {
    set_bit(pReg,yMask);
  }
  else
  {
    reset_bit(pReg,yMask);
  }
}

int PWR_CheckBit(volatile uint8 *pReg, uint8 yMask)
{
  if (*pReg & yMask)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

void pwr_ctl(int nDevice, int nState)
{
  switch (nDevice)
  {
    case CDH_ADC:
      set_reset_bit(&(cdhio->PWRCTL),PWR_CDH_ADC,nState);
      break;
      
    case CDH_IMU1:
      set_reset_bit(&(cdhio->PWRCTL),PWR_IMU1,nState);
      break;
    
    /*case CDH_IMU2:
      set_reset_bit(&(cdhio->PWRCTL),PWR_IMU2,nState);
      break;*/
      
    case CDH_DAC:
      set_reset_bit(&(cdhio->PWRCTL),PWR_PPTDAC,nState);
      break;
      
    case RADIO:
      set_reset_bit(&(cdhio->PWRCTL),PWR_RADIO,nState);
      break;
      
    case FIPEX:
      set_reset_bit(&(cdhio->PWRCTL),PWR_FIPEX,nState);
      break;
      
    case SP1_ADC:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_SP1AMPADC,nState);
      break;
      
    case SP1_MAG:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_SP1MAG,nState);
      break;
      
    case SP2_ADC:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_SP2AMPADC,nState);
      break;
      
    case SP2_MAG:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_SP2MAG,nState);
      break;
      
    case SP3_ADC:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_SP3AMPADC,nState);
      break;
      
    case SP3_MAG:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_SP3MAG,nState);
      break;
      
    case BD4_ADC:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_BD4AMPADC,nState);
      break;
      
    case BD4_MAG:
      set_reset_bit(&(cdhio->PWRCTL2),PWR2_BD4MAG,nState);
      break;
      
    case EPS_ADC:
      set_reset_bit(&(cdhio->PWRCTL),PWR_EPS_ADC,nState);
      break;
      
    default:
      break;
  }
}

void PWR_AllDevicesOff(void)
{
  pwr_ctl(CDH_ADC,PWR_OFF);
  pwr_ctl(CDH_IMU1,PWR_OFF);
  //pwr_ctl(CDH_IMU2,PWR_OFF);  
  pwr_ctl(CDH_DAC,PWR_OFF);
  pwr_ctl(RADIO,PWR_OFF);
  pwr_ctl(SP1_ADC,PWR_OFF);
  pwr_ctl(SP1_MAG,PWR_OFF);  
  pwr_ctl(SP2_ADC,PWR_OFF);
  pwr_ctl(SP2_MAG,PWR_OFF);
  pwr_ctl(SP3_ADC,PWR_OFF);
  pwr_ctl(SP3_MAG,PWR_OFF);  
  pwr_ctl(BD4_ADC,PWR_OFF);
  pwr_ctl(BD4_MAG,PWR_OFF);
  pwr_ctl(EPS_ADC,PWR_OFF);
  pwr_ctl(FIPEX,PWR_OFF);   
}

void PWR_AllADCsOn(void)
{
   pwr_ctl(CDH_ADC,PWR_ON);
   pwr_ctl(SP1_ADC,PWR_ON);
   pwr_ctl(SP2_ADC,PWR_ON);
   pwr_ctl(SP3_ADC,PWR_ON);
   pwr_ctl(BD4_ADC,PWR_ON);
   pwr_ctl(EPS_ADC,PWR_ON);
}

void PWR_AllMagsOn(void)
{
  pwr_ctl(SP1_MAG,PWR_ON);  
  pwr_ctl(SP2_MAG,PWR_ON);
  pwr_ctl(SP3_MAG,PWR_ON);
  pwr_ctl(BD4_MAG,PWR_ON);
}

void PWR_IMU1On(uint8 yOn)
{
  pwr_ctl(CDH_IMU1,yOn);
}

/*void PWR_IMU2On(uint8 yOn)
{
  pwr_ctl(CDH_IMU2,yOn);  
}*/

void PWR_RadioOn(uint8 yOn)
{
  pwr_ctl(RADIO,yOn);
}

void PWR_FIPEXOn(uint8 yOn)
{
  pwr_ctl(FIPEX,yOn);
}

int PWR_GetStatus(uint8 yDev)
{
int nRC = -1;

  switch (yDev)
  {
    case CDH_ADC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_CDH_ADC);
      break;
      
    case CDH_IMU1:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_IMU1);
      break;
    
    /*case CDH_IMU2:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_IMU2);
      break;*/
      
    case CDH_DAC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_PPTDAC);
      break;
      
    case RADIO:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_RADIO);
      break;
      
    case FIPEX:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_FIPEX);
      break;
      
    case SP1_ADC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_SP1AMPADC);
      break;
      
    case SP1_MAG:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_SP1MAG);
      break;
      
    case SP2_ADC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_SP2AMPADC);
      break;
      
    case SP2_MAG:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_SP2MAG);
      break;
      
    case SP3_ADC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_SP3AMPADC);
      break;
      
    case SP3_MAG:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_SP3MAG);
      break;
      
    case BD4_ADC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_BD4AMPADC);
      break;
      
    case BD4_MAG:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL2),PWR2_BD4MAG);
      break;
      
    case EPS_ADC:
      nRC = PWR_CheckBit(&(cdhio->PWRCTL),PWR_EPS_ADC);
      break;
      
    default:
      nRC = -1;
      break;
  }
  
  return(nRC);
}

void PWR_PrintStatus(void)
{
  print_uart_msg("Power Status:\n");
  print_uart_msg("Radio:        %d\n",PWR_GetStatus(RADIO));
  print_uart_msg("FIPEX:        %d\n",PWR_GetStatus(FIPEX));
  print_uart_msg("IMU1 (ST):    %d\n",PWR_GetStatus(CDH_IMU1));
  //print_uart_msg("IMU2 (Epson): %d\n",PWR_GetStatus(CDH_IMU2));
  print_uart_msg("CDH ADC:      %d\n",PWR_GetStatus(CDH_ADC));
  print_uart_msg("CDH DAC:      %d\n",PWR_GetStatus(CDH_DAC));
  print_uart_msg("SP1 ADC:      %d\n",PWR_GetStatus(SP1_ADC));
  print_uart_msg("SP1 MAG:      %d\n",PWR_GetStatus(SP1_MAG));
  print_uart_msg("SP2 ADC:      %d\n",PWR_GetStatus(SP2_ADC));
  print_uart_msg("SP2 MAG:      %d\n",PWR_GetStatus(SP2_MAG));
  print_uart_msg("SP3 ADC:      %d\n",PWR_GetStatus(SP3_ADC));
  print_uart_msg("SP3 MAG:      %d\n",PWR_GetStatus(SP3_MAG));
  print_uart_msg("BD4 ADC:      %d\n",PWR_GetStatus(BD4_ADC));
  print_uart_msg("BD4 MAG/TP:   %d\n",PWR_GetStatus(BD4_MAG));
}


