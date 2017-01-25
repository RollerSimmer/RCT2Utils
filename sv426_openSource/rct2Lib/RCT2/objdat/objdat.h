#ifndef _OBJDAT_
#define _OBJDAT_

#include<img256_lib.h>
#include "../iso/iso.h"

// header to go into another file

//ride ids

#include <stdtypes.h>
#include"../rct2_chunk.h"
//#include"../rct2.h"
#include<FileIO2.h>

#ifdef OBJDAT_ALL__CPP
	#ifndef dllPort
		#define dllPort __declspec(dllexport) 
	#endif
#else
	#ifndef dllPort
		#define dllPort __declspec(dllimport) 
	#endif
#endif// OBJDAT_ALL__CPP



typedef enum
{
	OT_RIDESHOP			=0,
	OT_SMALLSCENERY		=1,
	OT_LARGESCENERY		=2,
	OT_WALL				=3,
	OT_PATHBANNER		=4,
	OT_PATH				=5,
	OT_PATHADDITIONS	=6,
	OT_SCENERYGROUP		=7,
	OT_PARKENTRANCE		=8,
	OT_WATER			=9,
	OT_SCENTEXT			=10,
	OT__NUM_TYPES		=11,
} OBJECTTYPEID;

//Producer types
enum
{
	PROD_STANDARD=8,
	PROD_EXPANSION_BASE=1,
	PROD_CUSTOM=0
};
#define PROD_EXPANSION(a) (PROD_EXPANSION_BASE+a)

//type 1 flags

//end; 

#define  T1_FULLSQUARE		0x00000001
//
#define  T1_OFFSET			0x00000002	//Image vertical reference is based on the center
										//of the tile (else: it is based on the top of the tile)
#define T1_FLAT				0x00000004	//Must be on a flat surface. Also, walls can't
										//occupy the same tile
#define T1_RARROW			0x00000008	//Provide a rotation button in the scenery dialog
#define T1_ANIMATION		0x00000010	//Animated object = multiple frames and
										//animation sequence present
#define T1_GARDEN_DRAW		0x00000020	//garden draw logic - three frames which
										//progress over time without water (wither)
#define T1_GARDEN_UNK		0x00000040	//garden draw logic - the frames can regress with
										//water (allows handymen to water them)
#define T1_DRAW2DIALOG		0x00000080	//Combine the first 2 frames when drawing the
										//item in the scenery dialog
#define T1_SPACEA			0x00000100	//Diagonal object - check T1_SPACEC
#define T1_GLASS			0x00000200	//A "glass" object: the first image is the "frame"
										//and the second image is the "glass"
#define T1_REMAP_1	0x00000400	//Uses the first remappable color
#define T1_1SPRAY			0x00000800	//Use fountain drawing logic = 2 frames: the first
										//frame is stationary and the second is animated
#define T1_4SPRAY			0x00001000	//Use fountain/4 drawing logic = the first frame is
										//stationary; there are "back" and "front"
										//animations (for 4 fountain sprays)
#define T1_CLOCK			0x00002000	//Use clock drawing logic = the first frame is
										//stationary; there are two animations (the hands
										//of the clock - which are timed to real time)
#define T1_SWAMPGOO			0x00004000	//Use the same image for all 4 views; plus
										//animate 16 frames
#define T1_ANIMDATA			0x00008000
										//Has animation sequence data (a sequence after
										//the "Group Info")
#define T1_DRAW2MAIN		0x00010000	//This specifies that the object should use 2
										//frames instead of 1 for the object on the main
										//game screen
#define T1_STACK			0x00020000	//Can be stacked and/or placed on water (e.g.
										//trees dont have this bit set)
#define T1_NOWALLS			0x00040000	//Specifies that no walls may be built at the same
										//location as this object (can be built below and
										//above)
#define T1_REMAP_2			0x00080000	//Uses the second remappable color
#define T1_NOSUPPORTS		0x00100000	//No supports - useful for "building" components:
										//walls/roofs, etc
#define T1_DIALOGFRAMES		0x00200000	//First set of frames are only for the scenery
										//dialog
#define T1_SMALL_COG		0x00400000	//? - only used for the small cogwheel
#define T1_UNKNOWN			0x00800000	//? - unknown
#define T1_SPACEB			0x01000000	//Occupies half of a tile
#define T1_SPACEC			0x02000000	//Occupies 3/4 of a tile - T1_SPACEA must be
										//set also
#define T1_PAINT_SUPPORTS	0x04000000	//Supports are painted with the first remappable
										//color (else they are painted black)
