// ParkDatDlg.cpp : implementation file
//

#define dllPort __declspec(dllimport)
#include "stdafx.h"
#include "ParkDat.h"
#include "ParkDatDlg.h"
#include "DlgProxy.h"
#include<rct2lib.h>
#include<codeshortcuts.h>
//#include<CStringOps.h>
#include<superString.h>
#include<direct.h>
#include<prompt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MANUAL_IMG_UPDATE 0

typedef struct OBJ_INDEX_MAP
{
	union
	{
	struct
	{
	short 
		rides[SV6_OBJDAT_NUMENTRIES_RIDES],
		smallScenery[SV6_OBJDAT_NUMENTRIES_SMALLSCENERY],
		largeScenery[SV6_OBJDAT_NUMENTRIES_LARGESCENERY],
		walls[SV6_OBJDAT_NUMENTRIES_WALLS],
		banners[SV6_OBJDAT_NUMENTRIES_BANNERS],
		paths[SV6_OBJDAT_NUMENTRIES_PATHS],
		pathUtilities[SV6_OBJDAT_NUMENTRIES_PATHUTILITIES],
		groups[SV6_OBJDAT_NUMENTRIES_GROUPS],
		entrance[SV6_OBJDAT_NUMENTRIES_ENTRANCE],
		palette[SV6_OBJDAT_NUMENTRIES_PALETTE],
		scenarioText[SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT];
	};
	short 
		items[SV6_OBJDAT_NUMENTRIES_ALL];
	};

	OBJ_INDEX_MAP();

}OBJ_INDEX_MAP;

OBJ_INDEX_MAP::OBJ_INDEX_MAP()
{
	int i;for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL){items[i]=i;}
}


typedef struct OBJ_USED_FLAGS
{
	union
	{
	struct
	{
	bool 
		rides[SV6_OBJDAT_NUMENTRIES_RIDES],
		smallScenery[SV6_OBJDAT_NUMENTRIES_SMALLSCENERY],
		largeScenery[SV6_OBJDAT_NUMENTRIES_LARGESCENERY],
		walls[SV6_OBJDAT_NUMENTRIES_WALLS],
		banners[SV6_OBJDAT_NUMENTRIES_BANNERS],
		paths[SV6_OBJDAT_NUMENTRIES_PATHS],
		pathUtilities[SV6_OBJDAT_NUMENTRIES_PATHUTILITIES],
		groups[SV6_OBJDAT_NUMENTRIES_GROUPS],
		entrance[SV6_OBJDAT_NUMENTRIES_ENTRANCE],
		palette[SV6_OBJDAT_NUMENTRIES_PALETTE],
		scenarioText[SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT];
	};
	bool 
		items[SV6_OBJDAT_NUMENTRIES_ALL];
	};

	OBJ_USED_FLAGS();
	Init();

}OBJ_USED_FLAGS;

OBJ_USED_FLAGS::OBJ_USED_FLAGS()
{
	Init();
}
OBJ_USED_FLAGS::Init()
{
	int i;
	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL){items[i]=0;}
}


OBJ_INDEX_MAP
	objIdxMap;

char*operator~(CString&s)
{
	return(s.GetBuffer(0));
}

FILENAME rct2ObjDir;

enum
{
	OPC__SV6_OPENED,
	OPC__SV6_SAVED,
	OPC__SV6_OPENING,
	OPC__SV6_SAVING,
	OPC__ODAT_OPENED,
	OPC__ODAT_SAVED,
	OPC__ODAT_REPLACED,
	OPC__ODAT_DELETED,
	OPC__ODAT_ADDED,
	OPC__ODAT_HEADERS_UPDATED,
};


SV6_FILE sv6;

OBJDAT_FILE curDat,&cdat=curDat;

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
// CParkDatDlg dialog

IMPLEMENT_DYNAMIC(CParkDatDlg, CDialog);

CParkDatDlg::CParkDatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParkDatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParkDatDlg)
	sv6Name = _T("");
	searchText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32


	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	sv6Loaded=false;
	memset(&appData,0,sz(appData));
}

