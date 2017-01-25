
#define dllPort __declspec(dllexport)
#include<rct2lib.h>
#include<fileio2.h>
#include<codeshortcuts.h>
#include<stdio.h>
#include"sv6.h"


dllPort 
MakeDatPath(FILENAME&dp,SV6_OBJDAT_HEADER&odh)
{
	int i;
	char datName[9];

	GetRct2Path(~dp);

	sscanf(odh.filename,"%8c",datName);
	datName[8]=0;
	i=7;
	while((i>0)&&(datName[i]==' '))
	{
		datName[i--]=0;
	}

	dp>>"ObjData";
	dp>>datName;
	dp&=".dat";
}

dllPort 
SV6_FILE::FixObj(int i)
{
	FILE*f;
	int j,k;
	bool isEmpty;
	char curDatName[9];
	char isEmpty_Str[2];
	char menuName[128];
	char*datMenuStr;
	BYTE lang;

	FILENAME datPath;

	char*listText[3]=
	{
		isEmpty_Str,
		curDatName,
		menuName
	};

	SV6_OBJDAT_HEADER_BLOCK
		&dats=fileDataA.availableItems;


	isEmpty=(dats.items[i].flags==DWORD(0xffffffff));

	if(!isEmpty)
	{
		sprintf(curDatName,"%8.8s",&dats.items[i].filename[0]);
		
		MakeDatPath(datPath,dats.items[i]);
		
		if(f=fopen(~datPath,"r+b"))
		{
			fread(&dats.items[i],sz(dats.items[i]),1,f);
			fclose(f);
		}
	}
}

dllPort 
SV6_FILE::FixObjs()
{
	int i;
	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		FixObj(i);
	}
}

SV6_FILE::SV6_FILE()
{
	parkSize=(short*)&this->fileDataA.parkData.parkSize;
	memset(mapPtrs,0,sz(mapPtrs));
	ptrsInitted=false;
}

SV6_FILE::OpenSv6(char*sv6FileName)
{
	::OpenSv6(this,sv6FileName);	

	InitMapPtrs();
}

SV6_FILE::SaveSv6(char*sv6FileName)
{
	::SaveSv6(this,sv6FileName);
}





