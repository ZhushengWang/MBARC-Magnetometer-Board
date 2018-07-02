#ifndef _TIME_CODE_H
#define _TIME_CODE_H

#include "includes.h"

void set_time(uint32 time_code);
uint32 get_time(void);
void increment_time(void);
void SetOneHzFlag(void);
uint32 GetOneHzFlag(void);
void Set250msFlag(void);
uint32 Get250msFlag(void);

#endif