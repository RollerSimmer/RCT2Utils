// ParkDat_Class_ImgPreview.cpp : implementation file
//

#include "stdafx.h"
#include "ParkDat.h"
#include "ParkDat_Class_ImgPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParkDat_Class_ImgPreview

ParkDat_Class_ImgPreview::ParkDat_Class_ImgPreview()
{
	i=0;do
	{
		imgs[i++]=new(IMG_256);	
	}
	while(i<SV6_OBJDAT_NUMENTRIES_ALL);
}

ParkDat_Class_ImgPreview::~ParkDat_Class_ImgPreview()
{
}

ParkDat_Class_ImgPreview::OnPaint()
{	
	if(InDrawRange())
	{
		DrawPreview();
	}

	//CStatic::OnPaint();
}

bool ParkDat_Class_ImgPreview::InDrawRange()
{
	bool result;

	result=true;

	return result;
}

ParkDat_Class_ImgPreview::DrawPreview()
{

}



BEGIN_MESSAGE_MAP(ParkDat_Class_ImgPreview, CStatic)
	//{{AFX_MSG_MAP(ParkDat_Class_ImgPreview)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParkDat_Class_ImgPreview message handlers
