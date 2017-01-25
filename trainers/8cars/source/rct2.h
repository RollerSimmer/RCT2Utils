#ifndef _RCT2_
#define _RCT2_

//#include <objdat.h>
#include <windows.h>
#include <stdtypes.h>

typedef enum
{	RCT2_VER_US=0,
	RCT2_VER_DEMO,
	RCT2_VER_EURO
}RCT2_VERSION;

//RCT2_VERSION Rct2Version;

#define RCT2_NUMVERSIONS	(RCT2_VER_EURO+1)

#define RCT2_VER_1_SV6

typedef union 
{
	long number;
	BYTE bytestr[4];
}RCT2_VERSIONDATASTRUCT;

RCT2_VERSIONDATASTRUCT RCT2_VERSIONDATA;

#define RCT2_TITLE "RollerCoaster Tycoon 2"
#define RCT2_EXENAME "rct2.exe"

#define RCT2_HIGHSIZE	256

/*FULL VERSION CODE*/

BYTE *RCT2_ADDR_GAMEDATASTARTADDR;

/*SV6*/
BYTE *RCT2_ADDR_GAMEDATABASE;

#define RCT2_ADDR_ABSMONTH (RCT2_ADDR_GAMEDATABASE +0x000000)
#define RCT2_ADDR_PARKMAP (RCT2_ADDR_GAMEDATABASE+0X000010)

#define RCT2_ADDR_SPRITECOUNTER (RCT2_ADDR_GAMEDATABASE+0X180010)	
#define RCT2_ADDR_SPRITES (RCT2_ADDR_GAMEDATABASE+0X180014)	
#define RCT2_ADDR_SPRITESTATS (RCT2_ADDR_GAMEDATABASE+0X3F1014)

#define RCT2_ADDR_MONEY (RCT2_ADDR_GAMEDATABASE+0X3F1034)		
#define RCT2_ADDR_LOAN (RCT2_ADDR_GAMEDATABASE+0X3F1038)	

#define RCT2_ADDR_NUMGUESTSINPARK  (RCT2_ADDR_GAMEDATABASE+0X3F149C) //??????

#define RCT2_ADDR_GUESTGENPROBABILITY (RCT2_ADDR_GAMEDATABASE+0X3F1D45)
#define RCT2_ADDR_HIGHLOAN (RCT2_ADDR_GAMEDATABASE+0X3F1D48)
#define RCT2_ADDR_FINANCHECKSUM1 (RCT2_ADDR_GAMEDATABASE+0x3F241C)
#define RCT2_ADDR_FINANCHECKSUM2 (RCT2_ADDR_GAMEDATABASE+0X3F2450)
		
#define RCT2_ADDR_PARKSTATUS0 (RCT2_ADDR_GAMEDATABASE+0X3F103C)	
#define RCT2_ADDR_PARKSTATUS1 (RCT2_ADDR_GAMEDATABASE+0X3F103D)
#define RCT2_ADDR_MAPENTRY (RCT2_ADDR_GAMEDATABASE+0X3F104A)
#define RCT2_ADDR_MAPSIZE (RCT2_ADDR_GAMEDATABASE+0X3F248C)

#define RCT2_ADDR_SAMEPRICEFLAGS1 (RCT2_ADDR_GAMEDATABASE+0X3F2490)
#define RCT2_ADDR_SAMEPRICEFLAGS2 (RCT2_ADDR_GAMEDATABASE+0X3F2FA4)

#define RCT2_ADDR_NAMESTRINGS	(RCT2_ADDR_GAMEDATABASE+0X3F454C)
#define RCT2_ADDR_RIDES (RCT2_ADDR_GAMEDATABASE+0X3FC550)

#define RCT2_ADDR_NEXTGUESTNUMBER (RCT2_ADDR_GAMEDATABASE+0X44AAC4)

#define RCT2_ADDR_WEATHER (RCT2_ADDR_GAMEDATABASE+0X4643A0)
#define RCT2_ADDR_MESSAGES (RCT2_ADDR_GAMEDATABASE+0X4643AC)
/*SV6*/

