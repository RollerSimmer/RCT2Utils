#ifndef SV6_ENCODE_DECODE_H
#define SV6_ENCODE_DECODE_H

#include "SV6.H"

__declspec(dllexport) 
int EncodeSv6Chunk
(
	int encodeType,
	DWORD encdChunk_maxSize,
	SV6_CHUNKHEADER *encdChunkHeader,
	BYTE *encdChunkData,
	DWORD dcodChunk_maxSize,
	SV6_CHUNKHEADER *dcodChunkHeader,
	BYTE *dcodChunkData,
	int i
);

__declspec(dllexport) 
DWORD DecodeSv6Chunk
(
	SV6_CHUNKHEADER *dcodChunkHeader,
	BYTE *dcodChunkData,
	DWORD dcodChunkMaxSize,
	SV6_CHUNKHEADER *encdChunkHeader,
	BYTE *encdChunkData,
	int i
);

__declspec(dllexport) 
EncodeSv6(int encodeType,SV6_FILE*sv6,char *outFileStream,int sv6CompressedSize);
__declspec(dllexport) 
SaveSv6(SV6_FILE*sv6,char *sv6FileName);


#endif //SV6_ENCODE_DECODE_H
