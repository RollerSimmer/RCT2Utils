// sv6_obj_fixer.h : main header file for the SV4_TO_SV6 application
//

#if !defined(AFX_SV4_TO_SV6_H__7EE5C8B7_ABFB_484B_8F37_085D9B607405__INCLUDED_)
#define AFX_SV4_TO_SV6_H__7EE5C8B7_ABFB_484B_8F37_085D9B607405__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerApp:
// See sv6_obj_fixer.cpp for the implementation of this class
//

class CSv6_obj_fixerApp : public CWinApp
{
public:
	CSv6_obj_fixerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSv6_obj_fixerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSv6_obj_fixerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SV4_TO_SV6_H__7EE5C8B7_ABFB_484B_8F37_085D9B607405__INCLUDED_)
