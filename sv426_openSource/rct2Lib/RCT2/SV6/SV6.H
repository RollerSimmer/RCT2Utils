#pragma once

#ifndef SV6_H
#define SV6_H

#ifndef _RCT2_
#endif //_RCT2_

#include"../rct2_chunk.h"
#include<stdtypes.h>
#include"SV6_MAP.H"
#include"SV6_MESSAGES.H"
#include"SV6_RIDES.H"
#include"SV6_SPRITES.H"
#include"SV6_OBJDAT.H"
#include<rct_svx.h>


//#include <objdat.h>
#include <windows.h>
#include <stdtypes.h>

#define RCT2_HIGHSIZE	256

/*FULL VERSION CODE*/




#define NEWELEMENTINDEX	0
#define OLDELEMENTINDEX	1

#define NUMELEMENTINDEXES 2

#define PIECECONSTRUCTOP_ARRAYSIZE	(0X100*4)

#ifndef _RCT2_
BYTE *RCT2_ADDRTRACKPIECECONSTRUCTOPBASE;
#endif//ndef _RCT2_

#define RCT2_ADDRTRACKPIECECONSTRUCTOP(INDEX) \
	(RCT2_ADDRTRACKPIECECONSTRUCTOPBASE \
		+(0X00994638-0X00994638)+(INDEX*PIECECONSTRUCTOP_ARRAYSIZE))

/*Track Piece Cconstruction Parameters*/

/* Map Tile sprite chain start index */
#ifndef _RCT2_
BYTE *_RCT2_ADDR_MAPXYSPRITECHAININDEXES;
#endif//ndef _RCT2_

#define RCT2_ADDR_MAPXYSPRITECHAININDEXES	\
	(_RCT2_ADDR_MAPXYSPRITECHAININDEXES+0)
/* Map Tile sprite chain start index */

//status byte 0
#define RCT2_MASK_OPENCLOSE			0X01 
//status byte 1
#define RCT2_MASK_CHEAT				0X01						
#define RCT2_MASK_USEMONEY			0X08

#ifndef _RCT2_
#define RCT2_WORD_EMPTY ((WORD)(0XFFFF)
#define RCT2_BYTE_EMPTY ((BYTE)(0XFF))
#define RCT2_DWORD_EMPTY ((DWORD)(0XFFFFFFFF))
#endif//ndef _RCT2_

/*
1C	Food Stall (all types)
1E	Drink Stall (all types)
20	Shop (all types)
23	Information Kiosk 
24	Bathroom (both types)   
2D	ATM
30	First Aid
*/
#ifndef _RCT2_

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
#endif//ndef _RCT2_


#define RCT2_NUMSHOPTRACKTYPES	7

#ifndef _RCT2_

BYTE RCT2_SHOPTRACKTYPES[RCT2_NUMSHOPTRACKTYPES];
#endif//ndef _RCT2_

extern int GetRct2Version();
int GetRCT2NameString(BYTE *nameString,WORD nameStringIndex);
int SetRCT2NameString(WORD nameStringIndex,BYTE *nameString);

#define RCT2_UNITSPERDAY	0X844
#define RCT2_DAYSPERMONTH	31
#define RCT2_MONTHSPERYEAR	8

typedef BYTE NAMESTRING[32];

#ifndef _RCT2_

typedef enum
{	RCT2_EAST,
	RCT2_SOUTH,
	RCT2_WEST,
	RCT2_NORTH
} RCT2_DIRECTION;

#endif//ndef _RCT2_


#define HIGHFTL 64
#define HIGHFULLFILE 128
#define HIGHFULLREGKEY 256
#define HIGHKEYNAMELENGTH 32
#define HIGHDELIMS 2

/*
#define RCT2REGKEYNAME "Software\\Infogrames"\
	"\\RollerCoaster Tycoon 2 Setup"
#define RCT2REGVALUENAME "Path"

int GetRct2Path(BYTE *path);

int rct2Suspended;
int SuspendRCT2();
int ResumeRCT2();

#endif //_RCT2_
*/

