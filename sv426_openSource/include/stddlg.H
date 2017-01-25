

#ifndef _STDDLG_
#define _STDDLG_
//put in all-purpose header-->

#include <windows.h>

#define EN_LOSTFOCUS EN_KILLFOCUS

typedef struct{int ID;HWND hwnd;}
	CONTROLBOXDATA;

typedef struct{CONTROLBOXDATA valueBtn,plusBtn,minusBtn;int value,low,high;} 
	PLUSMINUSBOX;

#define CBENTRYCAPTIONSIZE 64 

typedef struct{char caption[CBENTRYCAPTIONSIZE];short data;}		
	CBENTRY;

typedef struct{CONTROLBOXDATA pulldown;int numentries;CBENTRY *entry;}
	DROPDOWNBOX;

int FindCBData(HWND hComboBox,int data);

int ChangeDropDown(DROPDOWNBOX *dropdown,int value,int startindex);

int ChangePlusMinus(PLUSMINUSBOX *plusMinus,WPARAM wparam);
int InitPlusMinus(HWND hdlg,PLUSMINUSBOX *plusMinus);

int GetControlIndex_HWND(CONTROLBOXDATA *cbArray,UINT entries,HWND hwnd);
int GetControlIndex_ID(CONTROLBOXDATA *cbArray,UINT entries,int id);

//<--put in all-purpose header
#endif //_STDDLG_
