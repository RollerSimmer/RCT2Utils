#ifndef _STDTYPES_H_
#define _STDTYPES_H_

#include<stdMacros.h>
#include<memory.h>

#define TRUE 1
#define FALSE 0
#define ON TRUE
#define OFF FALSE
#define YES TRUE
#define NO FALSE

typedef unsigned __int64 QWORD;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

typedef union
{
	struct
	{
		BYTE 
			low:4,
			high:4;
	} nibbles;
	struct
	{
		BYTE 
			_1:1,
			_2:1,
			_3:1,
			_4:1,
			_5:1,
			_6:1,
			_7:1,
			_8:1;
	} bitFlags; 
	BYTE byteVal;
	char charVal;


} BYTE_DELUXE;

typedef struct FLAG_8
{
	BYTE 
		data;
	#ifdef __cplusplus
	BYTE GetBit(WORD bitNum)
	{
		return (data&(1<<bitNum))>>bitNum;
	}
	BYTE SetBit(WORD bitNum,BYTE val)
	{
		val&=1;
		data&=(~(1<<bitNum));
		data|=(val<<bitNum);
		return data;
	}
	#endif //__cplusplus
}
FLAG_8,
SET_8;

typedef struct FLAG_256
{
	FLAG_8 
		data[256/8];
	#ifdef __cplusplus
	BYTE 
	GetBit(WORD bitNum)
	{
		return(data[bitNum>>5].GetBit(bitNum&BYTE(256/8-1)));
	}

	BYTE 
	SetBit(WORD bitNum,BYTE val)
	{
		return(data[bitNum>>5].SetBit(bitNum&BYTE(256/8-1),val));
	}
	SetAll()
	{
		memset(data,BYTE(0xFF),sz(data));
	}
	ClearAll()
	{
		memset(data,BYTE(0),sz(data));
	}
	#endif //__cplusplus
}
FLAG_256,SET_256;

#ifndef NULL
#define NULL 0
#endif


#endif //_STDTYPES_H_
