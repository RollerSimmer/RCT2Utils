#define DEBUG 1

#include "Sv4to6Convert.h"

#include"../rct1/sv4/SV4.H"
#include"../rct2/sv6/SV6.H"
#include"../rct2/sv6/SV6_ENCODE.H"
#include"../rct2/sv6/SV6_DECODE.H"
#include <FileIO2.h>
#include "parkConvert.H"


#define sz(a) (sizeof(a))

DecodeSv4(SV4_FILE*sv4,BYTE*inFileStream,long sv4CompressedSize)
{
	#define ifs (inFileStream)

	DWORD i;

	SV6_CHUNKHEADER 
		encdChunkHeader=
		{
			ET_RLE,
			sv4CompressedSize			
		},
		dcodChunkHeader=
		{
			ET_RLE,
			sz(sv4->fileDataA)
		};

	i=
	DecodeSv6Chunk
	(
		&dcodChunkHeader,
		(BYTE*)&(sv4->fileDataB),
		dcodChunkHeader.chunkSize_Encoded,
		&encdChunkHeader,
		inFileStream,
		0
	)
	-sz(SV6_CHUNKHEADER);
	sv4->checkSum=*(DWORD*)(&inFileStream[i]);
	i+=4;
	
	#undef ifs
}

OpenSv4(SV4_FILE*sv4,char*sv4File)
{
	long sv4CompressedSize;
	char *inFileStream;

	if(FExist(sv4File))
	{
		sv4CompressedSize=FSize(sv4File);
		inFileStream=(char*)malloc(sv4CompressedSize);
		
		QuickRead(inFileStream,sv4File,0,sv4CompressedSize);

		DecodeSv4(sv4,(BYTE*)inFileStream,sv4CompressedSize-4);

		free(inFileStream);
	}	
}

Sv4to6Convert(CSv4_to_sv6Dlg *dlgP,char*sv6File,char*sv4File)
{
	#define dlg (*dlgP)

	SV4_FILE *sv4=(SV4_FILE*)malloc(sz(SV4_FILE));
	SV6_FILE *sv6=(SV6_FILE*)malloc(sz(SV6_FILE));;

	#if(DEBUG)
		#include "sv4to6convert_sv4Sizes.inl"
	#else
	#endif

	
	
	OpenSv4(sv4,sv4File);

	ConvertPark(sv6,sv4);

	//SaveSv6(sv6,sv6File);

	free(sv4);
	free(sv6);
}	
	
#undef dlg
