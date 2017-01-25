#define OBJDAT_ALL__CPP

#include"objdat.h"
#include<stdlib2.h>
#include<codeShortcuts.h>
#include<mem3.h>

dllPort
OBJDAT_FILE::
AddImage(int imgI,IMG_256&img,short imgEncdType,short seeThruColor)
{
	WORD	
		width,height;
	DWORD	
		alignWidth,tmpImgSz;
	WORD 
		x,y,i,j;
	WORD
		curSpan;
	#define TMP_IMG__MAX_SZ 1000000
	BYTE *tmpImgBufr;
	
	IMG_256&big=img;

	union{DWORD objImgI,oii,objImgSz;};

	union{WORD*comprsTable,*ct;};
	union
	{	BYTE*compressedRow,*cRow,*tibP;
		DAT_GRAPH__COMPRESSED_SCANLINE_RECORD*scanChunk,*sc;
	};
	union
	{	BYTE*objImgBufr;

	};
	bool done;

	DATGRAPHINFOSTRUCT&id=*this->imageDirectory;
	BYTE*ib=&this->imageBufr[id.startaddress];

	switch(imgEncdType)
	{
	case IMG_IF_IMAGEDATA_COMPACT:
		//skip span
		tibP=tmpImgBufr=(BYTE*)malloc(tmpImgSz=TMP_IMG__MAX_SZ);
		objImgSz=0;

		ct=(WORD*)tmpImgBufr;
		cRow=(BYTE*)&ct[img.h];
		oii=DWORD(cRow-tmpImgBufr);
		
		for_i0(y,img.h)
		{
			ct[y]=oii;
			
			x=0;

			while(x<img.w)
			{
				while((x<img.w)&&(img.pix(x,y)==seeThruColor))
				{	++x;	}
				if((x<img.w)&&(img.pix(x,y)!=seeThruColor))
				{
					sc->xofs=x;
					sc->numBytes=0;
					while((x<img.w)&&(img.pix(x,y)!=seeThruColor))
					{
						sc->imgData[sc->numBytes]=
							img.pix(x,y);
						++sc->numBytes;				
						++x;
					}
					cRow+=(curSpan=sc->numBytes+sz(*sc));
					oii+=curSpan;
				}
			}
			if(oii>tmpImgSz)
				break;		
		}
		break;
	case IMG_IF_IMAGEDATA:
		tmpImgBufr=(BYTE*)malloc(tmpImgSz=img.w*img.h);
		//tibP=tmpImgBufr;
		memcpy(tmpImgBufr,img.imgData,tmpImgSz);
		//raw
		break;
	}

	switch(imgEncdType)
	{
	case IMG_IF_IMAGEDATA_COMPACT:
	case IMG_IF_IMAGEDATA:
		#if 0

		realloc
		
		


		MemMove_OverwriteOnly
		(	,tmpImgBufr,objImgSz,
			true,
			WORD overwriteOnlyByte
		);
		#endif
		break;
	}

}

dllPort
OBJDAT_FILE::
ClearImages()
{
	this->numImages=0;
	this->scanLineSize=0;
	if(imageDirectory!=NULL)
		free(imageDirectory);
	if(imageBufr!=NULL)
		free(imageBufr);
}

#if 0
dllPort
OBJDAT_FILE::
CopyImage
(	
	int imgI,
	IMG_256&img,
	short alignUnitSize
)
{
	WORD	
		width,height;
	DWORD	
		alignWidth;
	WORD 
		x,y,i,j;
	
	IMG_256&big=img;

	union{WORD*comprsTable,*ct;};
	union
	{	BYTE*compressedRow,*cRow;
		DAT_GRAPH__COMPRESSED_SCANLINE_RECORD*scanChunk,*sc;
	};
	bool done;

	DATGRAPHINFOSTRUCT&id=*this->imageDirectory;
	BYTE*ib=&this->imageBufr[id.startaddress];

	height=id.height;
	width=id.width;
	alignWidth=round(width,alignUnitSize);

	big.ImgMalloc(width,alignWidth);
	
	//szBuf=width*height;
	big.Clear(0);

	switch(id.flags&0xf)
	{
	case IMG_IF_IMAGEDATA_COMPACT:
		ct=(WORD*)ib;

		for_i0(y,id.height)
		{			
			cRow=
				(BYTE*)
				&ib[ct[y]];
			done=false;

			do
			{
				x=sc->xofs;

				done=x>=width;

				if(!done)
				{
					MemMove_OverwriteOnly_Exclude
					(
						//&imgData[bmpY_neg*width+bmpX],
						&big.pix(x,y),
						sc->imgData,
						sc->numBytes,
						false,
						0,
						true,
						0
					);
					done=sc->rowEnd;

					cRow+=sc->numBytes+sz(*sc);
				}
			}
			while(!done);

		}
		break;
	case IMG_IF_IMAGEDATA:
		for_i0(y,id.height)
		{
			MemMove_OverwriteOnly_Exclude
			(
				//&imgData[bmpY_neg*width+bmpX],
				&big.pix(0,y),
				&ib[y*id.width],
				id.width,
				false,
				0,
				false,
				0
			);
		}
		break;
	case IMG_IF_PALETTE:
		break;
	}

	#undef id
}
#endif