#pragma once
#ifdef dllPort

#ifndef _RCT_
#define _RCT_

#include <objdat.h>
#include <windows.h>
#include <stdtypes.h>

#include "SV4_MAP.H"
#include "SV4_MESSAGES.H"
#include "SV4_RIDES.H"
#include "SV4_SPRITES.H"
#include "../../shared/svx/svx.h"

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

#define RCT_NUMSHOPTRACKTYPES	7

BYTE RCT_SHOPTRACKTYPES[RCT_NUMSHOPTRACKTYPES];

int GetRctVersion();
int GetRCTNameString(BYTE *nameString,int nameStringIndex);

#define RCT_UNITSPERDAY	0X844
#define RCT_DAYSPERMONTH	31
#define RCT_MONTHSPERYEAR	8

typedef BYTE NAMESTRING[32];

#if 0

typedef enum
{	RCT_EAST,
	RCT_SOUTH,
	RCT_WEST,
	RCT_NORTH
} RCT_DIRECTION;

#endif

/*
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
int ResumeRCT()
*/

#endif //_RCT_

//#include ""

typedef enum 
{
	FT_SV4=0,
	FT_SC4=1
} SV4_SC4_FILETYPE;

/*
Code  	Meaining
00 	Copy the data bytes without change.
01 	RLE
02 	RLE , then string decompression
03 	Rotate sequential bytes right by: 1, then 3, then 5, then 7 bits, then 1 etc.
*/

/*
typedef enum
{
	ET_LITERAL,
	ET_RLE,
	ET_RLE_STRING,
	ET_ROTATE_1357,
}
SV4_ENCODETYPE;
*/

typedef struct
{
	BYTE encodeType;
	DWORD chunkSize_Encoded;
} SV4_CHUNKHEADER;

typedef struct
{
	WORD fileType;
	WORD numImbeddedCustomObjs; 
	DWORD versionMarker/*=120001*/;
	DWORD unk0x08/*=0x00031144*/;
	DWORD unk0x0C[0x20-0x0C];
} SV4_HEADER;

typedef struct
{
	WORD 
		month:3,
		_year:13;
	WORD
		day;//DAY = ((Value*16) div 0x8421)+1
	BYTE 
		fill0x04[0x10-0x04];
} SV4_TIMEDATA;


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
SV4_PARKSTATUS;


//#ifndef
//#define


//#endif

//typedef struct{}SV4_PARKDATA;
#include "SV4_SV4_PARKDATA.inl"

typedef struct 
{
	SV4_PARKDATA parkData;
} SV4_UNCOMPRESSED_FILEDATA;

#define SV4_UNCOMPRESSED_FILEDATA_SIZE \
	sizeof(SV4_UNCOMPRESSED_FILEDATA)

typedef struct
{
	union 
	{
		SV4_UNCOMPRESSED_FILEDATA
			fileDataA;
		BYTE fileDataB[SV4_UNCOMPRESSED_FILEDATA_SIZE];
	};
	DWORD checkSum; //formed by starting with zero and adding each byte of the file to a 32 bit variable.

	int
	dllPort
	OpenSv4(char*)
	//,SaveSv4(char*)
	,DecodeSv4(BYTE*inFileStream,long sv4CompressedSize)
	;
}
SV4_FILE;

#endif //dllPort

