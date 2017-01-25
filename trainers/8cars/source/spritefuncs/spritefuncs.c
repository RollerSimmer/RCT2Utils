/*
#include <windows.h>
#include <malloc.h>
#include "spritefuncs.h"
#include "..\rct2.h"
#include "process.h"
#include "../8cars.h"

char itemcolor=0;

WORD GetLastFreeSprite(SPRITESTRUCTARRAY *spriteBlock,WORD firstfree)
{
	WORD index,prevI;
	#define cursprite ((*spriteBlock)[index])
	{	
		index=prevI=firstfree;

		while (index!=RCT2_WORD_EMPTY)
		{	prevI=index;
			index=cursprite.nextInClass;
		}
		
		return prevI;
	}
	#undef cursprite
}

SortSpriteChain(SPRITESTRUCTARRAY *spriteBlock,short SpriteID,short *firstSpriteIndex)
{
	int i,prevI,nextI;

	#define cursprite ((*spriteBlock)[i])

	prevI=RCT2_WORD_EMPTY;

	for(i=0;i<NUMSPRITES;i++)
		if(cursprite.spriteID==(char)SpriteID)
		{	
			cursprite.nextInClass=RCT2_WORD_EMPTY;
			if(prevI==RCT2_WORD_EMPTY)
				*firstSpriteIndex=i;
			else 
				(*spriteBlock)[prevI].nextInClass=i;				
			cursprite.prevInClass=prevI;
			prevI=i;
		}		

	#undef cursprite
}

int FreeSprite
(	SPRITESTRUCT *cursprite,WORD *prevFreeI,WORD index
)
{
	memset(cursprite,0,sizeof(SPRITESTRUCT));
	cursprite->spriteID=RCT2_BYTE_EMPTY;
	cursprite->prevInClass=*prevFreeI;
	cursprite->nextInClass=RCT2_WORD_EMPTY;
	*prevFreeI=index;
	cursprite->spriteIndex=index;
}
/*
typedef enum
{		SPR_FREE=0,SPR_VEHI,SPR_PERSON,
		SPR_FLOAT,SPR_JUNK,SPR_OVERSIZED
}
SPRITETYPE 
*/
/*
int RemoveSprite
(	WORD index,WORD prevI,WORD nextI,WORD *prevFreeI,
	SPRITETYPE spritetype,SPRITESTATS *spritestats,
	SPRITESTRUCT *cursprite
)
{
	if (spritestats->statsB[SPR_COUNT][spritetype])
	{			
		--spritestats->statsB[SPR_COUNT][spritetype];
		++spritestats->statsA.availSprites;
		if(spritestats->statsA.nextFreeSprite==RCT2_WORD_EMPTY)
			spritestats->statsA.nextFreeSprite=index;					
		spritestats->statsB[SPR_FIRSTINDEX][spritetype]=nextI;
		
		FreeSprite(cursprite,prevFreeI,index);
								
	}
}

int SpriteFunc(SPRITEFUNCCLASS fclass,SPRITEFUNCID func)
{
	//SPRITESTRUCT sprite;
	#define cursprite ((*spriteBlock)[index])
	SPRITESTRUCTARRAY *spritePtrBase,*spriteBlock;
	SPRITESTATS spritestats;
	WORD index,lastindex,prevI,nextI,nextFreeI,prevFreeI;

	if 
	(	!WinRead
		(	mainWindow,
			RCT2_TITLE,&spritestats,RCT2_ADDR_SPRITESTATS,
			sizeof(SPRITESTATS)
		)
	) return FALSE;

	spritePtrBase=RCT2_ADDR_SPRITES;
	index=0;

	switch(fclass)
	{
	case SF_GUEST:
	case SF_STAFF:
	case SF_TRASH:
	case SF_FLOAT:

		if((spriteBlock=malloc(sizeof(SPRITESTRUCTARRAY)))==NULL)
		{	MessageBox
			(	mainWindow,"Not enough memory (requires appx. 2.5 MB free space)","Message",
				MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND			
				|MB_ICONWARNING
			);
			return FALSE;
		}

		WinRead
		(	mainWindow,RCT2_TITLE,spriteBlock,
			spritePtrBase,sizeof(*spriteBlock)
		);

		prevFreeI=GetLastFreeSprite(spriteBlock,spritestats.statsA.nextFreeSprite);

		switch(fclass)
		{
		case SF_GUEST:
			
			if(
				(index=spritestats.statsA.firstPerson)==RCT2_WORD_EMPTY
				||(spritestats.statsA.peopleCount==0)
			) break;


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
					case GUEST_REMOVEALL:
						RemoveSprite
						(	index,prevI,nextI,&prevFreeI,
							SPR_PERSON,&spritestats,&cursprite
						);
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
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
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
							SPR_PERSON,&spritestats,&cursprite
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
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
				break;
			}
			break;

		case SF_TRASH:

			if
			(	((index=spritestats.statsA.firstJunk)==RCT2_WORD_EMPTY)
				||(spritestats.statsA.junkCount==0)
			) break;

			lastindex=RCT2_WORD_EMPTY;

			
			prevI=cursprite.prevInClass;
			nextI=cursprite.nextInClass;
			nextFreeI=spritestats.statsA.nextFreeSprite;

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
						SPR_JUNK,&spritestats,&cursprite
					);
					break;

				}

				index=nextI;

			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case TRASH_REMOVEALL:
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
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
						SPR_FLOAT,&spritestats,&cursprite
					);
					break;

				}

				index=nextI;

			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case FLOAT_REMOVEALL:
				SortSpriteChain(spriteBlock,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
				break;
			}
			break;
	
		} //func

		WinWrite
		(	mainWindow,RCT2_TITLE,RCT2_ADDR_SPRITES,
			spriteBlock,sizeof(*spriteBlock)
		);

		WinWrite
		(	mainWindow,
			RCT2_TITLE,RCT2_ADDR_SPRITESTATS,&spritestats,
			sizeof(SPRITESTATS)
		);

		free(spriteBlock);
		return TRUE;

	default:
		free(spriteBlock);
		return FALSE;	
	}
};

int PacifyVandals()
{
	return SpriteFunc(SF_GUEST, GUEST_PACIFYVANDALS);
}

int MakeGuestsHappy()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKEHAPPY);
}

int HealNausea()
{
	return SpriteFunc(SF_GUEST,GUEST_HEALNAUSEA);
}

int GiveGuestsBurgers()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEFOOD);
}

int GiveGuestDrinks()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEDRINKS);
}

int HelpGuestsFindRestrooms()
{
	return SpriteFunc(SF_GUEST,GUEST_GOTORESTROOM);
}

int VitalizeGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_VITALIZE);
}

int GiveGuestsBalloons()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEBALLOONS);
}

int GiveGuestsUmbrellas()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEUMBRELLAS);
}

int HandOutParkMaps()
{
	return SpriteFunc(SF_GUEST,GUEST_HANDOUTMAPS);
}

int WildGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKEWILD);
}

int TameGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKETAME);
}

int GiveAllGuests100Cash()
{
	return SpriteFunc(SF_GUEST,GUEST_ADD100CASH);
}

int GiveAllGuests1000Cash()
{
	return SpriteFunc(SF_GUEST,GUEST_ADD1000CASH);
}

int AllAroundGuests()
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

int RemoveGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_REMOVEALL);
}

int FreezeGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_FREEZE);
}

int FastStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKEFAST);
}

int FreezeStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKEFROZEN);
}

int NormalStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKENORMAL);
}

int SlowStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKESLOW);
}

int FireStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_REMOVEALL);
}

int CleanPaths()
{
	return SpriteFunc(SF_TRASH,TRASH_REMOVEALL);
}

int RemoveFloatingObjects()
{
	return SpriteFunc(SF_FLOAT,FLOAT_REMOVEALL);
}
//==============================================

int ResetGuestNumbers()
{
	long newNextGuestNumber=1;
	char *ptr=RCT2_ADDR_NEXTGUESTNUMBER;
	
	WinWrite
	(	mainWindow,RCT2_TITLE,ptr,
		&newNextGuestNumber,sizeof(newNextGuestNumber)
	);
}



*/
//H
//#undef RCT2_FREEZE
#define RCT2_FREEZE

