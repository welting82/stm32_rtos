#ifndef I2C_H
#define I2C_H

#include "base_init.h"
#include "uart.h"

#define AXDL345_ADDR 0xE5

void I2C1_Configuration(void);
void I2C2_Configuration(void);

#endif /* I2C_H */