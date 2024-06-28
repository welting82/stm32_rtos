#include "gyro.h"

SPI_HandleTypeDef hspi5;

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
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
    
	HAL_SPI_Init(&hspi5);
}

void Read_gyro(void* pvParameters)
{
	// TODO: toggle CS
	
	HAL_SPI_Transmit(hspi5, *pData, Size, uint32_t Timeout)
	HAL_SPI_Receive(hspi5, *pData, Size, uint32_t Timeout)
}