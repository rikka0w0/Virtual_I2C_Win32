#pragma once

//I2C address of the TPS53632G
#define TPS_ADDR 0x80

//Convertions between VID and voltage (100 times of actual set output voltage)
#define Vol100ToVID(vol) (vol-25)
#define VIDTOVol100(VID) (VID+25)

//Convert IMON to output current (10 times of actual output current)
#define IMONToCurrent10(IMON) (IMON * 680 / 255 * 0.895)

/*
Set the VSR register, range: 0x19 to 0x7F
Control the output voltage, range: 0.5 to 1.52V
*/
void TPS_SetVSR(unsigned char val);
/*
Read a value which is proportional to the output current, range: 0 to 0xFF
*/
unsigned char TPS_GetIMON(void);