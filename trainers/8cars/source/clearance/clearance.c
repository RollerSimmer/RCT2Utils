//clearance.c

#include "clearance.h"
#include "../rct2.h"
#include "../8cars.h"
#include <objdat.h>
#include <windows.h>
#include <string.h>


int GetObjStringTableSize(char* StrTblPtr)
{
	BYTE
		StrTbl[255*LNG_PORTUGESE],leadCh,ch;
	int 
		pos; 
	
	WinRead(mainWindow,RCT2_TITLE,&StrTbl[0],StrTblPtr,sizeof(StrTbl));

	pos=0;

	do
	{	leadCh=StrTbl[pos++];
		if((leadCh!=(char)0xff)&&(leadCh<=LNG_PORTUGESE))
			pos+=strlen(&StrTbl[pos])+1;
		else break;
	}
	while(1);

	return pos;
}


/*	
optimize: 
	small scenery

	walls
*/




int GetTrackElementClearance(LPPARKMAPDATA MapData)
{
	WORD 
		rideI=(BYTE)MapData->byte7.rideindex,
		elmtID=(BYTE)MapData->byte4.elmtID,
		pieceI=(BYTE)MapData->byte5.index,
		clearance,\
		trackType,
		vehiObjID;
	BYTE
		*ptr,bytevalue,i,elmtArrayIndex;

	TRACKSPECSTRUCT
		trackSpecs;

	TRACKPIECESPECSTRUCT
		*pieceSpecsPtr;

	TRACKPIECESPECSTRUCTARRAY
		pieceSpecs;

	TYPE0HEADER 
		rideObjHeader,*rideObjPtr;

	RIDESTRUCT
		ride;

	WinRead
	(	mainWindow,RCT2_TITLE,&ride,
		ptr=(RIDESTRUCT*)RCT2_ADDR_RIDES+rideI,
		sizeof(ride)
	);
	trackType=ride.trackType&0xff;
	vehiObjID=ride.vehiObjID&0xff;

	ptr=RCT2_ADDR_TRACKTYPECONSTRUCTOP;
	
	if	
	(	!WinRead
		(	mainWindow,RCT2_TITLE,&trackSpecs,
			ptr=&(((TRACKSPECSTRUCT*)RCT2_ADDR_TRACKTYPECONSTRUCTOP)[trackType]),
			sizeof(TRACKSPECSTRUCT)
		)
	)
		return 0;

	clearance=((BYTE)trackSpecs.ClearanceBase>>3)&0xff;

	ptr=RCT2_ADDR_RIDEOBJECTFILEPOINTERS;

	WinRead(mainWindow,RCT2_TITLE,&rideObjPtr,
		(DWORD*)ptr+=vehiObjID,sizeof(rideObjPtr));
	WinRead(mainWindow,RCT2_TITLE,&rideObjHeader,rideObjPtr,
		sizeof(rideObjHeader));

	elmtArrayIndex=OLDELEMENTINDEX;

	for(i=0;i<NUMRIDECLASSFIELDS;i++)
	{
		if(rideObjHeader.rideclass[i]==RC_ROLLERCOASTER)
			elmtArrayIndex=NEWELEMENTINDEX;
	}

	ptr=RCT2_ADDRTRACKPIECECONSTRUCTOP(elmtArrayIndex);

	pieceSpecsPtr=0;

	WinRead(mainWindow,RCT2_TITLE,&pieceSpecsPtr,
		(DWORD*)ptr+=elmtID,sizeof(pieceSpecsPtr));
	WinRead(mainWindow,RCT2_TITLE,&pieceSpecs,pieceSpecsPtr,sizeof(pieceSpecs));

	if(pieceSpecs[pieceI].pieceI==pieceI)
		clearance+=((BYTE)pieceSpecs[pieceI].clearance>>3);
	
	return (BYTE)clearance;
}

//WinRead(mainWindow,RCT2_TITLE,,,sizeof())	

int GetSmallSceneryClearance(LPPARKMAPDATA MapData)
{
	WORD 
		elmtID=(BYTE)MapData->byte4.elmtID;

	BYTE
		*ptr=0;

	TYPE1HEADER	*smallScenObjHeaderPtr,smallScenObjHeader;

	ptr=RCT2_ADDR_SMALLSCENERYOBJECTFILEPOINTERS;

	if(!WinRead(mainWindow,RCT2_TITLE,
			&smallScenObjHeaderPtr,
			(DWORD*)ptr+=elmtID,sizeof(smallScenObjHeaderPtr)))
		return 0;

	if((DWORD)smallScenObjHeaderPtr==RCT2_DWORD_EMPTY)
	{	return 0;
	}
	else
	{	WinRead(mainWindow,RCT2_TITLE,&smallScenObjHeader,smallScenObjHeaderPtr,sizeof(smallScenObjHeader));
	
	return ((BYTE)(smallScenObjHeader.height)>>3)&0xff;
	}
}


