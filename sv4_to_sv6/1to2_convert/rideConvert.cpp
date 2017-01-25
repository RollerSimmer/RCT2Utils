#include "rideConvert.H"

#include <codeshortcuts.h>
#include <string.h>

#define TT_EMPTYRIDESTRUCT ((BYTE)(0xFF))

ConvertRide(RCT2_RIDESTRUCT *r6p,SV4_RIDESTRUCT *r4p);

ConvertRides
(	
	RCT2_RIDESTRUCTARRAY *s6_rides,SV4_RIDESTRUCTARRAY *s4_rides,
	WORD *s6_numRideStructsUsed,WORD s4_numRideStructsUsed
)
{
	#define RCTX_NUMRIDES 255

	int r64i,usedRideSlotTally;

	*s6_numRideStructsUsed=s4_numRideStructsUsed;

	#define sz(a) (sizeof((a)))
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
			||(usedRideSlotTally>=s4_numRideStructsUsed)
			)
			{
				usedRideSlotTally++;
				ConvertRide(&r6,&r4);
			}
			else
			{
				ms0(r6);
				r4.trackType=TT_EMPTYRIDESTRUCT;				
			}
		}
	}
	#undef r6
	#undef r4
	#undef ms0
	#undef sz

}

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
		
		//equ64s(trackType);
		//equ64s(vehiObjID);

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

	}
	#undef
	#undef r6
	#undef r4
	#undef ms0
	#undef equ64s
	#undef mm64s
	#undef mma64s
	#undef mm64
	#undef mma64
	#undef sz
}

