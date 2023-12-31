/**
  ******************************************************************************
  * @file    stm32f4xx_hal_msp_template.c
  * @author  MCD Application Team
  * @brief   This file contains the HAL System and Peripheral (PPP) MSP initialization
  *          and de-initialization functions.
  *          It should be copied to the application folder and renamed into 'stm32f4xx_hal_msp.c'.           
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP HAL MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions HAL MSP Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @note   This function is called from HAL_Init() function to perform system
  *         level initialization (GPIOs, clock, DMA, interrupt).
  * @retval None
  */
void HAL_MspInit(void)
{

}

/**
  * @brief  DeInitializes the Global MSP.
  * @note   This functiona is called from HAL_DeInit() function to perform system
  *         level de-initialization (GPIOs, clock, DMA, interrupt).
  * @retval None
  */
void HAL_MspDeInit(void)
{

}

/**
  * @brief  Initializes the PPP MSP.
  * @note   This functiona is called from HAL_PPP_Init() function to perform 
  *         peripheral(PPP) system level initialization (GPIOs, clock, DMA, interrupt)
  * @retval None
  */
void HAL_PPP_MspInit(void)
{

}

/**
  * @brief  DeInitializes the PPP MSP.
  * @note   This functiona is called from HAL_PPP_DeInit() function to perform 
  *         peripheral(PPP) system level de-initialization (GPIOs, clock, DMA, interrupt)
  * @retval None
  */
void HAL_PPP_MspDeInit(void)
{

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART2)
  {
    __HAL_RCC_GPIOD_CLK_ENABLE(); /* Enable clock to PORTD - UART2 pins PD5 and PD6 */
    __HAL_RCC_USART2_CLK_ENABLE(); /* Enable clock to UART2 module */

    GPIO_InitTypeDef UART2_GPIO_Handler; /*Create GPIO_InitTypeDef struct instance */
    UART2_GPIO_Handler.Pin = GPIO_PIN_5 | GPIO_PIN_6;
    UART2_GPIO_Handler.Mode = GPIO_MODE_AF_PP;
    UART2_GPIO_Handler.Pull = GPIO_PULLUP;
    UART2_GPIO_Handler.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    UART2_GPIO_Handler.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &UART2_GPIO_Handler);
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  if(hi2c->Instance == I2C1)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE(); /* Enable clock to PORTB - I2C1 pins PB6 and PB7 */
    __HAL_RCC_I2C1_CLK_ENABLE(); /* Enable clock to I2C1 module */

    GPIO_InitTypeDef  hi2c;
    hi2c.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    hi2c.Mode = GPIO_MODE_AF_OD;
    hi2c.Pull = GPIO_NOPULL;
    hi2c.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    hi2c.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &hi2c);
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
  }

  if(hi2c->Instance == I2C2)
  {
    __HAL_RCC_GPIOF_CLK_ENABLE(); /* Enable clock to PORTF - I2C2 pins PF7 and PF9 */
    __HAL_RCC_I2C2_CLK_ENABLE(); /* Enable clock to I2C2 module */

    GPIO_InitTypeDef  hi2c;
    hi2c.Pin = GPIO_PIN_7 | GPIO_PIN_9;
    hi2c.Mode = GPIO_MODE_AF_OD;
    hi2c.Pull = GPIO_PULLUP;
    hi2c.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    hi2c.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOF, &hi2c);
    HAL_NVIC_SetPriority(I2C2_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);

    GPIO_InitTypeDef cs_pin; // pull high CS pin for enable L3GD20 i2c interface
    cs_pin.Pin = GPIO_PIN_1;
    cs_pin.Mode = GPIO_MODE_OUTPUT_PP;
    cs_pin.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &cs_pin);
  }
}



