//spritefuncs.h

#ifndef _SPRITEFUNCS_
#define _SPRITEFUNCS_

#include "..\rct2.h"

// header 

int GiveAllGuests100Cash();
int GiveAllGuests1000Cash();
int PacifyVandals();
int MakeGuestsHappy();
int HealNausea();
int GiveGuestsBurgers();
int GiveGuestDrinks();
int HelpGuestsFindRestrooms();
int VitalizeGuests();
int GiveGuestsBalloons();
int HandOutParkMaps();
int GiveGuestsUmbrellas();
int AllAroundGuests();
int WildGuests();
int TameGuests();
int RemoveGuests();
int FreezeGuests();
int PutPeepsInUniform
(	WORD shirtColor,WORD pantsColor,
	WORD overridePurchases
);

int FireStaff();

int FastStaff();
int NormalStaff();
int SlowStaff();
int FreezeStaff();


int CleanPaths();

int RemoveFloatingObjects();

typedef enum 
{
	GUEST_ADD100CASH,
	GUEST_ADD1000CASH,
	GUEST_HEALNAUSEA,
	GUEST_MAKEHAPPY,
	GUEST_GIVEFOOD,
	GUEST_GIVEDRINKS,
	GUEST_PACIFYVANDALS,
	GUEST_GOTORESTROOM,
	GUEST_VITALIZE,
	GUEST_GIVEBALLOONS,
	GUEST_HANDOUTMAPS,
	GUEST_GIVEUMBRELLAS,
	GUEST_MAKETAME,
	GUEST_MAKEWILD,
	GUEST_REMOVEALL,
	GUEST_FREEZE,
	GUEST_PUTINUNIFORM,

	STAFF_REMOVEALL,
	STAFF_MAKEFAST,
	STAFF_MAKENORMAL,
	STAFF_MAKESLOW,
	STAFF_MAKEFROZEN,

	TRASH_REMOVEALL,

	FLOAT_REMOVEALL

} SPRITEFUNCID;

typedef enum
{	SF_GUEST,
	SF_STAFF,
	SF_TRASH,
	SF_FLOAT
} SPRITEFUNCCLASS;

int ResetGuestNumbers();

//header 

#endif //_SPRITEFUNCS_



