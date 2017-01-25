#include"bitmap_extract.h"
#include<codeshortcuts.h>
#include<mem3.h>
#include<BMPLib.h>
#include<img256_lib.h>
#define SUPER_STRING__C_STRING
#include<superString.h>

RGBQUAD*GetColorPalette()
{
	RGBQUAD*colors;

	HRSRC 
		hPalRsrc;
	HGLOBAL 
		hPalRsrcData;
	char 
		*strRsrc;
	DWORD
		intRsrc;
	DWORD err;

	intRsrc=IDR_PALETTE_RCT2;

	hPalRsrc=
	FindResource
	(	NULL,strRsrc=MAKEINTRESOURCE(IDR_PALETTE_RCT2),
		"PALETTE"
	);
	if(hPalRsrc==NULL)
	{err=GetLastError();colors=NULL;}
	else
	{
	hPalRsrcData=LoadResource(NULL,hPalRsrc);


	colors=(RGBQUAD*)LockResource(hPalRsrcData);
	}
	return colors;
}


Bitmap_Extract__ReadFullView
(	WORD view,WORD width,WORD height,
	BYTE*imgData,OBJDAT_FILE&odat,
	bool doFlip
)
{
	ISOMETRIC_TILE_VECTOR
		pos;

	BYTE numCols,numRows,col,row;
	bool done;
	long x,y,z,yNeg,i,j,
		bmpX,bmpY,bmpY_neg,
		bmpX_left,bmpY_top,bmpY_top_neg,
		baseHeight;
	DWORD szBuf=width*height;
	union{WORD*comprsTable,*ct;};
	union
	{	BYTE*compressedRow,*cRow;
		DAT_GRAPH__COMPRESSED_SCANLINE_RECORD*scanChunk,*sc;
	};
	DWORD yStartAddr;
	
	IMG_256__CHAIN zStack;
	
	union
	{	IMG_256__CHAIN_LINK 
			curChainLink,
			ccl;
	};
	union
	{	IMG_256
			bmpImg,
			big;
	};
	union
	{	IMG_256__CHAIN_LINK 
			*curChainLinkPtr,
			*cclP;
	};

	POINT curPt;
	RECT boundBox={0,0,width,height};

	DWORD curCol,curRow;

	view&=3;

	i=4+view;
	j=0;

	memset(imgData,0,szBuf);

	odat.LScen_GetTileDim(numCols,numRows);

	#define t odat.optional.largeScenery.tilePos[j]
	#define id odat.imageDirectory[i]

	zStack.Set(NULL,NULL);

	while((i<odat.numImages)&&(t.eosTest!=WORD(0xffff)))
	{
		
		GetTileCenterXYZ
		(	view,bmpX,bmpY,z,numCols,numRows,
			col=t.x/32,row=t.y/32,
			baseHeight=t.baseHeight,
			width,height
		);
		bmpY_top_neg=height-1-bmpY+16;

		bmpX_left=bmpX+id.xofs;
		bmpY=(bmpY_top=bmpY+id.yofs);
		bmpY_neg=(bmpY_top_neg-=id.yofs);

		
		switch(id.flags&0xf)
		{
		case IMG_IF_IMAGEDATA_COMPACT:
		case IMG_IF_IMAGEDATA:
			ccl.imageData.Set(id.width,id.height,NULL);
			ccl.imageData.ImgMalloc();

			ccl.z=z;
			ccl.x=bmpX_left;
			ccl.y=bmpY_top;
			zStack+=ccl;
			(~zStack)->imageData.Clear(0);

			break;
		}
		
		switch(id.flags&0xf)
		{
		case IMG_IF_IMAGEDATA_COMPACT:

			ct=(WORD*)&odat.imageBufr[id.startaddress];

			for_i0(y,id.height)
			{			
				cRow=
					(BYTE*)
					&odat.imageBufr
					[id.startaddress+ct[y]]
					;
				done=false;

				do
				{
					bmpX=bmpX_left+sc->xofs;

					done=bmpX>=width;

					if(!done)
					{
						curPt.x=bmpX;
						curPt.y=bmpY_neg;

						x=sc->xofs;

						if(PtInRect(&boundBox,curPt))
						{
							MemMove_OverwriteOnly_Exclude
							(
								//&imgData[bmpY_neg*width+bmpX],
								&ccl.imageData.pix(x,y),
								sc->imgData,
								sc->numBytes,
								false,
								0,
								true,
								0
							);
						}
						else
						{
							goto DummyLine;
							DummyLine:;

						}
						done=sc->rowEnd;

						cRow+=sc->numBytes+sz(*sc);
					}
				}
				while(!done);

				++bmpY;
				if(bmpY_neg==0)
					break;
				--bmpY_neg;				
			}
			break;
		case IMG_IF_IMAGEDATA:
			yStartAddr=id.startaddress;
			for_i0(y,id.height)
			{
				MemMove_OverwriteOnly_Exclude
				(
					//&imgData[bmpY_neg*width+bmpX],
					&ccl.imageData.pix(0,y),
					&odat.imageBufr[yStartAddr],
					id.width,
					false,
					0,
					true,
					0
				);

				yStartAddr+=id.width;

				++bmpY;
				--bmpY_neg;
			}
			break;
		case IMG_IF_PALETTE:
			break;
		}

		i+=4;
		++j;
	}

	big.Set(width,height,imgData);
	zStack.curLink=zStack.rootLink;

	if(~zStack!=NULL)
	{
		do
		{
			cclP=~zStack;
			big.Paste(cclP->x,cclP->y,cclP->imageData,true,0);
			;
		}
		while(++zStack);
	}

	if(doFlip)
	{
		big.Flip();
	}

	#undef t
	#undef id
}


