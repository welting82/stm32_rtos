#ifndef BASE_INIT_H
#define BASE_INIT_H

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

void Clock_Configuration(void);
void peripheral_init();
void Delay_ms(volatile int time_ms);

#endif /* BASE_INIT_H */