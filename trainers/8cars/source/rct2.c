#pragma data_seg ("SHARED_DATA")
 
#include "rct2.h"
#include "process\process.h"
#include "8cars.h"
#include "malloc.h"

//-- code streams --

char RCT2_GAMEDATA_CODESEARCH[]=
	"\x66\x83\xC1\x16\x66\x83\xC2\x1A\xBE\x1F\x00\x00\x00\x66\xA1";

char RCT2_ADDR_PARKMAPPTRS_CODESEARCH[]=
	"\x51\x0F\xB7\xF1\xC1\xE6\x08\x66\x0B\xF0\xC1\xEE\x03\x8B\xB6";
	
char RCT2_ADDR_XYSPRITECHAINS_CODESEARCH[]=
	"\xC1\xE0\x03\x66\x0B\xC1\x66\x8B\x34\x45";

char RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODESEARCH[]=
	"\x8A\x80\xB5\x01\x00\x00\x0A\xC0\x75\x0A\x0F\xB6\x06\x8A\x04\xC5";

char RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODESEARCH[]=
	"\x66\xC1\xE2\x03\x66\x8B\x6E\x05\x83\xE5\x0F\x6B\xED\x0A\x03\x2C\xBD";

char RCT2_ADDR_OBJECTFILEPOINTERS_CODESEARCH[]=
	"\x72\x02\xFE\xC2\x8A\xF2\x0F\xB6\x5F\x01\x8B\x1C\x9D";

char RCT2_ADDR_LANDMOVERSIZE_CODESEARCH[]=
	"\x66\x6B\xED\x0F\x66\x6B\xFF\x0F\x66\x03\xC5\x66\x03\xDF\x66\x83\x3D";

//RCT2_VERSION Rct2Version=0;

//-- code reference addrs --

char *RCT2_ADDR_GAMEDATASTARTADDR=0x0668824;
char *RCT2_ADDR_PARKMAPPTRS_STARTADDR=0x065E5CB;
char *_RCT2_ADDR_XYSPRITECHAINIS_STARTADDR=0x00673897;
char *RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODEREF=NULL;
char *RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODEREF=NULL;
char *RCT2_ADDR_OBJECTFILEPOINTERS_CODEREF=NULL;
char *RCT2_ADDR_LANDMOVERSIZE_CODEREF=NULL;

//-- data addrs --

char *RCT2_ADDR_GAMEDATABASE=0x00F663A8; 

//	4685FC+EE5558=134DB54

char *_RCT2_ADDR_PARKMAPPOINTERS=0x13CE9A4;

BYTE *_RCT2_ADDR_MAPXYSPRITECHAININDEXES=0x00F1EF60;

char *RCT2_ADDR_TRACKTYPECONSTRUCTOPBASE=0x0097D218;

char *RCT2_ADDRTRACKPIECECONSTRUCTOPBASE=0X00994638;

char *_RCT2_ADDR_LANDMOVERSIZE=0X009A9800;
char *RCT2_ADDR_OBJECTFILEPOINTERSBASE=0X009ACFA4;
RCT2_VERSIONDATASTRUCT RCT2_VERSIONDATA={201028};

BYTE RCT2_SHOPTRACKTYPES[RCT2_NUMSHOPTRACKTYPES]=
{	STT_FOODSTALL,	
	STT_DRINKSTALL,
	STT_SHOP,
	STT_INFOKIOSK,
	STT_RESTROOM,
	STT_ATM,
	STT_FIRSTAID
};

PARKMAPDATA BORDERTILE={0x00,0x80,0x02,0x02,0x00,0x00,0x01,0x00};

int GetMapIndex(short x,short y,PARKMAPPTRARRAY *mapptrs)
{	return((int)((*mapptrs)[y][x])-(int)(RCT2_ADDR_PARKMAP))>>3;
}

int SetMapIndex(short x,short y,PARKMAPPTRARRAY *mapptrs,DWORD newI)
{	(DWORD)(*mapptrs)[y][x]=(DWORD)(RCT2_ADDR_PARKMAP)+(newI<<3);
}

typedef BYTE PARKMAPDATA_2[8];

