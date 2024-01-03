#include "i2c.h"
// #include <stdio.h>

I2C_HandleTypeDef  hi2c1;
I2C_HandleTypeDef  hi2c2;
HAL_StatusTypeDef res;
extern xSemaphoreHandle xSemaphore;

void I2C1_Configuration(void) // for AXDL345
{
	//UART Configuration
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000; //100kHz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0x00;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c1);
}

void I2C2_Configuration(void)  // for L3GD20
{
	//UART Configuration
	hi2c2.Instance = I2C2;
	hi2c2.Init.ClockSpeed = 100000; //100kHz
	hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c2.Init.OwnAddress1 = 0x00;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c2);
}

void AXDL345_main(void* pvParameters)
{
	float data[3] = {0};
	ADXL345_I2C_init();
	while (1)
	{
		if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				ADXL345_I2C_getOutput(&data[0]);
				printf("X = %f, Y = %f, Z = %f\r\n",data[0],data[1],data[2]);
				xSemaphoreGive( xSemaphore );
			}
		}
		vTaskDelay(500);
	}
}


