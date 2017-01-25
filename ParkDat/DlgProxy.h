// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__F5275413_2950_45FC_A76C_A5FD034CD45B__INCLUDED_)
#define AFX_DLGPROXY_H__F5275413_2950_45FC_A76C_A5FD034CD45B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParkDatDlg;

/////////////////////////////////////////////////////////////////////////////
// CParkDatDlgAutoProxy command target

class CParkDatDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CParkDatDlgAutoProxy)

	CParkDatDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CParkDatDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkDatDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CParkDatDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CParkDatDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CParkDatDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CParkDatDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__F5275413_2950_45FC_A76C_A5FD034CD45B__INCLUDED_)
