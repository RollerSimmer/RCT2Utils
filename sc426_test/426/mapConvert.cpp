
#include "mapConvert.H"
#include"426_map_surface.h"
#include"426_objdat.h"
#include"trackElementConvert.h"
#include<codeshortcuts.h>
#include"colorConvert.h"
#include"426_compileflags.h"


bool ConvertMapElement
(	SV6_PARKMAPDATA&,SV4_PARKMAPDATA&
	,short&incI
	,short&incJ
)
;
IncI4(int&i,short incI);
IncI6(int&j,short incJ);

int watchI;
int watchJ;
int watchTileCount;


ConvertMap
(
SV6_PARKMAPDATABLOCK&sv6Map
,SV4_PARKMAPDATABLOCK&sv4Map
,int parkSz
)
{
	BYTE 
	blankTile[8]=
	{0,0x80,2,2,0,0,1,0};
	//convert map from sv4 to sv6

	bool eot=false;

	SV6_PARKMAPDATABLOCK&m6=sv6Map;
	SV4_PARKMAPDATABLOCK&m4=sv4Map;

	enum
	{
		i_sv4=0,
		i_sv6
	};

	DWORD numTiles[2]=
	{
		SV4_MAP_MAXTILES*SV4_MAP_MAXTILES,
		SV6_MAP_MAXTILES*SV6_MAP_MAXTILES
	};

	int i4,&i=i4;
	int i6,&j=i6;
	long tileCount,&tc=tileCount;
	short incI,incJ;
	int x,y;

	i=0;j=0;tc=0;
	
	do
	{
		incI=0;
		incJ=0;

		x=tc%256;
		y=tc/256;
		if
		(
		(x==0)||(y==0)
		||
		(x>=(parkSz-1))||(y>=(parkSz-1))
		)
		{
			memcpy(&m6[j],blankTile,sz(m6[j]));
			incJ=1;
			if((x<128)&&(x<128))
			{
			incI=1;
			while(!(m4[i].tileflags&0x80))
			{	
				++i;	
			}
			}
			eot=true;
		}
		else
		{
			watchI=i;
			watchJ=j;
			watchTileCount=tc;

			eot
			=
			ConvertMapElement(m6[j],m4[i],incI,incJ);
		}
		if(eot)
		{
			++tc;
			eot=false;
		}
		
		IncI4(i,incI);
		IncI6(j,incJ);
	}
	while(tc<numTiles[i_sv6]);
}

IncI4(int&i,short incI)
{
	i+=incI;
}

IncI6(int&j,short incJ)
{
	j+=incJ;
}


