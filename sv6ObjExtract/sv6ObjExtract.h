// sv6ObjExtract.h : main header file for the SV6OBJEXTRACT application
//

#if !defined(AFX_SV6OBJEXTRACT_H__628FC812_F83E_4E17_9AAF_434DF552F216__INCLUDED_)
#define AFX_SV6OBJEXTRACT_H__628FC812_F83E_4E17_9AAF_434DF552F216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSv6ObjExtractApp:
// See sv6ObjExtract.cpp for the implementation of this class
//

class CSv6ObjExtractApp : public CWinApp
{
public:
	CSv6ObjExtractApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSv6ObjExtractApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSv6ObjExtractApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SV6OBJEXTRACT_H__628FC812_F83E_4E17_9AAF_434DF552F216__INCLUDED_)
