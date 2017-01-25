#define OBJDAT_ALL__CPP

#include"objdat.h"
#include"objdat_all.h"
#include"../sv6/SV6_ENCODE_DECODE.H"
#include<stdmacros.h>
#include<codeShortcuts.h>
#include<stdio.h>


//+temp func headers
//-temp func headers

#define BUFSZ_MAX 25000000

dllPort
OBJDAT_FILE::
OBJDAT_FILE()
{
	memset(this,0,sz(*this));
}

dllPort
OBJDAT_FILE::
Init_SetType(int odType)
{
	OBJDATHEADER&ofh=objFileHeader;
	int i;

	this->ClearImages();
	OBJDAT_FILE();
	this->objType=odType;
	memset(ofh.filename,' ',sz(ofh.filename));
	memset(groupInfo.filename,' ',sz(groupInfo.filename));

	ofh.flagNibbles[0].hi=0;
	ofh.flagNibbles[0].lo=odType;
	ofh.flagBytes[3]=0;
	
	for_i0(i,3)
	{	stringTable[i].entries[0].lang=LNG_DONE;	}

	switch(odType)
	{
	case OT_LARGESCENERY:

		TYPE2HEADER&lsh=objHeader.typLScen;

		lsh.BuildFee=1;
		lsh.RemoveFee=-1;
		lsh.flags=T2_NOFLAGS;
		lsh.CursorSel=0;
		lsh.scrolling=BYTE(0xff);
		
		OPTIONAL__LARGE_SCENERY
			&ols=this->optional.largeScenery;

		ols.tilePos[0].eosTest=WORD(0xffff);

		break;
	}
}

dllPort
bool OBJDAT_FILE::HasGroupInfo()
{
	switch(objType)
	{
	case OT_SMALLSCENERY:
	case OT_LARGESCENERY:
	case OT_WALL:
	case OT_PATHBANNER:
	case OT_PATHADDITIONS:
		return true;
	case OT_RIDESHOP:
	case OT_PATH:
	case OT_SCENERYGROUP:
	case OT_PARKENTRANCE:
	case OT_WATER:
	case OT_SCENTEXT:	
	default:
		return false;
	};


}

dllPort
WORD OBJDAT_FILE::GetNumStringTables()
{
	switch(objType)
	{
	case OT_RIDESHOP:
	case OT_SCENTEXT:	
		return 3;
	case OT_SMALLSCENERY:
	case OT_LARGESCENERY:
	case OT_WALL:
	case OT_PATHBANNER:
	case OT_PATHADDITIONS:
	case OT_PATH:
	case OT_SCENERYGROUP:
	case OT_PARKENTRANCE:
	case OT_WATER:
	default:
		return 1;
	};
}

dllPort
OBJDAT_FILE::DecodeObj_Optional_Ride(BYTE*decdChunk,DWORD&i)
{
	BYTE numColorSchemes;
	DWORD j,k;

	union
	{
		DWORD curLength;
		struct
		{
			DWORD 
				unk:5,
				flatRideLength:(32-5);
		};		
	};
	DWORD frl,u;


	#define r optional.ride

	r.numColorSchemes=decdChunk[i++];
	if(r.numColorSchemes==(BYTE)(0xff))
		r.numColorSchemes=32;

	for_i0(j,r.numColorSchemes)
	{
		memmove(&r.colorSchemes[j],&decdChunk[i],
			sz(r.colorSchemes[j]));
		i+=sz(r.colorSchemes[j]);
	}
	for_i0(j,4)
	{
		curLength=decdChunk[i++];
		if(curLength==(BYTE)(0xff))
		{
			curLength=*(WORD*)(&decdChunk[i]);
			i+=2;
		}
		r.vehicleLoad[j].numLoadingPositions=curLength;
		#if 0
			frl=flatRideLength;
			u=unk;
			if(IsFlatRide())
			{
				curLength=frl;
			}
		#endif 

		if(curLength>0)
		{
			curLength=
				__min(sz(r.vehicleLoad[j].loadingPos),curLength);

			memmove
			(	r.vehicleLoad[j].loadingPos,&decdChunk[i],
				curLength			
			);
			i+=r.vehicleLoad[j].numLoadingPositions;
		}
	}	

	#undef r// optional.ride
}

