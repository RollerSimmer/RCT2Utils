    
#include <windows.h>
#include <math.h>
#include <memory.h>
#include "..\process\process.h"
#include "..\rct2.h"
#include "mapfuncs.h"
#include "..\8cars.h"
#include <stdlib2.h>
#include "..\clearance\clearance.h"

#undef __KEEPENTRYUNOWNED__

typedef struct{int index,colorscheme;short *low,*high;}RIDELOWHIGH ;
typedef struct{short index,heightoffset,colorscheme,*stationRaised;}RIDE_RAISELOWERSTRUCT;
typedef struct{short index,colorscheme;}RIDE_BURYSTRUCT;
#define RIDE_EXCAVATESTRUCT RIDE_BURYSTRUCT
#define RIDE_ZEROCLEARANCESTRUCT RIDE_BURYSTRUCT
#define RIDE__TOGGLE_VISIBILITY_STRUCT RIDE_BURYSTRUCT
#define RIDE__TOGGLE_CHAIN_STRUCT RIDE_BURYSTRUCT

SetLandGroundType(PARKMAPDATA*mapData,WORD groundType);

typedef struct
{	WORD objFlags,groundFlags,edgeFlags,lowHeight,highHeight;
	short offset;
} ALL_RAISELOWERSTRUCT;
typedef struct
{	WORD objFlags,groundFlags,edgeFlags,lowHeight,highHeight;
} ALL_REMOVESTRUCT;

typedef struct
{	WORD newLandType,groundFlags,edgeFlags;
} ALL__CHAMGE_LAND_STRUCT;

typedef struct 
{	DWORD count; 
} ALL_GETCOUNTSTRUCT;

POINT MakePoint(LONG x,LONG y)
{
	POINT p={x,y};
	return p;
}

BOOL PointInRect(CONST RECT *rect,POINT point)
{
	return 
		(point.x>=rect->left)
		&&(point.x<=rect->right)
		&&(point.y>=rect->top)
		&&(point.y<=rect->bottom);
}

#define NumInRange(a,b,c) ((a>=b)&&(a<=c))

int GetFirstIndexOfElementType
(	RCT2_MAPELEMENTTYPE targetElmtType, PARKMAPDATA *MapData
)
{
	int i=0,elmttype,moretiles=TRUE;

	do
	{	elmttype=MapData[i].byte0.elmtType;
		if(elmttype==targetElmtType)
			return i;
		moretiles=!MapData[i].byte1.lastElementOnTile;
		i++;
	} while(moretiles);

	return 0;
}


int GetLandI(PARKMAPDATA *MapData)
{	
	return GetFirstIndexOfElementType(MET_SURFACE,MapData);
}

int GetCountOfElementType
(	RCT2_MAPELEMENTTYPE targetElmtType, PARKMAPDATA *MapData
)
{
	int i=0,elmttype,moretiles=TRUE;
	int c=0;

	do
	{	elmttype=MapData[i].byte0.elmtType;
		if(elmttype==targetElmtType)
			++c;
		moretiles=!MapData[i].byte1.lastElementOnTile;
		i++;
	} while(moretiles);

	return c;
}

int GetLandCount(PARKMAPDATA *MapData)
{
	return GetCountOfElementType(MET_SURFACE,MapData);
}



WORD GetLandEdgeType(PARKMAPDATA *MapData,int landI)
{	
	WORD edgeType;
	return edgeType=
	(
		(BYTE)MapData[landI].byte0.elmtSpec06
		<<LANDTYPEEXTENDER_BITPLACE
	)
	|(
		(MapData[landI].byte4.landslope&EDGEGROUNDTYPE_BITMASK)
		>>EDGEGROUNDTYPE_BITPLACE
	);
}

WORD GetLandGroundType(PARKMAPDATA *MapData,int landI)
{	
	WORD groundType;
	return groundType=
	(
		(BYTE)MapData[landI].byte0.elmtSpec00
		<<LANDTYPEEXTENDER_BITPLACE
	)
	|(
		(MapData[landI].byte5.terrainWater&EDGEGROUNDTYPE_BITMASK)
		>>EDGEGROUNDTYPE_BITPLACE
	);
}



SetLandGroundType(PARKMAPDATA*mapData,WORD groundType)
{	
	union
	{
		struct{short lo:3,hi:1;};
		short whole;
	}
	gt;

	gt.whole=groundType;

	mapData[0].byte0.elmtSpec00
	&=
	(BYTE)(~GROUNDTYPE_EXTENDERBITMASK);
	
	mapData[0].byte0.elmtSpec00
	|=
	(BYTE)((gt.hi&1)<<GROUNDTYPE_EXTENDERBITPLACE);

	mapData[0].byte5.terrainWater
	&=
	(BYTE)(~EDGEGROUNDTYPE_BITMASK);

	mapData[0].byte5.terrainWater
	|=
	(BYTE)((gt.lo&7)<<EDGEGROUNDTYPE_BITPLACE);
}

int GetOwnership(BYTE *ownership,BYTE *border,LPPARKMAPDATA MapData)
{	
	*ownership=
		((*MapData).byte7.ownership
		&OWNERSHIP_MASK)>>OWNERSHIP_SHIFT;
	*border=
		((*MapData).byte7.ownership
		&BORDERFENCE_MASK)>>BORDERFENCE_SHIFT;
}

