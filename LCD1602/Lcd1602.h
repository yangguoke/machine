#ifndef LCD1602_H
	#define LCD1602_H

#ifdef _LCD1602_C_
#define _LCD1602_DEF
#else
#define _LCD1602_DEF extern
#endif

sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;

_LCD1602_DEF void init_lcd1602();
_LCD1602_DEF void lcd1602_WriteData(unsigned char Data);
_LCD1602_DEF void lcd1602_WriteCmd(unsigned char Cmd);
_LCD1602_DEF void lcd1602_ShowData(unsigned char Data,unsigned char pos);
_LCD1602_DEF void lcd1602_ShowString(unsigned char *String,unsigned char pos);
#endif

