#include "../8cars_windowName.h"
#include <windows.h>
#include <winver.h>
#include <COMMCTRL.H>
#include "8carsfunc.h"
#include "../resource.h"
#include "../rct2.h"
#include "../weather/weather.h"
#include "../dlg/ridedlg/ridedlg.h"
#include "../dlg/staffdlg/staffdlg.h"
#include "../dlg/mapobjmandlg/mapobjmandlg.H"
#include "../guests/guestfuncs.h"
#include "../dlg/peep color/peepColor.h"

char AboutString[512];

int  APIENTRY AboutBox(HWND hwnd);

HWND mainWindow,rct2Window;
HANDLE rct2Thread;
HMENU mainMenu;
HINSTANCE hinst; 
HACCEL haccel;
HHOOK rct2KeyboardHook;
DWORD rct2ThreadID;
UINT _8CarsTimer;

typedef enum{X,Y,Z,DIR}XYZCOORD;

char savepath[128];

char _8CARS_EXENAME[32]="8cars.exe";

#define _8CARSHELP_HTML	"\\8carshelp.HTML"
#define _8CARSHELP_TXT	"\\8carshelp.txt"

//#undef USE_ACCELERATOR
#define USE_ACCELERATOR
#undef TEST_PROCEDURE_CALL
//#define TEST_PROCEDURE_CALL

HHOOK rct2KeyboardHook;
char mainWindowName[64];
HWND mainWindow;
HACCEL haccel;

int CALLBACK CustMessageDlgProc
(
    HWND  CustMsgDlg,	// handle to dialog box
    UINT  msg,	// message
    WPARAM  wparam,	// first message parameter
	LPARAM  lparam 	// second message parameter
);	

int CALLBACK LandMoverDlgProc
(
    HWND  LandMoverDlg,	// handle to dialog box
    UINT  msg,	// message
    WPARAM  wparam,	// first message parameter
	LPARAM  lparam 	// second message parameter
);

int CALLBACK GuestEntryDlgProc
(
    HWND  GuestEntryDlg,	// handle to dialog box
    UINT  msg,	// message
    WPARAM  wparam,	// first message parameter
	LPARAM  lparam 	// second message parameter
);	

int CALLBACK RandomTerrainDlgProc
(	HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam
);

//Set8carsDllLocals(_8CARS_WINDOWTITLE,_Rct2KeyboardHook,_haccel,Rct2Version);
int Set8carsDllLocals
(
	char *newMain,HHOOK newhook,HACCEL newAccel,
	int _Rct2Version
)
{	strncpy(&mainWindowName,newMain,sizeof(mainWindowName)-1);
	mainWindow=FindWindow(NULL,&mainWindowName);	
	rct2KeyboardHook=newhook;
	haccel=newAccel;	
	_Rct2Version=GetRct2Version();
}

typedef struct
{
	DWORD 
		repeatCount		:16,
		scanCode		:8,
		isExtendedKey	:1,
		reserved		:4,
		altDown			:1,
		prevKeyState	:1,
		transitionState	:1;
}	KEYSTROKE_MESSAGEFLAGS;


#define TS_UP	1	//transitions states
#define TS_DOWN	0

int MenuSwitch(HWND hwnd,WORD commandID);

#define VK_TO_SCANCODE	0
#define VK_TO_ASCII		2

/*
  can use:
  F6-F12
  ctrl+F-[0-12]
*/
/*
typedef struct 
{	union
	{	struct
		{	BYTE 
				recentPress	:1,
				reserved	:6,
				down		:1;
		}	stateBits;
		BYTE 
			stateByte;
	}	shift,ctrl,alt;
} SHIFTS;
*/
typedef struct 
{	union
	{	struct
		{	BYTE 
				toggled		:1,
				reserved	:6,
				down		:1;
		}	stateBits;
		BYTE 
			stateByte;
	}	shift,ctrl,alt;
} SHIFTS;

SHIFTS shifts={{0},{0},{0}};

