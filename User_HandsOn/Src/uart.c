#include "uart.h"

extern xSemaphoreHandle xSemaphore;
UART_HandleTypeDef huart2; /*Create UART_InitTypeDef struct instance */
char RX_Buffer; //"Interrupt inputt"
char rec_data[100]; //"receice data"
char TX_Buffer[50] = "Hello World\r\n";
char tmp_Buffer[20] = "Loop Cnt: ";
uint8_t Uart2_Rx_Cnt = 0;
uint8_t loop_cnt = 0;

void UART2_Configuration(void)
{
	//UART Configuration
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 921600;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	HAL_UART_Init(&huart2);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if((Uart2_Rx_Cnt == sizeof(rec_data)-2) || (RX_Buffer == '\r') || (RX_Buffer == '\n'))
	{
		rec_data[Uart2_Rx_Cnt] = '\r';
		rec_data[Uart2_Rx_Cnt+1] = '\n';

		HAL_UART_Transmit(&huart2, (uint8_t *)&rec_data, sizeof(rec_data),0xFFFF);
		if(Uart2_Rx_Cnt == sizeof(rec_data)-2) HAL_UART_Transmit(&huart2, (uint8_t *)"overflow\r\n", 10,0xFFFF);
		memset(rec_data,0,sizeof(rec_data));
		Uart2_Rx_Cnt = 0;
	}
	else
	{
		rec_data[Uart2_Rx_Cnt++] = RX_Buffer;
	}
	HAL_UART_Receive_IT(huart, (uint8_t*)&RX_Buffer, 1);
}

void calc_Task(void* pvParameters)
{
	int idx = 10;
    while (1) {
		if( xSemaphore != NULL )
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				if(loop_cnt > 99) loop_cnt = 0;
				tmp_Buffer[idx] = loop_cnt/10 + 48;
				tmp_Buffer[idx + 1] = loop_cnt%10 + 48;
				tmp_Buffer[idx + 2] = '\r';
				tmp_Buffer[idx + 3] = '\n';
				tmp_Buffer[idx + 4] = '\0';
				loop_cnt++;
				xSemaphoreGive( xSemaphore );
			}
		vTaskDelay(500);
    }
}

void send_hello_world(void* pvParameters)
{
    while (1) {
		if( xSemaphore != NULL )
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
        		HAL_UART_Transmit(&huart2, (uint8_t*)&TX_Buffer, sizeof(TX_Buffer),50);
				xSemaphoreGive( xSemaphore );
			}
        vTaskDelay(1000);
    }
}

void send_counting(void* pvParameters)
{
    while (1) {
		if( xSemaphore != NULL )
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				HAL_UART_Transmit(&huart2, (uint8_t*)&tmp_Buffer, sizeof(tmp_Buffer),50);
				xSemaphoreGive( xSemaphore );
			}
        vTaskDelay(500);
    }
}