#define TESTNEW

#include <windows.h>
#include <malloc.h>
#include "spritefuncs.h"
#include "..\rct2.h"
#include "process.h"
#include "../8cars.h"
#include "../ridefuncs/ridefuncs.h"
#include "../parkstatus/parkstatus.h"

char itemcolor=0;

WORD GetLastFreeSprite(SPRITESTRUCTARRAY *spriteBlock,WORD firstfree)
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
(	SPRITESTRUCTARRAY *spriteBlock,
	SPRITE_MAPXYINDEXES *mapXYChainIndexes,
	short SpriteID,short *firstSpriteIndex
)
{

	int i,x,y,prevI,nextI;
	WORD curIndex;

	prevI=RCT2_WORD_EMPTY;

	for(i=0;i<NUMSPRITES;i++)
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

SortHandymanTiles
(	SPRITESTRUCTARRAY *spriteBlock,
	SPRITE_MAPXYINDEXES *mapXYChainIndexes,
	short SpriteID,short *firstSpriteIndex
)
{

	WORD i,x,y,prevI,nextI,lastValidI;
	WORD curIndex,nextOnTile;

	#define cursprite ((*spriteBlock)[i])
	//Sort Handyman Tiles
	for (x=0;x<MAP_MAXTILES;x++)
	{	
		for (y=0;y<MAP_MAXTILES;y++)
		{
			lastValidI=RCT2_WORD_EMPTY;
			curIndex=(WORD)(*mapXYChainIndexes)[x][y];
			(*mapXYChainIndexes)[x][y]=RCT2_WORD_EMPTY;
			while(curIndex!=(WORD)RCT2_WORD_EMPTY)
			{
				nextOnTile=(*spriteBlock)[curIndex].nextOnThisTile;

				if((*spriteBlock)[curIndex].spriteID!=SPR_ID_FREE)  // valid sprite
				{
					if(lastValidI!=RCT2_WORD_EMPTY)
						(*spriteBlock)[lastValidI].nextOnThisTile=curIndex;
					else 
						(*mapXYChainIndexes)[x][y]=curIndex;
					lastValidI=curIndex;
				}
				else 
				{
					(*spriteBlock)[curIndex].nextOnThisTile=0;
				}

				/*
				if((*spriteBlock)[curIndex].spriteID==SPR_ID_PERSON)
					break;
				*/
			
				curIndex=nextOnTile;
			}

			if(lastValidI!=RCT2_WORD_EMPTY)
			{
				nextOnTile=(*spriteBlock)[lastValidI].nextOnThisTile;
				if(nextOnTile!=RCT2_WORD_EMPTY)
				{
					if((*spriteBlock)[nextOnTile].spriteID==SPR_ID_FREE) //
						(*spriteBlock)[lastValidI].nextOnThisTile=RCT2_WORD_EMPTY;
				}
			}
		} // for (y=0;y<MAP_MAXTILES;y++)
	}
	//	if((SpriteID==SPR_ID_JUNK)
	//			||((SpriteID==SPR_ID_PERSON)&&()))
	#undef cursprite

}

EmptyRidesOfGuests
(	SPRITESTATS *spritestats,
	SPRITESTRUCT *spriteBlock
)
{
	WORD index;
	RIDESTRUCT vehiOwner,*rideArray=RCT2_ADDR_RIDES;
	index=spritestats->statsA.firstVehicle;
	while(index!=RCT2_WORD_EMPTY)
	{
		WinRead
		(	mainWindow,RCT2_TITLE,&vehiOwner,
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
		WinRead
		(	mainWindow,RCT2_TITLE,&vehiOwner,
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

	_EmptyRidesOfGuests();
}

WORD GetPrevOnTile
(	WORD x,WORD y,WORD index,
	SPRITESTRUCTARRAY *sprites,
	SPRITE_MAPXYINDEXES *mapXYChainIndexes
)
{
	WORD 
		retV=RCT2_WORD_EMPTY,
		curIndex=(*mapXYChainIndexes)[x][y];
	if(index==curIndex)
		retV=RCT2_WORD_EMPTY;
	else 
	{
		while 
		(	((*sprites)[curIndex].nextOnThisTile!=index)
			&&((*sprites)[curIndex].nextOnThisTile!=RCT2_WORD_EMPTY)	
			&&(curIndex<NUMSPRITES)
			&&(curIndex!=(*sprites)[curIndex].nextOnThisTile)
		)
		{
			curIndex=(*sprites)[curIndex].nextOnThisTile;
			if((*sprites)[curIndex].nextOnThisTile==index)
				retV=curIndex;
		}
		if(curIndex>NUMSPRITES)
			curIndex++;curIndex--;
	}
	return retV;	
}

int RemoveSprite
(	WORD index,WORD prevI,WORD nextI,WORD *prevFreeI,
	SPRITETYPE spritetype,SPRITESTATS *spritestats,
	SPRITESTRUCT *cursprite,
	SPRITESTRUCTARRAY *sprites,
	SPRITE_MAPXYINDEXES *mapXYChainIndexes
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
			SetRCT2NameString(stringIndex,nullString);
		}

		#ifdef TESTNEW
			memset(&((*sprites)[index]),0,sizeof(SPRITESTRUCT));
		#endif // TESTNEW
		(*sprites)[index].spriteID=SPR_ID_FREE;
		(*sprites)[index].typeStatsOffset=SPR_FREE<<1;
		(*sprites)[index].nextOnThisTile=nextOnTileI;
		(*sprites)[index].nextInClass=RCT2_WORD_EMPTY;
		(*sprites)[index].prevInClass=RCT2_WORD_EMPTY;
		(*sprites)[index].spriteIndex=index;
	}
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

int SpriteFunc(SPRITEFUNCCLASS fclass,SPRITEFUNCID func)
{
	//SPRITESTRUCT sprite
	#define cursprite ((*spriteBlock)[index])
	SPRITESTRUCTARRAY *spritePtrBase,*spriteBlock;
	SPRITE_MAPXYINDEXES *mapXYChainIndexes,*mapXYChainIndexesPtrBase;

	SPRITESTATS spritestats;
	WORD index,lastindex,prevI,nextI,nextFreeI,prevFreeI;

	WATCHARRAY *watcharray;

	RIDESTRUCT rideOn,*rideArray=RCT2_ADDR_RIDES;

	WORD newAttendance;

	if 
	(	!WinRead
		(	mainWindow,
			RCT2_TITLE,&spritestats,RCT2_ADDR_SPRITESTATS,
			sizeof(SPRITESTATS)
		)
	) return FALSE;

	spritePtrBase=RCT2_ADDR_SPRITES;
	mapXYChainIndexesPtrBase=RCT2_ADDR_MAPXYSPRITECHAININDEXES;

	index=0;

	switch(fclass)
	{
	case SF_GUEST:
	case SF_STAFF:
	case SF_TRASH:
	case SF_FLOAT:

		if((spriteBlock=malloc(sizeof(SPRITESTRUCTARRAY)))==NULL)
		{	MessageBox
			(	mainWindow,"Not enough memory (requires appx. 2.5 MB free space)","Message",
				MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND			
				|MB_ICONWARNING
			);
			return FALSE;
		}
		watcharray=spriteBlock;

		if((mapXYChainIndexes=malloc(sizeof(SPRITE_MAPXYINDEXES)))==NULL)
		{	MessageBox
			(	mainWindow,"Not enough memory (requires appx. 32 KB free space)","Message",
				MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND		
				|MB_ICONWARNING
			);
			return FALSE;
		}
		#ifdef RCT2_FREEZE
			SuspendRCT2();
		#endif // RCT2_FREEZE

		WinRead
		(	mainWindow,RCT2_TITLE,spriteBlock,
			spritePtrBase,sizeof(*spriteBlock)
		);
		WinRead
		(	mainWindow,RCT2_TITLE,mapXYChainIndexes,
			mapXYChainIndexesPtrBase,sizeof(*mapXYChainIndexes)
		);

		WinRead
		(	mainWindow,
			RCT2_TITLE,&spritestats,RCT2_ADDR_SPRITESTATS,
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
				newAttendance=GetCurrentAttendance();
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
							//RIDESTRUCT rideOn,*rideArray=RCT2_ADDR_RIDES;
							WinRead
							(	mainWindow,RCT2_TITLE,&rideOn,
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
								spriteBlock,mapXYChainIndexes
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
				SortSpriteChain(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
				SortHandymanTiles(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
				SortSpriteChain(spriteBlock,mapXYChainIndexes,SPR_ID_PERSON,&(spritestats.statsA.firstPerson));
				EmptyRidesOfGuests(&spritestats,spriteBlock);
				SetCurrentAttendance(newAttendance);
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
							spriteBlock,mapXYChainIndexes
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
				SortSpriteChain(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
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
						spriteBlock,mapXYChainIndexes
					);
					break;

				}

				index=nextI;

			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case TRASH_REMOVEALL:
				SortSpriteChain(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));				
				SortHandymanTiles(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
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
						spriteBlock,mapXYChainIndexes
					);
					break;

				}

				index=nextI;

			}
			while (index!=RCT2_WORD_EMPTY);

			switch (func)
			{
			case FLOAT_REMOVEALL:
				SortSpriteChain(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));
				SortHandymanTiles(spriteBlock,mapXYChainIndexes,RCT2_BYTE_EMPTY,&(spritestats.statsA.nextFreeSprite));				
				break;
			}
			break;
	
		} //func

		WinWrite
		(	mainWindow,RCT2_TITLE,
			RCT2_ADDR_MAPXYSPRITECHAININDEXES,
			mapXYChainIndexes,sizeof(*mapXYChainIndexes)
		);
		WinWrite
		(	mainWindow,RCT2_TITLE,RCT2_ADDR_SPRITES,
			spriteBlock,sizeof(*spriteBlock)
		);

		WinWrite
		(	mainWindow,
			RCT2_TITLE,RCT2_ADDR_SPRITESTATS,&spritestats,
			sizeof(SPRITESTATS)
		);

		#ifdef RCT2_FREEZE
			ResumeRCT2();
		#endif // RCT2_FREEZE

		free(mapXYChainIndexes);
		free(spriteBlock);
		return TRUE;

	default:
		free(spriteBlock);
		return FALSE;	
	}
};

int PacifyVandals()
{
	return SpriteFunc(SF_GUEST, GUEST_PACIFYVANDALS);
}

int MakeGuestsHappy()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKEHAPPY);
}

