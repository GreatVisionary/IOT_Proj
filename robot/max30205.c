#include "max30205.h"

void max30205_i2c_readBytes(uint8_t address, uint8_t reg, uint8_t* data, uint8_t size) {
  HAL_I2C_Mem_Read(&hi2c2, MAX30205_ADDR, reg,	1, data, size, 100);
}

uint8_t max30205_i2c_readByte(uint8_t address, uint8_t reg) {
	uint8_t value = 0;
  HAL_I2C_Mem_Read(&hi2c2, MAX30205_ADDR, reg,	1, (uint8_t*)&value, 1, 100);
	return value;
}

uint8_t max30205_i2c_writeByte(uint8_t address, uint8_t reg, uint8_t value) {
	uint8_t ret;
  ret = HAL_I2C_Mem_Write(&hi2c2, MAX30205_ADDR, reg,	1, (uint8_t*)&value, 1, 100);
	return ret;
}

void MAX30205_Init(void)
{
  max30205_i2c_writeByte(MAX30205_ADDR, MAX30205_CONFIG, 0x00); //mode setting	
  max30205_i2c_writeByte(MAX30205_ADDR, MAX30205_THYST , 0x00); //threshold
  max30205_i2c_writeByte(MAX30205_ADDR, MAX30205_TOS, 0x00); 
}

void MAX30205_Shutdown(void)
{
  uint8_t config_reg = max30205_i2c_readByte(MAX30205_ADDR, MAX30205_CONFIG);  // Get the current register
  max30205_i2c_writeByte(MAX30205_ADDR, MAX30205_CONFIG, config_reg | 0x01);
}

void MAX30205_OneShotMode(void)
{
	MAX30205_Shutdown();
	uint8_t config_reg = max30205_i2c_readByte(MAX30205_ADDR, MAX30205_CONFIG);  // Get the current register
  max30205_i2c_writeByte(MAX30205_ADDR, MAX30205_CONFIG, config_reg | 0x80);
}

float MAX30205_GetTemperature(void) 
{
	uint8_t buffer[2];
	uint8_t config_reg = max30205_i2c_readByte(MAX30205_ADDR, MAX30205_CONFIG);  // Get the current register
  max30205_i2c_writeByte(MAX30205_ADDR, MAX30205_CONFIG, config_reg | 0x80);   // Set one-shot mode
	max30205_i2c_readBytes(MAX30205_ADDR, MAX30205_TEMP, buffer, 2);
	
	//solution 1
	//int16_t raw = ((uint16_t)buffer[0] << 8) | buffer[1];
	//return	((double)raw  * 0.00390625);
	
	//solution 2
	double raw_temp=0;
	if(buffer[0]&0x40)raw_temp+=64;
	if(buffer[0]&0x20)raw_temp+=32;
	if(buffer[0]&0x10)raw_temp+=16;
	if(buffer[0]&0x08)raw_temp+=8;
	if(buffer[0]&0x04)raw_temp+=4;
	if(buffer[0]&0x02)raw_temp+=2;
	if(buffer[0]&0x01)raw_temp+=1;
	
	if(buffer[1]&0x80)raw_temp+=0.5;
	if(buffer[1]&0x40)raw_temp+=0.25;
	if(buffer[1]&0x20)raw_temp+=0.125;
	if(buffer[1]&0x10)raw_temp+=0.0625;
	if(buffer[1]&0x08)raw_temp+=0.03125;
	if(buffer[1]&0x04)raw_temp+=0.015625;
	if(buffer[1]&0x02)raw_temp+=0.0078125;
	if(buffer[1]&0x01)raw_temp+=0.00390625;
	
	return raw_temp * 1.07;//抽象的倍数，如果后续正常了就删除
}
