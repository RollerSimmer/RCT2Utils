// RCT2Landmark_LScenDlg.h : header file
//

#if !defined(AFX_RCT2LANDMARK_LSCENDLG_H__C92C74ED_3692_4D1B_9D17_822FAD1C6BAF__INCLUDED_)
#define AFX_RCT2LANDMARK_LSCENDLG_H__C92C74ED_3692_4D1B_9D17_822FAD1C6BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRCT2Landmark_LScenDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CRCT2Landmark_LScenDlg dialog

#define RCT2LMM_SETTINGS_FILE "RCT2LMM_settings.bin"
#define RCT2LIB_DLL__PATH "E:\Programming\dlls\rct2Lib.dll"

typedef 
class CRCT2Landmark_LScenDlg : public CDialog
{
	DECLARE_DYNAMIC(CRCT2Landmark_LScenDlg);
	friend class CRCT2Landmark_LScenDlgAutoProxy;

// Construction
public:
	HINSTANCE rct2Lib_handle;

	FILENAME
		settingsFile;

	struct
	{
		FILENAME
			lscenDatFName,
			projectFName;
		UINT startImgI;
		bool useImgI;
		bool useColRowRot;		
	}
		appData;

	CString	outputStr;

	ExtractProjectFile();
	CRCT2Landmark_LScenDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CRCT2Landmark_LScenDlg();
	BOOL DataSet();
	BOOL DataGet();

	AddOutputLine(char*line);

	ProgressInit(int lo,int hi,int pos,int step);
	ProgressInit();
	Progress();

// Dialog Data
	//{{AFX_DATA(CRCT2Landmark_LScenDlg)
	enum { IDD = IDD_RCT2LANDMARK_LSCEN_DIALOG };
	CEdit	outputBox;
	CProgressCtrl	progressBar;
	CString	lscenDatName;
	CString	rct2lmmProjectName;
	UINT	startImgI;
	BOOL	useImgI;
	BOOL	useColRowRot;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRCT2Landmark_LScenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL UpdateData( BOOL bSaveAndValidate = TRUE );
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRCT2Landmark_LScenDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CRCT2Landmark_LScenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonSv6name();
	afx_msg void OnButtonExtractToProject();
	afx_msg void OnButtonExtractBitmaps();
	afx_msg void OnButtonLscenDatName();
	afx_msg void OnButtonRct2lmmProjectName();
	afx_msg void OnButtonTestSaveDat();
	afx_msg void OnButtonExtractFullViews();
	afx_msg void OnButtonExtractTileImages();
	afx_msg void OnButtonBuildDat();
	afx_msg void OnCheckUseColRowRot();
	afx_msg void OnCheckUseImgNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
}CRCT2Landmark_LScenDlg;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCT2LANDMARK_LSCENDLG_H__C92C74ED_3692_4D1B_9D17_822FAD1C6BAF__INCLUDED_)
