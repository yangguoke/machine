#ifndef CONFIG_H
	#define CONFIG_H

#define _Fosc_  12000000
#define _BaudRate_ 9600

#define TIME_RELOAD_25MS (65536-25000)
#define SCAN_KEY_TIME_BASE 25
#define USE_SIMPLE_KEY
#define USE_RECEIVE


 sbit SimpleKey_PIN=P1^7;
 #ifdef USE_RECEIVE
 sbit IIC_DEV_01_SCL=P1^0;
 sbit IIC_DEV_01_SDA=P1^1;
 #else
  sbit test_led1=P1^0;
 sbit test_led2=P1^1;	 
 sbit test_led3=P1^2;
 sbit test_led4=P1^3;
 sbit IIC_DEV_01_SCL=P2^3;
 sbit IIC_DEV_01_SDA=P2^4;
 #endif
#endif
