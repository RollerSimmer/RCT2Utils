#ifndef _8CARS_
#define _8CARS_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern char AboutString[512];

extern int  APIENTRY AboutBox(HWND hwnd);

extern HWND mainWindow,rct2Window;
extern HANDLE rct2Thread;
extern HMENU mainMenu;
extern HINSTANCE hinst; 
extern HACCEL haccel;
extern HHOOK rct2KeyboardHook;
extern DWORD rct2ThreadID;
extern UINT _8CarsTimer;

typedef enum{X,Y,Z,DIR}XYZCOORD;

extern char savepath[128];

extern char _8CARS_EXENAME[32];
#define _8CARSHELP_HTML	"\\8carshelp.HTML"
#define _8CARSHELP_TXT	"\\8carshelp.txt"

#include "8cars_windowName.h"

#endif
