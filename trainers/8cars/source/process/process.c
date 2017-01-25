
//-----------------------
//split up at some point 

//Process.c--header for process-editing routines
#include "process.h"

/*
BOOL WriteProcessMemory(
  

    HANDLE  hProcess,	// handle to process whose memory is written to  
    LPVOID  lpBaseAddress,	// address to start writing to 
    LPVOID  lpBuffer,	// pointer to buffer to write data to
    DWORD  nSize,	// number of bytes to write
    LPDWORD  lpNumberOfBytesWritten 	// actual number of bytes written 
   );

BOOL ReadProcessMemory(
  

    HANDLE  hProcess,	// handle of the process whose memory is read  
    LPCVOID  lpBaseAddress,	// address to start reading
    LPVOID  lpBuffer,	// address of buffer to place read data
    DWORD  nSize,	// number of bytes to read
    LPDWORD  lpNumberOfBytesRead 	// address of number of bytes read
   );

HANDLE OpenProcess(
  

    DWORD  dwDesiredAccess,	// access flag 
    BOOL  bInheritHandle,	// handle inheritance flag 
    DWORD  dwProcessId 	// process identifier 
   );   

DWORD GetWindowThreadProcessId(
  

    HWND  hWnd,	// handle of window
    LPDWORD  lpdwProcessId 	// address of variable for process identifier
   );	

HWND FindWindow(
    LPCTSTR  lpClassName,	// address of class name
    LPCTSTR  lpWindowName 	// address of window name
);

BOOL CloseHandle(
    HANDLE  hObject 	// handle to object to close  
);	

*/

int WinReadWrite
(	HWND callWindow,int Func, LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	LPDWORD nBytes
)
{
	int rwResult;
	HANDLE hndl;
	HWND hwnd;
	DWORD procID;

	if ((hwnd=FindWindow(NULL, WindowName))==NULL) 
	{
		MessageBox
		(	callWindow,"No window","Message", 
			MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND			
			|MB_ICONWARNING
		);

		return FALSE;
	};

	GetWindowThreadProcessId(hwnd,&procID);

	if((hndl=OpenProcess(PROCESS_ALL_ACCESS,FALSE,procID))==NULL) 
	{	MessageBox
		(	callWindow,"No process","Message", 
			MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND			
			|MB_ICONWARNING
		);

		return FALSE;
	};
	

	rwResult=FALSE;
	
	switch (Func)
	{
	case WR_WRITE:
		if (WriteProcessMemory(hndl,lpDest,lpSrc,*nBytes,nBytes))
		{
			rwResult=TRUE;
			break;
		}
		else 
			break;				
	case WR_READ:
		if (ReadProcessMemory(hndl,lpSrc,lpDest,*nBytes,nBytes))
		{
			 rwResult=TRUE;
			break;
		}
		else 
			break;
	default:
		break;
	}
	
	CloseHandle(hndl);

	return rwResult;
}

int WinWriteBytes
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	LPDWORD nBytes
)
{
	return WinReadWrite(callWindow,WR_WRITE,WindowName,lpDest,lpSrc,nBytes);
}

int WinReadBytes
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	LPDWORD nBytes
)
{
	return WinReadWrite(callWindow,WR_READ,WindowName,lpDest,lpSrc,nBytes);
}

int WinWrite
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	DWORD nBytes
)
{
	return WinReadWrite(callWindow,WR_WRITE,WindowName,lpDest,lpSrc,&nBytes);
}

int WinRead
(	HWND callWindow,
	LPCSTR WindowName, LPVOID lpDest,LPVOID lpSrc, 
	DWORD nBytes
)
{
	return WinReadWrite(callWindow,WR_READ,WindowName,lpDest,lpSrc,&nBytes);
}

int WinBitFunc 
(	HWND callWindow,
	int Func, LPCSTR WindowName, 
	LPVOID lpDest, int mask
)
{
	char tmp;
	
	if(WinRead(callWindow,WindowName,&tmp,lpDest,1))
	{
		switch (Func)
		{
		case WBF_OR:tmp|=(char)(mask);break;
		case WBF_AND:tmp&=(char)(mask);break;
		case WBF_XOR:tmp^=(char)(mask);break;
		}
		return WinWrite(callWindow,WindowName,lpDest,&tmp,1);
	}

}


int WinAndB (HWND callWindow,LPCSTR WindowName, LPVOID lpDest, int mask)
{
	return WinBitFunc(callWindow,WBF_AND,WindowName,lpDest,mask);
}

int WinXorB (HWND callWindow,LPCSTR WindowName, LPVOID lpDest, int mask)
{
	return WinBitFunc(callWindow,WBF_XOR,WindowName,lpDest,mask);
}

int WinOrB (HWND callWindow,LPCSTR WindowName, LPVOID lpDest, int mask)
{
	return WinBitFunc(callWindow,WBF_OR,WindowName,lpDest,mask);
}


