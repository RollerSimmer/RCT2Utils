//stdtypes.h

#ifndef	_STDTYPES_
#define	_STDTYPES_

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef int BOOL;

#ifndef TRUE
#define TRUE ((BOOL)(-1))
#define FALSE ((BOOL)(0))
#endif //TRUE

#define BIT_SET		1	
#define BIT_CLEAR	0	

#ifndef NULL
#define NULL ((void*)0)
#endif //NULL

#if!defined __cplusplus
#define bool BOOL
#define true TRUE
#define false (!true)
#endif //__cplusplus
//#ifndef
//#endif // 

typedef unsigned long SIZE_T;

#ifndef CSTR_EQUAL
#define CSTR_EQUAL 0
#define CSTR_LESS_THAN -1
#define CSTR_GREATER_THAN 1
#endif // CSTR_EQUAL

#endif //_STDTYPES_
