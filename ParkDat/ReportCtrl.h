#if !defined(AFX_REPORTCTRL_H__EE5330CE_8B51_4793_9C0E_93855973D327__INCLUDED_)
#define AFX_REPORTCTRL_H__EE5330CE_8B51_4793_9C0E_93855973D327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ReportCtrl window

typedef int (CALLBACK*PCOMPARE)(long,long,long); 

class ReportCtrl : public CListCtrl
{
// Construction
public:
	ReportCtrl();

	SwapItems(LVITEM&a,LVITEM&b);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReportCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:


	virtual ~ReportCtrl();

	SortItems(int col,int order);
	// Generated message map functions
protected:
	//{{AFX_MSG(ReportCtrl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCTRL_H__EE5330CE_8B51_4793_9C0E_93855973D327__INCLUDED_)
