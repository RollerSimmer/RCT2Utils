#include"../stdafx.h"
#include "rideConvert.H"
#include"426_ride_trackVehiConvert.h"
#include"colorConvert.h"
#include"426_compileflags.h"

#include <codeshortcuts.h>
#include <string.h>

#define TT_EMPTYRIDESTRUCT ((BYTE)(0xFF))

ConvertRide(RCT2_RIDESTRUCT *r6p,SV4_RIDESTRUCT *r4p);
ResetRide(RCT2_RIDESTRUCT&r6);
RideColorConvert(RCT2_RIDESTRUCT&r6,SV4_RIDESTRUCT r4);

ConvertRides
(	
	RCT2_RIDESTRUCTARRAY *s6_rides,SV4_RIDESTRUCTARRAY *s4_rides,
	WORD *s6_numRideStructsUsed,WORD s4_numRideStructsUsed
)
{
	#define RCTX_NUMRIDES 255

	int r64i,usedRideSlotTally;

	*s6_numRideStructsUsed=s4_numRideStructsUsed;
	usedRideSlotTally=0;

	//#define sz(a) (sizeof((a)))
	#define r6 ((*s6_rides)[r64i])
	#define r4 ((*s4_rides)[r64i])
	#define ms0(a) (memset(&(a),0,sz(a)))
	DoRidesConvert:
	{
		for_i0(r64i,RCTX_NUMRIDES)
		{
						
			if
			(
			(r4.trackType!=TT_EMPTYRIDESTRUCT)
			||
			(usedRideSlotTally<=s4_numRideStructsUsed)
			)
			{
				usedRideSlotTally++;
				ConvertRide(&r6,&r4);
				ResetRide(r6);
			}
			else
			{
				ms0(r6);
				r6.trackType=TT_EMPTYRIDESTRUCT;				
			}
		}
	}
	#undef r6
	#undef r4
	#undef ms0
	#undef sz

}

cr_TrackAndVehicleConvert
(	
BYTE&t6,BYTE&v6,
BYTE t4,BYTE v4
)
;

