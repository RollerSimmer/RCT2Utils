#ifndef _BMPLIB_H_
#define _BMPLIB_H_

#ifndef BITMAP_16_HEADER

#include <windows.H>
#include <stdmacros.h>
#include <STDTYPES.H>

//typedef RGBQUAD*RGBQUAD_PTR;


typedef struct RGB_24BIT
{
	BYTE
		red,
		green,
		blue;
	operator=(RGBQUAD quad)
	{
		blue=quad.rgbBlue;
		red=quad.rgbGreen;
		green=quad.rgbRed;	
	}
	RGB_24BIT SetRGB(int r,int g,int b)
	{
		red=r,
		green=g,
		blue=b;
		return(*this);
	}
}
RGB_24BIT;

typedef struct 
{
	WORD
		red:5,
		green:5,
		blue:5;
	union 
	{	
		WORD
			bit0x15:1,
			transparent:1;
	};
}
RGB_16BIT;

typedef struct BGR_24BIT
{
	BYTE
		blue,
		green,
		red;
	operator=(RGBQUAD quad)
	{
		blue=quad.rgbBlue;
		red=quad.rgbGreen;
		green=quad.rgbRed;	
	}
	bool operator==(BGR_24BIT color2)
	{
		bool result;
		#define colorSame(a) (a==color2.a)
		result=
		(
			true
			&&colorSame(blue)
			&&colorSame(red)
			&&colorSame(green)
		);	
		#undef colorSame
		return(result);
	}
	BGR_24BIT SetRGB(int r,int g,int b)
	{
		red=r,
		green=g,
		blue=b;
		return(*this);
	}
}
BGR_24BIT;

BGR_24BIT Bgr_24bit(int r,int g,int b);

typedef struct 
{
	WORD
		blue:5,
		green:5,
		red:5;
	union 
	{	
		WORD
			bit0x15:1,
			transparent:1;
	};
}
BGR_16BIT;

typedef struct 
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader; 
	RGBQUAD			bmiColors[16]; 
} BITMAP_16_HEADER;

typedef struct 
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader; 
	RGBQUAD		  bmiColors[256]; 
} BITMAP_256_HEADER;

typedef struct 
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader; 
} BITMAP_16M_HEADER,BITMAP_NOPAL_HEADER;

typedef union
{
	BITMAP_16_HEADER header16;
	BITMAP_256_HEADER header256;
	BITMAP_16M_HEADER header16M;
} 
BITMAP_HEADER;

#endif //BITMAP_16_HEADER

typedef struct RGBQUAD_RGB
{
    BYTE    rgbRed; 
    BYTE    rgbGreen; 
    BYTE    rgbBlue; 
    BYTE    rgbReserved; 
}
RGBQUAD_RGB;

typedef RGBQUAD RGBQUAD_BGR;

typedef struct
{
	union
	{
		DWORD 
			sig//='FFIR'
			;
		char riffSignature[4];
	};
	union
	{	
		DWORD 
			filelengthMinus8;
	};
	DWORD 
		riffType//=' LAP'
		;
}
MSPAL_FILEHEADER;

typedef struct
{
	DWORD 
		signature//='atad'
		;
	DWORD chunkSize;
}
MSPAL_CHUNKHEADER;

typedef struct
{
	WORD 
		palVersion,
		numColors;
	RGBQUAD_RGB
		colors[];
}
MSPAL_CHUNK;

typedef struct 
{
	MSPAL_FILEHEADER fileHeader;
	MSPAL_CHUNKHEADER chunkHeader;
	MSPAL_CHUNK chunk;
} MSPAL_FILESTRUCT;

int LoadBitmap_16
(
	BITMAP_16_HEADER *bitmap16,
	BYTE **imageData,
	char *bmpFileName
);

int SaveBitmap_16
(
	BITMAP_16_HEADER *bitmap16,
	long width,
	long height,
	long topDown,
	RGBQUAD *colors,
	BYTE *imageData,
	char *bmpFileName,
	bool doOverwritePrompt
);

int InitBitmap_16
(
	BITMAP_16_HEADER *bitmap16,
	long width,
	long height,
	long topDown,
	RGBQUAD *colors
);

int LoadBitmap_256
(
	BITMAP_256_HEADER *bitmap256,
	BYTE **imageData,
	char *bmpFileName
);

int SaveBitmap_256
(
	BITMAP_256_HEADER *bitmap256,
	long width,
	long height,
	long topDown,
	RGBQUAD *colors,
	BYTE *imageData,
	char *bmpFileName,
	bool doOverwritePrompt
);

int InitBitmap_256
(
	BITMAP_256_HEADER *bitmap256,
	long width,
	long height,
	long topDown,
	RGBQUAD *colors
);

int LoadBitmap_16M
(
	BITMAP_16M_HEADER *bitmap16M,
	BGR_24BIT **imageData,
	char *bmpFileName
);

int InitBitmap_16M
(	
	BITMAP_16M_HEADER *bitmap16M,
	long width,
	long height,
	long topDown
	//

);

int SaveBitmap_16M
(	
	BITMAP_16M_HEADER *bitmap16M,
	long width,
	long height,
	long topDown,
	BGR_24BIT *imageData,
	char *bmpFileName,
	bool doOverwritePrompt
);

int LoadMSPalette
(
	MSPAL_FILESTRUCT&msPal,
	RGBQUAD*&colors,
	char*palFile,
	bool mallocColors
);

int LoadJascPalette
(
	WORD&colorCount,
	RGBQUAD*&colors,
	char*palFile,
	bool mallocColors
);

RECT CommonRect(RECT r,RECT s);
RECT operator&(RECT r,RECT s);

#ifndef BMP_FUNCTIONS__DEFINED
#include <BMPLib__Functions.h>
#endif BMP_FUNCTIONS__DEFINED

#endif //_BMPLIB_H_
