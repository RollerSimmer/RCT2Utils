
#define dllPort __declspec(dllexport)
#include<rct2lib.h>
#include<fileio2.h>
#include<codeshortcuts.h>
#include<stdio.h>
#include"sv6.h"
#include"../../readResource.h"
#include"../../resource.h"
#include<rct_svx.h>

BYTE byteEmpty=0xff,&be=byteEmpty;
WORD wordEmpty=0xffff,&we=wordEmpty;
DWORD dwordEmpty=0xffffffff,&dwe=dwordEmpty;

gnp_SetSpriteStats(SPRITESTATS&);
gnp_SetParkInfo(SV6_PARKDATA&);

int 	
dllPort 
SV6_FILE::
GenNewPark(HMODULE module)
{
	SV6_FILE&p=*this;

	SV6_HEADER&h=this->fileDataA.header;
	SV6_OBJDAT_HEADER_BLOCK&ai=this->fileDataA.availableItems;
	SV6_TIMEDATA&td=this->fileDataA.timeData;
	SV6_PARKMAPDATABLOCK&map=this->fileDataA.parkMap;
	SV6_PARKDATA&pd=this->fileDataA.parkData;

	SV6_PARKMAPDATA mt;

	int i,x,y;

	//HMODULE module;
	//module=GetModuleHandle("rct2lib.dll");

	ReadResource
	(	module,"GEN_TEMPLATE"
		,IDR__GEN_TEMPLATE__SV6_HEADER
		,&h,sz(SV6_HEADER)
	);

	//avail items

	ReadResource
	(	module,"GEN_TEMPLATE"
		,IDR__GEN_TEMPLATE__OBJ_DAT_TABLE
		,&ai,sz(SV6_OBJDAT_HEADER_BLOCK)
	);

	//time

	memset(&td,0,sz(SV6_TIMEDATA));

	//map


	memset(map,0,sz(SV6_PARKMAPDATABLOCK));

	#if 0

	ReadResource
	(	module,"GEN_TEMPLATE"
		,IDR__GEN_TEMPLATE__PARK_MAP_ENTRY
		,&mt,sz(SV6_PARKMAPDATA)
	);

	for_i0(y,256)
	{
	for_i0(x,256)
	{
		map[y*256+x]=mt;
	}
	}
	#else
	
	ReadResource
	(	module,"GEN_TEMPLATE"
		,IDR__GEN_TEMPLATE__PARK_MAP
		,&map[0],sz(SV6_PARKMAPDATABLOCK)
	);

	#endif
	InitMapPtrs();

	//park

	memset(&pd,0,sz(SV6_PARKDATA));

	ReadResource
	(	module,"GEN_TEMPLATE"
		,IDR__GEN_TEMPLATE__PARK_DATA
		,&pd.parkNameOffset
		,sz(SV6_PARKDATA)
		-sz(pd.spriteStats)
		-sz(pd.sprites)
	);

	SV6_SPRITESTRUCT*spr;

	WORD next=1;
	WORD fore=we;

	for_i0(i,SV6_NUMSPRITES)
	{
		spr=&pd.sprites[i];
		spr->spriteID=be;
		spr->spriteIndex=i;
		spr->nextInClass=next;
		spr->prevInClass=fore;
		fore=i;
		next++;
		if(next==SV6_NUMSPRITES)
			next=we;
	}

	gnp_SetSpriteStats(pd.spriteStats);

	//SV6_*spr;

		//clear menus and tables

	#define setAll(a)\
		memset(&a,be,sz(a))

	setAll(pd.ridesMenu);
	setAll(pd.vehicleMenu);
	setAll(pd.sceneryMenu);
	setAll(pd.bannerMenu);

	#undef setAll

	this->SetAllTrackFeatures();

		//info

	gnp_SetParkInfo(pd);
	this->ChangeMoney(200000);

		//rides

	
	for_i0(i,255)
	{
		MemClr(pd.rides[i]);
		pd.rides[i].trackType=be;
		
	}
		//messages already cleared

	return(1);
}


