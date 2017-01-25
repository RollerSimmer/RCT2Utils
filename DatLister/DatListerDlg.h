// DatListerDlg.h : header file
//

#if !defined(AFX_DATLISTERDLG_H__2ECB7359_6992_44A7_B274_976ECD183414__INCLUDED_)
#define AFX_DATLISTERDLG_H__2ECB7359_6992_44A7_B274_976ECD183414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDatListerDlg dialog

class CDatListerDlg : public CDialog
{
// Construction
public:
	CDatListerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDatListerDlg)
	enum { IDD = IDD_DATLISTER_DIALOG };
	CProgressCtrl	progressBar;
	CListCtrl	datList;
	CString	datFolder;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatListerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDatListerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDirectorySelect();
	afx_msg void OnButtonList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATLISTERDLG_H__2ECB7359_6992_44A7_B274_976ECD183414__INCLUDED_)
