#define _TIMER_C_
#include "..\\Includes.h"

void init_timer0()
{
	TMOD|=0x01;
	TL0=TIME_RELOAD_25MS&0xff;
	TH0=(TIME_RELOAD_25MS>>8)&0xff;
	TR0=1;
	EA=1;
	ET0=1;
}

void timer0() interrupt	1
{
   	TL0=TIME_RELOAD_25MS&0xff;
	TH0=(TIME_RELOAD_25MS>>8)&0xff;
	_Timer++;
	sys_tick_int=1;
	if(_Timer==39)
	{
		_Timer=0;
		clksec_changed=1;
		seconds_gone++;
	}
}
 void Delayms(unsigned int n)
 {
	unsigned int i,j;
	for(j=n;j>0;j--)
	for(i=112;i>0;i--);
 }