//#include ""

#ifndef _RCT2_

typedef enum 
{
	FT_RCT2_OBJDAT,
	FT_SC6,
	FT_SV6
} SV6_SC6_FILETYPE;

#endif


/*
Code  	Meaining
00 	Copy the data bytes without change.
01 	RLE
02 	RLE , then string decompression
03 	Rotate sequential bytes right by: 1, then 3, then 5, then 7 bits, then 1 etc.
*/


typedef struct
{
	WORD fileType;
	WORD numImbeddedCustomObjs; 
	DWORD versionMarker/*=120001*/;
	DWORD unk0x08/*=0x00031144*/;
	BYTE unk0x0C[0x20-0x0C];
} SV6_HEADER;

typedef struct
{
	WORD 
		month:3,
		year:13;
	WORD
		day;//DAY = ((Value*16) div 0x8421)+1
	BYTE 
		fill0x04[0x10-0x04];
} SV6_TIMEDATA;








typedef struct
{
	DWORD
		opened:1,
		unk01:1,
		landModProhibit:1,
		prohibitScenRemoval:1,
		realGuestNames:1,
		highConstructProhibit:1,
		lowIntensityGuests:1,
		prohibitAdvertising:1,
		cheat:1,
		highIntensityGuests:1,
		fill10:1,
		notUsingMoney:1,
		difficultGuestSpawning:1,
		freeAttractionEntry:1,
		difficultParkRating:1,
		noRealNames:1,
		fill16:16;
} 
SV6_PARKSTATUS;