gnp_SetSpriteStats(SPRITESTATS&ss)
{
	ss.statsA.availSprites=SV6_NUMSPRITES;

	ss.statsA.firstVehicle
	=ss.statsA.firstPerson
	=ss.statsA.firstFloat
	=ss.statsA.firstJunk
	=ss.statsA.firstOversizedRideCar
	=we;

	ss.statsA.nextFreeSprite
	=ss.statsA.vehiCount
	=ss.statsA.peopleCount
	=ss.statsA.floatingCount
	=ss.statsA.junkCount
	=ss.statsA.oversizedCount
	=0;
}

gnp_SetParkInfo(SV6_PARKDATA&pd)
{
	WEATHER 
		WS_SUNNY={1920,0,0,23,23,0,0,0,0,0,0};

	pd.parkNameOffset.v=0;
	pd.loan=2000000;

	SV6_PARKSTATUS*ps=&pd.parkStatus;
	ps->freeAttractionEntry=1;
	//ps->highIntensityGuests=0;
	ps->noRealNames=1;
	//ps->opened=0;
	
	pd.climate=2;
	//pd.landPurchaseCost=0;

	pd.scenarioGoal=3;
	pd.parkValue=0;
	pd.companyValue=pd.parkValue+pd.money-pd.loan;

	pd.weather=WS_SUNNY;
	strcpy(pd.userName,"User");
	pd.admissionFee=100;

	#if 0
	pd.mainParkEntry.x=WORD(0X8000);

	pd.viewingAngle=0;
	pd.zoomFactor=0;
	if(pd.parkEntriesUsedFlag[0])
	{
	pd.horzViewPos=pd.parkEntriesXpos[0];
	pd.vertViewPos=pd.parkEntriesYpos[0];
	}	
	
	memset
	(	pd.peepMapEntryPoints
		,be,sz(pd.peepMapEntryPoints)
	);

	memset
	(
		pd.patrolAreas
		,be,sz(pd.patrolAreas)
	);

	memset
	(
		pd.staffTypePatrolAreas
		,be,sz(pd.staffTypePatrolAreas)
	);
	#endif

	strcpy(pd.scenarioFile,"BlankParkMaker");
}

int 	
dllPort 
SV6_FILE::
ChangeMoney(long newVal)
{
	long money,loan,highloan,checksum1,checksum2;
	SV6_PARKDATA&pd=this->fileDataA.parkData;

	money=newVal;
	loan=pd.loan;
	highloan=pd.maxLoan;

	/*
	1st financial checksum:
			[ 70093A minus cash, ror 5, 
			minus loan, ror
			7, add maxloan, ror 3 ] 
	*/

	//calc checksum1

	__asm
	{
		mov eax,70093Ah
		sub eax,money
		ror eax,5
		sub eax,loan
		ror eax,7
		add eax,highloan
		ror eax,3
		mov checksum1,eax
	}

	
	/*
	2nd financial checksum:
			cash ror thirteen, 
			xor 0F4EC9621
	*/

	//calc checksum2
	__asm
	{
		mov eax,money
		ror eax,13
		xor eax,0F4EC9621h
		mov checksum2,eax 
	}

//	softice rules

/*
	umm... rotate the amount of money(dword) by 0D and xor 
	by F4EC9621 then store it in 013587F8... that works for me 
*/
	pd.money=money;
	pd.financialChecksum_1=checksum1;
	pd.financialChecksum_2=checksum2;
}

dllPort 
int 	
SV6_FILE::
ClearSprites()
{
	SPRITESTATS*ss=&this->fileDataA.parkData.spriteStats;
	SV6_SPRITESTRUCT*s=&fileDataA.parkData.sprites[0];
	gnp_SetSpriteStats(*ss);

	SV6_SPRITESTRUCT*spr;

	long 
	i,
	next=1,
	fore=RCTX_WORD_EMPTY;

	for_i0(i,SV6_NUMSPRITES)
	{
		spr=&s[i];
		spr->spriteID=be;
		spr->spriteIndex=i;
		spr->nextInClass=next;
		spr->prevInClass=fore;
		fore=i;
		next++;
		if(next==SV6_NUMSPRITES)
			next=we;
	}
	return(true);

}
