#include "includes.h"

extern CDH_IO_t *cdhio;

#define WD_MAX_TIMEOUT 28800   //8 hours = 28800

int nWD_CommandTimeout = WD_MAX_TIMEOUT;

void WD_DisableOBAutoKick(void)
{
  cdhio->CONTROL1 |= CTL1_CDH_OB_WD_KICK_DISABLE; //Disable auto-kick
}

void WD_DisableEPSAutoKick(void)
{
  cdhio->CONTROL1 |= CTL1_CDH_OFFBD_WD_KICK_DISABLE; //Disable auto-kick
}

void WD_KickEPSWatchdog(void)
{
  cdhio->CONTROL1 = cdhio->CONTROL1 ^ CTL1_CDH_OFFBD_WD_KICK; 
}

void WD_KickOBWatchdog(void)
{
  cdhio->CONTROL1 = cdhio->CONTROL1 ^ CTL1_CDH_ONBD_WD_KICK;  
}

void WD_ResetCommandTimeout(void)
{
  nWD_CommandTimeout = WD_MAX_TIMEOUT;
}

void WD_CheckCommandTimeout(void)
{
  nWD_CommandTimeout--;
  if (nWD_CommandTimeout <= 0)
  {
    print_uart_msg("%lu: Command Watchdog Timeout!  Power Cycle Enabled.\n",get_time());
    
    OP_SetMissionPhase(BL_FIRST_TURNON);
    OP_SetInitialWait(60);
    OP_SetEnableDeploy(1);
    
    disable_ints();
    
    WD_DisableEPSAutoKick();
    
    //Wait for reboot
    while (1)
    {
      ;
    }    
  }
}