typedef struct
{
/*0x0 -- Sprite-related timer */
DWORD spriteTimer;
/*0x4 -- Sprite structures [256][10000]*/
SV6_SPRITESTRUCTARRAY sprites;

/*0x271004 -- Sprite# of next sprite object to be added*/
SPRITESTATS spriteStats;

/*0x27101C -- Offset of park name in name string array - only use the lower 10 bits (the MSB is set if there is a string entry).*/
SVX__STRING_NAME_OFFSET parkNameOffset;
/*0x27101E -- ???*/
BYTE unk0x27101E[6];
/*0x271024 -- Money (10x)  (in dimes for US) */
DWORD money;
/*0x271028 -- Loan (10x)*/
DWORD loan;
/*0x27102C -- Park status:*/
SV6_PARKSTATUS parkStatus;



/*0x271030 -- Admission fee (10x)*/
WORD admissionFee;
/*0x271032 -- Main park entry [3][2] (x,y,z--in that order)*/
MAINENTRANCE_LOCATIONSTRUCT mainParkEntry;


/*0x271039 -- ???*/
BYTE unk0x271039[1];
/*0x27103A -- map entry point structures [2][6] in the following format:*/
ENTRYPOINTSTRUCT peepMapEntryPoints[2];


/*0x271046 -- ???*/
BYTE unk0x271046[1];
/*0x271047 -- Research rate: 0 = none, 1 = minimum, 2 = normal, 3 = maximum*/
BYTE researchRate;
/*0x271048 -- ???*/
BYTE unk0x271048[4];
/*0x27104C -- Rides Menu*/
BYTE ridesMenu[32];
/*0x27106C -- Vehicle Menu (similar to above ride menu - one bit for each vehicle)*/
BYTE vehicleMenu[32];
/*0x27108C -- Ride feature 1 table, [128][4] 128 structures of 4 bytes for each ride.*/
BYTE rideFeatureTable[2][128][4];

/*0x27148C -- Number of guests in park*/
WORD numGuestsInPark;
/*0x27148E -- ?*/
BYTE unk0x27148E[2];
/*0x271490 -- budgetVals [14][8][4]*/
DWORD budgetVals[2][14][8];

/*0x271810 -- ?number of guests in park*/
DWORD unk_numGuestsInPark;
/*0x271814 -- ?*/
BYTE unk0x271814[1];
/*0x271815 -- color for handymen*/
BYTE handmanColor;
/*0x271816 -- color for mechanics*/
BYTE mechanicColor;
/*0x271817 -- color for security guards*/
BYTE securityColor;
/*0x271818 -- Scenery Menu*/
BYTE sceneryMenu[128];
/*0x271898 -- banner menu items: bit 0=standard, 1=jungle, 2=roman, 3=egyptian, 4=mining, 5=jurrasic, 6=asian,7=snow*/
BYTE bannerMenu[2];

/*0x27189A -- ?*/
BYTE unk0x27189A[94];
/*0x2718F8 -- current park rating*/
WORD curParkRating;
/*0x2718FA -- historical park rating (for curve) the low byte is in 19910A through 199129 while the high byte is in 19912A through 199149. an FF indicates 'not used'*/
WORD histParkRating[32];
/*0x27193A -- Research selection: bit 0=Rollercoasters, bit 1 = Thrill rides, bit 2 = Gentle rides, bit 3 = Shops/stalls, bit 4 = Theming, bit 5 = Ride improvements*/
BYTE researchSelection;
/*0x27193B -- research progress description: 0=initial research, 1=designing, 2=completing*/
BYTE researchProgress;
/*0x27193C -- last development - research item*/
BYTE lastDevelopment_Item;
/*0x27193D -- last development - corresponding ride*/
BYTE lastDevelopment_ride;
/*0x27193E -- last development - research category*/
BYTE lastDevelopment_category;
/*0x27193F -- last development - flag*/
BYTE lastDevelopment_flag;
/*0x271940 -- Research items. up to 200 entries of 5 bytes each. Not used in LL (goto 199C9C for LL)*/
BYTE researchItems[1000];
/*0x271D28 -- next development - research item*/
BYTE nextDevelopment_Item;
/*0x271D29 -- next development - corresponding ride*/
BYTE nextDevelopment_ride;
/*0x271D2A -- next development - research category*/
BYTE nextDevelopment_category;
/*0x271D2B -- next development - flag*/
BYTE nextDevelopment_flag;
/*0x271D2C -- ?*/
BYTE unk0x271D2C[2];
/*0x271D2E -- ?*/
BYTE unk0x271D2E[4];
/*0x271D32 -- Cheat detection: count of owned land*/
WORD cheat_ownedLandCount;
/*0x271D34 -- ?*/
BYTE unk0x271D34[1];
/*0x271D35 -- Probabilty of new guest generation*/
BYTE guestGenProbability;

/*0x271D36 -- ?*/
BYTE unk0x271D36[2];
/*0x271D38 -- Max Loan (10x)*/
DWORD maxLoan;
/*0x271D3C -- cash in pocket for new guests*/
WORD newGuest_cash;
/*0x271D3E -- avg hunger of newly generated guests.*/
BYTE newGuest_thirst;
/*0x271D3F -- avg thirst of newly generated guests.*/
BYTE newGuest_hunger;
/*0x271D40 -- scenario goal: 1 = #peeps (& park rating), 2 = park value, 3 = have fun!, 4 = competition, 5 = ten different coasters with excitement at least 6.00, 6 = maintain park rating & #peeps, 7 = monthly ride income, 8 = ten different coasters with excitement a*/
BYTE scenarioGoal;
/*0x271D41 -- number of years to reach goal (10 for competitions)*/
BYTE scenarioTimeLimit_inYears;
/*0x271D42 -- ?*/
BYTE unk0x271D42[2];
/*0x271D44 -- money (park value/ride income) goal / coaster excitement goal (only for goal type 9)*/
DWORD scenarioGoal_dwordValue;
/*0x271D48 -- #peeps goal / minimum coaster length (meters)*/
WORD scenarioGoal_wordValue;
/*0x271D4A -- Advertising, 1 byte for each type, lower 4 bits indicate weeks remaining.*/
ADVERT_BYTE advertising[20];
/*0x271D5E -- 1 Byte for each type of advertising, indicates the ride/food associated with the advertising that displays it.*/
BYTE advertisingItems[6];
/*0x271D64 -- ?*/
BYTE unk0x271D64[16];
/*0x271D74 -- 128 DWords (previous cash values)*/
DWORD prevCashVals[128];
/*0x271F74 -- Recent change in cash*/
DWORD recentCashChange;
/*0x271F78 -- previous recent change in cash multiplied by 7(?)*/
DWORD recentCashChange_x7;
/*0x271F7C -- sum of "recent changes in cash"*/
DWORD recentCashChanges_sum;
/*0x271F80 -- ?*/
BYTE unk0x271F80[2];
/*0x271F82 -- ?*/
BYTE unk0x271F82[2];
/*0x271F84 -- 128 DWords: Weekly Profit over time*/
DWORD weeklyProfitHistory[128];
/*0x272184 -- Park value*/
DWORD parkValue;
/*0x272188 -- 128 DWords: Park Value over time*/
DWORD parkValueHistory[128];
/*0x272388 -- scenario objective value at completion Note: MSB set to indicated objective not met; if bit 0 set - failed objective*/
DWORD scenarioObjectiveValAtCompletion;
/*0x27238C -- Total Admissions*/
DWORD totalAdmissions;
/*0x272390 -- income from admissions*/
DWORD admissionIncome;
/*0x272394 -- Company Value [cash + park value - loan]*/
DWORD companyValue;
/*0x272398 -- ?*/
BYTE unk0x272398[16];
/*0x2723A8 -- park awards - four structures of 4 bytes each. Each structure consists of two words. The first word is a flag to indicate if there is an award(zero=no, nonzero = yes); the second word indicates the award/string as follows: 0=most untidy, 1=tidiest, 2=bes*/
PARKAWARDSTRUCT parkAwards[4];
/*0x2723B8 -- Cost of buy land*/
WORD landPurchaseCost;
/*0x2723BA -- Cost of buy rights*/
WORD rightsPurchaseCost;
/*0x2723BC -- ?*/
BYTE unk0x2723BC[2];
/*0x2723BE -- ?*/
BYTE unk0x2723BE[2];
/*0x2723C0 -- contains 58 BB C3 00 if error detected????*/
DWORD ifError_contains0x00C3BB58;
/*0x2723C4 -- user name (null terminated string)*/
char userName[64];
/*0x272404 -- Version number of game - convert to decimal: first digit is major version number; next two digits are minor version number; last three digits are revision number.*/
DWORD RCT2version;
/*0x272408 -- company value at scenario completion*/
DWORD companyValue_atScenarioCompletion;
/*0x27240C -- 1st financial checksum */
DWORD financialChecksum_1;



/*0x272410 -- number of ride structures used*/
WORD numRideStructsUsed;
/*0x272412 -- negative of number of rides available (for cheat detection)*/
WORD cheat_negNumRidesAvail;
/*0x272414 -- max number of tiles(land) allowed to own (for cheat detection)*/
short cheat_maxOwnedTilesAllowed;
/*0x272416 -- negative of max number of tiles allowed to own*/
short cheat_maxOwnedTilesAllowed_neg;
/*0x272418 -- 3rd financial checksum: [cash - loan - all values in monthly expense/income table.]*/
DWORD financialChecksum_3_unused;
/*0x27241C -- Scenario Slot Number Checksum*/
DWORD checksum_scenarioSlotNumber;
/*0x272420 -- Name of winner; if not won or unknown, the character '?' is used*/
char winnerName[32];
/*0x272440 -- 2nd financial checksum */
DWORD financialChecksum_2;


/*0x272444 -- (copyright notice in SC4 files)*/
char copyrightNotice[40];
/*0x27246C -- 0 in SV4 files, FED3 in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_FED3inSC4;
/*0x27246E -- 0 in SV4 files, F318 in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_F318inSC4;
/*0x272470 -- 0 in SV4 files, B218 in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_B218inSC4;
/*0x272472 -- 0 in SV4 files, 458A in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_458AinSC4;
/*0x272474 -- ?*/
BYTE unk0x272474[2];
/*0x272476 -- ?*/
BYTE unk0x272476[2];
/*0x272478 -- meaning unknown, 32*(park_size - 1)*/
WORD unk_32_x_par_parkSize_minus_1_par;
/*0x27247A -- meaning unknown, value in 199C88 plus 011E*/
WORD unk_value_at_0x272478_plus_011E;
/*0x27247C -- Map Size (width=height)*/
WORD parkSize;



















/*0x27247E -- meaning unknown, value in 199C88 minus 1 (except full size park in which case the value is 0FFF)*/
WORD unk_value_at_0x272478_minus_1_except_fullSizePark;
/*0x272480 -- Same price*/
DWORD samePrice_1;
/*0x272484 -- ?*/
BYTE unk0x272484[2];
/*0x272486 -- ?*/
BYTE unk0x272486[3];
/*0x272489 -- Water color (0=normal, 1=red) -- not used in RCT2, see palette object*/
BYTE waterColor;
/*0x27248A -- ?*/
BYTE unk0x27248A[2];
/*0x27248C -- Research items in LL only*/
BYTE researchItems2[900];
/*0x272810 -- ???*/
BYTE unk0x272810[1600];
/*0x272E50 -- ???*/
BYTE unk0x272E50[2];
/*0x272E52 -- Scenario name (null-terminated)*/
char scenarioName[64];
/*0x272E92 -- Scenario details string  (null-terminated)*/
char scenarioDetailsText[256];
/*0x272F92 -- ?*/
BYTE unk0x272F92[2];
/*0x272F94 -- Same price (new in RCT2)*/
DWORD samePrice_2;
/*0x272F98 -- parkEntryXpos [4][2]: X positions of park entries (32 units per tile; 0x8000 = empty)*/
short parkEntriesXpos[4];
/*0x272FA0 -- parkEntryYpos [4][2]: Y positions of park entries (32 units per tile; 0x8000 = empty)*/
short parkEntriesYpos[4];
/*0x272FA8 -- parkEntryZPos [4][2]: Z positions of park entries*/
short parkEntriesZpos[4];
/*0x272FB0 -- parkEntryFlag [4]: array of 4 bytes; (0=unused; 1=used) */
BYTE parkEntriesUsedFlag[4];
/*0x272FB4 -- Scenario file name (null-terminated)*/
char scenarioFile[68];
/*0x272FF8 -- ? (empty)*/
BYTE unk0x272FF8[3444];
/*0x273D6C -- banner info. [250][8] 8-byte structures*/
BANNERINFOSTRUCT bannerInfo[250];



/*0x27453C -- Names strings [1024][32]*/
char nameStrings[1024][32];




/*0x27C53C -- Incrementing Game Time Counter -- used to trigger various events */
DWORD gameTimeCounter;
/*0x27C540 -- Ride Structures[255][608]*/
RCT2_RIDESTRUCTARRAY rides;
/*0x2A22E0 -- a game time counter - not used as a trigger for any events as far as I can tell*/
WORD gameTimeCounter2;
/*0x2A22E2 -- Horizontal view position (0000 to 1FFF, negated depending on Viewing angle)*/
WORD horzViewPos;
/*0x2A22E4 -- Vertical view position (0000 to 1FFF, negated depending on Viewing angle)*/
WORD vertViewPos;
/*0x2A22E6 -- Viewing Zoom factor (0 = closest, 1 = medium, 2 = far)*/
BYTE zoomFactor;
/*0x2A22E7 -- Viewing angle (0 = from NE, 1 = from NW, 2 = from SW, 3 = from SE)*/
BYTE viewingAngle;







/*0x2A22E8 -- Animation object locations [1000][6]*/
ANIMATIONOBJECTLOCATION animationObjectLocations[2000];









/*0x2A51C8 -- number of animation objects (Park/Ride entry, queue & banner, fountains, etc) points*/
DWORD numAnimationObjects;
/*0x2A51CC -- ?*/
BYTE unk0x2A51CC[12];
/*0x2A51D8 -- progression of scrolling text (start point of scrolling text)*/
WORD scrollingTextProgression;
/*0x2A51DA -- ?*/
BYTE unk0x2A51DA[4];
/*0x2A51DE -- ?*/
BYTE unk0x2A51DE[2];
/*0x2A51E0 -- ?*/
BYTE unk0x2A51E0[116];
/*0x2A5254 -- Data Logging [8][19212] - (graphic charts for G's, etc on rides)*/
BYTE dataLogging[8][19212];
/*0x2CAAB4 -- Next Guest Number*/
DWORD nextGuestNumber;
/*0x2CAAB8 -- another game counter, two upper bits always zero*/
WORD gameTimeCounter3;
/*0x2CAABA -- Individual staff member pathrol areas [200][64][8]*/
BYTE patrolAreas[200][64][8];
/*0x2E3ABA -- Staff type covered patrol areas [4][64][8]*/
BYTE staffTypePatrolAreas[4][64][8];
/*0x2E42BA -- Patrol area flags [200] -- For each byte: Bit 0 is set if there is */
BYTE patrolArea_flags[200];


/*0x2E4382 -- ? - has the value 01 -- staff related*/
BYTE unk0x2E4382[1];
/*0x2E4383 -- ? - has the value 01 -- staff related*/
BYTE unk0x2E4383[1];
/*0x2E4384 -- ? - has the value 01 -- staff related*/
BYTE unk0x2E4384[1];
/*0x2E4385 -- ? - has the value 01 -- staff related*/
BYTE unk0x2E4385[1];
/*0x2E4386 -- ? [8] -- 8 bytes each with values of zero */
BYTE unk0x2E4386[8];
/*0x2E438E -- climate (0=wet, 1=normal, 2=dry, 3=cold)*/
BYTE climate;
/*0x2E438F -- ? - usually has the value 05 but a few scenarios have the value 0B*/
BYTE unk_usually_5_but_someScenarios_8[1];
/*0x2E4390 -- Weather Timer */
WEATHER weather;















/*0x2E439C -- Message structures [268][61]:*/
MESSAGESTRUCTARRAY messages;















/*0x2E8378 -- Scenario name?*/
char scenarioName2[62];
/*0x2E83B6 -- Scenario slot?*/
WORD scenarioSlot;
/*0x2E83B8 -- scenario flags (expansion packs only) bit 12: error while loading*/
DWORD scenarioFlags;
/*0x2E83BC -- Unknown flags*/
WORD unk_flags1;
/*0x2E83BE -- Unknown counter*/
WORD unk_counter1;
/*0x2E83C0 -- ?*/
BYTE unk0x2E83C0[428];
/*0x2E856C -- these last four bytes of the file contain an additional checksum in */
DWORD extraFileChecksum;
}
SV6_PARKDATA;

