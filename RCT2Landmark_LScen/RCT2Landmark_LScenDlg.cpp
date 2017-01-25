// RCT2Landmark_LScenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RCT2Landmark_LScen.h"
#include "RCT2Landmark_LScenDlg.h"
#include "DlgProxy.h"
#include<rct2Lib.h>
#include<direct.h>
#include"parse/Parse_Output.h"
#include"parse/Parse_Input.h"
#include"bitmap/bitmap_extract.h"
//#define SUPER_STRING__C_STRING
#define STDAFX_INCLUDED
#define SUPER_STRING__C_STRING
#include<superString.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




OBJDAT_FILE
	dat;

/////////////////////////////////////////////////////////////////////////////
// CRCT2Landmark_LScenDlg dialog

IMPLEMENT_DYNAMIC(CRCT2Landmark_LScenDlg, CDialog);

CRCT2Landmark_LScenDlg::CRCT2Landmark_LScenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRCT2Landmark_LScenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRCT2Landmark_LScenDlg)
	lscenDatName = _T("");
	rct2lmmProjectName = _T("");
	startImgI = 0;
	useImgI = FALSE;
	useColRowRot = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;


}

CRCT2Landmark_LScenDlg::~CRCT2Landmark_LScenDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

BOOL CRCT2Landmark_LScenDlg::UpdateData(BOOL bSaveAndValidate)
{
	BOOL retv;
	if(bSaveAndValidate==DDX_SET)
	{
		lscenDatName
		=~appData.lscenDatFName;
		rct2lmmProjectName
		=~appData.projectFName;
		startImgI
		=appData.startImgI;
		useImgI
		=appData.useImgI;
		useColRowRot
		=
		appData.useColRowRot
		;
	}

	retv=CDialog::UpdateData(bSaveAndValidate);

	if(bSaveAndValidate==DDX_GET)
	{
		appData.lscenDatFName
		=lscenDatName.GetBuffer(0);	
		appData.projectFName			
		=rct2lmmProjectName.GetBuffer(0);
		appData.startImgI
		=startImgI;
		appData.useImgI
		=useImgI;
		appData.useColRowRot
		=
		useColRowRot
		;
	}

	return retv;
}