int InitMapDataBlock(PARKMAPDATABLOCK *mapdatablock)
{

#undef NONZERO_WRITE
#ifdef NONZERO_WRITE
	PARKMAPDATA_2 initStruct={0xFF,0x80,0x20,0x20,0,0,0,0};
	DWORD i=0,lastI=0,bytesWritten=0,writeSize=sizeof(PARKMAPDATA);

	memcpy(&((*mapdatablock)[i]),&initStruct,writeSize);

	lastI=i;
	i+=(writeSize/sizeof(PARKMAPDATA));
	bytesWritten=writeSize;

	while((bytesWritten+writeSize)<=(MAPDATASTRUCTURES_MAX*sizeof(PARKMAPDATA)))
	{
		memcpy(&((*mapdatablock)[i]),&((*mapdatablock)[lastI]),writeSize);
		bytesWritten+=writeSize;
		lastI=i;
		i+=(writeSize/sizeof(PARKMAPDATA));
		writeSize*=2;
	}

	writeSize=sizeof(PARKMAPDATA);
	while(bytesWritten<(MAPDATASTRUCTURES_MAX*sizeof(PARKMAPDATA)))
	{
		memcpy(&((*mapdatablock)[i]),&((*mapdatablock)[lastI]),writeSize);
		bytesWritten+=writeSize;
		lastI=i;
		i+=(writeSize/sizeof(PARKMAPDATA));
	}
#else 
	memset(mapdatablock,0,MAPDATASTRUCTURES_MAX*sizeof(PARKMAPDATA));

#endif // NONZERO_WRITE
}


DWORD GetTileStructCount(PARKMAPDATA *mapdata)
{
	DWORD i=0,count=1;
	while(!mapdata[i].byte1.lastElementOnTile) 
	{	++i;
		++count;
	}
	return count;
}

short Rct2MapDataFunc
(	RCT2_MAPDATAFUNC mapdatafunc,short x,short y,LPPARKMAPDATA mapdata,int count
)
{
	static PARKMAPPTRARRAY *mapptrs;
	static PARKMAPDATABLOCK *mapdatablock;
	static int mapDataBaseAddr;
	
	PARKMAPPTRARRAY *sortMapPtrs;
	PARKMAPDATABLOCK *sortMapDataBlock;
	DWORD i,sortI,nextFreeAddr,tileStructCount;

	PARKMAPDATA_2 trailStruct={0x16,0xD0,0xFF,0x10,0x01,0x00,0x5A,0x00};

	switch(mapdatafunc)
	{
	case MDF_INIT:
		if
		(	((mapptrs=malloc(sizeof(*mapptrs)))==NULL)
			||((mapdatablock=malloc(sizeof(*mapdatablock)))==NULL)
		)
		{	MessageBox
			(	mainWindow,"Not enough memory (requires appx. 1MB free space)","Message",
				MB_DEFBUTTON1|MB_OK|MB_APPLMODAL|MB_SETFOREGROUND			
				|MB_ICONWARNING
			);
			return FALSE;
		}
		if
		(	(!WinRead(mainWindow,RCT2_TITLE,mapptrs,RCT2_ADDR_PARKMAPPOINTERS,sizeof(*mapptrs)))
		)
			return FALSE;
		if
		(	(!WinRead(mainWindow,RCT2_TITLE,mapdatablock,RCT2_ADDR_PARKMAP,sizeof(*mapdatablock)))
		)
			return FALSE;
	
		return TRUE;		

	case MDF_READ:
		memcpy(mapdata,&(*mapdatablock)[GetMapIndex(x,y,mapptrs)],sizeof(PARKMAPDATA)*count);
		return TRUE;

	case MDF_WRITE:
		memcpy(&(*mapdatablock)[GetMapIndex(x,y,mapptrs)],mapdata,sizeof(PARKMAPDATA)*count);
		return TRUE;

	case MDF_DONE:
		if(mapptrs!=NULL)
			WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_PARKMAPPOINTERS,mapptrs,sizeof(*mapptrs));
		if(mapdatablock!=NULL)
			WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_PARKMAP,mapdatablock,sizeof(*mapdatablock));
		free(mapptrs);
		mapptrs=NULL;
		mapdatablock=NULL;
		return TRUE;

	case MDF_OPTIMIZE:
		if((sortMapDataBlock=malloc(sizeof(*sortMapDataBlock)))==NULL)
		{	
			MessageBox
			(	mainWindow,"Not enough memory (requires appx. 1MB free space)","Message",
				MB_OK|MB_APPLMODAL|MB_SETFOREGROUND|MB_ICONWARNING
			);
			return FALSE;
		}
		else 
		{
			Rct2MapDataFunc(MDF_INIT,0,0,NULL,0);

			InitMapDataBlock(sortMapDataBlock);

			sortI=0;

			for(y=0;y<RCT2_HIGHSIZE;y++)
			{
				for(x=0;x<RCT2_HIGHSIZE;x++)
				{
					i=GetMapIndex(x,y,mapptrs);

					tileStructCount=GetTileStructCount(&(*mapdatablock)[i]);
					memcpy
					(	&(*sortMapDataBlock)[sortI],&(*mapdatablock)[i],
						tileStructCount*sizeof(PARKMAPDATA)
					);

					SetMapIndex(x,y,mapptrs,sortI);
					
					sortI+=tileStructCount;					
				}
			}

			memcpy(&(*sortMapDataBlock)[sortI],&trailStruct,sizeof(trailStruct));

			memcpy(mapdatablock,sortMapDataBlock,sizeof(*mapdatablock));
			free(sortMapDataBlock);			

			Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);

			nextFreeAddr=sortI*sizeof(PARKMAPDATA)+(DWORD)RCT2_ADDR_PARKMAP;
			
			WinWrite
			(	mainWindow,RCT2_TITLE,RCT2_ADDR_PARKMAPPOINTER_NEXTFREE,
				&nextFreeAddr,sizeof(nextFreeAddr)
			);
			return TRUE;
		}
	}
	return FALSE;
}


