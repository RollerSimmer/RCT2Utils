#include <windows.h>
#include"SV6.h"

#undef RCT2_WORD_EMPTY 
#define RCT2_WORD_EMPTY ((unsigned short)(0xffff))


#undef RCT2_FREEZE

#define TESTNEW

#include <malloc.h>
//#include "../ridefuncs/ridefuncs.h"
//#include "../parkstatus/parkstatus.h"

char itemcolor=0;

WORD GetLastFreeSprite(SV6_SPRITESTRUCTARRAY *spriteBlock,WORD firstfree)
{
	WORD index;
	#define cursprite ((*spriteBlock)[index])
	{	
		index=firstfree;

		while (cursprite.nextInClass!=RCT2_WORD_EMPTY)
		{	index=cursprite.nextInClass;
		}
		
		return index;
	}
	#undef cursprite
}

SortSpriteChain
(	SV6_SPRITESTRUCTARRAY *spriteBlock,
	short SpriteID,short *firstSpriteIndex
)
{

	int i,x,y,prevI,nextI;
	WORD curIndex;

	prevI=RCT2_WORD_EMPTY;
	
	for(i=0;i<SV6_NUMSPRITES;i++)
	{
		if((*spriteBlock)[i].spriteID==(BYTE)SpriteID)
		{	
			(*spriteBlock)[i].nextInClass=RCT2_WORD_EMPTY;
			if(prevI==RCT2_WORD_EMPTY)
				*firstSpriteIndex=i;
			else 
				(*spriteBlock)[prevI].nextInClass=i;				
			(*spriteBlock)[i].prevInClass=prevI;
			prevI=i;
		}		
	}
}


SV6_FILE
::
EmptyRidesOfGuests
(	SPRITESTATS *spritestats,
	SV6_SPRITESTRUCT *spriteBlock
)
{

	WORD index;
	RCT2_RIDESTRUCT 
		vehiOwner,
		*rideArray
		=&this->fileDataA.parkData.rides[0];
	index=spritestats->statsA.firstVehicle;
	while(index!=RCT2_WORD_EMPTY)
	{
		memcpy
		(	&vehiOwner,
			&(rideArray[spriteBlock[index].byte30.ownerRide]),
			sizeof(vehiOwner)
		);
		if(vehiOwner.trackType!=0x43) //mini golf
		{
			memset(&(spriteBlock[index].union52.guestsInVehicle),RCT2_BYTE_EMPTY,sizeof(spriteBlock[index].union52.guestsInVehicle)); //empty the seats in vehicles
			spriteBlock[index].unionB0.vehi.passengerCount[0]
				=spriteBlock[index].unionB0.vehi.passengerCount[1]
				=0;
		}
		index=spriteBlock[index].nextInClass;
	}

	index=spritestats->statsA.firstOversizedRideCar;
	while(index!=RCT2_WORD_EMPTY)
	{
		memcpy
		(	&vehiOwner,
			&(rideArray[spriteBlock[index].byte30.ownerRide]),
			sizeof(vehiOwner)
		);

		if(vehiOwner.trackType!=0x43) //mini golf
		{
			memset(&(spriteBlock[index].union52.guestsInVehicle),RCT2_BYTE_EMPTY,sizeof(spriteBlock[index].union52.guestsInVehicle));
			spriteBlock[index].unionB0.vehi.passengerCount[0]
				=spriteBlock[index].unionB0.vehi.passengerCount[1]
				=0;
		}
		index=spriteBlock[index].nextInClass;
	}

	EmptyRidesOfGuests(spritestats,spriteBlock);

	return true;
}


