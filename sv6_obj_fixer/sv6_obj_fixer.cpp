// sv6_obj_fixer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "sv6_obj_fixer.h"
#include "sv6_obj_fixerDLG.h"
#include "RCT2\SV6\SV6_OBJDAT_FIX.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

InitProgram()
{
//	InitObjects();
}


/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerApp

BEGIN_MESSAGE_MAP(CSv6_obj_fixerApp, CWinApp)
	//{{AFX_MSG_MAP(CSv6_obj_fixerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerApp construction

CSv6_obj_fixerApp::CSv6_obj_fixerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSv6_obj_fixerApp object

CSv6_obj_fixerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerApp initialization

BOOL CSv6_obj_fixerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CSv6_obj_fixerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse;

	InitProgram();	
	
	nResponse=dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