#define T1_POLE				0x08000000	//? - only used for suppleg1.dat
#define T1_RESA				0x10000000	//unused
#define T1_RESB				0x20000000	//unused
#define T1_RESC				0x40000000	//unused
#define T1_RESD				0x80000000

#define OBJDAT_CHECKSUM_STARTVALUE 0xF369A75B

typedef struct 
{	
	union
	{
		long flags;
		BYTE flagBytes[4];
		struct{BYTE lo:4,hi:4;}
			flagNibbles[4];
	};
	char filename[8];
	long checksum;
} OBJDATHEADER;

typedef enum
{	RC_TRANSPORT=		0,
	RC_GENTLE=			1,
	RC_ROLLERCOASTER=	2,
	RC_THRILL=			3,
	RC_WATER=			4,
	RC_SHOPSTALL=		5,
} RIDECLASS;

#define NUMRIDECLASSFIELDS	2
#define MAXNUMSTALLITEMS	2

#define HIGHEINRATING	0X2F


typedef struct 
{
	WORD 
		reserved000;
	DWORD
		reserved002;
	WORD
		reserved006;
	DWORD
		flags;	
	BYTE
		TrackType[3],
		minCarsPerTrain, 
		maxCarsPerTrain,
		numTrains,		// 0xFF indicates a variable number
							// of vehicles 
		fill012[0x14-0x12],	//012: 0 for shops/flat rides 
							//013: 0 for shops/flat rides 
		numLeadVehicles,	// number of special lead vehicles
							// eg. locomotive engine and tender = 2 
		fill015[0x019-0x015],	// all 0xFF for
								// shops/flat rides 
		unused019,			// always zero in files 

		rideWindowMaxAnims,	// byte; // number of animations used
							// in ride control window : vehicle display (-1) 
		unused01B[3],		// always zero in files
		fill01E[0x021-0x01E],		// 01E: 192 in shops 
									// 01F: 32 in shops 
									// 020: 2 in shops 
		unused021,			// always zero in files 
		fill022[0x025-0x022],	// 022: 0 for shops 
								// 023: unknown08       : byte; // 0 for shops 
								// 024: unknown09       : byte; // 0 for shops 
		numPassengersFirstVehicle,	// high bit is set in
									// some cases - purpose unknown 
		grahicsRenders,				// bits set to indicate if there
									//	are graphics for various items: bit 0 for flat, bit 1 for
									// gentle slope, bit 2 for steep slope 
		fill027,					// 0 for shops/flat rides 
		animRegionWidth,				// offset horizontally of
									// animation region 
		animRegionTop,				// offset above center to top of
									// animation region 
		animRegionBottom,			// offset below center to bottom
									// of animation region 
		fill02B[0x030-0x02B],		// 2B: 0 in shops/flat rides 
									// 02C: unknown12       : byte; // 0 in shops 
									// 02D: unknown13       : byte; // 4 in shops 
									// 02E: unknown14       : byte; // 0 in shops 
									// 02F: unknown15       : byte; // 0 in shops 
		unused030[62],				// always zero in files 
		fill06E,					// 0 in shops 
		spinningVehicle,			// nonzero value indicates the
									// vehicle spins as it moves 
		fill070[0x075-0x070];		// 070: 0 in shops/flat rides 
									// 071: 0xFF in shops/flat rides 
									// 072: 0 in shops/flat rides 
									// 073: 0xFF in shops 
									// 074: 0 in shops/flat rides 
	WORD	
		defaultSpeed1;
	BYTE
		unknown077[0X07A-0X077],	// 077: 1 in shops 
									// 078: unknown23       
									// 079: 1 in shops/flat rides 									// 079: unknown24       : byte; // 6 in shops 
		fill07A[96];					// 0's in shops/flat rides 
	WORD
		defaultSpeed2;
	BYTE
		fill0DC[214],		// 0's in shops/flat rides 
		//1B2:
		excitementFactor,
		//1B3:
		intensityFactor,
		//1B4:
		nauseaFactor,
		//1B5:
		maxTrackHeight,
		//1B6
		rideFeatureOverlayMask[8],	// similar to ride feature 
									// tables in RCT1 - used as 
									// a mask to overlay track default 
		//1BE:
		rideclass[NUMRIDECLASSFIELDS],
		stallItem[MAXNUMSTALLITEMS];	// 0xFF if not a stall,
									// otherwise, is an index to the item 

} TYPE0HEADER;




