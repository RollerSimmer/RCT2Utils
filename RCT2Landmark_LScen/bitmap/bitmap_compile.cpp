#include"bitmap_compile.h"
#include<codeshortcuts.h>
#include<mem3.h>
//#include<BMPLib.h>
#include<img256_lib.h>
#include<malloc.h>


#if 1
typedef struct:IMG_256
{
	TileTrim(int bg);
}
RCT2_IMG_256;

RCT2_IMG_256::TileTrim(int bg)
{
	int acy,bx,xfStart,xbStart,ytop,ybtm;
	int i,count;
	int xb,xf;


	
	if(w>4)
	{	
		bx=this->w/2;
		if(h>=bx)
		{	
			ytop=0;
			ybtm=h-1;
			xbStart=bx-3;
			xfStart=bx+2;

			count=bx-2;

			while(count>0)
			{
				xb=xbStart;
				xf=xfStart;

				i=count;

				if(i>0)
				do
				{
					pix(xb,ytop)
					=	
					pix(xf,ytop)
					#if 0
					=
					pix(xb,ybtm)
					=	
					pix(xf,ybtm)
					#endif
					=	
					bg
					;

					if(xb<=0)break;
					++xf;
					--xb;
					if(xf>=w)break;

					--i;
				}	
				while(i>0);

				xbStart-=2;
				xfStart+=2;

				if(ybtm<=0)break;
				ytop+=1;
				ybtm-=1;
				if(ytop>=w)break;

				count-=2;
			}
			
		}

	}
}


#endif

bool&tf(bool*f,short x,short y,short w)
{	return(f[y*w+x]);	}

//unsignedShortAddress
short&usa(short*us,short v,short x,short y,short w,short h)
{	return(us[v*w*h+y*w+x]);	}


WORD GetCropTop(IMG_256&i,WORD seeThruColor)
{
	int x,y;

	for_i0(y,i.h)
	{
	for_i0(x,i.w)
	{
		if(i.pix(x,y)!=seeThruColor)
		{
			return(y);						
		}
	}
	}
	

	return(0);
}