ConvertRide(RCT2_RIDESTRUCT *r6p,SV4_RIDESTRUCT *r4p)
{
	#define sz(a) (sizeof(a))
	#define r6 (*r6p)
	#define r4 (*r4p)
	#define ms0(a) (memset(&(a),0,sz(a)))
	#define equ64s(a) (r6.a=r4.a)
	#define mm64(a,b) (memmove(&(r6.a),&(r4.b),sz(r6.a)))
	#define mma64(a,b) (memmove(&(r6.a),&(r4.b),sz(r6.a)))
	#define mm64s(a) (mm64(a,a))
	#define mma64s(a) (mma64(a,a))

	DoRideConvert:
	{

		ms0(r6);

		//convert individual fields from SV4 to SV6
		
		cr_TrackAndVehicleConvert
		(
		r6.trackType,r6.vehiObjID
		,r4.trackType,r4.vehiObjID
		)
		;

		memset(&(r6.rideStatusFlags),0,sz(r6.rideStatusFlags));
		memmove(&(r6.rideStatusFlags),&(r4.rideStatusFlags),sz(r4.rideStatusFlags));

		equ64s(opmode);
		equ64s(colorScheme);
		
		////mma64(0 /*replace*/,vehicolors1);

		////mma64(0 /*replace*/,unk0x01E);
				
		equ64s(ridestatus);
		

		equ64s(nameStringIndex);
		equ64s(stringNumerator);
		mma64s(overallViewFocus);
		mma64s(stationFoci);
		mma64s(stationHeights);
		mma64s(stationLengths);
		mma64s(stationSignal);
		mma64s(trainsInLoadingPos);
		mma64s(rideEntrances);
		mma64s(rideExits);
		mma64s(lastQueueGuestIndex);
		mma64s(guestsInQueue);
		mma64s(TrainSpriteIndexes);
		equ64s(DepartureControlFlags);
		equ64s(amtStations);
		equ64s(amtTrains);
		equ64s(amtCarsPerTrain);
		////mma64(0 /*replace*/,unk0x07A);
		equ64s(maxTrains);
		////mma64(0 /*replace*/,unk0x07D);
		equ64s(minWait);
		equ64s(maxWait);
		equ64s(launchSpeed);
		////mma64(0 /*replace*/,unk0x081);
		equ64s(dataLoggingIndex);
		equ64s(specialTrackElements);
		////mma64(0 /*replace*/,unk0x086);
		equ64s(maxspeedLo);
		equ64s(maxspeedHi);
		equ64s(avgspeedLo);
		equ64s(avgspeedHi);
		////mma64(0 /*replace*/,unk0x090);
		mma64s(rideLengths);
		mma64s(rideTimes);
		equ64s(maxPosVertGs);
		equ64s(maxNegVertGs);
		equ64s(maxLatGs);
		//mma64(0 /*replace*/,unk0x0B2);
		//equ64s(0 /*replace*/,unk_curvatureRelated);
		//mma64(0 /*replace*/,unk0x0C0);
		//mma64(0 /*replace*/,unk0x0C2);
		equ64s(inversions);
		equ64s(drops);
		//mma64(0 /*replace*/,unk0x0C6);
		equ64s(highDrop);
		//equ64s(0 /*replace*/,unk_undergroundTrackLength);
		//mma64(0 /*replace*/,unk0x0CC);
		//mma64(0 /*replace*/,unk0x0CE);
		//mma64(0 /*replace*/,unk0x0CF);
		equ64s(curCustomerCount);
		equ64s(customerCountTimer);
		mma64s(lastCustomerCounts);
		equ64s(ticketPrice);
		//mma64(0 /*replace*/,unk0x0EA);
		equ64s(excitement);
		equ64s(intensity);
		equ64s(nausea);
		//mma64(0 /*replace*/,unk0x0F6);
		equ64s(satisfaction);
		//mma64(0 /*replace*/,unk0x0FB);
		equ64s(totalCustomers);
		equ64s(totalProfit);
		//equ64s(0 /*replace*/,curPopularity);
		//equ64s(0 /*replace*/,guestThoughtCount);
		//equ64s(0 /*replace*/,guestGoodThoughtCount);
		equ64s(numGuestsOnRide);
		//mma64(0 /*replace*/,unk0x10C);
		equ64s(absBuiltMonth);
		equ64s(runningCost);
		//mma64(0 /*replace*/,unk0x134);
		equ64s(breakdownType);
		//mma64(0 /*replace*/,unk0x144);
		equ64s(reliabilityCountdown);
		equ64s(reliability);
		//equ64s(0 /*replace*/,fill148);
		equ64s(downtime);
		equ64s(inspectionFrequency);
		equ64s(timeSinceLastInspection);
		mma64s(unk0x14C);
		//equ64s(0 /*replace*/,hourlyIncome);
		//equ64s(0 /*replace*/,profit);
		equ64s(queuetime);
		//mma64(0 /*replace*/,unk0x169);
		mma64s(trackColorSchemes);
		equ64s(rideMusic);
		equ64s(stationTheme);
		//mma64(0 /*replace*/,unk0x17A);

		//mma64(unk0x002,0 /*replace*/);
		//mm64(vehicolors1,0 /*replace*/);
		//mma64(unk0x046,0 /*replace*/);
		//mma64(unk0x082,0 /*replace*/);
		//equ64(reqAmtTrains,0 /*replace*/);
		//equ64(reqAmtCarsPerTrain,0 /*replace*/);
		//mma64(unk0x0CD,0 /*replace*/);
		//mma64(unk0x0D1,0 /*replace*/);
		//mma64(unk0x0D6,0 /*replace*/);
		//mma64(unk0x0E0,0 /*replace*/);
		//mma64(unk0x102,0 /*replace*/);
		//mma64(unk0x116,0 /*replace*/);
		//mma64(unk0x118,0 /*replace*/);
		//mma64(unk0x13A,0 /*replace*/);
		//mma64(unk0x146,0 /*replace*/);
		//equ64(unk_maintenanceRelatedFlag,0 /*replace*/);
		//mma64(unk0x14E,0 /*replace*/);
		//equ64(popularityOutOf25,0 /*replace*/);
		//equ64(pop_TotalThoughtCountTo25,0 /*replace*/);
		//equ64(pop_GoodThoughtCountOutOf25,0 /*replace*/);
		//equ64(currentMusicPlaying,0 /*replace*/);
		//mma64(unk0x15D,0 /*replace*/);
		//mma64(unk0x184,0 /*replace*/);
		//equ64(mechanicStatus,0 /*replace*/);
		//equ64(nearestHandman_spriteIndex,0 /*replace*/);
		//mma64(unk0x190,0 /*replace*/);
		//mma64(unk0x194,0 /*replace*/);
		//equ64(unk_cheatDetection,0 /*replace*/);
		//equ64(unk_breakDownTimer,0 /*replace*/);
		//mma64(unk0x19D,0 /*replace*/);
		//equ64(onRidePhotosSold,0 /*replace*/);
		//mma64(unk0x1AA,0 /*replace*/);
		//equ64(unk_hasntBeenFixedTimer,0 /*replace*/);
		//mma64(unk0x1AE,0 /*replace*/);
		//mma64(unk0x1B9,0 /*replace*/);

		RideColorConvert(r6,r4);

	}
//	#undef
	#undef r6
	#undef r4
	#undef ms0
	#undef equ64s
	#undef mm64s
	#undef mma64s
	#undef mm64
	#undef mma64
//	#undef sz
}

