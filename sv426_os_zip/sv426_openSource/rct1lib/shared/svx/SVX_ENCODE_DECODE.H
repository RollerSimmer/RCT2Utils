#pragma once

#include<rct_svx.h>
#include "SVX.H"

#ifndef dllPort
#define dllPort __declspec(dllexport) 
#endif

dllPort
int EncodeSvXChunk
(
	int encodeType,
	DWORD encdChunk_maxSize,
	SVX_CHUNKHEADER *encdChunkHeader,
	BYTE *encdChunkData,
	DWORD dcodChunk_maxSize,
	SVX_CHUNKHEADER *dcodChunkHeader,
	BYTE *dcodChunkData,
	int i
);

dllPort
DWORD DecodeSvXChunk
(
	SVX_CHUNKHEADER *dcodChunkHeader,
	BYTE *dcodChunkData,
	DWORD dcodChunkMaxSize,
	SVX_CHUNKHEADER *encdChunkHeader,
	BYTE *encdChunkData,
	int i
);