LRESULT CALLBACK RCT2KeyInterceptProc
(	int  code,	// hook code
	WPARAM  wparam,	// virtual-key code
	LPARAM  lparam 	// keystroke-message information
)
{
	KEYSTROKE_MESSAGEFLAGS keyMsgFlags;
/*
	UINT 
		keyScanCode=MapVirtualKey(wparam,VK_TO_SCANCODE),
		keyAscii=MapVirtualKey(wparam,VK_TO_ASCII);
*/
	shifts.ctrl.stateByte=GetKeyState(VK_CONTROL);
	shifts.shift.stateByte=GetKeyState(VK_SHIFT);
	shifts.alt.stateByte=GetKeyState(VK_MENU);

	memcpy(&keyMsgFlags,&lparam,sizeof(keyMsgFlags));

	switch(wparam)
	{
	case VK_F1:	case VK_F2:	case VK_F3:	case VK_F4:
	case VK_F5:	case VK_F6:	case VK_F7:	case VK_F8:	
	case VK_F9:	case VK_F10: case VK_F11: case VK_F12:
		if(keyMsgFlags.transitionState==TS_DOWN)
		{
			if	(	(!shifts.alt.stateBits.down)
					&&(!shifts.ctrl.stateBits.down)
					&&(!shifts.shift.stateBits.down)
				)
			{	
				switch(wparam)
				{
				case VK_F1:	case VK_F2:	case VK_F3:	case VK_F4:
				case VK_F5:	
					goto LINE_FKEY_EXIT;
				default:
					goto LINE_FKEY;
				}
			}
			if(shifts.alt.stateBits.down)
				goto LINE_ALT_FKEY;
			if(shifts.ctrl.stateBits.down)
				goto LINE_CTRL_FKEY;
			if(shifts.shift.stateBits.down)
				goto LINE_SHIFT_FKEY;

			LINE_FKEY:
				switch(wparam)
				{
				/*
					key	function
					F6	ID_PARK_OPEN
					F7	ID_PARK_CLOSE
					F8	ID_MONEY_ADD5000CASH
					F9	ID_MONEY_SUBTRACT50000CASH
					F10	ID_RIDES_EDITRIDESTATS
					F11	ID_MISC_MAPOBJECTMANIPULATION
					F12	ID_GUESTS_TRAMS_LARGETRAM
				*/
				case VK_F6:
					MenuSwitch(mainWindow,ID_PARK_OPEN);
					break;
				case VK_F7:
					MenuSwitch(mainWindow,ID_PARK_CLOSE);
					break;
				case VK_F8:
					MenuSwitch(mainWindow,ID_MONEY_ADD5000CASH);
					break;
				case VK_F9:
					MenuSwitch(mainWindow,ID_MONEY_SUBTRACT5000CASH);
					break;
				case VK_F10:
					//MenuSwitch(rct2Window,ID_RIDES_EDITRIDESTATS);
					break;
				case VK_F11:
					//MenuSwitch(rct2Window,ID_MISC_MAPOBJECTMANIPULATION);
					break;
				case VK_F12:
					#ifdef TEST_PROCEDURE_CALL
						MessageBox(NULL,"F12 was pressed","Message",MB_ICONEXCLAMATION|MB_OK|MB_SYSTEMMODAL);
					#endif //TEST_PROCEDURE_CALL 
					MenuSwitch(mainWindow,ID_GUESTS_TRAMS_LARGETRAM);
					break;
				}
				goto LINE_FKEY_EXIT;
			LINE_CTRL_FKEY:
				/*
					key	function
					F1	ID_LANDSCAPE_ACTIVATEMOUNTAINTOOL
				*/
				switch(wparam)
				{
				case VK_F1:
					MenuSwitch(mainWindow,ID_LANDSCAPE_ACTIVATEMOUNTAINTOOL);
					break;
				case VK_F2:
					break;
				case VK_F3:
					break;
				case VK_F4:
					break;
				case VK_F5:
					break;
				case VK_F6:
					break;
				case VK_F7:
					break;
				case VK_F8:
					break;
				case VK_F9:
					break;
				case VK_F10:
					break;
				case VK_F11:
					break;
				case VK_F12:
					break;
				}
				goto LINE_FKEY_EXIT;
			LINE_ALT_FKEY:
				switch(wparam)
				{
				case VK_F1:
					break;
				case VK_F2:
					break;
				case VK_F3:
					break;
				case VK_F4:
					break;
				case VK_F5:
					break;
				case VK_F6:
					break;
				case VK_F7:
					break;
				case VK_F8:
					break;
				case VK_F9:
					break;
				case VK_F10:
					break;
				case VK_F11:
					break;
				case VK_F12:
					break;
				}
				goto LINE_FKEY_EXIT;
			LINE_SHIFT_FKEY:
				/*
					F1	ID_PARK_INCREASETIME_1DAY
					F2	ID_PARK_DECREASETIME_1DAY
					F3	ID_PARK_INCREASETIME_1MONTH
					F4	ID_PARK_DECREASETIME_1MONTH
					F5	ID_MISC_ZEROALLCLEARANCES_ABSOLUTE
					F6	ID_MISC_ZEROALLCLEARANCES_RELATIVE
					F7	ID_MISC_RESTORECLEARANCES
					F8	ID_STAFF_HANDYMAN_MOWGRASS_PLAIN
					F9	ID_STAFF_HANDYMAN_FIXVANDALISM
					F10	ID_STAFF_HANDYMAN_WATERGARDENS
					F11	ID_WEATHER_MAKESUNNY
					F12	ID_STAFF_MECHANIC_RENEWRIDES
				*/
				switch(wparam)
				{
				case VK_F1:
					MenuSwitch(mainWindow,ID_PARK_INCREASETIME_1DAY);
					break;
				case VK_F2:
					MenuSwitch(mainWindow,ID_PARK_DECREASETIME_1DAY);
					break;
				case VK_F3:
					MenuSwitch(mainWindow,ID_PARK_INCREASETIME_1MONTH);
					break;
				case VK_F4:
					MenuSwitch(mainWindow,ID_PARK_DECREASETIME_1MONTH);
					break;
				case VK_F5:
					//MenuSwitch(mainWindow,ID_MISC_ZEROALLCLEARANCES_ABSOLUTE);
					break;
				case VK_F6:
					//MenuSwitch(mainWindow,ID_MISC_ZEROALLCLEARANCES_RELATIVE);
					break;
				case VK_F7:
					//MenuSwitch(mainWindow,ID_MISC_RESTORECLEARANCES);
					break;
				case VK_F8:
					//MenuSwitch(mainWindow,ID_STAFF_HANDYMAN_MOWGRASS_PLAIN);
					break;
				case VK_F9:
					//MenuSwitch(mainWindow,ID_STAFF_HANDYMAN_FIXVANDALISM);
					break;
				case VK_F10:
					//MenuSwitch(mainWindow,ID_STAFF_HANDYMAN_WATERGARDENS);
					break;
				case VK_F11:
					MenuSwitch(mainWindow,ID_WEATHER_MAKESUNNY);
					break;
				case VK_F12:
					MenuSwitch(mainWindow,ID_STAFF_MECHANIC_RENEWRIDES);
					break;
				}
				goto LINE_FKEY_EXIT;
			LINE_FKEY_EXIT:
				break;
		}
		break;
	}

	//

	if(rct2KeyboardHook!=NULL)
		return CallNextHookEx(rct2KeyboardHook,code,wparam,lparam);
	else
		return FALSE;
}

