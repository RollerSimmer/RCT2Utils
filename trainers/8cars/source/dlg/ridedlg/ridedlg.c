 
#include <windows.h>
#include "ridedlg.h"
#include "../../resource.h"
#include <stddlg.h>
#include "../../rct2.h"
#include "../../8cars.h"
#include <stdlib2.h>
#include "../../parkstatus/parkstatus.h"
#include "../../ridefuncs/ridefuncs.h"
#include <objdat.h>

#include <stddlg.h>
//
/*
int FindCBData(HWND hComboBox,int data, int startindex)
{
	int 
		count,
		i,j;

	char 
		tmpstr[64];

	count=SendMessage(hComboBox,CB_GETCOUNT,0,0);

	for(i=startindex;i<count;i++)
	{	
		SendMessage(hComboBox,CB_GETLBTEXT,i,&tmpstr); 
		if((j=SendMessage(hComboBox,CB_GETITEMDATA,i,0))==data) 
			return i;
	}
	return -1;
}


int ChangeDropDown(DROPDOWNBOX *dropdown,int value,int startindex)
{
	int index;

	index=FindCBData(dropdown->pulldown.hwnd,value,startindex);
	return SendMessage(dropdown->pulldown.hwnd,CB_SETCURSEL,index,0);
}
*/
//
typedef enum
{	RMVB_CIRCUITS=0,
	RMVB_RAISELOWEROFFSET,
	RMVB_LAUNCHSPEED,
	RMVB_LIFTSPEED,
	RMVB_NUMTRAINS,
	RMVB_NUMCARS,
	RMVB_RIDEAGE
} RIDEMENUVALUEBOX;

#define NUMRIDEMENUVALUEBOXES (RMVB_RIDEAGE+1)

#define HIGHSPEED_BYTE	255
#define HIGHSPEED_MPH	573

PLUSMINUSBOX valueBox[NUMRIDEMENUVALUEBOXES]=
{	{{IDC_CIRCUITS,NULL},{IDC_CIRCUITS_PLUS,NULL},{IDC_CIRCUITS_MINUS,NULL},0,0,7},
	{{IDC_RAISELOWEROFFSET,NULL},{IDC_RAISELOWEROFFSET_PLUS,NULL},{IDC_RAISELOWEROFFSET_MINUS,NULL},0,-127,127},
	{{IDC_LAUNCHSPEED,NULL},{IDC_LAUNCHSPEED_PLUS,NULL},{IDC_LAUNCHSPEED_MINUS,NULL},0,0,HIGHSPEED_MPH},
	{{IDC_LIFTSPEED,NULL},{IDC_LIFTSPEED_PLUS,NULL},{IDC_LIFTSPEED_MINUS,NULL},0,0,255},
	{{IDC_NUMTRAINS,NULL},{IDC_NUMTRAINS_PLUS,NULL},{IDC_NUMTRAINS_MINUS,NULL},0,1,31},
	{{IDC_NUMCARS,NULL},{IDC_NUMCARS_PLUS,NULL},{IDC_NUMCARS_MINUS,NULL},0,0,20},
	{{IDC_RIDEAGE,NULL},{IDC_RIDEAGE_PLUS,NULL},{IDC_RIDEAGE_MINUS,NULL},0,-8192,8192}
};

typedef enum
{	RMCHK_FIXBREAKDOWN=0,
	RMCHK_RENEW,
	RMCHK_MAKERELIABLE,
	RMCHK_RAISELOWER,
	RMCHK_BURY,
	RMCHK_EXCAVATE,
	RMCHK_ZEROCLEARANCE,
	RMCHK__TOGGLE_VISIBLE,
	RMCHK__TOGGLE_CHAIN
} RIDEMENUCHECKBOX;

#define NUMRIDEMENUCHECKBOXES (RMCHK__TOGGLE_CHAIN+1)

#define EN_LOSTFOCUS EN_KILLFOCUS

CONTROLBOXDATA checkBox[NUMRIDEMENUCHECKBOXES]=
{	{IDC_FIXBREAKDOWN_CHECK,NULL},
	{IDC_RENEW_CHECK,NULL},
	{IDC_MAKERELIABLE_CHECK,NULL},
	{IDC_RAISELOWER_CHECK,NULL},
	{IDC_BURY_CHECK,NULL},
	{IDC_EXCAVATE_CHECK,NULL},
	{IDC_ZEROCLEARANCE_CHECK,NULL},
	{IDC__TOGGLE_VISIBLE__CHECK,NULL},
	{IDC__TOGGLE_CHAIN__CHECK,NULL}
};

