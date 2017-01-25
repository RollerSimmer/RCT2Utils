 
#include <windows.h>
#include <math.h>
#include <memory.h>
#include "..\process\process.h"
#include "..\rct2.h"
#include "terrfuncs.h"
#include "..\mapfuncs\mapfuncs.h"
#include "..\8cars.h"
#include <stdlib2.h>
#include <fcntl.h>
#include <share.h>
#include <sys/stat.h>

#define HIGHFTL 80

#define EvenUp(a) ((a+1)&~1)

typedef char SCANLINE[256][256];

typedef SCANLINE* LPSCANLINE ;
  
typedef struct 
{ // bmi 
   BITMAPINFOHEADER bmiHeader; 
   RGBQUAD          bmiColors[256]; 
} BITMAPINFO_256; 

typedef struct 
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
} BMPFILEHEAD;

typedef struct 
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFO_256 bmih;
} BMPFILEHEAD_256;

typedef struct
{
	RGBQUAD          aColors[256];
} BMPFILEPAL;
//	BYTE             aBitmapBits[];


// BMPFILEHEAD bmpFilehead;

#define BM_ID 0X4D42		//'BM'

int SetMapHeight
(	int *init,int done,int x,int y,PARKMAPPTRARRAY* lpMapPtrs,
	LPSCANLINE scanline, WORD parksize
)
{

#define C (int)((*scanline)[y][x]&0XFE) 
#define N (int)((*scanline)[y-1][x]&0XFE)  
#define S (int)((*scanline)[y+1][x]&0XFE) 
#define W (int)((*scanline)[y][x-1]&0XFE) 
#define E (int)((*scanline)[y][x+1]&0XFE) 
#define NW (int)((*scanline)[y-1][x-1]&0XFE) 
#define NE (int)((*scanline)[y-1][x+1]&0XFE) 
#define SW (int)((*scanline)[y+1][x-1]&0XFE) 
#define SE (int)((*scanline)[y+1][x+1]&0XFE)

	POINT xy;
	RECT ValidXYRange={1,1,255,255};

	int nw_corner,ne_corner,sw_corner,se_corner,
		CornertoCorner2,NWSE_Test,NESW_Test;
	int n_sign,s_sign,e_sign,w_sign;
	int nw_sign,ne_sign,se_sign,sw_sign;
	int moretiles, inWriteRange;

	int i;
	BYTE landlevel, Slope;	
	PARKMAPDATA pmd[512];
	LPPARKMAPDATA parkMapPtr;


	if(done)
	{
		Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);
		return (TRUE);
	}
	
	ValidXYRange.right=ValidXYRange.bottom=parksize-2;


	//if(inWriteRange=PointInRect(&ValidXYRange, MakePoint(x,y)))
	{
		landlevel=C;

		n_sign=range(N-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(n_sign<0)n_sign+=RCT2_HEIGHTUNIT;
		s_sign=range(S-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(s_sign<0)s_sign+=RCT2_HEIGHTUNIT;
		e_sign=range(E-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(e_sign<0)e_sign+=RCT2_HEIGHTUNIT;
		w_sign=range(W-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(w_sign<0)w_sign+=RCT2_HEIGHTUNIT;
		ne_sign=range(NE-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(ne_sign<0)ne_sign+=RCT2_HEIGHTUNIT;
		nw_sign=range(NW-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(nw_sign<0)nw_sign+=RCT2_HEIGHTUNIT;
		se_sign=range(SE-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(se_sign<0)se_sign+=RCT2_HEIGHTUNIT;
		sw_sign=range(SW-C,-(RCT2_HEIGHTUNIT<<1),RCT2_HEIGHTUNIT);if(sw_sign<0)sw_sign+=RCT2_HEIGHTUNIT;
			
		nw_corner=sign(sign(n_sign+w_sign)+nw_sign);
		ne_corner=sign(sign(n_sign+e_sign)+ne_sign);
		sw_corner=sign(sign(s_sign+w_sign)+sw_sign);
		se_corner=sign(sign(s_sign+e_sign)+se_sign);
		
		CornertoCorner2=
			(abs(nw_corner-se_corner)==2)^(abs(ne_corner-sw_corner)==2);
			
		if ((nw_corner|ne_corner|sw_corner|se_corner)<0)
		{
		
			landlevel-=RCT2_HEIGHTUNIT;		
			if(nw_corner<1)nw_corner++;
			if(ne_corner<1)ne_corner++;
			if(sw_corner<1)sw_corner++;
			if(se_corner<1)se_corner++;	
			
		};

		if(CornertoCorner2)
			CornertoCorner2=(nw_corner+ne_corner+sw_corner+se_corner)==3;
		
		Slope=
			((nw_corner&1)<<NW_BIT)|((ne_corner&1)<<NE_BIT)
			|((sw_corner&1)<<SW_BIT)|((se_corner&1)<<SE_BIT)
 			|((CornertoCorner2&1)<<4);

		if (!((Slope&0XF)^0XF)) 
			Slope=0;
		
  
	};

	moretiles=TRUE;	

	parkMapPtr=(*lpMapPtrs)[y][x];

	if(!(*init))
		*init=Rct2MapDataFunc(MDF_INIT,0,0,NULL,0);
		
	if(*init)
	{
		i=0;
		Rct2MapDataFunc(MDF_READ,x,y,pmd,512);
		do
		{
			//WinWrite(RCT2_TITLE,RCT2_ADDR_WEATHER,&WeatherSunny,sizeof(WeatherSunny))
			//if(inWriteRange)
			{
 				if(pmd[i].byte0.elmtType==0) //surface data
				{
					pmd[i].byte4.landslope=(pmd[i].byte4.landslope&0xE0)|Slope;
					pmd[i].baseheight=pmd[i].clearheight=landlevel; 
					
				} 	
			}
		 	moretiles=
				(	(!(pmd[i].byte1.lastElementOnTile))
					&&((i+1)<512)	); 
			i++;
			
		} while(moretiles);
		Rct2MapDataFunc(MDF_WRITE,x,y,pmd,512);
	} // if(*init)
	else	
	{
		Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);
	}

	return (TRUE);
  
}
////
int GetMapHeight
(	int *init,int done,int x,int y,PARKMAPPTRARRAY* lpMapPtrs,
	LPSCANLINE scanline, WORD parksize
)
{

#define C_EQU(a) ((*scanline)[y][x]=(a)&0XFE) 

	POINT xy;
	RECT ValidXYRange={1,1,255,255};

	int nw_corner,ne_corner,sw_corner,se_corner,
		CornertoCorner2,NWSE_Test,NESW_Test;
	int n_sign,s_sign,e_sign,w_sign;
	int nw_sign,ne_sign,se_sign,sw_sign;
	int moretiles, inWriteRange;

	int i;
	BYTE landlevel, Slope;	
	PARKMAPDATA pmd[512];
	LPPARKMAPDATA parkMapPtr;


	if(done)
	{
		Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);
		return (TRUE);
	}
	
	ValidXYRange.right=ValidXYRange.bottom=parksize-2;


	//if(inWriteRange=PointInRect(&ValidXYRange, MakePoint(x,y)))
	{	
		Slope=0;
  	}

	moretiles=TRUE;	

	if(!(*init))
		*init=Rct2MapDataFunc(MDF_INIT,0,0,NULL,0);
		
	if(*init)
	{
		i=0;
		Rct2MapDataFunc(MDF_READ,x,y,pmd,512);
		do
		{
			//WinWrite(RCT2_TITLE,RCT2_ADDR_WEATHER,&WeatherSunny,sizeof(WeatherSunny))
			//if(inWriteRange)
			{
 				if(pmd[i].byte0.elmtType==0) //surface data
				{
					Slope=pmd[i].byte4.landslope&~0xE0;
					landlevel=pmd[i].baseheight; 
					if(Slope!=0) 
						++landlevel;
					C_EQU(landlevel);
				} 	
			}
		 	moretiles=
				(	(!(pmd[i].byte1.lastElementOnTile))
					&&((i+1)<512)	); 
			i++;
			
		} while(moretiles);
	} // if(*init)
	else	
	{
		Rct2MapDataFunc(MDF_DONE,0,0,NULL,0);
	}

	return TRUE;
  
}

int SaveTerrainBMP(HWND hwnd,HINSTANCE hinstance)
{	
	int x,y,i;
	long error;	
	char bdata;
	HCURSOR hcursor, lhcursor; 

	SCANLINE scanline;
		
	char filetitle[HIGHFTL]="";
	DWORD nBytes,svNBytes;
	WORD parksize;


	OPENFILENAME  ofn;
	OFSTRUCT ofs;
	int hfile;
	SECURITY_ATTRIBUTES secuAttrb={sizeof(SECURITY_ATTRIBUTES),NULL,FALSE};

	PARKMAPPTRARRAY MapPtrs;

	int init;
	
	/*
		bmpFilehead.bmfh.bfType==BM_ID;
		bmpFilehead.bmih.bmiHeaderbiBitCount=8;
		bmpFilehead.bmih.bmiHeaderbiCompression==BI_RGB;
	*/


	BMPFILEHEAD_256
		bmpFilehead=
		{
			{	BM_ID,
				0,
				0,0,
				sizeof(BMPFILEHEAD_256),
			}
			,
			{
				{
					/*
					   DWORD  biSize; 
					   LONG   biWidth; 
					   LONG   biHeight; 
					   WORD   biPlanes; 
					   WORD   biBitCount 
					   DWORD  biCompression; 
					   DWORD  biSizeImage; 
					   LONG   biXPelsPerMeter; 
					   LONG   biYPelsPerMeter; 
					   DWORD  biClrUsed; 
					   DWORD  biClrImportant; 
					*/
					0,
					0,0,
					1,8,
					BI_RGB,
					0,
					720,720, 
					256,
					256
				}

				// , {}
			}
		};

	memset(scanline,0,sizeof(scanline)); 

	ofn.lStructSize=sizeof(ofn); 
    ofn.hwndOwner=hwnd; 
    ofn.hInstance=hinstance; 
    ofn.lpstrFilter="Windows Bitmap(*.bmp)\0*.bmp\0\0"; 
    ofn.lpstrCustomFilter=NULL; 
    ofn.nMaxCustFilter=NULL; 
    ofn.nFilterIndex=1; 
    ofn.lpstrFile=NULL; 
    ofn.nMaxFile=0; 
    ofn.lpstrFileTitle=&filetitle; 
    ofn.nMaxFileTitle=HIGHFTL; 
    ofn.lpstrInitialDir=NULL; 
    ofn.lpstrTitle="Save Bitmap Terrain As"; 
    ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES
		|OFN_OVERWRITEPROMPT; 
    //ofn.nFileOffset; 
    //ofn.nFileExtension; 
    ofn.lpstrDefExt="BMP";; 
    ofn.lCustData=0; 
    ofn.lpfnHook=NULL; 
    ofn.lpTemplateName=NULL;

	if (!GetOpenFileName(&ofn)) 
		return FALSE;
	
	if(WinRead(mainWindow,RCT2_TITLE,&parksize,RCT2_ADDR_MAPSIZE,2))
	{
		WinRead(mainWindow,RCT2_TITLE,&MapPtrs,RCT2_ADDR_PARKMAPPOINTERS,sizeof(PARKMAPPTRARRAY));

		bmpFilehead.bmih.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);

		bmpFilehead.bmfh.bfSize=sizeof(BMPFILEHEAD_256)+
			(bmpFilehead.bmih.bmiHeader.biSizeImage
				=EvenUp(parksize)*parksize);

		bmpFilehead.bmih.bmiHeader.biWidth=bmpFilehead.bmih.bmiHeader.biHeight=parksize;
		
		#define palcolor(i,c) (bmpFilehead.bmih.bmiColors[i].rgb##c)
		{
			for(i=0;i<256;i++)
			{
				palcolor(i,Red)=
				palcolor(i,Green)=
				palcolor(i,Blue)=
					i;
				palcolor(i,Reserved)=0;					
			}
		}
		#undef palcolor

		if(parksize>=3)
		{
			hcursor=LoadCursor(NULL,IDC_WAIT);
			lhcursor=SetCursor(hcursor); 
			
			init=FALSE;
			
			for (y=1;y<=parksize-2;y++)			
			{
				for (x=1;x<=parksize-2;x++)
				{
					GetMapHeight(&init,FALSE,
						x,y,&MapPtrs,&scanline,parksize);
					if(!init) goto ExitFor;
				}
			}
			GetMapHeight(&init,TRUE,0,0,NULL,NULL,0);

			ExitFor:

			if(init)
			{
				if(	(hfile=_sopen(&filetitle,_O_BINARY|_O_CREAT|_O_SEQUENTIAL|_O_RDWR,
						_SH_DENYNO,_S_IREAD|_S_IWRITE)
					)
					==-1
				)
					goto ExitIf;

				_write(hfile,&bmpFilehead,sizeof(BMPFILEHEAD_256));

				svNBytes=
					bmpFilehead.bmih.bmiHeader.biSizeImage
					/bmpFilehead.bmih.bmiHeader.biHeight;

				for(y=parksize-1;y>=0;y--)
				{
					nBytes=svNBytes;			
					_write(hfile,&(scanline[y]),nBytes);
				}
				_close(hfile);
			}

			ExitIf:
				hcursor=SetCursor(lhcursor); 
		}
				
	}
	return FALSE;

}

int LoadTerrainBMP(HWND hwnd,HINSTANCE hinstance)
{	
	int x,y;
	long error;	
	char bdata;
	HCURSOR hcursor, lhcursor; 

	SCANLINE scanline;
		
	char filetitle[HIGHFTL]="";
	DWORD nBytes,svNBytes;
	WORD parksize;


	OPENFILENAME  ofn;
	OFSTRUCT ofs;
	HFILE hfile;
	SECURITY_ATTRIBUTES secuAttrb={sizeof(SECURITY_ATTRIBUTES),NULL,FALSE};

	PARKMAPPTRARRAY MapPtrs;

	int init;

	BMPFILEHEAD bmpFilehead;

	memset(&scanline,0,sizeof(scanline)); 

	ofn.lStructSize=sizeof(ofn); 
    ofn.hwndOwner=hwnd; 
    ofn.hInstance=hinstance; 
    ofn.lpstrFilter="Windows Bitmap(*.bmp)\0*.bmp\0\0"; 
    ofn.lpstrCustomFilter=NULL; 
    ofn.nMaxCustFilter=NULL; 
    ofn.nFilterIndex=1; 
    ofn.lpstrFile=NULL; 
    ofn.nMaxFile=0; 
    ofn.lpstrFileTitle=&filetitle; 
    ofn.nMaxFileTitle=HIGHFTL; 
    ofn.lpstrInitialDir=NULL; 
    ofn.lpstrTitle="Open Bitmap Terrain"; 
    ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_LONGNAMES; 
    //ofn.nFileOffset; 
    //ofn.nFileExtension; 
    ofn.lpstrDefExt="BMP";; 
    ofn.lCustData=0; 
    ofn.lpfnHook=NULL; 
    ofn.lpTemplateName=NULL;
		
	if (!GetOpenFileName(&ofn)) 
		return FALSE;

	hfile=
		CreateFile
		(	&filetitle,GENERIC_READ,0,&secuAttrb,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,
			NULL
		);
	error=GetLastError(); 
	
	if (hfile==NULL) 
		return FALSE;
		
	nBytes=sizeof(BITMAPFILEHEADER);
	ReadFile(hfile,&bmpFilehead.bmfh,nBytes,&nBytes,NULL);
	nBytes=sizeof(BITMAPINFOHEADER);
	ReadFile(hfile,&bmpFilehead.bmih,nBytes,&nBytes,NULL);

	error=GetLastError();
	
	if(WinRead(mainWindow,RCT2_TITLE,&parksize,RCT2_ADDR_MAPSIZE,2))
	{
		
		WinRead(mainWindow,RCT2_TITLE,&MapPtrs,RCT2_ADDR_PARKMAPPOINTERS,sizeof(PARKMAPPTRARRAY));

		if ((bmpFilehead.bmfh.bfType==BM_ID)
			&&(bmpFilehead.bmih.biBitCount==8)
			&&(bmpFilehead.bmih.biWidth==bmpFilehead.bmih.biHeight)
			&&(bmpFilehead.bmih.biWidth==parksize)
			&&(bmpFilehead.bmih.biCompression==BI_RGB)
			&&(parksize>=3))

		{
			hcursor=LoadCursor(NULL,IDC_WAIT);
			lhcursor=SetCursor(hcursor); 
			
			SetFilePointer(hfile,sizeof(BMPFILEPAL),NULL,FILE_CURRENT);

			svNBytes=bmpFilehead.bmih.biSizeImage/bmpFilehead.bmih.biHeight;
			
			for (y=parksize-1;y>=0;y--)
			{
				nBytes=svNBytes;			
				ReadFile(hfile,&(scanline[y]),nBytes,&nBytes,NULL);			
			};

			CloseHandle(hfile); 			

			init=FALSE;
			
			for (y=1;y<=parksize-2;y++)			
			{
				for (x=1;x<=parksize-2;x++)
				{
					SetMapHeight(&init,FALSE,
						x,y,&MapPtrs,&scanline,parksize);
					if(!init) goto ExitFor;
				}
			}

			SetMapHeight(&init,TRUE,0,0,NULL,NULL,0);
			if(!init) goto ExitFor;

			return TRUE;
			ExitFor:
			
			hcursor=SetCursor(lhcursor); 
		}
	}
	CloseHandle(hfile); 			
	return FALSE;

}
	
int GenerateRandomTerrain(int avgheight,int incline,int variation)
{
	SCANLINE scanline;




}