/*Park Map Pointers*/
char *_RCT2_ADDR_PARKMAPPOINTERS;

#define RCT2_ADDR_PARKMAPPOINTERS (_RCT2_ADDR_PARKMAPPOINTERS)
#define RCT2_ADDR_PARKMAPPOINTER_NEXTFREE ((void*)((DWORD)(_RCT2_ADDR_PARKMAPPOINTERS)	\
			+RCT2_HIGHSIZE*RCT2_HIGHSIZE*4))
/*Park Map Pointers*/

/*Land Mover*/
BYTE *_RCT2_ADDR_LANDMOVERSIZE;

#define RCT2_ADDR_LANDMOVERSIZE _RCT2_ADDR_LANDMOVERSIZE
/*Land Mover*/

/*Object Pointers*/
BYTE *RCT2_ADDR_OBJECTFILEPOINTERSBASE;

#define RCT2_ADDR_OBJECTFILEPOINTERS \
	RCT2_ADDR_OBJECTFILEPOINTERSBASE
#define RCT2_ADDR_RIDEOBJECTFILEPOINTERS \
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0X09ACFA4-0x09ACFA4))
#define RCT2_ADDR_SMALLSCENERYOBJECTFILEPOINTERS \
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09AD1A4-0X09ACFA4))
#define RCT2_ADDR_LARGESCENERYOBJECTFILEPOINTERS \
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09AD594-0X09ACFA4))
#define RCT2_ADDR_WALLOBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09AD794-0X09ACFA4))
#define RCT2_ADDR_PATHBANNEROBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09AD994-0X09ACFA4))
#define RCT2_ADDR_PATHOBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09ADA14-0X09ACFA4))
#define RCT2_ADDR_PATHADDITIONOBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09ADA54-0X09ACFA4))
#define RCT2_ADDR_SCENERYGROUPOBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09ADA90-0X09ACFA4))
#define RCT2_ADDR_PARKENTRANCEOBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09ADADC-0X09ACFA4))
#define RCT2_ADDR_WATEROBJECTFILEPOINTERS	\
	(RCT2_ADDR_OBJECTFILEPOINTERSBASE \
	+ (0x09ADAE0-0X09ACFA4))
/*Object Pointers*/

/*Track Type Cconstruction Parameters*/
BYTE *RCT2_ADDR_TRACKTYPECONSTRUCTOPBASE;

#define RCT2_ADDR_TRACKTYPECONSTRUCTOP \
	(RCT2_ADDR_TRACKTYPECONSTRUCTOPBASE \
	+ (0x097CF40-0x097CF40))

/*Track Type Cconstruction Parameters*/


/*Track Piece Cconstruction Parameters*/

#define NEWELEMENTINDEX	0
#define OLDELEMENTINDEX	1

#define NUMELEMENTINDEXES 2

#define PIECECONSTRUCTOP_ARRAYSIZE	(0X100*4)

BYTE *RCT2_ADDRTRACKPIECECONSTRUCTOPBASE;

#define RCT2_ADDRTRACKPIECECONSTRUCTOP(INDEX) \
	(RCT2_ADDRTRACKPIECECONSTRUCTOPBASE \
		+(0X00994638-0X00994638)+(INDEX*PIECECONSTRUCTOP_ARRAYSIZE))

/*Track Piece Cconstruction Parameters*/

/* Map Tile sprite chain start index */
BYTE *_RCT2_ADDR_MAPXYSPRITECHAININDEXES;

#define RCT2_ADDR_MAPXYSPRITECHAININDEXES	\
	(_RCT2_ADDR_MAPXYSPRITECHAININDEXES+0)
/* Map Tile sprite chain start index */

//status byte 0
#define RCT2_MASK_OPENCLOSE			0X01 
//status byte 1
#define RCT2_MASK_CHEAT				0X01						
#define RCT2_MASK_USEMONEY			0X08

#define RCT2_WORD_EMPTY 0XFFFF
#define RCT2_BYTE_EMPTY 0XFF
#define RCT2_DWORD_EMPTY 0XFFFFFFFF