BYTE GetOwnershipAt(short x,short y)
{
	PARKMAPDATA	MapData[512];
	int i,moretiles;
	BYTE ownership,border;

	Rct2MapDataFunc(MDF_READ,x,y,&MapData,512);

	ownership=OWN_UNOWNED;
	
	
	for (i=0,moretiles=TRUE;(i<512)&&moretiles;i++)	
	{
		int elmttype;

		elmttype=MapData[i].byte0.elmtType;
		if(elmttype==MET_SURFACE)
		{
			GetOwnership(&ownership,&border,&MapData[i]);
			moretiles=FALSE;
		}
		else 	
			moretiles=!MapData[i].byte1.lastElementOnTile;
	}
	
	return ownership;
}

BYTE GetBorderFenceBits(short x,short y)
{
	BYTE border=0;

	int cur,north,south,east,west;

	cur=GetOwnershipAt(x,y)&OWN_LANDOWNED;
	north=GetOwnershipAt(x,y+1)&OWN_LANDOWNED;
	south=GetOwnershipAt(x,y-1)&OWN_LANDOWNED;
	east=GetOwnershipAt(x+1,y)&OWN_LANDOWNED;
	west=GetOwnershipAt(x-1,y)&OWN_LANDOWNED;

	if(cur) return 0;	
	if(north)
		border|=BORDERFENCE_NORTH;
	if(south)
		border|=BORDERFENCE_SOUTH;
	if(east)
		border|=BORDERFENCE_EAST;
	if(west)
		border|=BORDERFENCE_WEST;

	return border;
}


int SetOwnership(LPPARKMAPDATA MapData,int ownership,int border)
{	
	(*MapData).byte7.ownership=0;
	(*MapData).byte7.ownership=
		((ownership<<OWNERSHIP_SHIFT)&OWNERSHIP_MASK)
		|((border<<BORDERFENCE_SHIFT)&BORDERFENCE_MASK);

	return (*MapData).byte7.ownership;
}

//memswap(&MapData[LandI],&MapData[i],sizeof(PARKMAPDATA));
int SwapMapDataElements
(	PARKMAPDATA *MapData,
	int i1,int i2
)
{
	int t2LastTile;

	if(i1>i2)memswap(&i2,&i1,sizeof(i1));

	t2LastTile=MapData[i2].byte1.lastElementOnTile;

	if(t2LastTile)
	{
		MapData[i1].byte1.lastElementOnTile=BIT_SET;
		MapData[i2].byte1.lastElementOnTile=BIT_CLEAR;
	}
	memswap(&(MapData[i1]),&(MapData[i2]),sizeof(PARKMAPDATA));
}

WORD GetMapTileElementCount(PARKMAPDATA	*MapData)
{
	WORD i=0;

	while (!MapData[i++].byte1.lastElementOnTile);

	return i;
}

int SortMapTileElements(MAPFUNCID func, PARKMAPDATA	*MapData)
{
	WORD count=GetMapTileElementCount(MapData),
		i,j,
		landI,landCount,landEdgeType,landGroundType;
	BYTE 
		landBaseHeight;


	if (count>1)
	{
		for(i=0;i<(count-1);i++)
		{	
			for(j=i+1;j<count;j++)
			{
				switch(func)
				{
				case SORT_BYBASEHEIGHT:
					if(	MapData[j].baseheight
						<MapData[i].baseheight
					)
						SwapMapDataElements(MapData,i,j);
					break;				
				} //switch(func)
			}
		}

		landI=GetLandI(MapData);
		landCount=GetLandCount(MapData);
		
		landEdgeType=GetLandEdgeType(MapData,landI);
		landGroundType=GetLandGroundType(MapData,landI);

		if(landI!=RCT2_WORD_EMPTY)
		{
			landBaseHeight=MapData[landI].baseheight;
			for(i=0;i<count;i++)
			{
				if(MapData[landI].baseheight==MapData[i].baseheight)
					if(landI>i)
					{
						SwapMapDataElements(MapData,i,landI);
						landI=i;
					}
			}
		}

	}


}

int RemoveMapElement(PARKMAPDATA *MapData,short *index,WORD *(*LandI))
{	
	int moretiles,i=(*index);
	do
	{	moretiles=!(MapData[i].byte1.lastElementOnTile);
		if(moretiles)
		{	memcpy(&MapData[i],&MapData[i+1],sizeof(PARKMAPDATA));
			++i;
		}
		else 
		{	if((i>0)&&(i==(*index)))
				MapData[i-1].byte1.lastElementOnTile=BIT_SET;
			MapData[i].baseheight=RCT2_BYTE_EMPTY;			
		}
	}
	while(moretiles);

	if((*index)<(*LandI))
		--(*LandI);
	if((*index)>0)
		--(*index);

	return TRUE;
}

BYTE a,b;

