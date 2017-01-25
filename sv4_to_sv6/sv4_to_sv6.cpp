// sv4_to_sv6.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "sv4_to_sv6.h"
#include "sv4_to_sv6Dlg.h"
#include "RCT2\SV6\SV6_OBJDAT.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

InitProgram()
{
	InitObjects();
}


/////////////////////////////////////////////////////////////////////////////
// CSv4_to_sv6App

BEGIN_MESSAGE_MAP(CSv4_to_sv6App, CWinApp)
	//{{AFX_MSG_MAP(CSv4_to_sv6App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSv4_to_sv6App construction

CSv4_to_sv6App::CSv4_to_sv6App()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSv4_to_sv6App object

CSv4_to_sv6App theApp;

/////////////////////////////////////////////////////////////////////////////
// CSv4_to_sv6App initialization

BOOL CSv4_to_sv6App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CSv4_to_sv6Dlg dlg;
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