/*
1C	Food Stall (all types)
1E	Drink Stall (all types)
20	Shop (all types)
23	Information Kiosk 
24	Bathroom (both types)   
2D	ATM
30	First Aid
*/
typedef enum
{	
	STT_FOODSTALL=	0x1C,	//Food Stall (all types)
	STT_DRINKSTALL=	0x1E,	//	Drink Stall (all types)
	STT_SHOP=		0x20,	//	Shop (all types)
	STT_INFOKIOSK=	0x23,	//Information Kiosk 
	STT_RESTROOM=	0x24,	//Bathroom (both types)   
	STT_ATM=		0x2D,	//ATM
	STT_FIRSTAID=	0x30	//First Aid
} RCT2_SHOPTRACKTYPE;


#define RCT2_NUMSHOPTRACKTYPES	7


BYTE RCT2_SHOPTRACKTYPES[RCT2_NUMSHOPTRACKTYPES];

extern int GetRct2Version();
int GetRCT2NameString(BYTE *nameString,WORD nameStringIndex);
int SetRCT2NameString(WORD nameStringIndex,BYTE *nameString);

#define RCT2_UNITSPERDAY	0X844
#define RCT2_DAYSPERMONTH	31
#define RCT2_MONTHSPERYEAR	8

typedef struct
{	WORD absmonth,day;	
} DATESTRUCT;

typedef struct{BYTE x,y;}RCTPOINT;

typedef struct
{
short
	WeatherTimer; 	
BYTE
	CurrentWeather,
	TargetWeather,
	CurrentTemp,
	TargetTemperature,
	Lightning,
	TargetLightning, 
	Shade,
	TargetShade,
	Rain,
	TargetRain;
}WEATHER;

typedef struct
{
BYTE 
	pieceI;
short
	xOfs,
	yOfs,
	zOfs;
BYTE 
	clearance,
	unknown0,
	flags;
} TRACKPIECESPECSTRUCT,TRACKPIECESPECSTRUCTARRAY[255];
////
typedef struct
{
BYTE
	MaxHeight,	//From ground
	ClearanceBase;
BYTE 
	CarDisplacment;
BYTE
	MaxTrainLength,
	fill4[4];
} TRACKSPECSTRUCT,TRACKSPECSTRUCTARRAY[0X5A];

#define SE_BIT 0
#define NE_BIT 1
#define NW_BIT 2
#define SW_BIT 3

#define ELMTTYPE_MASK 0x3c
#define ELMTTYPE_SHIFT 2

#define ELMTSPECS00_MASK	3
#define ELMTSPECS00_SHIFT	0

#define ES00_PATH_QUEUE		1

typedef enum
{ 
	MET_SURFACE		= 0X0,
	MET_PATH		= 0X1,
	MET_TRACKELMT	= 0X2,
	MET_SHOPSTALL	= 0X2,
	MET_SCEN1TILE	= 0X3,
	MET_ENTRYEXIT	= 0X4,
	MET_FENCEWALL	= 0X5,
	MET_SCENMULTILE	= 0X6,
	MET_BANNERS		= 0X7
} RCT2_MAPELEMENTTYPE;

#define ELMTSPECS06_MASK	0xC0
#define ELMTSPECS06_SHIFT	6

#define ES00_FLAG_ISQUEUE	1

typedef struct 
{
	union
	{
		struct
		{
			unsigned char 
				elmtSpec00	:2,
				elmtType	:3,
				unk05		:1,
				elmtSpec06	:2;
		};
		BYTE data;
	};
}	MAPBYTE0;

typedef struct
{
	unsigned char 
		NEOccupied				:1,	
		SEOccupied				:1,	
		SWOccupied				:1,	
		NWOccupied				:1,	
		ghosted					:1,
		pathAddsVandalized		:1,
		unk06					:1,
		lastElementOnTile		:1;
}	MAPBYTE1;

#define EE_RIDEENTRY	0
#define EE_RIDEEXIT		1
#define EE_PARKGATE		2

