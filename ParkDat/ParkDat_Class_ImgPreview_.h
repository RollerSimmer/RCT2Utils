#if !defined(AFX_PARKDAT_CLASS_IMGPREVIEW_H__F4979FE8_6EB3_4FED_9691_0F05D35F778E__INCLUDED_)
#define AFX_PARKDAT_CLASS_IMGPREVIEW_H__F4979FE8_6EB3_4FED_9691_0F05D35F778E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParkDat_Class_ImgPreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParkDat_Class_ImgPreview window

#include<img256_lib.h>
#include<rct2Lib.h>


class ParkDat_Class_ImgPreview : public CStatic
{
//data 
public:
	int i;

	IMG_256*imgs[SV6_OBJDAT_NUMENTRIES_ALL];

// Construction
public:
	ParkDat_Class_ImgPreview();

// Attributes
public:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParkDat_Class_ImgPreview)
	OnPaint();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ParkDat_Class_ImgPreview();

	bool InDrawRange();	
	DrawPreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(ParkDat_Class_ImgPreview)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKDAT_CLASS_IMGPREVIEW_H__F4979FE8_6EB3_4FED_9691_0F05D35F778E__INCLUDED_)