OBJDAT_FILE::DecodeObj_Optional_SmScenery(BYTE*decdChunk,DWORD&i)
{
	DWORD j;

	OPTIONAL__SMALL_SCENERY&ss=optional.smallScenery;
	if(objHeader.typSScen.flags&T1_ANIMDATA)
	{
		for_i0(j,SMALL_SCENERY__MAX_ANIMATION_SEQUENCE_SIZE)
		{
			ss.animationSequence[j]=decdChunk[i++];
			
			if(ss.animationSequence[j]==BYTE(0xff))
				break;
		}
	}

}

dllPort
OBJDAT_FILE::DecodeObj_Optional_LgScenery(BYTE*decdChunk,DWORD&i)
{
	#define ls optional.largeScenery
	DWORD curSz,j;

	if(objHeader.typLScen.flags&T2_3DTEXT)
	{
		memmove(ls._3dLetters,&decdChunk[i],curSz=sz(ls._3dLetters));
		i+=curSz;
	}

	j=0;
	do
	{
		ls.tilePos[j].eosTest=*(WORD*)(&decdChunk[i]);
		if(ls.tilePos[j].eosTest==WORD(0xffff))
		{
			i+=2;
			break;
		}

		memmove(&ls.tilePos[j],&decdChunk[i],curSz=sz(ls.tilePos[j]));
		i+=curSz;
		++j;
	}
	while(j<LARGE_SCENERY__MAX_POS_STRUCTS);

	#undef ls //optional.largeScenery
}

OBJDAT_FILE::DecodeObj_Optional_Group(BYTE*decdChunk,DWORD&i)
{
	OBJDATHEADER*g=optional.groupObjs;

	DWORD j=0,curSz;
	while(j<GROUP_OBJECTS__MAX)
	{
		g[j].flagBytes[0]=decdChunk[i];
		if(g[j].flagBytes[0]==BYTE(0xff))
		{	i++;
			break;
		}
		memcpy(&g[j],&decdChunk[i],curSz=sz(g[j]));
		i+=curSz;
		j++;
	}

}

dllPort
OBJDAT_FILE::DecodeObj_Optional(BYTE*decdChunk,DWORD&i)
{
	
	switch(objType)
	{
	case OT_RIDESHOP:
		DecodeObj_Optional_Ride(decdChunk,i);	
		break;
	case OT_SMALLSCENERY:
		DecodeObj_Optional_SmScenery(decdChunk,i);
		break;
	case OT_LARGESCENERY:
		DecodeObj_Optional_LgScenery(decdChunk,i);	
		break;
	case OT_SCENERYGROUP:
		DecodeObj_Optional_Group(decdChunk,i);	
		break;
	case OT_WALL:
	case OT_PATHBANNER:
	case OT_PATHADDITIONS:
	case OT_PATH:
	case OT_PARKENTRANCE:
	case OT_WATER:
	case OT_SCENTEXT:	
	default:
		break;
	};
	
}


dllPort
DWORD OBJDAT_FILE::Images_GetBufrSz()
{
	DWORD bufSz=0,i=0,maxStartAddrI=0;

	while(i<numImages)
	{
		if(bufSz<imageDirectory[i].startaddress)
		{
			bufSz=imageDirectory[i].startaddress;
			maxStartAddrI=i;
		}
		++i;
	}
	if(maxStartAddrI==0)
	{
		bufSz=this->scanLineSize;
	}
	else
	{
		#define id imageDirectory[maxStartAddrI]

		bool lastSpan;
		BYTE*curRowP;
		DWORD j=0,maxRowJ=0,maxRow=0;
		WORD*rows=(WORD*)&this->imageBufr[id.startaddress];

		switch(id.flags&0xf)
		{
		case IMG_IF_IMAGEDATA_COMPACT:

			while(j<id.height)
			{
				if(maxRow<rows[j])
				{
					maxRowJ=j;
					maxRow=rows[j];
				}
				++j;
			}		
			curRowP=&imageBufr[maxRow+id.startaddress];

			maxRow+=id.startaddress;

			do
			{
				lastSpan=(curRowP[0]&0x80);
				maxRow+=(curRowP[0]&0x7f)+2;
				curRowP+=(curRowP[0]&0x7f)+2;
			}
			while(!lastSpan);

			bufSz=maxRow;
			
			break;
		case IMG_IF_PALETTE:
			bufSz=id.width*3+id.startaddress;
			break;
		case IMG_IF_IMAGEDATA:
		default:
			bufSz=
				id.startaddress
				+(id.width*id.height);
			break;
		}
		#undef id imageDirectory[maxStartAddrI]
	}
	return bufSz;
}

