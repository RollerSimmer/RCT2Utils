#ifndef SV6_SPRITES_H
#define SV6_SPRITES_H

#define SV6_NUMSPRITES 10000
#define SPRITETYPES 6

#include "SV6_MAP.H"

#ifndef SPRITESTATS_DEFINED

typedef union
{	struct 
	{	unsigned short  
			nextFreeSprite,
			firstVehicle,
			firstPerson,
			firstFloat,
			firstJunk,
			firstOversizedRideCar,			
			availSprites,
			vehiCount, 
			peopleCount,
			floatingCount,
			junkCount,
			oversizedCount;
	} statsA;
	unsigned short statsB[2][SPRITETYPES];
} SPRITESTATS;

#define SPRITESTATS_DEFINED
#endif

#ifndef SPRITETYPE_DEFINED

typedef enum
{		SPR_FREE=0,SPR_VEHI,SPR_PERSON,
		SPR_FLOAT,SPR_JUNK,SPR_OVERSIZED
}
SPRITETYPE;

#define SPRITETYPE_DEFINED
#endif// SPRITETYPE_DEFINED


#define SPR_FIRSTINDEX 0
#define SPR_COUNT 1

#define INTENSITY_LOWMASK	0X0F
#define INTENSITY_HIGHMASK	0XF0

#define ITEM_BALLOON	(1<<0X00)

#define ITEM_MAP		(1<<0X02)

#define ITEM_UMBRELLA	(1<<0X04)
#define ITEM_DRINK		(1<<0X05)
#define ITEM_BURGER		(1<<0X06)
#define ITEM_TSHIRT		(1<<0X14)

#define SPR_ID_VEHICLE		00
#define SPR_ID_PERSON		01
#define SPR_ID_FLOATING		02
#define SPR_ID_JUNK			03
#define SPR_ID_FREE			0XFF

#define SPR_PT_GUEST	0
#define SPR_PT_STAFF	1


#define DIMESINDOLLAR	10

#define GAS_OUTOFPARK	1
#define GAS_INPARK		0
			
typedef struct 
{
	BYTE 
		spriteID,
		trashtype;
	WORD  
		nextOnThisTile,
		nextInClass,
		prevInClass;
	BYTE
		typeStatsOffset,
		fill09;
	WORD  
		spriteIndex;
	BYTE 
		fill0C[0x0E-0x0C];
	short 
		x,y,z,
		personStructCounter;
	BYTE 
		fill16[0x1e-0x16],
		direction,
		fill1F[0X22-0X1F];
	short 
		textStringIndex,
		nextX, nextY;
	union {short nextZ,flytextmoney,vehiSpeed;} word28;
	BYTE 
		guestAdmissionStatus,
		curstate,
		fill2C[1],
		personGraphic,
		persontype,
		numRidesBeenOn;
	union {BYTE shirtcolor,ownerRide;}byte30;
	union {BYTE pantcolor,vehitypeObjID;}byte31;
	union {struct{BYTE body,trim;}vehicolor; short personX;}word32;
	short 
		personY;
	BYTE 
		fill36[0X38-0X36],
		energy,
		targetenergy,
		happiness,
		targethappiness,
		nausea,
		targetnausea,
		nothunger,
		notthirst,
		restroomNeed,
		fill42[2],
		intensityPref,
		nauseaTolerance,
		fill45[0X52-0X45];
	
	union
	{	short guestsInVehicle[32];
		struct
		{
			BYTE 
 				fill52[0X68-0X52],
				unkCurRideOnI_A,
				fill69[0X6E-0X69],
				animationType,
				fill6F[1],
				animationSequence,
				fill71[3];
			short
				QueueGuestInFrontIndex;
			BYTE
				fill76[0x79-0X76],
				unkCurRideOnI_B,
				fill80[0x92-0X80];

		} personStruct;
	} union52;
	BYTE fill92[0x9c-0x92];
	long 
		personID,
		cashInPocket,
		cashSpent,
		timeOfEntry;
	BYTE
		fillAC[0xAD-0XAC],
		byte0AD,
		fillAE[0xB0-0xAE];
	union
	{
		struct
		{
			BYTE 
				fillB0[0xB3-0xB0],
				passengerCount[2],
				fillB5[0xC4-0xB5];
		} vehi; 
		struct 
		{
			BYTE thought,item;
			short isThoughPresent;
		} thoughts[5];
	} unionB0;
	BYTE 
		fillC4[1],
		guestRideDestination,
		staffAssignments,
		ORPhotoRideID,
		trackingState,
		fillC9[0xE4-0xC9];
	short 
		amtPaidEntryFee,
		amtSpentRides,
		amtSpentFoodDrink,
		amtSpentSouvenirs;
	BYTE		
		itemsEaten,
		itemsDrunk,
		souvenirsBought,
		fillEF[1],
		couponType,
		rideAssocCoupon,
		fillF2[1],
		vandalFlag,
		fillF4[2],
		balloonColor,
		umbrellaColor,
		hatColor,
		favoriteRide,
		fillFA[2];
	DWORD
		items;
} SV6_SPRITESTRUCT,SV6_SPRITESTRUCTARRAY[SV6_NUMSPRITES];

typedef WORD SV6_SPRITE_MAPXYINDEXES[SV6_MAP_MAXTILES][SV6_MAP_MAXTILES];


#endif SV6_SPRITES_H
