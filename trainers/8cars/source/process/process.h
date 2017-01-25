//Process.h--header for process-editing routines

#include <windows.h>

#ifndef _PROCESS_
#define _PROCESS_



#define WR_READ 1
#define WR_WRITE 2

int WinWriteBytes
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	LPDWORD nBytes
);

int WinReadBytes
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	LPDWORD nBytes
);
int WinWrite
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	DWORD nBytes
);

int WinRead
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	DWORD nBytes
);

#define WBF_OR 1
#define WBF_AND 2
#define WBF_XOR 3

int WinOrB (HWND callWindow,LPCSTR WindowName, LPVOID lpDest, int mask);
int WinAndB (HWND callWindow,LPCSTR WindowName, LPVOID lpDest, int mask);
int WinXorB (HWND callWindow,LPCSTR WindowName, LPVOID lpDest, int mask);

#endif //_PROCESS_

