#include "includes.h"

extern CDH_IO_t *cdhio;

void DAC_SetDACRaw(uint16 wValue)
{
  cdhio->DAC12_L = wValue & 0xFF;  //Set L first
  cdhio->DAC12_H = (wValue >> 8) & 0xFF;
  
  print_uart_msg("DAC:   Setting DAC to %04X\n",wValue);
}

void DAC_SetDACVolts(float fVolts)
{
  uint16 wValue;
  
  wValue = (uint16)(fVolts * 4096/3.3);
  
  DAC_SetDACRaw(wValue);
}


