#include <stdtypes.h>
#include "parkConvert.H"

#include <string.h>
#include <memory.h>


ConvertPark(SV6_FILE *sv6,SV4_FILE *sv4)
{
	SV6_CHUNKHEADER templateHeaders[SV6_NUMCHUNKS]=
	{	
		{ET_LITERAL,sizeof(sv6->fileDataA.header)},
		{ET_LITERAL,sizeof(sv6->fileDataA.availableItems)},
		{ET_LITERAL,sizeof(sv6->fileDataA.timeData)},
		{ET_LITERAL,sizeof(sv6->fileDataA.parkMap)},
		{ET_LITERAL,sizeof(sv6->fileDataA.parkData)},
	};

	struct
	{
		SV6_CHUNKHEADER 
			*templateHeader,
			*chunkHeader;
	} 
	chunkHeaders[SV6_NUMCHUNKS]=
	{
		{&templateHeaders[0],&(sv6->fileDataA.header_header)},
		{&templateHeaders[1],&(sv6->fileDataA.availableItems_header)},
		{&templateHeaders[2],&(sv6->fileDataA.timeData_header)},
		{&templateHeaders[3],&(sv6->fileDataA.parkMap_header)},
		{&templateHeaders[4],&(sv6->fileDataA.parkData_header)},
	};

	int i;

	for(i=0;i<SV6_NUMCHUNKS;i++)	
	{	
		memmove
		(
			chunkHeaders[i].chunkHeader,
			chunkHeaders[i].templateHeader,
			sizeof(chunkHeaders[i].chunkHeader)
		);
	}

	#define sz(a) (sizeof(a))

	#define WATERCOLOR_RED 1

	#define s6o	(sv6->fileDataA.availableItems)
	#define s6w (sv6->fileDataA.parkData.waterColor)
	#define s4w (sv4->fileDataA.parkData.waterColor)
	DoWaterColorConvert:
	{
		//copy object table

		if(s4w==WATERCOLOR_RED)
		{
			memmove
			(
				&(RCT1emulationTable.palette),
				&redWater,
				sz(RCT1emulationTable.palette)
			);
		}
		memmove(&s6o,&RCT1emulationTable,sz(s6o));

		s6w=s4w;
	}
	#undef s6o
	#undef s5w
	#undef s4w

	#undef WATERCOLOR_RED


	#define s6t (sv6->fileDataA.timeData)
	#define s4t (sv4->fileDataA.parkData.time)
	DoTimeConvert:
	{

		//convert sv4 file to sv6 file

		memmove(&s6t,&s4t,sz(s6t));	

	}
	#undef s6t
	#undef s4t

	DoMapConvert:
	/*

	ConvertMap
	(	&(sv6->fileDataA.parkMap),
		&(sv4->fileDataA.parkData.parkMap)
	);

	*/

	#define s6 (sv6->fileDataA.parkData)
	#define s4 (sv4->fileDataA.parkData)
	#define ms0(a) (memset(&(a),0,sz((a))))
	#define mm(a,b) \
		(memmove(&(a),&(b),sz((a))))
	#define mma(a,b) \
		(memmove((a),(b),sz((a))))
	#define mm64s(a) (mm(s6.a,s4.a)) 
	#define mma64s(a) (mma(s6.a,s4.a)) 
	#define mm64(a,b) (mm(s6.a,s4.b)) 
	#define mma64(a,b) (mma(s6.a,s4.b)) 

	DoParkDataConvert:
	{

		//convert sv4 file to sv6 file

		s6.spriteTimer=s4.spriteTimer;

		ConvertSprites
		(	
			&(s6.sprites),&(s4.sprites),
			&(s6.spriteStats),&(s4.spriteStats)
		);

		s6.parkNameOffset=s6.parkNameOffset;
		
		memmove(s6.unk0x271020,s4.unk0x198830,sz(s6.unk0x271020));

		s6.money=s4.money;
		s6.loan=s4.loan;

		memmove((&s6.parkStatus),(&s4.parkStatus),sz(s6.parkStatus));

		mm(s6.mainParkEntry,s4.mainParkEntry);

		mma(s6.unk0x271039,s4.unk0x198849);

		mma64s(peepMapEntryPoints);

		mm64s(mainParkEntry);

		mma64(unk0x271046,unk0x198856);

		mm64s(researchRate);

		mma64(unk0x271048,unk0x198858);

		mma64s(ridesMenu);

		mma64s(vehicleMenu);

		mma64s(rideFeatureTable);

		mm64s(numGuestsInPark);

		mma64(unk0x27148E,unk0x198C9E);

		mma64s(budgetVals);

		mm64s(unk_numGuestsInPark);

		mma64(unk0x271814,unk0x199024);

		mm64s(handmanColor);
		mm64s(mechanicColor);
		mm64s(securityColor);

		mma64s(sceneryMenu);

		mma64s(bannerMenu);

		mma64(unk0x27189A,unk0x1990AA);

		mm64s(curParkRating);
		
		mma64s(histParkRating);

		mm64s(researchSelection);
		mm64s(researchProgress);

		mm64s(lastDevelopment_Item);
		mm64s(lastDevelopment_ride);
		mm64s(lastDevelopment_category);
		mm64s(lastDevelopment_flag);

		mma64s(researchItems);

		mm64s(nextDevelopment_Item);
		mm64s(nextDevelopment_ride);
		mm64s(nextDevelopment_category);
		mm64s(nextDevelopment_flag);

		mma64(unk0x271D2C,unk0x19953C);
		mma64(unk0x271D2E,unk0x19953E);

		mm64s(cheat_ownedLandCount);

		mm64(unk0x271D34[0],unk0x199544[0]);
		mm64(guestGenProbability,unk0x199544[1]);
		mma64(unk0x271D36,unk0x199546);

		mm64s(maxLoan);

		mm64s(newGuest_cash);

		mm64s(newGuest_thirst);
		mm64s(newGuest_hunger);
		mm64s(scenarioGoal);
		mm64s(scenarioTimeLimit_inYears);

		mma64(unk0x271D42,unk0x199552);

		mm64s(scenarioGoal_dwordValue);
		mm64s(scenarioGoal_wordValue);

		mma64s(advertising);
		mma64s(advertisingItems);

		mma64(unk0x271D64,unk0x199574);

		mma64s(prevCashVals);

		mm64s(recentCashChange);
		mm64s(recentCashChange_x7);
		mm64s(recentCashChanges_sum);

		mma64(unk0x271F80,unk0x199790);
		mma64(unk0x271F82,unk0x199792);

		mma64s(weeklyProfitHistory);

		mm64s(parkValue);

		mma64s(parkValueHistory);

		mm64s(scenarioObjectiveValAtCompletion);
		mm64s(totalAdmissions);
		mm64s(admissionIncome);
		mm64s(companyValue);

		mma64(unk0x272398,unk0x199BA8);

		mma64s(parkAwards);

		mm64s(landPurchaseCost);
		mm64s(rightsPurchaseCost);

		mma64(unk0x2723BC,unk0x199BCC);
		mma64(unk0x2723BE,unk0x199BCE);

		mm64s(ifError_contains0x00C3BB58);

		mma64s(userName);

		mm64s(companyValue_atScenarioCompletion);
		mm64s(financialChecksum_1);
		mm64s(numRideStructsUsed);
		mm64s(cheat_negNumRidesAvail);
		mm64s(cheat_maxOwnedTilesAllowed);
		mm64s(cheat_maxOwnedTilesAllowed_neg);
		mm64s(financialChecksum_3_unused);
		mm64s(checksum_scenarioSlotNumber);

		mma64s(winnerName);

		mm64s(financialChecksum_2);

		mma64s(copyrightNotice);

		mm64s(cheat_0inSV4_FED3inSC4);
		mm64s(cheat_0inSV4_F318inSC4);
		mm64s(cheat_0inSV4_B218inSC4);
		mm64s(cheat_0inSV4_458AinSC4);

		mma64(unk0x272474,unk0x199C84);
		mma64(unk0x272476,unk0x199C86);

		mm64s(unk_32_x_par_parkSize_minus_1_par);

		mm64(unk_value_at_0x272478_plus_011E,unk_value_at_0x272478_plus_011E);
		
		mm64s(parkSize);
		mm64s(samePrice_1);

		mma64(unk0x272484,unk0x199C94);
		mma64(unk0x272486,unk0x199C96);

		mm64s(waterColor);
		
		mma64(unk0x27248A,unk0x199C9A);

		mma64s(researchItems2);

		ms0(s6.unk0x272810);

		//fix this
		ms0(s6.unk0x272E50);

		ms0(s6.scenarioName);

		strncpy(s6.scenarioName,s4.scenarioName2,sz(s4.scenarioName2));

		ms0(s6.scenarioDetailsText);

		//fix this
		ms0(s6.unk0x272F92);

		ms0(s6.samePrice_2);

		ConvertAnimationObjects
		(
			&s6.numAnimationObjects,s4.numAnimationObjects,
			&s6.animationObjectLocations[0],&s4.animationObjectLocations[0],
			&s6.parkEntriesXpos[0],
			&s6.parkEntriesYpos[0],
			&s6.parkEntriesZpos[0],
			&s6.parkEntriesUsedFlag[0]
		);

		ms0(s6.scenarioFile);

		ms0(s6.unk0x272FF8);

		ConvertBanners
		(	
			&s6.bannerInfo[0],&s4.bannerInfo[0]		
		);

		mma64s(nameStrings);

		mm64s(gameTimeCounter);

		//ConvertRides(&s6.rides,&s4.rides,&s6.numRideStructsUsed,s4.numRideStructsUsed);










	}
	#undef ms0
	#undef mm
	#undef mma
	#undef mm64s
	#undef mma64s
	#undef mm64
	#undef mma64
	#undef s6
	#undef s4

	#undef sz
}


