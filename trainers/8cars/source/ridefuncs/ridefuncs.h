//ridefuncs.h

#ifndef _RIDEFUNCS_
#define _RIDEFUNCS_

#include "../8cars.h"
#include "../rct2.h"

typedef enum
{	RF_REPAIR,RF_RELIABILITY,RF_RENEW,RF_10MINUTEINSPECTIONS,
	RF_EMPTYOFGUESTS,RF_GETTOTALRIDECOUNT,
}RIDEFUNCID;

/*
typedef enum
{	RF_RIDE
}RIDEFUNCCLASS
*/

int RepairRides();
int RenewRides();
int MakeRidesReliable();
int _10MinuteInspections();
DWORD GetRideCount();

typedef enum
{	TSF_ANYHEIGHT,
	TSF_10FOOTSHOPS,
	TSF_8CARSPERTRAIN,
	TSF_ULTRAEXCITINGRIDES,
	TSF_ULTRAINTENSERIDES,
	TSF_ULTRANAUSEATINGRIDES
} TRACKSPECFUNC;


int AnyHeightConstruction();
int _10FootShops();
int _8CarsPerTrain();

int UltraExcitingRides();
int UltraIntenseRides();
int UltraNauseatingRides();

DWORD getRideCount();

int UniformItemPricing();

#endif //_RIDEFUNCS_

SetRideHeightOffsets(RIDESTRUCT *ride,int heightoffset);