CParkDatDlg::~CParkDatDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.


	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CParkDatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParkDatDlg)
	DDX_Control(pDX, IDC__TEXT__SEARCH_RESULT, searchRslt);
	DDX_Control(pDX, IDC__IMG_FRAME, imgPreview);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, outputBox);
	DDX_Control(pDX, IDC__LIST__DATS, datList);
	DDX_Control(pDX, IDC_PROGRESS, progress);
	DDX_Text(pDX, IDC__EDIT__SV6_NAME, sv6Name);
	DDV_MaxChars(pDX, sv6Name, 255);
	DDX_Text(pDX, IDC__EDIT__SEARCH, searchText);
	DDV_MaxChars(pDX, searchText, 128);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParkDatDlg, CDialog)
	//{{AFX_MSG_MAP(CParkDatDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC__BUTTON__SV6_NAME, OnButtonSv6Name)
	ON_BN_CLICKED(IDC__BUTTON__OPEN_SV6, OnButtonOpenSv6)
	ON_BN_CLICKED(IDC__BUTTON__ADD_DAT, OnButtonAddDat)
	ON_BN_CLICKED(IDC__BUTTON__DELETE_SELECTED_DAT, OnButtonDeleteSelectedDat)
	ON_BN_CLICKED(IDC__BUTTON__REPLACE_SELECTED_DAT, OnButtonReplaceSelectedDat)
	ON_BN_CLICKED(IDC__BUTTON__UPDATE_DAT_HEADERS, OnButtonUpdateDatHeaders)
	ON_BN_CLICKED(IDC__BUTTON__SAVE_SV6, OnButtonSaveSv6)
	ON_BN_CLICKED(IDC__BUTTON__UPDATE_IMG_PREVIEW, OnButtonUpdateImgPreview)
	ON_NOTIFY(LVN_KEYDOWN, IDC__LIST__DATS, OnKeydownListDats)
	ON_NOTIFY(HDN_ITEMCLICK, IDC__LIST__DATS, OnItemclickListDats)
	ON_NOTIFY(HDN_ITEMDBLCLICK, IDC__LIST__DATS, OnItemdblclickListDats)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC__LIST__DATS, OnItemchangedListDats)
	ON_BN_CLICKED(IDC__BUTTON__DELETE_UNUSED, OnButtonDeleteUnused)
	ON_BN_CLICKED(IDC__BUTTON__SEARCH, OnButtonSearch)
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParkDatDlg message handlers

