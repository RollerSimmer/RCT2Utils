#ifndef SV4_MAP_H
#define SV4_MAP_H

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
} SV4_MAPBYTE4;

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
}SV4_MAPBYTE5;


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
}SV4_MAPBYTE6;

#define PAS_ALLTRASHEMPTY 0xff


typedef union 
{
	BYTE
		ownership,
		rideindex,
		pathAdditionStatus,
		item;
} SV4_MAPBYTE7;

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
	SV4_MAPBYTE4 
		byte4;
	SV4_MAPBYTE5
		byte5;
	SV4_MAPBYTE6
		byte6;
	SV4_MAPBYTE7
		byte7;
} SV4_PARKMAPDATA;

typedef SV4_PARKMAPDATA* LPSV4_PARKMAPDATA;

#define SV4_MAP_MAXTILES	128
typedef LPSV4_PARKMAPDATA SV4_PARKMAPPTRARRAY[SV4_MAP_MAXTILES][SV4_MAP_MAXTILES];

typedef SV4_PARKMAPDATA SV4_PARKMAPDATABLOCK[49152];

SV4_PARKMAPDATA SV4_BORDERTILE;	//"\x00\x80\x02\x02\x00\x00\x01\x00"

//#define BORDERTILESTRING "\x00\x80\x02\x02\x00\x00\x01\x00"

typedef enum
{	RCT_MDF_READ,
	RCT_MDF_WRITE,
	RCT_MDF_INIT,
	RCT_MDF_DONE,
}	RCT_MAPDATAFUNC;

short RctMapDataFunc
(	RCT_MAPDATAFUNC mapdatafunc,short x,short y,LPSV4_PARKMAPDATA mapdata,int count	
);

#endif //SV4_MAP_H
