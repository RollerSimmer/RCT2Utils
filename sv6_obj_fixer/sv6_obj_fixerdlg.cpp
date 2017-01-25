// sv6_obj_fixerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sv6_obj_fixer.h"
#include "sv6_obj_fixerDLG.h"
#include <FileIO2.h>
#include <FCNTL.H>
#include <io.h>
#include <SHARE.H>
#include <sys/STAT.H>
#include <direct.h>
#include "rct2/sv6/SV6_FIXOBJECTS.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerDlg dialog

CSv6_obj_fixerDlg::CSv6_obj_fixerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSv6_obj_fixerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSv6_obj_fixerDlg)
	m_sv6FileName = _T("");
	m_messageText = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSv6_obj_fixerDlg::OnCancel()
{
	this->OnOK();
}

void CSv6_obj_fixerDlg::OnOK()
{
	UpdateData(DDX_GET);

	strcpy(sv6FileName,m_sv6FileName.GetBuffer(0));

	settings_fHndl=_sopen(settings_filename,_O_BINARY|_O_CREAT|_O_RDWR|_O_TRUNC,_SH_DENYNO,_S_IREAD|_S_IWRITE);

	sprintf
	(	ioBuffer,
		"%s\r\n",
		sv6FileName
	);
	
	_write
	(	settings_fHndl,
		ioBuffer,
		settings_fileLength=
			__min
			(	strlen(ioBuffer),
				sizeof(ioBuffer)-1					
			)
	);

	_close(settings_fHndl);


	CDialog::OnOK();
}

void CSv6_obj_fixerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSv6_obj_fixerDlg)
	DDX_Control(pDX, IDC_EDIT_SV6NAME, m_sv6FileNameEdit);
	DDX_Text(pDX, IDC_EDIT_SV6NAME, m_sv6FileName);
	DDV_MaxChars(pDX, m_sv6FileName, 128);
	DDX_Text(pDX, IDC_MESSAGE, m_messageText);
	DDV_MaxChars(pDX, m_messageText, 256);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSv6_obj_fixerDlg, CDialog)
	//{{AFX_MSG_MAP(CSv6_obj_fixerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_WRITESV6FILE, OnButtonWritesv6file)
	ON_BN_CLICKED(IDC_BUTTON_SV6NAME, OnButtonSv6name)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerDlg message handlers

int MakeFullFileName(char *buffer,char *filename,int maxLen)
{
	char 
		//drive[3]="C:",
		path[FILENAME_MAXSIZE];

	_getcwd(path,sizeof(path)-1);
	if(strcmp(path,"\\\\")==0)
		path[1]=0;
	else 
		strncat(path,"\\",FILENAME_MAXSIZE);
	
//	drive[0]=_getdrive()+'A'-1;

//	strncpy(buffer,drive,maxLen);
	strncpy(buffer,path,maxLen);
	strncat(buffer,filename,maxLen);

	return TRUE;
}

BOOL CSv6_obj_fixerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	MakeFullFileName
	(	settings_filename,
		SETTINGS_FILENAME,
		sizeof(settings_filename)-1
	);

	if(FExist(settings_filename)) 
	{
		settings_fHndl=
			_sopen(settings_filename,_O_BINARY|_O_RDWR,_SH_DENYNO);

		_read
		(	settings_fHndl,
			ioBuffer,
			settings_fileLength=
				__min
				(	filelength(settings_fHndl),
					sizeof(ioBuffer)-1					
				)
		);

		ioBuffer[settings_fileLength]=0;

		sscanf
		(	ioBuffer,
			"%[^\r\n,;]",
			sv6FileName
		);


		_close(settings_fHndl);

	}
	else 
	{
		strcpy(sv6FileName,"\0");
	}

	m_sv6FileName=sv6FileName;

	UpdateData(DDX_SET);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSv6_obj_fixerDlg::OnPaint() 
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

HCURSOR CSv6_obj_fixerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSv6_obj_fixerDlg::OnButtonSv6name() 
{
	// TODO: Add your control notification handler code here

	#define SV6_FILENAME_FILTER "RCT2 park file (.SV6)\0*.SV6\0All files\0*.*\0"
	#define SV6_FILENAME_DEFEXT "SV6"
	#define SV6_FILENAME_TITLE "Select SV6 File"
	#define SV6_FILENAME_FLAGS \
		(OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER)

	char filename[FILENAME_MAXSIZE]="\0";

	if
	(	GetSaveFileName_Quick
		(	
			sizeof(filename),
			filename,
			SV6_FILENAME_FLAGS,
			SV6_FILENAME_FILTER,
			SV6_FILENAME_DEFEXT,
			SV6_FILENAME_TITLE
		)
	)
	{
		UpdateData(DDX_GET);
		m_sv6FileName=filename;
		UpdateData(DDX_SET);
	}
	
}

void CSv6_obj_fixerDlg::OnButtonWritesv6file() 
{
	// TODO: Add your control notification handler code here
	char 
		sv6File[FILENAME_MAXSIZE];

	UpdateData(DDX_GET);
	strcpy(sv6File,m_sv6FileName.GetBuffer(0));

	//fix sv6 objects	
	FixSV6Objects
	(
		this,
		sv6File
	);
	

	//save sv6
}

