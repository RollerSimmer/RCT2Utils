
extern int Set8carsDllLocals
(
	char *newMain,HHOOK newhook,HACCEL newAccel,
	int _Rct2Version
);

extern LRESULT CALLBACK RCT2KeyInterceptProc
(	int  code,	// hook code
	WPARAM  wparam,	// virtual-key code
	LPARAM  lparam 	// keystroke-message information
);

extern int APIENTRY MainWndProc
(	HWND hwnd, 
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
