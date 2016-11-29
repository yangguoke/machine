#include "..\\Includes.h"

void init_data()
{
   _Timer=0;
   seconds_gone=0;
}

void init_mcu()
{
	init_timer0();
	init_uart();
	init_data();
	enable_simple_key();
}

void main()
{

	init_mcu();
	while(1)
	{
	   	if(sys_tick_int)
		{
			sys_tick_int=0;
			#ifndef USE_RECEIVE
			check_simple_key();
			if(bDosimpleKey_Event)
			{
				bDosimpleKey_Event=0;
				test_led1=0;
				test_led2=0;
				test_led3=0;
				test_led4=0;
			}
			if(bDoLongsimpleKey_Event)
			{
				bDoLongsimpleKey_Event=0;
				test_led1=1;
				test_led2=1;
				test_led3=1;
				test_led4=1;
			}
			#endif
			#ifdef USE_RECEIVE
			read_data=I2C_byteread(0xaa,0x01);
			if(read_data!=0xff)
			{
				printf("%d\r\n",read_data);
			}
			#endif				
		}
		

		if(clksec_changed)
		{	
			clksec_changed=0;
			#ifndef USE_RECEIVE
			I2C_bytewrite(0xaa,0x01,0x03);
			#endif

		}
	
	}

}