typedef enum
{
    T0_FLAT				= 0x00000001,	//no horizontal movement of vehicle  
										//only rotation
    T0_UNK_01			= 0x00000002,	// 
    T0_UNUSED_01		= 0x00000004,	// 
    T0_UNK_02			= 0x00000008,	// 
    T0_UNK_03			= 0x00000010,	// 
    T0_TWISTER			= 0x00000020,	// 
    T0_ENTERPRISE		= 0x00000040,	// 
    T0_UNUSED_02		= 0x00000080,	// 
    T0_GETWET			= 0x00000100,	// guests get wet when they
										// go on this ride (?) 
    T0_COASTER_BOATS	= 0x00000200,	// 
    T0_COVERED			= 0x00000400,	// indicates a "covered"
										// ride - preferred when raining 
    T0_UNK_04			= 0x00000800,	// 
    T0_UNK_05			= 0x00001000,	// 
    T0_UNK_06			= 0x00002000,	// 
    T0_UNK_07			= 0x00004000,	// 
    T0_UNK_08			= 0x00008000,	// 
    T0_SPIN_WILD_MOUSE	= 0x00010000,	// 
    T0_UNUSED_03		= 0x00020000,	// 
    T0_UNK_09			= 0x00040000,	// 
    T0_NOREMAP			= 0x00080000,	// prevent the user from
										// being able to remap map 1 colors. 
    T0_MAGIC_CARPET		= 0x00100000	// 
}	TYPE0FLAGS;

typedef enum
{
	ITEMID_BALLOON			=  0, 
	ITEMID_SOUVENIR		=  1, 
	ITEMID_MAP				=  2, 
	ITEMID_UMBRELLA		=  4, 
	ITEMID_DRINK			=  5, 
	ITEMID_BURGER			=  6, 
	ITEMID_FRIES			=  7, 
	ITEMID_ICECREAM		=  8, 
	ITEMID_COTTONCANDY		=  9, 
	ITEMID_PIZZA			= 13, 
	ITEMID_POPCPRN			= 15, 
	ITEMID_HOTDOG			= 16, 
	ITEMID_SEAFOOD			= 17, 
	ITEMID_HAT				= 18, 
	ITEMID_CANDYAPPLE		= 19, 
	ITEMID_TSHIRT			= 20, 
	ITEMID_DOUGHNUT		= 21, 
	ITEMID_COFFEE			= 22, 
	ITEMID_CHICKEN			= 24, 
	ITEMID_LEMONADE		= 25, 
	ITEMID_PRETZEL			= 35, 
	ITEMID_HOTTCHOCOLATE	= 36, 
	ITEMID_ICETEA			= 37, 
	ITEMID_FUNNELCAKE      = 38, 
	ITEMID_SUNGLASES		= 39, 
	ITEMID_BEEFNOODLE		= 40, 
	ITEMID_FRIEDRICE		= 41, 
	ITEMID_WONTONSOUP		= 42, 
	ITEMID_MEATBALLSOUP	= 43, 
	ITEMID_STARFRUITDRINK	= 44, 
	ITEMID_SOYBEANMILK		= 45, 
	ITEMID_SUJONKWADRINK	= 46, 
	ITEMID_SUBSANDWICH		= 47, 
	ITEMID_COOKIE			= 48, 
	ITEMID_ROASTSAUSAGE		= 52
} RCT2_ITEMTYPE;	

typedef enum
{
	TRACK_FOODSTALL		= 0x1C,	// clearance 4 
	TRACK_DRINKSTALL	= 0x1E,	// clearance 4 
	TRACK_SOUVENIR		= 0x20,	// clearance 4 
	TRACK_INFPOKIOSK	= 0x23,	// clearance 3 
	TRACK_RESTROOM		= 0x24,	// clearance 2 
	TRACK_ATM			= 0x2D,	// clearance 2 
	TRACK_FIRSTAID		= 0x30	// clearance 3 
} RCT2_TRACKTYPE;