#define PADSIZE 0X40
#define BLOCKSIZE 0X80000
#define BUFFSIZE (BLOCKSIZE+PADSIZE) 
#define MAXADDR 0x900000
//#define RCT2_ADDR_TIMEFUNCSTR ((LPVOID)0x009A6030)
//#define BASEADDR RCT2_ADDR_TIMEFUNCSTR
#define STARTADDR 0x580000

int InitVersionAddresses(WORD version)
{
	char 
		*tmpbuff;
	DWORD 
		addr;
		
	int i,cmplen=3;

	WORD finds=0;

	tmpbuff=malloc(BUFFSIZE);

	addr=STARTADDR;

	//1

	while(addr<MAXADDR)
	{
		if(!WinRead(mainWindow,RCT2_TITLE,tmpbuff,addr,BUFFSIZE))
		{	addr=MAXADDR;
			goto EXITLINE;
		}
			
		for(i=0;(i<BLOCKSIZE)&&(addr<MAXADDR);i++)
		{
			#define FOUND_PARKDATA					(1<<0)
			#define FOUND_PARKMAPPTRS				(1<<1)
			#define FOUND_XYSPRCHAINDATA			(1<<2)
			#define FOUND_TRACKTYPE_CONSTRUCTOP		(1<<3)
			#define FOUND_TRACKPIECE_CONSTRUCTOP	(1<<4)
			#define FOUND_OBJECTFILEPOINTERS		(1<<5)
			#define FOUND_LANDMOVERSIZE				(1<<6)

			if(memcmp(&RCT2_GAMEDATA_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_GAMEDATA_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_PARKDATA))
				{	finds|=FOUND_PARKDATA;
					RCT2_ADDR_GAMEDATASTARTADDR=
						addr+sizeof(RCT2_GAMEDATA_CODESEARCH)-1;
				}
			}
			else if(memcmp(&RCT2_ADDR_PARKMAPPTRS_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_ADDR_PARKMAPPTRS_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_PARKMAPPTRS))
				{	finds|=FOUND_PARKMAPPTRS;
					RCT2_ADDR_PARKMAPPTRS_STARTADDR=
						addr+sizeof(RCT2_ADDR_PARKMAPPTRS_CODESEARCH)-1;
				}
			}
			else if(memcmp(&RCT2_ADDR_XYSPRITECHAINS_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_ADDR_XYSPRITECHAINS_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_XYSPRCHAINDATA))
				{	finds|=FOUND_XYSPRCHAINDATA;
					_RCT2_ADDR_XYSPRITECHAINIS_STARTADDR=
						addr+sizeof(RCT2_ADDR_XYSPRITECHAINS_CODESEARCH)-1;
				}
			}
			else if(memcmp(&RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_TRACKTYPE_CONSTRUCTOP))
				{	finds|=FOUND_TRACKTYPE_CONSTRUCTOP;
					RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODEREF=
						addr+sizeof(RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODESEARCH)-1;
				}
			}
			/*
				#define FOUND_PARKDATA					(1<<0)
				#define FOUND_PARKMAPPTRS				(1<<1)
				#define FOUND_XYSPRCHAINDATA			(1<<2)
				#define FOUND_TRACKTYPE_CONSTRUCTOP		(1<<3)
				#define FOUND_TRACKPIECE_CONSTRUCTOP	(1<<4)
				#define FOUND_OBJECTFILEPOINTERS		(1<<5)
				#define FOUND_LANDMOVERSIZE				(1<<6)
			*/
			else if(memcmp(&RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_TRACKPIECE_CONSTRUCTOP))
				{	finds|=FOUND_TRACKPIECE_CONSTRUCTOP;
					RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODEREF=
						addr+sizeof(RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODESEARCH)-1;
				}
			}
			else if(memcmp(&RCT2_ADDR_OBJECTFILEPOINTERS_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_ADDR_OBJECTFILEPOINTERS_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_OBJECTFILEPOINTERS))
				{	finds|=FOUND_OBJECTFILEPOINTERS;
					RCT2_ADDR_OBJECTFILEPOINTERS_CODEREF=
						addr+sizeof(RCT2_ADDR_OBJECTFILEPOINTERS_CODESEARCH)-1;
				}
			}
			else if(memcmp(&RCT2_ADDR_LANDMOVERSIZE_CODESEARCH,&(tmpbuff[i]),sizeof(RCT2_ADDR_LANDMOVERSIZE_CODESEARCH)-1)==0)
			{	if(!(finds&FOUND_LANDMOVERSIZE))
				{	finds|=FOUND_LANDMOVERSIZE;
					RCT2_ADDR_LANDMOVERSIZE_CODEREF=
						addr+sizeof(RCT2_ADDR_LANDMOVERSIZE_CODESEARCH)-1;
				}
			}
			if(finds==(	FOUND_PARKDATA|FOUND_PARKMAPPTRS|FOUND_XYSPRCHAINDATA
						|FOUND_TRACKTYPE_CONSTRUCTOP|FOUND_TRACKPIECE_CONSTRUCTOP
						|FOUND_OBJECTFILEPOINTERS|FOUND_LANDMOVERSIZE)	)
				goto EXITLINE;
				
			++addr;
		}
	}
	