int RemoveSprite
(	WORD index,WORD prevI,WORD nextI,WORD *prevFreeI,
	SPRITETYPE spritetype,SPRITESTATS *spritestats,
	SV6_SPRITESTRUCT *cursprite,
	SV6_SPRITESTRUCTARRAY *sprites
)
{
	WORD nextOnTileI,stringIndex;

	static char nullString[32]="INIT";
	if(nullString[0]=='I')
		memset(nullString,0,sizeof(nullString));
		
	if (spritestats->statsB[SPR_COUNT][spritetype]>0)
	{			
		--spritestats->statsB[SPR_COUNT][spritetype];
		++spritestats->statsA.availSprites;
		//if(spritestats->statsA.nextFreeSprite==RCT2_WORD_EMPTY)
		//	spritestats->statsA.nextFreeSprite=index;
		spritestats->statsB[SPR_FIRSTINDEX][spritetype]=nextI;

		nextOnTileI=(*sprites)[index].nextOnThisTile;

		if(((*sprites)[index].textStringIndex&0xF000)==0x8000) // custom string index
		{
			stringIndex=(*sprites)[index].textStringIndex&0x3FF;
			#if 0
			SetRCT2NameString(stringIndex,(BYTE*)(nullString));
			#endif
		}

		#ifdef TESTNEW
			memset(&((*sprites)[index]),0,sizeof(SV6_SPRITESTRUCT));
		#endif // TESTNEW
		(*sprites)[index].spriteID=SPR_ID_FREE;
		(*sprites)[index].typeStatsOffset=SPR_FREE<<1;
		(*sprites)[index].nextOnThisTile=nextOnTileI;
		(*sprites)[index].nextInClass=RCT2_WORD_EMPTY;
		(*sprites)[index].prevInClass=RCT2_WORD_EMPTY;
		(*sprites)[index].spriteIndex=index;
	}

	return true;
}

typedef BYTE WATCHARRAY[1000][0X100];

union
{
	BYTE byteData[4];
	WORD wordData[2];
	DWORD dwordData[1];
}
SpriteFunc_Data;

#define PPIU_shirtColor SpriteFunc_Data.byteData[0]
#define PPIU_pantsColor SpriteFunc_Data.byteData[1]
#define PPIU_overridePurchases SpriteFunc_Data.byteData[2]