Bitmap_Compile__ReadFullView
(	WORD width,WORD height,WORD menuWidths[4],WORD menuHgts[4],
	BYTE*menuImgs[4],BYTE*imgData[4],OBJDAT_FILE&odat,
	bool doFlip,
	WORD seeThruColor
)
{
	//_msize
	DWORD szBlock[4];
	WORD view;
	WORD baseHeightPix,baseHeight;
	WORD cropTop;
	BYTE numCols,numRows;

	bool isBackEdge;

	ISOMETRIC_TILE_VECTOR
		pos,nw,se;

	typedef IMG_256 IMG_256_4[4];

	IMG_256_4 bigImg,&bi=bigImg;
	RCT2_IMG_256 tileImg,&ti=tileImg;
	IMG_256 curMenuImg,&cmi=curMenuImg;

	short	
		col,row,i=0,&c=col,&r=row;
	long
		x,y,z,xofs,yofs;

	short
		tCol=0,&translatedCol=tCol,
		tRow=0,&translatedRow=tRow;

	long numTiles;
	short uniTileDim,&utd=uniTileDim;
	short
		*tileHeights,*&th=tileHeights,
		*curTlHeight_Units,curTlHeight,
		tileWidth;
	short
		imgI;

	short 
		curTl_Clearance,
		curTl_Base;



	#if 0
	bool
		*tilesOccupied,*&to=tilesOccupied; 
	#endif

	BYTE 
		*lsth=&odat.lscen_tileHeights[0];

	LARGE_SCENERY__POS_STRUCT 
		*tp=&odat.optional.largeScenery.tilePos[0],
		*&tilePos=tp;
	ISOMETRIC_TILE_VECTOR 
		curTile,&ct=curTile;

	odat.LScen_GetTileDim(numCols,numRows);

	uniTileDim=__max(numCols,numRows);
	numTiles=uniTileDim*uniTileDim;

	for_i0(view,4)
	{
		szBlock[view]=_msize(imgData[view]);
	}
	for_i0(view,4)
	{
		szBlock[view]=_msize(menuImgs[view]);
	}

	#if 0
	to=(bool*)malloc(sz(*to)*numTiles);
	memset(to,0,sz(*to)*numTiles);

	th=(short*)malloc(sz(*th)*numTiles*4);
	memset(th,0,sz(*th)*numTiles*4);
	#endif

	for_i0(view,4)
	{	bi[view].Set(width,height,imgData[view]);	}

	#if 0

	i=0;
	
	while(tp[i].eosTest!=WORD(0xffff))
	{
		col=tp[i].x/32;
		row=tp[i].y/32;
		tf(to,c,r,uniTileDim)=true;
	++i;
	}

	#endif

	#if 0

	i=0;
	while(tp[i].eosTest!=WORD(0xffff))
	{
	view=0;
	while(view<4)
	{
		pos.Set(tp[i].x/32,tp[i].y/32);

		curTlHeight_Units=&usa(th,view,pos.x,pos.y,utd,utd);
		*curTlHeight_Units=0;
		
		if(pos.InBox(nw.Set(0,0),se.Set(utd,utd)))
		{
			++*curTlHeight_Units;			
			pos+=zBakInc[view];
			
			if(pos.InBox(nw.Set(0,0),se.Set(utd,utd)))
			{
				while(!tf(to,pos.x,pos.y,utd))
				{
					++*curTlHeight_Units;			

					pos+=zBakInc[view];
					if(!pos.InBox(nw.Set(0,0),se.Set(utd,utd)))
						break;
				}
			}
		}
		*curTlHeight_Units=__max(*curTlHeight_Units,2);
	++view;	
	}
	++i;
	}

	#endif

	if(doFlip)
	{	for_i0(view,4)
		{	bi[view].Flip();	}
	}

	odat.ClearImages();

	for_i0(view,4)
	{	
		cmi.Set(menuWidths[view],menuHgts[view],menuImgs[view]);
		xofs=-menuWidths[view]/2;
		yofs=0;

		imgI=(view&3);

		if(doFlip)
			cmi.Flip();


		odat.AddImage(imgI,xofs,yofs,cmi,IMG_IF_IMAGEDATA,seeThruColor);
	}


	i=0;
	while(tp[i].eosTest!=WORD(0xffff))
	{
	view=0;
	while(view<4)
	{
		col=tp[i].x/32;
		row=tp[i].y/32;
		baseHeightPix=tp[i].baseHeight;
		cropTop=GetCropTop(bi[view],seeThruColor);

		ct.Set(0,0);
		
		TranslatePos
		(	view,ct,numCols,numRows,
			col,row		
		);
		tCol=ct.x;
		tRow=ct.y;

		isBackEdge=(tCol==0)||(tRow==0);

		GetTileCenterXYZ
		(	view,x,y,z,
			numCols,numRows,
			col,row,tp[i].baseHeight,
			width,height
		);

		curTlHeight_Units=&usa(th,view,pos.x,pos.y,utd,utd);

		#if 0

		if(isBackEdge)
			curTlHeight=y+32-baseHeightPix-cropTop;
		else
			curTlHeight=32*(*curTlHeight_Units);

		#else

		curTl_Clearance=
		__max(lsth[i],tp[i].clearanceHeight);
		curTl_Base=tp[i].baseHeight;

		curTlHeight=curTl_Clearance+32;

		#endif
		

		tileWidth=64;

		xofs=-32;
		yofs=-curTlHeight+32;

		if(ti.ImgMalloc(tileWidth,curTlHeight))
		{
		//ti.Clear(seeThruColor);

			bi[view].Copy(x+xofs,y+yofs,ti,false,0);
			#if 1
				ti.TileTrim(0);

			#endif			
			imgI=((i+1)*4)|(view&3);
			odat.AddImage(imgI,xofs,yofs,ti,IMG_IF_IMAGEDATA,seeThruColor);
			ti.ImgFree();
		}

	++view;	
	}
	++i;
	}
}
