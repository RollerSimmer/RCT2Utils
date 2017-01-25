
 
#ifndef _RCT_
#define _RCT_

#include <objdat.h>
#include <windows.h>
#include <stdtypes.h>

typedef enum
{	RCT_VER_US_LL=0,
/*	RCT_VER_DEMO,
	RCT_VER_EURO
*/
}RCT_VERSION;

RCT_VERSION RctVersion;

#define RCT_NUMVERSIONS	(RCT_VER_US_LL+1)

#define RCT_VER_1_SV6

typedef union 
{
	long number;
	BYTE bytestr[4];
}RCT_VERSIONDATASTRUCT;

RCT_VERSIONDATASTRUCT RCT_VERSIONDATA[RCT_NUMVERSIONS];

#define RCT_TITLE "RollerCoaster Tycoon"
#define RCT_EXENAME "rct2.exe"

/*FULL VERSION CODE*/

BYTE *RCT_ADDR_GAMEDATASTARTADDR[];

/*SV6*/
BYTE *RCT_ADDR_GAMEDATABASE[RCT_NUMVERSIONS];

#define RCT_ADDR_ABSMONTH (RCT_ADDR_GAMEDATABASE[RctVersion]+0x000000)
#define RCT_ADDR_PARKMAP (RCT_ADDR_GAMEDATABASE[RctVersion]+0X000010)

#define RCT_ADDR_SPRITECOUNTER (RCT_ADDR_GAMEDATABASE[RctVersion]+0X60010)	
#define RCT_ADDR_SPRITES (RCT_ADDR_GAMEDATABASE[RctVersion]+0X060014)	
#define RCT_ADDR_SPRITESTATS (RCT_ADDR_GAMEDATABASE[RctVersion]+0X198814)

#define RCT_ADDR_MONEY (RCT_ADDR_GAMEDATABASE[RctVersion]+0x198834)		
#define RCT_ADDR_LOAN (RCT_ADDR_GAMEDATABASE[RctVersion]+0x198838)	

#define RCT_ADDR_GUESTGENPROBABILITY (RCT_ADDR_GAMEDATABASE[RctVersion]+0X199545)
#define RCT_ADDR_HIGHLOAN (RCT_ADDR_GAMEDATABASE[RctVersion]+0X199548)
#define RCT_ADDR_FINANCHECKSUM1 (RCT_ADDR_GAMEDATABASE[RctVersion]+0x199C1C)
#define RCT_ADDR_FINANCHECKSUM2 (RCT_ADDR_GAMEDATABASE[RctVersion]+0x199C50)
		
#define RCT_ADDR_PARKSTATUS0 (RCT_ADDR_GAMEDATABASE[RctVersion]+0x19883C)	
#define RCT_ADDR_PARKSTATUS1 (RCT_ADDR_GAMEDATABASE[RctVersion]+0x19883D)
#define RCT_ADDR_MAPENTRY (RCT_ADDR_GAMEDATABASE[RctVersion]+0x198842)
#define RCT_ADDR_MAPSIZE (RCT_ADDR_GAMEDATABASE[RctVersion]+0X199C8C)
#define RCT_ADDR_NUMGUESTSINPARK (RCT_ADDR_GAMEDATABASE[RctVersion]+0x198C9C)

#define RCT_ADDR_SAMEPRICEFLAGS1 (RCT_ADDR_GAMEDATABASE[RctVersion]+0X199C90)

#define RCT_ADDR_NAMESTRINGS	(RCT_ADDR_GAMEDATABASE[RctVersion]+0X19B89C)
#define RCT_ADDR_RIDES (RCT_ADDR_GAMEDATABASE[RctVersion]+0X1A38A0)

#define RCT_ADDR_NEXTGUESTNUMBER (RCT_ADDR_GAMEDATABASE[RctVersion]+0X1F06A4)

#define RCT_ADDR_WEATHER (RCT_ADDR_GAMEDATABASE[RctVersion]+0X1F432C)
#define RCT_ADDR_MESSAGES (RCT_ADDR_GAMEDATABASE[RctVersion]+0X1F4338)

/*SV6*/

/* Park Map pointers */
BYTE *_RCT_ADDR_PARKMAPPOINTERS[RCT_NUMVERSIONS];

#define RCT_ADDR_PARKMAPPOINTERS (_RCT_ADDR_PARKMAPPOINTERS[RctVersion]+0)

/* Park Map pointers */

