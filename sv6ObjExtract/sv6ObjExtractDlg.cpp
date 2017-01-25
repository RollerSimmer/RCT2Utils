// sv6ObjExtractDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sv6ObjExtract.h"
#include "sv6ObjExtractDlg.h"

#include <FileIO2.h>
#include <FCNTL.H>
#include <io.h>
#include <SHARE.H>
#include <sys/STAT.H>
#include <direct.h>
#include "rct2/sv6/SV6_EXTRACTOBJS.h"

#define sz(a) (sizeof(a))

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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


/////////////////////////////////////////////////////////////////////////////
// CSv6ObjExtractDlg dialog

CSv6ObjExtractDlg::CSv6ObjExtractDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSv6ObjExtractDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSv6ObjExtractDlg)
	m_extractDir = _T("");
	m_sv6Name = _T("");
	m_progressMessage = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSv6ObjExtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSv6ObjExtractDlg)
	DDX_Text(pDX, IDC_EDIT_EXTRACTDIR, m_extractDir);
	DDV_MaxChars(pDX, m_extractDir, 256);
	DDX_Text(pDX, IDC_EDIT_SV6NAME, m_sv6Name);
	DDV_MaxChars(pDX, m_sv6Name, 256);
	DDX_Text(pDX, IDC_MESSAGE, m_progressMessage);
	DDV_MaxChars(pDX, m_progressMessage, 256);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSv6ObjExtractDlg, CDialog)
	//{{AFX_MSG_MAP(CSv6ObjExtractDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SV6NAME, OnButtonSv6name)
	ON_BN_CLICKED(IDC_BUTTON_EXTRACTDIR, OnButtonExtractdir)
	ON_BN_CLICKED(IDC_BUTTON_EXTRACTOBJECTS, OnButtonExtractobjects)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSv6ObjExtractDlg message handlers

BOOL CSv6ObjExtractDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
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
			sv6FileName,
			extractDir
		);

		_close(settings_fHndl);

	}
	else 
	{
		strcpy(sv6FileName,"\0");
		strcpy(extractDir,"\0");
	}

	m_sv6Name=sv6FileName;
	m_extractDir=extractDir;

	UpdateData(DDX_SET);

	return TRUE;  // return TRUE  unless you set the focus to a control
}




void CSv6ObjExtractDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	UpdateData(DDX_GET);

	strcpy(sv6FileName,m_sv6Name.GetBuffer(0));
	strcpy(extractDir,m_extractDir.GetBuffer(0));

	settings_fHndl=_sopen(settings_filename,_O_BINARY|_O_CREAT|_O_RDWR|_O_TRUNC,_SH_DENYNO,_S_IREAD|_S_IWRITE);

	sprintf
	(	ioBuffer,
		"%s\r\n"
		"%s\r\n",
		sv6FileName,
		extractDir
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

	CDialog::OnClose();	
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSv6ObjExtractDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSv6ObjExtractDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSv6ObjExtractDlg::OnButtonSv6name() 
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
		m_sv6Name=filename;
		UpdateData(DDX_SET);
	}

	
}

#define MAX_PATH_2 (MAX_PATH*2)

void CSv6ObjExtractDlg::OnButtonExtractdir() 
{
	// TODO: Add your control notification handler code here

	char 
		retPath[MAX_PATH_2],
		retName[MAX_PATH_2];

	typedef ITEMIDLIST 
		ITEMIDLIST_ARRAY[20];

	//ITEMIDLIST 
	//	itemIDlist;
	union 
	{
		ITEMIDLIST_ARRAY *retItemIDlistArray;
		ITEMIDLIST *retItemIDlist;
	};

	BROWSEINFO 
		browseInfo=
		{
			NULL,
			NULL,
			retName,
			"Choose Directory",
			BIF_EDITBOX,
			NULL,
			0,
			0
		};

	browseInfo.pidlRoot=
		NULL;

	retItemIDlist=SHBrowseForFolder(&browseInfo);

	SHGetPathFromIDList
	(
		retItemIDlist,
		retPath
	);


	UpdateData(DDX_GET);
	m_extractDir=retPath;
	UpdateData(DDX_SET);

}

#define CZMAX 512

typedef class
{
public:
	char cz[CZMAX];
	operator=(CString cStr)
	{
		strncpy(cz,cStr.GetBuffer(0),CZMAX-1);
	}
	operator=(char *s)
	{
		strncpy(cz,s,CZMAX-1);
	}
} 
czString;

char* operator<<(char*s,CString cs)
{
	strcpy(s,cs.GetBuffer(0));
	return s;
}

void CSv6ObjExtractDlg::OnButtonExtractobjects() 
{
	// TODO: Add your control notification handler code here

	CSv6ObjExtractDlg_type *dlg=
		(CSv6ObjExtractDlg_type*)this;


	memset(this->sv6FileName,0,sz(this->sv6FileName));

	sv6FileName<<m_sv6Name;
	extractDir<<m_extractDir;

	ExtractSv6Objects
	(	
		sv6FileName,
		extractDir,
		dlg
	);

}

#undef sz//(a) (sizeof(a))

void CSv6ObjExtractDlg::OnOK() 
{
	// TODO: Add extra validation here

	this->OnClose();
	
	CDialog::OnOK();
}

void CSv6ObjExtractDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	this->OnClose();
	
	CDialog::OnCancel();
}

CSv6ObjExtractDlg::ProgressMessage(char*message)
{
	UpdateData(DDX_GET);
	this->m_progressMessage=message;
	UpdateData(DDX_SET);	
}