EXITLINE:
	free(tmpbuff);
//1
	WinRead
	(	mainWindow,RCT2_TITLE,&RCT2_ADDR_GAMEDATABASE,
		RCT2_ADDR_GAMEDATASTARTADDR,
		sizeof(RCT2_ADDR_GAMEDATABASE)
	);
	WinRead
	(	mainWindow,RCT2_TITLE,&_RCT2_ADDR_PARKMAPPOINTERS,
		RCT2_ADDR_PARKMAPPTRS_STARTADDR,
		sizeof(_RCT2_ADDR_PARKMAPPOINTERS)
	);
	WinRead
	(	mainWindow,RCT2_TITLE,&_RCT2_ADDR_MAPXYSPRITECHAININDEXES,
		_RCT2_ADDR_XYSPRITECHAINIS_STARTADDR,
		sizeof(_RCT2_ADDR_MAPXYSPRITECHAININDEXES)
	);
	/*
		char RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODESEARCH[]=
			"\x8A\x80\xB5\x01\x00\x00\x0A\xC0\x75\x0A\x0F\xB6\x06\x8A\x04\xC5\x18\xD2\x97\x00";

		char RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODESEARCH[]=
			"\x66\xC1\xE2\x03\x66\x8B\x6E\x05\x83\xE5\x0F\x6B\xED\x0A\x03\x2C\xBD";

		char RCT2_ADDR_OBJECTFILEPOINTERS_CODESEARCH[]=
			"\x72\x02\xFE\xC2\x8A\xF2\x0F\xB6\x5F\x01\x8B\x1C\x9D";

		char RCT2_ADDR_LANDMOVERSIZE_CODESEARCH[]=
			"\x66\x6B\xED\x0F\x66\x6B\xFF\x0F\x66\x03\xC5\x66\x03\xDF\x66\x83\x3D";
		//-------------------------

		char RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODEREF[]=
		{
			NULL,NULL,NULL
		};

		char RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODEREF[]=
		{
			NULL,NULL,NULL
		};

		char RCT2_ADDR_OBJECTFILEPOINTERS_CODEREF[]=
		{
			NULL,NULL,NULL
		};

		char RCT2_ADDR_LANDMOVERSIZE_CODEREF[]=
		{
			NULL,NULL,NULL
		};
		//-------------------------

		char *RCT2_ADDR_TRACKTYPECONSTRUCTOPBASE=
		{
			0x0097D218,0X008FC218,0x0097D218
		};

		char *RCT2_ADDRTRACKPIECECONSTRUCTOPBASE=
		{	0X00994638,0X000913608,0X00994638
		};

		char *_RCT2_ADDR_LANDMOVERSIZE=
		{
			0X009A9800,0X00928800,0X009A9800	
		};

		char *RCT2_ADDR_OBJECTFILEPOINTERSBASE=
		{
			0X009ACFA4,0X0092BFB8,0X009ACFA4
		};
	*/
	/* 
		aaa = code search array
		bbb = code address array for data address reference
		ccc = found constant 
		ddd = data address array
	*/

	WinRead
	(	mainWindow,RCT2_TITLE,&RCT2_ADDR_TRACKTYPECONSTRUCTOPBASE,
		RCT2_ADDR_TRACKTYPE_CONSTRUCTOP_CODEREF,
		sizeof(RCT2_ADDR_TRACKTYPECONSTRUCTOPBASE)
	);
	WinRead
	(	mainWindow,RCT2_TITLE,&RCT2_ADDRTRACKPIECECONSTRUCTOPBASE,
		RCT2_ADDR_RCT2_TRACKPIECE_CONSTRUCTOPPTRS_CODEREF,
		sizeof(RCT2_ADDRTRACKPIECECONSTRUCTOPBASE)
	);
	WinRead
	(	mainWindow,RCT2_TITLE,&_RCT2_ADDR_LANDMOVERSIZE,
		RCT2_ADDR_LANDMOVERSIZE_CODEREF,
		sizeof(_RCT2_ADDR_LANDMOVERSIZE)
	);
	WinRead
	(	mainWindow,RCT2_TITLE,&RCT2_ADDR_OBJECTFILEPOINTERSBASE,
		RCT2_ADDR_OBJECTFILEPOINTERS_CODEREF,
		sizeof(RCT2_ADDR_OBJECTFILEPOINTERSBASE)
	);
} 

