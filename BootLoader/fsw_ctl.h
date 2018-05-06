#ifndef _FSW_CTL_H
#define _FSW_CTL_H

#include "includes.h"

int FSW_VerifyCode(uint8 *pBuf);
void FSW_CopyCode(uint8 *pBuf);
void FSW_Boot(uint8 *pBuf);                  
void FSW_BootPartition(uint8 yPartition);

#endif