int 
SV6_FILE
::
SpriteFunc(SPRITEFUNCCLASS fclass,SPRITEFUNCID func)
{
	
	//SV6_SPRITESTRUCT sprite
	#define cursprite ((*spriteBlock)[index])
	SV6_SPRITESTRUCTARRAY *spritePtrBase,*spriteBlock;

	SPRITESTATS spritestats;
	WORD index,lastindex,prevI,nextI,nextFreeI,prevFreeI;

	WATCHARRAY *watcharray;

	RCT2_RIDESTRUCT rideOn,
		*rideArray
		=&this->fileDataA.parkData.rides[0];

	WORD newAttendance;

	memcpy
	(	&spritestats
		,
		&this->fileDataA.parkData.spriteStats
		,
		sizeof(SPRITESTATS)
	);

	spritePtrBase=&this->fileDataA.parkData.sprites;

	index=0;

	switch(fclass)
	{
	case SF_GUEST:
	case SF_STAFF:
	case SF_TRASH:
	case SF_FLOAT:

		spriteBlock
			=
			(SV6_SPRITESTRUCTARRAY*)
			(&this->fileDataA.parkData.sprites);
		watcharray=(WATCHARRAY*)(spriteBlock);

		#ifdef RCT2_FREEZE
		//	SuspendRCT2();
		#endif // RCT2_FREEZE

		memcpy
		(	
			spriteBlock
			,
			spritePtrBase
			,
			sizeof(*spriteBlock)
		);

		memcpy
		(	
			&spritestats
			,
			&this->fileDataA.parkData.sprites
			,
			sizeof(SPRITESTATS)
		);

		prevFreeI=GetLastFreeSprite(spriteBlock,spritestats.statsA.nextFreeSprite);

		switch(fclass)
		{
		case SF_GUEST:
			
			if(
				(index=spritestats.statsA.firstPerson)==RCT2_WORD_EMPTY
				||(spritestats.statsA.peopleCount==0)
			) break;
			

			switch(func)
			{	
			case GUEST_REMOVEALL:
				//newAttendance=GetCurrentAttendance();
				break;				
			}

			do
			{
				prevI=cursprite.prevInClass;
				nextI=cursprite.nextInClass;
				nextFreeI=spritestats.statsA.nextFreeSprite;

				if(cursprite.persontype==SPR_PT_GUEST)
				{
					switch(func)
					{	
					case GUEST_ADD100CASH:
						cursprite.cashInPocket+=100*DIMESINDOLLAR;
						break;
					case GUEST_ADD1000CASH:
						cursprite.cashInPocket+=1000*DIMESINDOLLAR;
						break;
					case GUEST_GIVEFOOD:						
						cursprite.nothunger=0xff;
						//cursprite.items=ITEM_BURGER; 
						break;
					case GUEST_GIVEDRINKS:
						cursprite.notthirst=0xff;
						//cursprite.items=ITEM_DRINK; 
						break;
					case GUEST_HEALNAUSEA:
						cursprite.nausea=cursprite.targetnausea=0;
						break;
					case GUEST_VITALIZE:
						cursprite.energy=cursprite.targetenergy=0xff;
						break;
					case GUEST_GOTORESTROOM:
						cursprite.restroomNeed=0;
						break;
					case GUEST_MAKEHAPPY:
						cursprite.happiness=cursprite.targethappiness=0xff;
						break;
					case GUEST_PACIFYVANDALS:
						cursprite.vandalFlag=0;
						break;
					case GUEST_GIVEBALLOONS:
						cursprite.items|=ITEM_BALLOON;
						cursprite.balloonColor=itemcolor;
						itemcolor=(itemcolor+1)&0x1f;
						break;
					case GUEST_HANDOUTMAPS:
						cursprite.items|=ITEM_MAP;
						break;
					case GUEST_GIVEUMBRELLAS:
						cursprite.items|=ITEM_UMBRELLA;
						cursprite.umbrellaColor=itemcolor;
						itemcolor=(itemcolor+1)&0x1f;				
						break;
					case GUEST_MAKETAME:
						cursprite.intensityPref&=!INTENSITY_LOWMASK;
						break;
					case GUEST_MAKEWILD:
						cursprite.intensityPref|=INTENSITY_HIGHMASK;
						break;
					case GUEST_PUTINUNIFORM:
						if
						(	PPIU_overridePurchases
							||(!(cursprite.items&ITEM_TSHIRT))	
						)	
						{	cursprite.byte30.shirtcolor=PPIU_shirtColor;	}
						cursprite.byte31.pantcolor=PPIU_pantsColor;
						break;
					case GUEST_REMOVEALL:
						switch(cursprite.curstate)
						{
						case 3:	//	on ____* 
						case 4:	//on ____* 
						case 7:	//on _____*
						case 17: //at _____*,
							//RCT2_RIDESTRUCT rideOn,*rideArray=RCT2_ADDR_RIDES;
							memcpy
							(
								&rideOn,
								&(rideArray[cursprite.union52.personStruct.unkCurRideOnI_A]),
								sizeof(rideOn)
							);
							if(rideOn.trackType!=0x43) //mini golf
								goto RemoveGuestLine;
							else 
								goto DontRemoveGuestLine;
						default:
							goto RemoveGuestLine;
						}
						RemoveGuestLine:
							if((cursprite.guestAdmissionStatus&GAS_OUTOFPARK)==GAS_INPARK)
								--newAttendance;
							RemoveSprite
							(	index,prevI,nextI,&prevFreeI,
								SPR_PERSON,&spritestats,&cursprite,
								spriteBlock
							);
							
						DontRemoveGuestLine:
							break;
					case GUEST_FREEZE:
						cursprite.energy=cursprite.targetenergy=0x0;
						break;

					}

				}

				index=nextI;
			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case GUEST_REMOVEALL:
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,(short*)&(spritestats.statsA.nextFreeSprite));
				SortSpriteChain(spriteBlock,SPR_ID_PERSON,(short*)&(spritestats.statsA.firstPerson));
				EmptyRidesOfGuests(&spritestats,&(*spriteBlock)[0]);
				//SetCurrentAttendance(newAttendance);
				break;
			}
			break;
			
		case SF_STAFF:

			if(
				(index=spritestats.statsA.firstPerson)==RCT2_WORD_EMPTY
				||(spritestats.statsA.peopleCount==0)
			) break;

			do
			{
				prevI=cursprite.prevInClass;
				nextI=cursprite.nextInClass;
				nextFreeI=spritestats.statsA.nextFreeSprite;

				if(cursprite.persontype==SPR_PT_STAFF)
				{
					switch(func)
					{	
					case STAFF_MAKEFAST:
						cursprite.energy=cursprite.targetenergy=0xff;
						cursprite.restroomNeed=0xff;
						break;
					
					case STAFF_MAKENORMAL:
						cursprite.energy=cursprite.targetenergy=0x80;
						cursprite.restroomNeed=0x80;
						break;

					case STAFF_MAKESLOW:
						cursprite.energy=cursprite.targetenergy=0x20;
						cursprite.restroomNeed=0x20;
						break;

					case STAFF_MAKEFROZEN:
						cursprite.energy=cursprite.targetenergy=0x00;
						cursprite.restroomNeed=0x00;
						break;

					case STAFF_REMOVEALL:				
						RemoveSprite
						(	index,prevI,nextI,&prevFreeI,
							SPR_PERSON,&spritestats,&cursprite,
							spriteBlock
						);
						break;
					};
				}

				index=nextI;
			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case STAFF_REMOVEALL:
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,(short*)&(spritestats.statsA.nextFreeSprite));
				break;
			}
			break;

		case SF_TRASH:

			if
			(	((index=spritestats.statsA.firstJunk)==RCT2_WORD_EMPTY)
				||(spritestats.statsA.junkCount==0)
			) break;

			lastindex=RCT2_WORD_EMPTY;

			do
			{
				prevI=cursprite.prevInClass;
				nextI=cursprite.nextInClass;
				nextFreeI=spritestats.statsA.nextFreeSprite;

				switch(func)		
				{
				case TRASH_REMOVEALL:			
					RemoveSprite
					(	index,prevI,nextI,&prevFreeI,
						SPR_JUNK,&spritestats,&cursprite,
						spriteBlock
					);
					break;

				}

				index=nextI;

			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case TRASH_REMOVEALL:
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,(short*)&(spritestats.statsA.nextFreeSprite));				
				break;
			}
			break;

		case SF_FLOAT:
			if
			(	((index=spritestats.statsA.firstFloat)==RCT2_WORD_EMPTY)
				||(spritestats.statsA.floatingCount==0)
			) break;

			lastindex=RCT2_WORD_EMPTY;

			do
			{
				prevI=cursprite.prevInClass;
				nextI=cursprite.nextInClass;
				nextFreeI=spritestats.statsA.nextFreeSprite;

				switch(func)		
				{
				case FLOAT_REMOVEALL:			
					RemoveSprite
					(	index,prevI,nextI,&prevFreeI,
						SPR_FLOAT,&spritestats,&cursprite,
						spriteBlock
					);
					break;

				}

				index=nextI;

			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case FLOAT_REMOVEALL:
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,(short*)&(spritestats.statsA.nextFreeSprite));
				break;
			}
			break;
	
		} //func

		memcpy
		(	&this->fileDataA.parkData.sprites,
			spriteBlock,sizeof(*spriteBlock)
		);

		memcpy
		(	
			&this->fileDataA.parkData.spriteStats,
			&spritestats,
			sizeof(SPRITESTATS)
		);

		#ifdef RCT2_FREEZE
			ResumeRCT2();
		#endif // RCT2_FREEZE

		free(spriteBlock);
		return TRUE;

	default:
		free(spriteBlock);
		return FALSE;	
	}
};

