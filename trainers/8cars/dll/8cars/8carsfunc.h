
int Set8carsDllLocals(char *newMain,HHOOK newhook,HACCEL newAccel);

extern LRESULT CALLBACK RCT2KeyInterceptProc
(	int  code,	// hook code
	WPARAM  wparam,	// virtual-key code
	LPARAM  lparam 	// keystroke-message information
);