BOOL CParkDatDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	InitDatListCtrl(); 

	LoadSettings();

	if(GetRct2Path(~rct2ObjDir))
		rct2ObjDir>>"ObjData";
	else
	{
		MessageBox
		(
			"RCT2 Installation not found\r\n"
			,"Warning"
			,MB_OK
		);

		rct2ObjDir="";
	}

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CParkDatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CParkDatDlg::OnPaint() 
{
	#if 0//(!MANUAL_IMG_UPDATE)
		UpdateImgPreview();
	#endif 

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
HCURSOR CParkDatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CParkDatDlg::OnClose() 
{
	if (CanExit())
	{
		SaveSettings();
		CDialog::OnCancel();
	}
}

void CParkDatDlg::OnOK() 
{
	if (CanExit())
	{
		SaveSettings();
		CDialog::OnCancel();
	}
}

void CParkDatDlg::OnCancel() 
{
	if (CanExit())
	{
		SaveSettings();
		CDialog::OnCancel();
	}
}

BOOL CParkDatDlg::CanExit()
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


LVColumn_GetSetup(LVCOLUMN&lvc,char*bufr,int bufrSz)
{
	lvc.mask=
		LVCF_FMT|LVCF_IMAGE|LVCF_ORDER
		|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	lvc.cchTextMax=bufrSz;
	lvc.pszText=bufr;
}

typedef struct DAT_TABLE_INDEXES
{
	struct
	{
		WORD lo,hi,numEntries;
		char text[4];
	}
	tableIndexes[DAT_TABLE_ENTRY__NUM_ENTRIES];
	DAT_TABLE_INDEXES();
}
DAT_TABLE_INDEXES;


DAT_TABLE_INDEXES::DAT_TABLE_INDEXES()
{
	int i,j;
	static
	struct
	{
		WORD numEntries;
		char text[4];
	}
		ti[DAT_TABLE_ENTRY__NUM_ENTRIES]=
		{
			{SV6_OBJDAT_NUMENTRIES_RIDES,SV6_OBJDAT_ABBV_RIDES},
			{SV6_OBJDAT_NUMENTRIES_SMALLSCENERY,SV6_OBJDAT_ABBV_SMALLSCENERY },
			{SV6_OBJDAT_NUMENTRIES_LARGESCENERY,SV6_OBJDAT_ABBV_LARGESCENERY },
			{SV6_OBJDAT_NUMENTRIES_WALLS,SV6_OBJDAT_ABBV_WALLS },
			{SV6_OBJDAT_NUMENTRIES_BANNERS,SV6_OBJDAT_ABBV_BANNERS },
			{SV6_OBJDAT_NUMENTRIES_PATHS,SV6_OBJDAT_ABBV_PATHS},
			{SV6_OBJDAT_NUMENTRIES_PATHUTILITIES,SV6_OBJDAT_ABBV_PATHUTILITIES},
			{SV6_OBJDAT_NUMENTRIES_GROUPS,SV6_OBJDAT_ABBV_GROUPS  },
			{SV6_OBJDAT_NUMENTRIES_ENTRANCE,SV6_OBJDAT_ABBV_ENTRANCE },
			{SV6_OBJDAT_NUMENTRIES_PALETTE,SV6_OBJDAT_ABBV_PALETTE},
			{SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT,SV6_OBJDAT_ABBV_SCENARIOTEXT}
		};

	j=0;
	for_i0(i,DAT_TABLE_ENTRY__NUM_ENTRIES)
	{
		strcpy(tableIndexes[i].text,ti[i].text);
		tableIndexes[i].numEntries=ti[i].numEntries;
		tableIndexes[i].lo=j;
		tableIndexes[i].hi=j+ti[i].numEntries-1;
		j+=ti[i].numEntries;		
	}
}

GetDatSlotTypStr(SUPER_STRING&text,int i)
{
	int j;
	bool inRange;
	static
		DAT_TABLE_INDEXES
			table;

	for_i0(j,DAT_TABLE_ENTRY__NUM_ENTRIES)
	{	
		
		inRange=
			(i>=table.tableIndexes[j].lo)
			&&
			(i<=table.tableIndexes[j].hi)
			;
		if(inRange)
		{
			text=table.tableIndexes[j].text;
			break;
		}
	}

}

SetLVItem
(	
	LVITEM lvi,
    UINT   mask, 
    int    iItem,
    int    iSubItem,
    UINT   state,
    UINT   stateMask,
    LPTSTR  pszText,
    int    cchTextMax,
    int    iImage,
    LPARAM lParam	
)
{
	#define s(a) (lvi.a=a)
	
    s(mask); 
    s(iItem);
    s(iSubItem);
    s(state);
    s(stateMask);
    s(pszText);
    s(cchTextMax);
    s(iImage);
    s(lParam);
	lvi.iIndent=0;

	#undef s
}

OBJ_USED_FLAGS usedObjs;
void GetUsedObjects(OBJ_USED_FLAGS&usedObjs); 

CParkDatDlg::InitDatListCtrl()
{
	LVCOLUMN lCol;
	char label[64];
	DWORD e;
	LPARAM lp;

	int selMark;


	int i,j,k;
	SUPER_STRING s;
	i=0;

	DWORD exStyle;

	exStyle=datList.GetExtendedStyle();
	exStyle|=LVS_EX_FULLROWSELECT;
	datList.SetExtendedStyle(exStyle);

	datList.SetGridLines(true);

	i=datList.InsertColumn(i,"Slot #",LVCFMT_LEFT,8*6,i);
	LVColumn_GetSetup(lCol,label,sz(label));
	datList.GetColumn(i,&lCol);
	++i;
	i=datList.InsertColumn(i,"Slot Type",LVCFMT_LEFT,8*8,i);
	datList.GetColumn(i,&lCol);
	++i;
	i=datList.InsertColumn(i,"In Park?",LVCFMT_LEFT,8*8,i);
	datList.GetColumn(i,&lCol);
	++i;
	i=datList.InsertColumn(i,"DAT Name",LVCFMT_LEFT,8*9,i);
	datList.GetColumn(i,&lCol);
	++i;
	i=datList.InsertColumn(i,"Menu Name",LVCFMT_LEFT,8*29,i);
	datList.GetColumn(i,&lCol);

	++i;

	LVITEM lvi;



	j=0;
	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		s.Number(3,3,i);
		#if 1
		datList.InsertItem
		(	LVIF_TEXT|LVIF_PARAM,
			i,(char*)~s,0,0,0,i	
		);
		#endif
	}

	datList.GetColumn(1,&lCol);
	j=lCol.iSubItem;
	

	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		GetDatSlotTypStr(s,i);
		datList.SetItemText(i,j,(char*)~s);
	}

	++j;
	s=" ";
	
	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		datList.SetItemText(i,j,(char*)~s);	
	}


	++j;
	s="DATNAME ";

	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		datList.SetItemText(i,j,(char*)~s);
	}

	++j;
	s="Menu Name";
	
	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		datList.SetItemText(i,j,(char*)~s);
	}

	selMark=
		datList.GetSelectionMark();

}

