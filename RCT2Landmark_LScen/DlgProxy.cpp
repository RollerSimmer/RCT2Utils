// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "RCT2Landmark_LScen.h"
#include "DlgProxy.h"
#include "RCT2Landmark_LScenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRCT2Landmark_LScenDlgAutoProxy

IMPLEMENT_DYNCREATE(CRCT2Landmark_LScenDlgAutoProxy, CCmdTarget)

CRCT2Landmark_LScenDlgAutoProxy::CRCT2Landmark_LScenDlgAutoProxy()
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
	ASSERT_KINDOF(CRCT2Landmark_LScenDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CRCT2Landmark_LScenDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CRCT2Landmark_LScenDlgAutoProxy::~CRCT2Landmark_LScenDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CRCT2Landmark_LScenDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CRCT2Landmark_LScenDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CRCT2Landmark_LScenDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRCT2Landmark_LScenDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CRCT2Landmark_LScenDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IRCT2Landmark_LScen to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {AC077A33-2B08-4081-A1EA-27B21DFD6BB5}
static const IID IID_IRCT2Landmark_LScen =
{ 0xac077a33, 0x2b08, 0x4081, { 0xa1, 0xea, 0x27, 0xb2, 0x1d, 0xfd, 0x6b, 0xb5 } };

BEGIN_INTERFACE_MAP(CRCT2Landmark_LScenDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CRCT2Landmark_LScenDlgAutoProxy, IID_IRCT2Landmark_LScen, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {AE238DB8-F57C-447B-B284-1894234CE28E}
IMPLEMENT_OLECREATE2(CRCT2Landmark_LScenDlgAutoProxy, "RCT2Landmark_LScen.Application", 0xae238db8, 0xf57c, 0x447b, 0xb2, 0x84, 0x18, 0x94, 0x23, 0x4c, 0xe2, 0x8e)

/////////////////////////////////////////////////////////////////////////////
// CRCT2Landmark_LScenDlgAutoProxy message handlers