/*

const 
    T0_UNK_00         = $00000001; // 
    T0_UNK_01         = $00000002; // 
    T0_UNUSED_01      = $00000004; // 
    T0_UNK_02         = $00000008; // 
    T0_UNK_03         = $00000010; // 
    T0_TWISTER        = $00000020; // 
    T0_ENTERPRISE     = $00000040; // 
    T0_UNUSED_02      = $00000080; // 
    T0_GET_WET        = $00000100; // guests get wet when they
go on this ride (?) 
    T0_COASTER_BOATS  = $00000200; // 
    T0_COVERED        = $00000400; // indicates a "covered"
ride - preferred when raining 
    T0_UNK_04         = $00000800; // 
    T0_UNK_05         = $00001000; // 
    T0_UNK_06         = $00002000; // 
    T0_UNK_07         = $00004000; // 
    T0_UNK_08         = $00008000; // 
    T0_SPIN_WILD_MOUSE= $00010000; // 
    T0_UNUSED_03      = $00020000; // 
    T0_UNK_09         = $00040000; // 
    T0_NO_REMAP       = $00080000; // prevent the user from
being able to remap map 1 colors. 
    T0_MAGIC_CARPET   = $00100000; // 

    Item_Balloon         =  0; 
    Item_Souvenir        =  1; 
    Item_Map             =  2; 
    Item_Umbrella        =  4; 
    Item_Drink           =  5; 
    Item_Burger          =  6; 
    Item_Fries           =  7; 
    Item_IceCream        =  8; 
    Item_CandyFloss      =  9; 
    Item_Pizza           = 13; 
    Item_PopCorn         = 15; 
    Item_HotDog          = 16; 
    Item_Seafood         = 17; 
    Item_Hat             = 18; 
    Item_CandyApple      = 19; 
    Item_Tshirt          = 20; 
    Item_Doughnut        = 21; 
    Item_Coffee          = 22; 
    Item_Chicken         = 24; 
    Item_Lemonade        = 25; 
    Item_Pretzel         = 35; 
    Item_HotChocolate    = 36; 
    Item_IceTea          = 37; 
    Item_FunnelCake      = 38; 
    Item_SunGlasses      = 39; 
    Item_BeefNoodle      = 40; 
    Item_FriedRiceNoodle = 41; 
    Item_WontonSoup      = 42; 
    Item_MeatBallSoup    = 43; 
    Item_StarFruitDrink  = 44; 
    Item_SoybeanMilk     = 45; 
    Item_SujonkwaDrink   = 46; 
    Item_SubSandwich     = 47; 
    Item_Cookie          = 48; 
    Item_RoastSausage    = 52; 

    Track_FoodStall      = $1C;    // clearance 4 
    Track_DrinkStall     = $1E;    // clearance 4 
    Track_Souvenir       = $20;    // clearance 4 
    Track_InfoKiosk      = $23;    // clearance 3 
    Track_Restroom       = $24;    // clearance 2 
    Track_ATM            = $2D;    // clearance 2 
    Track_FirstAid       = $30;    // clearance 3 

*/

typedef struct 
{
	WORD
		MsgRef;			     // zero 
	DWORD
		fill02,
		flags;				// zero 
	BYTE 
		height,
		cursorsel;
	short
		buildfee,
		removefee;
	DWORD
		graphicsStart;		// -- zero in DAT files
	WORD 
		animDelay,
		animCountMask,		// -- bits0..4: animation counter mask(ie. sequence length - 1) bit 5: 0=continuous animation
		animSeqLength;		// 0x80 max
	BYTE
		BaseIndex,
		fill1B;				// zero in DAT files 
} TYPE1HEADER;

typedef struct
{
	WORD
		reserved0; // Always zero in files 
	DWORD
		reserved1; // Always zero in files 
	char
		CursorSel,
		flags;		// bit 3 = 3D sign 
	WORD
		BuildFee;
	short 
		RemoveFee;
	DWORD
		reserved2;
	BYTE
		reserved3,	// Always zero in files 
		scrolling;	// 0xFF if not scrolling, otherwise,
					//indicates scrolling direction, location 
	DWORD
		reserved4, // Always zero in files 
		reserved5; // Always zero in files 
} TYPE2HEADER;

typedef enum 
{
	T2_NOFLAGS=		0x00,
	T2_REMAP_1=		0x01,		//uses first color selection
	T2_REMAP_2=		0x02,		//uses second color selection
	T2_3DTEXT=		0x04,
	T2_SCROLL=		0x08,		//uses standard scrolling text technique
	T2_PHOTOGENIC=	0x10,		//guests appreciate the scenery object (and
								//photograph it)
	T2_UNUSED_1=	0x20,		//unused
	T2_UNUSED_2=	0x40,		//unused
	T2_UNUSED_3=	0x80,		//unused
} T2_FLAGS;

#define T2_3DLETTERTABLESIZE	0x40E
						   
typedef struct
{
	short
		Row,				// div by 32  (0xffff means end of list)
		Col,				// div by 32 
		Z;					// div by 16 
	BYTE
		clearance,			// shr by 2 
		unknown1,			// 
		flags;				// upper nibble=tile occupation (F=full
							//	tile), lower nibble=walls (0=all sides) 
} TYPE2TILESPEC,*TYPE2TILESPECPTR;