typedef enum 
{	RMDDL_RIDESELECT=0,
	RMDDL_TRACKTYPE,
	RMDDL_TRAINTYPE,
	RMDDL_OPERMODE,
	RMDDL_COLORSCHEME
} RIDEMENUDROPDOWNLIST;

#define NUMRIDEMENUDROPDOWNLISTS (RMDDL_COLORSCHEME+1)

#define NUMRIDES 254
#define NUMVEHICLES 128

#define RN_NOTUSED "<Not Used>"

CBENTRY 
	RideSelectStrings[NUMRIDES],

	TrackTypes[]=
	{	{"Spiral RC",0x00},
		{"Stand-up RC",0x01},
		{"Suspended Swinging RC",0x02},
		{"Inverted RC",0x03},
		{"Junior RC",0x04},
		{"Railway/Trams",0x05},
		{"Monorail",0x06},
		{"Suspended Single-Rail RC",0x07},
		{"Boat Hire/Jet Skis",0x08},
		{"Woooden Wild Mouse",0x09},
		{"Single-Rail/Soap Box Derby RC )",0x0A},
		{"Car Ride",0x0B},
		{"Launched Freefall",0x0C},
		{"Bobsleigh RC",0xD},
		{"Observation Tower",0x0E},
		{"Looping RC",0x0F},
		{"Water Slide",0x10},
		{"Mine Train RC",0x11},
		{"Chairlift ",0x12},
		{"Corkscrew RC/Hypercoaster",0x13},
		{"Hedge Maze",0x14},
		{"Spiral Slide",0x15},
		{"Go Karts",0x16},
		{"Log Flume",0x17},
		{"River Rapids",0x18},
		{"Bumper Cars",0x19},
		{"Pirate Ship",0x1A},
		{"Swinging Inverter Ship",0x1B},
		{"Food Stall (all types)",0x1C},
		{"Drink Stall (all types)",0x1E},
		{"Shop (all types)   ",0x20},
		{"Merry-Go-Round",0x21},
		{"Information Kiosk (all types)",0x23},
		{"Bathroom (all types)",0x24},
		{"Ferris Wheel",0x25},
		{"Motion Simulator",0x26},
		{"3D Cinema",0x27},
		{"Top Spin",0x28},
		{"Space Rings",0x29},
		{"Reverse Freefall RC",0x2A},
		{"Elevator",0x2B},
		{"Vertical RC",0x2C},
		{"ATM",0x2D},
		{"Twist/Snow Cups",0x2E},
		{"Haunted House",0x2F},
		{"First Aid",0x30},
		{"Circus Show",0x31},
		{"Ghost Train/Haunted Mansion",0x32},
		{"[{Stand-up/Hyper}]-Twister/Floorless  RC",0x33},
		{"Wooden [Twister]",0x34},
		{"Side-Friction RC",0x35},
		{"[Spinning] Steel Wild Mouse",0x36},
		{"Multi-Dimensional RC (4D)",0x37},
		{"Flying RC",0x39},
		{"Virginia Reel",0x3B},
		{"Splash Boats",0x3C},
		{"Mini Helicopters",0x3D},
		{"Lay-down RC",0x3E},
		{"Suspended Monorail",0x3F},
		{"Reverser RC",0x41},
		{"{Standard/Reversed} Heartline Twister RC",0x42},
		{"Mini Golf",0x43},
		{"Giga Coaster",0x44},
		{"Roto-Drop",0x45},
		{"Flying Saucers",0x46},
		{"Crooked House",0x47},
		{"Monorail Cycles",0x48},
		{"[Compact] Inverted [[Vertical] Shuttle] RC",0x49},
		{"Water Coaster",0x4A},
		{"Air Powered Vertical Coaster",0x4B},
		{"Inverted Hairpin Coaster",0x4C},
		{"Magic Carpet",0x4D},
		{"Submarine Ride",0x4E},
		{"River Rafts",0x4F},
		{"Enterprize",0x51},
		{"Inverted Impulse Coaster",0x56},
		{"Mini Roller Coaster",0x57},
		{"Mine Ride",0x58},
		{"LIM Launched Roller Coaster",0x5A},
		{RN_NOTUSED,0xFF}
	},

	TrainTypes[NUMVEHICLES],

	#define EMPTYSLOTTEXT "<empty>"

	OperModes[]=
	{	{"Normal Mode",0x00},
		{"Continuous Circuit Mode ",0x01},
		{"Reverse-Incline Launched Shuttle Mode",0x02},
		{"Powered Launch Mode ",0x03},
		{"Shuttle Mode",0x04},
		{"Boat Hire Mode",0x05},
		{"Upward Launch Mode",0x06},
		{"Rotating Lift Mode",0x07},
		{"Station to Station Mode (chairlift)",0x08},
		{"Single ride per admission ",0x09},
		{"Multiple rides per admission",0x0A},
		{"Maze Mode",0x0B},
		{"Race Mode",0x0C},
		{"Bumper-Car Mode",0x0D},
		{"Swing Mode (pirate ships)",0x0E},
		{"Shop/Stall Mode",0x0F},
		{"Rotation Mode (carousel)",0x10},
		{"Forward Rotation (ferris wheel) ",0x11},
		{"Backward Rotation (ferris wheel) ",0x12},
		{"Film: ""Avenging Aviators"" ",0x13},
		{"3D Film: ""Mouse Tails""",0x14},
		{"Space Rings Mode",0x15},
		{"Beginners Mode (top spin)",0x16},
		{"LIM-Powered Launch Mode",0x17},
		{"Film: ""Thrill Riders""",0x18},
		{"3D Film: ""Storm Chasers""",0x19},
		{"3D Film: ""Space Raiders"" ",0x1A},
		{"Intense Mode (top spin)",0x1B},
		{"Berserk Mode (top spin)",0x1C},
		{"Haunted House Mode",0x1D},
		{"Circus Show Mode",0x1E},
		{"Downward Launch Mode",0x1F},
		{"Crooked House Mode",0x20},
		{"Freefall Drop Mode",0x21},
		{"Continuous Circuit Block Sectioned Mode",0x22},
		{"Powered Launch (no station pass)",0x23},
		{"Powered Launch Block Sectioned Mode",0x24},
	},

	ColorSchemes[]=
	{	{"Main",COLORCSCHEME_MAIN},
		{"Alternative #1",COLORCSCHEME_ALT(1)},
		{"Alternative #2",COLORCSCHEME_ALT(2)},
		{"Alternative #3",COLORCSCHEME_ALT(3)},
		{"Station Entries",COLORCSCHEME_STATIONENTRY}
	};

	#define NUMTRACKTYPES (sizeof(TrackTypes)/sizeof(CBENTRY))
	#define NUMOPERMODES (sizeof(OperModes)/sizeof(CBENTRY)) 
	#define NUMCOLORSCHEMES (sizeof(ColorSchemes)/sizeof(CBENTRY)) 

