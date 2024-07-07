#include "gyro.h"
extern xSemaphoreHandle xSemaphore;

void Read_gyro(void* pvParameters)
{
    float data[3] = {0};
    L3GD20_SPI_init();
	while (1)
	{
		if( xSemaphore != NULL )
		{
			if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
			{
				L3GD20_SPI_getOutput(&data);
				printf(" X = %6.3f(dps),  Y = %6.3f(dps),  Z = %6.3f(dps)\r\n",data[0],data[1],data[2]);
    			// printf("temp:%d\r\n",L3GD20_SPI_getTemp());
    			// printf("Status:%x\r\n",L3GD20_SPI_getStatus());
    			// printf("REG3:%x\r\n",L3GD20_SPI_getCTR_REG3());
				memset(data,0,3);
				L3GD20_SPI_getOutputM(data);
				printf("MX = %6.3f(dps), MY = %6.3f(dps), MZ = %6.3f(dps)\r\n",data[0],data[1],data[2]);
				xSemaphoreGive( xSemaphore );
			}
		}
		vTaskDelay(500);
	}
}