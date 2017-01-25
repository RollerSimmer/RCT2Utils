// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "ParkDat.h"
#include "DlgProxy.h"
#include "ParkDatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParkDatDlgAutoProxy

IMPLEMENT_DYNCREATE(CParkDatDlgAutoProxy, CCmdTarget)

CParkDatDlgAutoProxy::CParkDatDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CParkDatDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CParkDatDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CParkDatDlgAutoProxy::~CParkDatDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CParkDatDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CParkDatDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CParkDatDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CParkDatDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CParkDatDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IParkDat to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {61F7709A-F31A-4B2B-BA08-043CC44553C7}
static const IID IID_IParkDat =
{ 0x61f7709a, 0xf31a, 0x4b2b, { 0xba, 0x8, 0x4, 0x3c, 0xc4, 0x45, 0x53, 0xc7 } };

BEGIN_INTERFACE_MAP(CParkDatDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CParkDatDlgAutoProxy, IID_IParkDat, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {D6004899-7FD4-492D-9D5C-1DE19FDB9E8A}
IMPLEMENT_OLECREATE2(CParkDatDlgAutoProxy, "ParkDat.Application", 0xd6004899, 0x7fd4, 0x492d, 0x9d, 0x5c, 0x1d, 0xe1, 0x9f, 0xdb, 0x9e, 0x8a)

/////////////////////////////////////////////////////////////////////////////
// CParkDatDlgAutoProxy message handlers
