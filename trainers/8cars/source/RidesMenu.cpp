// RidesMenu.cpp : implementation file
//

#include "stdafx.h"
#include "8cars.h"
#include "RidesMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RidesMenu dialog


RidesMenu::RidesMenu(CWnd* pParent /*=NULL*/)
	: CDialog(RidesMenu::IDD, pParent)
{
	//{{AFX_DATA_INIT(RidesMenu)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RidesMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RidesMenu)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RidesMenu, CDialog)
	//{{AFX_MSG_MAP(RidesMenu)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RidesMenu message handlers
