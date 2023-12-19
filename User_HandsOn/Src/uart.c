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

		HAL_UART_Transmit(&huart2, (uint8_t *)&rec_data, sizeof(rec_data),HAL_MAX_DELAY);
		if(Uart2_Rx_Cnt == sizeof(rec_data)-2) HAL_UART_Transmit(&huart2, (uint8_t *)"overflow\r\n", 10,HAL_MAX_DELAY);
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
        		HAL_UART_Transmit(&huart2, (uint8_t*)&TX_Buffer, sizeof(TX_Buffer),HAL_MAX_DELAY);
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
				HAL_UART_Transmit(&huart2, (uint8_t*)&tmp_Buffer, sizeof(tmp_Buffer),HAL_MAX_DELAY);
				xSemaphoreGive( xSemaphore );
			}
        vTaskDelay(500);
    }
}

void output_data(uint8_t *buf, uint8_t len)
{
	memset(rec_data,0,sizeof(rec_data));
	memcpy(rec_data,buf,len);
	while( xSemaphore != NULL )
	{
		if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE && len > 0)
		{
			rec_data[len] = '\r';
			rec_data[len+1] = '\n';
			HAL_UART_Transmit(&huart2, (uint8_t*)&rec_data, len + 2,HAL_MAX_DELAY);
			xSemaphoreGive( xSemaphore );
		}
		break;
	}
	return;
}

void outputError(uint8_t CRLF, const char *format, va_list ap)
{
	#define BUF_SIZE 100
	char buf[BUF_SIZE];
	int32_t nb;

	while( xSemaphore != NULL )
	{
		if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE)
		{
			nb = (int32_t)vsnprintf(buf, BUF_SIZE, format, ap);
			if (nb > 0)
			{
				uint32_t nb_size = (uint32_t)nb;
				if(CRLF == 1U)
				{
					if (nb >= 2 && ((buf[nb-2] == '\r' && buf[nb-1] == '\n') || (buf[nb-2] == '\n' && buf[nb-1] == '\r')))
					{
						// Check if the string ends with "\r\n" or "\n\r"
						// Do nothing since \r\n already within the ends of buffer
					}
					else
					{
						// Append "\r\n" to the end of the buffer
						if (nb < BUF_SIZE - 2)
						{
							buf[nb] = '\r';
							buf[nb+1] = '\n';
							buf[nb+2] = '\0';
							nb_size+=2U;
						}
						else
						{
							// Buffer is not large enough to append "\r\n"
							// Truncate the message to fit in the buffer
							buf[BUF_SIZE-3] = '\r';
							buf[BUF_SIZE-2] = '\n';
							buf[BUF_SIZE-1] = '\0';
							nb_size= (uint32_t)(BUF_SIZE-1);
						}
					}
				}
				HAL_UART_Transmit(&huart2, (uint8_t*)&buf, nb_size,HAL_MAX_DELAY);
			}
		}
		break;
	}
}