/* Map Tile sprite chain start index */
BYTE *_RCT_ADDR_MAPXYSPRITECHAININDEXES[RCT_NUMVERSIONS];

#define RCT_ADDR_MAPXYSPRITECHAININDEXES	\
	(_RCT_ADDR_MAPXYSPRITECHAININDEXES[RctVersion]+0)
/* Map Tile sprite chain start index */

/*Land Mover*/
BYTE *_RCT_ADDR_LANDMOVERSIZE[RCT_NUMVERSIONS];

#define RCT_ADDR_LANDMOVERSIZE _RCT_ADDR_LANDMOVERSIZE[RctVersion]
/*Land Mover*/

/*Track Type Cconstruction Parameters*/
BYTE *RCT_ADDR_TRACKTYPECONSTRUCTOPBASE[RCT_NUMVERSIONS];

#define RCT_ADDR_TRACKTYPECONSTRUCTOP \
	(RCT_ADDR_TRACKTYPECONSTRUCTOPBASE[RctVersion] \
	+ (0x097CF40-0x097CF40))

/*Track Type Cconstruction Parameters*/


/*Track Piece Cconstruction Parameters*/

#define NEWELEMENTINDEX	0
#define OLDELEMENTINDEX	1

#define NUMELEMENTINDEXES 2

#define PIECECONSTRUCTOP_ARRAYSIZE	(0X100*4)

BYTE *RCT_ADDR_TRACKPIECECONSTRUCTOPBASE[RCT_NUMVERSIONS];

#define RCT_ADDR_TRACKPIECECONSTRUCTOP \
	(RCT_ADDR_TRACKPIECECONSTRUCTOPBASE[RctVersion]+0)

/*Track Piece Cconstruction Parameters*/

/*Large scenery specs*/
BYTE *RCT_ADDR_SCENMULTILESPECBASE[RCT_NUMVERSIONS];

#define RCT_ADDR_SCENMULTILESPECS \
	(RCT_ADDR_SCENMULTILESPECBASE[RctVersion]+0)
//799A60	4*?	Array of pointers to 9-byte large scenery spec record arrays 
/*Large scenery specs*/

/*Small scenery attribute specs*/
BYTE *RCT_ADDR_SCEN1TILESPECBASE[RCT_NUMVERSIONS];

#define RCT_ADDR_SCEN1TILESPECS \
	(RCT_ADDR_SCEN1TILESPECBASE[RctVersion]+0)
 
//8893F0	8*?	Array of attribute specs for small scenery 
/*Small scenery attribute specs*/

//status byte 0
#define RCT_MASK_OPENCLOSE			0X01 
//status byte 1
#define RCT_MASK_CHEAT				0X01						
#define RCT_MASK_USEMONEY			0X08

#define RCT_WORD_EMPTY 0XFFFF
#define RCT_BYTE_EMPTY 0XFF
#define RCT_DWORD_EMPTY 0XFFFFFFFF

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
} RCT_SHOPTRACKTYPE;

#define RCT_NUMSHOPTRACKTYPES	7

BYTE RCT_SHOPTRACKTYPES[RCT_NUMSHOPTRACKTYPES];

int GetRctVersion();
int GetRCTNameString(BYTE *nameString,int nameStringIndex);

#define RCT_UNITSPERDAY	0X844
#define RCT_DAYSPERMONTH	31
#define RCT_MONTHSPERYEAR	8

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
	CarDisplaceent;
BYTE
	MaxTrainLength,
	fill4[4];
} TRACKSPECSTRUCT,TRACKSPECSTRUCTARRAY[0X5A];


typedef struct 
{
	WORD	
		fill0;
	BYTE	
		clearance,
		fill3,
		cursorType,
		scenType;
	WORD	
		unkIndex;
} SCEN1TILE_ATTRIBSPECSTRUCT; 

#define SE_BIT 0
#define NE_BIT 1
#define NW_BIT 2
#define SW_BIT 3

#define ELMTTYPE_MASK 0x3c
#define ELMTTYPE_SHIFT 2


typedef enum
{
#define MET_SURFACE		0X0
#define MET_PATH		0X1
#define MET_TRACKELMT	0X2
#define MET_SHOPSTALL	0X2
#define MET_SCEN1TILE	0X3
#define MET_ENTRYEXIT	0X4
#define MET_FENCEWALL	0X5
#define MET_SCENMULTILE	0X6
#define MET_BANNERS		0X7		
} RCT_MAPELEMENTTYPE;

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
#define GRASSSTATE_RESERED	7

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

