#ifndef L3GD20_H
#define L3GD20_H

#include "base_init.h"

// Write/Read bytes
#define L3GD20_SPI_RWbit       7
#define L3GD20_SPI_MULTIBYTE   6
#define L3GD20_SPI_WRITE       0
#define L3GD20_SPI_READ        1


#define L3GD20_DEVID_REG      0x0F
#define L3GD20_CTRL_REG1      0x20
#define L3GD20_CTRL_REG2      0x21
#define L3GD20_CTRL_REG3      0x22
#define L3GD20_CTRL_REG4      0x23
#define L3GD20_CTRL_REG5      0x24
#define L3GD20_REFERENCE      0x25
#define L3GD20_OUT_TEMP       0x26
#define L3GD20_STATUS_REG     0x27
#define L3GD20_OUT_X_L        0x28
#define L3GD20_OUT_X_H        0x29
#define L3GD20_OUT_Y_L        0x2A
#define L3GD20_OUT_Y_H        0x2B
#define L3GD20_OUT_Z_L        0x2C
#define L3GD20_OUT_Z_H        0x2D
#define L3GD20_FIFO_CTRL_REG  0x2E
#define L3GD20_FIFO_SRC_REG   0x2F
#define L3GD20_INT1_CFG       0x30
#define L3GD20_INT1_SRC       0x31
#define L3GD20_INT1_TSH_XH    0x32
#define L3GD20_INT1_TSH_XL    0x33
#define L3GD20_INT1_TSH_YH    0x34
#define L3GD20_INT1_TSH_YL    0x35
#define L3GD20_INT1_TSH_ZH    0x36
#define L3GD20_INT1_TSH_ZL    0x37
#define L3GD20_INT1_DURATION  0x38


void SPI5_Configuration(void);
void L3GD20_SPI_getOutput(float* data);
HAL_StatusTypeDef L3GD20_SPI_SingleByteWrite(char addr, char data);
char L3GD20_SPI_SingleByteRead(char addr);

#endif /* L3GD20_H */