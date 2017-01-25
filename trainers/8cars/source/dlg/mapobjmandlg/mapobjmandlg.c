//mapobjmandlg.c
 
#include <windows.h>
#include "mapobjmandlg.H"
#include "../../resource.h"
#include <stddlg.h>
#include "../../rct2.h"
#include "../../8cars.h"
#include <stdlib2.h>
#include "../../parkstatus/parkstatus.h"
#include "../../mapfuncs/mapfuncs.h"
#include<codeshortcuts.h>

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

/*
#define IDC_CHECK_WATER                 1075

  
#define IDC_CHECK_LAND                  1076
#define IDC_CHECK_REDCLAY               1078
#define IDC_CHECK_TANDIRT               1079
#define IDC_CHECK_BROWNDIRT             1080
#define IDC_CHECK_GRASSDIRT             1087
#define IDC_CHECK_GRASS                 1088
#define IDC_CHECK_ROCK                  1089
#define IDC_CHECK_SAND                  1093
#define IDC_CHECK_REDROCK               1094
#define IDC_CHECK_CHECKER               1095
#define IDC_CHECK_SNOW                  1096
#define IDC_CHECK_REDGRID               1097
#define IDC_CHECK_YELLOWGRID           1098
#define IDC_CHECK_PURPLEGRID           1101
#define IDC_CHECK_GREENGRID            1102

#define IDC_CHECK_SIDE_DIRT             1081
#define IDC_CHECK_SIDE_BROWNWOOD        1082
#define IDC_CHECK_SIDE_BLACKWOOD        1083
#define IDC_CHECK_SIDE_ICE              1084

#define IDC_HEIGHTOFFSET                1085
#define IDC_HEIGHTOFFSET_PLUS           1086
#define IDC_HEIGHTOFFSET_MINUS          1090

*/

CBENTRY
landTypeDropListEntries[]
=
{
	{"Grass",0},
	{"Sand",1},
	{"Brown Dirt",2},
	{"Black Rock",3},
	{"Redrock",4},
	{"Checker",5},
	{"Grass/Dirt",6},
	{"Snow",7},
	{"Red Grid",8},
	{"Yellow Grid",9},
	{"Purple Grid",10},
	{"Green Grid",11},
	{"Red Clay",12},
	{"Tan Dirt",13},
};



typedef enum
{
	MOM_OTCHK_RIDETRACK=0,
	MOM_OTCHK_SMALLSCENERY,
	MOM_OTCHK_LARGESCENERY,
	MOM_OTCHK_WALLS,
	MOM_OTCHK_PATHBANNER,
	MOM_OTCHK_PATHENTRANCE,
	MOM_OTCHK_WATER,
	MOM_OTCHK_LAND,
	MOM_OTCHK_PATH,
	MOM__OTCHK__NULL_ITEMS,
	NUMOBJTYPECHECKBOXES,
} MOM_OBJECTTYPECHECKBOX;


CONTROLBOXDATA objTypeCheckBox[]=
{
	{IDC_CHECK_RIDETRACK,NULL},
	{IDC_CHECK_SMALLSCENERY,NULL},
	{IDC_CHECK_LARGESCENERY,NULL},
	{IDC_CHECK_WALLS,NULL},
	{IDC_CHECK_PATHBANNER,NULL},
	{IDC_CHECK_PARKENTRANCE,NULL},
	{IDC_CHECK_WATER,NULL},
	{IDC_CHECK_LAND,NULL},
	{IDC_CHECK_PATH,NULL},
	{IDC__CHECK__NULL_ITEMS,NULL},
};

enum 
{
	DRPDN__NEW_LAMD_TYPE,
	NUM_DROP_DOWN_BOXES
};

#define NUM_TERRAIN_TEXTURES 14

DROPDOWNBOX objTypeDropListBox[]=
{
	{	{IDC__DROP_LIST__NEW_LAND_TYPE,NULL}
		,NUM_TERRAIN_TEXTURES
		,&landTypeDropListEntries[0]
	},
};

#define objTypeDropListBox_Entries \
	(sizeof(objTypeDropListBox)/sizeof(DROPDOWNBOX))

/*
typedef enum
{
	SLTF_GRASS			=1<<0,
	SLTF_SAND			=1<<1,		
	SLTF_BROWNDIRT		=1<<2,
	SLTF_BLACKROCK		=1<<3,
	SLTF_REDROCK		=1<<4,

	SLTF_CHECKER		=1<<5,
	SLTF_GRASSDIRT		=1<<6,
	SLTF_SNOW			=1<<7,
	SLTF_REDGRID		=1<<8,
	SLTF_YELLOWGRID		=1<<9,
	SLTF_PURPLEGRID		=1<<A,
	SLTF_GREENGRID		=1<<B,
	SLTF_REDCLAY		=1<<C,
	SLTF_TANDIRT		=1<<D
}	SURFACLANDTYPEFLAG;

*/

