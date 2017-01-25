// RidesMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RidesMenu dialog

class RidesMenu : public CDialog
{
// Construction
public:
	RidesMenu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RidesMenu)
	enum { IDD = IDD_RIDESMENU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RidesMenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RidesMenu)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
