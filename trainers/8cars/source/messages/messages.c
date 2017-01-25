//messages.h

#include <string.h>
#include <malloc.h>
#include "messages.h"
#include "../rct2.h"
#include "../process\process.h"
#include "../8cars.h"
#include "../resource.h"

int WriteRct2Message
(	char *msgString,short color,
	short icon,short month,short day
)			
{	MESSAGESTRUCT message;

	if(FindWindow(NULL,RCT2_TITLE)==NULL) return FALSE;

	ShiftOutMessages();

	memset(&message,0,MESSAGESTRUCTSIZE);
	message.lettersDisplayed=0;
	message.icon=icon;
	message.month=month;
	message.day=day;
	message.color=color;
	strncpy(&message.text,msgString,sizeof(message.text));
	
	WinWrite
	(	mainWindow,
		RCT2_TITLE,
		RCT2_ADDR_MESSAGES,
		&message,sizeof(message)
	);
}


int ClearAllMessages()
{	int i;
	MESSAGESTRUCT message,*messageptr;
	memset(&message,0,sizeof(message));
	messageptr=RCT2_ADDR_MESSAGES;
	for(i=0;i<NUMMESSAGES;i++)
	{	WinWrite
		(	mainWindow,RCT2_TITLE,messageptr,
			&message,sizeof(message)
		);
		++messageptr;
	}
}

int ShiftOutMessages()
{	int i;
	short msgblank=FALSE;
	MESSAGESTRUCT curmessage,*messageptr;

	MESSAGESTRUCTARRAY *messagebuff;

	messagebuff=malloc(NUMMESSAGES*MESSAGESTRUCTSIZE);
	messageptr=RCT2_ADDR_MESSAGES;

	WinRead(mainWindow,RCT2_TITLE,messagebuff,messageptr,NUMMESSAGES*MESSAGESTRUCTSIZE);
	
	memcpy(&curmessage,&(*messagebuff)[0],MESSAGESTRUCTSIZE);
	if(curmessage.icon!=RCT2_MSGICON_HIDE)
	{
		memset(&(*messagebuff)[0],0,MESSAGESTRUCTSIZE);
		
		for(i=11;(i<(NUMMESSAGES-1))&&(!msgblank);i++)
		{	if(msgblank=(*messagebuff)[i].icon==RCT2_MSGICON_HIDE)
			{	memcpy(&(*messagebuff)[i],&curmessage,MESSAGESTRUCTSIZE);
				goto exitfor;
			}
		}
		exitfor:

		if(i>=NUMMESSAGES-1)
		{	i=NUMMESSAGES-1;
			memcpy(&(*messagebuff)[11],&(*messagebuff)[12],(NUMMESSAGES-12)*MESSAGESTRUCTSIZE);
			memcpy(&(*messagebuff)[i],&curmessage,MESSAGESTRUCTSIZE);
		}
	}

	WinWrite(mainWindow,RCT2_TITLE,messageptr,messagebuff,NUMMESSAGES*MESSAGESTRUCTSIZE);
	
	free(messagebuff);
}


	
//WriteRct2Message("",WriteRct2Message("",RCT2_MSGCOLOR_WHITE,0,0);

extern int cmdmsg(char* c)
{	
	WriteRct2Message(c,RCT2_MSGCOLOR_PURPLE,RCT2_MSGICON_GRAPH,0,1);
}

