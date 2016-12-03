#ifndef __STATE_H_
#define _STATE_H_

#ifdef _STATE_MACHINE_C_
	#define STATE_DEC
#else
	#define STATE_DEC	extern	
#endif

#define TIME_BASE			15

#define STATE_STABLE_COUNT		(100/TIME_BASE)
	
enum TxState{
	StartUp,
	SystemRun,
	StandBy,
	MaxState
};

typedef void (*StateFunc)(void);

typedef  unsigned char (*NextState)(void);

struct WorkState
{
	unsigned char state;
	StateFunc Enter;
	StateFunc Leave;
	StateFunc Run;
	StateFunc SysTickRun;
	NextState Next; 
};

STATE_DEC unsigned char  state,prev_state;
STATE_DEC bit force_new_state;
STATE_DEC  struct WorkState *pWorkState;

STATE_DEC void state_machine_init();
STATE_DEC void state_machine_engine();
STATE_DEC void state_machine_tick();
 
#endif

