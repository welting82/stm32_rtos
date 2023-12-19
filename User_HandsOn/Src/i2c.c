#include "i2c.h"

I2C_HandleTypeDef  hi2c1;
I2C_HandleTypeDef  hi2c2;
HAL_StatusTypeDef res;

void I2C1_Configuration(void) // for AXDL345
{
	//UART Configuration
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000; //100kHz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0x00;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c1);
    // res = HAL_I2C_IsDeviceReady(&hi2c1,0xE5,1,3);
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
    // res = HAL_I2C_IsDeviceReady(&hi2c2,0xAA,10,30);
}

void i2c_main(void)
{
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1);  //pull for L3GD20 CS pin;
    uint8_t data[3] = {0x30,0x31,0x32};

    res = HAL_I2C_Master_Transmit(&hi2c1, AXDL345_ADDR, (uint8_t *)&data, 1,HAL_MAX_DELAY);
    res = HAL_I2C_Master_Receive(&hi2c1, AXDL345_ADDR, (uint8_t *)&data, 10,HAL_MAX_DELAY);
	debug_print("res = 0x%x",res);
    return;
}


