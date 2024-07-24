#ifndef MAX_30205_H
#define MAX_30205_H

#include "stm32h7xx_hal.h"
#include "i2c.h"
#include "robot.h"

#define MAX30205_ADDR 	0x90
#define MAX30205_TEMP 	0x00
#define MAX30205_CONFIG 0x01
#define MAX30205_THYST 	0x02
#define MAX30205_TOS 		0x03

// I2C
void max30205_i2c_readBytes(uint8_t address, uint8_t reg, uint8_t* data, uint8_t size);
uint8_t max30205_i2c_readByte(uint8_t address, uint8_t reg);
uint8_t max30205_i2c_writeByte(uint8_t address, uint8_t reg, uint8_t value);

// function
void MAX30205_Init(void);
void MAX30205_Shutdown(void);
void MAX30205_OneShotMode(void);
float MAX30205_GetTemperature(void);

#endif//MAX_30205_H
