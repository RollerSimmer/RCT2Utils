
#include <windows.h>
#include "resource.h"
 
LRESULT APIENTRY MainWndProc
(	HWND hwnd, 
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

HINSTANCE hinst; 
 
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
 
    wc.style = 0; 
    wc.lpfnWndProc = (WNDPROC) MainWndProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = hinstance; 
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wc.hbrBackground = COLOR_BACKGROUND; 
    wc.lpszMenuName =  MAKEINTRESOURCE(IDM_MENU1); 
    wc.lpszClassName = "MainWClass"; 
 
    if (!RegisterClass(&wc)) 
        return FALSE; 
 
    hinst = hinstance; 
 
    hwnd = 
		CreateWindow
		(	"MainWClass", "Sample Application", 
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
			400, 45, NULL, NULL, hinstance, 
			NULL
		); 
 
    if (hwnd == NULL) 
        return FALSE; 
 
    ShowWindow(hwnd, nCmdShow); 
    UpdateWindow(hwnd); 
 
    while (GetMessage(&msg, NULL, 0, 0)) 
	{ 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 
    return msg.wParam; 
        UNREFERENCED_PARAMETER(hPrevInstance); 
} 

LRESULT APIENTRY MainWndProc
(	HWND hwnd, 
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


