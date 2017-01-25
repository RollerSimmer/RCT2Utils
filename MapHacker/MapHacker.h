// MapHacker.h : main header file for the MAPHACKER application
//

#if !defined(AFX_MAPHACKER_H__18C34631_858E_4A80_BEF3_E3943E0DA117__INCLUDED_)
#define AFX_MAPHACKER_H__18C34631_858E_4A80_BEF3_E3943E0DA117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapHackerApp:
// See MapHacker.cpp for the implementation of this class
//

class CMapHackerApp : public CWinApp
{
public:
	CMapHackerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapHackerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMapHackerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPHACKER_H__18C34631_858E_4A80_BEF3_E3943E0DA117__INCLUDED_)
