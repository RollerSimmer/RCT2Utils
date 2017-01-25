// sv6ObjExtractDlg.h : header file
//

#if !defined(AFX_SV6OBJEXTRACTDLG_H__8E75B615_1358_480D_9D40_A536EBD53EA8__INCLUDED_)
#define AFX_SV6OBJEXTRACTDLG_H__8E75B615_1358_480D_9D40_A536EBD53EA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSv6ObjExtractDlg dialog

#define FILENAME_MAXSIZE 0x100
#define SETTINGS_FILENAME "settings.txt"
#define DDX_SET FALSE
#define DDX_GET TRUE

class CSv6ObjExtractDlg : public CDialog
{
// Construction
public:
	char 
		settings_filename[FILENAME_MAXSIZE],
		ioBuffer[FILENAME_MAXSIZE*2],
		sv6FileName[FILENAME_MAXSIZE],
		extractDir[FILENAME_MAXSIZE];
	int settings_fHndl;
	long settings_fileLength;
	
	CSv6ObjExtractDlg(CWnd* pParent = NULL);	// standard constructor

	ProgressMessage(char*message);

// Dialog Data
	//{{AFX_DATA(CSv6ObjExtractDlg)
	enum { IDD = IDD_SV6OBJEXTRACT_DIALOG };
	CString	m_extractDir;
	CString	m_sv6Name;
	CString	m_progressMessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSv6ObjExtractDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSv6ObjExtractDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSv6name();
	afx_msg void OnButtonExtractdir();
	afx_msg void OnButtonExtractobjects();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef class CSv6ObjExtractDlg CSv6ObjExtractDlg_type;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SV6OBJEXTRACTDLG_H__8E75B615_1358_480D_9D40_A536EBD53EA8__INCLUDED_)
