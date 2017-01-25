#ifndef _MAPFUNCS_
#define _MAPFUNCS_

#include <windows.h>

POINT MakePoint(LONG x,LONG y);

BOOL PointInRec(CONST RECT*,POINT);

typedef enum
{	OWN_INVERT,OWN_INVERTIGNORE,OWN_UNOWNTORIGHTS,
		OWN_DEOWNBORDER,OWN_OWNALLLAND,OWN_RESTOREBORDERFENCE,
		OWN_REMOVEBORDERFENCE,
	LAND_MOWGRASS,LAND_MOWGRASSPLAIN,LAND_CAPATMAXHEIGHT, LAND_FIXINVISIBLEBORDER,LAND_DELETEEXTRAS,
	SCEN_WATERGARDENS,
	PATH_EMPTYTRASH,PATH_FIXVANDALISM,PATH_VANDALIZE,
	CLEARANCE_ZEROALL_ABSOLUTELY,CLEARANCE_ZEROALL_RELATIVELY,CLEARANCE_RESTOREALL,
	RIDE_GETLOWHIGH,RIDE_RAISELOWER,RIDE_BURY,RIDE_EXCAVATE,RIDE_ZEROCLEARANCE,
		RIDE__TOGGLE_VISIBILITY,RIDE__TOGGLE_CHAIN,
	SORT_BYBASEHEIGHT,
	ALL_RAISELOWER,ALL_REMOVE,ALL_GETCOUNT,ALL__CHANGE_LAND_TYPE
} MAPFUNCID;
 
typedef enum
{	MF_CLEARANCE,MF_OWN,MF_LAND,MF_SCEN,
	MF_PATH,MF_RIDE,MF_SORT,MF_ALL
} MAPFUNCCLASS;

int InvertOwnership();
int InvertOwnershipIgnore();
int ChangeUnowntoRights();

int MowGrass();
int MowGrassPlain();
int WaterGardens();
int EmptyTrash();
int VandalizePark();
int FixVandalism();
int DeownBorderLand();
int RestoreBorderFence();
int RemoveBorderFence();
int ZeroAllClearancesAbsolutely();
int ZeroAllClearancesRelatively();
int RestoreAllClearances();
int SortMapElmentsInternally();
int EliminateDuplicateSurfaceData();

int CapLandAtMaxHeight();
int FixInvisibleBorder();

int GetRideLowHighHeights(int index,int colorscheme,short *ridelow,short *ridehigh);
int RaiseLowerRide(short index,short heightoffset,short colorscheme);
int BuryRide(short index,short colorscheme);
int ExcavateRide(short index,short colorscheme);
int MakeRideZeroClearance(short index,short colorscheme);

int ToggleRideVisibility(short index,short colorscheme);
int ToggleRideLiftChain(short index,short colorscheme);

DWORD GetUsedMapDataStructCount();

int OptimizeMapDataSpace();

int SetMapEntryPoints
(	int x1,int y1,int z1,
	int x2,int y2,int z2,
	short dir1,short dir2
);

typedef enum
{
	SETF_DIRT		=1<<0,
	SETF_BROWNWOOD	=1<<1,
	SETF_BLACKWOOD	=1<<2,
	SETF_ICE		=1<<3
}	SURFACEEDGETYPEFFLAG;

typedef enum
{
	SLTF_GRASS			=1<<0X0,
	SLTF_SAND			=1<<0X1,		
	SLTF_BROWNDIRT		=1<<0X2,
	SLTF_BLACKROCK		=1<<0X3,
	SLTF_REDROCK		=1<<0X4,
	SLTF_CHECKER		=1<<0X5,
	SLTF_GRASSDIRT		=1<<0X6,
	SLTF_SNOW			=1<<0X7,
	SLTF_REDGRID		=1<<0X8,
	SLTF_YELLOWGRID		=1<<0X9,
	SLTF_PURPLEGRID		=1<<0XA,
	SLTF_GREENGRID		=1<<0XB,
	SLTF_REDCLAY		=1<<0XC,
	SLTF_TANDIRT		=1<<0XD
}	SURFACELANDTYPEFLAG;

/*
typedef enum
{
	RL_OTCHK_RIDETRACK=0,
	RL_OTCHK_SMALLSCENERY,
	RL_OTCHK_LARGESCENERY,
	RL_OTCHK_WALLS,
	RL_OTCHK_PATHBANNER,
	RL_OTCHK_PATHENTRANCE,
	RL_OTCHK_WATER,
	RL_OTCHK_LAND
} RL_OBJECTTYPECHECKBOX;
*/

typedef enum
{
	OTF_RIDETRACK		=1<<0X0,
	OTF_SMALLSCENERY	=1<<0X1,		
	OTF_LARGESCENERY	=1<<0X2,
	OTF_WALLS			=1<<0X3,
	OTF_PATHBANNER		=1<<0X4,
	OTF_PARKENTRANCE	=1<<0X5,
	OTF_WATER			=1<<0X6,
	OTF_LAND			=1<<0X7,
	OTF_PATH			=1<<0X8,
	OTF_NULL			=1<<0X9,

}	OBJECTTYPEFLAG;

int RaiseLowerObjects
(	WORD objFlags,WORD groundFlags,WORD edgeFlags,WORD lowHeight,WORD highHeight,short offset
);
int RemoveObjects
(	WORD objFlags,WORD groundFlags,WORD edgeFlags,WORD lowHeight,WORD highHeight
);

int ChangeLandType
(	WORD newLandType,WORD groundFlags,WORD edgeFlags
);


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

#endif