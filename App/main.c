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
		}
		

		if(clksec_changed)
		{	
			clksec_changed=0;
			
			//printf("%d\r\n",clksec_changed);					
		}
	
	}

}