typedef struct 
{
	WORD reserved00;	// Always zero in files 
	DWORD reserved02;	// Always zero in files 
	BYTE cursorsel,
		Flags,
		clearance,
		effects;		// first nibble = visibility (0 = opaque),upper nibble: 1 = animated (8 frames) 
	WORD
		buildFee;		// *10. 
	BYTE
		reserved0C,		// Always zero in files 
		scrolling;		// 0xFF if not scrolling 
} TYPE3HEADER;


typedef struct 
{	// Banners : length = 12. 
	WORD
		reserved0;	// always zero 
	DWORD
		reserved1;	// always zero 
	BYTE
		Scrolling,	// 0xFF if not scrolling, otherwise,
					// indicates scrolling direction, location 
		Flags;		
	WORD
		BuildFee,	// X 10. refund is 75% (rounded down) 
		reserved2;	// always zero 
} TYPE4HEADER;

typedef enum
{
	T4_REMAP_1=		0x01	//uses first color selection
} T4_FLAGS;

#define TYPE5HEADER_SIZE 0x0E

typedef struct 
{
	BYTE data[TYPE5HEADER_SIZE];
} TYPE5HEADER;

typedef struct 
{	// Path Additions : length = 14. 
	WORD
		reserved0;	// Always zero in files 
	DWORD
		reserved1;	// Always zero in files 
	WORD
		Flags;	
	BYTE
		Subtype,
		CursorSel;
	WORD
		BuildFee;	// X 10. 
	BYTE
		reserved2,	// Always zero in files 
		unknown1;	// Always zero in files 
} TYPE6HEADER; 

typedef enum
{
	T6_HOLDTRASH=		0x0001,	//has an extra static frame
	T6_CANSIT=			0x0002,	//	
	T6_CANVANDAL=		0x0004,	//has second static frame
	T6_LIGHT=		    0x0008,	
	T6_JUMPFOUNTAIN=	0x0010,
	T6_JUMPSNOWBALL=    0x0020,
	T6_UNKNOWN1=	    0x0040,	//set for benches and jumping
								//fountains/snowballs and Litter bins
	T6_UNKNOWN2=	    0x0080,	//set for benches and jumping
								//fountains/snowballs
	T6_QLINETV=		    0x0100
} T6_FLAGS;


#define TYPE7HEADER_SIZE 0x10E

typedef struct 
{
	BYTE data[TYPE7HEADER_SIZE];	
} TYPE7HEADER;

#define TYPE8HEADER_SIZE 0x08

typedef struct 
{
	BYTE data[TYPE8HEADER_SIZE];	
} TYPE8HEADER;

/*
Subtypes: 
0 = Lamp (edge centered, 1 dialog view, 2 frames of static (normal and vandalized) 
1 = Litter bin (edge centered/inset, 1 dialog view, 3 frames of static (normal and
vandalized, and full) 
2 = Bench (edge centered/inset, 1 dialog view, 2 frames of static (normal and
vandalized) 
3 = Jump fountain (corners, 1 dialog view, 1 frame of static) 
*/

// 9 Water 0x10 1 No 0 Yes 

typedef struct
{	// "Water" -- Color palette : length = 16. 
	BYTE fill00[0x10]; //filled with zeros 
} TYPE9HEADER;
  
#define TYPE10HEADER_SIZE 0x08

typedef struct 
{
	BYTE data[TYPE10HEADER_SIZE];	
} TYPE10HEADER;

/*	
typedef struct 
{
} TYPE2HEADER;
typedef struct 
{
} TYPE3HEADER;
typedef struct 
{
} TYPE4HEADER;
typedef struct 
{
} TYPE6HEADER;
typedef struct 
{
} TYPE7HEADER;
typedef struct 
{
} TYPE8HEADER;
typedef struct 
{
} TYPE9HEADER;
*/

typedef union
{	
	union{TYPE0HEADER typ0,typRide;};
	union{TYPE1HEADER typ1,typSScen;};
	union{TYPE2HEADER typ2,typLScen;};
	union{TYPE3HEADER typ3,typWalls;};
	union{TYPE4HEADER typ4,typBanners;};
	union{TYPE5HEADER typ5,typPaths;};
	union{TYPE6HEADER typ6,typPathAdd;};
	union{TYPE7HEADER typ7,typGroup;};
	union{TYPE8HEADER typ8,typEntrance;};
	union{TYPE9HEADER typ9,typWater;};
	union{TYPE10HEADER typ10,typSText;};
} TYPESPECHEADER;