CParkDatDlg::
LoadSettings()
{
	FILE*f;
	getcwd(~settingsFile,sz(settingsFile)-1);
	settingsFile>>SETTINGS_FILENAME;

	if(f=fopen(~settingsFile,"r+b"))
	{
		fread(&appData,sz(appData),1,f);
		fclose(f);
	}

	

	DataSet();
}

CParkDatDlg::
SaveSettings()
{
	FILE*f;

	DataGet();

	if(f=fopen(~settingsFile,"w+b"))
	{
		fwrite(&appData,sz(appData),1,f);
		fclose(f);
	}
}

CParkDatDlg::
DataGet()
{
	UpdateData(DDX_GET);
	#define a appData
	{	
		a.sv6Name=sv6Name.GetBuffer(0);
	}
	#undef a
}

CParkDatDlg::DataSet()
{
	#define a appData
	{
		sv6Name=~a.sv6Name;
	}
	#undef a
	UpdateData(DDX_SET);
}


void CParkDatDlg::OnButtonSv6Name() 
{
	// TODO: Add your control notification handler code here
	DataGet();

	GetSaveFileName_Quick
	(	
		sz(appData.sv6Name),
		~appData.sv6Name,
		OFN_EXPLORER|OFN_FILEMUSTEXIST,
		"RCT2 Park File (SV6)\0*.sv6",
		"sv6",
		"Select SV6 Park File"
	);

	DataSet();
}

void CParkDatDlg::OnButtonOpenSv6() 
{
	// TODO: Add your control notification handler code here

	DataGet();

	this->OutputMsg(OPC__SV6_OPENING,~appData.sv6Name);

	sv6Loaded=true;
	OpenSv6(&sv6,~appData.sv6Name);
	
	SetMenusToAvailable();
	
	GetUsedObjects(usedObjs);
	
	UpdateDatTable();

	this->OutputMsg(OPC__SV6_OPENED);

	UpdateImgPreview();	
}

MakeDatPath(FILENAME&dp,SV6_OBJDAT_HEADER&odh)
{
	int i;
	char datName[9];

	GetRct2Path(~dp);

	sscanf(odh.filename,"%8c",datName);
	datName[8]=0;
	i=7;
	while((i>0)&&(datName[i]==' '))
	{
		datName[i--]=0;
	}

	dp>>"ObjData";
	dp>>datName;
	dp&=".dat";
}

CParkDatDlg::UpdateDatTable()
{

	int i;

	if(sv6Loaded)
	{
		ProgressStart(0,SV6_OBJDAT_NUMENTRIES_ALL,0,1);

		for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
		{
			UpdateViewTableItem(i);

			ProgressStep();			
		}
		ProgressEnd();

	}
}

CParkDatDlg::ProgressStart(int lo,int hi,int pos,int step)
{
	progress.SetRange(lo,hi);
	progress.SetPos(pos);
	progress.SetStep(step);
}

CParkDatDlg::ProgressEnd()
{
	progress.SetRange(0,1);
	progress.SetPos(0);
	progress.SetStep(1);
}

CParkDatDlg::ProgressStep()
{
	progress.StepIt();
}

int FindFreeSlot(short objType);

void CParkDatDlg::OnButtonAddDat() 
{
	// TODO: Add your control notification handler code here
	int i;

	FILENAME addDatName;

	addDatName=rct2ObjDir;
	addDatName>>"*.dat";


	DataGet();

	if
	(
		GetSaveFileName_Quick
		(	
			sz(addDatName),
			~addDatName,
			OFN_EXPLORER|OFN_FILEMUSTEXIST,
			"RCT2 Object Data File (DAT)\0*.dat",
			"dat",
			"Select RCT2 DAT File"
		)
	)
	{
		cdat.LoadObjDatFile(~addDatName);

		i=FindFreeSlot(cdat.objType);

		if(i<RCT2_BASES[OT__NUM_TYPES])
		{
			ReplaceItem(i,~addDatName);
		}
	}

	DataSet();

	UpdateImgPreview();
	
}