//typedef struct{CONTROLBOXDATA pulldown;int numentries;CBENTRYARRAY *entry;}
//	DROPDOWNBOX;
/*
	IDC_RIDESELECT,
	IDC_TRACKTYPE,
	IDC_TRAINTYPE,
	IDC_OPERMODE
	IDC_COLORSCHEME

*/

#define NUMRIDES 254
#define NUMVEHICLES 128
#define NUMTRACKTYPES (sizeof(TrackTypes)/sizeof(CBENTRY))
#define NUMOPERMODES (sizeof(OperModes)/sizeof(CBENTRY)) 
#define NUMCOLORSCHEMES (sizeof(ColorSchemes)/sizeof(CBENTRY)) 

DROPDOWNBOX dropDownList[NUMRIDEMENUDROPDOWNLISTS]=
{	{{IDC_RIDESELECT,NULL},NUMRIDES,&RideSelectStrings},
	{{IDC_TRACKTYPE,NULL},NUMTRACKTYPES,&TrackTypes},
	{{IDC_TRAINTYPE,NULL},NUMVEHICLES,&TrainTypes},
	{{IDC_OPERMODE,NULL},NUMOPERMODES,&OperModes},
	{{IDC_COLORSCHEME,NULL},NUMCOLORSCHEMES,&ColorSchemes}
};