int GetRct2Version()
{
	char 
		*tmpbuff,*addr;
		
	int version=0,retVersion=RCT2_VER_EURO;

	int i,cmplen=3;

	tmpbuff=malloc(BUFFSIZE);

	addr=STARTADDR;

	version=RCT2_VER_EURO;

#if 0

	while(addr<MAXADDR)
	{
		if(!WinRead(mainWindow,RCT2_TITLE,tmpbuff,addr,BUFFSIZE))
		{	addr=MAXADDR;
			goto EXITLINE;
		}
			
		for(i=0;(i<BLOCKSIZE)&&(addr<MAXADDR);i++)
		{
			#if 0
				if(addr==BASEADDR)
				{	i++;
					i--;
				}
				/*	goto EXITLINE*/;
			#endif

			version=0;
			while(version<(RCT2_VER_EURO+1))
			{
				if(memcmp(&RCT2_VERSIONDATA,&(tmpbuff[i]),sizeof(RCT2_VERSIONDATA))==0) 
				{	retVersion=version;
					goto EXITLINE;
				}
				++version;
			}
/////
			++addr;
		}
	} //while(addr<MAXADDR)

#endif //0
	
EXITLINE:
	free(tmpbuff);

	if(addr>=MAXADDR)
		retVersion=RCT2_VER_EURO;

	InitVersionAddresses(retVersion);

	return retVersion;
}

int GetRCT2NameString(char *nameString,WORD nameStringIndex)
{
	return
		WinRead
		(	mainWindow,RCT2_TITLE,nameString,	
			((NAMESTRING*)RCT2_ADDR_NAMESTRINGS)[nameStringIndex],
			sizeof(NAMESTRING)
		);
}

int SetRCT2NameString(WORD nameStringIndex,BYTE *nameString)
{
	return
		WinRead
		(	mainWindow,RCT2_TITLE,
			((NAMESTRING*)RCT2_ADDR_NAMESTRINGS)[nameStringIndex],
			nameString,sizeof(NAMESTRING)
		);
}

int GetRct2Path(char *path)
{
	char *chp=RCT2REGKEYNAME;
	HKEY  hkey;
	long 
		size=HIGHFULLFILE,
		datatype=REG_SZ;

	if
	(	RegOpenKeyEx
		(	HKEY_LOCAL_MACHINE,RCT2REGKEYNAME,0,
			KEY_QUERY_VALUE,&hkey
		)
		==ERROR_SUCCESS
	)
	{	if(RegQueryValueEx(hkey,RCT2REGVALUENAME,NULL,&datatype,path,&size))
			return FALSE;
		return TRUE;
	}
	else 
		return FALSE;
}

int SuspendRCT2()
{
	DWORD threadID,processID;

	if((rct2Window=FindWindow(RCT2_TITLE,NULL))==NULL)
		return rct2Suspended=FALSE;

	threadID=GetWindowThreadProcessId(rct2Window,&processID);

	rct2Thread=		
		OpenThreadU
		(	THREAD_SUSPEND_RESUME,FALSE,threadID
		);
	rct2Suspended=
		(long)SuspendThread(rct2Thread)==-1;

	return rct2Suspended;
}

int ResumeRCT2()
{	
	ResumeThread(rct2Thread);
	rct2Suspended=FALSE;		
	return rct2Suspended;
}

