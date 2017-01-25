// sv4_to_sv6.h : main header file for the SV4_TO_SV6 application
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
// CSv4_to_sv6App:
// See sv4_to_sv6.cpp for the implementation of this class
//

class CSv4_to_sv6App : public CWinApp
{
public:
	CSv4_to_sv6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSv4_to_sv6App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSv4_to_sv6App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SV4_TO_SV6_H__7EE5C8B7_ABFB_484B_8F37_085D9B607405__INCLUDED_)