dllPort
OBJDAT_FILE::DecodeObj_Images(BYTE*decdChunk,DWORD&i)
{
	DWORD curSpan;

	switch(objType)
	{
	case OT_SCENTEXT:
		return 0;
	case OT_RIDESHOP:
	case OT_SMALLSCENERY:
	case OT_LARGESCENERY:
	case OT_SCENERYGROUP:
	case OT_WALL:
	case OT_PATHBANNER:
	case OT_PATHADDITIONS:
	case OT_PATH:
	case OT_PARKENTRANCE:
	case OT_WATER:
	default:
		memmove(&numImages,&decdChunk[i],curSpan=sz(numImages));
		i+=curSpan;
		memmove(&scanLineSize,&decdChunk[i],curSpan=sz(scanLineSize));
		i+=curSpan;

		if(imageDirectory!=NULL)
			free(imageDirectory);
		if(imageBufr!=NULL)
			free(imageBufr);

		imageDirectory=(DATGRAPHINFOSTRUCT*)malloc(curSpan=numImages*sz(imageDirectory[0])); 
		memmove(imageDirectory,&decdChunk[i],curSpan);
		i+=curSpan;

		//imageBufr=(BYTE*)malloc(curSpan=Images_GetBufrSz()); 
		imageBufr=(BYTE*)malloc(curSpan=dcodChunkSz-i); 

		memmove(imageBufr,&decdChunk[i],curSpan);
		#if 0
		curSpan=Images_GetBufrSz();
		#endif
		i+=curSpan;

		break;
	};
}

dllPort
OBJDAT_FILE::DecodeObjDatFile()
{
	SV6_CHUNKHEADER decdChunk_header;
	static BYTE*decdChunk=NULL;
	DWORD retBufSz,i,iInc;
	bool strTableDone;
	DWORD tmpLen;
	
	decdChunk=(BYTE*)realloc(decdChunk,BUFSZ_MAX);

	retBufSz=
		DecodeSv6Chunk
		(
			&decdChunk_header,
			decdChunk,
			BUFSZ_MAX,
			&objEncd.chunkHdr,
			objEncd.chunk,
			0
		);

	//convert decdChunk to OBJDAT_FILE
	retBufSz=decdChunk_header.chunkSize_Encoded;
	dcodChunkSz=retBufSz;

	this->objFileHeader=objEncd.objFileHeader;
	i=0;
	switch(objType=objFileHeader.flagNibbles[0].lo)
	{
		case OT_RIDESHOP:
			#define movObjHeader(a)\
			memmove\
			(	&this->objHeader.a,\
				&decdChunk[i],sz(objHeader.a)\
			);\
			i+=sz(this->objHeader.a)

			movObjHeader(typRide);
			break;
		case OT_SMALLSCENERY:
			movObjHeader(typSScen);
			break;
		case OT_LARGESCENERY:
			movObjHeader(typLScen);
			break;
		case OT_WALL:
			movObjHeader(typWalls);
			break;
		case OT_PATHBANNER:
			movObjHeader(typBanners);
			break;
		case OT_PATH:
			movObjHeader(typPaths);
			break;
		case OT_PATHADDITIONS:
			movObjHeader(typPathAdd);
			break;
		case OT_SCENERYGROUP:
			movObjHeader(typGroup);
			break;
		case OT_PARKENTRANCE:
			movObjHeader(typEntrance);
			break;
		case OT_WATER:
			movObjHeader(typWater);
			break;
		case OT_SCENTEXT:	
			movObjHeader(typSText);
			break;
		default:
			#undef movObjHeader
			break;
	};

	BYTE 
		stringI=0,
		strTableI=0,
		numStrTables=GetNumStringTables();
	
	while(strTableI<numStrTables)
	{
		strTableDone=false;
		stringI=0;
		while 
		(	stringI
			<RCT2__OBJDAT__STRING_TABLE__ENTRY__NUM_LANGUAGES
		)
		{
			stringTable[strTableI].entries[stringI].lang=decdChunk[i++];
			strTableDone=stringTable[strTableI].entries[stringI].lang==BYTE(0xff);
			if(!strTableDone)
			{
				strncpy
				(	stringTable[strTableI].entries[stringI].text,
					(char*)&decdChunk[i],
					RCT2__OBJDAT__STRING_TABLE__ENTRY__MAX_LENGTH-1
				);
				iInc=strlen((char*)&decdChunk[i])+1;
				i+=iInc;
			}
			else
				break;

			++stringI;
		}
		if(!strTableDone)
		{
			do
			{
				strTableDone=decdChunk[i++]==BYTE(0xff);
				if(!strTableDone)
				{
					tmpLen=strlen((char*)&decdChunk[i]);
					i+=tmpLen+1;
				}
			}
			while(!strTableDone);			
		}
		++strTableI;

	}

	if(HasGroupInfo())
	{
		memmove(&groupInfo,&decdChunk[i],
			sz(groupInfo));
		i+=sz(groupInfo);
	}

	DecodeObj_Optional(decdChunk,i);

	DecodeObj_Images(decdChunk,i);

	#if 0
	free(decdChunk);
	#endif
}

