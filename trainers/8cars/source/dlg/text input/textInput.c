// + Text Input Box

//TEXTINPUT.C

#include <stddlg.h>
#include "TEXTINPUT.H"
#include "../../resource.h"

int maxLength;
char *textBuffer,*lpPrompt,*lpBaseString;

CONTROLBOXDATA 
	TextBox=	{IDC_TEXT,NULL},
	PromptBox=	{IDC_PROMPT,NULL};

CONTROLBOXDATA 
	*lpBoxes[]=
	{	
		&TextBox,
		&PromptBox,
	};
#define NUMBOXES (sizeof(lpBoxes)/sizeof(lpBoxes[0]))

int CALLBACK GetTextDlgProc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam)
{	
	int i;

	switch(msg)
	{
	case WM_INITDIALOG:
		for (i=0;i<NUMBOXES;i++)
		{
			//typedef struct{int ID;HWND hwnd;}
			lpBoxes[i]->hwnd=GetDlgItem(hdlg,lpBoxes[i]->ID);
		}
		SetDlgItemText(hdlg,PromptBox.ID,lpPrompt);
		SetDlgItemText(hdlg,TextBox.ID,lpBaseString);

		SendMessage(TextBox.hwnd,EM_SETLIMITTEXT,maxLength,0);
				
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDOK:
			GetDlgItemText(hdlg,TextBox.ID,textBuffer,maxLength);
		case IDCANCEL:
			EndDialog(hdlg,TRUE);
			return FALSE;
			;
		default:
			return FALSE;
		}
	default:
		return FALSE;		
	}
}

int *TextInputBox
(
	HINSTANCE instance,HWND window,
	char *retBuff,	
	char *prompt,char *baseString,
	int argMaxLength
)
{
	int retv;

	

	lpPrompt=prompt;
	lpBaseString=baseString;
	textBuffer=retBuff;
	maxLength=argMaxLength;

	if(maxLength==0)
		return NULL;
	else 		
		textBuffer[0]=0;
	
	retv=
		DialogBox
		(	instance,MAKEINTRESOURCE(IDD_TEXTDIALOG),
			window,&GetTextDlgProc
		);

	return textBuffer;
}

// - Text Input Box