#define SV6_NUMCHUNKS 5
#define SV6_NUMCHUNKHEADERS SV6_NUMCHUNKS

typedef struct 
{
	union
	{
		struct
		{
			SV6_CHUNKHEADER header_header;
			SV6_CHUNKHEADER availableItems_header;
			SV6_CHUNKHEADER timeData_header;
			SV6_CHUNKHEADER parkMap_header;
			SV6_CHUNKHEADER parkData_header;
		};
		SV6_CHUNKHEADER chunkHeaders[5];
	};
	union
	{
		struct
		{
			SV6_HEADER header;
			//no importObjects
			SV6_OBJDAT_HEADER_BLOCK availableItems;
			SV6_TIMEDATA timeData;
			SV6_PARKMAPDATABLOCK parkMap;
			SV6_PARKDATA parkData;
		};
		BYTE sv6Stream
		[	
			sizeof(SV6_HEADER)
			+sizeof(SV6_OBJDAT_HEADER_BLOCK)
			+sizeof(SV6_TIMEDATA)
			+sizeof(SV6_PARKMAPDATABLOCK)
			+sizeof(SV6_PARKDATA)
		];
	};
} SV6_UNCOMPRESSED_FILEDATA;

#define SV6_UNCOMPRESSED_FILEDATA_SIZE \
	sizeof(SV6_UNCOMPRESSED_FILEDATA)

