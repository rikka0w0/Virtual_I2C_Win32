#pragma once

/*
Uncomment the following line if you are using native COM port or other types of USB to COM adapters
RTS, DTR and CTS are normally active high, but they are ACTIVE LOW on PL2303
*/
#define PL2303

/*
The Address of EEPROM(24C02) for the hardware configuration described in the readme file
*/
#define EEPROM_ADDR 0xA0

//COM
char I2C_StartCOM(const char* PortName);
void I2C_StopCOM(void);





//I2C Bus
/*
Initialize the I2C bus and release SDA and SDL, the bus is now in idle state
*/
void I2C_Init(void);
void I2C_Send_Start(void);
void I2C_Send_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
/*
Write a single byte to the I2C bus, and then release SDA, be ready to receive ACK or NACK from the slave device
*/
void I2C_WriteByte(unsigned char dat);
/*
Read a signle byte from the I2C bus
*/
unsigned char I2C_ReadByte(void);
/*
*/
void I2C_WaitForACK(void);




//Write a single byte to the EEPROM (24C02)
void EEPROM_WriteByte(unsigned char address, unsigned char data);
//Read a single byte from the EEPROM (24C02)
unsigned char EEPROM_ReadByte(unsigned char address);