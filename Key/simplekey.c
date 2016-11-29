
#define _SIMPLEKEY_C_

#include "..\include.h"

#ifdef USE_SIMPLE_KEY
#define SIMPLEYKEY_LONG_PRESS_TIME			1500
#define SIMPLEKEY_VERY_LONG_PRESS_TIME		6000
unsigned short simple_key_press_very_long_counting;
unsigned char simple_key_press_counting;
unsigned char simple_key_release_counting;

void init_simple_key()
{

	simple_key_release_counting=0;
	simple_key_press_counting=0;
	bDoLongsimpleKey_Event=0;
	bDosimpleKey_Event=0;
	simple_key_press_very_long_counting=0;
	bSimpleKey_very_long_Event=0;
	SimpleKey_PIN=1;
}

void enable_simple_key()
{
	init_simple_key();
	bSimpleyKeyEnabled=1;
}
void disable_simple_key()
{
	bSimpleyKeyEnabled=0;
}
void check_simple_key()
{	
	if(!SimpleKey_PIN)		/// mean key pressed
	{
		if(simple_key_press_counting<(2500/SCAN_KEY_TIME_BASE))
		{
			simple_key_press_counting++;
			if(simple_key_press_counting>=(150/SCAN_KEY_TIME_BASE))
			{
				simple_key_release_counting=0;
			}
			if(simple_key_press_counting==(SIMPLEYKEY_LONG_PRESS_TIME/SCAN_KEY_TIME_BASE))
			{
				/// the key pressed more than 1.2seconds, just, pump out the simple key
				bDoLongsimpleKey_Event=1;
				bDosimpleKey_Event=0;
			}
		}
		if(simple_key_press_very_long_counting<(SIMPLEKEY_VERY_LONG_PRESS_TIME/SCAN_KEY_TIME_BASE+10))
		{
			simple_key_press_very_long_counting++;
			if(simple_key_press_very_long_counting==(SIMPLEKEY_VERY_LONG_PRESS_TIME/SCAN_KEY_TIME_BASE))
			{
				bSimpleKey_very_long_Event=1;
				bDoLongsimpleKey_Event=0;
				bDosimpleKey_Event=0;
			}
		}
	}
	else		//	else the key is released
	{
		if(simple_key_release_counting<(300/SCAN_KEY_TIME_BASE))
		{
			simple_key_release_counting++;
			if(simple_key_release_counting>=(100/SCAN_KEY_TIME_BASE))
			{
				if(simple_key_press_counting>=((SIMPLEYKEY_LONG_PRESS_TIME-50)/SCAN_KEY_TIME_BASE)
				//	&&simple_key_press_counting<((SIMPLEYKEY_LONG_PRESS_TIME+100)/SCAN_KEY_TIME_BASE)
				)
				{
					if(simple_key_press_very_long_counting<(SIMPLEKEY_VERY_LONG_PRESS_TIME/SCAN_KEY_TIME_BASE))
						//bDoLongsimpleKey_Event=1;
					bDosimpleKey_Event=0;
				}
				else if(simple_key_press_counting>(150/SCAN_KEY_TIME_BASE)
						&&simple_key_press_counting<((SIMPLEYKEY_LONG_PRESS_TIME-50)/SCAN_KEY_TIME_BASE)
				)
				{
					// when >100, then means the key processed,else the key may not be processed
					bDosimpleKey_Event=1;
					bDoLongsimpleKey_Event=0;
				}
				simple_key_press_counting=0;
				simple_key_press_very_long_counting=0;
			}
		}
	}
}
#endif

