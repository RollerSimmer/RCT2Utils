// ReportControl.cpp : implementation file
//

#include "stdafx.h"
#include "ParkDat.h"
#include "ReportControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportControl

ReportControl::ReportControl()
{
}

ReportControl::~ReportControl()
{
}


BEGIN_MESSAGE_MAP(ReportControl, CListCtrl)
	//{{AFX_MSG_MAP(ReportControl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReportControl message handlers

void ReportControl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	const int COL = pNMListView->iSubItem;
	SortItems(COL, COL == m_nSortCol ? !m_bSortAscending : TRUE);

	*pResult = 0;
}

int ReportControl::GetIndex(int row)
{
	return(GetParam(row));
};

int ReportControl::GetParam(int row)
{
	int p;
	p=this->GetItemData(row);
	return p;
};

ReportControl::SelectItem(int i)
{
	EnsureVisible(i,FALSE);
	SetSelectionMark(i);
	SetItemState
	(i,LVIS_SELECTED|LVIS_FOCUSED,0xFF);
	RedrawItems(i,i);
	UpdateWindow();
}

int ReportControl::TextSearch
(int i,char*s,bool wrap,bool caseIgnore)
{
	CString ss=s;
	return(TextSearch(i,ss,wrap,caseIgnore));	
}

int ReportControl::TextSearch
(int i,CString ss,bool wrap,bool caseIgnore)
{
	//int j=0;
	int ic,jc,ii,jj;
	int fi;
	CString cs;
	if(caseIgnore)ss.MakeUpper();
	ic=this->GetItemCount();
	jc=this->GetColumnCount();
	for(ii=i;ii<ic;ii++){for(jj=0;jj<jc;jj++){
		cs=GetItemText(ii,jj);
		if(caseIgnore)cs.MakeUpper();
		fi=cs.Find(ss);
		if(fi!=-1)	return ii;
	}}
	if(wrap)	{
	for(ii=0;ii<=i;ii++){for(jj=0;jj<jc;jj++){
		cs=GetItemText(ii,jj);
		if(caseIgnore)cs.MakeUpper();
		fi=cs.Find(ss);
		if(fi!=-1)	return ii;
	}}
	}
	return(-1);
} 
