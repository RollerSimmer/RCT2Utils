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


//functions
public:
	bool InDrawRange();	
	DrawPreview();
	FreeAllImgs();

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
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ParkDat_Class_ImgPreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(ParkDat_Class_ImgPreview)
	afx_msg void OnActionUpdate();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKDAT_CLASS_IMGPREVIEW_H__F4979FE8_6EB3_4FED_9691_0F05D35F778E__INCLUDED_)
