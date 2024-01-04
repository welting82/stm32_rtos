/*
 * @section DESCRIPTION
 *
 * ADXL345, triple axis, I2C interface, accelerometer.
 *
 * Datasheet:
 *
 * http://www.analog.com/static/imported-files/data_sheets/ADXL345.pdf
 */

/**
 * Includes
 */
#include "ADXL345_i2c.h"
HAL_StatusTypeDef i2c_res;

void ADXL345_I2C_init(void)
{
    if(HAL_I2C_IsDeviceReady(&hi2c1,ADXL345_I2C_READ,1,3) != HAL_OK)
    {
        printf("i2c NG!\r\n");
        return;
    }
    else
    {
        printf("i2c ok!\r\n");
    }

    // initialize the BW data rate
    //frequence greater than or equal to 0x0A is written into the rate bits (Bit D3 through Bit D0) in the BW_RATE register
    ADXL345_I2C_setDataRate(ADXL345_1600HZ);

    //Data format (for +-16g) - This is done by setting Bit D3 of the DATA_FORMAT register (Address 0x31) and writing a value of 0x03 to the range bits (Bit D1 and Bit D0) of the DATA_FORMAT register (Address 0x31).
    ADXL345_I2C_SingleByteWrite(ADXL345_DATA_FORMAT_REG,0x0F);
 
    // Set Offset  - programmed into the OFSX, OFSY, and OFXZ registers, calibration by hand......(find the zero point and balance)
    ADXL345_I2C_SingleByteWrite(ADXL345_OFSX_REG,0x00);
    ADXL345_I2C_SingleByteWrite(ADXL345_OFSY_REG,0x05);
    ADXL345_I2C_SingleByteWrite(ADXL345_OFSZ_REG,0xFD);

    uint8_t reg =  ADXL345_I2C_getPowerControl();
    reg = reg | (1<<3);
    i2c_res = HAL_ERROR;
    i2c_res = ADXL345_I2C_SingleByteWrite(ADXL345_POWER_CTL_REG,reg);

    return;
}

char ADXL345_I2C_SingleByteRead(char address)
{
   char tx = address;
   char output;
   i2c_res = HAL_ERROR;
   i2c_res = HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_WRITE, (uint8_t *)&tx, sizeof(tx),HAL_MAX_DELAY);
   i2c_res = HAL_I2C_Master_Receive(&hi2c1, ADXL345_I2C_READ, (uint8_t *)&output, sizeof(output),HAL_MAX_DELAY);
    return output;
}

/*
address     8-bit I2C slave address [ addr | 0 ]
data        Pointer to the byte-array data to send
length        Number of bytes to send
returns     HAL status
*/
HAL_StatusTypeDef ADXL345_I2C_SingleByteWrite(char address, char data)
{
   char tx[2];
   tx[0] = address;
   tx[1] = data;
    return HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_WRITE, (uint8_t *)&tx, sizeof(tx),HAL_MAX_DELAY);
}



void ADXL345_I2C_multiByteRead(char address, uint8_t* output, uint8_t size)
{
    // HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_WRITE, address, 1,HAL_MAX_DELAY);
    i2c_res = HAL_ERROR;
    i2c_res = HAL_I2C_Mem_Read(&hi2c1,ADXL345_I2C_READ, address, I2C_MEMADD_SIZE_8BIT, (uint8_t *)output, size, HAL_MAX_DELAY);
    return;
}


HAL_StatusTypeDef ADXL345_I2C_multiByteWrite(char address, char* ptr_data, uint8_t size)
{
    // HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_WRITE, address, 1,HAL_MAX_DELAY);
    return HAL_I2C_Mem_Write(&hi2c1,ADXL345_I2C_READ, address, I2C_MEMADD_SIZE_8BIT, (uint8_t *)ptr_data, size, HAL_MAX_DELAY);
}


void ADXL345_I2C_getOutput(float* readings)
{
    uint8_t buffer[6];
    ADXL345_I2C_multiByteRead(ADXL345_DATAX0_REG, buffer, 6);
    readings[0] = (float)((short)(buffer[1] << 8 | buffer[0])*0.0048);//4.8mg/LSB is result tring by hand.....
    readings[1] = (float)((short)(buffer[3] << 8 | buffer[2])*0.0048);//4.8mg/LSB is result tring by hand.....
    readings[2] = (float)((short)(buffer[5] << 8 | buffer[4])*0.0048);//4.8mg/LSB is result tring by hand.....
}

char ADXL345_I2C_getDeviceID()
{  
    uint8_t res = 0;
    ADXL345_I2C_multiByteRead(ADXL345_DEVID_REG,&res,1);
    return res;
    // return ADXL345_I2C_SingleByteRead(ADXL345_DEVID_REG);
}

int ADXL345_I2C_setPowerMode(char mode)
{ 
    //Get the current register contents, so we don't clobber the rate value.
    char registerContents = (mode << 4) | ADXL345_I2C_SingleByteRead(ADXL345_BW_RATE_REG);
    return ADXL345_I2C_SingleByteWrite(ADXL345_BW_RATE_REG, registerContents);
}

char ADXL345_I2C_getPowerControl()
{
    return ADXL345_I2C_SingleByteRead(ADXL345_POWER_CTL_REG);
}

int ADXL345_I2C_setPowerControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_POWER_CTL_REG, settings);
}

char ADXL345_I2C_getDataFormatControl(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_DATA_FORMAT_REG);
}

int ADXL345_I2C_setDataFormatControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_DATA_FORMAT_REG, settings);
}

