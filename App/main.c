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
	
	I2C_bytewrite(0xa0,0x00,0x12);
	printf("%d\r\n",I2C_byteread(0xa0,0x00));
	state_machine_init();
	while(1)
	{
	   	if(sys_tick_int)
		{
			sys_tick_int=0;
			check_simple_key();
			state_machine_tick();
			state_machine_engine();
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
		}
	
	}

}
