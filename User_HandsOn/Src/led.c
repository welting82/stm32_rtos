#include "led.h"


void LED3_Configuration(void)
{
    __HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitTypeDef LED3_GPIO_Handler;
    LED3_GPIO_Handler.Pin = GPIO_PIN_13;
    LED3_GPIO_Handler.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOG, &LED3_GPIO_Handler);
}

void Blink_Task(void* pvParameters)
{
    while (1) {
        HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
        vTaskDelay(200);
        HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
        vTaskDelay(200);
    }
}