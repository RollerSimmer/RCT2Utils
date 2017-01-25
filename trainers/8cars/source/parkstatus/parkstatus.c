#include "../rct2.h"
#include "parkstatus.h"
#include "../process/process.h"
#include "../8cars.h"
#include <stdtypes.h>
#include "../ridefuncs/ridefuncs.h"
#include "../mapfuncs/mapfuncs.h"

WORD CompressAbsMonth(WORD month,WORD year)
{	WORD absmonth;
	__asm
	{	mov ax,[month]
		mov dx,[year]
		shl dx,3
		and ax,7
		or ax,dx
		mov [absmonth],ax
	}
	return absmonth;
}
WORD ExtractAbsMonth(WORD *month,WORD *year,WORD absmonth)
{	
	__asm
	{	
		mov ax,[absmonth]
		mov dx,ax
		shr dx,3
		and ax,7
		mov edi,[month]
		mov [edi],ax
		mov edi,[year]
		mov [edi],dx
	}
	return month;
}


int IncDate(short dayInc,short monthInc,short yearInc)
{	
	short 
		day,month,year;

	GetDate(&day,&month,&year);

	day+=dayInc;
	if(day<0)
		--month;
	month=month+(day/RCT2_DAYSPERMONTH);
	day%=RCT2_DAYSPERMONTH;
	if(day<0)
		day+=RCT2_DAYSPERMONTH;

	month+=monthInc;
	if(month<0)
		--year;
	year=year+(month/RCT2_MONTHSPERYEAR);
	month%=RCT2_MONTHSPERYEAR;

	year+=yearInc;
	SetDate(day,month,year);
}

int SetDate(short day,short month,short year)
{	
	DATESTRUCT date;

	date.absmonth=CompressAbsMonth(month,year);
	
	date.day=day*RCT2_UNITSPERDAY;
	
	WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_ABSMONTH,&date,sizeof(date));	
}

int GetDate(short *day,short *month,short *year)
{	
	DATESTRUCT date;	
	
	WinRead(mainWindow,RCT2_TITLE,&date,RCT2_ADDR_ABSMONTH,sizeof(date));

	ExtractAbsMonth(month,year,date.absmonth);
	
	*day=date.day/RCT2_UNITSPERDAY;
}

int SetCurrentAttendance(WORD attendance)
{
	WinWrite
	(	mainWindow,RCT2_TITLE,RCT2_ADDR_NUMGUESTSINPARK,
		&attendance,sizeof(attendance)
	);
}

WORD GetCurrentAttendance()
{
	WORD attendance;

	WinRead
	(	mainWindow,RCT2_TITLE,&attendance,
		RCT2_ADDR_NUMGUESTSINPARK,sizeof(attendance)
	);
	return attendance;
}

//-- Count Objects --

DisplayCount(char *objectTypeString,DWORD curCount,DWORD maxCount)
{
	#define DISPLAYFORMAT "There are %d %s data structures in your park; there is a max of %d.  You have %d left to use"
	char displayString[256];

	sprintf(displayString,DISPLAYFORMAT,curCount,objectTypeString,maxCount,maxCount-curCount);
	MessageBox(mainWindow,displayString,"Message",MB_OK);
}

CountRides()
{
	#define MAXRIDES 255
	DisplayCount("ride",GetRideCount(),MAXRIDES);
}

CountMapData()
{
	DisplayCount("map",GetUsedMapDataStructCount(),MAPDATASTRUCTURES_MAX);
}

CountSprites()
{
	SPRITESTATS spritestats;

	memset(&spritestats,0,sizeof(spritestats));
	//	NUMSPRITES 
	WinRead
	(	mainWindow,
		RCT2_TITLE,&spritestats,RCT2_ADDR_SPRITESTATS,
		sizeof(SPRITESTATS)
	);

	DisplayCount("sprite",(DWORD)NUMSPRITES-spritestats.statsA.availSprites,NUMSPRITES);
}