dllPort
OBJDAT_FILE::EncodeObj_Optional_Ride(BYTE*decdChunk,DWORD&i)
{
	BYTE numColorSchemes;
	DWORD j,k,curLength;

	#define r optional.ride

	r.numColorSchemes=decdChunk[i++];
	if(r.numColorSchemes==(BYTE)(0xff))
		r.numColorSchemes=32;

	for_i0(j,r.numColorSchemes)
	{
		memmove(&decdChunk[i],&r.colorSchemes[j],
			sz(r.colorSchemes[j]));
		i+=sz(r.colorSchemes[j]);
	}
	for_i0(j,4)
	{
		curLength=r.vehicleLoad[j].numLoadingPositions;
		if(WORD(curLength)&WORD(0xff00))
		{
			decdChunk[i++]=0xff;
			*(WORD*)&decdChunk[i]=WORD(curLength);
			i+=2;
		}

		if(curLength>0)
		{
			curLength=
				__min(sz(r.vehicleLoad[j].loadingPos),curLength);

			memmove
			(	&decdChunk[i],r.vehicleLoad[j].loadingPos,
				curLength			
			);
			i+=curLength;
		}
	}	

	#undef r// optional.ride
}

dllPort
OBJDAT_FILE::EncodeObj_Optional_SmScenery(BYTE*decdChunk,DWORD&i)
{
	DWORD j;

	#define ss optional.smallScenery
	if(objHeader.typSScen.flags&T1_ANIMATION)
	{
		for_i0(j,SMALL_SCENERY__MAX_ANIMATION_SEQUENCE_SIZE)
		{
			decdChunk[i++]=ss.animationSequence[j];
			
			if(ss.animationSequence[j]==BYTE(0xff))
				break;
		}
	}
	#undef ss // optional.smallScenery

}

dllPort
OBJDAT_FILE::EncodeObj_Optional_LgScenery(BYTE*decdChunk,DWORD&i)
{

	#define ls optional.largeScenery
	DWORD curSz,j;

	if(objHeader.typLScen.flags&T2_3DTEXT)
	{
		memmove(&decdChunk[i],ls._3dLetters,curSz=sz(ls._3dLetters));
		i+=curSz;
	}

	j=0;
	do
	{
		*(WORD*)(&decdChunk[i])=ls.tilePos[j].eosTest;
		if(ls.tilePos[j].eosTest==WORD(0xffff))
		{	i+=2;
			break;
		}

		memmove(&decdChunk[i],&ls.tilePos[j],curSz=sz(ls.tilePos[j]));
		i+=curSz;
		++j;
	}
	while(j<LARGE_SCENERY__MAX_POS_STRUCTS);

	#undef ls //optional.largeScenery
}