int RefreshWindow(HWND hwnd)
{
	RECT rect;
	HRGN hrgn;

	GetUpdateRect(hwnd,&rect,TRUE);

	RedrawWindow(hwnd,&rect,NULL,RDW_ERASE);
}

PROCESS_INFORMATION processinfo;

#define SE_ERRHIGH 32



int APIENTRY MainWndProc
(	HWND hwnd, 
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	int result=TRUE;
	HHOOK svHook;

	switch(uMsg)
	{
	case WM_CHILDACTIVATE:
		ShowWindow(hwnd,SW_SHOW);
		RefreshWindow(hwnd);		
		return FALSE;

	case WM_MOVE:
	case WM_SIZE:
		RefreshWindow(hwnd);
		return TRUE;  

	case WM_KEYDOWN:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);		

	case WM_COMMAND:

		result=MenuSwitch(hwnd,LOWORD(wParam));
		return result;

	case WM_CLOSE:
		PostQuitMessage(0);
		return TRUE;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}

int MenuSwitch(HWND hwnd,WORD commandID)
{
	int 
		result=TRUE,
		hprocess;
	BYTE 
		byteData;
	char 
		path1[128],path2[128],
		*cmdline[2]={&path1,NULL};

	HANDLE 
		curProcess=GetCurrentProcess(),
		curThread=GetCurrentThread();

	SetPriorityClass(curProcess,REALTIME_PRIORITY_CLASS);
	SetThreadPriority(curThread,THREAD_PRIORITY_HIGHEST);
	
	switch(commandID)  // command id
	{
	case ID_PARK_OPEN:         
		WinOrB(hwnd,RCT2_TITLE,RCT2_ADDR_PARKSTATUS0,RCT2_MASK_OPENCLOSE);
		break;
	case ID_PARK_CLOSE:                  
		WinAndB(hwnd,RCT2_TITLE,RCT2_ADDR_PARKSTATUS0,~RCT2_MASK_OPENCLOSE);
		break;
	case ID_PARK_COUNTOBJECTS_RIDES:
		CountRides();
		break;
	case ID_PARK_COUNTOBJECTS_MAPTILEOBJECTS:
		CountMapData();
		break;
	case ID_PARK_COUNTOBJECTS_SPRITES:
		CountSprites();
		break;
	case ID_PARK_OPTIMIZEMAPDATASPACE:
		OptimizeMapDataSpace();
		break;
	case ID_PARK_INVERTLANDOWNERSHIP_INCLUDERIGHTSFORSALE:
		InvertOwnership();
		break;
	case ID_PARK_INVERTLANDOWNERSHIP_INGORERIGHTSFORSALE:
		InvertOwnershipIgnore();
		break;
	case ID_PARK_SETUNOWNEDTORIGHTS:
		ChangeUnowntoRights();
		break;
	case ID_PARK_OWNALLLAND:
		OwnAllLand();		
		break;
	case ID_PARK_QUIT:
	case IDCANCEL:
		PostQuitMessage(0);
		return TRUE;
	case ID_PARK_DEOWNBORDERLAND:
		DeownBorderLand();
		break;
	case ID_PARK_BORDERFENCE_RESTORE:
		RestoreBorderFence();
		break;
	case ID_PARK_BORDERFENCE_REMOVE:
		RemoveBorderFence();
		break;
	case ID_PARK_ADDCUSTOMMESSAGE:
		DialogBox
		(	hinst,
			MAKEINTRESOURCE(IDD_INSERTCUSTOMMESSAGE),
			hwnd,CustMessageDlgProc
		);
		break;
	case ID_PARK_CLEARALLMESSAGES:
		ClearAllMessages();
		break;

	case ID_PARK_INCREASETIME_1DAY:
		IncDate(1,0,0);
		break;
	case ID_PARK_INCREASETIME_1MONTH:
		IncDate(0,1,0);
		break;
	case ID_PARK_INCREASETIME_1YEAR:
		IncDate(0,0,1);
		break;
	case ID_PARK_DECREASETIME_1DAY:
		IncDate(-1,0,0);
		break;
	case ID_PARK_DECREASETIME_1MONTH:
		IncDate(0,-1,0);
		break;
	case ID_PARK_DECREASETIME_1YEAR:
		IncDate(0,0,-1);
		break;
	case ID_PARK_RESETDATE:
		SetDate(0,0,0);
		break;

	case ID_PARK_CHANGEGUESTENTRYPOINTS:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_GUESTENTRYPOINTS),
			hwnd,GuestEntryDlgProc
		);
		break;
	case ID_MONEY_USEMONEY:
		WinAndB(hwnd,RCT2_TITLE,RCT2_ADDR_PARKSTATUS1,!RCT2_MASK_USEMONEY);
		break;
	case ID_MONEY_DONTUSEMONEY:
		WinOrB(hwnd,RCT2_TITLE,RCT2_ADDR_PARKSTATUS1,RCT2_MASK_USEMONEY);
		break;
	case ID_WEATHER_MAKESUNNY:         
		SETWEATHER(WS_SUNNY);
		break;
	case ID_WEATHER_STARTHEAVYRAIN:
		SETWEATHER(WS_HEAVYRAIN);	
		break;
	case ID_WEATHER_STARTTHUNDERSTORM:
		SETWEATHER(WS_THUNDERSTORM);
		break;
	case ID_WEATHER_STARTSHOWER:
		SETWEATHER(WS_SHOWER);
		break;
	case ID_WEATHER_MAKECOLD:
		SETWEATHER(WS_COLD);
		break;
	case ID_WEATHER_MAKEFREEZING:        
		SETWEATHER(WS_FREEZE);
		break;
	case ID_WEATHER_MAKEHOT:
		SETWEATHER(WS_HOT);	
		break;
	case ID_WEATHER_FREEZEWEATHER:
		FreezeWeather();
		break;
	case ID_LANDSCAPE_LOADTERRAINBMP:
		LoadTerrainBMP(hwnd,hinst);			
		break;
	case ID_LANDSCAPE_SAVETERRAINBMP:
		SaveTerrainBMP(hwnd,hinst);			
		break;
	case ID_LANDSCAPE_GENERATERANDOMTERRAIN:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_RANDOMTERRAIN),
			hwnd,RandomTerrainDlgProc
		);
		break;
	case ID_LANDSCAPE_CAPLANDATMAXHEIGHT:
		CapLandAtMaxHeight();
		break;
	case ID_LANDSCAPE_ACTIVATEMOUNTAINTOOL:
		byteData=0;
		WinWrite(hwnd,RCT2_TITLE,RCT2_ADDR_LANDMOVERSIZE,&byteData,sizeof(BYTE));
		break;
	case ID_LANDSCAPE_ADJUSTLANDMOVERSIZE:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_TERRAINTOOLSIZE),
			hwnd,LandMoverDlgProc
		);
		break;
	case ID_LANDSCAPE_FIXINVISBLEBORDER:
		FixInvisibleBorder();
		break;
	case ID_STAFF_ADVERTISING_PROMOTEGENTLERIDES:
		TameGuests();
		break;
	case ID_STAFF_ADVERTISING_PROMOTEINTENSERIDES:
		WildGuests();
		break;
	case ID_STAFF_ADVERTISING_PROMOTEALLRIDES:
		AllAroundGuests();
		break;
	case ID_STAFF_BANKER_GIVEALLGUESTS100CASH:
		GiveAllGuests100Cash();
		break;
	case ID_STAFF_BANKER_GIVEALLGUESTS1000CASH:
		GiveAllGuests1000Cash();
		break;
	case ID_STAFF_HANDYMAN_MOWGRASS:
		MowGrass();
		break;
	case ID_STAFF_HANDYMAN_MOWGRASS_PLAIN:
		MowGrassPlain();
		break;
	case ID_STAFF_HANDYMAN_WATERGARDENS:
		WaterGardens();		
		break;			
	case ID_STAFF_HANDYMAN_EMPTYTRASH:
		EmptyTrash();
		break;
	case ID_STAFF_HANDYMAN_CLEANPATHS:
		CleanPaths();
		break;
	case ID_STAFF_MECHANIC_REPAIRRIDES:
		RepairRides();
		break;
	case ID_STAFF_MECHANIC_RENEWRIDES:
		RenewRides();
		break;
	case ID_STAFF_MECHANIC_MAKERIDESRELIABLE:
		MakeRidesReliable();
		break;
	case ID_STAFF_SECURITY_PACIFYVANDALS:
		PacifyVandals();
		break;
	case ID_STAFF_HANDYMAN_FIXVANDALISM:
		FixVandalism();
		break;
	case ID_PARK_VANDALIZEPARK:
		VandalizePark();
		break;
	case ID_STAFF_ENTERTAINER_MAKEGUESTSHAPPY:
		MakeGuestsHappy();
		break;
	case ID_STAFF_ENTERTAINER_GIVEGUESTSBALLOONS:
		GiveGuestsBalloons();
		break;
	case ID_STAFF_CATERER_GIVEGUESTSDRINKS:
		GiveGuestDrinks();
		break;
	case ID_STAFF_CATERER_GIVEGUESTSBURGERS:
		GiveGuestsBurgers();
		break;
	case ID_STAFF_FIRSTAID_HEALNAUSEA:
		HealNausea();
		break;
	case ID_STAFF_FIRSTAID_VITALIZEGUESTS:
		VitalizeGuests();
		break;
	case ID_STAFF_PARKGUIDE_HELPGUESTSFINDRESTROOMS:
		HelpGuestsFindRestrooms();
		break;
	case ID_STAFF_PARKGUIDE_HANDOUTPARKMAPS:
		HandOutParkMaps();
		break;
	case ID_STAFF_PARKGUIDE_GIVEGUESTSUMBRELLAS:
		GiveGuestsUmbrellas();
		break;
	case ID_STAFF_RESEARCHER_COMPLETERESEARCH:
		break;
	case ID_STAFF_STAFFSPEED_FAST:
		FastStaff();
		break;
	case ID_STAFF_STAFFSPEED_NORMAL:
		NormalStaff();
		break;
	case ID_STAFF_STAFFSPEED_SLOW:
		SlowStaff();
		break;
	case ID_STAFF_STAFFSPEED_FREEZE:
		FreezeStaff();
		break;
	case ID_STAFF_EDITSTAFF:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_STAFFMENU),
			hwnd,StaffMenuDlgProc
		);
		break;

	case ID_RIDES_EDITRIDESTATS:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_RIDESMENU),
			hwnd,RideMenuDlgProc
		);
		break;
	case ID_RIDES_10MINUTEINSPECTIONS:
		_10MinuteInspections();
		break;
	case ID_RIDES_UNIFORMITEMPRICING:
		UniformItemPricing();
		break;
	case ID_RIDES_ANYHEIGHTCONSTRUCTION:
		AnyHeightConstruction();
		break;
	case ID_RIDES_10FOOTSHOPS:
		_10FootShops();
		break;
	case ID_RIDES_8CARSPERTRAIN:
		_8CarsPerTrain();
		break;	
	case ID_RIDES_ULTRAEXCITINGRIDES:
		UltraExcitingRides();
		break;			
	case ID_RIDES_ULTRAINTENSERIDES:
		UltraIntenseRides();
		break;
	case ID_RIDES_ULTRANAUSEATINGRIDES:
		UltraNauseatingRides();
		break;
	case ID_GUESTS_ALLAROUNDGUESTS:
		AllAroundGuests();
		break;
	case ID_GUESTS_TRAMS_SMALLTRAM:
		Tram_Small();
		break;
	case ID_GUESTS_TRAMS_MEDIUMTRAM:
		Tram_Medium();
		break;
	case ID_GUESTS_TRAMS_LARGETRAM:
		#ifdef TEST_PROCEDURE_CALL
			MessageBox(NULL,"Large Tram Proc called","Message",MB_ICONEXCLAMATION|MB_OK|MB_SYSTEMMODAL);
		#endif //TEST_PROCEDURE_CALL 
		Tram_Large();
		break;
	case ID_GUESTS_TRAMS_HUGETRAM:
		Tram_Huge();
		break;
	case ID_GUESTS_REMOVEALLGUESTS:
		RemoveGuests();
		break;
	case ID_GUESTS_RESETGUESTNUMBERS:
		ResetGuestNumbers();
		break;
	case ID_GUESTS_FREEZEGUESTMOVEMENT:
		FreezeGuests();
		break;
	case ID_GUESTS_UNIFORMPEEPS:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_UNIFORMPEEPS),
			hwnd,UniformPeepColorProc
		);
		break;

	case ID_HELP_CONTENTS:
		//WinHelp(hwnd,"help/8cars.hlp",HELP_FINDER,0);
		
		strcpy(&path1,"");
		strncat(&path1,&savepath,128);
		strcat(&path1,_8CARSHELP_HTML);
		hprocess=
			ShellExecute
			(	hwnd,"open",&path1,NULL,
				&savepath,0
			);
		//hprocess=CreateProcess(&path2,"notepad E:\\8cars\\c\\src\\8carshelp.txt",NULL,NULL,FALSE,0,NULL,NULL,&startup,&processinfo);
		if(hprocess<=SE_ERRHIGH)
		{	
			strcpy(&path1,"");
			strncat(&path1,&savepath,128);
			strcat(&path1,_8CARSHELP_TXT);
			hprocess=
				ShellExecute
				(	hwnd,"open",&path1,NULL,
					&savepath,0
				);			
			if(hprocess<=SE_ERRHIGH)
				MessageBox(hwnd,"Failed to open help file","Message",MB_ICONEXCLAMATION|MB_OK|MB_APPLMODAL);
		}
		break;
	case ID_HELP_ABOUT:
		AboutBox(hwnd);
		break;
	case ID_MONEY_SUBTRACT5000CASH:
		IncCash(-50000,TRUE,50000);
		break;
	case ID_MONEY_ADD5000CASH:
		IncCash(50000,TRUE,50000);
		break;
	case ID_MONEY_SUBTRACT50000CASH:
		IncCash(-500000,TRUE,500000);
		break;
	case ID_MONEY_ADD50000CASH:
		IncCash(500000,TRUE,500000);
		break;
	case ID_MONEY_SUBTRACT500000CASH:
		IncCash(-5000000,TRUE,5000000);
		break;
	case ID_MONEY_ADD500000CASH:
		IncCash(5000000,TRUE,5000000);
		break;
	case ID_MONEY_SUBTRACT5000000CASH:
		IncCash(-50000000,TRUE,5000000);
		break;
	case ID_MONEY_ADD5000000CASH:
		IncCash(50000000,TRUE,5000000);
		break;
	case ID_MONEY_ADDCASH_CUSTOM:
		IncCashCustom();
		break;

	case ID_MISC_SORTMAPELEMENTSINTERNALLY:
		SortMapElmentsInternally();
		break;	
	case ID_DEBUG_ELIMINATEDUPLICATESUFACEDATA:
		EliminateDuplicateSurfaceData();
		break;
	case ID_MISC_REMOVEFLOATINGOBJECTS:
		RemoveFloatingObjects();
		break;	
	case ID_MISC_ZEROALLCLEARANCES_ABSOLUTE:
		ZeroAllClearancesAbsolutely();
		break;	
	case ID_MISC_ZEROALLCLEARANCES_RELATIVE:
		ZeroAllClearancesRelatively();
		break;	
	case ID_MISC_RESTORECLEARANCES:
		RestoreAllClearances();
		break;	
	case ID_MISC_MAPOBJECTMANIPULATION:
		DialogBox
		(	hinst,MAKEINTRESOURCE(IDD_MAPOBJECTMANIPULATION),
			hwnd,MapObjectManipulationDlgProc
		);
		break;	
	default:
		result=FALSE;
		break;
	}

	SetPriorityClass(curProcess,NORMAL_PRIORITY_CLASS);
	SetThreadPriority(curThread,THREAD_PRIORITY_NORMAL);

	if(result)
		CommandMessage(commandID);
	return result;
}