int FindFreeSlot(short objType)
{
	int i,j,retI,d;
	SV6_OBJDAT_HEADER_BLOCK
		&dt=sv6.fileDataA.availableItems,
		&datTable=dt
		;

	objType=__min(objType,OT__NUM_TYPES);
	i=RCT2_BASES[objType];
	if(objType<OT__NUM_TYPES)
	{
		while(i<RCT2_BASES[objType+1])
		{
			if(long(dt.items[i].flags)==long(-1))
			{
				retI=i;
				break;
			}
			++i;
		}
		if(i>=RCT2_BASES[objType+1])
			retI=RCT2_BASES[OT__NUM_TYPES];
	}
	else 
		retI=i;

	return retI;

}



CParkDatDlg::ReplaceItem(int i,OBJDATHEADER&o)
{
	char s[9];
	CString oldObj,newObj;
	SV6_OBJDAT_HEADER_BLOCK
		&dt=sv6.fileDataA.availableItems,
		&datTable=dt
		;
	sscanf(dt.items[i].filename,"%8s",s);
	if(s[0]==char(0xFF))
		oldObj="(Empty Slot)";
	else 
		oldObj=s;
	memcpy(&dt.items[i],&o,sz(dt.items[i]));
	UpdateViewTableItem(i);
	sscanf(dt.items[i].filename,"%8s",s);
	newObj=s;


	OutputMsg(OPC__ODAT_REPLACED,i,~oldObj,~newObj);


}

CParkDatDlg::ReplaceItem(int i,char*ofn)
{
	OBJDATHEADER oh;
	FILE*f;

	if(f=fopen(ofn,"r+b"))
	{
		fread(&oh,sz(oh),1,f);
		fclose(f);
		ReplaceItem(i,oh);
	}
	
}

int CParkDatDlg::FindListIndex(int i)
{
	int li=0,nItems=datList.GetItemCount(),
		d;

	while(li<nItems)
	{
		d=datList.GetParam(li);
		if(d==i)
			return(li);
		++li;
	}

	return li;
}


CParkDatDlg::UpdateViewTableItem(int i)
{
	union
	{
		LPARAM lp;
		BYTE lpb[4];
	};
	int j,k,listI;
	bool isEmpty;
	char curDatName[9];
	char isEmpty_Str[2];
	char menuName[128];
	char*datMenuStr;
	BYTE lang;

	FILENAME datPath;

	char*listText[3]=
	{
		isEmpty_Str,
		curDatName,
		menuName
	};

	SV6_OBJDAT_HEADER_BLOCK
		&dats=sv6.fileDataA.availableItems;


	isEmpty=(dats.items[i].flags==DWORD(0xffffffff));

	if(isEmpty)
	{
		strcpy(isEmpty_Str," ");
		curDatName[0]=0;
		menuName[0]=0;
		this->imgPreview.imgs[i]->Clear(0);
	}
	else
	{
		if(usedObjs.items[i])
			strcpy(isEmpty_Str,"X");
		else
			strcpy(isEmpty_Str," ");
		sprintf(curDatName,"%8.8s",&dats.items[i].filename[0]);
		#if 1
			MakeDatPath(datPath,dats.items[i]);
			#if 1

				memset
				(	&cdat.stringTable[0].entries,
					0,
					sz(cdat.stringTable[0].entries)
				);

				if(FExist(~datPath))
				{
					cdat.LoadObjDatFile(~datPath);
				
					k=0;

					datMenuStr="";
					while(k<RCT2__OBJDAT__STRING_TABLE__ENTRY__NUM_LANGUAGES)
					{
						lang=cdat.stringTable[0].entries[k].lang;
						if(lang==LNG_USENGLISH)
						{
							datMenuStr=cdat.stringTable[0].entries[k].text;
							break;
						}
						++k;
					}

					cdat.CopyImage(0,*(this->imgPreview.imgs[i]),4);

					

				}
				else
				{
					datMenuStr="** ERROR ** FILE NOT FOUND";
				}

				strcpy(menuName,datMenuStr);


			#else
				strcpy(menuName,~datPath);
			#endif
		#else
			menuName[0]=0;
		#endif
	}

	#if 0
	//get menu name
	#endif

	listI=FindListIndex(i);

	if(listI<datList.GetItemCount())
	{

		for_i0(j,3)
		{
			switch(j)
			{
			case 0:
				lp=listText[j][0];
				break;
			case 1:
			case 2:
				lp=0;
				for_i0(k,3)
				{	lpb[3-k]=listText[j][k];	}
				break;
			}
			
			datList.SetItemText(listI,j+2,listText[j]);
			datList.SetItem(listI,j+2,LVIF_PARAM,NULL,0,0,0,i);
		}
	}
	else
		listI=datList.GetItemCount();

}