//String Table(s): Folowing the Object Header 
//is a string table containing text in different
//languages.Each string begins with a byte to specify the language. 

typedef enum
{
	LNG_UKENGLISH	=0,
	LNG_USENGLISH	=1,
	LNG_FRENCH		=2,
	LNG_DEUTCSH		=3,
	LNG_SPANISH		=4,
	LNG_ITALIAN		=5,
	LNG_DUTCH		=6,
	LNG_SVERIGE		=7,
	LNG_KOREAN		=9,
	LNG_CHINESE1	=10,
	LNG_CHINESE2	=11,
	LNG_PORTUGESE	=13,
	LNG_DONE	=BYTE(0xff)
} STRTBLLANGUAGE;

//Group Info: a sixteen byte structure. There is a four byte value. This is followed by an
//eight byte string indicating which scenery group file this item belongs to (if any). That is
//followed by a 4-byte value. 

typedef struct
{	long flag; //(first byte is 0xFF if default item - 87 otherwise) 
	char filename[8];
	long Reserved;
} DATGROUPINFO;

//Image directory: First is a 4-byte value which specifies how many images are in the file.
//Then a 4-byte value which specifies the length of the scan line graphic data (starting after
//the image directory). Then there is a sixteen byte entry for each image. It uses the same
//format as the csg1i.dat file of RCT1. 

#define IMG_IF_IMAGEDATA	1
#define IMG_IF_COMPACT	4
#define IMG_IF_PALETTE	8
#define IMG_IF_IMAGEDATA_COMPACT \
	(IMG_IF_IMAGEDATA|IMG_IF_COMPACT)

typedef struct
{
	DWORD startaddress;
	short
		width,height,xofs,yofs; // signed 
	WORD 
		flags, 
		unused; // to pad the structure to 16 bytes 
} DATGRAPHINFOSTRUCT;

typedef struct
{
	BYTE numBytes:7,rowEnd:1;
	BYTE xofs;
	BYTE imgData[];
}
	DAT_GRAPH__COMPRESSED_SCANLINE_RECORD;

	

//StartAddress points to the start of the scan line index in the file. It is an offset rather than
//an absolute address - the first scan line index has a StartAddress of 00000000. 

// end of header to go into another file


#define RCT2_OBJMAX_RIDES			128
#define RCT2_OBJMAX_SMALLSCENERY	252
#define RCT2_OBJMAX_LARGESCENERY	128
#define RCT2_OBJMAX_WALLS			128
#define RCT2_OBJMAX_BANNERS			32
#define RCT2_OBJMAX_PATHS			16	
#define RCT2_OBJMAX_PATHADDITIONS	15
#define RCT2_OBJMAX_THEMEGROUPS		19
#define RCT2_OBJMAX_PARKENTRANCES	1
#define RCT2_OBJMAX_WATER			1
#define RCT2_OBJMAX_SCENARIOTEXT	1

const short
	RCT2_RIDES__BASE_TABLE_INDEX=
		0,
	RCT2_SMALLSCENERY__BASE_TABLE_INDEX=
		RCT2_RIDES__BASE_TABLE_INDEX+RCT2_OBJMAX_RIDES,
	RCT2_LARGESCENERY__BASE_TABLE_INDEX=
		RCT2_SMALLSCENERY__BASE_TABLE_INDEX+RCT2_OBJMAX_SMALLSCENERY,
	RCT2_WALLS__BASE_TABLE_INDEX=	
		RCT2_LARGESCENERY__BASE_TABLE_INDEX+RCT2_OBJMAX_LARGESCENERY,
	RCT2_BANNERS__BASE_TABLE_INDEX=
		RCT2_WALLS__BASE_TABLE_INDEX+RCT2_OBJMAX_WALLS,
	RCT2_PATHS__BASE_TABLE_INDEX=
		RCT2_BANNERS__BASE_TABLE_INDEX+RCT2_OBJMAX_BANNERS,
	RCT2_PATHADDITIONS__BASE_TABLE_INDEX=
		RCT2_PATHS__BASE_TABLE_INDEX+RCT2_OBJMAX_PATHS,
	RCT2_THEMEGROUPS__BASE_TABLE_INDEX=
		RCT2_PATHADDITIONS__BASE_TABLE_INDEX+RCT2_OBJMAX_PATHADDITIONS,
	RCT2_PARKENTRANCES__BASE_TABLE_INDEX=
		RCT2_THEMEGROUPS__BASE_TABLE_INDEX+RCT2_OBJMAX_THEMEGROUPS,
	RCT2_WATER__BASE_TABLE_INDEX=
		RCT2_PARKENTRANCES__BASE_TABLE_INDEX+RCT2_OBJMAX_PARKENTRANCES,
	RCT2_SCENARIOTEXT__BASE_TABLE_INDEX=
		RCT2_WATER__BASE_TABLE_INDEX+RCT2_OBJMAX_WATER,
	RCT2__TABLE_END___BASE_TABLE_INDEX=
		RCT2_SCENARIOTEXT__BASE_TABLE_INDEX+RCT2_OBJMAX_SCENARIOTEXT,
	RCT2_BASES[]=
	{
		RCT2_RIDES__BASE_TABLE_INDEX,
		RCT2_SMALLSCENERY__BASE_TABLE_INDEX,
		RCT2_LARGESCENERY__BASE_TABLE_INDEX,
		RCT2_WALLS__BASE_TABLE_INDEX,	
		RCT2_BANNERS__BASE_TABLE_INDEX,
		RCT2_PATHS__BASE_TABLE_INDEX,
		RCT2_PATHADDITIONS__BASE_TABLE_INDEX,
		RCT2_THEMEGROUPS__BASE_TABLE_INDEX,
		RCT2_PARKENTRANCES__BASE_TABLE_INDEX,
		RCT2_WATER__BASE_TABLE_INDEX,
		RCT2_SCENARIOTEXT__BASE_TABLE_INDEX,
		RCT2__TABLE_END___BASE_TABLE_INDEX
	};