#define RCT_HEIGHTUNIT 4
#define RCT_MAXHEIGHT 124 
#define RCT_MINHEIGHT 0 


#define RCT_HIGHSIZE	256

#define TF_LASTTILE 0X80

#define GROUNDTYPE_EXTENDERBITPLACE	0
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
	BYTE 
		elmtType,
		tileflags,
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

#define MAP_MAXTILES	128
typedef LPPARKMAPDATA PARKMAPPTRARRAY[MAP_MAXTILES][MAP_MAXTILES];

typedef PARKMAPDATA PARKMAPDATABLOCK[49152];

PARKMAPDATA BORDERTILE;	//"\x00\x80\x02\x02\x00\x00\x01\x00"

//#define BORDERTILESTRING "\x00\x80\x02\x02\x00\x00\x01\x00"

typedef enum
{	MDF_READ,
	MDF_WRITE,
	MDF_INIT,
	MDF_DONE,
}	RCT_MAPDATAFUNC;

short Rct2MapDataFunc
(	RCT_MAPDATAFUNC mapdatafunc,short x,short y,LPPARKMAPDATA mapdata,int count	
);

#define NUMSPRITES 5000
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
		fillFA[2],
		items[4];
} SPRITESTRUCT,SPRITESTRUCTARRAY[NUMSPRITES];

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

#define RCT_NUMRIDES

