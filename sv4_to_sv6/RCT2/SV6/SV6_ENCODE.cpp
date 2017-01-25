
#include <windows.h>
#include <FileIO2.h>
#include <stdlib2.h>
#include "SV6_ENCODE.H"
#include <string.h>
#include <codeshortcuts.h>

DWORD CalcSv6Checksum(BYTE*fileStream,int fileLength)
{
	int i;
	DWORD sum;

	#define fs fileStream
	DoCalcSv6Checksum:
	{
		sum=0;
		for_i0(i,fileLength)
		{
			sum+=fs[i];
		}
	}
	#undef fs //filestream

	return sum;
}

#include "SV6_ENCODE_EncodeSv6Chunk.inl"

#define INBUF_MAXSIZE (sizeof(SV6_FILE)*2)

int EncodeSv6(int encodeType,SV6_FILE*sv6,char *outFileStream,int sv6CompressedSize)
{
	int i=0,fileLength,chunkI;

	#define s (sv6->fileDataA)
	#define ofs outFileStream
	#define cc (*(LP_SV6_CHUNK)(&outFileStream[i]))
	#define cch \
		(cc.header)
	#define sz(a) (sizeof(a))
	#define equ(a,b) (memmove(a,b,sz(a)))
	#define mm(a,b,c) (memmove(a,b,c))
	#define bytesleft ((i<INBUF_MAXSIZE)?(INBUF_MAXSIZE-i):0)
	DoEncodeSv6:
	{
		i=EncodeSv6Chunk(encodeType,bytesleft,&cc.header,(BYTE*)(&cc.buffer),sz(s.header),&s.header_header,(BYTE*)(&s.header),i);
		chunkI++;

		/*

		i=
			SkipImportObjects
			(	
				&cc,i,
				s.header.numImbeddedCustomObjs
			);
		*/

		s.header.numImbeddedCustomObjs=0;

		i=EncodeSv6Chunk(encodeType,bytesleft,&cc.header,(BYTE*)(&cc.buffer),sz(s.availableItems),&s.availableItems_header,(BYTE*)(&s.availableItems),i);
		chunkI++;
		i=EncodeSv6Chunk(encodeType,bytesleft,&cc.header,(BYTE*)(&cc.buffer),sz(s.timeData),&s.timeData_header,(BYTE*)(&s.timeData),i);
		chunkI++;
		i=EncodeSv6Chunk(encodeType,bytesleft,&cc.header,(BYTE*)(&cc.buffer),sz(s.parkMap),&s.parkMap_header,(BYTE*)(&s.parkMap),i);
		chunkI++;
		i=EncodeSv6Chunk(encodeType,bytesleft,&cc.header,(BYTE*)(&cc.buffer),sz(s.parkData),&s.parkData_header,(BYTE*)(&s.parkData),i);
		chunkI++;

		fileLength=i;
		sv6->checkSum=CalcSv6Checksum((BYTE*)outFileStream,fileLength);
		memcpy(&cc,&(sv6->checkSum),sz(sv6->checkSum));
		i+=sz(sv6->checkSum);
		fileLength=i;
	}
	#undef bytesleft
	#undef mm
	#undef sz
	#undef equ
	#undef cc
	#undef cch
	#undef ofs
	#undef chunkAtI
	#undef s


	return fileLength;
}

SaveSv6(SV6_FILE*sv6,char *sv6FileName)
{
	
	int sv6CompressedSize;
	char *outFileStream;

	if(FExist(sv6FileName))
	{
		outFileStream=(char*)malloc(INBUF_MAXSIZE);

		sv6CompressedSize=EncodeSv6(ET_AUTODETECT,sv6,outFileStream,sv6CompressedSize);
		//sv6CompressedSize=EncodeSv6(ET_LITERAL,sv6,outFileStream,sv6CompressedSize);

		QuickWrite(outFileStream,sv6FileName,0,sv6CompressedSize);

		free(outFileStream);
	}
	

}
