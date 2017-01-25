#include <windows.h>
#include "../../resource.h"
#include <stddlg.h>
#include <stdlib2.h>
#include "peepColor.h"
#include "../../spritefuncs/spritefuncs.h""

#define RGB_BLACK (RGB(0,0,0))
#define RGB_WHITE (RGB(255,255,255))

BYTE shirtIndex,pantsIndex;

/* 
	IDC_SHIRTCOLOR
	IDC_PANTSCOLOR
*/
//typedef struct{CONTROLBOXDATA pulldown;int numentries;CBENTRY *entry;}
//	DROPDOWNBOX;

UINT CX_COLORRECT,CY_COLORRECT;

CBENTRY colorListEntries[32];

typedef struct{BYTE red,green,blue,index;} PALETTEENTRY_B;
static PALETTEENTRY_B colorPalette[32]=
{
	{47,67,67,0},
	{111,131,131,1},
	{183,195,195,2},
	{63,67,119,3},
	{119,119,175,4},
	{135,83,187,5},
	{15,67,187,6},
	{67,135,227,7},
	{143,211,243,8},
	{43,147,143,9},
	{131,207,207,10},
	{31,123,0,11},
	{79,135,95,12},
	{99,143,59,13},
	{71,175,39,14},
	{135,159,95,15},
	{135,139,59,16},
	{255,231,47,17},
	{215,167,52,18},
	{143,83,7,19},
	{255,111,23,20},
	{183,71,0,21},
	{179,131,67,22},
	{127,87,31,23},
	{123,103,75,24},
	{207,131,99,25},
	{163,59,59,26},
	{143,0,0,27},
	{227,7,0,28},
	{143,23,79,29},
	{219,59,143,30},
	{235,159,159,31}
};


typedef enum
{
	PIU_OVERRIDEPURCHASE=0
} PEEPSINUNIFORM_CHECKBOX;

#define NUM_PIU_OVERRIDEPURCHASE (PIU_OVERRIDEPURCHASE+1)

CONTROLBOXDATA checkBoxes[]=
{	
	{IDC_OVERRIDEPURCHASECHECK,NULL}
};
#define numCheckBoxes (sizeof(checkBoxes)/sizeof(CONTROLBOXDATA))

DROPDOWNBOX cbArray[2]=
{
	{{IDC_SHIRTCOLOR,NULL},32,&colorListEntries[0]},
	{{IDC_PANTSCOLOR,NULL},32,&colorListEntries[0]}
};

#define cbArray_Entries (sizeof(cbArray)/sizeof(DROPDOWNBOX))

POINT startXY[2]={{75,18},{75,39}};
RECT drawBoxRect;
UINT drawBoxWidth;
BYTE *clothesIndex[2];

int UniPeepColorInitProc(HWND hdlg)
{
	UINT i,j;

	RECT curWinRect,clientRect;

	shirtIndex=pantsIndex=0;

	GetWindowRect(hdlg,&clientRect);

	for(i=0;i<32;i++)
	{
		memset
		(	colorListEntries[i].caption,0,
			sizeof(colorListEntries[i].caption)
		);
		colorListEntries[i].data=i;		
	}

	for(i=0;i<numCheckBoxes;i++)
	{
		checkBoxes[i].hwnd=GetDlgItem(hdlg,checkBoxes[i].ID);
	}

	clothesIndex[0]=&shirtIndex;
	clothesIndex[1]=&pantsIndex;

	for(i=0;i<cbArray_Entries;i++)
	{	

		cbArray[i].pulldown.hwnd=
			GetDlgItem(hdlg,cbArray[i].pulldown.ID);
		cbArray[i].entry=&colorListEntries;

		for(j=0;j<32;j++)
		{
			SendMessage
			(	cbArray[i].pulldown.hwnd,CB_ADDSTRING,0,""	);
		}
	}
	GetClientRect(cbArray[0].pulldown.hwnd,&clientRect);
	CX_COLORRECT=clientRect.right;
	CY_COLORRECT=clientRect.bottom;
}

UINT GetPicIndex(hdlg,x,y)
{
	int i;

	for(i=0;i<cbArray_Entries;i++)
	{	
		if(	inrange(y,startXY[i].y,startXY[i].y+10)
			&&inrange(x,startXY[i].x,startXY[i].x+383)	
		)
		{
			*clothesIndex[i]=(x-startXY[i].x)/12;			
			return i;			
		}
	}
	return 2;
}

