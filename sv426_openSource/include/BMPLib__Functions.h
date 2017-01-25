//#include <BMPLib__Functions.h>

#ifndef BMP_FUNCTIONS__DEFINED
#define BMP_FUNCTIONS__DEFINED

#ifndef _BMPLIB_H_
#include<BMPLib.h>
#endif //_BMPLIB_H_

bool operator !=(RECT rect1,RECT rect2)
{
	return
	(
		false 
		||(rect1.left!=rect2.left)
		||(rect1.top!=rect2.top)
		||(rect1.right!=rect2.right)
		||(rect1.bottom!=rect2.bottom)
	);
}
bool operator ==(RECT rect1,RECT rect2)
{
	return(!(rect1!=rect2));
}

bool operator !=(BGR_24BIT a,BGR_24BIT b)
{
	return
	(
		false 
		||(a.blue!=b.blue)
		||(a.green!=b.green)
		||(a.red!=b.red)
	);
}

bool operator ==(RGBQUAD a,RGBQUAD b)
{
	int cmp;
	
	cmp=
		memcmp(&a,&b,sz(RGBQUAD)-1);

	return(cmp==0);	
}

typedef 
FLAG_8
IMG16_4PLANE;

typedef struct
{
	BYTE 
		data;
	BYTE hi()	{	return((data&0xf0)>>4);	}
	BYTE lo()	{	return(data&0xf);	}
	BYTE hiEqu(WORD val)	{	data&=0xf;return(data|=((val&0xf)<<4));	}
	BYTE loEqu(WORD val)	{	data&=0xf0;return(data|=(val&0xf));	}

	BYTE nibble(WORD nibble)
	{
		nibble&=1;
		switch(nibble)
		{
		case 0://lo
			return hi();
		case 1://hi
			return lo();
		}
	}

	BYTE nibbleEqu(WORD nibble,short val)
	{
		nibble&=1;
		val&=0xf;
		switch(nibble)
		{
		case 0://lo
			return hiEqu(val);
		case 1://hi
			return loEqu(val);
		}
	}

}
IMG16_1PLANE;

#define PAL_LOOK_UP__TABLE_1 1
#define PAL_LOOK_UP__TABLE_2 2

#define PAL_LOOK_UP_TYPE PAL_LOOK_UP__TABLE_1
#if(PAL_LOOK_UP_TYPE==PAL_LOOK_UP__TABLE_1)

#define COLORMAP_MAXCOLORLEVELS 8
typedef BYTE 
	PAL_COLORMAP
	[COLORMAP_MAXCOLORLEVELS]
	[COLORMAP_MAXCOLORLEVELS]
	[COLORMAP_MAXCOLORLEVELS]
	;
#elif(PAL_LOOK_UP_TYPE==PAL_LOOK_UP__TABLE_2)

#define COLORMAP_MAXCOLORLEVELS 256

//#define COLORMAP___INSTANCE___USE__SET_256

typedef struct PAL_COLORMAP_STRUCT
{
	#if defined COLORMAP___INSTANCE___USE__SET_256
	SET_256 instances;	
	#else
	BYTE firstInstance;
	#endif //defined COLORMAP___INSTANCE___USE__SET_256
	BGR_24BIT color;
}
PAL_COLORMAP_STRUCT;

typedef struct PAL_COLORMAP
{
	PAL_COLORMAP_STRUCT entries[COLORMAP_MAXCOLORLEVELS];
	WORD numEntries;
	bool ColorInTable(WORD&retIndex,int r,int g,int b);
	InitColorTable(bool ignorePureBlack);
	AddColorToTable
	(
		int palI,
		int r,
		int g,
		int b
	);
	WORD GetColorIndex(int r,int g,int b);
	WORD GetClosestColor_TableIndex(int r,int g,int b);
}
PAL_COLORMAP;

#endif //defined PAL__USE_LOOK_UP_TABLE

