 
#include <windows.h>
#include "staffdlg.h"
#include "../../resource.h"
#include <stddlg.h>
#include "../../rct2.h"
#include "../../8cars.h"
#include <stdlib2.h>
#include "../../parkstatus/parkstatus.h"
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

#define STAFFSELECTFORMAT "%03.3d--%s"

typedef enum 
{	SMDDL_STAFFSELECT=0,
	SMDDL_STAFFTYPESELECT
} STAFFMENUDROPDOWNLIST;


#define NUMSTAFFMENUDROPDOWNLISTS (SMDDL_STAFFTYPESELECT+1)

#define NUMSTAFF 512
DWORD numStaff=0;

CBENTRY 
	StaffSelectStrings[NUMSTAFF],

	StaffTypes[]=
	{
		{"Handyman",0x01},
		{"Mechanic",0x2},
		{"Security",3},
		{"Panda",4},
		{"Tiger",5},
		{"Elephant entertainer",6},
		{"Roman entertainer",7},
		{"Gorilla entertainer",8},
		{"Snowman entertainer",9},
		{"Knight entertainer",0xa},
		{"Astronaut entertainer",0xb},
		{"Bandit entertainer",0xc},
		{"Sheriff entertainer",0xd},
		{"Pirate entertainer",0xe}
	};

	#define NUMSTAFFTYPES (sizeof(StaffTypes)/sizeof(CBENTRY))

//typedef struct{CONTROLBOXDATA pulldown;int numentries;CBENTRYARRAY *entry;}
//	DROPDOWNBOX;
/*
	IDC_STAFFSELECT,
	IDC_STAFFTYPESELECT,
	IDC_TRAINTYPE,
	IDC_OPERMODE
	IDC_COLORSCHEME

*/

DROPDOWNBOX SDLG_dropDownList[NUMSTAFFMENUDROPDOWNLISTS]=
{	{{IDC_STAFFSELECT,NULL},NUMSTAFF,&StaffSelectStrings},
	{{IDC_STAFFTYPESELECT,NULL},NUMSTAFFTYPES,&StaffTypes},
};

#define NUMCAPTIONS (sizeof(CaptionBox)/sizeof(CONTROLBOXDATA))


int StaffChangeProc(HWND hdlg,short index)
{	
	SPRITESTRUCT sprite,*spriteArray; 

	short 
		persongraphic;

	char tmpstr[64];

#if 1
	HWND testhndl;
	int j;
#endif

	spriteArray=RCT2_ADDR_SPRITES;

	if(!WinRead(mainWindow,RCT2_TITLE,&sprite,&(spriteArray[index]),sizeof(sprite))) return FALSE;

	persongraphic=sprite.personGraphic;

	ChangeDropDown(&SDLG_dropDownList[SMDDL_STAFFTYPESELECT],persongraphic,0);
}

int SDLG_ApplyChanges(HWND hdlg)
{	
	SPRITESTRUCT sprite,*spriteArray; 

	short 
		index,
		persongraphic;

	char tmpstr[64];

#if 1
	HWND testhndl;
	int j;
#endif

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
		(	SDLG_dropDownList[i].pulldown.hwnd,CB_GETITEMDATA,	\
			SendMessage(SDLG_dropDownList[i].pulldown.hwnd,CB_GETCURSEL,0,0),0	\
		)
	{	index=GetCBData(SMDDL_STAFFSELECT);
		persongraphic=GetCBData(SMDDL_STAFFTYPESELECT);
	}
	#undef GetCBData

	spriteArray=RCT2_ADDR_SPRITES;
	if(!WinRead(mainWindow,RCT2_TITLE,&sprite,&(spriteArray[index]),sizeof(sprite))) return FALSE;
	
	sprite.personGraphic=persongraphic;

	if(!WinWrite(mainWindow,RCT2_TITLE,&(spriteArray[index]),&sprite,sizeof(sprite))) 
		return FALSE;
}

//

