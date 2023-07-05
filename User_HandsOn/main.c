#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#define BLINK_TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

void UART2_Configuration(void);
void Clock_Configuration(void);
void LED3_Configuration(void);
void Delay_ms(volatile int time_ms);

UART_HandleTypeDef huart2; /*Create UART_InitTypeDef struct instance */
char RX_Buffer; //"Interrupt inputt"
char rec_data[10]; //"receice data"
char TX_Buffer[50] = "Hello World\r\n";
uint8_t Uart2_Rx_Cnt = 0;
uint8_t loop_cnt = 0;

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

void LED3_Configuration(void)
{
    __HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitTypeDef LED3_GPIO_Handler;
    LED3_GPIO_Handler.Pin = GPIO_PIN_13;
    LED3_GPIO_Handler.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOG, &LED3_GPIO_Handler);
}

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

void Clock_Configuration(void)
{
    __HAL_RCC_USART2_CLK_ENABLE(); /* Enable clock to UART2 module */

    // PLL Configuration
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

}

/*Generate ms */
void Delay_ms(volatile int time_ms)
{
  int j;
  for(j = 0; j < time_ms*4000; j++)
    {}  /* excute NOP for 1ms */
}


void vAssertCalled( const char * pcFile, unsigned long ulLine )
{
  volatile unsigned long ul = 0;

  ( void ) pcFile;
  ( void ) ulLine;

  vTaskSuspendAll();
  taskENTER_CRITICAL();
  {
    /* Set ul to a non-zero value using the debugger to step out of this
       function. */
    printf("%s %s: line=%lu\n", __func__, pcFile, ulLine);
    while( ul == 0 ) {
      portNOP();
    }
  }
  taskEXIT_CRITICAL();
}

void vApplicationTickHook( void )
{

}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}

static void Blink_Task(void* pvParameters)
{
    TickType_t xLastFlashTime;

    xLastFlashTime = xTaskGetTickCount();

    while (1) {
        HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
        vTaskDelayUntil(&xLastFlashTime, 500);
        HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
        vTaskDelayUntil(&xLastFlashTime, 1500);
    }
}


int main(void)
{
	HAL_Init(); /* HAL library initialization */
	Clock_Configuration();
	UART2_Configuration(); /* Call UART2 initialization define below */
	LED3_Configuration();
	xTaskCreate(Blink_Task, "LED", configMINIMAL_STACK_SIZE, NULL,
                BLINK_TASK_PRIORITY, NULL);

    vTaskStartScheduler();
	while(1)
	{
	}
}