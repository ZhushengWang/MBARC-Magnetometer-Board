/*
  All the C header files are included here
*/

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "MCF51AC256.h"

#include "cdh_consts.h"
#include "pe_vectors_MCF51ACx.h"

#include "main.h"
#include "console.h"
#include "power_control.h"
#include "adc.h"
#include "lithium.h"
#include "op_status.h"
#include "util.h"
#include "time_code.h"
#include "deploy.h"
#include "telecommand.h"
#include "mag.h"
#include "mtq.h"
#include "epson_imu2.h"
#include "dac_ctl.h"
#include "st_imu1.h"
#include "mram.h"
#include "fsw_ctl.h"
#include "fipex.h"
#include "fipex_script.h"
#include "fipex_data.h"
#include "adcs.h"
#include "telemetry.h"
#include "watchdog.h"

//Global constants
#define true  1
#define false 0

#define TEST_MODE 0
#define RADIO_MODE 1
#define MEMORY_MODE 2

#endif