////
typedef enum
{
	RMC_RIDENAME
}
RIDEMENUCAPTION;


CONTROLBOXDATA CaptionBox[]=
{
	{IDC_RIDENAME,NULL}
};

#define NUMCAPTIONS (sizeof(CaptionBox)/sizeof(CONTROLBOXDATA))

char *ReadRCT2DatStringTable(STRTBLLANGUAGE Language,char *StrTbl)
{	char *chp;
	
	if (Language<LNG_PORTUGESE+1)
 	{	chp=StrTbl;
		while((*chp!=Language)&&(*chp<LNG_PORTUGESE+1))
			chp+=strlen(chp+1)+2;
		return chp+1;
	}
	return StrTbl;
}

////
int GetVehicleNames()
{	
	DWORD *Rct2RideObjAddrs,CurRideObjAddr;
	int i,lastI,listI;

	#define STRTABLEBUFFSIZE 512

	char nameTable[STRTABLEBUFFSIZE], *chp;

	Rct2RideObjAddrs=RCT2_ADDR_RIDEOBJECTFILEPOINTERS;

	dropDownList[RMDDL_TRAINTYPE].numentries=0;
	listI=0;

	for(i=0;i<NUMVEHICLES;i++) 
	{	WinRead(mainWindow,RCT2_TITLE,&CurRideObjAddr,&(Rct2RideObjAddrs[i]),4);

		if(CurRideObjAddr!=RCT2_DWORD_EMPTY)
		{	if
			(	WinRead
				(	mainWindow,RCT2_TITLE,&nameTable,CurRideObjAddr+sizeof(TYPE0HEADER),STRTABLEBUFFSIZE
				)
			)
			{
				chp=ReadRCT2DatStringTable(LNG_USENGLISH,chp=&nameTable);
				strncpy(&TrainTypes[listI].caption,chp,CBENTRYCAPTIONSIZE);
				TrainTypes[listI].data=i;
				dropDownList[RMDDL_TRAINTYPE].numentries=++listI;
			}
			else 
				break;
		}
	}
}

int RideChangeProc(HWND hdlg,short index)
{	
	RIDESTRUCT ride,*ridearray; 

	short 
		traintype,opmode,tracktype,
		launchspeed,liftspeed,numtrains,numcars,
		buildAbsMonth,curAbsMonth,rideage,circuits,
		heightoffset,colorscheme,
		nameStringIndex,


		month,day,year;

	char tmpstr[32];

#if 1
	HWND testhndl;
	int j;
#endif

	ridearray=RCT2_ADDR_RIDES;

	if(!WinRead(mainWindow,RCT2_TITLE,&ride,&(ridearray[index]),sizeof(ride))) return FALSE;

	GetDate(&day,&month,&year);
	curAbsMonth=(year<<3)|month;
	
	tracktype=(BYTE)ride.trackType;
	traintype=(BYTE)ride.vehiObjID;
	opmode=(BYTE)ride.opmode;
	launchspeed=(short)((BYTE)ride.launchSpeed)*HIGHSPEED_MPH/HIGHSPEED_BYTE;
	liftspeed=ride.liftChainSpeed;
	numtrains=ride.amtTrains;
	numcars=ride.amtCarsPerTrain;
	buildAbsMonth=ride.absBuiltMonth;
	circuits=ride.numCircuits;
	nameStringIndex=ride.nameStringIndex&0x3ff;

	rideage=(curAbsMonth-buildAbsMonth)>>3;

	ChangeDropDown(&dropDownList[RMDDL_TRACKTYPE],tracktype,0);
	ChangeDropDown(&dropDownList[RMDDL_TRAINTYPE],traintype,0);
	ChangeDropDown(&dropDownList[RMDDL_OPERMODE],opmode,0);

	
	
	#define SetItemText(a) \
		SetDlgItemText(hdlg,valueBox[a].valueBtn.ID,&tmpstr);
	#define DoItoa(a) \
		itoa(a,&tmpstr,10)
	{

/*
		traintype,
		opmode,
		tracktype,
		launchspeed,
		liftspeed,
		numtrains,
		numcars,
		buildAbsMonth,
		curAbsMonth,
		circuits,
		heightoffset,
		colorscheme,
*/		
		
		DoItoa(circuits);
		SetItemText(RMVB_CIRCUITS);
		//DoItoa();
		//SetItemText(RMVB_RAISELOWEROFFSET);
		DoItoa(liftspeed);
		SetItemText(RMVB_LIFTSPEED);
		DoItoa(numtrains);
		SetItemText(RMVB_NUMTRAINS);
		DoItoa(numcars);
		SetItemText(RMVB_NUMCARS);
		DoItoa(rideage);
		SetItemText(RMVB_RIDEAGE);
		DoItoa(launchspeed);
		SetItemText(RMVB_LAUNCHSPEED);
	}
	#undef DoItoa
	#undef SetItemText


	#define SetCaption(c)		\
		SetDlgItemText(hdlg,CaptionBox[c].ID,&tmpstr)
	{
		GetRCT2NameString(&tmpstr,nameStringIndex);
		SetCaption(RMC_RIDENAME);
	}
	#undef SetCaption
}