ResetRide(RCT2_RIDESTRUCT&r6)
{
	int i;
	SV6_RIDESTATUSFLAGS*rf;

	rf=&r6.rideStatusFlags;

	r6.ridestatus=0;//0=closed

	//flags
	{
	rf->brokenDown=0;
	rf->crashed=0;
	rf->doStationPass=0;
	rf->everBeenOpened=0;
	rf->playMusic=0;
	rf->ridePreserved=0;
	rf->sixFlafsDesign=0;
	rf->setAfterBreakdown=0;
	rf->dontShowRawStats=0;
	rf->indestructibleTrackPiecesPresent=0;
	rf->playMusic=0;
	rf->ridePreserved=0;
	rf->tested=0;
	rf->testInProgress=0;
	rf->trainOnTrack=0;
	}

	r6.dataLoggingIndex=RCTX_BYTE_EMPTY;
	r6.breakdownType=RCTX_BYTE_EMPTY;
	r6.absBuiltMonth=0;
	r6.curCustomerCount=0;
	r6.currentMusicPlaying=RCTX_BYTE_EMPTY;
	r6.avgspeedHi=0;
	r6.avgspeedLo=0;
	r6.drops=0;
	
	memset(r6.guestsInQueue,0,sz(r6.guestsInQueue));
	
	memset
	(
	&r6.lastQueueGuestIndex[0]
	,RCTX_BYTE_EMPTY
	,sz(r6.lastQueueGuestIndex)
	);


	r6.favRideGuestCount=0;
	r6.downtime=0;
	r6.excitement=RCTX_WORD_EMPTY;
	r6.intensity=0;
	r6.nausea=0;
	r6.drops=0;

	for_i0(i,4){r6.guestsInQueue[i]=0;}
	
	r6.highDrop=0;
	r6.inversions=0;

	for_i0(i,10){r6.lastCustomerCounts[i]=0;}
	
	for_i0(i,4){r6.lastQueueGuestIndex[i]=RCTX_BYTE_EMPTY;}


	//r6.launchSpeed=0;
	r6.liftChainSpeed=5;
	r6.numCircuits=1;
	r6.numGuestsOnRide=0;
	r6.onRidePhotosSold=0;
	r6.queuetime=0;
	r6.reliability=0;
	
	for_i0(i,4){r6.rideLengths[i]=0;}
	
	r6.rideMusic=0x11;
	
	for_i0(i,4){r6.rideTimes[i]=0;}
	
	r6.runningCost=0;
	r6.satisfaction=0;

	for_i0(i,4)
	{	if(r6.stationLengths[i]>0)r6.stationSignal[i]=1;	
		else r6.stationSignal[i]=0;	
	}

	r6.stringNumerator=0;

	r6.timeSinceLastInspection=0;
	r6.totalCustomers=0;
	r6.totalProfit=0;

	for_i0(i,4){r6.trainsInLoadingPos[i]=RCTX_BYTE_EMPTY;}


	for_i0(i,32){r6.TrainSpriteIndexes[i]=RCTX_BYTE_EMPTY;}

	r6.unk_cheatDetection=1;
	r6.reliabilityCountdown=RCT_BYTE_EMPTY;
	r6.reliability=100;
	r6.unk_hasntBeenFixedTimer=0;			

	//r6.nearestHandman_spriteIndex=RCTX_WORD_EMPTY;
	r6.mechanicStatus=0;

	r6.unk0x146[0]
	=r6.unk0x146[1]
	=r6.unk0x146[4]
	=RCTX_BYTE_EMPTY
	;
	r6.breakdownType
	=RCTX_BYTE_EMPTY
	;
	r6.unk0x194[0]=0x14;

	r6.unk0x1AE[0x1B3-0x1AE]=0x80;
	r6.unk0x1AE[0x1B7-0x1AE]=0x80;
	r6.unk_cheatDetection=1;

	r6.nearestHandman_spriteIndex=RCTX_BYTE_EMPTY;

	r6.unk_breakDownTimer=0;
	r6.unk_hasntBeenFixedTimer=0;
	r6.unk_maintenanceRelatedFlag=0x0B;

	r6.reqAmtTrains=r6.amtTrains;
	r6.reqAmtCarsPerTrain=r6.amtCarsPerTrain;
	r6.maxTrains=(1<<4)|8;

	r6.unk0x1CA[0x1CC-0x1CA]=1;
	r6.runningCost=RCTX_WORD_EMPTY;
	r6.unk0x194[0]=0x14;
	
	#if(_426__SKIP_RIDE_STATIONS)

	r6.amtStations=0;

	for_i0(i,4)
	{	
		r6.stationFoci[i].x=RCTX_BYTE_EMPTY;
		r6.stationFoci[i].y=RCTX_BYTE_EMPTY;
		r6.stationHeights[i]=0;r6.stationLengths[i]=0;
		r6.rideEntrances[i].x=RCTX_BYTE_EMPTY;
		r6.rideEntrances[i].y=RCTX_BYTE_EMPTY;
		r6.rideExits[i].x=RCTX_BYTE_EMPTY;
		r6.rideExits[i].y=RCTX_BYTE_EMPTY;
	}

	#endif
}