int ADXL345_I2C_setDataRate(char rate)
{
    //Get the current register contents, so we don't clobber the power bit.
    char registerContents = ADXL345_I2C_SingleByteRead(ADXL345_BW_RATE_REG);

    registerContents &= 0x10;
    registerContents |= rate;

    return ADXL345_I2C_SingleByteWrite(ADXL345_BW_RATE_REG, registerContents);

}


char ADXL345_I2C_getOffset(char axis)
{
    char address = 0;

    if (axis == ADXL345_X) {
        address = ADXL345_OFSX_REG;
    } else if (axis == ADXL345_Y) {
        address = ADXL345_OFSY_REG;
    } else if (axis == ADXL345_Z) {
        address = ADXL345_OFSZ_REG;
    }

    return ADXL345_I2C_SingleByteRead(address);
}

int ADXL345_I2C_setOffset(char axis, char offset)
{
    char address = 0;

    if (axis == ADXL345_X) {
        address = ADXL345_OFSX_REG;
    } else if (axis == ADXL345_Y) {
        address = ADXL345_OFSY_REG;
    } else if (axis == ADXL345_Z) {
        address = ADXL345_OFSZ_REG;
    }

    return ADXL345_I2C_SingleByteWrite(address, offset);
}

char ADXL345_I2C_getFifoControl(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_FIFO_CTL);
}

int ADXL345_I2C_setFifoControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_FIFO_STATUS, settings);
}

char ADXL345_I2C_getFifoStatus(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_FIFO_STATUS);
}

char ADXL345_I2C_getTapThreshold(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_THRESH_TAP_REG);
}

int ADXL345_I2C_setTapThreshold(char threshold)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_THRESH_TAP_REG, threshold);
}

float ADXL345_I2C_getTapDuration(void)
{
    return (float)ADXL345_I2C_SingleByteRead(ADXL345_DUR_REG)*625;
}

int ADXL345_I2C_setTapDuration(short int duration_us)
{
    short int tapDuration = duration_us / 625;
    char tapChar[2];
    tapChar[0] = (tapDuration & 0x00FF);
    tapChar[1] = (tapDuration >> 8) & 0x00FF;
    return ADXL345_I2C_multiByteWrite(ADXL345_DUR_REG, tapChar, 2);
}

float ADXL345_I2C_getTapLatency(void)
{
    return (float)ADXL345_I2C_SingleByteRead(ADXL345_LATENT_REG)*1.25;
}

int ADXL345_I2C_setTapLatency(short int latency_ms)
{
    latency_ms = latency_ms / 1.25;
    char latChar[2];
    latChar[0] = (latency_ms & 0x00FF);
    latChar[1] = (latency_ms << 8) & 0xFF00;
    return ADXL345_I2C_multiByteWrite(ADXL345_LATENT_REG, latChar, 2);
}

float ADXL345_I2C_getWindowTime(void)
{
    return (float)ADXL345_I2C_SingleByteRead(ADXL345_WINDOW_REG)*1.25;
}

int ADXL345_I2C_setWindowTime(short int window_ms)
{
    window_ms = window_ms / 1.25;
    char windowChar[2];
    windowChar[0] = (window_ms & 0x00FF);
    windowChar[1] = ((window_ms << 8) & 0xFF00);
    return ADXL345_I2C_multiByteWrite(ADXL345_WINDOW_REG, windowChar, 2);
}

char ADXL345_I2C_getActivityThreshold(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_THRESH_ACT_REG);
}

int ADXL345_I2C_setActivityThreshold(char threshold)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_THRESH_ACT_REG, threshold);
}

char ADXL345_I2C_getInactivityThreshold(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_THRESH_INACT_REG);
}

int ADXL345_I2C_setInactivityThreshold(char threshold)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_THRESH_INACT_REG, threshold);
}

char ADXL345_I2C_getTimeInactivity(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_TIME_INACT_REG);
}

int ADXL345_I2C_setTimeInactivity(char timeInactivity)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_TIME_INACT_REG, timeInactivity);
}

char ADXL345_I2C_getActivityInactivityControl(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_ACT_INACT_CTL_REG);
}

int ADXL345_I2C_setActivityInactivityControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_ACT_INACT_CTL_REG, settings);
}

char ADXL345_I2C_getFreefallThreshold(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_THRESH_FF_REG);
}

int ADXL345_I2C_setFreefallThreshold(char threshold)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_THRESH_FF_REG, threshold);
}

char ADXL345_I2C_getFreefallTime(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_TIME_FF_REG)*5;
}

int ADXL345_I2C_setFreefallTime(short int freefallTime_ms)
{
     freefallTime_ms = freefallTime_ms / 5;
     char fallChar[2];
     fallChar[0] = (freefallTime_ms & 0x00FF);
     fallChar[1] = (freefallTime_ms << 8) & 0xFF00;
    
    return ADXL345_I2C_multiByteWrite(ADXL345_TIME_FF_REG, fallChar, 2);
}

char ADXL345_I2C_getTapAxisControl(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_TAP_AXES_REG);
}

int ADXL345_I2C_setTapAxisControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_TAP_AXES_REG, settings);
}

char ADXL345_I2C_getTapSource(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_ACT_TAP_STATUS_REG);
}

char ADXL345_I2C_getInterruptEnableControl(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_INT_ENABLE_REG);
}

int ADXL345_I2C_setInterruptEnableControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_INT_ENABLE_REG, settings);
}

char ADXL345_I2C_getInterruptMappingControl(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_INT_MAP_REG);
}

int ADXL345_I2C_setInterruptMappingControl(char settings)
{
    return ADXL345_I2C_SingleByteWrite(ADXL345_INT_MAP_REG, settings);
}

char ADXL345_I2C_getInterruptSource(void)
{
    return ADXL345_I2C_SingleByteRead(ADXL345_INT_SOURCE_REG);
}




