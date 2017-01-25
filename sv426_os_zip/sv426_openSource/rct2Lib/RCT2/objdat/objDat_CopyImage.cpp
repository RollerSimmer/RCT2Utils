#define OBJDAT_ALL__CPP

#include"objdat.h"
#include<stdlib2.h>
#include<codeShortcuts.h>
#include<mem3.h>

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

	DATGRAPHINFOSTRUCT&id=this->imageDirectory[imgI];
	BYTE*ib=&this->imageBufr[id.startaddress];

	height=id.height;
	width=id.width;
	alignWidth=round(width,alignUnitSize);

	big.ImgMalloc(alignWidth,height);
	
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