#include "gyro.h"


void Read_gyro(void* pvParameters)
{
    float data[3] = {0};
    L3GD20_SPI_init();
    printf(,L3GD20_SPI_getTemp());
	while (1)
	{
		if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				L3GD20_SPI_getOutput(&data);
				printf("X = %6.3f(g), Y = %6.3f(g), Z = %6.3f(g)\r\n",data[0],data[1],data[2]);
				xSemaphoreGive( xSemaphore );
			}
		}
		vTaskDelay(100);
	}
}