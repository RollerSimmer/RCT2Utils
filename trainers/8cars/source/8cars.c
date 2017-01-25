

#include <windows.h>
#include <COMMCTRL.H>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include "dll/8carsfunc.h"
#include "resource.h"
#include "process/process.h"
#include "rct2.h"
#include "terrfuncs/terrfuncs.h"
#include "mapfuncs/mapfuncs.h"
#include "8cars.h"
#include "weather/weather.h"
#include "moneyfuncs\moneyfuncs.h"
#include "messages/messages.h"
#include "parkstatus/parkstatus.h"
#include "dlg/ridedlg/ridedlg.h"
#include "dlg/mapobjmandlg/mapobjmandlg.H"
#include "guests/guestfuncs.h"

HINSTANCE _8carsFuncDllInst;

//GetProcAddress(_8carsFuncDllInst,"
//"))
//#define ~ (*(~*)GetProcAddress(_8carsFuncDllInst,"~"))
#define RCT2WINDOW (*(HWND*)GetProcAddress(_8carsFuncDllInst,"rct2Window"))
#define MAINMENU (*(HMENU*)GetProcAddress(_8carsFuncDllInst,"mainMenu"))
#define _8CARS_HINST (*(HINSTANCE*)GetProcAddress(_8carsFuncDllInst,"hinst"))
#define _8CARS_HACCEL (*(HACCEL*)GetProcAddress(_8carsFuncDllInst,"haccel"))
#define RCT2KEYBOARDHOOK (*(HHOOK*)GetProcAddress(_8carsFuncDllInst,"rct2KeyboardHook"))
#define RCT2THREADID (*(DWORD*)GetProcAddress(_8carsFuncDllInst,"rct2ThreadID"))
#define SAVEPATHADDR (GetProcAddress(_8carsFuncDllInst,"savepath"))

HACCEL _haccel;
HHOOK _Rct2KeyboardHook;
HWND _mainWindow;
int _Rct2Version;

//#define USE_REGHOTKEY
//#undef USE_KEYHOOK
#define USE_KEYHOOK
#undef TEST_CALCULATOR
//#define TEST_CALCULATOR

VOID CALLBACK _8carsTimerProc
(
	HWND  hwnd,	// handle of window for timer messages 
	UINT  msg,	// WM_TIMER message
	UINT  idEvent,	// timer identifier
	DWORD  dwTime 	// current system time
);

#ifdef USE_KEYHOOK
LRESULT CALLBACK RCT2KeyInterceptProc
(	int  code,	// hook code
	WPARAM  wparam,	// virtual-key code
	LPARAM  lparam 	// keystroke-message information
);
#endif // USE_KEYHOOK

RIDESTRUCT ride;
SPRITESTRUCT sprite;

