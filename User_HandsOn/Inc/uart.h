#ifndef UART_H
#define UART_H

#include "base_init.h"

void UART2_Configuration(void);
void calc_Task(void* pvParameters);
void send_hello_world(void* pvParameters);
void send_counting(void* pvParameters);
void output_data(uint8_t *buf, uint8_t len);

#endif /* UART_H */