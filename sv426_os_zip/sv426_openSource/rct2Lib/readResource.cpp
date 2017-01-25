
#include"readResource.h"

int ReadResource(HMODULE hModule,char*type,int id,void*buf,int bufSz)
{
	char*rn=MAKEINTRESOURCE(id);
	void*resBuf;
	HRSRC ri=FindResource(hModule,rn,type);
	if(!ri)return(0);
	int e=GetLastError();
	HGLOBAL r=LoadResource(hModule,ri);
	if(!r)return(0);
	resBuf=LockResource(r);
	if(!resBuf)return(0);
	
	memcpy(buf,resBuf,bufSz);

	DeleteObject(r);
	return(1);
}