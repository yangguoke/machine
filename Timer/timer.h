#ifndef TIMER_H
	#define TIMER_H

#ifdef _TIMER_C_
#define _TIMER_DEF
#else
#define _TIMER_DEF extern
#endif

_TIMER_DEF unsigned char seconds_gone;
_TIMER_DEF unsigned char _Timer;		
_TIMER_DEF bit clksec_changed;
_TIMER_DEF bit sys_tick_int;

_TIMER_DEF void init_timer0();
_TIMER_DEF void timer0();	
 _TIMER_DEF void Delayms(unsigned int n);
#endif
