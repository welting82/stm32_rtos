#ifndef MAIN_H
#define MAIN_H

#include "base_init.h"
#include "uart.h"
#include "led.h"

#define BASIC_TASK_PRIORITY	        ( tskIDLE_PRIORITY )
#define UART_TX_TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )
#define UART_RX_TASK_PRIORITY		( UART_TX_TASK_PRIORITY + 1UL )


#endif /* MAIN_H */