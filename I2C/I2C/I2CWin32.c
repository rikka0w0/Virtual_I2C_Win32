#include <Windows.h>
#include "I2C.h"
#include "BitOperation.h"

#define Delay() Sleep(1)

//Hardware pin definition
#ifdef PL2303
#define SDA_H() COM_RTS_High()
#define SDA_L() COM_RTS_Low()
#define SCL_H() COM_DTR_High()
#define SCL_L() COM_DTR_Low()
#define SDA()	(!(I2C_GetComStatus()&MS_CTS_ON))
#else
#define SDA_H() COM_RTS_Low()
#define SDA_L() COM_RTS_High()
#define SCL_H() COM_DTR_Low()
#define SCL_L() COM_DTR_High()
#define SDA()	(I2C_GetComStatus()&MS_CTS_ON)
#endif

//COM port
#define COM_DTR_High() EscapeCommFunction(hCom,SETDTR)
#define COM_DTR_Low() EscapeCommFunction(hCom,CLRDTR)
#define COM_RTS_High() EscapeCommFunction(hCom,SETRTS)
#define COM_RTS_Low() EscapeCommFunction(hCom,CLRRTS)

HANDLE hCom;

//if result == 0xFFFFFFFF => fail
char I2C_StartCOM(const char* PortName) {
	DCB config;

	//Attempt to open the port
	hCom = CreateFileA(PortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCom == (HANDLE)(-1))
		return FALSE;
	//assert(hCom != (HANDLE)0xFFFFFFFF);

	//Set the buffer size
	SetupComm(hCom, 1024, 1024);

	//Reconfig the COM port
	GetCommState(hCom, &config);
	config.BaudRate = 9600;
	config.ByteSize = 8;
	config.Parity = NOPARITY;
	config.StopBits = ONESTOPBIT;
	config.fOutxCtsFlow = FALSE;
	config.fOutxDsrFlow = FALSE;
	config.fDsrSensitivity = FALSE;
	config.fDtrControl = DTR_CONTROL_DISABLE;
	config.fRtsControl = RTS_CONTROL_DISABLE;
	SetCommState(hCom, &config);

	return TRUE;
}

//Stop the COM port, release the handle
void I2C_StopCOM(void) {
	CloseHandle(hCom);
	hCom = NULL;
}

DWORD I2C_GetComStatus() {
	DWORD res;
	GetCommModemStatus(hCom, &res);
	return res;
}




//I2C protocol -------------------------------------------------------
void I2C_Init(void)
{
	SDA_H();
	Delay();
	SCL_H();
	Delay();
}

void I2C_Send_Start(void)
{
	SDA_H();
	SCL_H();
	SDA_L();
}

void I2C_Send_Stop(void)
{
	SDA_L();
	SCL_H();
	SDA_H(); //Master release the bus
}

void I2C_Send_ACK(void) {
	SCL_L();
	SDA_L();
	SCL_H();
}

void I2C_Send_NACK(void) {
	SCL_L();
	SDA_H();
	SCL_H();
}

void I2C_WriteByte(unsigned char dat)
{
	SCL_L();
	if (dat & 0x80) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x40) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x20) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x10) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x08) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x04) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x02) SDA_H(); else SDA_L();
	SCL_H();

	SCL_L();
	if (dat & 0x01) SDA_H(); else SDA_L();
	SCL_H();

	//Release the SDA bus
	SCL_L();
	SDA_H();
}

unsigned char I2C_ReadByte(void)
{
	DWORD sta;
	unsigned char res;
	res = 0;

	SCL_L();
	SDA_H(); //Master release the bus

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x80;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x40;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x20;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x10;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x08;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x04;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x02;
	SCL_L();

	SCL_H();
	Delay();
	if (SDA())
		res |= 0x01;
	SCL_L();

	return res;
}

void I2C_WaitForACK(void){
	unsigned char i = 0;
	SCL_H();
	while (SDA() && i < 200) {
		i++;
		Sleep(1);
	}
	SCL_L();
}