LRESULT APIENTRY MainWndProc
(	HWND hwnd, 
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

void GetExeName(char *exeName,char *cmdLine,int maxLen)
{

}

int APIENTRY WinMain
(	HINSTANCE hinstance,
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine,
	int nCmdShow
) 
	{ 
    MSG msg;
    WNDCLASS wc;
    HWND hwnd;
	int lerror,procp;


	_8carsFuncDllInst=LoadLibrary("8carsfunc.dll");
	procp=GetProcAddress(_8carsFuncDllInst,"RCT2KeyInterceptProc");  

//	InitCommonControls(); 
	
	//save current path
	_getcwd(SAVEPATHADDR,128);
	
    wc.style = 0; 
    wc.lpfnWndProc = 
		(WNDPROC) 
		GetProcAddress(_8carsFuncDllInst,"MainWndProc"); 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = hinstance; 
    wc.hIcon = LoadIcon(hinstance, IDI_8CARS_ICON); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wc.hbrBackground = COLOR_BACKGROUND; 
    wc.lpszMenuName =  MAKEINTRESOURCE(IDR_MENU1); 
    wc.lpszClassName = "8CarsClass"; 
 
    if (!RegisterClass(&wc)) 
        return FALSE; 
 
    memcpy(GetProcAddress(_8carsFuncDllInst,"hinst"),&hinstance,sizeof(hinstance)); 

	if ((RCT2WINDOW=FindWindow(NULL,RCT2_TITLE))==NULL)
		MessageBox
		(	hwnd,"RCT2 is not loaded","Message",
			MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND			
			|MB_ICONWARNING
		);

	_Rct2Version=0;

	hwnd=
		CreateWindowEx
		(	
			0
			,			
			"8CarsClass"
			,
			_8CARS_WINDOWTITLE
			,
			WS_OVERLAPPEDWINDOW
			,
			100
			,
			50
			,
			500
			,
			45
			,
			NULL
			,
			NULL
			,
			hinstance
			,
			NULL
			
		);

	if (hwnd == NULL) 
        return FALSE; 
	_mainWindow=hwnd;

	MAINMENU=GetMenu(hwnd);
 
    ShowWindow(hwnd, nCmdShow); 
    UpdateWindow(hwnd); 

	//AboutBox(hwnd);

	_haccel=LoadAccelerators(_8CARS_HINST,MAKEINTRESOURCE(IDR_ACCELERATOR1));

	//_Rct2Version=GetRct2Version();

	RCT2THREADID=GetWindowThreadProcessId(RCT2WINDOW,NULL);
////
#ifndef TEST_CALCULATOR
	if(RCT2WINDOW!=NULL)
	{
#endif //TEST_CALCULATOR
		#ifdef USE_REGHOTKEY
		{
		}
		#endif
		#ifdef USE_KEYHOOK
		{
			#ifdef TEST_CALCULATOR
				RCT2THREADID=GetWindowThreadProcessId(FindWindow(NULL,"Calculator"),NULL);
			#endif //TEST_CALCULATOR

			if(	(	_Rct2KeyboardHook=
						SetWindowsHookEx
						(	WH_KEYBOARD,
							GetProcAddress(_8carsFuncDllInst,"RCT2KeyInterceptProc"),
							_8carsFuncDllInst,
							RCT2THREADID
						)
				)==NULL
			)
			{
				lerror=GetLastError(); 
			}
			#ifdef TEST_CALCULATOR
				RCT2THREADID=GetWindowThreadProcessId(RCT2WINDOW),NULL);
			#endif //TEST_CALCULATOR


			Set8carsDllLocals(_8CARS_WINDOWTITLE,_Rct2KeyboardHook,_haccel,_Rct2Version);
		}
		#endif

////
#ifndef TEST_CALCULATOR
	}
#endif //TEST_CALCULATOR

//	_8CarsTimer=SetTimer(_mainWindow,1,10,_8carsTimerProc);	
		
	cmdmsg("8 Cars per Trainer initialized");

	while (GetMessage(&msg, NULL, 0, 0)) 
	{ 
		if(!TranslateAccelerator(_mainWindow,_haccel,&msg))
		{	
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}    
	}

	UnhookWindowsHookEx(_Rct2KeyboardHook);
	FreeLibrary(_8carsFuncDllInst);

//	KillTimer(_mainWindow,1);

	cmdmsg("8 Cars per Trainer terminated");

    return 0;
        
} 


STARTUPINFO startup=
{	sizeof(STARTUPINFO),
	NULL,
	NULL,
	NULL,
	0,0,
	0,0,
	0,0,
	0,
	0,
	0,
	0,
	NULL,
	NULL,NULL,NULL
};



/*

HHOOK SetWindowsHookEx
(	int  idHook,	// type of hook to install
	HOOKPROC  lpfn,	// address of hook procedure
	HINSTANCE  hMod,	// handle of application instance
	DWORD  dwThreadId 	// identity of thread to install hook for 
);

*/
//#undef USE_REGHOTKEY



typedef struct 
{	int vkey1,vkey2;
	UINT msg;
	WPARAM wparam;
	LPARAM lparam;
} HOTKEYMESSAGE;


HOTKEYMESSAGE hotKeyMessages[]=
{		
	{VK_MENU,VK_F1,WM_COMMAND,ID_PARK_OPEN,NULL},
	{VK_MENU,VK_F2,WM_COMMAND,ID_PARK_CLOSE,NULL},
	{VK_MENU,VK_F3,WM_COMMAND,ID_MONEY_ADD5000CASH,NULL},	
	{VK_MENU,VK_F5,WM_COMMAND,ID_MONEY_SUBTRACT50000CASH,NULL},
	{VK_MENU,VK_F6,WM_COMMAND,ID_STAFF_BANKER_GIVEALLGUESTS100CASH,NULL},
	{VK_MENU,VK_F7,WM_COMMAND,ID_STAFF_ENTERTAINER_MAKEGUESTSHAPPY,NULL}
};

#define NUMHOTKEYMESSAGES \
	(sizeof(hotKeyMessages)/sizeof(HOTKEYMESSAGE))


