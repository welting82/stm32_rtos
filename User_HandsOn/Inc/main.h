#ifndef MAIN_H
#define MAIN_H

#include "base_init.h"
#include "uart.h"
#include "led.h"
#include "i2c.h"

#define UART_H_TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )
#define UART_CNT_TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )
#define I2C_TASK_PRIORITY		    ( tskIDLE_PRIORITY + 2UL )


#endif /* MAIN_H */