#ifndef dllPort
#define dllPort __declspec(dllexport)
#endif


typedef char SCANLINE[256][256];

typedef SCANLINE* LPSCANLINE ;
 


typedef dllPort struct SV6_FILE
{
	union 
	{
		SV6_UNCOMPRESSED_FILEDATA
			fileDataA;
		BYTE fileDataB[SV6_UNCOMPRESSED_FILEDATA_SIZE];
	};
	DWORD checkSum; //formed by starting with zero and adding each byte of the file to a 32 bit variable.		

	//map pointers

	short*parkSize;
	SV6_PARKMAPPTRARRAY
		mapPtrs; 
	SV6_PARKMAPDATA*map_nextFree;
	bool ptrsInitted;

	//functions

	dllPort 
		FixObj(int i),
		FixObjs();

	//open/save
	dllPort 
	OpenSv6(char*sv6FileName);
	dllPort 
	SaveSv6(char*sv6FileName);

	//init
	dllPort 
	SV6_FILE();

	dllPort 
	void InitMapPtrs();

	//sprites
	dllPort 
	int	
		FireStaff(),

		CleanPaths(),
		RemoveFloatingObjects(),
		ResetGuestNumbers(),
		GiveAllGuests100Cash(),
		GiveAllGuests1000Cash(),
		PacifyVandals(),
		MakeGuestsHappy(),
		HealNausea(),
		GiveGuestsBurgers(),
		GiveGuestDrinks(),
		HelpGuestsFindRestrooms(),
		VitalizeGuests(),
		GiveGuestsBalloons(),
		HandOutParkMaps(),
		GiveGuestsUmbrellas(),
		AllAroundGuests(),
		WildGuests(),
		TameGuests(),
		RemoveGuests(),
		FreezeGuests(),
		PutPeepsInUniform
		(	WORD shirtColor,WORD pantsColor,
			WORD overridePurchases
		),
		FastStaff(),
		NormalStaff(),
		SlowStaff(),
		FreezeStaff(),

	dllPort 
	int	
		SetAllTrackFeatures(),
		SetTrackFeatures(short trackIndex);

	EmptyRidesOfGuests
	(	SPRITESTATS *spritestats,
		SV6_SPRITESTRUCT*spriteBlock
	);

	int SpriteFunc(SPRITEFUNCCLASS fclass,SPRITEFUNCID func);

	//terrain

	dllPort 
	int SetMapHeight(
		int *init,int done,int x,int y,SV6_PARKMAPPTRARRAY* lpMapPtrs,
		LPSCANLINE scanline, WORD parksize
	);

	dllPort 
	int
	GetMapHeight
	(	int *init,int done,int x,int y,SV6_PARKMAPPTRARRAY* lpMapPtrs,
		LPSCANLINE scanline, WORD parksize
	);

	dllPort 
	int LoadTerrainBMP();
	dllPort 
	int SaveTerrainBMP();

	//map

	dllPort 
	short
	Rct2MapDataFunc
	(	int mapdatafunc,short x,short y,LP_SV6_PARKMAPDATA mapdata,int count
	);

	dllPort 
	int	
	GenNewPark(HMODULE module),
	ChangeMoney(long);

	dllPort 
	int 	
	ClearSprites();


}
SV6_FILE;


typedef struct
{ 
	SV6_CHUNKHEADER header;
	char buffer[100];
} SV6_CHUNK,*LP_SV6_CHUNK;


typedef struct
{
	SV6_OBJDAT_HEADER 
		objHeader;
	SV6_CHUNKHEADER 
		chunkHeader;
}
SV6_OBJDAT_HEADER_AND_CHUNK_HEADER;



#include"SV6_ENCODE.H"
#include"SV6_DECODE.H"


#endif SV6_H
