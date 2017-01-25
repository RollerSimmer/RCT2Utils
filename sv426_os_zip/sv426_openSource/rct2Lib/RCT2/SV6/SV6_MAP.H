#pragma once
//SV6_MAP_H=symbol

#if!defined(dllPort)
#define dllPort __declspec(dllexport)
#endif

#ifndef SV6_MAP_H
#define SV6_MAP_H

#define SE_BIT 0
#define NE_BIT 1
#define NW_BIT 2
#define SW_BIT 3

#define ELMTTYPE_MASK 0x3c
#define ELMTTYPE_SHIFT 2

#define ELMTSPECS00_MASK	3
#define ELMTSPECS00_SHIFT	0

#define ES00_PATH_QUEUE		1

#ifndef _RCT2_

typedef enum
{
	MET_SURFACE		=0x0,
	MET_PATH		=0X1,
	MET_TRACKELMT	=0X2,
	MET_SHOPSTALL	=0X2,
	MET_SCEN1TILE	=0X3,
	MET_ENTRYEXIT	=0X4,
	MET_FENCEWALL	=0X5,
	MET_SCENMULTILE	=0X6,
	MET_BANNERS		=0X7,
} RCT2_MAPELEMENTTYPE;

#endif //_RCT2_

#define ELMTSPECS06_MASK	0xC0
#define ELMTSPECS06_SHIFT	6

#define ES00_FLAG_ISQUEUE	1

typedef struct 
{
	unsigned char 
		elmtSpec00	:2,
		elmtType	:4,
		elmtSpec06	:2;
}	SV6_MAPBYTE0;

typedef struct 
{
	unsigned char 
		bit00	:1,
		bit01	:1,
		elmtType	:4,
		bit06	:1,
		bit07	:1;
}	
SV6_MAPBYTE0_ALT;

typedef struct
{
	unsigned char 
		NEOccupied				:1,	
		SEOccupied				:1,	
		SWOccupied				:1,	
		NWOccupied				:1,	
		ghosted					:1,
		pathAddsVandalized		:1,
		indestructibleTrack		:1,
		lastElementOnTile		:1;
}	SV6_MAPBYTE1;

typedef struct
{
	unsigned char 
		fill0:5,
		wall_color2_hi:2;
}	SV6_MAPBYTE1_ALT;

#define EE_RIDEENTRY	0
#define EE_RIDEEXIT		1
#define EE_PARKGATE		2

#define EE_RIDEEXIT_CLEARANCE	5
#define EE_RIDEENTRY_CLEARANCE	7
#define EE_PARKGATE_CLEARANCE	12


#define TRACK_STATIONPLATFORM_END		0X01
#define TRACK_STATIONPLATFORM_BEGIN		0X02
#define TRACK_STATIONPLATFORM_MIDDLE	0X03

typedef struct
{
	BYTE 
		slope:5,
		edge:3;
}LAND_SLOPE_BYTE;

typedef union 
{
	BYTE
		elmtID,
		bannerindex;
	LAND_SLOPE_BYTE
		landslope;
} SV6_MAPBYTE4;

typedef union 
{
struct
{
BYTE
	slope:2,
	isSloped:1,
	path5_bit3:1,
	pathId:4;
}
path;

unsigned char 
	whole;
} SV6_MAPBYTE4_ALT;

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

typedef struct
{
	BYTE 
		waterHeight:5,
		ground:3;
}TERRAIN_WATER_BYTE;

typedef union
{
	BYTE
		index,
		scenAge,
		pathAdditions,
		parkEntryIndex,
		bannerPosition;
	TERRAIN_WATER_BYTE
		terrainWater;
}SV6_MAPBYTE5;

typedef union
{
struct
{
	unsigned char 
		additions	:4,
		path5_bits4_to_6	:3,
		ghosted	:1;
}
path;
struct
{
	unsigned char 
		color3:5,
		unk_wall_5_5:3;
}
wall;
unsigned char 
	whole;
}	
SV6_MAPBYTE5_ALT;

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
}SV6_MAPBYTE6;

typedef union
{
struct
{
	unsigned char 
		edge0:1,
		edge1:1,
		edge2:1,
		edge3:1,
		crnr0:1,
		crnr1:1,
		crnr2:1,
		crnr3:1;
}
path;
struct
{
	unsigned char 
		color1:5,
		color2_lo:3;
}
wall;
unsigned char 
	whole;
}	
SV6_MAPBYTE6_ALT;

#define PAS_ALLTRASHEMPTY 0xff

typedef union 
{
	BYTE
		ownership,
		rideindex,
		pathAdditionStatus,
		color2,
		item,
		wallAnimFrame;

} SV6_MAPBYTE7;

typedef union
{
struct
{
	unsigned char 
		addStatus0:2,
		addStatus1:2,
		addStatus2:2,
		addStatus3:2;
}
path;
unsigned char 
	whole;
}	
SV6_MAPBYTE7_ALT;

#define RCT2_HEIGHTUNIT 2
#define RCT2_MAXHEIGHT 62 
#define RCT2_MINHEIGHT 2 


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
	SV6_MAPBYTE0
		byte0;
	SV6_MAPBYTE1
		byte1;
	BYTE
		baseheight,
		clearheight;
	SV6_MAPBYTE4 
		byte4;
	SV6_MAPBYTE5
		byte5;
	SV6_MAPBYTE6
		byte6;
	SV6_MAPBYTE7
		byte7;

	dllPort
		GetLandType(short&ground,short&edge),
		SetLandType(short ground,short edge);

} SV6_PARKMAPDATA,*LP_SV6_PARKMAPDATA;


typedef struct 
{
	SV6_MAPBYTE0_ALT
		byte0;
	SV6_MAPBYTE1_ALT
		byte1;
	BYTE
		baseheight,
		clearheight;
	SV6_MAPBYTE4_ALT 
		byte4;
	SV6_MAPBYTE5_ALT
		byte5;
	SV6_MAPBYTE6_ALT
		byte6;
	SV6_MAPBYTE7_ALT
		byte7;
	SetWallColors(short c1,short c2,short c3)
	{
		byte5.wall.color3=c3;
		byte6.wall.color1=c1;
		byte6.wall.color2_lo=c2&0x7;
		byte1.wall_color2_hi=(c2&0x18)>>3;
	}
} SV6_PARKMAPDATA_ALT;



typedef BYTE SV6_PARKMAPDATA_2[8];

typedef SV6_PARKMAPDATA* LPSV6_PARKMAPDATA;

typedef LPSV6_PARKMAPDATA SV6_PARKMAPPTRARRAY[256][256];

#define SV6_MAPDATASTRUCTURES_MAX 196608
typedef SV6_PARKMAPDATA SV6_PARKMAPDATABLOCK[SV6_MAPDATASTRUCTURES_MAX];

SV6_PARKMAPDATA SV6_BORDERTILE;	//"\x00\x80\x02\x02\x00\x00\x01\x00"

#define BORDERTILESTRING "\x00\x80\x02\x02\x00\x00\x01\x00"

#ifndef _RCT2_

typedef enum
{	RCT2_MDF_READ,
	RCT2_MDF_WRITE,
	RCT2_MDF_INIT,
	RCT2_MDF_DONE,
	RCT2_MDF_OPTIMIZE
}	RCT2_MAPDATAFUNC;

#endif //_RCT2_

#define SV6_MAP_MAXTILES 256

typedef LP_SV6_PARKMAPDATA SV6_PARKMAPPTRARRAY[256][256];

#endif //SV6_MAP_H