#define EE_RIDEEXIT_CLEARANCE	5
#define EE_RIDEENTRY_CLEARANCE	7
#define EE_PARKGATE_CLEARANCE	12


#define TRACK_STATIONPLATFORM_END		0X01
#define TRACK_STATIONPLATFORM_BEGIN		0X02
#define TRACK_STATIONPLATFORM_MIDDLE	0X03

typedef union 
{
	BYTE
		elmtID,
		landslope,
		bannerindex;
} MAPBYTE4;

#define OWNERSHIP_MASK 0XF0
#define OWNERSHIP_SHIFT 4
#define BORDERFENCE_MASK 0XF
#define BORDERFENCE_SHIFT 0


#define OWN_UNOWNED 0

//#define 1, 3 or 5 = construction rights purchased

#define OWN_UNOWNED		0
#define OWN_RIGHTSOWNED 1
#define OWN_LANDOWNED	2
#define OWN_RIGHTSAVAIL	4
#define OWN_LANDAVAIL	8


#define BORDERFENCE_NONE	0
#define BORDERFENCE_NORTH	1
#define BORDERFENCE_EAST	2
#define BORDERFENCE_SOUTH	4
#define BORDERFENCE_WEST	8

typedef union
{
	BYTE
		index,
		scenAge,
		terrainWater,
		pathAdditions,
		parkEntryIndex,
		bannerPosition;
}MAPBYTE5;


#define COLORCSCHEME_MASK 0x03
#define COLORCSCHEME_MAIN 0x00
#define COLORCSCHEME_ALT(a) (a)
#define COLORCSCHEME_STATIONENTRY 0x04

#define GRASSSTATE_MASK		0x7
#define GRASSSTATE_MOWED	0
#define GRASSSTATE_CLEAR	1
#define GRASSSTATE_CLUMPS	4
#define GRASSSTATE_RESERVED	7

typedef union
{
	BYTE
		grass,
		color,
		edgeCorner,
		parkEntryPath,
		item,
		bannerNoEntry;
}MAPBYTE6;

#define PAS_ALLTRASHEMPTY 0xff

typedef union 
{
	BYTE
		ownership,
		rideindex,
		pathAdditionStatus,
		item;
} MAPBYTE7;

#define RCT2_HEIGHTUNIT 2
#define RCT2_MAXHEIGHT 62 
#define RCT2_MINHEIGHT 2 


#define TF_LASTTILE 0X80

#define GROUNDTYPE_EXTENDERBITPLACE 0
#define GROUNDTYPE_EXTENDERBITMASK \
		(1<<GROUNDTYPE_EXTENDERBITPLACE)

#define EDGETYPE_EXTENDERBITPLACE 7
#define EDGETYPE_EXTENDERBITMASK \
	(1<<EDGETYPE_EXTENDERBITPLACE)

#define EDGEGROUNDTYPE_BITPLACE 5
#define EDGEGROUNDTYPE_BITMASK \
	(7<<EDGEGROUNDTYPE_BITPLACE)

#define LANDTYPEEXTENDER_BITPLACE 3

#define WATER_ABSHEIGHTBITPLACE 0
#define WATER_ABSHEIGHTBITMASK 0X1F

typedef struct 
{
	MAPBYTE0
		byte0;
	MAPBYTE1
		byte1;
	BYTE
		baseheight,
		clearheight;
	MAPBYTE4 
		byte4;
	MAPBYTE5
		byte5;
	MAPBYTE6
		byte6;
	MAPBYTE7
		byte7;
} PARKMAPDATA;

typedef PARKMAPDATA* LPPARKMAPDATA;

typedef LPPARKMAPDATA PARKMAPPTRARRAY[256][256];

#define MAPDATASTRUCTURES_MAX 196608
typedef PARKMAPDATA PARKMAPDATABLOCK[MAPDATASTRUCTURES_MAX];

PARKMAPDATA BORDERTILE;	//"\x00\x80\x02\x02\x00\x00\x01\x00"

#define BORDERTILESTRING "\x00\x80\x02\x02\x00\x00\x01\x00"