void CParkDatDlg::OnButtonDeleteSelectedDat() 
{
	// TODO: Add your control notification handler code here

	POSITION p;
	int i;

	p=datList.GetFirstSelectedItemPosition();
	if(p!=NULL)
	{
		i=datList.GetNextSelectedItem(p);
		i=datList.GetParam(i);

		DeleteItem(i);
	}

	UpdateImgPreview();	
}

CParkDatDlg::DeleteItem(int i)
{
	char objNm[9];

	SV6_OBJDAT_HEADER_BLOCK
		&dt=sv6.fileDataA.availableItems,
		&datTable=dt
		;

	sscanf(dt.items[i].filename,"%8s",objNm);
	memset(&dt.items[i],BYTE(0xFF),sz(dt.items[i]));
	UpdateViewTableItem(i);
	OutputMsg(OPC__ODAT_DELETED,i,objNm);
}


void CParkDatDlg::OnButtonReplaceSelectedDat() 
{
	// TODO: Add your control notification handler code here
	POSITION p;
	int i;

	FILENAME addDatName;

	addDatName=rct2ObjDir;
	addDatName>>"*.dat";


	p=datList.GetFirstSelectedItemPosition();

	DataGet();

	if(p!=NULL);
	{
		if
		(
			GetSaveFileName_Quick
			(	
				sz(addDatName),
				~addDatName,
				OFN_EXPLORER|OFN_FILEMUSTEXIST,
				"RCT2 Object Data File (DAT)\0*.dat",
				"dat",
				"Select RCT2 DAT File"
			)
			
		)
		{
			cdat.LoadObjDatFile(~addDatName);

			i=datList.GetNextSelectedItem(p);
			i=datList.GetParam(i);

			if(cdat.objType<OT__NUM_TYPES)
			{
				if
				(	(i>=RCT2_BASES[cdat.objType])
					&&(i<=RCT2_BASES[cdat.objType+1])
				)
				{
					if(i<RCT2_BASES[OT__NUM_TYPES])
					{
						ReplaceItem(i,~addDatName);
					}
				}
			}
		}
	}

	UpdateImgPreview();	
}

CParkDatDlg::SetMenusToAvailable()
{
	SV6_PARKDATA
		&pd=sv6.fileDataA.parkData;

	BYTE setData=0xff,&sd=setData;
	
	if(sv6Loaded)
	{
		#define setAll(a)\
			memset(&a,sd,sz(a))

		setAll(pd.ridesMenu);
		setAll(pd.vehicleMenu);
		setAll(pd.sceneryMenu);
		setAll(pd.bannerMenu);

		#undef clear

		sv6.SetAllTrackFeatures();
	}
}



void CParkDatDlg::OnButtonUpdateDatHeaders() 
{
	// TODO: Add your control notification handler code here

	int i;

	if(!sv6Loaded)
		return;

	ProgressStart(0,SV6_OBJDAT_NUMENTRIES_ALL,0,1);

	for_i0(i,SV6_OBJDAT_NUMENTRIES_ALL)
	{
		sv6.FixObj(i);
		UpdateViewTableItem(i);
		ProgressStep();
	}

	ProgressEnd();

	OutputMsg(OPC__ODAT_HEADERS_UPDATED);

	UpdateImgPreview();	

}

void CParkDatDlg::OnButtonSaveSv6() 
{
	// TODO: Add your control notification handler code here
	if(!sv6Loaded)
		return;

	DataGet();

	this->OutputMsg(OPC__SV6_SAVING,~appData.sv6Name);
	
	SaveSv6(&sv6,~appData.sv6Name);
	
	DataSet();

	this->OutputMsg(OPC__SV6_SAVED);

}