short ConvertME_Surface(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;
short ConvertME_EntryExit(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;
short ConvertME_Path(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;
short ConvertME_TrackElmt(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;
short ConvertME_SmScenery(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;
short ConvertME_LgScenery(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;
short ConvertME_Wall(SV6_PARKMAPDATA*e6p,SV4_PARKMAPDATA&e4)
;
short ConvertME_Banner(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
;

bool ConvertMapElement
(	SV6_PARKMAPDATA&elmt6,SV4_PARKMAPDATA&elmt4
	,short&incI
	,short&incJ
)
{
	bool eot;
	SV6_PARKMAPDATA e4_asSv6=*(SV6_PARKMAPDATA*)&elmt4;
	SV6_PARKMAPDATA&e6=elmt6;
	SV4_PARKMAPDATA e4=elmt4;
	SV6_PARKMAPDATA*e6p=&elmt6;

	SV6_PARKMAPDATA*e6_back;

	eot=e4_asSv6.byte1.lastElementOnTile;

	incI=1;
	incJ=0;

	e6=e4_asSv6;//default 
	e6_back=&elmt6;--e6_back;
	
	e6.byte0=e4_asSv6.byte0;
	e6.byte1=e4_asSv6.byte1;
	e6.byte1.ghosted=0;
	e6.baseheight=e4.baseheight/2;
	e6.clearheight=e4.clearheight/2;

	switch(e4_asSv6.byte0.elmtType)
	{
	case MET_SURFACE:
		incJ=ConvertME_Surface(e6,e4);
		break;
	case MET_PATH:
		incJ=ConvertME_Path(e6,e4);
		break;
	case MET_TRACKELMT:
		incJ=ConvertME_TrackElmt(e6,e4);
		break;
	//case MET_SHOPSTALL:
	//	break;
	case MET_SCEN1TILE:
		incJ=ConvertME_SmScenery(e6,e4);
		break;
	case MET_ENTRYEXIT:
		incJ=ConvertME_EntryExit(e6,e4);
		break;
	case MET_FENCEWALL:
		incJ=ConvertME_Wall(e6p,e4);
		break;
	case MET_SCENMULTILE:
		incJ=ConvertME_LgScenery(e6,e4);
		break;
	case MET_BANNERS:
		#if(_426__CONVERT_BANNERS)
		incJ=ConvertME_Banner(e6,e4);
		#endif
		break;		
	}

	if(eot)
	{	e6p[incJ-1].byte1.lastElementOnTile=1;
	}

	#if 1
	if(incJ==1)
	{
		elmt6=e6;
	}
	#endif

	return(eot);
}

short ConvertME_Surface(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	SV6_PARKMAPDATA&e4_asSv6=*(SV6_PARKMAPDATA*)&e4;
	short e,g,ee,gg;

	e4_asSv6.GetLandType(g,e);
	ee=cliffConvert426[e];
	gg=groundConvert426[g];
	e6.SetLandType(gg,ee);

	e6.byte4.landslope.slope=e4_asSv6.byte4.landslope.slope;
	e6.byte5.terrainWater.waterHeight=e4_asSv6.byte5.terrainWater.waterHeight;

	e6.byte6.grass=e4.byte6.grass;
	e6.byte7.ownership=e4.byte7.ownership;
	
	return(1);
	
	//e6.byte5.terrainWater
}

short ConvertME_EntryExit(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	SV6_PARKMAPDATA&e4_asSv6=*(SV6_PARKMAPDATA*)&e4;

	#if(_426__SKIP_RIDE_STATIONS)
	if(e4.byte4.elmtID<2)
		return(0);
	#endif

	return(1);

	//e4_asSv6.

}

typedef 
union
{
struct
{
BYTE
	l:2,
	h:5,
	f:1;
};
BYTE
	v;
}_PATH_ID;


short ConvertME_Path(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	_PATH_ID pid;
	SV6_PARKMAPDATA*e46=(SV6_PARKMAPDATA*)&e4;
	SV6_PARKMAPDATA_ALT*e4a=(SV6_PARKMAPDATA_ALT*)&e4;
	SV6_PARKMAPDATA_ALT*e6a=(SV6_PARKMAPDATA_ALT*)&e6;

	pid.v=0;
	pid.l=e46->byte0.elmtSpec00;
	pid.h=e4a->byte4.path.pathId;
	

	if(pid.v>=PATH_CONVERT_TABLE__NUM_ENTRIES)
		return(false);
	if(pid.h==1)
		e6a->byte4.path.pathId
		=pathConvertTable[pid.v].mapIndex;



	e6a->byte4.path.pathId
	=pathConvertTable[pid.v].mapIndex;

	e6a->byte0.bit06=0;
	e6a->byte0.bit07=0;
	e6.byte0.elmtSpec00=0;
	e6.byte1.ghosted=0;
	e6.byte1.indestructibleTrack=0;
	e6.byte1.pathAddsVandalized=0;

	switch(pathConvertTable[pid.v].pathType)
	{
	case QUEUE:
	{
		e6a->byte0.bit00=1;
		break;
	}
	case PATH:
	{
		e6a->byte0.bit00=0;
		break;
	}
	case EMPTYENTRY:
	{
		return(false);
	}
	}

	e6a->byte4.path.isSloped=e4a->byte4.path.isSloped;
	e6a->byte4.path.path5_bit3=0;
	e6a->byte4.path.slope=e6a->byte4.path.slope;
	e6a->byte5=e4a->byte5;
	e6a->byte6=e4a->byte6;
	e6a->byte7=e4a->byte7;	

	return(1);

}


bool _cte_IsStation(short a){return((a>=1)&&(a<=3));}

short ConvertME_TrackElmt(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	_PATH_ID pid;
	SV6_PARKMAPDATA&e46=*(SV6_PARKMAPDATA*)&e4;
	SV6_PARKMAPDATA_ALT&e4a=*(SV6_PARKMAPDATA_ALT*)&e4;
	SV6_PARKMAPDATA_ALT&e6a=*(SV6_PARKMAPDATA_ALT*)&e6;

	//e6a=e4a;
	e6.byte4.elmtID
	=
	RCT1to2trackElementConversionTable[e4.byte4.elmtID]
	;

	#if(_426__SKIP_RIDE_STATIONS)
	if(_cte_IsStation(e6.byte4.elmtID))
	{
		return(0);
	}
	#endif

	if(e6.byte4.elmtID==RCTX_BYTE_EMPTY)
	{
		return(0);
	}

	return(1);

}

short ConvertME_SmScenery(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	short ei;
	RCT_COLOR c;

	ei=(e6.byte4.elmtID=e4.byte4.elmtID);
	e6.byte5.scenAge=0;

	c=colorMaps_sScen[ei][0];
	Rct1to2ColorMap(e6.byte6.color,c,e4.byte6.color);
	
	c=colorMaps_sScen[ei][1];
	Rct1to2ColorMap(e6.byte7.color2,c,e4.byte6.color);
	
	return(1);
}

short ConvertME_LgScenery(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	short ei;
	RCT_COLOR c;

	ei=(e6.byte4.elmtID=e4.byte4.elmtID);
	e6.byte5.index=e4.byte5.index;

	c=colorMaps_lScen[ei][0];
	Rct1to2ColorMap(e6.byte6.color,c,e4.byte6.color);
	
	c=colorMaps_lScen[ei][1];
	Rct1to2ColorMap(e6.byte7.color2,c,e4.byte7.color2);

	return(1);
}

short ConvertME_Wall(SV6_PARKMAPDATA*e6p,SV4_PARKMAPDATA&e4)
{
	short incJ;

	short i,iOpp;
	BYTE remapColor,rc,color1,color2;	
	short w[4];//walls
	short*wp[4];//wallPointers
	short lc[4];//landCorners
	short sci,eci;//start and end corner index
	bool diamondSlope;
	short zeroCorner;
	bool raiseHeight=false;
	bool eot;
	short lastI;
	
	SV6_PARKMAPDATA*e46=(SV6_PARKMAPDATA*)&e4;
	SV6_PARKMAPDATA*e6=e6p;
	SV6_PARKMAPDATA_ALT*e46a=(SV6_PARKMAPDATA_ALT*)&e4;
	SV6_PARKMAPDATA_ALT*e6a=(SV6_PARKMAPDATA_ALT*)e6p;
	SV4_PARKMAPDATA_ALT*e4a=(SV4_PARKMAPDATA_ALT*)&e4;

	#define slc(a)\
		lc[a]=e4a->byte4.wall.corner##a
	slc(0);
	slc(1);
	slc(2);
	slc(3);
	#undef slc

	diamondSlope=e4a->byte4.wall.diamondSlope;
	if(diamondSlope)
	{
		zeroCorner=4;
		for_i0(i,4)
		{
		if(!lc[i])
		{
			zeroCorner=i;
			i=4;
		}		
		}
		if(zeroCorner!=4)
		{
		for_i0(i,4)
		{lc[i]=(i==zeroCorner)?0:1;}
		for_i0(i,4)
		{
		iOpp=(i+2)%4;
		if(i==zeroCorner)++lc[iOpp];
		}
		}
	}

	for_i0(i,4){wp[i]=&w[i];}
		
	e4a->GetWalls(wp);


	incJ=0;

	rc
	=
	e4a->byte4.wall.colorLo
	|
	(e46->byte0.elmtSpec06<<3)
	;
	remapColor=RCT1to2colorConvertTable[rc];


	short t;
	for_i0(i,4)
	{
	t=(w[i]&0xf);
	if((t>=0)&&(t<0xd))
	{
		lastI=i;
		//e6[incJ]=e46[0];//default 
		MemClr(e6[incJ]);

		e6[incJ].byte0=e46[0].byte0;
		e6[incJ].byte1=e46[0].byte1;
		e6[incJ].byte1.ghosted=0;
		e6[incJ].byte1.lastElementOnTile=0;
		e6[incJ].baseheight=e4.baseheight/2;
		e6[incJ].clearheight=e4.clearheight/2;


		e6[incJ].byte4.elmtID=w[i];
		
		Rct1to2ColorMap
		(
		color1,colorMaps_walls[w[i]][0]
		,remapColor
		)
		;

		Rct1to2ColorMap
		(
		color2,colorMaps_walls[w[i]][1]
		,remapColor
		)
		;
		#if 1
		if(color1==0x18)
			color1=0x18;
		#endif

		//rotation
		e6[incJ].byte0.elmtSpec00=i;

		//slope
		sci=(i-2)%4;
		eci=(sci+1)%4;
		if(sci<0)sci+=4;
		if(eci<0)eci+=4;

		raiseHeight=false;	
		if((lc[sci]>0)&&(lc[eci]>0))
		{	
			raiseHeight=true;	
			--lc[sci];--lc[eci];	
		}
		if(raiseHeight)
		{
			e6[incJ].baseheight+=2;
			e6[incJ].clearheight+=2;
		}

		e6a[incJ].byte0.bit07=lc[sci];
		e6a[incJ].byte0.bit06=lc[eci];	

		e6a[incJ].SetWallColors(color1,color2,0);
			
		++incJ;
	}	
	}

	eot=e46->byte1.lastElementOnTile;
	if((lastI!=-1)&&(eot))
	{
		e46[lastI].byte1.lastElementOnTile=eot;		
	}

	return(incJ);
}

short ConvertME_Banner(SV6_PARKMAPDATA&e6,SV4_PARKMAPDATA&e4)
{
	SV6_PARKMAPDATA&e46=*(SV6_PARKMAPDATA*)&e4;

	#define _sb(a) (e6.byte##a=e46.byte##a) 
	//set byte
	_sb(4);
	_sb(5);
	_sb(6);
	_sb(7);
	#undef _sb
	
	return(1);
}
