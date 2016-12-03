#define _STATE_MACHINE_C_

#include "..\\Includes.h"

void IdleFunc(){
}

void StartUpEnter()
{

}

void StartUpRun()
{

}

void StartUpTick()
{

}

unsigned char StartUpNext(){
	
		return state;
}

void SystemRun_Enter()
{

}

void SystemRun_Leave()
{

}
void SystemRun_Run()
{

}
void SystemRun_Tick()
{

}
unsigned char SystemRun_Next()
{

	return state;
}

void StandBy_Enter()
{	
	
}
void StandBy_Leave()
{

}
void StandBy_Run()
{

}
void StandBy_Tick()
{

}
unsigned char StandBy_Next()
{	
	return state;
}

code struct WorkState stateArray[]=
{
	{
		StartUp,
		StartUpEnter,
		IdleFunc,
		StartUpRun,
		StartUpTick,
		StartUpNext,	
	},
	{
		SystemRun,
		SystemRun_Enter,
		SystemRun_Leave,
		SystemRun_Run,
		SystemRun_Tick,
		SystemRun_Next,
	},	
	{
		StandBy,
		StandBy_Enter,
		StandBy_Leave,
		StandBy_Run,
		StandBy_Tick,
		StandBy_Next,
	},	
	
};

void getState(unsigned char st)
{	
	unsigned char x;		 	
	for(x=0;x<MaxState;x++){
		if(stateArray[x].state==st)	   {
			pWorkState=stateArray+x;
			break;
		}
	}	
}

void state_machine_init()
{
	state=StartUp;
	pWorkState=&stateArray[StartUp];
	pWorkState->Enter();
	force_new_state=0;	
}
void state_machine_engine()
{
	unsigned char newState;

	pWorkState->Run();
	newState=pWorkState->Next();
	if(force_new_state||(newState!=state)){
		force_new_state=0;
		pWorkState->Leave();
		getState(newState);	// state will change now

		prev_state=state;
		state=newState;	
		
		pWorkState->Enter();
	}
}
void state_machine_tick(){
	pWorkState->SysTickRun();
}


