#if !defined(AFX_REPORTCONTROL_H__2988F5BD_DDFD_4FAD_8E1E_1CF149261BCA__INCLUDED_)
#define AFX_REPORTCONTROL_H__2988F5BD_DDFD_4FAD_8E1E_1CF149261BCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportControl.h : header file
//

#include<ReportCtrl.h>

/////////////////////////////////////////////////////////////////////////////
// ReportControl window

class ReportControl : public CReportCtrl
{
public:
	int GetIndex(int row);
	int GetParam(int row);
	
// Construction
public:
	ReportControl();
	SelectItem(int i);
	int TextSearch(int i,CString s,bool wrap,bool caseIgnore);
	int TextSearch(int i,char*s,bool wrap,bool caseIgnore);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReportControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ReportControl();


	// Generated message map functions
protected:
	//{{AFX_MSG(ReportControl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCONTROL_H__2988F5BD_DDFD_4FAD_8E1E_1CF149261BCA__INCLUDED_)
