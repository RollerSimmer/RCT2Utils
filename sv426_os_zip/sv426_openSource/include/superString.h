#ifndef SUPER_STRING__H
#define SUPER_STRING__H



#include<stdtypes.h>

typedef struct CHAR_SET
{
	union{BYTE b[256/8],bytes[256/8];};
	CHAR_SET();
	CHAR_SET&operator=(BYTE*chars);
	CHAR_SET&operator=(BYTE c);
	CHAR_SET operator|(CHAR_SET&c2);//bitwise OR
	CHAR_SET&operator|=(CHAR_SET&c2);
	CHAR_SET operator|(BYTE*chars);
	CHAR_SET&operator|=(BYTE*chars);
	CHAR_SET operator|(BYTE c);
	operator|=(BYTE c);
	CHAR_SET operator&(CHAR_SET&c2);//bitwise AND
	CHAR_SET&operator&=(CHAR_SET&c2);
	CHAR_SET operator&(BYTE*chars);
	CHAR_SET&operator&=(BYTE*chars);
	CHAR_SET operator&(BYTE c);
	CHAR_SET&operator&=(BYTE c);
	bool IsSet();
	bool operator!();//IsSet()
	bool operator&&(CHAR_SET&c2);//boolean AND
	bool operator&&(BYTE*chars);
	bool operator&&(BYTE c);
	CHAR_SET operator^(CHAR_SET&c2);//take out chars
	CHAR_SET&operator^=(CHAR_SET&c2);
	CHAR_SET operator^(BYTE*chars);
	CHAR_SET&operator^=(BYTE*chars);
	CHAR_SET operator^(BYTE c);
	CHAR_SET&operator^=(BYTE c);
	CHAR_SET operator-(CHAR_SET&c2);//take out chars
	CHAR_SET&operator-=(CHAR_SET&c2);
	CHAR_SET operator-(BYTE*chars);
	CHAR_SET&operator-=(BYTE*chars);
	CHAR_SET operator-(BYTE c);
	CHAR_SET&operator-=(BYTE c);
	CHAR_SET operator~();//bitwise NOT
}
	CHAR_SET;

typedef struct SUPER_STRING
{
	union{bool initialized,init;};
	union{DWORD length,l;};
	union{char*buffer,*bufr,*str;BYTE*bufrByt;};
	SUPER_STRING();
	SUPER_STRING&operator/=(int n);//set to number
	SUPER_STRING&Number(int minDigits,int maxDigits,int n)//set to number
		;
	SUPER_STRING&operator+=(SUPER_STRING s2);//append
	SUPER_STRING&operator+=(char*s2);//append
	SUPER_STRING&operator+=(char c);//append char
	//SUPER_STRING&operator=(SUPER_STRING s2);
	SUPER_STRING&operator=(BYTE*s2);
	SUPER_STRING&operator=(char*s2);
	BYTE*operator~();//char pointer
	SUPER_STRING operator+();//uppercase
	SUPER_STRING operator-();//lowercase
	SUPER_STRING GetToken(DWORD&p,CHAR_SET delims,char&retDelim);
	SUPER_STRING GetToken(DWORD&p,BYTE*delims,char&retDelim);//
	SUPER_STRING GetToken(DWORD&p,char*delims,char&retDelim);
	SUPER_STRING GetToken_Exclude(DWORD&p,char*delims,char&retDelim);
	bool operator==(SUPER_STRING&s2);
	bool operator==(char*s2);
	bool InitOn();
	DWORD operator!();//string length 
	char&operator[](int i);//array
}
	SUPER_STRING;



#ifdef SUPER_STRING__C_STRING

#if !defined(STDAFX_INCLUDED)
#include <afxwin.h>
#endif

char*operator~(CString&s);

#endif// SUPER_STRING__C_STRING

//bool operator==(char*s1,char*s2);

#endif
