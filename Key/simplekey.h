#ifndef _SIMPLEKEY_H_
	#define _SIMPLEKEY_H_
#ifdef _SIMPLEKEY_C_
#define _SIMPLEKEY_DEF_
#else
#define _SIMPLEKEY_DEF_ extern 
#endif

_SIMPLEKEY_DEF_ bit 	bDoLongsimpleKey_Event;
_SIMPLEKEY_DEF_ bit 	bDosimpleKey_Event;
_SIMPLEKEY_DEF_ bit 	bSimpleKey_very_long_Event;
_SIMPLEKEY_DEF_ bit  	bSimpleyKeyEnabled;

#ifdef USE_STANDBY_KEY
_SIMPLEKEY_DEF_ bit  	bEventStandByKey;
#endif

#ifdef USE_SECOND_SIMPLE_KEY
_SIMPLEKEY_DEF_ bit 	x_bDoLongsimpleKey_Event;
_SIMPLEKEY_DEF_ bit 	x_bDosimpleKey_Event;
_SIMPLEKEY_DEF_ bit 	x_bSimpleKey_very_long_Event;
_SIMPLEKEY_DEF_ bit  	x_bSimpleyKeyEnabled;
#endif

_SIMPLEKEY_DEF_ void init_simple_key();
_SIMPLEKEY_DEF_ void enable_simple_key();
_SIMPLEKEY_DEF_ void disable_simple_key();
_SIMPLEKEY_DEF_ void check_simple_key();

#endif
