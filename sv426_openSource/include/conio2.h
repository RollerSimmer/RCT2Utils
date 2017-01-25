//conio2.h 
//extended console I/O

#ifndef _CONIO2_
#define _CONIO2_

#define ASCII_ESC	27

char Prompt
(	
	char *promptStr,char *validKeys
);

#define PrintableChar(ch) ((((ch)>=' ')&&((ch)<='\x7f'))?(ch):'.')

#endif //_CONIO2_