typedef enum
{	MDF_READ,
	MDF_WRITE,
	MDF_INIT,
	MDF_DONE,
	MDF_OPTIMIZE
}	RCT2_MAPDATAFUNC;

short Rct2MapDataFunc
(	RCT2_MAPDATAFUNC mapdatafunc,short x,short y,LPPARKMAPDATA mapdata,int count	
);

#define NUMSPRITES 10000
#define SPRITETYPES 6

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

typedef enum
{		SPR_FREE=0,SPR_VEHI,SPR_PERSON,
		SPR_FLOAT,SPR_JUNK,SPR_OVERSIZED
}
SPRITETYPE;

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
} SPRITESTRUCT,SPRITESTRUCTARRAY[NUMSPRITES];

#define MAP_MAXTILES 256

typedef WORD SPRITE_MAPXYINDEXES[MAP_MAXTILES][MAP_MAXTILES];

typedef BYTE NAMESTRING[32];

#define RSF_BROKENDOWN	(1<<7)

typedef enum 
{	
	INSPECT_10MIN	=0,
	INSPECT_20MIN	=1,
	INSPECT_30MIN	=2,
	INSPECT_45MIN	=3,
	INSPECT_1HOUR	=4,
	INSPECT_2HOUR	=5,
	INSPECT_NEVER	=6
}	RIDEINSPECTIONFREQUENCY;

typedef struct 
{
	BYTE 
		trackType,
		vehiObjID,
		fill002[2],
		opmode,
		colorScheme;
	struct {BYTE primary,trim;} vehicolors1[32];
	BYTE 
		fill046[3],
		ridestatus;
	short 
		nameStringIndex;
	long 
		stringNumerator;
	RCTPOINT 
		overallViewFocus,
		stationFoci[4];
	BYTE 
		stationHeights[4],
		stationLengths[4],
		stationSignal[4],
		trainsInLoadingPos[4];
	RCTPOINT
		rideEntrances[4],
		rideExits[4];
	short 
		lastQueueGuestIndex[4];
	BYTE 
		fill082[4];
	short 
		TrainSpriteIndexes[32];
	BYTE 
		DepartureControlFlags,
		amtStations,
		amtTrains,
		amtCarsPerTrain,
		reqAmtTrains,
		reqAmtCarsPerTrain,
		maxTrains,
		fill0CD[1],
		minWait,
		maxWait,
		launchSpeed,
		fill0D1[3],
		dataLoggingIndex,
		specialTrackElements,
		fill0D6[2];
	short 
		maxspeedLo,
		maxspeedHi,
		avgspeedLo,
		avgspeedHi;
	BYTE 
		fill0E0[4];
	long 
		rideLengths[4];
	short
		rideTimes[4],
		maxPosVertGs,
		maxNegVertGs,
		maxLatGs;
	BYTE 
		fill102[0x12],
		inversions,
		drops,
		fill116[1],
		highDrop,
		fill118[8];
	short 
		curCustomerCount,
		customerCountTimer,
		lastCustomerCounts[10],
		ticketPrice;
	BYTE
		fill13A[6];
	short
		excitement,
		intensity,
		nausea;
	BYTE
		fill146[5],
		satisfaction,
		fill14C[4];
	long
		totalCustomers,
		totalProfit;
	BYTE
		/*
		158		1	popularity (multiply by 4 for percent;
					see next two fields)
		*/
		popularityOutOf25,
		/*
		159		1	counter which increases every time a guest 
					"thinks" about ride--resets at 25
		*/
		pop_TotalThoughtCountTo25,
		/*
		15A		1	how many positive (ie good) thoughts there are 
					out of the count in 159; this value gets 
					copied to the popularity rating when the
					above thought count reaches 25
		*/
		pop_GoodThoughtCountOutOf25,
		/*
		15B		1	total guests currently on ride
		*/
		numGuestsOnRide,
		/*
		15C		1	Music being played:
					(FF=not used,closed,etc)
					value	music style
					13d	Dodgems
					14	Fairgrounds organ
					15 	Roman Fanfare
					16	Oriental 
					17	Matrian
					18	Jumgle drums
					19	Egyptian 
					20	Toyland
					21	?(blank)
					22	Space
					23	Horror
					24	Techno
					25	Gentle
					26	Summer
					27	Water
					28	Wild West
					29	Jurassic
					30	Rock 1
					31	Ragtime
					32	Fantasy			
					33	Rock 2
					34	Ice
					35	Snow
					36	Custom	1
					37	Custom	2
					38	Medieval
					39	Urban
					40	Organ
					41	Mechanical
					42	Modern
					43	Pirates
					44	Rock 3
					45	Candy		
		*/
		currentMusicPlaying,
		fill15D[0X180-0x15D];
	short 
		absBuiltMonth,
		runningCost;
	BYTE
		fill184[0xF],
		breakdownType,
		fill194[2],
		reliabilityCountdown,
		reliability,
		fill198[1],
		downtime,
		inspectionFrequency,
		timeSinceLastInspection,
		fill19C[0x1A8-0X19C];
	short 
		onRidePhotosSold;
	BYTE
		fill1AA[0X1B8-0X1AA],
		queuetime,
		fill1B9[0X1CD-0X1B9],
		liftChainSpeed;
	short 
		favRideGuestCount,
		rideStatusFlags;
	BYTE
		fill1D2[2],
		seatColors[32],
		fill1F4[3],
		numCircuits,
		fill1F8[8],
		guestsInQueue[4],
		fill204[0X260-0X204];
} RIDESTRUCT, RIDESTRUCTARRAY[256];

