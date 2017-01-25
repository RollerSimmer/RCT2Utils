
#define dllPort __declspec(dllexport)
#include"sv4.h"
#include"..\..\shared\svx\svx_encode_decode.h"
#include <FileIO2.h>

dllPort
int 
SV4_FILE::
OpenSv4(char*sv4File)
{
	long sv4CompressedSize;
	char *inFileStream;
	bool retv=true;

	if(FExist(sv4File))
	{
		sv4CompressedSize=FSize(sv4File);
		inFileStream=(char*)malloc(sv4CompressedSize);
		
		QuickRead(inFileStream,sv4File,0,sv4CompressedSize);

		DecodeSv4((BYTE*)inFileStream,sv4CompressedSize-4);

		free(inFileStream);
		retv=false;
	}	
	return(retv);
}

dllPort
int 
SV4_FILE::
DecodeSv4(BYTE*inFileStream,long sv4CompressedSize)
{
	#define ifs (inFileStream)

	DWORD i;
	bool retv=true;

	SVX_CHUNKHEADER 
		encdChunkHeader=
		{
			ET_RLE,
			sv4CompressedSize			
		},
		dcodChunkHeader=
		{
			ET_RLE,
			sz(this->fileDataA)
		};

	i=
	DecodeSvXChunk
	(
		&dcodChunkHeader,
		(BYTE*)&(this->fileDataB),
		dcodChunkHeader.chunkSize_Encoded,
		&encdChunkHeader,
		inFileStream,
		0
	)
	-sz(SVX_CHUNKHEADER);
	this->checkSum=*(DWORD*)(&inFileStream[i]);
	i+=4;
	
	#undef ifs

	return(retv);


}
