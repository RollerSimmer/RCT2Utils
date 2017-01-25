DWORD DecodeSv6Chunk
(
	SV6_CHUNKHEADER *dcodChunkHeader,
	BYTE *dcodChunkData,
	DWORD dcodChunkMaxSize,
	SV6_CHUNKHEADER *encdChunkHeader,
	BYTE *encdChunkData,
	int i
)
{
	#define TMPBUF_MAXSIZE 4000000

	long outI,m,inI;
	int 
		rotCount,
		encdChunkSize,
		decodeType;

	
	char 
		*chunkp,**chunkpp=&chunkp,
		soffset;
	BYTE 
		slength,
		tmpI,
		leadbyte,
		dataByte,
		*tmpbuf,
		rleLength;
	SV6_CHUNKHEADER 
		tmpChunkHeader;

	//debug
	long
		rle_numRepeatBlocks,
		rle_numStreamBlocks,
		decode_completeLength,
		rle_string_totalReferencedBytes,
		rle_string_totalDirectBytes,
		rle_string_totalReferences,
		slength_max,
		slength_min,
		rleLength_min,
		rleLength_max;


	encdChunkSize=encdChunkHeader->chunkSize_Encoded;

	#define ech \
		(*encdChunkHeader)
	#define sz(a) (sizeof(a))
	#define equ(a,b) (memmove(a,b,sz(a)))
	#define mm(a,b,c) (memmove(a,b,c))
	#define encodetype (ech.encodeType)
	#define ecSz (ech.chunkSize_Encoded)
	#define ceb (encdChunkData[inI])
	#define dbuf (dcodChunkData)
	#define ebuf (encdChunkData)
	#define set0(a) (memset(&(a),0,sz(a)))

	DoDecodeChunk:
	{
		encdChunkData=(BYTE*)&encdChunkData[0];

		mm
		(
			dcodChunkHeader,
			&ech,
			sz(SV6_CHUNKHEADER)
		);
	
		switch(ech.encodeType)
		{
		case ET_RLE:
			outI=0;
			inI=0;

			while((inI<ecSz)&&(outI<dcodChunkMaxSize))
			{	
				leadbyte=ceb;
				++inI;
								
				if(leadbyte&0x80)
				//repeat
				{	
					rleLength=BYTE(1-char(leadbyte));
					dataByte=ebuf[inI];
					if((outI+rleLength)<=dcodChunkMaxSize)
						memset(&dbuf[outI],dataByte,rleLength);
					++inI;
					++rle_numRepeatBlocks;
				}
				else
				//stream
				{	
					rleLength=BYTE(char(leadbyte)+1);
					if((outI+rleLength)<=dcodChunkMaxSize)
						memcpy(&dbuf[outI],&ebuf[inI],rleLength);
					inI+=rleLength;
					++rle_numStreamBlocks;
				}
				outI+=rleLength;
			}

			break;
		case ET_RLE_STRING:

			ech.encodeType=ET_RLE;

			mm
			(
				&tmpChunkHeader,
				&ech,
				sz(SV6_CHUNKHEADER)
			);
			tmpbuf=(BYTE*)malloc(TMPBUF_MAXSIZE);

			tmpI=
				DecodeSv6Chunk
				(
					&tmpChunkHeader,
					tmpbuf,
					TMPBUF_MAXSIZE,
					encdChunkHeader,
					encdChunkData,
					0
				);

			tmpChunkHeader.chunkSize_Encoded=TMPBUF_MAXSIZE;

			ech.encodeType=ET_RLE_STRING;
			
			outI=0;
			inI=0;

			while((inI<TMPBUF_MAXSIZE)&&(outI<dcodChunkMaxSize))
			{
				leadbyte=tmpbuf[inI++];

				if(leadbyte==BYTE(0xff))
				{
					if(inI<TMPBUF_MAXSIZE)
					{
						dataByte=tmpbuf[inI++];
						slength=1;						
						dcodChunkData[outI]=dataByte;
					}
				}
				else 
				{	
					//#define ASM_RLE_STRING
					#ifndef ASM_RLE_STRING
						slength=BYTE(leadbyte&0x07)+1;
						soffset=char((leadbyte&0xF8)>>3)-char(0x20);

					#else
						_asm
						{
							mov al,leadbyte
							mov al,[leadbyte]
							mov ah,al
							shr al,3	//al=soffset
							and al,0x1f 
							and ah,0x0f	//ah=slength
							inc ah
							sub al,0x20
							mov [slength],ah
							mov [soffset],al
						}
					#endif //ASM_RLE_STRING
					if((outI+slength)<=dcodChunkMaxSize)
						memmove(&dcodChunkData[outI],&dcodChunkData[int(outI)+int(soffset)],slength);
				}
			
				outI+=slength;
			}

			free(tmpbuf);

			break;
		case ET_ROTATE_1357:
			for 
			(	
				inI=0,outI=0,rotCount=1;
				((inI<ecSz)&&(outI<dcodChunkMaxSize));
				inI++,outI++,rotCount=(rotCount+2)&7
			)
			{	m=ceb;
				_asm	
				{	mov al,byte ptr[m]	
					mov cl,byte ptr[rotCount]	
					ror al,cl
					and eax, 0xff
					mov [m],eax
				}
				dcodChunkData[outI]=m;
			}
			break;

		case ET_LITERAL:
		default:
			mm
			(
				dcodChunkData,
				encdChunkData,
				__min(ech.chunkSize_Encoded,dcodChunkMaxSize)
			);

			inI=ech.chunkSize_Encoded;

			break;

		}

		i+=(encdChunkSize+sz(SV6_CHUNKHEADER));
	}
	#undef set0
	#undef dbuf
	#undef ebuf
	#undef ceb
	#undef mm
	#undef sz
	#undef equ
	#undef ech

	return i;
}