int HealNausea()
{
	return SpriteFunc(SF_GUEST,GUEST_HEALNAUSEA);
}

int GiveGuestsBurgers()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEFOOD);
}

int GiveGuestDrinks()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEDRINKS);
}

int HelpGuestsFindRestrooms()
{
	return SpriteFunc(SF_GUEST,GUEST_GOTORESTROOM);
}

int VitalizeGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_VITALIZE);
}

int GiveGuestsBalloons()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEBALLOONS);
}

int GiveGuestsUmbrellas()
{
	return SpriteFunc(SF_GUEST,GUEST_GIVEUMBRELLAS);
}

int HandOutParkMaps()
{
	return SpriteFunc(SF_GUEST,GUEST_HANDOUTMAPS);
}

int WildGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKEWILD);
}

int TameGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_MAKETAME);
}

int GiveAllGuests100Cash()
{
	return SpriteFunc(SF_GUEST,GUEST_ADD100CASH);
}

int GiveAllGuests1000Cash()
{
	return SpriteFunc(SF_GUEST,GUEST_ADD1000CASH);
}

int PutPeepsInUniform
(	WORD shirtColor,WORD pantsColor,
	WORD overridePurchases
)
{
	PPIU_shirtColor=shirtColor;
	PPIU_pantsColor=pantsColor;
	PPIU_overridePurchases=overridePurchases;
	return SpriteFunc(SF_GUEST,GUEST_PUTINUNIFORM);	
}

int AllAroundGuests()
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

int RemoveGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_REMOVEALL);
}

int FreezeGuests()
{
	return SpriteFunc(SF_GUEST,GUEST_FREEZE);
}

int FastStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKEFAST);
}

int FreezeStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKEFROZEN);
}

int NormalStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKENORMAL);
}

int SlowStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_MAKESLOW);
}

int FireStaff()
{
	return SpriteFunc(SF_STAFF,STAFF_REMOVEALL);
}

int CleanPaths()
{
	return SpriteFunc(SF_TRASH,TRASH_REMOVEALL);
}

int RemoveFloatingObjects()
{
	return SpriteFunc(SF_FLOAT,FLOAT_REMOVEALL);
}
//==============================================

int ResetGuestNumbers()
{
	long newNextGuestNumber=1;
	char *ptr=RCT2_ADDR_NEXTGUESTNUMBER;
	
	WinWrite
	(	mainWindow,RCT2_TITLE,ptr,
		&newNextGuestNumber,sizeof(newNextGuestNumber)
	);
}



