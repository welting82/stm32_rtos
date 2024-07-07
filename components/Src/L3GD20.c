#include "L3GD20.h"

SPI_HandleTypeDef hspi5;
HAL_StatusTypeDef res;

void SPI5_Configuration(void)
{
	//SPI Configuration
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
    
	HAL_SPI_Init(&hspi5);
}

void L3GD20_SPI_init()
{
	//Setting power mode
	res = L3GD20_SPI_SingleByteWrite(L3GD20_CTRL_REG1,0xCF);
	//Setting scale
	res = L3GD20_SPI_SingleByteWrite(L3GD20_CTRL_REG4,0x30);
	return;
}

int8_t L3GD20_SPI_getTemp()
{
	//1LSB = 1 Celsius deg
	return (int8_t)L3GD20_SPI_SingleByteRead(L3GD20_OUT_TEMP);
}

uint8_t L3GD20_SPI_getStatus()
{
	return (uint8_t)L3GD20_SPI_SingleByteRead(L3GD20_STATUS_REG);
}

uint8_t L3GD20_SPI_getCTR_REG3()
{
	return (uint8_t)L3GD20_SPI_SingleByteRead(L3GD20_CTRL_REG3);
}

void L3GD20_SPI_getOutput(float* data)
{
	data[0] = (short)(L3GD20_SPI_SingleByteRead(L3GD20_OUT_X_H)<<8 | L3GD20_SPI_SingleByteRead(L3GD20_OUT_X_L));
	data[1] = (short)(L3GD20_SPI_SingleByteRead(L3GD20_OUT_Y_H)<<8 | L3GD20_SPI_SingleByteRead(L3GD20_OUT_Y_L));
	data[2] = (short)(L3GD20_SPI_SingleByteRead(L3GD20_OUT_Z_H)<<8 | L3GD20_SPI_SingleByteRead(L3GD20_OUT_Z_L));
	return;
}

void L3GD20_SPI_getOutputM(float* data)
{
	uint8_t raw_data[6] = {0};
	L3GD20_SPI_MultiByteRead(L3GD20_OUT_X_L,&raw_data,6);
	*data = (short) (*(raw_data+1)<<8 | *raw_data);
	*(data+2) = (short) (*(raw_data+3)<<8 | *(raw_data+2));
	*(data+1) = (short) (*(raw_data+5)<<8 | *(raw_data+4));
	return;
}

char L3GD20_SPI_SingleByteRead(char addr)
{
	uint8_t tx = 0;
	char data = 0;
	// Set CS low for enable SPI
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);

	tx |= (L3GD20_SPI_READ << L3GD20_SPI_RWbit | addr);

	res = HAL_SPI_Transmit(&hspi5, (uint8_t*)&tx, sizeof(tx),HAL_MAX_DELAY);
	res = HAL_SPI_Receive(&hspi5, (uint8_t*)&data, sizeof(data), HAL_MAX_DELAY);

	// Set CS high for disable SPI
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
	return data;
}

void L3GD20_SPI_MultiByteRead(char addr, uint8_t* pdata, uint8_t len)
{
	uint8_t tx = 0;
	// Set CS low for enable SPI
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);

	tx |= (L3GD20_SPI_READ << L3GD20_SPI_RWbit | 1 << L3GD20_SPI_MULTIBYTE | addr);

	res = HAL_SPI_Transmit(&hspi5, (uint8_t*)&tx, sizeof(tx),HAL_MAX_DELAY);
	res = HAL_SPI_Receive(&hspi5, pdata, len, HAL_MAX_DELAY);

	// Set CS high for disable SPI
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
	return;
}

HAL_StatusTypeDef L3GD20_SPI_SingleByteWrite(char addr, char data)
{
	uint8_t tx[2] = {0};
	// Set CS low for enable SPI
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);

	tx[0] |= (L3GD20_SPI_WRITE << L3GD20_SPI_RWbit | addr);
	tx[1] = data;

	res = HAL_SPI_Transmit(&hspi5, tx, sizeof(tx),HAL_MAX_DELAY);

	// Set CS high for disable SPI
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
	return res;
}

// void L3GD20_SPI_MultiByteWrite()
// {
	
// }