int
SV6_FILE
::
 PacifyVandals()
{
	return SpriteFunc(SF_GUEST, GUEST_PACIFYVANDALS);
}

int
SV6_FILE
::
 MakeGuestsHappy()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKEHAPPY);
}

int
SV6_FILE
::
 HealNausea()
{
	return SpriteFunc(SF_GUEST,GUEST_HEALNAUSEA);
}

int
SV6_FILE
::
 GiveGuestsBurgers()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEFOOD);
}

int
SV6_FILE
::
 GiveGuestDrinks()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEDRINKS);
}

int
SV6_FILE
::
 HelpGuestsFindRestrooms()
{
	return SpriteFunc(SF_GUEST,GUEST_GOTORESTROOM);
}

int
SV6_FILE
::
 VitalizeGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_VITALIZE);
}

int
SV6_FILE
::
 GiveGuestsBalloons()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEBALLOONS);
}

int
SV6_FILE
::
 GiveGuestsUmbrellas()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEUMBRELLAS);
}

int
SV6_FILE
::
 HandOutParkMaps()
{
	return SpriteFunc(SF_GUEST,GUEST_HANDOUTMAPS);
}

int 
SV6_FILE
::
WildGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKEWILD);
}

int 
SV6_FILE
::
TameGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKETAME);
}