//1
int UniPeepColorApplyProc()
{
	int i,curSel,overridePurchaces;

	for(i=0;i<cbArray_Entries;i++)
	{	
		if 
		(	(	*clothesIndex[i]=
				SendMessage(cbArray[i].pulldown.hwnd,CB_GETCURSEL,0,0)
			)
			==CB_ERR
		) return FALSE;
	}

	#define ReadCheck(a) \
		(SendMessage(checkBoxes[a].hwnd,BM_GETCHECK,0,0)==BST_CHECKED)
	{	
		overridePurchaces=ReadCheck(PIU_OVERRIDEPURCHASE);
	}
	#undef ReadCheck

	PutPeepsInUniform(shirtIndex,pantsIndex,overridePurchaces);

	return TRUE;
}

#define GetBackground(state) (state&ODS_SELECTED?	\
	COLOR_HIGHLIGHT:COLOR_WINDOW)
#define GetForeground(state) (state&ODS_SELECTED?	\
	COLOR_HIGHLIGHTTEXT:COLOR_WINDOWTEXT)

int CALLBACK UniformPeepColorProc
(	HWND hdlg,UINT msg,
	WPARAM wparam,LPARAM lparam
)
{	
	int x,y,index;
	LPMEASUREITEMSTRUCT lpmis;
	LPDRAWITEMSTRUCT lpdis;
	HBITMAP curColorImage;
	COLORREF clrForeground,clrBackground;
	TEXTMETRIC tm;
	HBRUSH drawBrush;
	int result,lerror;
	RECT drawRect;

	switch(msg)
	{
	case WM_INITDIALOG:
		UniPeepColorInitProc(hdlg);
		return TRUE;
	case WM_MEASUREITEM: 
		lpmis=(LPMEASUREITEMSTRUCT)lparam; 

		//if (lpmis->itemHeight<CY_COLORRECT) 
		//	lpmis->itemHeight=CY_COLORRECT; 
		return FALSE;
	case WM_DRAWITEM: 
		lpdis=(LPDRAWITEMSTRUCT)lparam; 
        if (lpdis->itemID == -1)            /* empty item */ 
            break; 
		//curColorImage=colorImages[lpdis->itemData].hbm;

		clrForeground=
			SetTextColor(lpdis->hDC,GetForeground(lpdis->itemState));
		clrBackground=
			SetBkColor(lpdis->hDC,GetBackground(lpdis->itemState)); 

        /* Calculate the vertical and horizontal position. */ 

        GetTextMetrics(lpdis->hDC, &tm); 
        y=(lpdis->rcItem.bottom+lpdis->rcItem.top-tm.tmHeight)
			/2; 
        x=LOWORD(GetDialogBaseUnits())/4; 

		//SelectObject(hdc, hbmIcon); 

		//BitBlt(lpdis->hDC, x, lpdis->rcItem.top + 1, 
		//	CX_COLORRECT, CY_COLORRECT, hdc, 0, 0, SRCPAINT); 

		drawRect.left=lpdis->rcItem.left+1;
		drawRect.top=lpdis->rcItem.top+1;
		drawRect.right=lpdis->rcItem.right;
		drawRect.bottom=lpdis->rcItem.bottom;

		drawBrush=
			CreateSolidBrush
			(	RGB
				(	
					colorPalette[lpdis->itemID].red,
					colorPalette[lpdis->itemID].green,
					colorPalette[lpdis->itemID].blue,
				)
			);

		//SelectObject(lpdis->hDC,drawBrush);

		result=FillRect(lpdis->hDC,&drawRect,drawBrush);
		lerror=GetLastError();

		DeleteObject(drawBrush);

		/* If the item has the focus, draw focus rectangle. */ 
		
		
		if
		(	(lpdis->itemState&(ODS_COMBOBOXEDIT|ODS_FOCUS))
			&&(lpdis->hwndItem==GetFocus())
		)
		{
			drawBrush=CreateSolidBrush(RGB_BLACK);
			//SelectObject(lpdis->hDC,drawBrush);
		}
		else
		{
			drawBrush=CreateSolidBrush(RGB_WHITE);
		}
		result=FrameRect(lpdis->hDC,&drawRect,drawBrush);
		lerror=GetLastError();

		DeleteObject(drawBrush);
 		
		return FALSE;
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDAPPLY:
		case IDOK:
			UniPeepColorApplyProc();
			if((LOWORD(wparam))==IDAPPLY)
				return FALSE;
		case IDCANCEL:
			EndDialog(hdlg,0);
			return FALSE;
			;
		default:
			return FALSE;
		};
	default:
		return FALSE;		
	}
}

