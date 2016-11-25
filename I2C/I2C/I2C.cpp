// I2C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
#include "I2C.h"
#include "TPS53632.h"
}


int main()
{
	unsigned char data;

	I2C_StartCOM("COM5");
	I2C_Init();
	
	//EEPROM 24C02 Test
	/*
	Sleep(1);
	EEPROM_WriteByte(0xF3, 0x47);
	Sleep(10);
	data = EEPROM_ReadByte(0xF3);
	*/

	//Digital power supply TPS53632 Test
	/*
	scanf_s("%d", &data);
	TPS_SetVSR(Vol100ToVID(data));
	Sleep(100);
	printf("%d\n", (int)IMONToCurrent10(TPS_GetIMON()));
	*/

	I2C_StopCOM();	

    return 0;
}