int CommandMessage(unsigned short cmd)
{
	switch(cmd)
	{
	case ID_PARK_OPEN:         	
		cmdmsg("Park open for business");
		break;
	case ID_PARK_CLOSE:                  
		cmdmsg("Park closed");
		break;
	case ID_PARK_VANDALIZEPARK:
		cmdmsg("Someone must not like your park");
		break;
	case ID_PARK_INVERTLANDOWNERSHIP:
	case ID_PARK_INVERTLANDOWNERSHIP_INGORERIGHTSFORSALE:
	case ID_PARK_INVERTLANDOWNERSHIP_INCLUDERIGHTSFORSALE:
		cmdmsg("Owned is now unowned, and vice versa");
		break;
	case ID_PARK_SETUNOWNEDTORIGHTS:
		cmdmsg("Construction rights for all unowned land has been acquired");
		break;
	case ID_PARK_OWNALLLAND:
		cmdmsg("All unpathed, unowned land is now yours");
		break;
	case ID_PARK_BORDERFENCE_RESTORE:
		cmdmsg("Park border restored");
		break;
	case ID_PARK_DEOWNBORDERLAND:
		cmdmsg("Border de-owned");
		break;
	case ID_PARK_BORDERFENCE_REMOVE:
		cmdmsg("Park border removed");
		break;
	case ID_PARK_ADDCUSTOMMESSAGE:
		break;
	case ID_PARK_CLEARALLMESSAGES:
		break;
	case ID_PARK_INCREASETIME_1DAY:
	case ID_PARK_INCREASETIME_1MONTH:
	case ID_PARK_INCREASETIME_1YEAR:
		cmdmsg("Time warp forward");
		break;
	case ID_PARK_DECREASETIME_1DAY:
	case ID_PARK_DECREASETIME_1MONTH:
	case ID_PARK_DECREASETIME_1YEAR:
		cmdmsg("Time warp backward");
		break;

	case ID_PARK_RESETDATE:
		cmdmsg("Date reset to March 1, Year 1");
		break;
	case ID_PARK_CHANGEGUESTENTRYPOINTS:
		cmdmsg("Guests now enter at the specified spots");
		break;
	case ID_PARK_QUIT:		
/*


*/		
		break;
	case ID_MONEY_USEMONEY:
		cmdmsg("Using money");
		break;
	case ID_MONEY_DONTUSEMONEY:
		cmdmsg("Not using money");
		break;
	case ID_MONEY_ADDCASH_CUSTOM:
		cmdmsg("Money changed by the custom amount");
		break;	
	case ID_MONEY_SUBTRACT5000000CASH:
	case ID_MONEY_SUBTRACT500000CASH:
	case ID_MONEY_SUBTRACT5000CASH:
	case ID_MONEY_SUBTRACT50000CASH:
		cmdmsg("Money decreased");
		break;	
	case ID_MONEY_ADD5000000CASH:
	case ID_MONEY_ADD5000CASH:	
	case ID_MONEY_ADD50000CASH:	
	case ID_MONEY_ADD500000CASH:
		cmdmsg("Money increased");		
		break;

	case ID_WEATHER_MAKESUNNY:         
		cmdmsg("It's nice and sunny");
		break;
	case ID_WEATHER_STARTHEAVYRAIN:
		cmdmsg("Get the umbrellas out");
		break;
	case ID_WEATHER_STARTTHUNDERSTORM:
		cmdmsg("Don't fly any kites!");
		break;
	case ID_WEATHER_STARTSHOWER:
		cmdmsg("It's about time this park took a shower!");
		break;
	case ID_WEATHER_MAKECOLD:
		cmdmsg("It's getting a little chilly");
		break;
	case ID_WEATHER_MAKEFREEZING:        
		cmdmsg("Icicles can be seen hanging from your rides");
		break;
	case ID_WEATHER_MAKEHOT:
		cmdmsg("Break out the UV-40!");
		break;
	case ID_WEATHER_FREEZEWEATHER:
		cmdmsg("Climate-control initiated");
		break;

	case ID_LANDSCAPE_LOADTERRAINBMP:
		cmdmsg("Terrain bitmap loaded (hopefully)");
		break;
	case ID_LANDSCAPE_SAVETERRAINBMP:
		cmdmsg("Terrain bitmap saved (hopefully)");
		break;
	case ID_LANDSCAPE_ADJUSTLANDMOVERSIZE:
		cmdmsg("Land mover adjusted");
		break;
	case ID_LANDSCAPE_ACTIVATEMOUNTAINTOOL:
		cmdmsg("Mountain tool activated");
		break;
	case ID_LANDSCAPE_CAPLANDATMAXHEIGHT:
		cmdmsg("Land capped at maximum editing height");
		break;

	case ID_STAFF_ADVERTISING_PROMOTEGENTLERIDES:
		cmdmsg("Guests will now ride gentler rides");
		break;
	case ID_STAFF_ADVERTISING_PROMOTEINTENSERIDES:
		cmdmsg("Guests will now ride more intense rides");
		break;
	case ID_STAFF_ADVERTISING_PROMOTEALLRIDES:
		cmdmsg("Guests will now ride any ride (within reason, of course)");
		break;
	case ID_STAFF_BANKER_GIVEALLGUESTS100CASH:
	case ID_STAFF_BANKER_GIVEALLGUESTS1000CASH:
		cmdmsg("Guests' wallets are a little heavier");
		break;
	case ID_STAFF_HANDYMAN_MOWGRASS:
	case ID_STAFF_HANDYMAN_MOWGRASS_PLAIN:
		cmdmsg("Grass mowed");
		break;
	case ID_STAFF_HANDYMAN_WATERGARDENS:
		cmdmsg("Gardens watered");
		break;			
	case ID_STAFF_HANDYMAN_EMPTYTRASH:
		//cmdmsg("");
		break;
	case ID_STAFF_HANDYMAN_CLEANPATHS:
		cmdmsg("Paths are spotless");
		break;
	case ID_STAFF_MECHANIC_REPAIRRIDES:
		//cmdmsg("");
		break;
	case ID_STAFF_MECHANIC_RENEWRIDES:
		cmdmsg("Rides are brand new");
		break;
	case ID_STAFF_MECHANIC_MAKERIDESRELIABLE:
		cmdmsg("Rides are very reliable");
		break;
	case ID_STAFF_SECURITY_PACIFYVANDALS:
		cmdmsg("Good job guards, you need a raise...............errm, perhaps not");
		break;
	case ID_STAFF_HANDYMAN_FIXVANDALISM:
		cmdmsg("New benches and lights installed");
		break;
	case ID_STAFF_ENTERTAINER_MAKEGUESTSHAPPY:
		cmdmsg("The guests glistening white teeth are blinding each other (Oh, Happy guests)");
		break;
	case ID_STAFF_ENTERTAINER_GIVEGUESTSBALLOONS:
		cmdmsg("Free baloons!");
		break;
	case ID_STAFF_CATERER_GIVEGUESTSDRINKS:
		cmdmsg("Thirst quenched");
		break;
	case ID_STAFF_CATERER_GIVEGUESTSBURGERS:
		cmdmsg("Hunger satiated");
		break;
	case ID_STAFF_FIRSTAID_HEALNAUSEA:
		cmdmsg("I feel very ... oh, healthy, yeah ");
		break;
	case ID_STAFF_FIRSTAID_VITALIZEGUESTS:
		cmdmsg("Guests are full of energy");
		break;
	case ID_STAFF_PARKGUIDE_HELPGUESTSFINDRESTROOMS:
		cmdmsg("Guests are relieved");
		break;
	case ID_STAFF_PARKGUIDE_HANDOUTPARKMAPS:
		cmdmsg("Free maps!");
		break;
	case ID_STAFF_PARKGUIDE_GIVEGUESTSUMBRELLAS:
		cmdmsg("Free umbrellas!");
		break;
	case ID_STAFF_RESEARCHER_COMPLETERESEARCH:
		break;

	case ID_STAFF_STAFFSPEED_FAST:
		cmdmsg("Watch those little guys move!");
		break;
	case ID_STAFF_STAFFSPEED_NORMAL:
		cmdmsg("Staff back to normal");
		break;
	case ID_STAFF_STAFFSPEED_SLOW:
		cmdmsg("Inspections -- every year");
		break;
	case ID_STAFF_STAFFSPEED_FREEZE:
		cmdmsg("Staff is in suspended animation");
		break;

	case ID_RIDES_EDITRIDESTATS:
		cmdmsg("Ride(s) edited");
		break;
	case ID_RIDES_10MINUTEINSPECTIONS:
		cmdmsg("All ride's inspection rates are set to every 10 minutes");
		break;
	case ID_RIDES_UNIFORMITEMPRICING:
		cmdmsg("Respective items are the same price throughout the park");
		break;
	case ID_RIDES_ANYHEIGHTCONSTRUCTION:
		cmdmsg("Now you can build 500-foot-high rides!");
		break;
	case ID_RIDES_10FOOTSHOPS:
		cmdmsg("Default clearance for shops is now 10 feet");
		break;
	case ID_RIDES_8CARSPERTRAIN:
		cmdmsg("Longer trains");
		break;
	case ID_RIDES_ULTRAEXCITINGRIDES: 
		cmdmsg("All rides will now have higher excitement ratings");
		break;
	case ID_RIDES_ULTRAINTENSERIDES:
		cmdmsg("All rides will now have higher intensity ratings");
		break;
	case ID_RIDES_ULTRANAUSEATINGRIDES:
		cmdmsg("All rides will now have higher nausea ratings");
		break;

	case ID_MISC_REMOVEFLOATINGOBJECTS:
		cmdmsg("Ducks and floating text have vanished");
		break;
	case ID_MISC_ZEROALLCLEARANCES:
		cmdmsg("You can now build through everything");
		break;
	case ID_MISC_RESTORECLEARANCES:
		cmdmsg("Clearances restored");
		break;
	case ID_MISC_SORTMAPELEMENTSINTERNALLY:
		cmdmsg("Don't worry, techie stuff just happened--supports should now show properly");
		break;
	case ID_MISC_MAPOBJECTMANIPULATION:
		cmdmsg("The map objects are feeling manipulated");
		break;

	case ID_GUESTS_ALLAROUNDGUESTS:
		cmdmsg("All around guests");
		break;
	case ID_GUESTS_REMOVEALLGUESTS:
		cmdmsg("All guests removed (besides golfers)");
		break;
	case ID_GUESTS_TRAMS_SMALLTRAM:
	case ID_GUESTS_TRAMS_MEDIUMTRAM:
	case ID_GUESTS_TRAMS_LARGETRAM:
	case ID_GUESTS_TRAMS_HUGETRAM:
		cmdmsg("Tram has arrived");
		break;
	case ID_GUESTS_RESETGUESTNUMBERS:
		cmdmsg("The next guest will be #1");
		break;
	case ID_GUESTS_FREEZEGUESTMOVEMENT:
		cmdmsg("Guests can't move!");
		break;
	case ID_GUESTS_UNIFORMPEEPS:
		cmdmsg("Now guests look even more the same");
		break;

	case ID_DEBUG_ELIMINATEDUPLICATESUFACEDATA:
		cmdmsg("Duplicate terrain glitch eliminated (yeah, whatever you say)");
		break;

	case ID_HELP_CONTENTS:
		break;
	case ID_HELP_ABOUT:
		break;
/*
	case ID_STAFF_HANDYMAN_EMPTYTRASH    40016
	case ID_STAFF_HANDYMAN_CLEANPATHS    40017
	case ID_STAFF_MECHANIC_FIXRIDES      40019
	case ID_STAFF_HANDYMAN_FIXVANDALISM  40023
	case ID_STAFF_MECHANIC_REPAIRRIDES   40031
	case ID_STAFF_RESEARCHER_COMPLETERESEARCH 40043
	case ID_WEATHER_CYCLEWEATHER         40057
	case ID_LANDSCAPE_GENERATERANDOMTERRAIN 40070
	case ID_GUESTS_EDITGUESTSTATS        40075
	case ID_GUESTS_TRAMS_LARGETRAM       40077
	case ID_GUESTS_TRAMS_SMALLTRAM       40078
	case ID_GUESTS_TRAMS_MEDIUMTRAM      40079
	case ID_GUESTS_TRAMS_HUGETRAM        40080
	case ID_GUESTS_REMOVEALLGUESTS       40081

	case ID_MISC_REMOVEFLOATINGOBJECTS   40083
	case ID_STAFF_FIREALL                40090
	case ID_PARK_FIXPARKSTATUS           40098
*/

/*
	case ID_LANDSCAPE_SAVETERRAINBMP:
	case ID_DEBUG_ELIMINATEDUPLICATESUFACEDATA:
	case ID_MONEY_ADDCASH_CUSTOM:
	case ID_MONEY_ADD5000000CASH:
	case ID_MONEY_SUBTRACT5000000CASH:
	case ID_PARK_VANDALIZEPARK:
*/
	default:
		break;

	}
}