CParkDatDlg::SetDatListToDefStyle()
{
	DWORD style;
	style=datList.GetExtendedStyle();

	style|=LVS_EX_GRIDLINES;
	style|=LVS_EX_FULLROWSELECT;

	datList.SetExtendedStyle(style);
}


CParkDatDlg::OutputMsg
(	int code,
	int d,char*s1,char*s2
)
{
	OutputMsg(code,d,s1,d,s2);
}


CParkDatDlg::OutputMsg
(	int code,
	int d1,char*s1
)
{
	OutputMsg(code,d1,s1,d1,s1);
}

CParkDatDlg::OutputMsg(int code)
{
	OutputMsg(code,0,"",0,"");
}

CParkDatDlg::OutputMsg(int code,char*s)
{
	OutputMsg(code,0,s,0,s);
}


CParkDatDlg::OutputMsg(
	int code,int d1,char*s1,int d2,char*s2
)
{
	DWORD l;
	CString outputAdd,&oa=outputAdd;

	outputBox.GetWindowText(outputStr);
	l=outputBox.GetWindowTextLength();
	outputBox.SetSel(l-1,l-1,false);
	
	oa="";

	switch(code)
	{
	case OPC__SV6_OPENED:
		oa.Format
		(	IDS__FORMAT__SV6_OPENED,
			s1
		);
		break;
	case OPC__SV6_SAVED:
		oa.Format
		(	IDS__FORMAT__SV6_SAVED,
			s1
		);
		break;
	case OPC__SV6_OPENING:
		oa.Format
		(	IDS__FORMAT__SV6_OPENING,
			s1
		);
		break;
	case OPC__SV6_SAVING:
		oa.Format
		(	IDS__FORMAT__SV6_SAVING,
			s1
		);
		break;
	case OPC__ODAT_OPENED:	break;
	case OPC__ODAT_SAVED:	break;
	case OPC__ODAT_REPLACED:	
		oa.Format
		(	IDS__FORMAT__DAT_REPLACED,
			d1,			
			s1,
			s2		
		);		

		break;
	case OPC__ODAT_DELETED:
		oa.Format
		(	IDS__FORMAT__DAT_DELETED,
			d1,
			s1		
		);		

		break;
	case OPC__ODAT_ADDED:	break;
	case OPC__ODAT_HEADERS_UPDATED:	
		oa.Format
		(	IDS___FORMAT___DAT__HEADERS_UPDATED
		);		
		break;
	}

	outputStr+=oa;
	
	outputBox.SetWindowText(outputStr);
	l=outputBox.GetWindowTextLength();
	outputBox.SetSel(l-1,l-1,false);
}


void CParkDatDlg::OnButtonUpdateImgPreview() 
{
	// TODO: Add your control notification handler code here
	#if MANUAL_IMG_UPDATE
		UpdateImgPreview();
	#endif 
}

CParkDatDlg::UpdateImgPreview() 
{
	POSITION p;
	int i;

	p=datList.GetFirstSelectedItemPosition();

	if(p!=NULL)
	{
		i=datList.GetNextSelectedItem(p);
		i=datList.GetParam(i);		
	}
	else 
		i=-1;

	imgPreview.i=i;

	imgPreview.SendMessage(WM_PAINT,0,0);	
}

void CParkDatDlg::OnKeydownListDats(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	

	*pResult = 0;
}


