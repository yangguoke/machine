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
		}
		

		if(clksec_changed)
		{	
			clksec_changed=0;
			printf("%d\r\n",);					
		}
	
	}

}