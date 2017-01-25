//weather.h


#ifndef _WEATHER_
#define _WEATHER_

#include "..\rct2.h"

WEATHER 
	WS_SUNNY,
	WS_HOT,
	WS_FREEZE,
	WS_COLD,
	WS_THUNDERSTORM,
	WS_HEAVYRAIN,
	WS_SHOWER;

#define SETWEATHER(weatherStruct)		\
	WinWrite	\
	(	mainWindow,RCT2_TITLE,RCT2_ADDR_WEATHER,&weatherStruct,	\
		sizeof(WEATHER)		\
	)

int FreezeWeather();

#endif //_WEATHER_