#define MESSAGECOLORS	13
#define MESSAGEICONS	9
struct DROPDOWNENTRY
{	
	char 
		String[16],
		ID;
}
MsgColor[MESSAGECOLORS]=
{	{"white",0x90},	
	{"red",0x91},
	{"green",0x92},
	{"gold",0x93},
	{"brown",0x94},
	{"grey",0x95},
	{"blue",0x96},	
	{"purple",0x97},
	{"beige",0x98},
	{"pink",0x99},
	{"aqua",0x9A},
	{"tan",0x9B},
	{"green",0x9C},
},
MsgIcon[MESSAGEICONS]=
{	{"Ride",1},
	{"Person walking",2},
	{"Person walking",3},
	{"Coins",4},
	{"Blank",5},
	{"Scenery",6},
	{"Crowd of people",7},
	{"Award",8},
	{"Graph",9},
};
	
int CALLBACK CustMessageDlgProc
(
    HWND  CustMsgDlg,	// handle to dialog box
    UINT  msg,	// message
    WPARAM  wparam,	// first message parameter
	LPARAM  lparam 	// second message parameter
)	

{	
	HWND hEBox,hColor,hTextSize,hIcon;
	
	int i;

	int Message;
	int itemHeight;

	char messageText[254] ;
	short color,icon;

	RECT rect;
	
	switch(msg)
	{
	case WM_INITDIALOG:	
		hEBox=GetDlgItem(CustMsgDlg,IDC_CUSTMSGEDIT);
		hColor=GetDlgItem(CustMsgDlg,IDC_COLORCOMBO);
		hIcon=GetDlgItem(CustMsgDlg,IDC_ICONCOMBO);

		SetDlgItemText(CustMsgDlg,IDC_CUSTMSGEDIT,"Message");

		SendMessage(hEBox,EM_SETSEL,0,-1);

		SendMessage(hColor,CB_RESETCONTENT,0,0); 

		for (i=0;i<MESSAGECOLORS;i++)
		{	SendMessage
			(	hColor,CB_ADDSTRING,0,
				(LPARAM)&MsgColor[i].String
			);
			SendMessage
			(	hColor,CB_SETITEMDATA,i,
				(LPARAM)MsgColor[i].ID
			);
		}

		SendMessage(hIcon,CB_RESETCONTENT,0,0); 
		
		for(i=0;i<MESSAGEICONS;i++) 
		{	SendMessage
			(	hIcon,CB_ADDSTRING,0,
				(LPARAM)&MsgIcon[i].String
			);
			SendMessage
			(	hIcon,CB_SETITEMDATA,i,
				(LPARAM)MsgIcon[i].ID
			);
		}

		SendMessage(hColor,CB_SETCURSEL,0,0);
		SendMessage(hIcon,CB_SETCURSEL,0,0);
		SendMessage(hIcon,CB_SETDROPPEDWIDTH,8*16,0); 

		SetFocus(hEBox);
		return FALSE;			
		
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDOK:
			hEBox=GetDlgItem(CustMsgDlg,IDC_CUSTMSGEDIT);
			hColor=GetDlgItem(CustMsgDlg,IDC_COLORCOMBO);
			hIcon=GetDlgItem(CustMsgDlg,IDC_ICONCOMBO);

			color=MsgColor[SendMessage(hColor,CB_GETCURSEL,0,0)].ID;
			icon=MsgIcon[SendMessage(hIcon,CB_GETCURSEL,0,0)].ID;
			GetDlgItemText(CustMsgDlg,IDC_CUSTMSGEDIT,&messageText,254);
			
			WriteRct2Message(&messageText,color,icon,0,1);			

		case IDCANCEL:
			EndDialog(CustMsgDlg,NULL); 
			return TRUE; 
		
		default:
			return FALSE;

		}

	default:
		return FALSE;
	}
	return FALSE;


}


