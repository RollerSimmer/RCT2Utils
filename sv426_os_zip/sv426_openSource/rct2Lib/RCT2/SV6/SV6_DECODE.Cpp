#include <windows.h>
#include <FileIO2.h>
#include <stdlib2.h>
#include "SV6.h"
#include <string.h>
#include<rct_svx.h>

int SkipImportObjects
(	
	void*inBufferP,
	int i,
	int objsLeft
)
{
	int j;

	SV6_OBJDAT_HEADER_AND_CHUNK_HEADER
		*imporObjBlock=
			(SV6_OBJDAT_HEADER_AND_CHUNK_HEADER*)
			inBufferP;

	#define iob (*imporObjBlock)
	//#define sz(a) (sizeof(a))
	#define bytBuf ((BYTE*)inBufferP)
	DoImportObjectSkip:
	{
		j=0;

		while(objsLeft>0)
		{
			j+=sz(iob);
			j+=iob.chunkHeader.chunkSize_Encoded;
			imporObjBlock=
				(SV6_OBJDAT_HEADER_AND_CHUNK_HEADER*)
				&bytBuf[j];
			objsLeft--;
		}
		
		i+=j;
	}
	#undef bytBuf
	#undef iob
	#undef sz

	return i;
	
}

#include "SV6_DECODE_DecodeSv6Chunk.inl"


DecodeSv6(SV6_FILE*sv6,char *inFileStream,int sv6CompressedSize)
{
	DWORD i=0,chunkI;

	#define s (sv6->fileDataA)
	#define chunkAtI (*((SV6_CHUNK*)(&inFileStream[i])))
	#define ifs inFileStream
	#define cc chunkAtI
	#define cch \
		(cc.header)
	#define sz(a) (sizeof(a))
	#define equ(a,b) (memmove(a,b,sz(a)))
	#define mm(a,b,c) (memmove(a,b,c))
	#define ms0_v(a) (memset(&(a),0,sz(a)))

	
	DoDecodeSv6:
	{
		ms0_v(s);
		chunkI=0;

		i=DecodeSv6Chunk(&s.header_header,((BYTE*)(&s.header)),sz(s.header),&cc.header,(BYTE*)(&cc.buffer),i);
		chunkI++;

		i=
			SkipImportObjects
			(	
				&cc,i,
				s.header.numImbeddedCustomObjs
			);

		s.header.numImbeddedCustomObjs=0;

		i=DecodeSv6Chunk(&s.availableItems_header,((BYTE*)(&s.availableItems)),sz(s.availableItems),&cc.header,(BYTE*)(&cc.buffer),i);
		chunkI++;
		i=DecodeSv6Chunk(&s.timeData_header,((BYTE*)(&s.timeData)),sz(s.timeData),&cc.header,(BYTE*)(&cc.buffer),i);
		chunkI++;
		i=DecodeSv6Chunk(&s.parkMap_header,((BYTE*)(&s.parkMap)),sz(s.parkMap),&cc.header,(BYTE*)(&cc.buffer),i);
		chunkI++;
		i=DecodeSv6Chunk(&s.parkData_header,((BYTE*)(&s.parkData)),sz(s.parkData),&cc.header,(BYTE*)(&cc.buffer),i);
		chunkI++;
	}
	#undef ms0_v
	#undef mm
	#undef sz
	#undef equ
	#undef cc
	#undef cch
	#undef ifs
	#undef chunkAtI
	#undef s
}

OpenSv6(SV6_FILE*sv6,char *sv6FileName)
{
	int sv6CompressedSize;
	char *inFileStream;

	if(FExist(sv6FileName))
	{
		sv6CompressedSize=FSize(sv6FileName);
		inFileStream=(char*)malloc(sv6CompressedSize);
		
		QuickRead(inFileStream,sv6FileName,0,sv6CompressedSize);

		DecodeSv6(sv6,inFileStream,sv6CompressedSize);

		free(inFileStream);
	}	

}

