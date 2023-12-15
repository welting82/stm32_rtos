#include "i2c.h"

I2C_HandleTypeDef  hi2c1;
I2C_HandleTypeDef  hi2c2;
HAL_StatusTypeDef res;

void I2C1_Configuration(void)
{
	//UART Configuration
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000; //100kHz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0x00;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c1);
    res = HAL_I2C_IsDeviceReady(&hi2c1,0x0,10,30);
}

void I2C2_Configuration(void)
{
	//UART Configuration
	hi2c2.Instance = I2C2;
	hi2c2.Init.ClockSpeed = 100000; //100kHz
	hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c2.Init.OwnAddress1 = 0x00;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c2);
    res = HAL_I2C_IsDeviceReady(&hi2c2,0x0,10,30);
}

void i2c_main(void)
{
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1);
}


