#ifndef __UART_H
#define __UART_H
#include "HAL_conf.h"
#include  "stdio.h"
#include "dtype.h"
		   
#ifdef MM32W0NTB		//NTB 32Pin UART1
	#define UART_BLE UART1
	#define UART_BLE_TX_PIN GPIO_Pin_9
	#define UART_BLE_RX_PIN GPIO_Pin_10
	#define UART_BLE_TX_PINSRC GPIO_PinSource9
	#define UART_BLE_RX_PINSRC GPIO_PinSource10
#else 							//PFB 48Pin UART2
	#define UART_BLE UART2
	#define UART_BLE_TX_PIN GPIO_Pin_2
	#define UART_BLE_RX_PIN GPIO_Pin_3
	#define UART_BLE_TX_PINSRC GPIO_PinSource2
	#define UART_BLE_RX_PINSRC GPIO_PinSource3
#endif

void uart_initwBaudRate(void);
#endif


