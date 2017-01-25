// ParkDatDlg.h : header file
//

#if !defined(AFX_PARKDATDLG_H__095E4EC6_BA91_4A97_9D05_DBA5D80B260C__INCLUDED_)
#define AFX_PARKDATDLG_H__095E4EC6_BA91_4A97_9D05_DBA5D80B260C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<rct2lib.h>
#include"ReportControl.h"
#include"ParkDat_Class_ImgPreview.h"

class CParkDatDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CParkDatDlg dialog

class CParkDatDlg : public CDialog
{
	DECLARE_DYNAMIC(CParkDatDlg);
	friend class CParkDatDlgAutoProxy;

// Construction
public:
	CParkDatDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CParkDatDlg();

	bool sv6Loaded;

	struct
	{
		FILENAME sv6Name;
	}
	appData;

	CString outputStr;



	FILENAME settingsFile;

	UpdateDatTable();

	ProgressStart(int lo,int hi,int pos,int step);
	ProgressEnd();
	ProgressStep();

	LoadSettings();
	SaveSettings();

	DataGet();
	DataSet();

	ReplaceItem(int i,OBJDATHEADER&o);
	ReplaceItem(int i,char*ofn);

	DeleteItem(int i);

	SetMenusToAvailable();

	UpdateViewTableItem(int i);
	UpdateViewTableItem_ListI(int i);

	UpdateImgPreview();

	int FindListIndex(int i);

	SetDatListToDefStyle();

	OutputMsg
	(	int code,
		int d1,char*s1,
		int d2,char*s2
	);
	OutputMsg
	(	int code,
		int d,char*s
	);
	OutputMsg
	(	int code,
		int d,char*s1,char*s2
	);
	OutputMsg(int code);
	CParkDatDlg::OutputMsg(int code,char*s);


// Dialog Data
	//{{AFX_DATA(CParkDatDlg)
	enum { IDD = IDD_PARKDAT_DIALOG };
	CStatic	searchRslt;
	ParkDat_Class_ImgPreview	imgPreview;
	CEdit	outputBox;
	ReportControl	datList;
	CProgressCtrl	progress;
	CString	sv6Name;
	CString	searchText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkDatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CParkDatDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();
	
	
	InitDatListCtrl();

	// Generated message map functions
	//{{AFX_MSG(CParkDatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonSv6Name();
	afx_msg void OnButtonOpenSv6();
	afx_msg void OnButtonAddDat();
	afx_msg void OnButtonDeleteSelectedDat();
	afx_msg void OnButtonReplaceSelectedDat();
	afx_msg void OnButtonUpdateDatHeaders();
	afx_msg void OnButtonSaveSv6();
	afx_msg void OnButtonUpdateImgPreview();
	afx_msg void OnKeydownListDats(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListDats(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemdblclickListDats(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListDats(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDeleteUnused();
	afx_msg void OnButtonSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKDATDLG_H__095E4EC6_BA91_4A97_9D05_DBA5D80B260C__INCLUDED_)
