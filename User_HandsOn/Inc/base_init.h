#ifndef BASE_INIT_H
#define BASE_INIT_H

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void Clock_Configuration(void);
void peripheral_init();
void Delay_ms(volatile int time_ms);

#endif /* BASE_INIT_H */