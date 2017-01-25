#include"..\..\StdAfx.h"
#include"sv6.h" 
#include<codeshortcuts.h>





short
SV6_FILE
::
Rct2MapDataFunc
(	int mapdatafunc,short x,short y,LP_SV6_PARKMAPDATA mapdata,int count
)
{
	static SV6_PARKMAPPTRARRAY *mapptrs;
	static SV6_PARKMAPDATABLOCK *mapdatablock;
	static int mapDataBaseAddr;
	
	SV6_PARKMAPPTRARRAY *sortMapPtrs;
	SV6_PARKMAPDATABLOCK *sortMapDataBlock;
	DWORD i,sortI,nextFreeAddr,tileStructCount;

	SV6_PARKMAPDATA_2 trailStruct={0x16,0xD0,0xFF,0x10,0x01,0x00,0x5A,0x00};

	switch(mapdatafunc)
	{
	case RCT2_MDF_INIT:
		if(!this->ptrsInitted)
			InitMapPtrs();
		return true;
	case RCT2_MDF_READ:
		if(ptrsInitted)
			memcpy(mapdata,mapPtrs[y][x],sz(SV6_PARKMAPDATA)*count);
		return(ptrsInitted);
	case RCT2_MDF_WRITE:
		if(ptrsInitted)
			memcpy(mapPtrs[y][x],mapdata,sz(SV6_PARKMAPDATA)*count);
		return(ptrsInitted);
	case RCT2_MDF_DONE:
		return true;
	case RCT2_MDF_OPTIMIZE:

		#if 0

			if((sortMapDataBlock=malloc(sizeof(*sortMapDataBlock)))==NULL)
			{	
				MessageBox
				(	mainWindow,"Not enough memory (requires appx. 1MB free space)","Message",
					MB_OK|MB_APPLMODAL|MB_SETFOREGROUND|MB_ICONWARNING
				);
				return FALSE;
			}
			else 
			{
				Rct2MapDataFunc(MDF_INIT,0,0,NULL,0);

				InitMapDataBlock(sortMapDataBlock);

				sortI=0;

				for(y=0;y<RCT2_HIGHSIZE;y++)
				{
					for(x=0;x<RCT2_HIGHSIZE;x++)
					{
						i=GetMapIndex(x,y,mapptrs);

						tileStructCount=GetTileStructCount(&(*mapdatablock)[i]);
						memcpy
						(	&(*sortMapDataBlock)[sortI],&(*mapdatablock)[i],
							tileStructCount*sizeof(SV6_PARKMAPDATA)
						);

						SetMapIndex(x,y,mapptrs,sortI);
						
						sortI+=tileStructCount;					
					}
				}

				memcpy(&(*sortMapDataBlock)[sortI],&trailStruct,sizeof(trailStruct));

				memcpy(mapdatablock,sortMapDataBlock,sizeof(*mapdatablock));
				free(sortMapDataBlock);			

				Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);

				nextFreeAddr=sortI*sizeof(SV6_PARKMAPDATA)+(DWORD)RCT2_ADDR_PARKMAP;
				
				WinWrite
				(	mainWindow,RCT2_TITLE,RCT2_ADDR_PARKMAPPOINTER_NEXTFREE,
					&nextFreeAddr,sizeof(nextFreeAddr)
				);
				return TRUE;
			}
		#endif
		return true;
	}
	return FALSE;
}

dllPort 
void
SV6_FILE
::
InitMapPtrs()
{
	int x=0,y=0;
	int numTiles=(*parkSize)*2;
	bool done,tileDone;
	map_nextFree=&this->fileDataA.parkMap[0];

	for_i0(y,256)
	{
	for_i0(x,256)
	{
		this->mapPtrs[y][x]=map_nextFree;
		tileDone=false;
		do
		{
			tileDone=map_nextFree->byte1.lastElementOnTile;
			++map_nextFree;
		}
		while(!tileDone);
	}
	}
	this->ptrsInitted=true;
}

typedef union
{
	struct
	{
		short l:3;
		short h:1;
	};
	short t;
}
CONVERT_LAND_TYPE;



dllPort
SV6_PARKMAPDATA::GetLandType(short&ground,short&edge)
{
	CONVERT_LAND_TYPE
		g,e;

	SV6_MAPBYTE0_ALT
		*b0=(SV6_MAPBYTE0_ALT*)&this->byte0;

	g.t=0;
	e.t=0;

	g.l=byte5.terrainWater.ground;
	e.l=byte4.landslope.edge;

	g.h=b0->bit00;
	e.h=b0->bit07;

	ground=g.t;
	edge=e.t;
}

dllPort
SV6_PARKMAPDATA::SetLandType(short ground,short edge)
{
	CONVERT_LAND_TYPE
		g,e;

	SV6_MAPBYTE0_ALT
		*b0=(SV6_MAPBYTE0_ALT*)&this->byte0;

	g.t=ground;
	e.t=edge;

	byte5.terrainWater.ground=g.l;
	byte4.landslope.edge=e.l;

	b0->bit00=g.h;
	b0->bit07=e.h;

}









