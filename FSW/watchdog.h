#ifndef _WATCHDOG_H
#define _WATCHDOG_H

#include "includes.h"

void WD_DisableOBAutoKick(void);
void WD_DisableEPSAutoKick(void);
void WD_KickEPSWatchdog(void);
void WD_KickOBWatchdog(void);
void WD_CheckCommandTimeout(void);
void WD_ResetCommandTimeout(void);

#endif