typedef enum
{
	MOM_LTCHK_GRASS=0,
	MOM_LTCHK_SAND,
	MOM_LTCHK_BROWNDIRT,
	MOM_LTCHK_ROCK,
	MOM_LTCHK_REDROCK,
	MOM_LTCHK_CHECKER,
	MOM_LTCHK_GRASSDIRT,
	MOM_LTCHK_SNOW,
	MOM_LTCHK_REDGRID,
	MOM_LTCHK_YELLOWGRID,
	MOM_LTCHK_PURPLEGRID,
	MOM_LTCHK_GREENGRID,
	MOM_LTCHK_REDCLAY,
	MOM_LTCHK_TANDIRT
} MOM_LANDTYPECHECKBOX;

#define NUMLANDTYPECHECKBOXES (MOM_LTCHK_TANDIRT+1)

CONTROLBOXDATA landTypeCheckBox[]=
{
	{IDC_CHECK_GRASS,NULL},
	{IDC_CHECK_SAND,NULL},
	{IDC_CHECK_BROWNDIRT,NULL},
	{IDC_CHECK_ROCK,NULL},
	{IDC_CHECK_REDROCK,NULL},
	{IDC_CHECK_CHECKER,NULL},
	{IDC_CHECK_GRASSDIRT,NULL},
	{IDC_CHECK_SNOW,NULL},
	{IDC_CHECK_REDGRID,NULL},
	{IDC_CHECK_YELLOWGRID,NULL},
	{IDC_CHECK_PURPLEGRID,NULL},
	{IDC_CHECK_GREENGRID,NULL},
	{IDC_CHECK_REDCLAY,NULL},
	{IDC_CHECK_TANDIRT,NULL}
};

typedef enum
{
	MOM_ETCHK_SIDE_DIRT,
	MOM_ETCHK_SIDE_BROWNWOOD,
	MOM_ETCHK_SIDE_BLACKWOOD,
	MOM_ETCHK_SIDE_ICE
} MOM_EDGETYPECHECKBOX;

#define NUMEDGETYPECHECKBOXES (MOM_ETCHK_SIDE_ICE+1)

CONTROLBOXDATA edgeTypeCheckBox[]=
{
	{IDC_CHECK_SIDE_DIRT,NULL},
	{IDC_CHECK_SIDE_BROWNWOOD,NULL},
	{IDC_CHECK_SIDE_BLACKWOOD,NULL},
	{IDC_CHECK_SIDE_ICE,NULL}
};

enum 
{
	MOM_ACHK_ACTION_RAISELOWER=0,
	MOM_ACHK_ACTION_REMOVE,
	MOM_ACHK_ACTION__CHANGE_LAND_TYPE,
	NUMACTIONCHECKBOXES
};


CONTROLBOXDATA actionCheckBox[]=
{
	{IDC_CHECK_ACTION_RAISELOWER,NULL},
	{IDC_CHECK_ACTION_REMOVE,NULL},
	{IDC__CHECK__ACTION__CHANGE_LAND_TYPE,NULL},
};

#define EN_LOSTFOCUS EN_KILLFOCUS


//IDC_HEIGHTOFFSET_PLUS


PLUSMINUSBOX raiseLowerBox=
{	{IDC_RAISELOWER_HEIGHTOFFSET_EDIT,NULL},{IDC_RAISELOWER_HEIGHTOFFSET_PLUS,NULL},{IDC_RAISELOWER_HEIGHTOFFSET_MINUS,NULL},0,-127,127
};

typedef enum {HR_LOW=0,HR_HIGH} HEIGHTRANGE_INDEX;

#define NUMHEIGHTRANGEINDEXES (HR_HIGH+1)

PLUSMINUSBOX heightRangeBox[]=
{	
	{{IDC_HEIGHTRANGE_LOW_EDIT,NULL},{IDC_HEIGHTRANGE_LOW_PLUS,NULL},{IDC_HEIGHTRANGE_LOW_MINUS,NULL},0,0,255},
	{{IDC_HEIGHTRANGE_HIGH_EDIT,NULL},{IDC_HEIGHTRANGE_HIGH_PLUS,NULL},{IDC_HEIGHTRANGE_HIGH_MINUS,NULL},255,0,255}
};

HWND hLocDlg;