typedef struct BITMAP_FILE
{
	BITMAP_HEADER*header;
	BITMAPFILEHEADER*fileHeader;
	BITMAPINFOHEADER*infoHeader;
	RGBQUAD*colorPal;
	union 
	{
		BYTE*imgBytes;
		void*img;
	};
	void*tmpBuf;
	char*filename;
	PAL_COLORMAP*colorMap;
	//construct/destruct
	Start();
	Start(BITMAP_HEADER*header);
	Finish();	
	//update
	UpdateHeaderPointers()	
	{	
		fileHeader=&(header->header256.bmfHeader);
		infoHeader=&(header->header256.bmiHeader);
		colorPal=&(header->header256.bmiColors[0]);
	}
	//functions
	InitBmp(BITMAP_HEADER&header,void*imgArea);
	void*ImgMalloc
	(	bool useHeader,int bitsPerPlane,
		int numPlanes,int width,int height
	);
	BITMAP_HEADER*DuplicateHeader()
	{
		BITMAP_HEADER*tmpHeader=(BITMAP_HEADER*)malloc(sz(BITMAP_HEADER));
		*tmpHeader=*header;
		return tmpHeader;
	}
	bool ColorDepthSwitch(int planes,int bits)
	{
		UpdateHeaderPointers();
		return 
		(	(infoHeader->biPlanes==planes)
			&&(infoHeader->biBitCount==bits)
		);
	}
	InitPalColorMap
	(	RGBQUAD*palette,WORD numEntries,bool mallocFlag
		,bool ignorePureBlack
	);
	int LoadJascPal
	(
		char *palFile
		,bool ignorePureBlack
	)
	;
	int LoadMSPal
	(
		char *palFile
		,bool ignorePureBlack
	)
	;
	int LoadPal
	(
		char *palFile
		,bool ignorePureBlack
	)
	;
	WORD GetMappedColorIndex(RGBQUAD color);
	WORD GetMappedColorIndex(BGR_24BIT color)
	{	
		RGBQUAD	colorQuad={color.blue,color.green,color.red,0};
		return GetMappedColorIndex(colorQuad);
	}
	DeCompress();
	Compress();
	//file
	Load(char*fileName,bool ignorePureBlack);
	Load();
	Save();
	Save(char*);
	Save(bool);
	Save(char*fileName,bool doOverwritePrompt);
	//dimensions
	SetDimensions_Size(int width,int height);
	SetDimensions_ColorDepth(int bitsPerPixelPlane,int numPlanes)
	{
		int colorUsed;
		(header->header16M.bmiHeader).biBitCount=bitsPerPixelPlane;
		(header->header16M.bmiHeader).biPlanes=numPlanes;
		colorUsed=bitsPerPixelPlane*numPlanes;
		if(colorUsed>256)
			colorUsed=0;
		(header->header16M.bmiHeader).biClrUsed
		=
		(header->header16M.bmiHeader).biClrImportant
		=
		colorUsed;
	}
	SetDimensions
	(	int width,int height,
		int bitsPerPixelPlane,int numPlanes
	)
	{
		SetDimensions_ColorDepth(bitsPerPixelPlane,numPlanes);
		SetDimensions_Size(width,height);
	}
	//
	DWORD PixelByteOffset(int x,int y,int plane)
	{
		return PixelBitOffset(x,y,plane)/8;
	}
	DWORD PixelBitOffset(int x,int y,int plane)
	{
		int 
			sizePlanePixel_inBits,numPlanes,height,
			sizeImage,sizePlane,sizePlaneRow,topDown,
			bitOffset;

		UpdateHeaderPointers();

		sizePlanePixel_inBits=infoHeader->biBitCount;
		numPlanes=infoHeader->biPlanes;
		height=infoHeader->biHeight;
		sizeImage=infoHeader->biSizeImage;
		sizePlane=sizeImage/__max(numPlanes,1);
		sizePlaneRow=sizePlane/height;
		topDown=(infoHeader->biHeight<0);
		bitOffset;

		if(!topDown)
			y=(height-1)-y;

		bitOffset=sizePlane*plane;
		bitOffset+=(y*sizePlaneRow);
		bitOffset*=8;
		bitOffset+=(sizePlanePixel_inBits*x);

		return bitOffset;
	}
	IMG16_1PLANE*img16_1plane(int ofs)
	{
		return((IMG16_1PLANE*)&imgBytes[ofs]);
	}
	IMG16_4PLANE*img16_4plane(int ofs)
	{
		return((IMG16_4PLANE*)&imgBytes[ofs]);
	}
	BYTE*img256(int ofs)
	{
		return((BYTE*)&imgBytes[ofs]);
	}
	BGR_24BIT*img16M(int ofs)
	{
		return((BGR_24BIT*)&imgBytes[ofs]);
	}
	WORD GetPixel(int x,int y);
	BGR_24BIT GetPixel_16M(int x,int y);
	SetPixel(int x,int y,WORD color);
	SetPixel(int x,int y,BGR_24BIT color);
	SwapPixels(int x,int y,int u,int v)
	{
		int tmpColor=GetPixel(x,y);
		SetPixel(x,y,GetPixel(u,v));
		SetPixel(u,v,tmpColor);
	}
	SwapPixels_16M(int x,int y,int u,int v)
	{
		BGR_24BIT tmpColor=GetPixel_16M(x,y);
		SetPixel(x,y,GetPixel_16M(u,v));
		SetPixel(u,v,tmpColor);
	}
	RECT GetImgRect()
	{
		UpdateHeaderPointers();

		RECT
			area=
			{	0,0,
				__max(infoHeader->biWidth,1)-1,
				__max(infoHeader->biHeight,1)-1
			};
		return area;	
	}
	RECT GetImgRect(int t,int l,int b,int r)
	{
		RECT
			area={t,l,b,r};
		return area;	
	}
	bool xyInRect(int x,int y,RECT r)
	{
		bool 
			result=
				(x>=r.left)
				&&(x<=r.right)
				&&(y>=r.top)
				&&(y<=r.bottom);
		return result;
	}
	Flip();
	Mirror();
	//Resize(int newWidth,int newHeight);
	CropForeground(WORD bgColor);
	CropForeground(BGR_24BIT bgColor);
	CropForeground(WORD bgColor,long&xOfs,long&yOfs);
	CropForeground(BGR_24BIT bgColor,long&xOfs,long&yOfs);
	Crop(RECT cropZone);
	//copy
	CopyImgFromBmp(BITMAP_FILE bmpToCopy);
	CopyHeaderFromBmp
	(	BITMAP_FILE bmpToCopy,
		bool mallocFlag
	);
	//operators
	operator =(BITMAP_HEADER &bmpHead);
}
BITMAP_FILE;

#endif //BMP_FUNCTIONS__DEFINED


