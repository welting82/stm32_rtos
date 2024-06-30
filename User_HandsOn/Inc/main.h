#ifndef MAIN_H
#define MAIN_H

#include "base_init.h"
#include "uart.h"
#include "led.h"

#define STACK_USAGE_TASK_PRIORITY	( tskIDLE_PRIORITY )
#define UART_H_TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )
#define GYRO_TASK_PRIORITY	    	( tskIDLE_PRIORITY + 1UL )


#endif /* MAIN_H */