int 
SV6_FILE
::
GiveAllGuests100Cash()
{
	return SpriteFunc(SF_GUEST,GUEST_ADD100CASH);
}

int 
SV6_FILE
::
GiveAllGuests1000Cash()
{
	return SpriteFunc(SF_GUEST,GUEST_ADD1000CASH);
}

int
SV6_FILE
::
PutPeepsInUniform
(	WORD shirtColor,WORD pantsColor,
	WORD overridePurchases
)
{
	PPIU_shirtColor=shirtColor;
	PPIU_pantsColor=pantsColor;
	PPIU_overridePurchases=overridePurchases;
	return SpriteFunc(SF_GUEST,GUEST_PUTINUNIFORM);	
}

int
SV6_FILE
::
AllAroundGuests()
{
	int retval=TRUE;
	if(!TameGuests())retval=FALSE;
	if(!WildGuests())retval=FALSE;
	if(!MakeGuestsHappy())retval=FALSE;
	if(!VitalizeGuests())retval=FALSE;
	if(!HelpGuestsFindRestrooms())retval=FALSE;
	if(!GiveGuestDrinks())retval=FALSE;
	if(!GiveGuestsBurgers())retval=FALSE;
	if(!PacifyVandals())retval=FALSE;
	//	if(!())retval=FALSE;
	return retval;
}

int
SV6_FILE
::
RemoveGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_REMOVEALL);
}

int
SV6_FILE
::
FreezeGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_FREEZE);
}

int
SV6_FILE
::
FastStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKEFAST);
}

int
SV6_FILE
::
FreezeStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKEFROZEN);
}

int
SV6_FILE
::
NormalStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKENORMAL);
}

int
SV6_FILE
::
SlowStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKESLOW);
}

int
SV6_FILE
::
FireStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_REMOVEALL);
}

int
SV6_FILE
::
CleanPaths()
{
	return SpriteFunc(SF_TRASH,TRASH_REMOVEALL);
}

int
SV6_FILE
::
RemoveFloatingObjects()
{
	return SpriteFunc(SF_FLOAT,FLOAT_REMOVEALL);
}
//==============================================

int
SV6_FILE
::
ResetGuestNumbers()
{
	long newNextGuestNumber=1;
	char *ptr=(char*)&(this->fileDataA.parkData.nextGuestNumber);

	this->fileDataA.parkData.nextGuestNumber
		=newNextGuestNumber;

	return true;
}

