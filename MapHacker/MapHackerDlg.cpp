// MapHackerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapHacker.h"
#include "MapHackerDlg.h"
#include<codeshortcuts.h>
//#include"RESOURCE.H"
#include<rct2lib.h>

extern "C"
{
#include<wprocess.h>
}

#include "rct2_miniHeader.h"

SV6_PARKMAPDATABLOCK map;
SV6_PARKMAPPTRARRAY mp;

#define MAP_BYTE_EDIT(a) (1020+(a))

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapHackerDlg dialog

CMapHackerDlg::CMapHackerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapHackerDlg::IDD, pParent)
{
	int i;
	//{{AFX_DATA_INIT(CMapHackerDlg)
	hexData = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ad.x=1;
	ad.y=1;
	ad.z=0;

	for_i0(i,8)
	{
	ad.d[i]=0;
	}

}

void CMapHackerDlg::DoDataExchange(CDataExchange* pDX)
{
	int i;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapHackerDlg)
	DDX_Text(pDX, IDC__EDIT__HEX_DATA, hexData);
	//}}AFX_DATA_MAP
	DDX_Text(pDX,IDC_EDIT_X,ad.x);
	DDV_MinMaxInt(pDX,ad.x,0,255);
	DDX_Text(pDX,IDC_EDIT_Y,ad.y);
	DDV_MinMaxInt(pDX,ad.y,0,255);
	DDX_Text(pDX,IDC_EDIT_Z,ad.z);
	DDV_MinMaxInt(pDX,ad.z,0,15);

	for_i0(i,8)
	{
	DDX_Text(pDX,MAP_BYTE_EDIT(i),ad.d[i]);
	DDV_MinMaxInt(pDX,ad.d[i],0,255);
	}

}

CMapHackerDlg::DdxGet()
{
	UpdateData(true);
}
CMapHackerDlg::DdxSet()
{
	UpdateData(false);
}


BEGIN_MESSAGE_MAP(CMapHackerDlg, CDialog)
	//{{AFX_MSG_MAP(CMapHackerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC__BUTTON__HEX_GET, OnButtonHexGet)
	ON_BN_CLICKED(IDC__BUTTON__HEX_SET, OnButtonHexSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapHackerDlg message handlers

BOOL CMapHackerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMapHackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMapHackerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMapHackerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


_getPointers()
{
	int x,y;
	DWORD pdw;
	WinRead
	(	NULL,
		"RollerCoaster Tycoon 2"
		,mp
		,RCT2__ADDR__MAP_PTR 
		,sz(mp)
	);

	for_i0(y,256)
	{
	for_i0(x,256)
	{
		pdw=(DWORD)mp[y][x];
		pdw-=(DWORD)RCT2_ADDR_MAP;
		pdw+=(DWORD)&map;
		mp[y][x]=(LP_SV6_PARKMAPDATA)pdw;
	}
	}
}

_setPointers()
{
	int x,y;
	DWORD pdw;

	for_i0(y,256)
	{
	for_i0(x,256)
	{
		pdw=(DWORD)mp[y][x];
		pdw-=(DWORD)&map;
		pdw+=(DWORD)RCT2_ADDR_MAP;
		mp[y][x]=(LP_SV6_PARKMAPDATA)pdw;
	}
	}

	WinWrite
	(	NULL,
		"RollerCoaster Tycoon 2"
		,RCT2__ADDR__MAP_PTR 
		,mp
		,sz(mp)
	);
}

bool _GetMapData()
{
	_getPointers();

	
	return
	WinRead
	(	NULL,
		"RollerCoaster Tycoon 2"
		,map
		,RCT2_ADDR_MAP 
		,sz(map)
	);
	
}

bool _SetMapData()
{
	_setPointers();

	return
	WinWrite
	(	NULL,
		"RollerCoaster Tycoon 2"
		,RCT2_ADDR_MAP 
		,map
		,sz(map)
	);
}

void CMapHackerDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here

	SV6_PARKMAPDATA*md;
	BYTE*mdb;
	int z,i;

	DdxGet();
	
	if(!_GetMapData())return;

	md=mp[ad.y][ad.x];

	z=0;
	while((z<ad.z)&&(!(md->byte1.lastElementOnTile)))
	{
	md++;		
	z++;
	}
	ad.z=z;
	mdb=(BYTE*)md;

	for_i0(i,8)
	{
		ad.d[i]=mdb[i];
	}

	DdxSet();

}

void CMapHackerDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here

	SV6_PARKMAPDATA*md;
	BYTE*mdb;
	int z,i;

	DdxGet();
	
	if(!_GetMapData())return;

	md=mp[ad.y][ad.x];

	z=0;
	while((z<ad.z)&&(!(md->byte1.lastElementOnTile)))
	{
	md++;		
	z++;
	}
	ad.z=z;
	mdb=(BYTE*)md;

	for_i0(i,8)
	{
		mdb[i]=ad.d[i];
	}

	if(!_SetMapData())return;

	DdxSet();
	
}

void CMapHackerDlg::OnButtonHexGet() 
{
	// TODO: Add your control notification handler code here
	char*s;
	
	DdxGet();

	hexData.Format
	(	
		"%02.2hX\r\n"
		"%02.2hX\r\n"
		"%02.2hX\r\n"
		"%02.2hX\r\n"
		"%02.2hX\r\n"
		"%02.2hX\r\n"
		"%02.2hX\r\n"
		"%02.2hX"
		,ad.d[0]
		,ad.d[1]
		,ad.d[2]
		,ad.d[3]
		,ad.d[4]
		,ad.d[5]
		,ad.d[6]
		,ad.d[7]
	);
	
	DdxSet();
}

void CMapHackerDlg::OnButtonHexSet() 
{
	// TODO: Add your control notification handler code here
	char*s;

	DdxGet();

	s=hexData.GetBuffer(0);

	sscanf
	(	
		s
		,
		"%hx "
		"%hx "
		"%hx "
		"%hx "
		"%hx "
		"%hx "
		"%hx "
		"%hx"
		,&ad.d[0]
		,&ad.d[1]
		,&ad.d[2]
		,&ad.d[3]
		,&ad.d[4]
		,&ad.d[5]
		,&ad.d[6]
		,&ad.d[7]
	);
	
	DdxSet();
}