cr_TrackAndVehicleConvert
(	
BYTE&t6,BYTE&v6,
BYTE t4,BYTE v4
)
{
	RCT1_TRACK_TYPE_CONVERT_TABLE*ct;

	short mi;
	short shopI;
	bool isShop;
	bool allSame;

	if(t4==RCTX_BYTE_EMPTY)
	{
		t6=t4;
		v6=0;
		return;
	}

	ct=&rct1TrackTypeConvertTable[t4];
	mi=ct->mapIndex;
	isShop=ct->isShop;
	allSame=ct->allTrackConvertsSame;

	if(isShop)
	{	
		shopI=rct1shopTrack_MapTable_indexConvert(mi);
		if(shopI==NUM_RCT1_SHOPS)
		{
			t6=RCTX_BYTE_EMPTY;
			v6=0;
			return;			
		}
		v6=rct1shopTrack_MapTable[shopI];
		t6=rct1shop_trackIDTable[shopI];
		return;
	}
	else 
	{
		v6=v4;
		t6=mi;
		if(allSame)
		{			
		}
		else if((t4==0x4)||(t4=0x57))
			//0x4="Junior"
			//0x57="Mini"
		{
			t6=GetMiniCoasterTrack(v4);
		}
		return;
	}
}

RideColorConvert(RCT2_RIDESTRUCT&r6,SV4_RIDESTRUCT r4)
{
	int i,c;

	for_i0(i,4)
	{
	for_i0(c,3)
	{
	r6.trackColorSchemes[i][c]
	=
	Rct1ColorConvert
	(
	r4.trackColorSchemes[i][c]
	);
	}
	}

	for_i0(i,12)
	{
	r6.vehicolors1[i].primary
	=
	Rct1ColorConvert
	(
	r4.vehicolors1[i].primary
	)
	;
	r6.vehicolors1[i].trim
	=
	Rct1ColorConvert
	(
	r4.vehicolors1[i].trim
	)
	;
	}
	

}


