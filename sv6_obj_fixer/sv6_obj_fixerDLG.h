// sv6_obj_fixerDlg.h : header file
//

#if !defined(AFX_SV4_TO_SV6DLG_H__6B0E1D81_3434_4405_BA62_C3A1D3A1E435__INCLUDED_)
#define AFX_SV4_TO_SV6DLG_H__6B0E1D81_3434_4405_BA62_C3A1D3A1E435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSv6_obj_fixerDlg dialog

#define FILENAME_MAXSIZE 128
#define SETTINGS_FILENAME "settings.txt"
#define DDX_SET FALSE
#define DDX_GET TRUE

class CSv6_obj_fixerDlg : public CDialog
{
// Construction
public:
	char 
		settings_filename[FILENAME_MAXSIZE],
		sv6FileName[FILENAME_MAXSIZE],
		ioBuffer[FILENAME_MAXSIZE*3];

	int
		settings_fHndl,
		settings_fileLength;
	
	CSv6_obj_fixerDlg(CWnd* pParent = NULL);	// standard constructor

//IDD_SV6_OBJ_FIXER_DIALOG	IDD_SV6_OBJ_FIXER_DIALOG

// Dialog Data
	//{{AFX_DATA(CSv6_obj_fixerDlg)
	enum { IDD = IDD_SV6_OBJ_FIXER_DIALOG };
	CEdit	m_sv6FileNameEdit;
	CString	m_sv6FileName;
	CString	m_messageText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSv6_obj_fixerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSv6_obj_fixerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnCancel();
	virtual void OnOK( );
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSv4name();
	afx_msg void OnButtonWritesv6file();
	afx_msg void OnButtonSv6name();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef class CSv6_obj_fixerDlg CSV6_OBJ_FIXERDLG;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SV4_TO_SV6DLG_H__6B0E1D81_3434_4405_BA62_C3A1D3A1E435__INCLUDED_)