typedef struct 
{
	BYTE  
		//000 : ride type (FF if not used) 
		trackType,
		//001 : vehicle type 
		vehiObjID;
	short
		//002,3 : bit 0 = train(s) on track, bit 1 = tested; bit 2 = test in progress; bit 3 = don't
		//show raw stats; bit 4 = pass through station without stopping; bit 5 = On-Ride photo;
		//bit 6 = ?; bit 7 = broken down; bit 10 = crashed; bit 12 = ever been opened; bit 13 =
		//play music; bit 14 = construction/demolition prohibited (indestructible ride); bit 15 =
		//demolition prohibited (used when there are indestructible track pieces) 
		rideStatusFlags;
	BYTE
		//004 : operating mode 
		opmode,
		//005 : color scheme (in original RCT code) 
		colorScheme;
	struct {BYTE primary,trim;} 
		//006..01D : body and trim colors 
		vehicolors1[12];
	BYTE 
		// 01E..020 : Track primary, secondary, and support colors (original RCT) 
		trackColorScheme[3],
		//021 : ride status - 0 = closed, 1 = open, 2 = test 
		ridestatus;
	short 
		//022..023 : text string index .if MSB of this word is set, use lower 10 bits for user
		//defined string index 
		nameStringIndex;
	long 
		//024..027 : string numerator (all 4 bytes for guest #, two bytes for "rides been on" etc.)
		stringNumerator;
	RCTPOINT 
		//028..029 : Final station entry segment(row, col) 
		overallViewFocus,
		//02A..031 : four sets of row-col bytes for station departure segments 
		stationFoci[4];
	BYTE 
		//032..035 : Station height (one byte for each station) 
		stationHeights[4],
		//036..039 : Station length (one byte for each station) 
		stationLengths[4],
		//03A..03D : Station signal (one byte for each station) [80 = green light, the lower
		//nibble specifies if train moving through signal, waiting for departure control, track not
		//clear, etc.] 
		stationSignal[4],
		//03E..041 : train in loading position (FF = none) (4 stations) 
		trainsInLoadingPos[4];
	RCTPOINT
		//042..049 : four sets of ride Entrance map location (row, col) 
		rideEntrances[4],
		//04A..051 : four sets of ride Exit map location (row, col) 
		rideExits[4];
	short 
		//052..059 : index (2 bytes) of last peep in queue line at station (4 stations) 
		lastQueueGuestIndex[4];
	BYTE
		//05A..05D : Num of peeps in queue line (one byte for each station) 
		guestsInQueue[4];
	WORD 
		//05E..075 : address of sprite data structure for each train. Set to FF for unavailable
		//train numbers. 
		TrainSpriteIndexes[12];
	BYTE 
		//076 : departure flags 
		DepartureControlFlags,
		//077 : # of stations 
		amtStations,
		//078 : # of trains 
		amtTrains,
		//079 : # of cars per train 
		amtCarsPerTrain,
		//07A..07B : ? 
		fill07A[2],
		//07C : max # of trains for current # of cars 
		maxTrains,
		//07D: ? 
		fill07D[1],
		//07E : minimum wait time 
		minWait,
		//07F : maximum wait time 
		maxWait,
		//080 : speed of powered launch/laps/#peeps 
		launchSpeed,
		//081..083 : ? 
		fill081[3],
		//084 : index of Data Logging structure (FF if none) 
		dataLoggingIndex,
		//085 : special track elements: bits 0 through 4: number of helix sections; bit 5= spinning
		//tunnel,water splash, rapids; bit 6= log reverser,waterfall; bit 7= whirlpool 
		specialTrackElements,
		//086,087 : ? 
		fill086[2];
	short 
		//088,089 : max speed lower word 
		maxspeedLo,
		//08A,08B : max speed upper word ~2.25 mph per bit 
		maxspeedHi,
		//08C,8D : avg speed lower word 
		avgspeedLo,
		//08E,8F : avg speed upper word ~2.25 mph per bit 
		avgspeedHi;
	BYTE 
		//090..93 : ? 
		fill090[4];
	long 
		//094..097 : ride length (1st section) - use upper word 
		//098..09B : ride length (2nd section) - use upper word 
		//09C..09F : ride length (3rd section) - use upper word 
		//0A0..0A3 : ride length (4th section) - use upper word 
		rideLengths[4];
	short
		//0A4, 0A5 : ride time (1st section) 
		//0A6, 0A7 : ride time (2nd section) 
		//0A8, 0A9 : ride time (3rd section) 
		//0AA, 0AB : ride time (4th section) 
		rideTimes[4],
		//0AC, 0AD : Maximum positive G force 
		maxPosVertGs,
		//0AE, 0AF : Maximum negative G force 
		maxNegVertGs,
		//0B0, 0B1 : Maximum lateral G force 
		maxLatGs;
	BYTE 
		//0B2..0BD: ? 
		//0BE,0BF : ?related to "curvature" of track 
		//0C0,0C1 : ? 
		//0C2,C3 : ? 
		fill0B2[0x12],
		//0C4: num of inversions (lower 5 bits) 
		inversions,
		//0C5 : num of drops (lower six bits) 
		drops,
		//C6 : ? 
		fill0C6[1],
		//0C7 : max drop height (in 1/3 meters ~ 1 ft) 
		highDrop,
		//0C8..CB : underground track length? 
		//CC,CD : ? 
		//CE : ? 
		//CF.
		fill0C8[8];
	short 
		/*
		0D0		2	Count of customers to enter ride/shop in 
					the current customer count timer interval;
					this value will be inserted into the 
					data queue at the next timer reset--resets 
					to 0 with the timer 			
		*/
		curCustomerCount,
		/*
		0D2		2	Customer count timer--resets at 1,000--			
					see next and previous field
		*/
		customerCountTimer,
		/*
		0D4		2*10	Data queue of 10 WORDs representing 
					the number of customers that entered 
					the ride in each of the last 10 1,000-tick 
					intervals of the customer count timer.
					This queue rotates out and a new 
					value is inserted in the front every timer 
					reset--it may be used to calculate 
					customers per hour
		*/
		lastCustomerCounts[10],
		//0E8,E9: ticket price 
		ticketPrice;
	BYTE
		//0EA..0EF : ? 
		fill13A[6];
	short
		//0F0, 0F1 : Excitement (divide by 100) 
		excitement,
		//0F2, 0F3 : Intensity (divide by 100) 
		intensity,
		//0F4, 0F5 : Nausea (divide by 100) 
		nausea;
	BYTE
		//0F6..0F9 : ? 
		fill0F6[4],
		//0FA : satisfaction (multiply by 5%) (-1 for unknown) 
		satisfaction,
		//0FB..0FF : ? 
		fill0FB[5];
	long
		//100..103 : total customers 
		totalCustomers,
		//104..107 : total profit 
		totalProfit;
	BYTE
		//108		1	popularity (multiply by 4 for percent;
		//			see next two fields)
		curPopularity,
		//109		1	counter which increases every time a guest 
		//			"thinks" about ride--resets at 25
		guestThoughtCount,
		//10A		1	how many positive (ie good) thoughts there are 
		//			out of the count in 159; this value gets 
		//			copied to the popularity rating when the
		//			above thought count reaches 25
		guestGoodThoughtCount,
		//10B : #people on ride 
		numGuestsOnRide,
		//10C..12F : ? 
		fill10C[0X130-0x10C];
	short 
		//130..131 : Month of construction (used to determine ride age) 
		absBuiltMonth,
		//132, 133 : running cost (multiply by $1.60) 
		runningCost;
	BYTE
		//134..142 : ? 
		fill134[0xF],
		//143 : Break Down type: -1=not broken, 0="safety cut-out", 1="restraints stuck
		//closed", 2="restraints stuck open", 3="doors stuck closed", 4="doors stuck open",
		//5="vehicle malfunction", 6="station brakes failure", 7="control failure" 
		breakdownType,
		//144..145 : ? 
		fill144[2],
		//146 : Reliability count down - when zero, Reliability is decremented 
		reliabilityCountdown,
		//147 : Reliability (%) 
		reliability,
		//148: Cheat detection flag? 
		fill148[1],
		//149 : down time (%) 
		downtime,
		//14A: Inspection interval (0 = 10 min, 1 = 20 min, 2 = 30 min, 3 = 45 min, 4 = 1 hr, 5
		//= 2 hr, 6 = never) 
		inspectionFrequency,
		//14B : time since last inspection (minutes) 
		timeSinceLastInspection,
		//14C..15F : ? 
		fill14C[0x160-0X14C];
	long
		//160..163 : Income per hour 
		hourlyIncome,
		//164..167 : profit 
		profit;
	BYTE
		//168 : queue time 
		queuetime,
		//169..16B : ? 
		fill169[0X16C-0X169],
		//16C..177 : track color schemes 
		trackColorSchemes[4][3],
		//178 : music selection (00=Dodgems, 01=Fairground organ, 02=Roman Fanfare,
		//03=Oriental, 04=Martian, 05=Jungle Drums, 06=Egyptian, 07=Toyland, 08=?,
		//09=Space, 0A=Horror, 0B=Techno, 0C=Gentle, 0D=summer, 0E=water, 0F=Wild
		//West, 10=Jurassic, 11=Rock, 12=Ragtime, 13=Fantasy 
		rideMusic,
		//179 : station theming (00=standard, 01=wooden, 02=canvas tent, 03=castle[grey],
		//04=castle[brown], 05=jungle, 06=log cabin, 07=classical, 08=abstract, 09=snow,
		//0A=pagoda, 0B=space) 
		stationTheme,
		//17A..25F : ? 
		fill17A[0x260-0x17A];
} RIDESTRUCT, RIDESTRUCTARRAY[256];