VOID CALLBACK _8carsTimerProc
(
	HWND hwnd,	// handle of window for timer messages 
	UINT msg,	// WM_TIMER message
	UINT idEvent,	// timer identifier
	DWORD dwTime 	// current system time
)
{	
	char buffer[2][256];

	int i;

	if(idEvent==1)
		for(i=0;i<NUMHOTKEYMESSAGES;i++)
		{
			if
			(	(GetKeyState(hotKeyMessages[i].vkey1)&&0x80)
				&&(GetKeyState(hotKeyMessages[i].vkey2)&&0x80)
			)
			{
				if(GetActiveWindow()==RCT2WINDOW)
					PostMessage
					(	_mainWindow,
						hotKeyMessages[i].msg,
						hotKeyMessages[i].wparam,
						hotKeyMessages[i].lparam
					);
			}
		}
}

#undef USE_KEYHOOK


//VK_F1


/*
VIRTUAL KEY CODES
  
Decimal	Hex	WINDOWS.H Identifier	Required	IBM Keyboard

 1	01	VK_LBUTTON		
 2	02	VK_RBUTTON		
 3	03	VK_CANCEL	*	Ctrl-Break
 4	04	VK_MBUTTON		
 8	08	VK_BACK	*	Backspace
 9	09	VK_TAB	*	Tab
12	0C	VK_CLEAR		Numeric keypad 5 with Num Lock OFF
13	0D	VK_RETURN	*	Enter
16	10	VK_SHIFT	*	Shift
17	11	VK_CONTROL	*	Ctrl
18	12	VK_MENU	*	Alt
19	13	VK_PAUSE		Pause
20	14	VK_CAPITAL	*	Caps Lock
27	1B	VK_ESCAPE	*	Esc
32	20	VK_SPACE	*	Spacebar
33	21	VK_PRIOR	*	Page Up
34	22	VK_NEXT	*	Page Down
35	23	VK_END		End
36	24	VK_HOME	*	Home
37	25	VK_LEFT	*	Left Arrow
38	26	VK_UP	*	Up Arrow
39	27	VK_RIGHT	*	Right Arrow
40	28	VK_DOWN	*	Down Arrow
41	29	VK_SELECT		
42	2A	VK_PRINT		
43	2B	VK_EXECUTE		
44	2C	VK_SNAPSHOT		Print Screen
45	2D	VK_INSERT	*	Insert
46	2E	VK_DELETE	*	Delete
47	2F	VK_HELP		
48–57	30–39		*	0 through 9 on main keyboard
65–90	41–5A		*	A through Z
96	60	VK_NUMPAD0		Numeric keypad 0 with Num Lock ON
 97	61	VK_NUMPAD1		Numeric keypad 1 with Num Lock ON
 98	62	VK_NUMPAD2		Numeric keypad 2 with Num Lock ON
 99	63	VK_NUMPAD3		Numeric keypad 3 with Num Lock ON
100	64	VK_NUMPAD4		Numeric keypad 4 with Num Lock ON
101	65	VK_NUMPAD5		Numeric keypad 5 with Num Lock ON
102	66	VK_NUMPAD6		Numeric keypad 6 with Num Lock ON
103	67	VK_NUMPAD7		Numeric keypad 7 with Num Lock ON
104	68	VK_NUMPAD8		Numeric keypad 8 with Num Lock ON
105	69	VK_NUMPAD9		Numeric keypad 9 with Num Lock ON
106	6A	VK_MULTIPLY		Numeric keypad * (enhanced keyboard)
107	6B	VK_ADD		Numeric keypad + (enhanced keyboard)
108	6C	VK_SEPARATOR		
109	6D	VK_SUBTRACT		Numeric keypad - (enhanced keyboard)
110	6E	VK_DECIMAL		Numeric keypad
111	6F	VK_DIVIDE		Numeric keypad /(enhanced keyboard)
112	70	VK_F1	*	Function key F1
113	71	VK_F2	*	Function key F2
114	72	VK_F3	*	Function key F3
115	73	VK_F4	*	Function key F4
116	74	VK_F5	*	Function key F5
117	75	VK_F6	*	Function key F6
118	76	VK_F7	*	Function key F7
119	77	VK_F8	*	Function key F8
120	78	VK_F9	*	Function key F9
121	79	VK_F10	*	Function key F10
122	7A	VK_F11		Function key F11 (enhanced keyboard)
123	7B	VK_F12		Function key F12 (enhanced keyboard)
124	7C	VK_F13		
125	7D	VK_F14		
126	7E	VK_F15		
127	7F	VK_F16		
144	90	VK_NUMLOCK		Num Lock
145	91	VK_SCROLL		Scroll Lock
*/

