#ifndef SV6_DECODE_H
#define SV6_DECODE_H

#include "SV6_ENCODE_DECODE.h"

DecodeSv6(SV6_FILE*sv6,char *inFileStream,int sv6CompressedSize);
DWORD DecodeSv6Chunk
(
	SV6_CHUNKHEADER *dcodChunkHeader,
	BYTE *dcodChunkData,
	DWORD dcodChunkMaxSize,
	SV6_CHUNKHEADER *encdChunkHeader,
	BYTE *encdChunkData,
	int i
);
OpenSv6(SV6_FILE*sv6,char *sv6FileName);


#endif //SV6_DECODE_H
