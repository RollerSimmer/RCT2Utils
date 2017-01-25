#include"ConvertParkData.h"
#include"rideConvert.h"
#include<codeshortcuts.h>

ConvertBanners(BANNERINFOSTRUCT*b6,BANNERINFOSTRUCT*b4)
;

ConvertNameStrings
(
char*n6
,char*n4
)
;

ConvertAnimationObjLocations
(
ANIMATIONOBJECTLOCATION*a6
,ANIMATIONOBJECTLOCATION*a4
)
;
ClearDataLogging(SV6_PARKDATA&p6)
;


ConvertParkData
(
	SV6_FILE&s6
	,SV4_PARKDATA&p4
)
{
	SV6_PARKDATA&p6=s6.fileDataA.parkData;
	DWORD debug_addr1;
	DWORD debug_addr2;
	int i;


	p6.parkNameOffset=p4.parkNameOffset;
	p6.parkSize=p4.parkSize;

	p6.mainParkEntry=p4.mainParkEntry;
	//p6.mainParkEntry.z/=2;
	p6.parkEntriesXpos[0]=p6.mainParkEntry.x;
	p6.parkEntriesYpos[0]=p6.mainParkEntry.y;
	p6.parkEntriesZpos[0]=p6.mainParkEntry.z;	
	for_i_base(i,1,3)
	{
	p6.parkEntriesXpos[i]=0x8000;
	p6.parkEntriesYpos[i]=0x8000;
	p6.parkEntriesZpos[i]=0x8000;
	}

	debug_addr1=DWORD(&p6.mainParkEntry)-DWORD(&p6);
	debug_addr2=DWORD(&p4.mainParkEntry)-DWORD(&p4);

	p6.horzViewPos=p4.horzViewPos;
	p6.vertViewPos=p4.vertViewPos;
	p6.zoomFactor=p4.zoomFactor;
	p6.viewingAngle=p4.viewingAngle;
	p6.nextGuestNumber=0;

	memcpy
	(
	p6.peepMapEntryPoints
	,p4.peepMapEntryPoints
	,sz(p6.peepMapEntryPoints)
	)
	;

	memcpy(&p6.parkStatus,&p4.parkStatus,sz(p6.parkStatus));
	
	p6.unk_32_x_par_parkSize_minus_1_par
		=int(32)*(p6.parkSize-1);
	p6.unk_value_at_0x272478_plus_011E
		=p6.unk_32_x_par_parkSize_minus_1_par
		+0x011E;
	p6.unk_value_at_0x272478_minus_1_except_fullSizePark
		=p6.unk_32_x_par_parkSize_minus_1_par
		-1;
	#if 0
	if(p6.parkSize==256)
		p6.unk_value_at_0x272478_minus_1_except_fullSizePark
		=0x0fff;
	#endif	

	ConvertBanners
	(
	&p6.bannerInfo[0]
	,&p4.bannerInfo[0]
	);

	ConvertNameStrings
	(
	&p6.nameStrings[0][0]
	,&p4.nameStrings[0][0]
	);

	#define s46(a)

	p6.numAnimationObjects
	=p4.numAnimationObjects;


	ConvertAnimationObjLocations
	(
	&p6.animationObjectLocations[0]
	,&p4.animationObjectLocations[0]
	);

	p6.numRideStructsUsed
	=p4.numRideStructsUsed;

	#if 1
	ConvertRides
	(	
		&p6.rides,&p4.rides
		,&p6.numRideStructsUsed
		,p4.numRideStructsUsed
	);
	#endif

	

	#if 1
	s6.ClearSprites();
	#endif

	ClearDataLogging(p6);

	//do more details later
}


ConvertBanners(BANNERINFOSTRUCT*b6,BANNERINFOSTRUCT*b4)
{
	int i;
	#if(_426__CONVERT_BANNERS)
	for(i=0;i<100;i++)
	{
		b6[i]=b4[i];
	}
	for(i=100
	#else
	for(i=0
	#endif
	;i<250;i++)
	{
		b6[i].bannerStyle=RCTX_BYTE_EMPTY;
	}

}

ConvertNameStrings
(
char*n6
,char*n4
)
{
	memcpy(n6,n4,1024*32);
}

ConvertAnimationObjLocations
(
ANIMATIONOBJECTLOCATION*a6
,ANIMATIONOBJECTLOCATION*a4
)
{
	const c4=1000;
	const c6=2000;
	int i;
	for(i=0;i<c4;i++)
	{
		a6[i]=a4[i];
		a6[i].height=a4[i].height/2;
	}
	for(i=c4;i<c6;i++)
	{
		memset(&a6[i],0,sz(a6[i]));
		a6[i].objectCode=0xd;
	}
}

ClearDataLogging(SV6_PARKDATA&p6)
{
	int i;
	
	for_i0(i,8)
	{
		memset
		(
		&p6.dataLogging[i][0],0,sz(p6.dataLogging[i])
		);
		p6.dataLogging[i][0]=RCTX_BYTE_EMPTY;
	}
}