#ifndef _STDLIB2_
#define _STDLIB2_

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include <stdtypes0.h>

int trim_spec(char *destStr,char *srcStr,char *delims);
int trim(char *destStr,char *srcStr);

int range(int n,int low,int high);
int sign(int n);
int inrange(int n,int l,int h);
int memswap(char *addr1,char *addr2,int bytes);
int round(int a,int unitSize);
int GetToken
(	char *retBuff,int p,const char *str,
	const char *delim,DWORD retBuff_MaxLength
);
int GetToken2
(	char *retBuff,int p,const char *str,
	const char *delim,DWORD retBuff_MaxLength
);
char* strtok_ci(char *strToken,const char *delims);

#define chrupr(c) (((c>='a')&&(c<='z'))?c-('a'-'A'):c) 
#define chrlwr(c) (((c>='A')&&(c<='Z'))?c+('a'-'A'):c) 

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_STDLIB2_
