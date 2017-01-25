//ridefuncs.c

#include "ridefuncs.h"
#include "..\8cars.h"

#include <windows.h> 
#include <objdat.h>

int RideFunc(BYTE lowI,BYTE highI,RIDEFUNCID func)
{

	RIDESTRUCT ride;
	RIDESTRUCTARRAY* ridePtrBase;
	BYTE i,stationI;
	int gameAbsMonth;
	DWORD usedRideCount=0; 

	i=lowI;

	ridePtrBase=RCT2_ADDR_RIDES;

	if(!WinRead(mainWindow,RCT2_TITLE,&gameAbsMonth,RCT2_ADDR_ABSMONTH,2))
		return FALSE;

	for(i=lowI;i<=highI;i++)
	{
		WinRead
		(	mainWindow,RCT2_TITLE,&ride,
			&((*ridePtrBase)[i]),sizeof(ride)
		);		

		switch(func)
		{
		case RF_REPAIR:
			ride.rideStatusFlags&=~RSF_BROKENDOWN;
			ride.downtime=0;
			ride.reliability=100;
			break;
		case RF_RELIABILITY:		
			ride.reliability=100;
			break;
		case RF_RENEW:
			ride.absBuiltMonth=gameAbsMonth;
			ride.reliability=100;
			break;

		case RF_10MINUTEINSPECTIONS:
			ride.inspectionFrequency=INSPECT_10MIN;
			break;
		case RF_EMPTYOFGUESTS:
			if(ride.trackType!=0x43) //mini golf
			{
				ride.numGuestsOnRide=0; 
				#define MAXNUMSTATIONS 4
				for(stationI=0;stationI<MAXNUMSTATIONS;stationI++)
				{
					ride.lastQueueGuestIndex[stationI]=RCT2_WORD_EMPTY;
					ride.guestsInQueue[stationI]=0;
				}			
			}
			break;
		case RF_GETTOTALRIDECOUNT:
			if(ride.trackType!=RCT2_BYTE_EMPTY)
				++usedRideCount;
			break;
		}

		WinWrite
		(	mainWindow,RCT2_TITLE,&((*ridePtrBase)[i]),
			&ride,sizeof(ride)
		);		
	}

	switch(func)
	{
	case RF_GETTOTALRIDECOUNT:
		return usedRideCount;
	default:
		return TRUE;
	}
}

int RepairRides()
{	return RideFunc(0,254,RF_REPAIR);
}

int RenewRides()
{	return RideFunc(0,254,RF_RENEW);
}

int MakeRidesReliable()
{	return RideFunc(0,254,RF_RELIABILITY);
}

int _10MinuteInspections()
{	return RideFunc(0,254,RF_10MINUTEINSPECTIONS);
}

//=========

SetRideHeightOffsets(RIDESTRUCT *ride,int heightoffset)
{
	int i;
	heightoffset=heightoffset*2;
	for (i=0;i<4;i++)
		if(ride->stationHeights[i]!=RCT2_BYTE_EMPTY)
			ride->stationHeights[i]+=heightoffset;
	return TRUE;
}

#define NUMTRACKTYPESLOTS (0X5A+1)

int IsShopTrackType(BYTE trackType)
{
	BYTE i;
	for (i=0;i<RCT2_NUMSHOPTRACKTYPES;i++)
	{
		if(RCT2_SHOPTRACKTYPES[i]==trackType)
			return TRUE;
	}
	return FALSE;
}