int MapFunc(MAPFUNCCLASS fclass,MAPFUNCID func,void *params)
{
	#define ridelowhigh (*(RIDELOWHIGH *)(params))
	#define raiselower (*(RIDE_RAISELOWERSTRUCT*)(params))
	#define bury (*(RIDE_BURYSTRUCT*)(params))
	#define excavate bury
	#define zeroclearance bury
	#define toggleVisibility bury
	#define toggleChain bury

	#define allChangeLand (*(ALL__CHAMGE_LAND_STRUCT*)(params))
	#define allRaiseLower (*(ALL_RAISELOWERSTRUCT*)(params))
	#define allRemove (*(ALL_REMOVESTRUCT*)(params))
	#define allGetCount (*(ALL_GETCOUNTSTRUCT*)(params))

	POINT xy;
	RECT ValidXYRange={1,1,254,254},XYRange;
	int x,y,moretiles;
	
	POINT low,high;
	short i,svI;
	WORD LandI,landCount,landEdgeType,landGroundType;
	WORD allObjMatch,allLandMatch;

	int xyInRange;
	int landpassed;

	BYTE ownership,svownership,border;
	short wasUnowned;

	BYTE elmttype;
	
	WORD parksize;

	//LPPARKMAPDATA parkMapPtr,svMapPtr;
	PARKMAPPTRARRAY MapPtrs;
		
	PARKMAPDATA	MapData[512], OldMapData, LandData;
	HCURSOR hcursor;
	

	if(!WinRead(mainWindow,RCT2_TITLE,&parksize,RCT2_ADDR_MAPSIZE,2)) 
		return FALSE;
	
	if(!Rct2MapDataFunc(MDF_INIT,0,0,NULL,0)) 
	{	Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);
		return FALSE;
	}
	
	ValidXYRange.right=ValidXYRange.bottom=parksize-2;
			
	hcursor=GetCursor();
	SetCursor(LoadCursor(NULL,IDC_WAIT));

	switch(func)
	{
	case LAND_FIXINVISIBLEBORDER:
		SetRect(&XYRange,0,0,parksize-1,parksize-1);
		break;
	default:
		SetRect(&XYRange,1,1,parksize-2,parksize-2);
		break;
	}

	switch(fclass)
	{
	case MF_CLEARANCE:
		GetElementClearance(TRUE,NULL);
		break;
	case MF_SORT:
	case MF_OWN:											
	case MF_LAND: 
	case MF_SCEN: 
	case MF_PATH: 
	case MF_RIDE:
	case MF_ALL:
		break;
	default:
		break;
	}



	for(y=XYRange.top;y<=XYRange.bottom;y++)
	{	
		for(x=XYRange.left;x<=XYRange.right;x++)
		{

			wasUnowned=FALSE;
//// 
			svI=i;
			landpassed=FALSE;
			ownership=svownership=OWN_UNOWNED;
						
			moretiles=TRUE;

			Rct2MapDataFunc(MDF_READ,x,y,&MapData,512);

			LandI=GetLandI(MapData);
			landCount=GetLandCount(MapData);
			landEdgeType=GetLandEdgeType(MapData,LandI);
			landGroundType=GetLandGroundType(MapData,LandI);

			i=0;

			switch(fclass)
			{
			case MF_SORT:
			
				SortMapTileElements(func,&MapData);
				break;

			case MF_CLEARANCE:
			case MF_OWN:											
			case MF_LAND: 
			case MF_SCEN: 
			case MF_PATH: 
			case MF_RIDE:
			case MF_ALL:

				if(fclass==MF_ALL)
				{
					if(func==ALL__CHANGE_LAND_TYPE)
						allLandMatch=
							(allChangeLand.edgeFlags&(1<<landEdgeType))
							||(allChangeLand.groundFlags&(1<<landGroundType));
					else
						allLandMatch=
							(allRaiseLower.edgeFlags&(1<<landEdgeType))
							||(allRaiseLower.groundFlags&(1<<landGroundType));
				}

				do
				{
					moretiles=true;
					elmttype=MapData[i].byte0.elmtType;
				
				//	if(PointInRect(&ValidXYRange, MakePoint(x,y)))
					{
						switch(fclass)
						{
						case MF_CLEARANCE:

							switch(func)
							{
							case CLEARANCE_ZEROALL_RELATIVELY:
							LINE_CLEARANCE_ZEROALL_RELATIVELY:
								MapData[i].clearheight=MapData[i].baseheight;
								break;
							case CLEARANCE_ZEROALL_ABSOLUTELY:
								if(elmttype==MET_SURFACE)
									goto LINE_CLEARANCE_ZEROALL_RELATIVELY;
////								
								MapData[i].clearheight=RCT2_MINHEIGHT;
								break;
							case CLEARANCE_RESTOREALL:
								MapData[i].clearheight=MapData[i].baseheight
								+GetElementClearance(FALSE,&(MapData[i]));
								break;							
							}
							break;

						case MF_ALL:
							switch(func)
							{
							case ALL_GETCOUNT:
								++allGetCount.count;
								break;
							default:
								goto LINE_MAPFUNC_MAINSWITCH;
							}
							break;


						case MF_OWN:											
						case MF_LAND: 
						case MF_SCEN: 
						case MF_PATH: 
						case MF_RIDE:
						LINE_MAPFUNC_MAINSWITCH:


												
							switch(elmttype)
							{
							case MET_TRACKELMT:
							//case MET_SHOPSTALL:
								switch(fclass)
								{

								case MF_ALL:
								case MF_RIDE:
									switch(func)
									{
									case ALL_RAISELOWER:
										if(allLandMatch&&(allRaiseLower.objFlags&OTF_RIDETRACK)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											goto LINE_RIDE_RAISELOWER;
										else
											break;

									case RIDE_GETLOWHIGH:
										if((ridelowhigh.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(ridelowhigh.index))
										)
										{	*ridelowhigh.low=
												min(*ridelowhigh.low,(BYTE)MapData[i].baseheight);
											*ridelowhigh.high=
												max(*ridelowhigh.high,(BYTE)MapData[i].baseheight);
										}
										break;

									case RIDE_RAISELOWER:
										if((raiselower.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(raiselower.index)))
										{	
										LINE_RIDE_RAISELOWER:
										////
											switch(MapData[i].byte4.elmtID)
											{
											case TRACK_STATIONPLATFORM_END:
											case TRACK_STATIONPLATFORM_BEGIN:
											case TRACK_STATIONPLATFORM_MIDDLE:
												//don't raise/lower these
												/*
												if(!(*raiselower.stationRaised&(MapData[i].))
												{	//raise station stats	
													*(raiselower).stationRaised=TRUE;
												}
												*/
												break;
											default:
												switch(func)
												{
												case RIDE_RAISELOWER:
													MapData[i].baseheight+=(BYTE)(raiselower.heightoffset);
													MapData[i].clearheight+=(BYTE)(raiselower.heightoffset);
													break;
												case ALL_RAISELOWER:
													MapData[i].baseheight=
														(BYTE)((short)(MapData[i].baseheight+allRaiseLower.offset)*2/2);
													MapData[i].clearheight=
														(BYTE)((short)(MapData[i].clearheight+allRaiseLower.offset)*2/2);				
													break;
												}
												/*
												if((LandI!=RCT2_WORD_EMPTY)
												   &&(MapData[LandI].baseheight>=MapData[i].baseheight)
												   &&(LandI<i)
												)
												{	SwapMapDataElements(&MapData,LandI,i);
													LandI=i;
												}
												*/
												break;
											}
										}
										break;
			

									case RIDE_BURY:
										if
										(	(bury.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(bury.index))	
										)
										{	
	////
											LINE_RIDE_BURY:
												if((LandI!=RCT2_WORD_EMPTY)&&(MapData[LandI].baseheight<=MapData[i].clearheight))
												{
													MapData[LandI].baseheight=
													MapData[LandI].clearheight=
														(MapData[i].clearheight+1)&~1;
													//MapData[i].clearheight=MapData[i].baseheight;
													//memswap(&MapData[LandI],&MapData[i],sizeof(PARKMAPDATA));
													if(LandI<i)
													{	SwapMapDataElements(&MapData,LandI,i);
														LandI=i;
													}
												}
										}
										break;
									case RIDE_EXCAVATE:
										if
										(	(excavate.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(excavate.index))
										)
										{
											LINE_RIDE_EXCAVATE:
												if((LandI!=RCT2_WORD_EMPTY)&&(MapData[LandI].baseheight>=MapData[i].baseheight))
												{
													MapData[LandI].baseheight=
													MapData[LandI].clearheight=
														(MapData[i].baseheight)&~1;
													if(LandI>i)
													{	SwapMapDataElements(&MapData,i,LandI);
														LandI=i;
													}
												}
										}
										break;
									case RIDE_ZEROCLEARANCE:
										if
										(	(zeroclearance.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(zeroclearance.index))
										)
										{
											LINE_RIDE_ZEROCLEARANCESTRUCT:
												MapData[i].clearheight=RCT2_MINHEIGHT;
										}
										break;

									case RIDE__TOGGLE_VISIBILITY:
										if
										(	(toggleVisibility.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(toggleVisibility.index))
										)
										{
											LINE__RIDE__TOGGLE_VISIBILITY:
											if(i>1)
											{
												MapData[i-1].byte0.data
													=(BYTE)0XFF;
												moretiles=false;
											}
										}
										break;

									case RIDE__TOGGLE_CHAIN:
										if
										(	(toggleChain.colorscheme==(MapData[i].byte6.color&COLORCSCHEME_MASK))
											&&(MapData[i].byte7.rideindex==(BYTE)(toggleChain.index))
										)
										{
											LINE__RIDE__TOGGLE_CHAIN:
											if((BYTE)MapData[i].byte0.elmtSpec06==2)
											{
												MapData[i].byte0.elmtSpec06=0;
											}
											else
											{
												MapData[i].byte0.elmtSpec06=2;
											}												
										}
										break;

									} //switch(func)
									break;
								} //switch(fclass)
								break;
							case MET_FENCEWALL:
								switch(fclass)
								{
								case MF_ALL:
									switch(func)
									{
									case ALL_RAISELOWER:
										if((allLandMatch)&&(allRaiseLower.objFlags&OTF_WALLS)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											MapData[i].baseheight+=allRaiseLower.offset;
											MapData[i].clearheight+=allRaiseLower.offset;
										}																				
										break;
									case ALL_REMOVE:
										if((allLandMatch)&&(allRemove.objFlags&OTF_WALLS)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											RemoveMapElement(&MapData,&i,&LandI);
										}
										break;


									}
									break;
								}
								break;
							case MET_SCENMULTILE:

								switch(fclass)
								{
								case MF_ALL:
									switch(func)
									{
									case ALL_RAISELOWER:
										if((allLandMatch)&&(allRaiseLower.objFlags&OTF_LARGESCENERY)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											MapData[i].baseheight+=allRaiseLower.offset;
											MapData[i].clearheight+=allRaiseLower.offset;
										}																				
										break;
									case ALL_REMOVE:
										if((allLandMatch)&&(allRemove.objFlags&OTF_LARGESCENERY)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											RemoveMapElement(&MapData,&i,&LandI);
										}
										break;
									}
									break;
								}
								break;

							case MET_BANNERS:

								switch(fclass)
								{
								case MF_ALL:

									if(MapData[i].byte0.data==(BYTE)0XFF) //NULL
									{
										switch(func)
										{
										case ALL_RAISELOWER:
											if((allLandMatch)&&(allRaiseLower.objFlags&OTF_NULL)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											{
												MapData[i].baseheight+=allRaiseLower.offset;
												MapData[i].clearheight+=allRaiseLower.offset;
											}																				
											break;
										case ALL_REMOVE:
											if((allLandMatch)&&(allRemove.objFlags&OTF_NULL)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											{
												RemoveMapElement(&MapData,&i,&LandI);
											}
											break;
										}
									}
									else
									{
										switch(func)
										{
										case ALL_RAISELOWER:
											if((allLandMatch)&&(allRaiseLower.objFlags&OTF_PATHBANNER)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											{
												MapData[i].baseheight+=allRaiseLower.offset;
												MapData[i].clearheight+=allRaiseLower.offset;
											}																				
											break;
										case ALL_REMOVE:
											if((allLandMatch)&&(allRemove.objFlags&OTF_PATHBANNER)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											{
												RemoveMapElement(&MapData,&i,&LandI);
											}
											break;
										}
										break;
									}
									break;
								}
								break;

							case MET_SURFACE:

								// svI=LandI=i;
								
								switch(fclass)
								{
								case MF_OWN:
									GetOwnership(&ownership,&border,&MapData[i]);
									border=BORDERFENCE_NONE;
									
									switch(func)
									{
															
									case OWN_INVERT:
									case OWN_INVERTIGNORE:

										if
										(	(func==OWN_INVERTIGNORE)
											&&(ownership&(OWN_RIGHTSOWNED|OWN_RIGHTSAVAIL|OWN_LANDAVAIL))
											&&(!(ownership&OWN_LANDOWNED))
										)
										{
											ownership++;	//ignore
											ownership--;
										}
										else
										{
										if ((ownership&OWN_LANDOWNED)==0)	
											ownership=OWN_LANDOWNED|OWN_LANDAVAIL;
										else 
											ownership=0;
										}

										//ownership=~ownership&(OWNERSHIP_MASK>>OWNERSHIP_SHIFT);	
										break;

									case OWN_UNOWNTORIGHTS:
										if(ownership==0)ownership=(OWN_RIGHTSOWNED|OWN_RIGHTSAVAIL); 
																						
										break;					

									case OWN_DEOWNBORDER:
										if	
										(	(x==1)||(y==1)
											||(x==(parksize-2))
											||(y==(parksize-2))
										)
											ownership=OWN_UNOWNED;
										else
											goto skipwrite_001;
										break;
									case OWN_OWNALLLAND:
										svownership=ownership;
										if (ownership&OWN_LANDOWNED)
											wasUnowned=FALSE;
											
										else
										{	ownership=OWN_LANDOWNED|OWN_LANDAVAIL;
											wasUnowned=TRUE;
										}

										break;

									case OWN_RESTOREBORDERFENCE:
										if(!(ownership&OWN_LANDOWNED))
											border=GetBorderFenceBits(x,y);	
										break;

									case OWN_REMOVEBORDERFENCE:
										//border=BORDERFENCE_NONE;
										break;
									}
									
									SetOwnership(&MapData[i],ownership,border);
									svI=i;
																
								skipwrite_001:
									break;

								case MF_LAND:
									switch(func)
									{
									case LAND_MOWGRASS:
										MapData[i].byte6.grass=
											(MapData[i].byte6.grass
											&~GRASSSTATE_MASK)
											|GRASSSTATE_MOWED;
										break;

									case LAND_MOWGRASSPLAIN:
										MapData[i].byte6.grass=
											(MapData[i].byte6.grass
											&~GRASSSTATE_MASK)
											|GRASSSTATE_CLEAR;

										break;

									case LAND_CAPATMAXHEIGHT:
										MapData[i].baseheight=
										MapData[i].clearheight=
											min((unsigned)MapData[i].baseheight,RCT2_MAXHEIGHT);

										break;

									case LAND_FIXINVISIBLEBORDER:
										if(!PointInRect(&ValidXYRange,MakePoint(x,y)))
										#if 0	
											if(memcmp(&MapData[i],&BORDERTILE,sizeof(MapData[i]))!=0)
										#endif //0	
												memcpy(&MapData[i],&BORDERTILE,sizeof(MapData[i]));
										break;
									case LAND_DELETEEXTRAS:
										if(i!=LandI)
											RemoveMapElement(&MapData,&i,&LandI);
										else 
											;
										break;

									}
									break;

								case MF_ALL:
									switch(func)
									{
									case ALL_RAISELOWER:
										if(allLandMatch)
										{
											if(allRaiseLower.objFlags&OTF_WATER)
											{	MapData[i].byte5.terrainWater=
												(
													(a=MapData[i].byte5.terrainWater&~WATER_ABSHEIGHTBITMASK
													)
													|
													(b=	(	(MapData[i].byte5.terrainWater&WATER_ABSHEIGHTBITMASK
															)+(allRaiseLower.offset/2)
														)&WATER_ABSHEIGHTBITMASK
													)
												);
											}

											if(allRaiseLower.objFlags&OTF_LAND)
											{	MapData[i].baseheight
												=MapData[i].clearheight
												=(MapData[i].clearheight+allRaiseLower.offset)&~1;
											}
										}
										break;

									case ALL__CHANGE_LAND_TYPE:
										if(allLandMatch)
										{
											SetLandGroundType(&MapData[i],allChangeLand.newLandType);
										}
										break;
									}
									break;
								}
								
								svI=i;
								
								break;

							case MET_PATH:
								switch(fclass)
								{
								case MF_PATH:

									switch(func)
									{
									case PATH_EMPTYTRASH:
										if (	(MapData[i].byte5.pathAdditions!=0)
												&&!(MapData[i].byte0.elmtSpec00&ES00_FLAG_ISQUEUE)	)
											MapData[i].byte7.pathAdditionStatus=PAS_ALLTRASHEMPTY; //empty
										break;
									case PATH_FIXVANDALISM:
										MapData[i].byte1.pathAddsVandalized=BIT_CLEAR;
										break;										
									case PATH_VANDALIZE:
										MapData[i].byte1.pathAddsVandalized=BIT_SET;
										break;										
									}
									break;

								case MF_OWN:
									switch(func)
									{
									case OWN_OWNALLLAND:
										if(wasUnowned)
											if(LandI!=0xffff)
												SetOwnership(&MapData[LandI],OWN_RIGHTSOWNED|OWN_RIGHTSAVAIL,border);
										break;

									}

								case MF_ALL:
									switch(func)
									{
									case ALL_RAISELOWER:
										if((allLandMatch)&&(allRaiseLower.objFlags&OTF_PATH)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											MapData[i].baseheight+=allRaiseLower.offset;
											MapData[i].clearheight+=allRaiseLower.offset;
										}																				
										break;
									case ALL_REMOVE:
										if((allLandMatch)&&(allRemove.objFlags&OTF_PATH)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											RemoveMapElement(&MapData,&i,&LandI);
										}
										break;
									}
									break;
								}


								break;
							
							case MET_SCEN1TILE:
								switch(fclass)
								{
								case MF_SCEN:
									switch(func)
									{
									case SCEN_WATERGARDENS:
										MapData[i].byte5.scenAge=0;
										break;
									}

								case MF_ALL:
									switch(func)
									{
									case ALL_RAISELOWER:
										if((allLandMatch)&&(allRaiseLower.objFlags&OTF_SMALLSCENERY)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											MapData[i].baseheight+=allRaiseLower.offset;
											MapData[i].clearheight+=allRaiseLower.offset;
										}
										break;
									case ALL_REMOVE:
										if((allLandMatch)&&(allRemove.objFlags&OTF_SMALLSCENERY)
											&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
										{
											RemoveMapElement(&MapData,&i,&LandI);
										}
										break;
									}
									break;
								}
								break;

		
							case MET_ENTRYEXIT:

								switch (MapData[i].byte4.elmtID&3)
								{
								case EE_PARKGATE:

									switch(fclass)
									{
									case MF_OWN: 
										switch(func)
										{
										case OWN_INVERT:
	#ifdef __KEEPENTRYUNOWNED__								
											MapData[i].byte7.ownership=0;	
	#endif											
											break;
										}
										break;
									case MF_ALL:
										switch(func)
										{
#undef RAISELOWERPARKGATES
#ifdef RAISELOWERPARKGATES
										case ALL_RAISELOWER:
											if((allLandMatch)&&(allRaiseLower.objFlags&OTF_PARKENTRANCE)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											{
												MapData[i].baseheight+=allRaiseLower.offset;
												MapData[i].clearheight+=allRaiseLower.offset;
											}
											break;
#endif RAISELOWERPARKGATES

										}
										break;
									}
									break;

								case EE_RIDEEXIT:
								case EE_RIDEENTRY:
									switch(fclass)
									{
									case MF_ALL:
									case MF_RIDE:
										switch(func)
										{	
									
										case ALL_RAISELOWER:
											if(allLandMatch&&(allRaiseLower.objFlags&OTF_RIDETRACK))
												goto LINE_RIDE_RAISELOWER;
											break;

										case RIDE_RAISELOWER:
											if(raiselower.colorscheme==COLORCSCHEME_STATIONENTRY)
												goto LINE_RIDE_RAISELOWER;
											break;
																		
										case RIDE_BURY:
											if(bury.colorscheme==COLORCSCHEME_STATIONENTRY)
												goto LINE_RIDE_BURY;
											break;			
										
										case RIDE_EXCAVATE:
											if(excavate.colorscheme==COLORCSCHEME_STATIONENTRY)
												goto LINE_RIDE_EXCAVATE;
											break;			
										case RIDE_ZEROCLEARANCE:
											if(zeroclearance.colorscheme==COLORCSCHEME_STATIONENTRY)
												goto LINE_RIDE_ZEROCLEARANCESTRUCT;
											break;			
										case RIDE__TOGGLE_VISIBILITY:
											if(toggleVisibility.colorscheme==COLORCSCHEME_STATIONENTRY)
												goto LINE__RIDE__TOGGLE_VISIBILITY;
											break;			
										case RIDE__TOGGLE_CHAIN:
											if(toggleChain.colorscheme==COLORCSCHEME_STATIONENTRY)
												goto LINE__RIDE__TOGGLE_CHAIN;
											break;			

										}
										break;
									}
									break;
								}
								break;
							}
						} //switch(elmttype)
					} //switch(fclass)

					moretiles=moretiles&&(!(MapData[i].byte1.lastElementOnTile)&&(i<256));
					i++;
				}			
				while (moretiles);
				break;
			default:
				break;
			} //switch(fclass)

			Rct2MapDataFunc(MDF_WRITE,x,y,&MapData,512);

		}	//X	
		
	} //Y

	Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);

	SetCursor(hcursor);

	return TRUE;

	#undef allGetCount
	#undef allRemove
	#undef allChangeLand
	#undef allRaiseLower
	#undef excavate
	#undef zerclearance
	#undef bury	
	#undef raiselower
	#undef ridelowhigh
}

int CapLandAtMaxHeight()
{
	return MapFunc(MF_LAND,LAND_CAPATMAXHEIGHT,NULL);
}

int FixInvisibleBorder()
{
	return MapFunc(MF_LAND,LAND_FIXINVISIBLEBORDER,NULL);
}

int InvertOwnership()
{
	return MapFunc(MF_OWN,OWN_INVERT,NULL);
}

int InvertOwnershipIgnore()
{
	return MapFunc(MF_OWN,OWN_INVERTIGNORE,NULL);
}


int ChangeUnowntoRights()
{
	return MapFunc(MF_OWN,OWN_UNOWNTORIGHTS,NULL);
}


int MowGrassPlain()
{
	return MapFunc(MF_LAND,LAND_MOWGRASSPLAIN,NULL);
}

int MowGrass()
{
	return MapFunc(MF_LAND,LAND_MOWGRASS,NULL);
}

int EliminateDuplicateSurfaceData()
{
	return MapFunc(MF_LAND,LAND_DELETEEXTRAS,NULL);
}

int WaterGardens()
{
	return MapFunc(MF_SCEN,SCEN_WATERGARDENS,NULL);

}

int EmptyTrash()
{
	return MapFunc(MF_PATH,PATH_EMPTYTRASH,NULL);
}

int VandalizePark()
{
	return MapFunc(MF_PATH,PATH_VANDALIZE,NULL);
}

int FixVandalism()
{
	return MapFunc(MF_PATH,PATH_FIXVANDALISM,NULL);
}

int DeownBorderLand()
{
	return MapFunc(MF_OWN,OWN_DEOWNBORDER,NULL);
}

int OwnAllLand()
{
	return MapFunc(MF_OWN,OWN_OWNALLLAND,NULL);
}

int RestoreBorderFence()
{
	return MapFunc(MF_OWN,OWN_RESTOREBORDERFENCE,NULL);
}

int RemoveBorderFence()
{
	return MapFunc(MF_OWN,OWN_REMOVEBORDERFENCE,NULL);
}

int ZeroAllClearancesRelatively()
{
	return MapFunc(MF_CLEARANCE,CLEARANCE_ZEROALL_RELATIVELY,NULL);
}

int ZeroAllClearancesAbsolutely()

{
	return MapFunc(MF_CLEARANCE,CLEARANCE_ZEROALL_ABSOLUTELY,NULL);
}


int RestoreAllClearances()
{
	return MapFunc(MF_CLEARANCE,CLEARANCE_RESTOREALL,NULL);
}

int SortMapElmentsInternally()
{
	return MapFunc(MF_SORT,SORT_BYBASEHEIGHT,NULL);
}

int GetRideLowHighHeights(int index,int colorscheme,short *ridelow,short *ridehigh)
{
	
	RIDELOWHIGH  ridelowhigh={index,colorscheme,ridelow,ridehigh};
	*ridelow=254;
	*ridehigh=2;

	return MapFunc(MF_RIDE,RIDE_GETLOWHIGH,&ridelowhigh);
}
////
int RaiseLowerRide
(	short index,short heightoffset,short colorscheme,
	short *stationRaised
)
{
	RIDE_RAISELOWERSTRUCT raiselower={index,heightoffset,colorscheme,stationRaised};
	*stationRaised=0;
	return MapFunc(MF_RIDE,RIDE_RAISELOWER,&raiselower);
}

int BuryRide(short index,short colorscheme)
{
	RIDE_BURYSTRUCT bury={index,colorscheme};
	return MapFunc(MF_RIDE,RIDE_BURY,&bury);
	
}

int ExcavateRide(short index,short colorscheme)
{
	RIDE_EXCAVATESTRUCT excavate={index,colorscheme};
	return MapFunc(MF_RIDE,RIDE_EXCAVATE,&excavate);
}

int MakeRideZeroClearance(short index,short colorscheme)
{
	RIDE_ZEROCLEARANCESTRUCT zerclearance={index,colorscheme};
	return MapFunc(MF_RIDE,RIDE_ZEROCLEARANCE,&zerclearance);
	
}

int ToggleRideVisibility(short index,short colorscheme)
{
	RIDE__TOGGLE_VISIBILITY_STRUCT toggleVisibility={index,colorscheme};	
	return MapFunc(MF_RIDE,RIDE__TOGGLE_VISIBILITY,&toggleVisibility);
	
}

int ToggleRideLiftChain(short index,short colorscheme)
{
	RIDE__TOGGLE_CHAIN_STRUCT toggleChain={index,colorscheme};
	return MapFunc(MF_RIDE,RIDE__TOGGLE_CHAIN,&toggleChain);
}


int RaiseLowerObjects
(	WORD objFlags,WORD groundFlags,WORD edgeFlags,WORD lowHeight,WORD highHeight,short offset
)
{
	ALL_RAISELOWERSTRUCT allRaiseLower=
	{	objFlags,groundFlags,edgeFlags,lowHeight,highHeight,offset};

	return MapFunc(MF_ALL,ALL_RAISELOWER,&allRaiseLower);
}
int RemoveObjects
(	WORD objFlags,WORD groundFlags,WORD edgeFlags,WORD lowHeight,WORD highHeight
)
{
	ALL_REMOVESTRUCT allRemove=
	{	objFlags,groundFlags,edgeFlags,lowHeight,highHeight};

	return MapFunc(MF_ALL,ALL_REMOVE,&allRemove);

}

int ChangeLandType
(	WORD newLandType,WORD groundFlags,WORD edgeFlags
)
{
	ALL__CHAMGE_LAND_STRUCT allChangeLand=
	{	newLandType,groundFlags,edgeFlags};

	return MapFunc(MF_ALL,ALL__CHANGE_LAND_TYPE,&allChangeLand);
}

DWORD GetUsedMapDataStructCount()
{
	ALL_GETCOUNTSTRUCT allGetCount={0};

	if(MapFunc(MF_ALL,ALL_GETCOUNT,&allGetCount))
		return allGetCount.count;
	else 
		return 0;
}

//-------------------------------

int OptimizeMapDataSpace()
{
	Rct2MapDataFunc(MDF_OPTIMIZE,0,0,NULL,0);	
};

//-------------------------------

int SetMapEntryPoints
(	int x1,int y1,int z1,
	int x2,int y2,int z2,
	short dir1,short dir2
)
{
	short mapsize=0;

	ENTRYPOINTSTRUCT mapEntry[2];
	short j;
	
	if(!WinRead(mainWindow,RCT2_TITLE,&mapsize,RCT2_ADDR_MAPSIZE,2)) return FALSE;

	x1=range(x1,1,mapsize-2)*32+16;
	x2=range(x2,1,mapsize-2)*32+16;
	y1=range(y1,1,mapsize-2)*32+16;
	y2=range(y2,1,mapsize-2)*32+16;
	z1=(range(z1,-6,117)+7);
	z2=(range(z2,-6,117)+7);

	mapEntry[0].x=x1;
	mapEntry[0].y=y1;
	mapEntry[0].z=z1;
	mapEntry[0].direction=dir1;
	mapEntry[1].x=x2;
	mapEntry[1].y=y2;
	mapEntry[1].z=z2;
	mapEntry[1].direction=dir2;


	for(j=0;j<2;j++)
	{
		switch(mapEntry[j].direction)
		{
		case RCT2_EAST:mapEntry[j].x-=7;break;
		case RCT2_SOUTH:mapEntry[j].y+=7;break;
		case RCT2_WEST:mapEntry[j].x+=7;break;
		case RCT2_NORTH:mapEntry[j].y-=7;break;
		}
	}

	WinWrite
	(	mainWindow,RCT2_TITLE,RCT2_ADDR_MAPENTRY,&mapEntry,
		sizeof(mapEntry)
	);


}
/*

									case MF_ALL:
										switch(func)
										{
										case ALL_RAISELOWER:
											if((allLandMatch)&&(allRaiseLower.objFlags&OTF_PARKENTRANCE)
												&&NumInRange(MapData[i].baseheight,allRaiseLower.lowHeight,allRaiseLower.highHeight))
											{
												MapData[i].baseheight+=allRaiseLower.offset;
												MapData[i].clearheight+=allRaiseLower.offset;
											}
											break;
										}
										break;
*/