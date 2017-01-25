typedef enum
{
	REPEAT=0,
	STREAM,
	INIT,
} RLE_TYPE;

#include "SV6_ENCODE_GetStringEncodeOffset.inl"
#include "SV6_ENCODE_RleEncodeFlush.inl"

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
)
{
	#define TMPBUF_MAXSIZE 5000000
	#define RLE_MAXCOUNT 125

	long 
		dcodI,
		encdI,
		m,
		tmpI,
		rleI,
		dcod_refStartI;

	int rotCount,rleLength;
	
	char *chunkp,**chunkpp=&chunkp,
		leadbyte,
		soffset,leadbyte2;

	BYTE 
		slength,
		oldDcb,
		//encdType,
		*tmpbuf,
		rleData[128];

	SV6_CHUNKHEADER 
		tmpChunkHeader,
		autoDetect_ChunkHeader;

	union
	{
		BYTE strRef;
		struct
		{
			BYTE
				slength_minus_1:3,
				soffset_plus_0x20:5;
		};
	};

//	union
//	{
		struct
		{
			BYTE 
				flush:1,
				type:2,
				lasttype:2,
				step:1,
				init:1,
				finished:1;
		}
			rle;
//	};


	#define ech (*encdChunkHeader)
	//#define sz(a) (sizeof(a))
	#define equ(a,b) (memmove(a,b,sz(a)))
	#define mm(a,b,c) (memmove(a,b,c))
	#define encodetype (ech.encodeType)
	#define encdChunkSize (ech.chunkSize_Encoded)
	#define ecb (encdChunkData[encdI])
	#define dcb (dcodChunkData[dcodI])
	#define ebuf (encdChunkData)
	#define dbuf (dcodChunkData)

	DoEncodeChunk:
	{
		mm
		(
			&ech,
			dcodChunkHeader,
			sz(SV6_CHUNKHEADER)
		);

		mm
		(
			&autoDetect_ChunkHeader,
			dcodChunkHeader,
			sz(SV6_CHUNKHEADER)
		);

		ech.encodeType=encodeType;

		switch(ech.encodeType)
		{
		case ET_RLE:
			
			dcodI=0;
			encdI=0;

			rle.type=INIT;
			rleI=rleLength=0;

			while((dcodI<dcodChunk_maxSize)&&(encdI<encdChunk_maxSize))
			{
				oldDcb=dcb;
				dcodI++;

				DoRleSwitch:
				{
					rle.init=rle.type==INIT;
					rle.finished=!((dcodI<dcodChunk_maxSize)&&(encdI<encdChunk_maxSize));
					rle.lasttype=rle.type;
					if(dcb==oldDcb) //repeat block
						rle.type=REPEAT;
					else
						rle.type=STREAM;
					rle.flush=
						(
							(rle.type!=rle.lasttype)
							&&(rle.lasttype!=INIT)
						)
						||(rleLength>=RLE_MAXCOUNT)
						||rle.finished;	
					rle.step=(rle.type==rle.lasttype);

					switch(rle.type) 
					{
					case REPEAT:
						if(rle.finished)
						{
							rleLength++;
							rleI=rleLength;
							rle.step=false;
						}
						if(rle.flush)
						{
							encdI=
								RleEncodeFlush
								(	rle.lasttype,ebuf,encdI,
									rleLength,&rleData[0]
								);			
							rle.init=true;
						}
						if(rle.init)
						{
							rleData[0]=dbuf[dcodI-1];
							rleI=rleLength=1;
							rle.step=false;
						}
						if(rle.step)
						{
							rleLength++;
							rleI=rleLength;
						}
						break;
					case STREAM:
						if(rle.finished)
						{
							rleLength++;
							rleData[rleI++]=oldDcb;
							rle.step=false;
						}
						if(rle.flush)
						{	
							encdI=
								RleEncodeFlush
								(	rle.lasttype,ebuf,encdI,
									rleLength,&rleData[0]
								);			
							rle.init=true;
						}
						if(rle.init)
						{
							rleData[0]=oldDcb;
							rleI=rleLength=1;
							rle.step=false;
						}
						if(rle.step)
						{
							rleLength++;
							rleData[rleI++]=oldDcb;
						}
						break;

					default:
						break;
					}
	

				}//DoRleSwitch:


			} // while(dcodI<dcodChunk_maxSize)

			ech.chunkSize_Encoded=encdI;
			break;

		case ET_RLE_STRING:
			
			mm
			(
				&tmpChunkHeader,
				dcodChunkHeader,
				sz(SV6_CHUNKHEADER)
			);

			tmpbuf=(BYTE*)malloc(TMPBUF_MAXSIZE);


			DoStringEncode:
			{
				encdI=0;
				dcodI=0;

				while((dcodI<dcodChunk_maxSize)&&(encdI<encdChunk_maxSize))
				{
					dcod_refStartI=max(long(dcodI)-0x20,0);
					soffset=
						GetStringEncodeOffset
						(
							&dbuf[dcod_refStartI],
							&dbuf[dcodI],
							dcod_refStartI,
							dcodI,
							&slength
						);

					if(soffset==0) //direct
					{
						if((encdI+2)<=encdChunk_maxSize)
						{
							tmpbuf[encdI++]=BYTE(0xff);
							tmpbuf[encdI++]=dbuf[dcodI++];
						}
						else 
						{
							tmpbuf[encdI++]=BYTE(0xf8);
						}
					}
					else //reference
					{
						slength=__max(slength,1);
						slength_minus_1=BYTE(slength-1) ;
						soffset_plus_0x20=BYTE(soffset+0x20);
						tmpbuf[encdI++]=strRef;
						dcodI+=slength;
					}	

				}
			}

			tmpChunkHeader.chunkSize_Encoded=encdI;

			tmpI=
				EncodeSv6Chunk
				(
					ET_RLE,
					encdChunk_maxSize,
					encdChunkHeader,
					encdChunkData,
					tmpChunkHeader.chunkSize_Encoded,
					&tmpChunkHeader,
					tmpbuf,
					0
				);

			ech.encodeType=ET_RLE_STRING;
			
			free(tmpbuf);

			break;
		case ET_ROTATE_1357:

			ech.chunkSize_Encoded=dcodChunk_maxSize;
			
			for 
			(	
				dcodI=0,encdI=0,rotCount=1;
				((dcodI<encdChunkSize)&&(encdI<dcodChunk_maxSize));
				dcodI++,encdI++,rotCount=(rotCount+2)&7
			)
			{	
				m=dcodChunkData[encdI];
				_asm	
				{	mov al,byte ptr[m]	
					mov cl,byte ptr[rotCount]	
					rol al,cl
					and eax, 0xff
					mov [m],eax
				}
				ecb=m;
			}

			break;
		case ET_AUTODETECT:
			
			
			tmpI=
				EncodeSv6Chunk
				(
					autoDetect_ChunkHeader.encodeType,
					encdChunk_maxSize,
					encdChunkHeader,
					encdChunkData,
					dcodChunk_maxSize,
					dcodChunkHeader,
					dcodChunkData,
					i
				);

			ech.chunkSize_Encoded=tmpI-(i+sz(SV6_CHUNKHEADER));

			break;
		case ET_LITERAL:
		default:
			ech.chunkSize_Encoded=dcodChunk_maxSize;

			mm
			(
				encdChunkData,
				dcodChunkData,
				dcodChunk_maxSize
			);

			break;

		}

		i+=(ech.chunkSize_Encoded+sz(SV6_CHUNKHEADER));
	}
	#undef dbuf
	#undef ebuf
	#undef dcb
	#undef ecb
	#undef mm
	#undef sz
	#undef equ
	#undef ec
	#undef ech
	#undef chunkAtI

	return i;

}