void CRCT2Landmark_LScenDlg::DoDataExchange(CDataExchange* pDX)
{


	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRCT2Landmark_LScenDlg)
	DDX_Control(pDX, IDC_EDIT_OUTPUT, outputBox);
	DDX_Control(pDX, IDC_RCT2LMM_PROGRESS, progressBar);
	DDX_Text(pDX, IDC__EDIT__LSCEN_DAT_NAME, lscenDatName);
	DDV_MaxChars(pDX, lscenDatName, 255);
	DDX_Text(pDX, IDC__EDIT__RCT2LMM_PROJECT_NAME, rct2lmmProjectName);
	DDV_MaxChars(pDX, rct2lmmProjectName, 255);
	DDX_Text(pDX, IDC_START_IMG_I, startImgI);
	DDV_MinMaxUInt(pDX, startImgI, 0, 9999);
	DDX_Check(pDX, IDC__CHECK__USE_IMG_NUM, useImgI);
	DDX_Check(pDX, IDC__CHECK__USE_COL_ROW_ROT, useColRowRot);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRCT2Landmark_LScenDlg, CDialog)
	//{{AFX_MSG_MAP(CRCT2Landmark_LScenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SV6NAME, OnButtonSv6name)
	ON_BN_CLICKED(IDC__BUTTON__EXTRACT_TO_PROJECT, OnButtonExtractToProject)
	ON_BN_CLICKED(IDC__BUTTON__LSCEN_DAT_NAME, OnButtonLscenDatName)
	ON_BN_CLICKED(IDC__BUTTON__RCT2LMM_PROJECT_NAME, OnButtonRct2lmmProjectName)
	ON_BN_CLICKED(IDC__BUTTON__TEST_SAVE_DAT, OnButtonTestSaveDat)
	ON_BN_CLICKED(IDC__BUTTON__EXTRACT_FULL_VIEWS, OnButtonExtractFullViews)
	ON_BN_CLICKED(IDC__BUTTON__EXTRACT_TILE_IMAGES, OnButtonExtractTileImages)
	ON_BN_CLICKED(IDC__BUTTON__BUILD_DAT, OnButtonBuildDat)
	ON_BN_CLICKED(IDC__CHECK__USE_COL_ROW_ROT, OnCheckUseColRowRot)
	ON_BN_CLICKED(IDC__CHECK__USE_IMG_NUM, OnCheckUseImgNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRCT2Landmark_LScenDlg message handlers

BOOL CRCT2Landmark_LScenDlg::OnInitDialog()
{
	int bytesRead;
	
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//rct2Lib_handle=LoadLibrary(RCT2LIB_DLL__PATH);
	_getcwd(~settingsFile,sz(settingsFile));
	settingsFile>>RCT2LMM_SETTINGS_FILE;
	
	bytesRead=QuickRead(&appData,~settingsFile,0,sz(appData));
	if(bytesRead==0)
		memset(&appData,0,sz(&appData));

	UpdateData(DDX_SET);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRCT2Landmark_LScenDlg::OnPaint() 
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
HCURSOR CRCT2Landmark_LScenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CRCT2Landmark_LScenDlg::OnClose() 
{
	UpdateData(DDX_GET);
	QuickWrite(&appData,~settingsFile,0,sz(appData),false);

	if (CanExit())
		CDialog::OnClose();
}

void CRCT2Landmark_LScenDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CRCT2Landmark_LScenDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CRCT2Landmark_LScenDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CRCT2Landmark_LScenDlg::OnButtonSv6name() 
{
	// TODO: Add your control notification handler code here
	
}

void CRCT2Landmark_LScenDlg::OnButtonExtractToProject() 
{
	// TODO: Add your control notification handler code here
	UpdateData(DDX_GET);

	CString curMsg;
	FILENAME path,tmpFile;
	
	UpdateData(DDX_GET);
	curMsg.Format("Loading %s\r\n",~this->appData.lscenDatFName);
	AddOutputLine(~curMsg);

	dat.LoadObjDatFile(~appData.lscenDatFName);

	#define skipNonLScen 0
	#if(skipNonLScen)
	if(dat.objType==OT_LARGESCENERY)
	{
	#endif
		curMsg.Format("Saving %s\r\n",~appData.projectFName);

		AddOutputLine(~curMsg);
	
		ExtractProjectFile();

	#if skipNonLScen
	}
	else
	{
		curMsg.Format("\"%s\" is not a large scenery file\r\n",~appData.projectFName);

		AddOutputLine(~curMsg);
	}
	#endif
	
	AddOutputLine("Done\r\n");

	ProgressInit();
	
}

void CRCT2Landmark_LScenDlg::OnButtonExtractTileImages() 
{
	// TODO: Add your control notification handler code here
	FILENAME path;

	CString curMsg;
	
	UpdateData(DDX_GET);

	curMsg.Format("Loading %s\r\n",~this->appData.lscenDatFName);

	AddOutputLine(~curMsg);

	dat.LoadObjDatFile(~appData.lscenDatFName);

	path=this->appData.projectFName;
	--path;

	curMsg.Format("Extracting tile views\r\n");

	AddOutputLine(~curMsg);

	Bitmap_Extract_TileViews
	(	path,dat,*this,appData.startImgI,
		appData.useImgI,
		appData.useColRowRot
	);	

	AddOutputLine("Done\r\n");
	
}

void CRCT2Landmark_LScenDlg::OnButtonExtractFullViews() 
{
	// TODO: Add your control notification handler code here
	OnButtonExtractBitmaps();	
}

void CRCT2Landmark_LScenDlg::OnButtonExtractBitmaps() 
{
	// TODO: Add your control notification handler code here

	FILENAME path;

	CString curMsg;
	
	UpdateData(DDX_GET);

	curMsg.Format("Loading %s\r\n",~this->appData.lscenDatFName);


	AddOutputLine(~curMsg);

	dat.LoadObjDatFile(~appData.lscenDatFName);

	//curMsg.Format("Loading %s\r\n",~this->appData.lscenDatFName);

	path=this->appData.projectFName;
	--path;

	if(dat.objType==OT_LARGESCENERY)
	{
		curMsg.Format("Extracting bitmaps\r\n");

		AddOutputLine(~curMsg);

		Bitmap_Extract(path,dat,*this);	
	}
	else
	{
		curMsg.Format("\"%s\" is not a large scenery file\r\n",~appData.projectFName);

		AddOutputLine(~curMsg);
	}


	AddOutputLine("Done\r\n");
}

void CRCT2Landmark_LScenDlg::OnButtonLscenDatName() 
{
	// TODO: Add your control notification handler code here

	UpdateData(DDX_GET);

	BrowseRct2File
	(	FAT_LOAD,
		~this->appData.lscenDatFName, 
		FT_RCT2_OBJDAT
	);

	UpdateData(DDX_SET);	
}

void CRCT2Landmark_LScenDlg::OnButtonRct2lmmProjectName() 
{
	// TODO: Add your control notification handler code here
	UpdateData(DDX_GET);

	GetSaveFileName_Quick
	(	
		sz(this->appData.projectFName),
		~this->appData.projectFName,
		OFN_PATHMUSTEXIST|OFN_CREATEPROMPT|OFN_EXPLORER,
		"RCT2 Landmark Maker Projects (RLP)\0*.rlp\0\0",
		"RLP",
		"Select Project File"
	);

	UpdateData(DDX_SET);	
	
}

void CRCT2Landmark_LScenDlg::OnButtonTestSaveDat() 
{
	// TODO: Add your control notification handler code here



	CString curMsg;
	FILENAME path,tmpFile;
	
	UpdateData(DDX_GET);
	curMsg.Format("Loading %s\r\n",~this->appData.lscenDatFName);

	this->AddOutputLine(~curMsg);


	dat.LoadObjDatFile(~appData.lscenDatFName);
	
	path=appData.lscenDatFName;path--;
	tmpFile=path;tmpFile>>"testObj0.dat";

	curMsg.Format("Saving %s\r\n",~tmpFile);

	this->AddOutputLine(~curMsg);

	dat.SaveObjDatFile(~tmpFile,false);

	this->AddOutputLine("Done\r\n");

}

CRCT2Landmark_LScenDlg::ExtractProjectFile()
{
	FILE*fProject;

	if
	(
		(fProject=fopen(~this->appData.projectFName,"wb"))
		!=NULL
	)
	{
		fseek(fProject,0,SEEK_SET);

		Parse_Output
		(	fProject,dat,
			appData.startImgI,
			appData.useImgI,
			appData.useColRowRot,
			*this
		);

		fclose(fProject);
	}
}

BOOL CRCT2Landmark_LScenDlg::DataSet()
{
	return UpdateData(DDX_SET);
}

BOOL CRCT2Landmark_LScenDlg::DataGet()
{
	return UpdateData(DDX_GET);
}

CRCT2Landmark_LScenDlg::AddOutputLine(char*line)
{
	CPoint pt; 
	int startP,endP;
	char*&l=line;

	
	outputBox.GetWindowText(outputStr);
	startP=endP=outputStr.GetLength()-1;
	outputBox.SetSel(startP,endP,false);
	
	outputStr+=l;	
	outputBox.SetWindowText(outputStr);
	
	startP=endP=outputStr.GetLength()-1;
	outputBox.SetSel(startP,endP,false);

	#if 0
	//outputBox.LineScroll(outputBox.GetLineCount(),0);
	#endif


}



void CRCT2Landmark_LScenDlg::OnButtonBuildDat() 
{
	// TODO: Add your control notification handler code here

	FILE*fProject;


	UpdateData(DDX_GET);

	CString curMsg;
	FILENAME path,tmpFile;
	
	UpdateData(DDX_GET);
	curMsg.Format("Compiling %s\r\n",~this->appData.projectFName);

	this->AddOutputLine(~curMsg);

	#if 0
		dat.LoadObjDatFile(~appData.lscenDatFName);	
	#else
		dat.Init_SetType(OT_LARGESCENERY);
	#endif

	if
	(
		(fProject=fopen(~this->appData.projectFName,"r+b"))
		!=NULL
	)
	{
		fseek(fProject,0,SEEK_SET);

		Parse_Input
		(	fProject,dat,
			appData.lscenDatFName,
			appData.projectFName,
			*this
		);

		fclose(fProject);
	}

	UpdateData(DDX_SET);

	UpdateData(DDX_GET);
	curMsg.Format("Saving %s\r\n",~appData.lscenDatFName);

	this->AddOutputLine(~curMsg);


	#if 1
	dat.SaveObjDatFile(~appData.lscenDatFName,false);	
	#endif

	UpdateData(DDX_GET);
	curMsg="Done\r\n";

	this->AddOutputLine(~curMsg);

	this->ProgressInit(0,1,0,1);

}

void CRCT2Landmark_LScenDlg::OnCheckUseColRowRot() 
{
	// TODO: Add your control notification handler code here
	UpdateData(DDX_GET);
	appData.useImgI=false;	
	UpdateData(DDX_SET);
}

void CRCT2Landmark_LScenDlg::OnCheckUseImgNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(DDX_GET);
	appData.useColRowRot=false;	
	UpdateData(DDX_SET);
	
}

CRCT2Landmark_LScenDlg::ProgressInit(int lo,int hi,int pos,int step)
{
	CProgressCtrl&pb=progressBar;
	DataGet();
	pb.SetRange(lo,hi);
	pb.SetPos(pos);
	pb.SetStep(step);
	DataSet();
}

CRCT2Landmark_LScenDlg::Progress()
{
	CProgressCtrl&pb=progressBar;
	DataGet();
	pb.StepIt();
	DataSet();
}

CRCT2Landmark_LScenDlg::ProgressInit()
{
	ProgressInit(0,1,0,1);
}