dllPort
OBJDAT_FILE::EncodeObj_Optional_Group(BYTE*decdChunk,DWORD&i)
{
	#define g optional.groupObjs

	DWORD j=0,curSz;
	while(j<0)
	{
		decdChunk[i]=g[j].flagBytes[0];
		if(g[j].flagBytes[0]==BYTE(0xff))
		{	i++;
			break;
		}
		memmove(&decdChunk[i],&g[j],curSz=sz(g[j]));
		i+=curSz;
	}
}

dllPort
OBJDAT_FILE::EncodeObj_Optional(BYTE*decdChunk,DWORD&i)
{
	
	switch(objType)
	{
	case OT_RIDESHOP:
		EncodeObj_Optional_Ride(decdChunk,i);	
		break;
	case OT_SMALLSCENERY:
		EncodeObj_Optional_SmScenery(decdChunk,i);
		break;
	case OT_LARGESCENERY:
		EncodeObj_Optional_LgScenery(decdChunk,i);	
		break;
	case OT_SCENERYGROUP:
		EncodeObj_Optional_Group(decdChunk,i);	
		break;
	case OT_WALL:
	case OT_PATHBANNER:
	case OT_PATHADDITIONS:
	case OT_PATH:
	case OT_PARKENTRANCE:
	case OT_WATER:
	case OT_SCENTEXT:	
	default:
		break;
	};
	
}

dllPort
OBJDAT_FILE::EncodeObj_Images(BYTE*decdChunk,DWORD&i)
{
	DWORD curSpan;

	switch(objType)
	{
	case OT_SCENTEXT:
		return 0;
	case OT_RIDESHOP:
	case OT_SMALLSCENERY:
	case OT_LARGESCENERY:
	case OT_SCENERYGROUP:
	case OT_WALL:
	case OT_PATHBANNER:
	case OT_PATHADDITIONS:
	case OT_PATH:
	case OT_PARKENTRANCE:
	case OT_WATER:
	default:
		memmove(&decdChunk[i],&numImages,curSpan=sz(numImages));
		i+=curSpan;
		memmove(&decdChunk[i],&scanLineSize,curSpan=sz(scanLineSize));
		i+=curSpan;

		memmove(&decdChunk[i],imageDirectory,curSpan=numImages*sz(imageDirectory[0]));
		i+=curSpan;

		//memmove(&decdChunk[i],imageBufr,curSpan=Images_GetBufrSz());
		curSpan=this->GetImageBufferSize();
		memmove(&decdChunk[i],imageBufr,curSpan);
		i+=curSpan;
		
		break;
	};
}

dllPort
CalcObjChecksum_XorRotate(DWORD&sum,BYTE data)
{
	#define DOASM 1

	#if(DOASM)
		__asm
		{
			pusha
			mov edi,sum
			mov eax,[edi]
			mov bl,byte ptr[data]
			xor al,bl
			mov cl,11
			rol eax,cl
			mov [edi],eax
			popa
		}
	#else
		union
		{
			BYTE sum_Bytes[4];
			DWORD sum_copy;
		};
		sum_copy=sum;
		sum_Bytes[0]^=data;
		sum=
			((sum_copy<<11)&0xfffff800)
			|((sum_copy>>(32-11))&0x7ff);
	#endif
}

dllPort
OBJDAT_FILE::EncodeObj_CalcChecksum(BYTE*decdChunk,DWORD&dcodFLength)
{
	#define CSUM__START_VAL (DWORD(0xF369A75B))
	DWORD i=0;
	DWORD sum;
	BYTE*hdrBytes=(BYTE*)&this->objFileHeader;
	DWORD lengthAfterHeader;


	sum=CSUM__START_VAL;

	#define DoCalc() \
		CalcObjChecksum_XorRotate(sum,hdrBytes[i++])

	i=0;
	DoCalc();
	i+=3;

	while(i<4+8) 
		DoCalc();
	
	#undef DoCalc
	#define DoCalc() \
		CalcObjChecksum_XorRotate(sum,decdChunk[i++])

	i=0;
	//lengthAfterHeader=dcodFLength-sz(this->objFileHeader);
	while(i<dcodFLength)
	{	DoCalc();	}

	this->objFileHeader.checksum=sum;

	#undef DoCalc

}