#define RCT2_MSGCOLOR_WHITE		0x90	
#define RCT2_MSGCOLOR_RED		0x91
#define RCT2_MSGCOLOR_GREEN		0x92
#define RCT2_MSGCOLOR_GOLD		0x93
#define RCT2_MSGCOLOR_BROWN		0x94
#define RCT2_MSGCOLOR_GREY		0x95
#define RCT2_MSGCOLOR_BLUE		0x96
#define RCT2_MSGCOLOR_PURPLE	0x97
#define RCT2_MSGCOLOR_BEIGE		0x98
#define RCT2_MSGCOLOR_PINK		0x99
#define RCT2_MSGCOLOR_AGUA		0x9A
#define RCT2_MSGCOLOR_TAN		0x9B
#define RCT2_MSGCOLOR_GREEN2	0x9C

#define RCT2_MSGICON_HIDE		0
#define RCT2_MSGICON_RIDE		1
#define RCT2_MSGICON_PERSON		2
#define RCT2_MSGICON_COINS		3
#define RCT2_MSGICON_BLANK		5
#define RCT2_MSGICON_SCENERY	6
#define RCT2_MSGICON_CROWD		7
#define RCT2_MSGICON_AWARD		8
#define RCT2_MSGICON_GRAPH		9

#define MESSAGESTRUCTSIZE 268
#define NUMMESSAGES 61

typedef struct
{
	BYTE
		icon,				//000
		fill001;			//001
	short 
		item;				//002
	BYTE 
		fill004[2],			//004
		lettersDisplayed,	//006
		fill007;			//007
	short 
		month,				//008
		day;				//00A			
	BYTE 
		color,				//00C
		text[255];			//00D
}
MESSAGESTRUCT,MESSAGESTRUCTARRAY[NUMMESSAGES];

typedef enum
{	RCT2_EAST,
	RCT2_SOUTH,
	RCT2_WEST,
	RCT2_NORTH
} RCT2_DIRECTION;

typedef struct
{	short x,y;
	BYTE z,direction;
} ENTRYPOINTSTRUCT;

#define HIGHFTL 64
#define HIGHFULLFILE 128
#define HIGHFULLREGKEY 256
#define HIGHKEYNAMELENGTH 32
#define HIGHDELIMS 2

#define RCT2REGKEYNAME "Software\\Infogrames"\
	"\\RollerCoaster Tycoon 2 Setup"
#define RCT2REGVALUENAME "Path"

int GetRct2Path(BYTE *path);

int rct2Suspended;
int SuspendRCT2();
int ResumeRCT2();

#endif //_RCT2_
