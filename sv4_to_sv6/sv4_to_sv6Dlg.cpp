// sv4_to_sv6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "sv4_to_sv6.h"
#include "sv4_to_sv6Dlg.h"
#include <FileIO2.h>
#include <FCNTL.H>
#include <io.h>
#include <SHARE.H>
#include <sys/STAT.H>
#include <direct.h>
#include "1to2_convert/Sv4to6Convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSv4_to_sv6Dlg dialog

CSv4_to_sv6Dlg::CSv4_to_sv6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSv4_to_sv6Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSv4_to_sv6Dlg)
	m_sv4FileName = _T("");
	m_sv6FileName = _T("");
	m_message = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSv4_to_sv6Dlg::OnCancel()
{
	this->OnOK();
}

void CSv4_to_sv6Dlg::OnOK()
{
	UpdateData(DDX_GET);

	strcpy(sv4FileName,m_sv4FileName.GetBuffer(0));
	strcpy(sv6FileName,m_sv6FileName.GetBuffer(0));

	settings_fHndl=_sopen(settings_filename,_O_BINARY|_O_CREAT|_O_RDWR|_O_TRUNC,_SH_DENYNO,_S_IREAD|_S_IWRITE);

	sprintf
	(	ioBuffer,
		"%s\r\n"
		"%s\r\n",
		sv4FileName,
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

void CSv4_to_sv6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSv4_to_sv6Dlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_EDIT_SV6NAME, m_sv6FileNameEdit);
	DDX_Control(pDX, IDC_EDIT_SV4NAME, m_sv4FileNameEdit);
	DDX_Text(pDX, IDC_EDIT_SV4NAME, m_sv4FileName);
	DDV_MaxChars(pDX, m_sv4FileName, 128);
	DDX_Text(pDX, IDC_EDIT_SV6NAME, m_sv6FileName);
	DDV_MaxChars(pDX, m_sv6FileName, 128);
	DDX_Text(pDX, IDC_MESSAGE, m_message);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSv4_to_sv6Dlg, CDialog)
	//{{AFX_MSG_MAP(CSv4_to_sv6Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SV4NAME, OnButtonSv4name)
	ON_BN_CLICKED(IDC_BUTTON_WRITESV6FILE, OnButtonWritesv6file)
	ON_BN_CLICKED(IDC_BUTTON_SV6NAME, OnButtonSv6name)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSv4_to_sv6Dlg message handlers

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

BOOL CSv4_to_sv6Dlg::OnInitDialog()
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
			"%[^\r\n,;] "
			"%[^\r\n,;]",
			sv4FileName,
			sv6FileName
		);


		_close(settings_fHndl);

	}
	else 
	{
		strcpy(sv6FileName,"\0");
		strcpy(sv4FileName,sv6FileName);
	}

	m_sv4FileName=sv4FileName;
	m_sv6FileName=sv6FileName;

	UpdateData(DDX_SET);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSv4_to_sv6Dlg::OnPaint() 
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

HCURSOR CSv4_to_sv6Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSv4_to_sv6Dlg::OnButtonSv4name() 
{
	// TODO: Add your control notification handler code here
	
	#define SV4_FILENAME_FILTER "RCT park file (.SV4)\0*.SV4\0All files\0*.*\0"
	#define SV4_FILENAME_DEFEXT "SV4"
	#define SV4_FILENAME_TITLE "Select SV4 File"
	#define SV4_FILENAME_FLAGS \
		(OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER)

	char filename[FILENAME_MAXSIZE]="\0";

	if
	(	GetSaveFileName_Quick
		(	
			sizeof(filename),
			filename,
			SV4_FILENAME_FLAGS,
			SV4_FILENAME_FILTER,
			SV4_FILENAME_DEFEXT,
			SV4_FILENAME_TITLE
		)
	)
	{
		UpdateData(DDX_GET);
		m_sv4FileName=filename;
		UpdateData(DDX_SET);
	}
}

void CSv4_to_sv6Dlg::OnButtonSv6name() 
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

void CSv4_to_sv6Dlg::OnButtonWritesv6file() 
{
	// TODO: Add your control notification handler code here
	char 
		sv4File[FILENAME_MAXSIZE],
		sv6File[FILENAME_MAXSIZE];

	UpdateData(DDX_GET);
	strcpy(sv4File,m_sv4FileName.GetBuffer(0));
	strcpy(sv6File,m_sv6FileName.GetBuffer(0));

	//convert sv4->sv6
	Sv4to6Convert(this,sv6File,sv4File);

	//save sv6

}
