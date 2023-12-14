#include "i2c.h"

I2C_HandleTypeDef  hi2c1;

void I2C1_Configuration(void)
{
	//UART Configuration
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000; //100kHz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0x00;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c1);
}



