#ifndef __UART_H
#define __UART_H
#include "HAL_conf.h"
#include  "stdio.h"
#include "dtype.h"

void UartSendGroup(u8* buf, u16 len);
void uart_initwBaudRate(void);
void UartSendByte(u8 dat);
#endif