#define RCT_MSGCOLOR_WHITE		0x90	
#define RCT_MSGCOLOR_RED		0x91
#define RCT_MSGCOLOR_GREEN		0x92
#define RCT_MSGCOLOR_GOLD		0x93
#define RCT_MSGCOLOR_BROWN		0x94
#define RCT_MSGCOLOR_GREY		0x95
#define RCT_MSGCOLOR_BLUE		0x96
#define RCT_MSGCOLOR_PURPLE	0x97
#define RCT_MSGCOLOR_BEIGE		0x98
#define RCT_MSGCOLOR_PINK		0x99
#define RCT_MSGCOLOR_AGUA		0x9A
#define RCT_MSGCOLOR_TAN		0x9B
#define RCT_MSGCOLOR_GREEN2	0x9C

#define RCT_MSGICON_HIDE		0
#define RCT_MSGICON_RIDE		1
#define RCT_MSGICON_PERSON		2
#define RCT_MSGICON_COINS		3
#define RCT_MSGICON_BLANK		5
#define RCT_MSGICON_SCENERY	6
#define RCT_MSGICON_CROWD		7
#define RCT_MSGICON_AWARD		8
#define RCT_MSGICON_GRAPH		9

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
{	RCT_EAST,
	RCT_SOUTH,
	RCT_WEST,
	RCT_NORTH
} RCT_DIRECTION;

typedef struct
{	short x,y;
	BYTE z,direction;
} ENTRYPOINTSTRUCT;

#define HIGHFTL 64
#define HIGHFULLFILE 128
#define HIGHFULLREGKEY 256
#define HIGHKEYNAMELENGTH 32
#define HIGHDELIMS 2

#define RCTREGKEYNAME "Software\\Infogrames"\
	"\\RollerCoaster Tycoon 2 Setup"
#define RCTREGVALUENAME "Path"

int GetRct2Path(BYTE *path);

int rctSuspended;
int SuspendRCT();
int ResumeRCT();

#endif //_RCT_