int EditTrackSpecs(TRACKSPECFUNC tsfunc)
{
	int i;

	TRACKSPECSTRUCT trackSpecs[NUMTRACKTYPESLOTS];

	TYPE0HEADER	*rideObjPtrs[128], curRideoObj;
	BYTE*specAddr=RCT2_ADDR_TRACKTYPECONSTRUCTOP;

	if(!WinRead(mainWindow,RCT2_TITLE,&trackSpecs,
			specAddr,sizeof(trackSpecs))
	)
		return FALSE;		
	
	for (i=0;i<NUMTRACKTYPESLOTS;i++)
	{	switch (tsfunc)
		{
		case TSF_ANYHEIGHT:
			trackSpecs[i].MaxHeight=0xff;
			break;
		case TSF_10FOOTSHOPS:
			if (IsShopTrackType(i))
			{	trackSpecs[i].ClearanceBase=4<<3;
			}
			break;
		case TSF_8CARSPERTRAIN:
			//if((BYTE)trackSpecs[i].MaxTrainLength<0x7f)
				trackSpecs[i].MaxTrainLength=0xff;
			break;
		case TSF_ULTRAEXCITINGRIDES:
			break;
		case TSF_ULTRAINTENSERIDES:
			break;
		case TSF_ULTRANAUSEATINGRIDES:
			break;
		default:
			break;
		}
	}

	if(!WinRead(mainWindow,RCT2_TITLE,rideObjPtrs,
		RCT2_ADDR_RIDEOBJECTFILEPOINTERS,sizeof(rideObjPtrs))
	)
		return FALSE;		

	for(i=0;i<RCT2_OBJMAX_RIDES;i++)
	{
		if(rideObjPtrs[i]!=0xFFFFFFFF)
		{
			WinRead
			(	mainWindow,RCT2_TITLE,&curRideoObj,rideObjPtrs[i],
				sizeof(curRideoObj)
			);

			switch(tsfunc)
			{
			case TSF_ANYHEIGHT:
				curRideoObj.maxTrackHeight=0xff;
				break;
			case TSF_10FOOTSHOPS:
				break;
		
			case TSF_8CARSPERTRAIN:
				curRideoObj.maxCarsPerTrain
					=max(curRideoObj.maxCarsPerTrain,15);
				goto CASE_TSFCHANGECARSPERTRAIN;
			CASE_TSFCHANGECARSPERTRAIN:
				curRideoObj.minCarsPerTrain
					=min(curRideoObj.minCarsPerTrain,1);
				break;

			case TSF_ULTRAEXCITINGRIDES:
				curRideoObj.excitementFactor=HIGHEINRATING;
				break;
			case TSF_ULTRAINTENSERIDES:
				curRideoObj.intensityFactor=HIGHEINRATING;
				break;
			case TSF_ULTRANAUSEATINGRIDES:
				curRideoObj.nauseaFactor=HIGHEINRATING;
				break;
			default:
				break;
			}

			WinWrite 
			(	mainWindow,RCT2_TITLE,rideObjPtrs[i],&curRideoObj,
				sizeof(curRideoObj)
			);
		}
	}

	WinWrite
	(	mainWindow,RCT2_TITLE,
		specAddr,
		&trackSpecs,sizeof(trackSpecs)
	);

	return TRUE;
}

int AnyHeightConstruction()
{
	return EditTrackSpecs(TSF_ANYHEIGHT);
	




}

int _10FootShops()
{
	return EditTrackSpecs(TSF_10FOOTSHOPS);
}

int _8CarsPerTrain()
{
	return EditTrackSpecs(TSF_8CARSPERTRAIN);
}	

int UltraExcitingRides()
{
	return EditTrackSpecs(TSF_ULTRAEXCITINGRIDES);
}	

int UltraIntenseRides()
{
	return EditTrackSpecs(TSF_ULTRAINTENSERIDES);
}	

int UltraNauseatingRides()
{
	return EditTrackSpecs(TSF_ULTRANAUSEATINGRIDES);
}	

int _EmptyRidesOfGuests()
{	return RideFunc(0,254,RF_EMPTYOFGUESTS);
}

DWORD GetRideCount()
{
	return RideFunc(0,254,RF_GETTOTALRIDECOUNT);
}

//====================================
int UniformItemPricing()
{	
	DWORD flags=0xffffffff;
	BYTE *ptr;
	
	if(!WinWrite(mainWindow,RCT2_TITLE,ptr=RCT2_ADDR_SAMEPRICEFLAGS1,&flags,sizeof(flags)))
		return FALSE;
	WinWrite(mainWindow,RCT2_TITLE,ptr=RCT2_ADDR_SAMEPRICEFLAGS2,&flags,sizeof(flags));

	return TRUE;
}