short moversize=0;

int CALLBACK LandMoverDlgProc
(
    HWND  LandMoverDlg,	// handle to dialog box
    UINT  msg,	// message
    WPARAM  wparam,	// first message parameter
	LPARAM  lparam 	// second message parameter
)	


{	
	HWND hEBox;
	
	int i;
	char strMoverSize[16];

	switch(msg)
	{
	case WM_INITDIALOG:	
		hEBox=GetDlgItem(LandMoverDlg,IDC_SIZEEDIT);

		moversize=0;

		SendMessage(hEBox,EM_SETLIMITTEXT,3,0);

		WinRead(mainWindow,RCT2_TITLE,&moversize,RCT2_ADDR_LANDMOVERSIZE,2);
		
		SetDlgItemText(LandMoverDlg,IDC_SIZEEDIT,_itoa(moversize,&strMoverSize,10));
		
		SetFocus(LandMoverDlg);
		return FALSE;			
	case WM_CHAR:
		switch((char)wparam)
		{
		case '+':
		case '=':
			LandMoverDlgProc
			(	LandMoverDlg,WM_COMMAND,IDC_BUTTONPLUS,0
			);
			return TRUE;
		case '-':
		case '_':
			LandMoverDlgProc
			(	LandMoverDlg,WM_COMMAND,IDC_BUTTONMINUS,0
			);
			return TRUE;
		default:
			return FALSE;
		}
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDC_BUTTONPLUS:
			if(moversize<255)++moversize;
			goto UpdateMoverSize;			
		case IDC_BUTTONMINUS:
			if(moversize>0)--moversize;
			goto UpdateMoverSize;
		case IDC_MOUNTAINTOOLBTN:
			moversize=0;
			UpdateMoverSize:
				SetDlgItemText(LandMoverDlg,IDC_SIZEEDIT,_itoa(moversize,&strMoverSize,10));
			return TRUE;

		case IDAPPLY:
		case IDOK:
			GetDlgItemText(LandMoverDlg,IDC_SIZEEDIT,&strMoverSize,sizeof(strMoverSize));
			moversize=(short)atoi(&strMoverSize);
			WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_LANDMOVERSIZE,&moversize,2);
			if (LOWORD(wparam)==IDAPPLY)return TRUE;
			
		case IDCANCEL:
			EndDialog(LandMoverDlg,NULL); 
			return TRUE; 
		
		default:
			return FALSE;

		}

	default:
		return FALSE;
	}
	return FALSE;


}

