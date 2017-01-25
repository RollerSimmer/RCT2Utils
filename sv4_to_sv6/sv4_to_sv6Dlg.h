// sv4_to_sv6Dlg.h : header file
//

#if !defined(AFX_SV4_TO_SV6DLG_H__6B0E1D81_3434_4405_BA62_C3A1D3A1E435__INCLUDED_)
#define AFX_SV4_TO_SV6DLG_H__6B0E1D81_3434_4405_BA62_C3A1D3A1E435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSv4_to_sv6Dlg dialog

#define FILENAME_MAXSIZE 128
#define SETTINGS_FILENAME "settings.txt"
#define DDX_SET FALSE
#define DDX_GET TRUE

class CSv4_to_sv6Dlg : public CDialog
{
// Construction
public:
	char 
		settings_filename[FILENAME_MAXSIZE],
		sv4FileName[FILENAME_MAXSIZE],
		sv6FileName[FILENAME_MAXSIZE],
		ioBuffer[FILENAME_MAXSIZE*3];

	int
		settings_fHndl,
		settings_fileLength;
	
	CSv4_to_sv6Dlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	//{{AFX_DATA(CSv4_to_sv6Dlg)
	enum { IDD = IDD_SV4_TO_SV6_DIALOG };
	CProgressCtrl	m_progress;
	CEdit	m_sv6FileNameEdit;
	CEdit	m_sv4FileNameEdit;
	CString	m_sv4FileName;
	CString	m_sv6FileName;
	CString	m_message;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSv4_to_sv6Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSv4_to_sv6Dlg)
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SV4_TO_SV6DLG_H__6B0E1D81_3434_4405_BA62_C3A1D3A1E435__INCLUDED_)
