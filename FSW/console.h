#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "includes.h"

void print_uart_msg(const char *template, ...);

int get_test_port_command(uint8 *pBuf);
int test_port_bytes_avail(void);
int test_port_go_boot_cmd(uint8 *pBuf, int nLen);
void SetMessageTXEnable(uint8 yVal);
void send_uart_str(char *pcStr);

#endif