int CALLBACK StaffMenuDlgProc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam)
{	
	int i,j,lerror;

	static short init=FALSE;

	short dobreak=FALSE;
	
	char tmpstr[16];
	
	switch(msg)
	{
	case WM_INITDIALOG:			  

		if (!init)
		{
			init=TRUE;
		}

		init=InitStaffList();

		for(i=0;i<NUMSTAFFMENUDROPDOWNLISTS;i++)
		{	
			SDLG_dropDownList[i].pulldown.hwnd=
				GetDlgItem(hdlg,SDLG_dropDownList[i].pulldown.ID);
			SendMessage(SDLG_dropDownList[i].pulldown.hwnd,CB_RESETCONTENT,0,0); 
		
			for(j=0;j<SDLG_dropDownList[i].numentries;j++)
			{	
				SendMessage
				(	SDLG_dropDownList[i].pulldown.hwnd,CB_ADDSTRING,0,
					&SDLG_dropDownList[i].entry[j].caption
				);
				if((lerror=GetLastError())!=0)
					SetLastError(0);

				SendMessage
				(	SDLG_dropDownList[i].pulldown.hwnd,CB_SETITEMDATA,j,
					SDLG_dropDownList[i].entry[j].data
				);
				if((lerror=GetLastError())!=0)
					SetLastError(0);

				SDLG_dropDownList[i].entry[j].data=
					SendMessage
					(	SDLG_dropDownList[i].pulldown.hwnd,CB_GETITEMDATA,j,
						0
					);
			}
////
		}

		return TRUE;
	case WM_COMMAND:
		dobreak=FALSE;
		if(init)
		{
			
			if(!dobreak)
				
				;

			if(!dobreak)
			{	if(LOWORD(wparam)==SDLG_dropDownList[SMDDL_STAFFSELECT].pulldown.ID)
				{	if(HIWORD(wparam)==CBN_SELCHANGE)
					{	StaffChangeProc
						(	hdlg,
							SendMessage
							(	SDLG_dropDownList[SMDDL_STAFFSELECT].pulldown.hwnd,
								CB_GETITEMDATA,
								SendMessage
								(	SDLG_dropDownList[SMDDL_STAFFSELECT].pulldown.hwnd,
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
			
			SDLG_ApplyChanges(hdlg);
			
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

#define PT_GUEST 0
#define PT_STAFF 1

int InitStaffList()
{
	DWORD listI,spriteIndex,count,strIndex;
	SPRITESTRUCT sprite,*spriteArray;
	SPRITESTATS spriteStats;
	char tmpBuff[128];

	numStaff=listI=0;

	if(!WinRead(mainWindow,RCT2_TITLE,&spriteStats,RCT2_ADDR_SPRITESTATS,sizeof(spriteStats))) return FALSE;

	spriteIndex=spriteStats.statsA.firstPerson;
	count=spriteStats.statsA.peopleCount;

	spriteArray=RCT2_ADDR_SPRITES;
	
	while(spriteIndex!=(DWORD)RCT2_WORD_EMPTY)
	{
		if(!WinRead(mainWindow,RCT2_TITLE,&sprite,&(spriteArray[spriteIndex]),sizeof(sprite))) return FALSE;

		if(sprite.persontype==PT_STAFF)
		{
			strIndex=sprite.textStringIndex;

			if((strIndex&0xf000)==0x8000)
			{
				GetRCT2NameString(tmpBuff,strIndex&0x3ff);
				tmpBuff[0x20]=0;
			}
			else 
				strcpy(tmpBuff,"<default name>");

			sprintf(&(StaffSelectStrings[listI].caption),STAFFSELECTFORMAT,listI,tmpBuff);
			StaffSelectStrings[listI].data=spriteIndex;

			if(numStaff<NUMSTAFF)
			{
				++numStaff;
				++listI;
			}
			else 
				goto EXITLINE;

		}
		spriteIndex=sprite.nextInClass;
	}

	EXITLINE:
		SDLG_dropDownList[SMDDL_STAFFSELECT].numentries=numStaff;
		return TRUE;
}
