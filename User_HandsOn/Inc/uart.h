#ifndef UART_H
#define UART_H

#include "base_init.h"

void UART2_Configuration(void);
void send_hello_world(void* pvParameters);
void Show_stack_usage(void* pvParameters);
void uart_tx_task();
void uart_rx_task();

#endif /* UART_H */