struct DROPDOWNENTRY DirectionEntry[4]=
{	"East",0,
	"South",1,
	"West",2,
	"North",3	
};


int CALLBACK GuestEntryDlgProc
(
    HWND  GuestEntryDlg,	// handle to dialog box
    UINT  msg,	// message
    WPARAM  wparam,	// first message parameter
	LPARAM  lparam 	// second message parameter
)	
{	
	ENTRYPOINTSTRUCT mapEntry[2];
	
	char tmpstr[8];
	
	char StartCoord[3][2]={"1","1","0"};

	HWND hCoordBox[3][2],hDirecBox[2];

	short RCTLoaded; 

	int direction[2];

	int Coord[3][2];

	int CoordBoxID[3][2]=
	{	{IDC_XEDIT,IDC_XEDIT2},
		{IDC_YEDIT,IDC_YEDIT2},
		{IDC_ZEDIT,IDC_ZEDIT2}	
	};

	int i,k;
	XYZCOORD j;

	char strXYZ[8];

	switch(msg)
	{
	case WM_INITDIALOG:	
		hCoordBox[X][0]=GetDlgItem(GuestEntryDlg,IDC_XEDIT);
		hCoordBox[X][1]=GetDlgItem(GuestEntryDlg,IDC_XEDIT2);
		hCoordBox[Y][0]=GetDlgItem(GuestEntryDlg,IDC_YEDIT);
		hCoordBox[Y][1]=GetDlgItem(GuestEntryDlg,IDC_YEDIT2);
		hCoordBox[Z][0]=GetDlgItem(GuestEntryDlg,IDC_ZEDIT);
		hCoordBox[Z][1]=GetDlgItem(GuestEntryDlg,IDC_ZEDIT2);
		hDirecBox[0]=GetDlgItem(GuestEntryDlg,IDC_DIRECTION);
		hDirecBox[1]=GetDlgItem(GuestEntryDlg,IDC_DIRECTION2);

		//		typedef struct
//		{	short x,y;
//			char z,direction;
//		} ENTRYPOINTSTRUCT;

		RCTLoaded=WinRead(mainWindow,RCT2_TITLE,&mapEntry,RCT2_ADDR_MAPENTRY,sizeof(mapEntry));
		
		mapEntry[0].x=mapEntry[0].x/32;
		mapEntry[1].x=mapEntry[1].x/32;
		mapEntry[0].y=mapEntry[0].y/32;
		mapEntry[1].y=mapEntry[1].y/32;
		mapEntry[0].z=mapEntry[0].z-7;
		mapEntry[1].z=mapEntry[1].z-7;

		for(i=0;i<2;i++)
		{	for(j=0;j<4;j++)
			{	SendMessage
				(	hDirecBox[i],CB_ADDSTRING,0,
					(LPARAM)&DirectionEntry[j].String
				);
				SendMessage
				(	hDirecBox[i],CB_SETITEMDATA,j,
					DirectionEntry[j].ID
				);				
			}	

			SendMessage(hDirecBox[i],CB_SETCURSEL,mapEntry[i].direction,0);

			for(j=X;j<=Z;j++)
			{	

				if(RCTLoaded)
					switch(j)
					{
					case X:_itoa(mapEntry[i].x,&tmpstr,10);break;
					case Y:_itoa(mapEntry[i].y,&tmpstr,10);break;
					case Z:_itoa(mapEntry[i].z,&tmpstr,10);break;
					}									
				else 
					strncpy(&tmpstr,StartCoord[j],3);				
			
				SetDlgItemText(GuestEntryDlg,CoordBoxID[j][i],&tmpstr);
				SendMessage(hCoordBox[j][i],EM_SETLIMITTEXT,3,0);
			}
		}

		SetFocus(GuestEntryDlg);
		
		return FALSE;			
		
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDAPPLY:
		case IDOK:
			hDirecBox[0]=GetDlgItem(GuestEntryDlg,IDC_DIRECTION);
			hDirecBox[1]=GetDlgItem(GuestEntryDlg,IDC_DIRECTION2);

			for(i=0;i<2;i++)
			{	k=SendMessage(hDirecBox[i],CB_GETCURSEL,0,0);
				direction[i]=SendMessage(hDirecBox[i],CB_GETITEMDATA,k,0);
				for(j=X;j<=Z;j++)
				{	GetDlgItemText(GuestEntryDlg,CoordBoxID[j][i],&strXYZ,8);
					Coord[j][i]=atoi(&strXYZ);
				}
			}


			SetMapEntryPoints
			(	Coord[X][0],Coord[Y][0],Coord[Z][0],
				Coord[X][1],Coord[Y][1],Coord[Z][1],
				direction[0],direction[1]
			);

			if(LOWORD(wparam)==IDAPPLY) 
				return TRUE;

		case IDCANCEL:
			EndDialog(GuestEntryDlg,NULL); 
			return TRUE; 
		
		default:
			return FALSE;

		}

	default:
		return FALSE;
	}
	return FALSE;


}


