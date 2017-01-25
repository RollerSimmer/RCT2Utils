

#ifndef _DLGHEADER_
#define _DLGHEADER_
//put in all-purpose header-->

typedef struct{int ID;HWND hwnd;}
	CONTROLBOXDATA;

typedef struct{CONTROLBOXDATA valueBtn,plusBtn,minusBtn;int value;} 
	PLUSMINUSBOX;

typedef struct{char caption[64],int data}
	CBENTRY;
typedef CBENTRY CBENTRYARRAY[];

typedef struct{CONTROLBOXDATA pulldown;int numentries;CBENTRYARRAY entry;}
	DROPDOWNBOX;
//<--put in all-purpose header
#endif //_DLGHEADER_
