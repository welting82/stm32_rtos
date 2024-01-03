#ifndef I2C_H
#define I2C_H

#include "base_init.h"
#include "uart.h"
#include "ADXL345_i2c.h"

void I2C1_Configuration(void);
void I2C2_Configuration(void);
void AXDL345_main(void* pvParameters);

#endif /* I2C_H */