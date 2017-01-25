// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__D92E2DB1_5377_44C1_85D0_60236D0B1477__INCLUDED_)
#define AFX_DLGPROXY_H__D92E2DB1_5377_44C1_85D0_60236D0B1477__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRCT2Landmark_LScenDlg;

/////////////////////////////////////////////////////////////////////////////
// CRCT2Landmark_LScenDlgAutoProxy command target

class CRCT2Landmark_LScenDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CRCT2Landmark_LScenDlgAutoProxy)

	CRCT2Landmark_LScenDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CRCT2Landmark_LScenDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRCT2Landmark_LScenDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRCT2Landmark_LScenDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CRCT2Landmark_LScenDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CRCT2Landmark_LScenDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CRCT2Landmark_LScenDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__D92E2DB1_5377_44C1_85D0_60236D0B1477__INCLUDED_)
