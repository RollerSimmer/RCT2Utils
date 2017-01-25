#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "weather.h"
#include "../8cars.h"
#include "../rct2.h"
#include "../resource.h"
#include <stdtypes.h>

WEATHER 
	WS_SUNNY={1920,0,0,23,23,0,0,0,0,0,0},
	WS_HOT={1920,0,0,37,37,0,0,0,0,0,0},
	WS_FREEZE={1920,1,1,0,0,0,0,1,1,0,0},
	WS_COLD={1920,1,1,8,8,0,0,1,1,0,0},
	WS_THUNDERSTORM={1920,5,5,16,16,2,2,2,2,2,2},
	WS_HEAVYRAIN={1920,4,4,16,16,0,0,2,2,2,2},
	WS_SHOWER={1920,3,3,16,16,0,0,1,1,1,1};

/*
Code Stream for set weather (2.01.028)

66FF0D48A73C01

Code Stream for set weather (addresses masked with 0x00):

66FF0000000000

(optionally replace 00000000's with address of weather timer)

Replace with:

EB059090909090
*/
char FREEZEWEATHER_CODE_TARGET[]=
	"\x66\xFF\x0D\x00\x00\x00\x00";

#define TIMER_ADDR_STRPOS 3

char FREEZEWEATHER_CODE_REPLACE[]=
	"\xEB\x05\x90\x90\x90\x90\x90";

int FreezeWeather_Init()
{

	WEATHER *weather;

	weather=RCT2_ADDR_WEATHER;
	
	*(DWORD*)(&(FREEZEWEATHER_CODE_TARGET[TIMER_ADDR_STRPOS]))=
		&(weather->WeatherTimer);
}

int FreezeWeather()
{
	static int 
		init=FALSE,freezeActive=FALSE;
	static DWORD codeReplaceAddr=0;

	int retv;
	DWORD retaddr;

	if(!init)
	{
		FreezeWeather_Init();
		init=TRUE;
	}

	if(!freezeActive&&((char*)codeReplaceAddr==NULL))
	{
		retaddr=	
			WinPatchMem
			(	mainWindow,RCT2_TITLE,
				FREEZEWEATHER_CODE_TARGET,
				FREEZEWEATHER_CODE_REPLACE,
				FALSE,0,sizeof(FREEZEWEATHER_CODE_TARGET)-1
			);
		retv=retaddr!=0;		
		freezeActive=TRUE;
		if(retv)
			codeReplaceAddr=retaddr-strlen(FREEZEWEATHER_CODE_TARGET);
		else
			codeReplaceAddr=0;//null
	}
	else if((char*)codeReplaceAddr!=NULL)
	{	
		if(freezeActive)
		{
			retv=
				WinWrite
				(	mainWindow,RCT2_TITLE,
					codeReplaceAddr,
					FREEZEWEATHER_CODE_TARGET,
					sizeof(FREEZEWEATHER_CODE_TARGET)-1
				);
			freezeActive=FALSE;
		}
		else 
		{
			retv=
				WinWrite
				(	mainWindow,RCT2_TITLE,
					codeReplaceAddr,
					FREEZEWEATHER_CODE_REPLACE,
					sizeof(FREEZEWEATHER_CODE_TARGET)-1
				);
				freezeActive=TRUE;
		}

	}
	else 
	{
		retaddr=	
			WinPatchMem
			(	mainWindow,RCT2_TITLE,
				FREEZEWEATHER_CODE_REPLACE,
				FREEZEWEATHER_CODE_TARGET,
				FALSE,0,sizeof(FREEZEWEATHER_CODE_TARGET)-1
			);
		retv=retaddr!=0;		
		freezeActive=FALSE;
		if(retv)
			codeReplaceAddr=retaddr-strlen(FREEZEWEATHER_CODE_TARGET);
		else
			codeReplaceAddr=0;//null
	}

	if(freezeActive)
		CheckMenuItem(mainMenu,ID_WEATHER_FREEZEWEATHER,MF_CHECKED);
	else
		CheckMenuItem(mainMenu,ID_WEATHER_FREEZEWEATHER,MF_UNCHECKED);

	return retv;
}