dllPort
OBJDAT_FILE::EncodeObjDatFile()
{
	SV6_CHUNKHEADER decdChunk_header;
	BYTE*decdChunk;
	DWORD retBufSz,i;
	DWORD decdChunk_curSpan;

	decdChunk=(BYTE*)malloc(BUFSZ_MAX);
	
	objEncd.objFileHeader=this->objFileHeader;
	i=0;
	//memmove(&decdChunk[i],&objEncd.objFileHeader,decdChunk_curSpan=sz(objEncd.objFileHeader));
	//i+=decdChunk_curSpan;

	switch(objType=objFileHeader.flagNibbles[0].lo)
	{
		case OT_RIDESHOP:
			#define movObjHeader(a)\
			memmove\
			(	\
				&decdChunk[i],\
				&this->objHeader.a,\
				decdChunk_curSpan=sz(objHeader.a)\
			);\
			i+=decdChunk_curSpan

			movObjHeader(typRide);
			break;
		case OT_SMALLSCENERY:
			movObjHeader(typSScen);
			break;
		case OT_LARGESCENERY:
			movObjHeader(typLScen);
			break;
		case OT_WALL:
			movObjHeader(typWalls);
			break;
		case OT_PATHBANNER:
			movObjHeader(typBanners);
			break;
		case OT_PATH:
			//movObjHeader(typPaths);
			break;
		case OT_PATHADDITIONS:
			movObjHeader(typPathAdd);
			break;
		case OT_SCENERYGROUP:
			//movObjHeader(typGroup);
			break;
		case OT_PARKENTRANCE:
			//movObjHeader(typEntrance);
			break;
		case OT_WATER:
			//movObjHeader(typWater
			break;
		case OT_SCENTEXT:	
			//movObjHeader(typSText);
			break;
		default:
			#undef movObjHeader
			break;
	};

	BYTE 
		stringI=0,
		strTableI=0,
		numStrTables=GetNumStringTables();
	
	while(strTableI<numStrTables)
	{
		while 
		(	stringI
			<RCT2__OBJDAT__STRING_TABLE__ENTRY__NUM_LANGUAGES
		)
		{
			decdChunk[i++]=stringTable[strTableI].entries[stringI].lang;
			if(stringTable[strTableI].entries[stringI].lang!=BYTE(0xff))
			{
				strncpy
				(	
					(char*)&decdChunk[i],
					stringTable[strTableI].entries[stringI].text,
					RCT2__OBJDAT__STRING_TABLE__ENTRY__MAX_LENGTH
				);
				i+=strlen((char*)&decdChunk[i])+1;
			}
			else
				break;

			++stringI;
		}
		++strTableI;

	}

	if(HasGroupInfo())
	{
		memmove(&decdChunk[i],&groupInfo,
			sz(groupInfo));
		i+=sz(groupInfo);
	}

	EncodeObj_Optional(decdChunk,i);

	EncodeObj_Images(decdChunk,i);

	dcodChunkSz=i;
	EncodeObj_CalcChecksum(decdChunk,dcodChunkSz);
	objEncd.objFileHeader=this->objFileHeader;

	decdChunk_header.encodeType=ET_LITERAL;
	decdChunk_header.chunkSize_Encoded=this->dcodChunkSz;

	i=0;

	if(objEncd.chunk!=NULL)
		free(objEncd.chunk);

	objEncd.chunk=(BYTE*)malloc(CHUNK_DATA__MAX_SIZE);


	//convert decdChunk to OBJDAT_FILE__ENCODED
	retBufSz=
		EncodeSv6Chunk
		(
			ET_RLE,
			CHUNK_DATA__MAX_SIZE,
			&objEncd.chunkHdr,
			objEncd.chunk,
			decdChunk_header.chunkSize_Encoded,
			&decdChunk_header,
			&decdChunk[i],
			0
		);

	retBufSz=decdChunk_header.chunkSize_Encoded;

	
	free(decdChunk);
}

dllPort
OBJDAT_FILE::LoadObjDatFile()
{
	LoadObjDatFile(~datFileName);
}

dllPort
OBJDAT_FILE::SaveObjDatFile(bool freeChunkBuff)
{
	SaveObjDatFile(~datFileName,freeChunkBuff);
}