void CParkDatDlg::OnItemclickListDats(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CParkDatDlg::OnItemdblclickListDats(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here

	
	*pResult = 0;
}

void CParkDatDlg::OnItemchangedListDats(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	#if(!MANUAL_IMG_UPDATE)
		UpdateImgPreview();
	#endif 
	
	*pResult = 0;
}

void GetUsedObjects(OBJ_USED_FLAGS&usedObjs) 
{
	int i;
	int et;
	RCT2_RIDESTRUCT*r=&sv6.fileDataA.parkData.rides[0],*cr;
	SV6_PARKMAPDATA*m=&sv6.fileDataA.parkMap[0],*cm;
	SV6_PARKMAPDATA_ALT*acm;

	usedObjs.Init();
	//
	for_i0(i,255)
	{	cr=&r[i];
		if(cr->trackType!=0xff)
			usedObjs.rides[cr->vehiObjID]=true;
	}
	for_i0(i,SV6_MAPDATASTRUCTURES_MAX)
	{	cm=&m[i];
		acm=(SV6_PARKMAPDATA_ALT*)cm;
		et=acm->byte0.elmtType;
		switch(et)
		{
		case MET_PATH		://1,
			{
				usedObjs.paths[acm->byte4.path.pathId]=true;
				if(acm->byte5.path.additions)
				usedObjs.pathUtilities[acm->byte5.path.additions-1]=true;
			break;
			}
		case MET_SCEN1TILE	://3,
			{
				usedObjs.smallScenery[cm->byte4.elmtID]=true;
			break;
			}
		case MET_FENCEWALL	://5,
			{
				usedObjs.walls[cm->byte4.elmtID]=true;
			break;
			}
		case MET_SCENMULTILE	://6,
			{
				usedObjs.largeScenery[cm->byte4.elmtID]=true;
			break;
			}
		}
	}//for_i0(i,SV6_MAPDATASTRUCTURES_MAX)

	for_i0(i,SV6_OBJDAT_NUMENTRIES_BANNERS)
	{
		usedObjs.banners[i]
		=((DWORD)sv6.fileDataA.availableItems.banners[i].flags
		!=(DWORD)0xFFFFFFFF);
	}
	for_i0(i,SV6_OBJDAT_NUMENTRIES_GROUPS)
	{
		usedObjs.groups[i]
		=((DWORD)sv6.fileDataA.availableItems.groups[i].flags
		!=(DWORD)0xFFFFFFFF);
	}

	usedObjs.entrance[0]=1;
	usedObjs.scenarioText[0]=1;
	usedObjs.palette[0]=1;

}
 
void CParkDatDlg::OnButtonDeleteUnused() 
{
	int i;
	//OBJ_USED_FLAGS usedObjs;
	// TODO: Add your control notification handler code here
	//GetUsedObjects(usedObjs);

	for_i0(i,SV6_OBJDAT_NUMENTRIES_RIDES){
		if(!usedObjs.rides[i])
		DeleteItem(objIdxMap.rides[i]);}
	for_i0(i,SV6_OBJDAT_NUMENTRIES_SMALLSCENERY){
		if(!usedObjs.smallScenery[i])
		DeleteItem(objIdxMap.smallScenery[i]);}
	for_i0(i,SV6_OBJDAT_NUMENTRIES_LARGESCENERY){
		if(!usedObjs.largeScenery[i])
		DeleteItem(objIdxMap.largeScenery[i]);}
	for_i0(i,SV6_OBJDAT_NUMENTRIES_WALLS){
		if(!usedObjs.walls[i])
		DeleteItem(objIdxMap.walls[i]);}
	for_i0(i,SV6_OBJDAT_NUMENTRIES_PATHS){
		if(!usedObjs.paths[i])
		DeleteItem(objIdxMap.paths[i]);}
	for_i0(i,SV6_OBJDAT_NUMENTRIES_PATHUTILITIES){
		if(!usedObjs.pathUtilities[i])
		DeleteItem(objIdxMap.pathUtilities[i]);}

	UpdateImgPreview();	

}
//##############
//##############


void CParkDatDlg::OnButtonSearch() 
{
	LVFINDINFO fi;
	// TODO: Add your control notification handler code here
	POSITION p;
	int i;
	p=datList.GetFirstSelectedItemPosition();
	if(p!=NULL)
	{
		i=datList.GetNextSelectedItem(p);
		i=datList.GetParam(i);
	}
	else{i=0;}
	
	DataGet();
	#if 0
	fi.flags=
		LVFI_STRING|LVFI_PARTIAL|LVFI_WRAP;
	fi.psz=searchText;
	fi.lParam=0;
	fi.vkDirection=VK_DOWN;
	fi.pt.x=1;
	fi.pt.y=0;
	#endif
	if(searchText!="")
	i=datList.TextSearch(i+1,searchText,true,true);
	CDC*srdc=searchRslt.GetDC();
	if(i==-1)
	{
		searchRslt.SetWindowText("Text not found");
		srdc->SetTextColor(RGB(255,0,0));
		searchRslt.UpdateWindow();
	}
	else
	{
		searchRslt.SetWindowText("Text found");
		srdc->SetTextColor(RGB(64,64,64));
		searchRslt.UpdateWindow();

		datList.SelectItem(i);
	}
}