int ApplyProc()
{	
	int i;
	WORD 
		edgeFlags=0,
		groundFlags=0,
		objFlags=0,
		actionFlags=0,

		lowHeight,
		highHeight;

	WORD 
		newLandType;

	short
		offset;

	#define ReadCheck(b,a) \
	(SendMessage(b[a].hwnd,BM_GETCHECK,0,0)==BST_CHECKED)
	#define SetBit(a,b) (a=a|(1<<b))
	{
		for(i=0;i<NUMOBJTYPECHECKBOXES;i++)
		{	
			if(ReadCheck(objTypeCheckBox,i))
				SetBit(objFlags,i);
		}

		for(i=0;i<NUMLANDTYPECHECKBOXES;i++)
		{	
			if(ReadCheck(landTypeCheckBox,i))
				SetBit(groundFlags,i);
		}


		for(i=0;i<NUMEDGETYPECHECKBOXES;i++)
		{	
			if(ReadCheck(edgeTypeCheckBox,i))
				SetBit(edgeFlags,i);

		}
		for (i=0;i<NUMACTIONCHECKBOXES;i++)
		{
			if(ReadCheck(actionCheckBox,i))
				SetBit(actionFlags,i);
		}
	}
	#undef SetBit
	#undef ReadCheck

	offset=raiseLowerBox.value;
	lowHeight=heightRangeBox[HR_LOW].value;
	highHeight=heightRangeBox[HR_HIGH].value;

	#define BitFlag(n) (1<<n)

	if(actionFlags&(BitFlag(MOM_ACHK_ACTION_RAISELOWER))) 
	{	
		if
		(	MessageBox(hLocDlg,"This will change the height of the specified objects. Press OK to proceed",
				"Confirmation",MB_APPLMODAL|MB_OKCANCEL|MB_SETFOREGROUND)
			==IDOK
		)
			return RaiseLowerObjects(objFlags,groundFlags,edgeFlags,lowHeight,highHeight,offset);
	}
	if(actionFlags&(BitFlag(MOM_ACHK_ACTION_REMOVE))) 
	{
		if
		(	MessageBox(hLocDlg,"This will remove the specified objects. Press OK to proceed",
				"Confirmation",MB_APPLMODAL|MB_OKCANCEL|MB_SETFOREGROUND)
			==IDOK
		)
			return RemoveObjects(objFlags,groundFlags,edgeFlags,lowHeight,highHeight);
	}
	if(actionFlags&(BitFlag(MOM_ACHK_ACTION__CHANGE_LAND_TYPE))) 
	{
		i=
			SendMessage
			(	objTypeDropListBox[DRPDN__NEW_LAMD_TYPE].pulldown.hwnd
				,CB_GETCURSEL,0,0		
			);
		newLandType=
			SendMessage
			(	objTypeDropListBox[DRPDN__NEW_LAMD_TYPE].pulldown.hwnd
				,CB_GETITEMDATA,i,0		
			);
		if
		(	MessageBox(hLocDlg,"This will change the land type of specified objects. Press OK to proceed",
				"Confirmation",MB_APPLMODAL|MB_OKCANCEL|MB_SETFOREGROUND)
			==IDOK
		)
			return ChangeLandType(newLandType,groundFlags,edgeFlags);
	}
}

int CALLBACK MapObjectManipulationDlgProc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam)
{
	short i,j,dobreak;

	static WORD init=FALSE;

	char tmpstr[32];

	switch(msg)
	{
	case WM_INITDIALOG:

		hLocDlg=hdlg;

		for(i=0;i<NUMOBJTYPECHECKBOXES;i++)
		{	objTypeCheckBox[i].hwnd=GetDlgItem(hdlg,objTypeCheckBox[i].ID);
		}

		for_i0(i,NUM_DROP_DOWN_BOXES)
		{
			objTypeDropListBox[i].pulldown.hwnd=
				GetDlgItem(hdlg,objTypeDropListBox[i].pulldown.ID);
			objTypeDropListBox[i].entry=&landTypeDropListEntries;

			for(j=0;j<NUM_TERRAIN_TEXTURES;j++)
			{
				SendMessage
				(	objTypeDropListBox[i].pulldown.hwnd
					,CB_ADDSTRING,0
					,landTypeDropListEntries[j].caption
				);
				SendMessage
				(	objTypeDropListBox[i].pulldown.hwnd
					,CB_SETITEMDATA
					,j
					,landTypeDropListEntries[j].data
				);
			}
		}

		for(i=0;i<NUMLANDTYPECHECKBOXES;i++)
		{	landTypeCheckBox[i].hwnd=GetDlgItem(hdlg,landTypeCheckBox[i].ID);
		}

		for(i=0;i<NUMEDGETYPECHECKBOXES;i++)
		{	edgeTypeCheckBox[i].hwnd=GetDlgItem(hdlg,edgeTypeCheckBox[i].ID);
		}

		for(i=0;i<NUMACTIONCHECKBOXES;i++)
		{	actionCheckBox[i].hwnd=GetDlgItem(hdlg,actionCheckBox[i].ID);	
		}

		if(TRUE)
			InitPlusMinus(hdlg,&raiseLowerBox);
		for (i=HR_LOW;i<NUMHEIGHTRANGEINDEXES;i++)
			InitPlusMinus(hdlg,&heightRangeBox[i]);
		
		return TRUE;
	case WM_COMMAND:

		dobreak=FALSE;

		if(!dobreak)
		{	dobreak=ChangePlusMinus(hdlg,&raiseLowerBox,wparam);
		}
		if(!dobreak)
		{	for (i=HR_LOW;i<NUMHEIGHTRANGEINDEXES;i++)
				dobreak=ChangePlusMinus(hdlg,&heightRangeBox[i],wparam);
		}		
		if(dobreak)
			return FALSE;			
		
		switch(LOWORD(wparam))
		{
		case IDOK:
		case IDAPPLY:
			ApplyProc();
			
			if(LOWORD(wparam)==IDAPPLY)
				break;
		case IDCANCEL:
			EndDialog(hdlg,0);
			return FALSE;
		default:
			return FALSE;
		}

	default:
		return FALSE;		
	}
}