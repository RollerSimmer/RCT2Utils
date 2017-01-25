//GUESTFUNCS.H

//header
#ifndef _GUESTFUNCS_
#define _GUESTFUNCS_

typedef enum
{
	TRAMT_SMALL		=0X20,
	TRAMT_MEDIUM	=0X40,
	TRAMT_LARGE		=0X80,
	TRAMT_HUGE		=0XFF
}TRAMTYPE;

int Tram_Large();
int Tram_Small();
int Tram_Medium();
int Tram_Huge();

#endif //_GUESTFUNCS_
// /header 
