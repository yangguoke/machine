#define _LCD1602_C_
#include "..\\Includes.h"

bit lcd1602_BusyFlag()
{
	bit busy_flag;
	RS=0;
	RW=1;
	E=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	busy_flag=(bit)(P0&0x80);
	E=0;
	return busy_flag;
}

void lcd1602_WriteData(unsigned char Data)
{
	while(lcd1602_BusyFlag());
	RS=1;
	RW=0;
	E=0;
	_nop_();
	_nop_();
	P0=Data;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	E=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	E=0;
}

void lcd1602_WriteCmd(unsigned char Cmd)
{
	while(lcd1602_BusyFlag());
	RS=0;
	RW=0;
	E=0;
	_nop_();
	_nop_();
	P0=Cmd;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	E=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	E=0;
}

void lcd1602_ShowData(unsigned char Data,unsigned char pos)
{
	lcd1602_WriteCmd(pos|0x80);
	lcd1602_WriteData(Data);
}

void lcd1602_ShowString(unsigned char *String,unsigned char pos)
{
	lcd1602_WriteCmd(pos|0x80);
	while(*String!='\0')
	{
		lcd1602_WriteData(*String);
		String++;
	}
}

void init_lcd1602()
{
	lcd1602_WriteCmd(0x38);
	Delayms(1);
	lcd1602_WriteCmd(0x0c);
	Delayms(1);
	lcd1602_WriteCmd(0x06);
	Delayms(1);
	lcd1602_WriteCmd(0x01);
	Delayms(1);
}

