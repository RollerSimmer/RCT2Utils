// ParkDat.h : main header file for the PARKDAT application
//

#if !defined(AFX_PARKDAT_H__C7013E26_41FE_48D9_971D_A5A46C519341__INCLUDED_)
#define AFX_PARKDAT_H__C7013E26_41FE_48D9_971D_A5A46C519341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CParkDatApp:
// See ParkDat.cpp for the implementation of this class
//

class CParkDatApp : public CWinApp
{
public:
	HACCEL accel;

	CParkDatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkDatApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code,LPMSG lpMsg); 
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CParkDatApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CParkDatApp*theAppP;



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKDAT_H__C7013E26_41FE_48D9_971D_A5A46C519341__INCLUDED_)