#define RCT2__OBJDAT__STRING_TABLE__ENTRY__MAX_LENGTH \
	0x100

#define RCT2__OBJDAT__STRING_TABLE__ENTRY__NUM_LANGUAGES \
	14

typedef struct
{
	struct
	{
		BYTE lang;
		char 
			text
			[RCT2__OBJDAT__STRING_TABLE__ENTRY__MAX_LENGTH];
	}
		entries[RCT2__OBJDAT__STRING_TABLE__ENTRY__NUM_LANGUAGES];
} 
	RCT2__OBJDAT__STRING_TABLE;
		
typedef struct
{	OBJDATHEADER objFileHeader;
	SV6_CHUNKHEADER chunkHdr;
	BYTE *chunk;
}
	OBJDAT_FILE__ENCODED;

#define CHUNK_DATA__MAX_SIZE 10000000

#define GROUP_OBJECTS__MAX 0x100
#define LARGE_SCENERY__MAX_SIZE 12
#define LARGE_SCENERY__MAX_POS_STRUCTS \
	(LARGE_SCENERY__MAX_SIZE*LARGE_SCENERY__MAX_SIZE)
#define RIDE__MAX_LOADING_POS_STRUCTS 2000

#define SMALL_SCENERY__MAX_ANIMATION_SEQUENCE_SIZE 1000

typedef struct
{
	union
	{
		WORD eosTest;
		struct
		{
			short 
				y,x,	//*32
				baseHeight;//*16
			BYTE
				clearanceHeight;//*8
			union
			{
				struct
				{
					BYTE 
						unk0:1,unk1:1,unk2:1,unk3:1,
						unk4:1,noSupports:1,unk6:1,unk7:1;
				};
				BYTE
					unkFlags;	
			};
			union
			{
				struct
				{
					BYTE 
						wall1:1,wall2:1,wall3:1,wall4:1, 
						quad1:1,quad2:1,quad3:1,quad4:1;
				};
				BYTE
					wallQuad;		
			};
		};
	};
}
	LARGE_SCENERY__POS_STRUCT;

typedef struct 
{
	BYTE animationSequence[SMALL_SCENERY__MAX_ANIMATION_SEQUENCE_SIZE];
}
	OPTIONAL__SMALL_SCENERY;

typedef struct OPTIONAL__LARGE_SCENERY
{
	BYTE _3dLetters[0x40e];
	LARGE_SCENERY__POS_STRUCT
		tilePos[LARGE_SCENERY__MAX_POS_STRUCTS];
}
	OPTIONAL__LARGE_SCENERY;
	


#define OPTIONAL__SCENERY_GROUP__MAX_ENTRIES 0x100

typedef struct 
{
	union
	{
		BYTE eosTest;
		OBJDATHEADER header;
	}
		dats[OPTIONAL__SCENERY_GROUP__MAX_ENTRIES];
}
	OPTIONAL__SCENERY_GROUP;
	
