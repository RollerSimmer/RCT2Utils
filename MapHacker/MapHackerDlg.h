// MapHackerDlg.h : header file
//

#if !defined(AFX_MAPHACKERDLG_H__E5A0A6D1_4C42_438F_BC55_4804AC69040E__INCLUDED_)
#define AFX_MAPHACKERDLG_H__E5A0A6D1_4C42_438F_BC55_4804AC69040E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMapHackerDlg dialog

class CMapHackerDlg : public CDialog
{
// Construction
public:
	CMapHackerDlg(CWnd* pParent = NULL);	// standard constructor

	HWND rct2Window;

// Dialog Data
	//{{AFX_DATA(CMapHackerDlg)
	enum { IDD = IDD_MAPHACKER_DIALOG };
	CString	hexData;
	//}}AFX_DATA
	
	struct
	{
		short	x;
		short	y;
		short	z;
		short d[8];
	}
	ad;

	DdxGet();
	DdxSet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapHackerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMapHackerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonRefresh();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonHexGet();
	afx_msg void OnButtonHexSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPHACKERDLG_H__E5A0A6D1_4C42_438F_BC55_4804AC69040E__INCLUDED_)