int ApplyChanges(HWND hdlg)
{	
	RIDESTRUCT ride,*ridearray; 

	short 
		index,
		traintype,opmode,tracktype,
		launchspeed,liftspeed,numtrains,numcars,
		buildAbsMonth,curAbsMonth,rideage,circuits,
		heightoffset,colorscheme,

		stationRaised,

		month,day,year;

	char tmpstr[32];

#if 1
	HWND testhndl;
	int j;
#endif

	short ridelow, ridehigh;

	short 
		fixbreakdown,raiselower,renew,makereliable,bury,
		excavate,zeroClearance,
		toggleVisibility,
		toggleChain
		;

	/*
	RMCHK_FIXBREAKDOWN,
	RMCHK_RENEW,
	RMCHK_MAKERELIABLE,
	RMCHK_RAISELOWER,
	RMCHK_BURY
	*/
	
	#define GetCBData(i)	\
		SendMessage	\
		(	dropDownList[i].pulldown.hwnd,CB_GETITEMDATA,	\
			SendMessage(dropDownList[i].pulldown.hwnd,CB_GETCURSEL,0,0),0	\
		)
	{	index=GetCBData(RMDDL_RIDESELECT);
		tracktype=GetCBData(RMDDL_TRACKTYPE);
		traintype=GetCBData(RMDDL_TRAINTYPE);
		opmode=GetCBData(RMDDL_OPERMODE);
		colorscheme=GetCBData(RMDDL_COLORSCHEME);
	}
	#undef GetCBData

	ridearray=RCT2_ADDR_RIDES;
	if(!WinRead(mainWindow,RCT2_TITLE,&ride,&(ridearray[index]),sizeof(ride))) return FALSE;
	
	#define GetItemText(a) \
		GetDlgItemText(hdlg,valueBox[a].valueBtn.ID,&tmpstr,sizeof(tmpstr));
	#define DoAtoi \
		atoi(&tmpstr)
	{
		GetItemText(RMVB_CIRCUITS);
		circuits=DoAtoi;
		GetItemText(RMVB_RAISELOWEROFFSET);
		heightoffset=DoAtoi;
		GetItemText(RMVB_LAUNCHSPEED);
		launchspeed=DoAtoi;
		GetItemText(RMVB_LIFTSPEED);
		liftspeed=DoAtoi;
		GetItemText(RMVB_NUMTRAINS);
		numtrains=DoAtoi;
		GetItemText(RMVB_NUMCARS);
		numcars=DoAtoi;
		GetItemText(RMVB_RIDEAGE);
		rideage=DoAtoi;
	}
	#undef DoAtoi
	#undef GetItemText

	GetDate(&day,&month,&year);
	curAbsMonth=(year<<3)|month;

	buildAbsMonth=curAbsMonth-(rideage<<3);

/*
		traintype,
		opmode,
		tracktype,
		launchspeed,
		liftspeed,
		numtrains,
		numcars,
		buildAbsMonth,
		curAbsMonth,
		circuits,
		heightoffset,
		colorscheme,
*/

	//*255/573
	//*573/255
	
	ride.trackType=tracktype;
	ride.vehiObjID=traintype;
	ride.opmode=opmode;
	ride.launchSpeed=launchspeed*HIGHSPEED_BYTE/HIGHSPEED_MPH;
	ride.liftChainSpeed=liftspeed;
	ride.amtTrains=ride.reqAmtTrains=numtrains;
	ride.amtCarsPerTrain=ride.reqAmtCarsPerTrain=numcars;
	ride.absBuiltMonth=buildAbsMonth;
	ride.numCircuits=circuits;

	/*
	RMCHK_FIXBREAKDOWN,
	RMCHK_RENEW,
	RMCHK_MAKERELIABLE,
	RMCHK_RAISELOWER,
	RMCHK_BURY
	*/

	#define ReadCheck(a) \
		(SendMessage(checkBox[a].hwnd,BM_GETCHECK,0,0)==BST_CHECKED)
	{	
		fixbreakdown=ReadCheck(RMCHK_FIXBREAKDOWN,);
		raiselower=ReadCheck(RMCHK_RAISELOWER);
		renew=ReadCheck(RMCHK_RENEW);
		makereliable=ReadCheck(RMCHK_MAKERELIABLE);
		bury=ReadCheck(RMCHK_BURY);
		excavate=ReadCheck(RMCHK_EXCAVATE);
		zeroClearance=ReadCheck(RMCHK_ZEROCLEARANCE);
		toggleVisibility=ReadCheck(RMCHK__TOGGLE_VISIBLE);
		toggleChain=ReadCheck(RMCHK__TOGGLE_CHAIN);
	}
	#undef ReadCheck
////

	if(fixbreakdown)
	{
		//fix ride breakdown
	}
	if(renew)
	{	ride.absBuiltMonth=curAbsMonth;
		ride.reliability=100;
	}
	if(makereliable)
	{	ride.reliability=100;
	}
	if(raiselower&&(heightoffset!=0))
	{
		heightoffset=heightoffset*2;

		GetRideLowHighHeights(index,colorscheme,&ridelow,&ridehigh);

		heightoffset=max(2-ridelow,heightoffset);
		heightoffset=min(255-ridehigh,heightoffset);

		switch(colorscheme)
		{
		case COLORCSCHEME_STATIONENTRY:
			//RaiseStationEntry(index,heightoffset);
			break;
		case COLORCSCHEME_ALT(1):
		case COLORCSCHEME_ALT(2):
		case COLORCSCHEME_ALT(3):
		case COLORCSCHEME_MAIN:
			RaiseLowerRide(index,heightoffset
				,colorscheme,&stationRaised);
			//SetRideHeightOffsets(&ride,heightoffset);
			break;
		}		

		
	}

	if(bury)
	{
		BuryRide(index,colorscheme);
		//bury ride
	}
	else{if(excavate)
		ExcavateRide(index,colorscheme);
	}
	
	if(zeroClearance)
	{	MakeRideZeroClearance(index,colorscheme);
	}


	if(toggleVisibility)
	{	
		ToggleRideVisibility(index,colorscheme);
	}
		
	if(toggleChain)
	{	
		ToggleRideLiftChain(index,colorscheme);
	}

	//\
	ToggleRideVisibility(index,colorscheme);\
	ToggleRideLiftChain(index,colorscheme);


	if(!WinWrite(mainWindow,RCT2_TITLE,&(ridearray[index]),&ride,sizeof(ride))) 
		return FALSE;
}

		
int CALLBACK RideMenuDlgProc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam)
{	
	int i,j,lerror;

	static short init=FALSE;

	short dobreak=FALSE;
	
	char tmpstr[16];

	RIDESTRUCT ride,*rideArray;

	char tmpStr[2][64];

	#define RIDESELECTFORMAT "%03.3d--%s"

	switch(msg)
	{
	case WM_INITDIALOG:
		
		init=FALSE;
		if (!init)
		{
			rideArray=RCT2_ADDR_RIDES;

			for(i=0;i<NUMRIDES;i++)
			{	
				if(WinRead(mainWindow,RCT2_TITLE,&ride,&(rideArray[i]),sizeof(ride))) 
				{
					if(ride.trackType==RCT2_BYTE_EMPTY)
						goto TMPSTR0_EQU_0;						
					else //if((ride.nameStringIndex&0xf000)==0x8000)
					{
						GetRCT2NameString(tmpStr[0],ride.nameStringIndex&0x03ff);
						tmpStr[0][0x30]=0;
						sprintf(tmpStr[1],"\"%s\"",tmpStr[0]);
						strcpy(tmpStr[0],tmpStr[1]);
					}
					//else
					//	strcpy(tmpStr[0],"<default name>");						
				}
				else
				TMPSTR0_EQU_0:
					strcpy(tmpStr[0],RN_NOTUSED);

				sprintf
				(	&RideSelectStrings[i].caption,RIDESELECTFORMAT,
					(RideSelectStrings[i].data=i),tmpStr[0]
				);
			}
			for(i=0;i<NUMVEHICLES ;i++)
			{	TrainTypes[i].data=i;
			}
							
			init=TRUE;
		}

		GetVehicleNames();
		

		for(i=0;i<NUMRIDEMENUDROPDOWNLISTS;i++)
		{	
			dropDownList[i].pulldown.hwnd=
				GetDlgItem(hdlg,dropDownList[i].pulldown.ID);
			SendMessage(dropDownList[i].pulldown.hwnd,CB_RESETCONTENT,0,0); 
		
			for(j=0;j<dropDownList[i].numentries;j++)
			{	
				SendMessage
				(	dropDownList[i].pulldown.hwnd,CB_ADDSTRING,0,
					&dropDownList[i].entry[j].caption
				);
				if((lerror=GetLastError())!=0)
					SetLastError(0);

				SendMessage
				(	dropDownList[i].pulldown.hwnd,CB_SETITEMDATA,j,
					dropDownList[i].entry[j].data
				);
				if((lerror=GetLastError())!=0)
					SetLastError(0);

				dropDownList[i].entry[j].data=
					SendMessage
					(	dropDownList[i].pulldown.hwnd,CB_GETITEMDATA,j,
						0
					);

			}
////
		}

		for(i=0;i<NUMRIDEMENUCHECKBOXES;i++)
		{	checkBox[i].hwnd=GetDlgItem(hdlg,checkBox[i].ID);
		}

		for(i=0;i<NUMRIDEMENUVALUEBOXES;i++)
		{	valueBox[i].valueBtn.hwnd=GetDlgItem(hdlg,valueBox[i].valueBtn.ID);
			valueBox[i].plusBtn.hwnd=GetDlgItem(hdlg,valueBox[i].plusBtn.ID);
			valueBox[i].minusBtn.hwnd=GetDlgItem(hdlg,valueBox[i].minusBtn.ID);
			itoa(valueBox[i].value,&tmpstr,10);
			SetDlgItemText(hdlg,valueBox[i].valueBtn.ID,&tmpstr);
		}

		for(i=0;i<NUMCAPTIONS;i++)
		{	CaptionBox[i].hwnd=GetDlgItem(hdlg,CaptionBox[i].ID);
		}

		return TRUE;
	case WM_COMMAND:
		dobreak=FALSE;
		if(init)
		{
			
			if(!dobreak)
				
				for(i=0;i<NUMRIDEMENUVALUEBOXES;i++)
				{	dobreak=ChangePlusMinus(hdlg,&valueBox[i],wparam);
					if(dobreak)break;
				}

			if(!dobreak)
			{	if(LOWORD(wparam)==dropDownList[RMDDL_RIDESELECT].pulldown.ID)
				{	if(HIWORD(wparam)==CBN_SELCHANGE)
					{	RideChangeProc
						(	hdlg,
							SendMessage
							(	dropDownList[RMDDL_RIDESELECT].pulldown.hwnd,
								CB_GETITEMDATA,
								SendMessage
								(	dropDownList[RMDDL_RIDESELECT].pulldown.hwnd,
									CB_GETCURSEL,0,0						
								),0
							)
						);
					}
				}				
			}
			if(dobreak)
				return FALSE;
		}

		switch(LOWORD(wparam))
		{ 
		case ID_APPLY:
			dobreak=TRUE;
		case IDOK:
			
			ApplyChanges(hdlg);
			
			if(dobreak) 
				return FALSE;
		case IDCANCEL:
			EndDialog(hdlg,0);
			return FALSE;
			;
		default:
			return FALSE;
		}
	default:
		return FALSE;		
	}
}
