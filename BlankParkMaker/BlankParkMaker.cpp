// BlankParkMaker.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include<rct2lib.h>
#include<STDIO.H>

writeFile(char*fn,void*buf,long szBuf);

SV6_FILE park,&p=park;


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	void*spriteBuf,*mapBuf,*ssBuf,*pdBuf;
	long sbSz,mbSz,ssbSz,pdbSz;

	
	SV6_PARKDATA*pd=&p.fileDataA.parkData;


	spriteBuf=&p.fileDataA.parkData.sprites;
	mapBuf=&p.fileDataA.parkMap;
	ssBuf=&p.fileDataA.parkData.spriteStats;
	pdBuf=&p.fileDataA.parkData.parkNameOffset;

	
	sbSz=sizeof(p.fileDataA.parkData.sprites);
	mbSz=sizeof(p.fileDataA.parkMap);
	ssbSz=sizeof(p.fileDataA.parkData.spriteStats);
	pdbSz=sizeof(p.fileDataA.parkData);
	pdbSz=pdbSz-ssbSz-sbSz;

	#define bindir "bin/"
	#define binhead1 "in_"
	#define binhead2 "out_"
	#define binext ".bin"
	#define binspr "sprite"
	#define binmap "mapData"
	#define binsps "spriteStats"
	#define binpkd "parkData"

	const char
	sNm_in[]=bindir binhead1 binspr binext,
	mNm_in[]=bindir binhead1 binmap binext,
	ssNm_in[]=bindir binhead1 binsps binext,
	pdNm_in[]=bindir binhead1 binpkd binext,
	sNm_out[]=bindir binhead2 binspr binext,
	mNm_out[]=bindir binhead2 binmap binext,
	ssNm_out[]=bindir binhead2 binsps binext,
	pdNm_out[]=bindir binhead2 binpkd binext
	;

	bool result;
	HMODULE module=GetModuleHandle("rct2lib.dll");
	#if 1
	result=p.OpenSv6("sv6_GenTest.sv6");

	writeFile((char*)sNm_in,spriteBuf,sbSz);
	writeFile((char*)mNm_in,mapBuf,mbSz);
	writeFile((char*)ssNm_in,ssBuf,ssbSz);
	writeFile((char*)pdNm_in,pdBuf,pdbSz);	

	#endif

	p.GenNewPark(module);


	#if 1

	writeFile((char*)sNm_out,spriteBuf,sbSz);
	writeFile((char*)mNm_out,mapBuf,mbSz);
	writeFile((char*)ssNm_out,ssBuf,ssbSz);
	writeFile((char*)pdNm_out,pdBuf,pdbSz);	

	p.SaveSv6("sv6_GenTest__out.sv6");


	#endif

	return 0;
}

writeFile(char*fn,void*buf,long bufSz)
{
	FILE*f;

	f=fopen(fn,"w+b");
	if(!f)
		return;

	fwrite(buf,bufSz,1,f);
	fclose(f);
}