Bitmap_Extract__ReadImage
(	WORD image,BYTE*imgData,
	DWORD&szBuf,
	OBJDAT_FILE&odat,bool doFlip
)
{
	WORD	
		width,height;
	WORD 
		x,y,i,j;
	union
	{	IMG_256
			bmpImg,
			big;
	};
	union{WORD*comprsTable,*ct;};
	union
	{	BYTE*compressedRow,*cRow;
		DAT_GRAPH__COMPRESSED_SCANLINE_RECORD*scanChunk,*sc;
	};
	bool done;

	#define id \
		odat.imageDirectory[image]

	height=id.height;
	width=szBuf/height;

	big.Set(width,height,imgData);

	//szBuf=width*height;
	memset(imgData,0,szBuf);

	switch(id.flags&0xf)
	{
	case IMG_IF_IMAGEDATA_COMPACT:
		ct=(WORD*)&odat.imageBufr[id.startaddress];

		for_i0(y,id.height)
		{			
			cRow=
				(BYTE*)
				&odat.imageBufr
				[id.startaddress+ct[y]]
				;
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
				&odat.imageBufr[id.startaddress+y*id.width],
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

	if(doFlip)
	{
		big.Flip();
	}


	#undef id
}



BITMAP_256_HEADER 
	bmp256=
	{
		{
			'MB',
			0,0,0,
			sz(BITMAPINFOHEADER)+sz(RGBQUAD)*256,			
		}

	};

#define COLORS_REVERSED
static bool paletteFlipped=false;

Bitmap_Extract
(	FILENAME&basePath,OBJDAT_FILE&odat,
	CRCT2Landmark_LScenDlg&dlg
)
{
	BYTE*imageData;

	RGBQUAD*colors=GetColorPalette();
	CString msg;
	FILENAME curFilePath,curMenuPath;

	WORD i;
	BYTE t;

	IMG_256 menuImg[4];


	#if defined(COLORS_REVERSED)

	if(!paletteFlipped)
	{
		for_i0(i,256)
		{	t=colors[i].rgbBlue;
			colors[i].rgbBlue=colors[i].rgbRed;
			colors[i].rgbRed=t;
		}
		paletteFlipped=true;

	}

	#endif COLORS_REVERSED

	struct
	{
		short xofs,yofs;
		WORD width,height;		
		DWORD totSz;
	}
		viewSizes[4];
	WORD view=0;

	dlg.DataGet();
	
	while(view<4)
	{
		#define vs viewSizes[view]
		odat.LScen_GetViewImgSize
		(
			view,
			vs.width,vs.height,
			vs.xofs,vs.yofs
		);	
		msg.Format
		(	"View %d: %d,%d,%d,%d\r\n",
			view,
			vs.width,vs.height,
			vs.xofs,vs.yofs		
		);
		dlg.AddOutputLine(~msg);

		imageData=(BYTE*)malloc(vs.totSz=vs.width*vs.height);

		Bitmap_Extract__ReadFullView
		(	view,vs.width,vs.height,
			imageData,odat,
			true
		);

		odat.CopyImage(view,menuImg[view],4);
		menuImg[view].Flip();

		curFilePath=basePath;
		curMenuPath=basePath;
		curFilePath&="view";
		curMenuPath&="menu";

		switch(view)
		{
		case VIEW_SW:
			curFilePath&="SW";
			curMenuPath&="SW";
			break;
		case VIEW_SE:
			curFilePath&="SE";
			curMenuPath&="SE";
			break;
		case VIEW_NE:
			curFilePath&="NE";
			curMenuPath&="NE";
			break;
		case VIEW_NW:
			curFilePath&="NW";
			curMenuPath&="NW";
			break;
		}
		curFilePath&=".bmp";
		curMenuPath&=".bmp";

		SaveBitmap_256
		(
			&bmp256,
			menuImg[view].w,
			menuImg[view].h,
			false,
			colors,
			menuImg[view].id,
			~curMenuPath,
			false
		);
		//curMenuImg.ImgFree();

		SaveBitmap_256
		(
			&bmp256,
			vs.width,
			vs.height,
			false,
			colors,
			imageData,
			~curFilePath,
			false
		);


		free(imageData);

		++view;
		#undef vs
	}
}

Bitmap_Extract_TileViews
(	FILENAME&basePath,OBJDAT_FILE&odat,
	CRCT2Landmark_LScenDlg&dlg,
	UINT startImgI,
	bool useImgI,
	bool useColRowRot
)
{
	BYTE*imageData;

	RGBQUAD*colors=GetColorPalette();
	CString msg;
	FILENAME curFilePath;
	DWORD tile;
	LARGE_SCENERY__POS_STRUCT*tp;

	char numStr[16];

	WORD i;
	BYTE t;

	#if defined(COLORS_REVERSED)

	if(!paletteFlipped)
	{
		for_i0(i,256)
		{	t=colors[i].rgbBlue;
			colors[i].rgbBlue=colors[i].rgbRed;
			colors[i].rgbRed=t;
		}
		paletteFlipped=true;

	}

	#endif COLORS_REVERSED

	struct
	{
		short xofs,yofs;
		WORD width,height,dwordAlignWidth;
		DWORD totSz;
	}
		viewSize;
	WORD view=0;
	WORD imageI;
	//WORD dwordAlignWidth;

	dlg.DataGet();

	imageI=0;
	
	while(imageI<odat.numImages)
	{
		#define vs viewSize

		tile=imageI/4;

		view=imageI%4;

		odat.GetImgSize
		(
			imageI,
			vs.width,vs.height,
			vs.xofs,vs.yofs
		);
		vs.dwordAlignWidth=(vs.width+3)&DWORD(0xfffffffc);
		vs.totSz=vs.dwordAlignWidth*vs.height;

		msg.Format
		(	"Image %d: %d,%d,%d,%d\r\n",
			imageI,
			vs.width,vs.height,
			vs.xofs,vs.yofs		
		);
		dlg.AddOutputLine(~msg);

		imageData=(BYTE*)malloc(vs.totSz);

		Bitmap_Extract__ReadImage
		(	imageI,
			imageData,
			vs.totSz,
			odat,
			true
		);

		curFilePath=basePath;

		if(useImgI)
		{
			sprintf
			(	numStr,"%02.2d",
				imageI+startImgI
			);
			curFilePath&=numStr;
		}
		else if(useColRowRot&&(odat.objType==OT_LARGESCENERY))
		{
			if(imageI>=4)
			{
				tp=&odat.optional.largeScenery.tilePos[imageI/4-1];
				sprintf
				(	numStr,"%02.2d_%02.2d_",
					tp->x/32,tp->y/32					
				);
			}
			else
			{
				sprintf
				(	numStr,"menu_"
				);
			}
			curFilePath&=numStr;
			sprintf
			(	numStr,"%02.2d",imageI%4				
			);
			curFilePath&=numStr;
		}
		else
		{		
			sprintf(numStr,"Tl%04.4d",tile);
			
			curFilePath&=numStr;
			switch(view)
			{
			case VIEW_SW:
				curFilePath&="SW";
				break;
			case VIEW_SE:
				curFilePath&="SE";
				break;
			case VIEW_NE:
				curFilePath&="NE";
				break;
			case VIEW_NW:
				curFilePath&="NW";
				break;
			}
		}
		curFilePath&=".bmp";

		msg.Format("\tSaving \"%s\"\r\n",~curFilePath);
		dlg.AddOutputLine(~msg);

		SaveBitmap_256
		(
			&bmp256,
			vs.width,
			vs.height,
			false,
			colors,
			imageData,
			~curFilePath,
			false
		);

		free(imageData);

		++imageI;
		#undef vs
	}
}
