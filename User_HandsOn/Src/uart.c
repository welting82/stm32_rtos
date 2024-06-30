#include "uart.h"

extern xSemaphoreHandle xSemaphore;
xTaskHandle pvCreatedTaskShow_stack_usage;

UART_HandleTypeDef huart2; /*Create UART_InitTypeDef struct instance */
char RX_Buffer; //"Interrupt inputt"
char rec_data[100]; //"receice data"
char TX_Buffer[50] = "Hello World!!!\r\n";
char tmp_Buffer[20] = "Loop Cnt: ";
uint8_t Uart2_Rx_Cnt = 0;
uint8_t loop_cnt = 0;

void UART2_Configuration(void)
{
	//UART Configuration
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
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

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;

  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart2);

  /* Wait for reception of a character on the USART RX line and echo this
   * character on console */
  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

void calc_Task(void* pvParameters)
{
	int idx = 10;
	while (1)
	{
		if( xSemaphore != NULL )
		{
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
		}
		vTaskDelay(500);
	}
}

void send_hello_world(void* pvParameters)
{
	while (1)
	{
		if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				HAL_UART_Transmit(&huart2, (uint8_t*)&TX_Buffer, sizeof(TX_Buffer),HAL_MAX_DELAY);
				xSemaphoreGive( xSemaphore );
			}
		}
		vTaskDelay(1000);
	}
}

void send_counting(void* pvParameters)
{
	while (1)
	{
		if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				HAL_UART_Transmit(&huart2, (uint8_t*)&tmp_Buffer, sizeof(tmp_Buffer),HAL_MAX_DELAY);
				xSemaphoreGive( xSemaphore );
			}
		}
		vTaskDelay(500);
	}
}
void Show_stack_usage(void* pvParameters)
{
	unsigned portBASE_TYPE uxHighWaterMark;

    while (1) {
		if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				uxHighWaterMark=uxTaskGetStackHighWaterMark(pvCreatedTaskShow_stack_usage);
				printf("Stack size left(word): %d\r\n",uxHighWaterMark);
				xSemaphoreGive( xSemaphore );
			}
		}
			vTaskDelay(5000);
	}
}