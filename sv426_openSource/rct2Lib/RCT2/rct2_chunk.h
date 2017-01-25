#ifndef RCT2_CHUNK__H
#define RCT2_CHUNK__H

#if 0
typedef enum
{
	ET_LITERAL,
	ET_RLE,
	ET_RLE_STRING,
	ET_ROTATE_1357,
	ET_AUTODETECT=0xff,
}
SV6_ENCODETYPE;
#endif

typedef struct
{
	BYTE encodeType;
	DWORD chunkSize_Encoded;
} SV6_CHUNKHEADER;

#endif RCT2_CHUNK__H
