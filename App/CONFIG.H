#ifndef CONFIG_H
	#define CONFIG_H

#define _Fosc_  12000000
#define _BaudRate_ 9600

#define TIME_RELOAD_25MS (65536-25000)
#define SCAN_KEY_TIME_BASE 25
#define USE_SIMPLE_KEY

 sbit test_led1=P1^0;
 sbit test_led2=P1^1;	 
 sbit test_led3=P1^2;
 sbit test_led4=P1^3;

 sbit SimpleKey_PIN=P1^7;
#endif
