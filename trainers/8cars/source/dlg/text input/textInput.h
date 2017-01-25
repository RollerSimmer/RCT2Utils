#ifndef _TEXTINPUT_
#define _TEXTINPUT_
//TEXTINPUT.H

#ifndef _WINDOWS_
#include <WINDOWS.h>
#endif //  _WINDOWS_


int *TextInputBox
(
	HINSTANCE instance,HWND window,
	char *retBuff,	
	char *prompt,char *baseString,
	int argMaxLength
);

#endif // _TEXTINPUT_