#define HIGHRTCONTROLS 3

typedef enum
{	RTC_AVGHEIGHT,RTC_INCLINE,RTC_VARIATION
} RT_CONTROL;

#define LOW 0
#define HIGH 1

int CALLBACK RandomTerrainDlgProc
(	HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam
)
{
	static int 
		barval[HIGHRTCONTROLS],
		barID[HIGHRTCONTROLS]=
		{	IDC_AVGHEIGHTBAR,
			IDC_INCLINEBAR,
			IDC_VARIATIONBAR		
		},
		editID[HIGHRTCONTROLS]=
		{	IDC_AVGHEIGHTEDIT,
			IDC_INCLINEEDIT,
			IDC_VARIATIONEDIT		
		},

		BarRange[HIGHRTCONTROLS][2]=
		{	{-6,117},{0,117},{0,117},			
		};

	static HWND 
		barHndl[HIGHRTCONTROLS]=
		{	NULL,NULL,NULL
		};

	int i,j,k;
	char tmpstr[8];


	//TBM_SETRANGE 
	//wParam = (WPARAM) (BOOL) fRedraw; 
	//lParam = (LPARAM) MAKELONG(lMinimum, lMaximum); 


	HWND hedit,hbar;
	
	//IDD_RANDOMTERRAIN
	//IDOK
	//IDCANCEL
	//
	//
	switch(msg)
	{
	case WM_INITDIALOG:
		for (i=0;i<HIGHRTCONTROLS;i++)
		{	//hedit=GetDlgItem(hdlg,editID[i]);
			barHndl[i]=GetDlgItem(hdlg,barID[i]);
			k=(BarRange[i][LOW]+BarRange[i][HIGH])/2;
			itoa(k,&tmpstr,10);
			SetDlgItemText(hdlg,editID[i],&tmpstr);
			SendMessage
			(	barHndl[i],TBM_SETRANGE,(WPARAM)TRUE,
				MAKELONG(BarRange[i][LOW],BarRange[i][HIGH])
			);			
			for(j=BarRange[i][LOW];j<BarRange[i][HIGH];j+=10)
				SendMessage(barHndl[i],TBM_SETTIC,0,j);
			SendMessage(barHndl[i],TBM_SETPOS,TRUE,k);
		}

		return TRUE;
	case WM_HSCROLL:
		hbar=(HWND)lparam;
		for (i=0;i<HIGHRTCONTROLS;i++)
			if(hbar==barHndl[i])
			{	j=SendMessage(hbar,TBM_GETPOS,0,0);
				itoa(j,&tmpstr,10);
				SetDlgItemText(hdlg,editID[i],&tmpstr);				
				return TRUE;
			}
		return FALSE;;

	case WM_COMMAND:

		switch(LOWORD(wparam))
		{
		case IDOK:
		case IDAPPLY:
			
			for (i=0;i<HIGHRTCONTROLS;i++)
				barval[i]=SendMessage(barHndl[i],TBM_GETPOS,0,0);

			GenerateRandomTerrain(barval[0],barval[1],barval[2]);
			if(LOWORD(wparam)==IDAPPLY)
				return TRUE;
		case IDCANCEL:
			EndDialog(hdlg,0);
			return TRUE;
			;
		default:
			return FALSE;
		}
	default:
		return FALSE;		
	}
}

int APIENTRY AboutBox(HWND hwnd)
{
	DWORD zero, dwBytes;
	char Data[1024];
	WORD p;

	char* s;

	//char _8carsCmdLine[128];
	//char _8CARS_EXENAME[32];

	GetFileVersionInfo
	(	_8CARS_EXENAME,0,
		dwBytes=GetFileVersionInfoSize(_8CARS_EXENAME,&zero),
		&Data
	);
	
	AboutString[p=0]=0; p++;
	VerQueryValue
	(	&Data,"\\StringFileInfo\\040904b0\\FileDescription",
		&s,&dwBytes
	);
	strcat(AboutString,s);
	strcat(AboutString,"\n\r""Version ");
	VerQueryValue
	(	&Data,"\\StringFileInfo\\040904b0\\FileVersion",
		&s,&dwBytes
	);
	strcat(AboutString,s);
	strcat(AboutString,"\n\r");
	VerQueryValue
	(	&Data,"\\StringFileInfo\\040904b0\\LegalCopyright",
		&s,&dwBytes
	);
	strcat(AboutString,s);

	MessageBox
	(	hwnd,&AboutString,"About 8 Cars Per Trainer",
		MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND
		|MB_ICONINFORMATION
	);
	

}

