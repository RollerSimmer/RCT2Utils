// ParkDat_Class_ImgPreview.cpp : implementation file
//

#include "stdafx.h"
#include "ParkDat.h"
#include "ParkDat_Class_ImgPreview.h"
#include<malloc.h>

#include<BMPLib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParkDat_Class_ImgPreview

MSPAL_FILESTRUCT*rct2Pal;

COLORREF colorRefMap[256];

#define READ_BG_COLOR__FROM_RESOURCE 1

#define STRETCH_IMG 0

bool imgsInitialized=false;

LoadDrawPalette()
{
	int pI;
	CString bgColorStr;
	char*bgcs;

	WORD r,g,b;

	union
	{
		DWORD pad;
		WORD iRsrc;
		LPCTSTR sRsrc;
	};
	
	pad=0;
	iRsrc=IDR_RCT2_PALETTE;

	RGBQUAD_RGB*c;


	HRSRC hpalFind;
	HGLOBAL hpal;

	hpalFind=
		FindResource
		(	NULL
			,
			sRsrc
			,
			"PALETTE"
		);
	hpal=LoadResource(NULL,hpalFind);
	rct2Pal=(MSPAL_FILESTRUCT*)LockResource(hpal);

	#if READ_BG_COLOR__FROM_RESOURCE
		bgColorStr.LoadString(IDS__BG_COLOR);
		bgcs=bgColorStr.GetBuffer(0);

		c=&rct2Pal->chunk.colors[0];
		sscanf
		(	bgcs
			," %hi %hi %hi "
			,&r
			,&g
			,&b
		);		

		c->rgbRed=r;
		c->rgbGreen=g;
		c->rgbBlue=b;
		
	#endif

	
	
	for(pI=0;pI<256;pI++)
	{
		c=&rct2Pal->chunk.colors[pI];
		if(pI<rct2Pal->chunk.numColors)
		{
			colorRefMap[pI]
			=RGB(c->rgbRed,c->rgbGreen,c->rgbBlue);
		}

	}

}


ParkDat_Class_ImgPreview::ParkDat_Class_ImgPreview()
{
	i=0;do
	{
		imgs[i]=new(IMG_256);	
		memset(imgs[i],0,sizeof(IMG_256));		
	}
	while((++i)<SV6_OBJDAT_NUMENTRIES_ALL);

	LoadDrawPalette();
	
	imgsInitialized=true;
}

ParkDat_Class_ImgPreview::~ParkDat_Class_ImgPreview()
{
}

bool ParkDat_Class_ImgPreview::InDrawRange()
{
	bool result;

	result=true;

	if(!imgsInitialized)
		return(false);
	else if(i==-1)
		result=false;
	else if(i>=RCT2_WATER__BASE_TABLE_INDEX)
		result=false;
	else if(imgs[i]->imgData==NULL)
		result=false;

	return(result);
	
}

#define PAGECOPY 1


#if PAGECOPY
PreparePasteDC(CDC*mdc,CDC*dc,IMG_256&img,int w,int h)
{
#else
PreparePasteDC(CDC*dc,IMG_256&img,int w,int h)
{
#endif

	const int RCT2_BG_INDEX=0;

	int x,y,pali;
	RGBQUAD_RGB c;


	y=0;
	do
	{
		if((y<img.h)&&(y<h))
		{
			x=0;
			do
			{
				if((x<img.w)&&(x<w))
				{
					pali=img.pix(x,y);
					if(pali!=RCT2_BG_INDEX)
					{
					#if PAGECOPY
					mdc->SetPixel(x,y,colorRefMap[pali]);
					#else
					dc->SetPixel(x,y,colorRefMap[pali]);
					#endif
					}
				}
			}
			while((++x)<img.w);
		}
	}
	while((++y)<img.h);

}

ParkDat_Class_ImgPreview::DrawPreview()
{
	CDC
		*dc
#if PAGECOPY
		,mdc
#endif
	;

	CBitmap mbmp;

	CRect r,fr;
	int w,h;
	CBrush bgBrush;

	dc=this->GetWindowDC();

	this->GetWindowRect(LPRECT(r));
	w=r.right-r.left;
	h=r.bottom-r.top;
	fr.SetRect(0,0,w,h);

	#if READ_BG_COLOR__FROM_RESOURCE
		bgBrush.CreateSolidBrush(colorRefMap[0]);
	#else
		bgBrush.CreateSolidBrush(RGB(128,128,128));
	#endif

#if PAGECOPY
	mdc.CreateCompatibleDC(dc);
	
	mbmp.CreateCompatibleBitmap(dc,w,h);

	mdc.SelectObject(mbmp);
//	mdc=new CDC;
#endif

#if PAGECOPY
	mdc.FillRect(&fr,&bgBrush);
#else
	dc->FillRect(&fr,&bgBrush);
#endif


	if(InDrawRange())
	{

		#if PAGECOPY
			PreparePasteDC(&mdc,dc,*this->imgs[i],w,h);

			#if(STRETCH_IMG)

				dc->StretchBlt
				(	0,0,w,h
					,&mdc
					,0,0,imgs[i]->w,imgs[i]->h
					,SRCCOPY
				);
			#else

				dc->StretchBlt
				(	0,0,w,h
					,&mdc
					,0,0,w,h
					,SRCCOPY
				);

			#endif
		#else
			PreparePasteDC(dc,*this->imgs[i],w,h);
		#endif

		#if PAGECOPY
//			delete mdc;
		#endif
	}
	else
	{
		dc->BitBlt
		(	0,0,w,h
			,&mdc
			,0,0
			,SRCCOPY
		);
	}

	#if PAGECOPY

		mdc.DeleteDC();
		
		mbmp.DeleteObject();
	//	mdc=new CDC;
	#endif


}



BEGIN_MESSAGE_MAP(ParkDat_Class_ImgPreview, CStatic)
	//{{AFX_MSG_MAP(ParkDat_Class_ImgPreview)
	ON_COMMAND(ID_ACTION_UPDATE, OnActionUpdate)
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParkDat_Class_ImgPreview message handlers

void ParkDat_Class_ImgPreview::OnActionUpdate() 
{
	// TODO: Add your command handler code here
	//DrawPreview();
	
}

int ParkDat_Class_ImgPreview::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//	DrawPreview();
	
	return CStatic::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void ParkDat_Class_ImgPreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	DrawPreview();
	CStatic::OnLButtonDown(nFlags, point);
}

void ParkDat_Class_ImgPreview::OnClicked() 
{
	// TODO: Add your control notification handler code here
	DrawPreview();
	
}

void ParkDat_Class_ImgPreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	DrawPreview();
	
	// Do not call CStatic::OnPaint() for painting messages
}



ParkDat_Class_ImgPreview::FreeAllImgs()
{
	i=0;do
	{
		#if 0
			imgs[i]->ImgFree();
		#endif
		free(imgs[i]);
	}
	while((++i)<SV6_OBJDAT_NUMENTRIES_ALL);

}

void ParkDat_Class_ImgPreview::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	FreeAllImgs();
	
	CStatic::OnClose();
}

int ParkDat_Class_ImgPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void ParkDat_Class_ImgPreview::OnDestroy() 
{

	FreeAllImgs();
	
	CStatic::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
