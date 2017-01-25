#include "guestfuncs.h"
#include "../8cars.h"
#include "../rct2.h"
#include <stdtypes.h>

//#define TEST_TRAM
#undef TEST_TRAM

int Tram(TRAMTYPE tramtype)
{
	BYTE guestGenProb=tramtype;
	char outStr[128];

	#ifdef TEST_TRAM
		sprintf(outStr,"Tram:\n\rRct2Version=%d &GAMEDATA:base=0x%x varaddr=0x%x",0,RCT2_ADDR_GAMEDATABASE,&RCT2_ADDR_GAMEDATABASE);
		MessageBox(NULL,outStr,"Message",MB_ICONEXCLAMATION|MB_OK|MB_SYSTEMMODAL);
	#endif TEST_TRAM

	return 
		WinWrite
		(	mainWindow,RCT2_TITLE,
			RCT2_ADDR_GUESTGENPROBABILITY,&guestGenProb,
			sizeof(guestGenProb)
		);
}

int Tram_Small()
{	return Tram(TRAMT_SMALL);
}

int Tram_Medium()
{	return Tram(TRAMT_MEDIUM);
}

int Tram_Large()
{	return Tram(TRAMT_LARGE);
}

int Tram_Huge()
{	return Tram(TRAMT_HUGE);
}