typedef union
{
	struct
	{
		BYTE numColorSchemes;
		struct{BYTE x,y,z;}
			colorSchemes[32];
		struct
		{
			WORD numLoadingPositions;
			struct{BYTE x:4,y:4;}
				loadingPos[RIDE__MAX_LOADING_POS_STRUCTS];
		}
			vehicleLoad[4];
	}
		ride;
	
	OPTIONAL__SMALL_SCENERY
		smallScenery;		
	OPTIONAL__LARGE_SCENERY
		largeScenery;
	OBJDATHEADER groupObjs[GROUP_OBJECTS__MAX];
}
	RCT2__OBJDAT__OPTIONAL_AREA;


enum
{
	IMG_ENCD_TYPE__RAW=1,
	IMG_ENCD_TYPE__=5,

};

dllPort 
typedef struct OBJDAT_FILE
{	
	FILENAME datFileName;
	OBJDAT_FILE__ENCODED objEncd;
	BYTE objType;
	OBJDATHEADER objFileHeader;
	TYPESPECHEADER objHeader;
	RCT2__OBJDAT__STRING_TABLE
		stringTable[3];
	OBJDATHEADER groupInfo;
	BYTE numCols,numRows;
	WORD numTiles;
	RCT2__OBJDAT__OPTIONAL_AREA
		optional;
	DWORD numImages;
	DWORD scanLineSize;
	DATGRAPHINFOSTRUCT*imageDirectory;
	DWORD dcodChunkSz;
	//+functions
	BYTE*imageBufr;

	dllPort
	OBJDAT_FILE();

	dllPort 
	Init_SetType(int odType);
	
	dllPort
	DWORD Images_GetBufrSz();
	dllPort 
	WORD GetNumStringTables();
	dllPort 
	bool HasGroupInfo();

	dllPort 
	DecodeObjDatFile(),
		DecodeObj_Optional(BYTE*decdChunk,DWORD&i),
			DecodeObj_Optional_Ride(BYTE*decdChunk,DWORD&i),
			DecodeObj_Optional_SmScenery(BYTE*decdChunk,DWORD&i),
			DecodeObj_Optional_LgScenery(BYTE*decdChunk,DWORD&i),
			DecodeObj_Optional_Group(BYTE*decdChunk,DWORD&i),
		DecodeObj_Images(BYTE*decdChunk,DWORD&i),
	EncodeObjDatFile(),
		EncodeObj_Optional(BYTE*decdChunk,DWORD&i),
			EncodeObj_Optional_Ride(BYTE*decdChunk,DWORD&i),
			EncodeObj_Optional_SmScenery(BYTE*decdChunk,DWORD&i),
			EncodeObj_Optional_LgScenery(BYTE*decdChunk,DWORD&i),
			EncodeObj_Optional_Group(BYTE*decdChunk,DWORD&i),
		EncodeObj_Images(BYTE*decdChunk,DWORD&i),
		EncodeObj_CalcChecksum(BYTE*decdChunk,DWORD&i),
	LoadObjDatFile(),
	SaveObjDatFile(bool freeChunkBuff),
	LoadObjDatFile(char*),
	SaveObjDatFile(char*datName,bool freeChunkBuff);
	
	dllPort
	LScen_GetTileDim(BYTE&cols,BYTE&rows),
	LScen_GetViewImgSize
	(WORD view,WORD&width,WORD&height,short&xofs,short&yofs),
	GetImgSize
	(WORD imgI,WORD&width,WORD&height,short&xofs,short&yofs),
	CopyImage(int imgI,IMG_256&img,short alignSize),
	AddImage
	(	int imgI,
		short xofs,
		short yofs,
		IMG_256&img,short imgEncdType,
		short seeThruColor
	),
	ClearImages();
	dllPort
	DWORD GetImageBufferSize();
	dllPort
	GetNumTiles();

	dllPort
	SortLScenTiles();

	dllPort
	bool IsFlatRide();
	//-functions
} 
	OBJDAT_FILE;


dllPort 
GetTileCenterXYZ
(	WORD view,long&x,long&y,long&z,
	WORD numCols,WORD numRows,
	WORD col,WORD row,WORD baseHeight,
	WORD imgWidth,WORD imgHeight
);

dllPort 
TranslatePos
(	WORD view,WORD&retCol,WORD&retRow,
	WORD numCols,WORD numRows,
	WORD col,WORD row
);

dllPort 
TranslatePos
(	WORD view,ISOMETRIC_TILE_VECTOR&pos,
	WORD numCols,WORD numRows,
	WORD col,WORD row
);


#endif // _OBJDAT_
