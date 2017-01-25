#define OBJDAT_ALL__CPP

#include"objdat.h"
#include<stdlib2.h>
#include<codeShortcuts.h>
#include<mem3.h>

dllPort
OBJDAT_FILE::
AddImage
(	int imgI,
	short xofs,
	short yofs,
	IMG_256&img,short imgEncdType,short seeThruColor
)
{
	WORD	
		width,height;
	DWORD	
		alignWidth,tmpImgSz,
		newScanLineSize;
	WORD 
		x,y,i,j;
	WORD
		curSpan;
	#define TMP_IMG__MAX_SZ 1000000
	BYTE *tmpImgBufr,*tmpReallocImgBufr;
	bool append;
	
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

	//DATGRAPHINFOSTRUCT*id=this->imageDirectory;
	//BYTE*ib=&this->imageBufr[id[0].startaddress];

	append=imgI>=numImages;
	imgI=__min(imgI,numImages);

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
		objImgSz=tmpImgSz;
		//tibP=tmpImgBufr;
		memcpy(tmpImgBufr,img.imgData,tmpImgSz);
		//raw
		break;
	}

	switch(imgEncdType)
	{
	case IMG_IF_IMAGEDATA_COMPACT:
	case IMG_IF_IMAGEDATA:
		#if 1

		this->scanLineSize=GetImageBufferSize();
		scanLineSize+=objImgSz;
		tmpReallocImgBufr=imageBufr;
		imageBufr=(BYTE*)realloc(imageBufr,scanLineSize);

		if(imageBufr!=NULL)
		{
			++numImages;
			imageDirectory=
				(DATGRAPHINFOSTRUCT*)
				realloc
				(	imageDirectory,
					sz(*imageDirectory)*numImages
				);
			if(!append)
			{
				memmove
				(	
					&imageDirectory[imgI+1],
					&imageDirectory[imgI],
					sz(*imageDirectory)*(numImages-(imgI+1))
				);
			}
			
			#define idir imageDirectory[imgI]
			#define idirNext imageDirectory[imgI+1]
			if(!append)
				idir.startaddress=
					idirNext.startaddress;
			else
			{
				idir.startaddress=
					scanLineSize
					-objImgSz;
			}
			idir.xofs=xofs;
			idir.yofs=yofs;
			idir.width=img.w;
			idir.height=img.h;
			idir.flags=DWORD(0xf)&imgEncdType;
			idir.unused=0;
			
			#undef idir
			#undef idirNext 			
			if(!append)
			{
				for_i_span(i,imgI+1,numImages-1,1)
				{
					imageDirectory[i].startaddress+=objImgSz;
				}
				memmove
				(
					&imageBufr[imageDirectory[imgI+1].startaddress],
					&imageBufr[imageDirectory[imgI].startaddress],
					scanLineSize-imageDirectory[imgI+1].startaddress
				);	
			}
			memcpy
			(
				&imageBufr[imageDirectory[imgI].startaddress],
				tmpImgBufr,
				objImgSz				
			);
		}
		else
		{
			imageBufr=tmpReallocImgBufr;
		}	

		if(tmpImgBufr!=NULL)
			free(tmpImgBufr);
		
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
	imageDirectory=NULL;
	imageBufr=NULL;
}

dllPort
DWORD 
OBJDAT_FILE::
GetImageBufferSize()
{
	union{DWORD imgBufrSz,ibSz,ibs;};
	int i;
	union{DWORD maxStartAddrI,mxSaI;};
	short x;
	DATGRAPHINFOSTRUCT*id;
	WORD imgEncdType;

	union{WORD*comprsTable,*ct;};
	union
	{	BYTE*compressedRow,*cRow,*tibP;
		DAT_GRAPH__COMPRESSED_SCANLINE_RECORD*scanChunk,*sc;
	};
	bool done;

	ibSz=0;
	i=0;
	
	if(numImages>0)
	{
		mxSaI=0;
		for_i0(i,numImages)
		{
			if
			(	imageDirectory[i].startaddress
				>imageDirectory[mxSaI].startaddress
			)
				mxSaI=i;		
		}
		i=mxSaI;
		id=&imageDirectory[i];
		switch(imgEncdType=id->flags&0xf)
		{
		case IMG_IF_IMAGEDATA_COMPACT:
			ct=(WORD*)&imageBufr[id->startaddress];
			if(id->height>0)
			{
				cRow=
					&imageBufr
					[	ct[id->height-1]
						+id->startaddress
					];
				done=false;
				while(!done)
				{
					done=sc->rowEnd;
					cRow+=sc->numBytes+sz(*sc);
				}		
				ibSz=DWORD(cRow-imageBufr);
			}
			else
			{
				ibSz=imageBufr[id->startaddress];
			}
			break;
		case IMG_IF_IMAGEDATA:
			ibSz=id->width*id->height;
			ibSz+=id->startaddress;
			break;
		}
	}
	else
		ibSz=0;


	return ibSz;
}




