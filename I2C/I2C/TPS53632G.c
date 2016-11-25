#include "I2C.h"
#include "TPS53632.h"

/*
This program is intended to be used with LMG5200POLEVM-10A GaN 48V-1V evaluation and demonstration board
*/


/*
Set the VSR register, range: 0x19 to 0x7F
Control the output voltage, range: 0.5 to 1.52V
*/
void TPS_SetVSR(unsigned char val) {
	I2C_Send_Start();
	
	I2C_WriteByte(TPS_ADDR);
	I2C_WaitForACK();
	
	I2C_WriteByte(0x00);
	I2C_WaitForACK();
	
	I2C_WriteByte(val);
	I2C_WaitForACK();
	
	I2C_Send_Stop();
}

/*
Read a value which is proportional to the output current, range: 0 to 0xFF
*/
unsigned char TPS_GetIMON(void) {
	unsigned char res;
	I2C_Send_Start();
	I2C_WriteByte(TPS_ADDR);
	I2C_WaitForACK();
	
	I2C_WriteByte(0x03);
	I2C_WaitForACK();
	
	I2C_Send_Start();
	I2C_WriteByte(TPS_ADDR | 0x01);
	I2C_WaitForACK();
	
	res = I2C_ReadByte();
	I2C_Send_ACK();

	I2C_Send_Stop();

	return res;
}