#include "I2C.h"
#include "BitOperation.h"

//Test program for EEPROM 24C02

void EEPROM_WriteByte(unsigned char address, unsigned char data)
{
	I2C_Send_Start();

	I2C_WriteByte(EEPROM_ADDR);
	I2C_WaitForACK();
	
	I2C_WriteByte(address);
	I2C_WaitForACK();
	
	I2C_WriteByte(data);
	I2C_WaitForACK();
	
	I2C_Send_Stop();
}
unsigned char EEPROM_ReadByte(unsigned char address)
{
	unsigned char data;
	I2C_Send_Start();
	I2C_WriteByte(EEPROM_ADDR);
	I2C_WaitForACK();
	
	I2C_WriteByte(address);
	I2C_WaitForACK();
	
	I2C_Send_Start();
	I2C_WriteByte(EEPROM_ADDR|1); //Read
	
	I2C_WaitForACK();
	data = I2C_ReadByte();

	I2C_Send_Stop();
	return data;
}