dllPort
OBJDAT_FILE::LoadObjDatFile(char*datName)
{
	FILE*datFile;
	datFile=fopen(datName,"r+b");

	if(datFile!=NULL)
	{	
		fseek(datFile,0,SEEK_SET);
		fread
		(	&objEncd.objFileHeader,
			sz(objEncd.objFileHeader),
			1,datFile
		);
		fread
		(	&objEncd.chunkHdr,
			sz(objEncd.chunkHdr),
			1,datFile
		);

		objEncd.chunk=(BYTE*)malloc(objEncd.chunkHdr.chunkSize_Encoded);
		fread
		(	objEncd.chunk,
			objEncd.chunkHdr.chunkSize_Encoded,
			1,datFile
		);

		DecodeObjDatFile();

		fclose(datFile);
	}
}

dllPort
OBJDAT_FILE::SaveObjDatFile(char*datName,bool freeChunkBuff)
{
	FILE*datFile;

	EncodeObjDatFile();

	datFile=fopen(datName,"w+b");

	if(datFile!=NULL)
	{	

		fseek(datFile,0,SEEK_SET);
		fwrite
		(	&objEncd.objFileHeader,
			sz(objEncd.objFileHeader),
			1,datFile
		);
		fwrite
		(	&objEncd.chunkHdr,
			sz(objEncd.chunkHdr),
			1,datFile
		);

		fwrite
		(	objEncd.chunk,
			objEncd.chunkHdr.chunkSize_Encoded,
			1,datFile
		);
		if(freeChunkBuff)
			free(objEncd.chunk);

		fflush(datFile);

		fclose(datFile);

	}
}

dllPort
OBJDAT_FILE::LScen_GetTileDim(BYTE&cols,BYTE&rows)
{
	short i,minX,maxX,minY,maxY,curX,curY;

	#define tp this->optional.largeScenery.tilePos
	
	i=minX=maxX=minY=maxY=0;

	while(tp[i].eosTest!=WORD(0xffff))
	{
		minX=__min(minX,curX=tp[i].x);
		maxX=__max(maxX,curX);
		minY=__min(minY,curY=tp[i].y);
		maxY=__max(maxY,curY);
		++i;
	}

	cols=abs(maxX-minX)/32+1;
	rows=abs(maxY-minY)/32+1;

	#undef tp// this->optional.largeScenery.tilePos
}

dllPort
OBJDAT_FILE::LScen_GetViewImgSize(WORD view,WORD&width,WORD&height,short&xofs,short&yofs)
{
	BYTE numRows,numCols;
	WORD i;
	RECT range;
	WORD tileWidth;

	#define xl range.left
	#define xr range.right
	#define yt range.top
	#define yb range.bottom

	view&=0x3;

	LScen_GetTileDim(numRows,numCols);
	tileWidth=__max(numRows,numCols);

/*
	xofs=yofs=width=height=0;
	xl=xr=yt=yb=0;

	i=4+view;

	while(i<this->numImages)
	{
		#define img this->imageDirectory[i]

		xl=__min(img.xofs,xl);
		yt=__min(img.yofs,yt);
		xr=__max(img.xofs+img.width,xr);
		yb=__max(img.xofs+img.height,yb);

		i+=4;

		#undef img 
	}
	xofs=xl;
	yofs=yt;

	width=xr-xl;
	height=yb-yt;
*/

	width=tileWidth*64;
	height=tileWidth*32+200;
	xofs=width/2-width;
	yofs=height/2-height;
	
	#undef xl
	#undef xr
	#undef yt
	#undef yb
}

dllPort
OBJDAT_FILE::
GetImgSize
(WORD imgI,WORD&width,WORD&height,short&xofs,short&yofs)
{
	#define id \
		this->imageDirectory[imgI]
	#define set(a)\
		a=id.a;

	set(xofs);
	set(yofs);
	set(width);
	set(height);
	
	#undef id 
	#undef set
}

dllPort
OBJDAT_FILE::
GetNumTiles()
{
	int i=0;
	LARGE_SCENERY__POS_STRUCT*tp;

	tp=&this->optional.largeScenery.tilePos[0];

	numTiles=0;

	while(tp[numTiles].eosTest!=WORD(0xffff))
	{	++numTiles;	}
}

dllPort
bool
OBJDAT_FILE::
IsFlatRide()
{
	TYPE0HEADER&r=this->objHeader.typRide;
	bool isFlat;

	isFlat=r.flags&T0_FLAT;

	return(isFlat);
}