int GetLargeSceneryClearance(LPPARKMAPDATA MapData)
{
	
	
	WORD 
		elmtID=(BYTE)MapData->byte4.elmtID,
		pieceI=(BYTE)MapData->byte5.index>>2,
		retv;

	DWORD 
		*ptrarray=0;

	DATGROUPINFO dgi;

	TYPE2HEADER	*largeScenObjHeaderPtr,largeScenObjHeader;

	TYPE2TILESPECPTR tileSpecsPtr;
	TYPE2TILESPEC tileSpecs;

	ptrarray=RCT2_ADDR_LARGESCENERYOBJECTFILEPOINTERS;

	if(!WinRead(mainWindow,RCT2_TITLE,&largeScenObjHeaderPtr,
				&(ptrarray[elmtID]),
				sizeof(largeScenObjHeaderPtr)))
		return 0;

	WinRead(mainWindow,RCT2_TITLE,&largeScenObjHeader,largeScenObjHeaderPtr,sizeof(largeScenObjHeader));

	tileSpecsPtr=&(largeScenObjHeaderPtr[1]);

	(char*)tileSpecsPtr+=GetObjStringTableSize(tileSpecsPtr);

	(char*)tileSpecsPtr+=sizeof(DATGROUPINFO);

	if(largeScenObjHeader.flags&T2_3DTEXT)
		(char*)tileSpecsPtr+=T2_3DLETTERTABLESIZE;

	if(!WinRead(mainWindow,RCT2_TITLE,&tileSpecs,&(tileSpecsPtr[pieceI]),sizeof(tileSpecs)))
		return 0;

	retv=((BYTE)tileSpecs.clearance>>3)&0xff;
	return retv;

}


int  GetEntryExitClearance(LPPARKMAPDATA MapData)
{
	WORD 
		entrytype=(BYTE)MapData->byte4.elmtID;
	
	switch (entrytype)
	{
	case EE_RIDEEXIT:	return EE_RIDEEXIT_CLEARANCE;
	case EE_RIDEENTRY:	return EE_RIDEENTRY_CLEARANCE;
	case EE_PARKGATE:	return EE_PARKGATE_CLEARANCE;
	default:			return 0;
	}
}

int GetFenceWallSceneryClearance(LPPARKMAPDATA MapData)
{
	WORD 
		elmtID=(BYTE)MapData->byte4.elmtID;

	DWORD 
		*ptrarray;

	TYPE3HEADER	*fenceWallScenObjHeaderPtr,fenceWallScenObjHeader;

	ptrarray=RCT2_ADDR_WALLOBJECTFILEPOINTERS;

	if(!WinRead(mainWindow,RCT2_TITLE,&fenceWallScenObjHeaderPtr,
			ptrarray=&(ptrarray[elmtID]),
			sizeof(fenceWallScenObjHeaderPtr)))
		return 0;

	if((DWORD)ptrarray==RCT2_DWORD_EMPTY)
	{	return 0;
	}
	else
	{	WinRead(mainWindow,RCT2_TITLE,&fenceWallScenObjHeader,
			fenceWallScenObjHeaderPtr,sizeof(fenceWallScenObjHeader));
		return (BYTE)fenceWallScenObjHeader.clearance;
	}
}


int GetBannerClearance()
{
	return 0;
}

short GetElementClearance(int init,LPPARKMAPDATA MapData)
{
	WORD i;
	PARKMAPDATA tmpMapData;

	static BYTE 
		WallClearances[RCT2_OBJMAX_WALLS],
		SScenClearances[RCT2_OBJMAX_SMALLSCENERY];

	if(init)
	{
		//init walls
		for (i=0;i<RCT2_OBJMAX_WALLS;i++)
		{	(BYTE)tmpMapData.byte4.elmtID=i;
			WallClearances[i]=GetFenceWallSceneryClearance(&tmpMapData);
		}
		//init small scenery
		for (i=0;i<RCT2_OBJMAX_SMALLSCENERY;i++)
		{	(BYTE)tmpMapData.byte4.elmtID=i;
			SScenClearances[i]=GetSmallSceneryClearance(&tmpMapData);
		}
		return 0;
	}

	i=MapData->byte4.elmtID;

	switch (MapData->byte0.elmtType)
	{
	case MET_SURFACE:
		return 0;
	case MET_PATH:		
		return STATIC_PATH_CLEARANCE;
	case MET_TRACKELMT:
	//case MET_SHOPSTALL:
		return GetTrackElementClearance(MapData);
	case MET_SCEN1TILE:	
		return SScenClearances[i];
	case MET_ENTRYEXIT:
		return GetEntryExitClearance(MapData);
	case MET_FENCEWALL:
		return WallClearances[i];
	case MET_SCENMULTILE:
		return GetLargeSceneryClearance(MapData);
	case MET_BANNERS:
		return GetBannerClearance(MapData);
	}
	return 0; //temporary result
	//get clearance of map object
}

