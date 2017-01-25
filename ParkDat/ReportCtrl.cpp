// ReportCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ParkDat.h"
#include "ReportCtrl.h"
#include<codeshortcuts.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportCtrl

ReportCtrl::ReportCtrl()
{
}

ReportCtrl::~ReportCtrl()
{
}


BEGIN_MESSAGE_MAP(ReportCtrl, CListCtrl)
	//{{AFX_MSG_MAP(ReportCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReportCtrl message handlers

typedef int (CALLBACK *cmpFuncTyp)(LPARAM, LPARAM, LPARAM);

int CALLBACK
SortCompare
(LPARAM p,LPARAM q,LPARAM sortVal)
{
	int retV=0;

	switch(sortVal)
	{
	case 1:
		retV=p-q;
		break;
	}

	return(retV);		
} 




void ReportCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW*lv = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int col=lv->iSubItem;

#if 0
	SortItems(col,1);
#endif

	*pResult = 0;
	
}

#define MAX_ROWS 2000
#define MAX__STRING_TABLE__SIZE 64
#define MAX__STRING_TABLE__LEN (MAX__STRING_TABLE__SIZE-1)
char strTbl[MAX_ROWS][MAX__STRING_TABLE__SIZE];

ReportCtrl::SortItems(int col,int order)
{
	int numItems=GetItemCount();
	int i,j,k,c;
	int*lo,*hi;
	LVITEM*loItem,*hiItem,*lviTmp;
	static LVITEM*lvi=NULL;
	if(order==0)
		return 0;

	if
	(
		lviTmp=(LVITEM*)realloc(lvi,sz(LVITEM)*numItems)
	)
		lvi=lviTmp;
	else
		return 0;

	if(order>0)//descending
	{
		lo=&j;
		hi=&i;
	}
	else
	{
		lo=&i;
		hi=&j;
	}
	char**loStr,**hiStr;

	for_i0(k,numItems)
	{
		lvi[k].mask=LVIF_TEXT;
		lvi[k].iItem=k;
		lvi[k].iSubItem=col;

		lvi[k].pszText=strTbl[k];
		lvi[k].cchTextMax=MAX__STRING_TABLE__SIZE;

		lvi[k].iItem=k;
		GetItem(&lvi[k]);
	}

	for_i0(i,numItems-1)
	{
		j=0;

		for_i_span_std(j,(i+1),(numItems-1))
		{
			loItem=&lvi[*lo];
			hiItem=&lvi[*hi];

			loStr=&loItem->pszText;
			hiStr=&hiItem->pszText;

			if((c=strcmp(*loStr,*hiStr))>0)
			{
				SwapItems(*loItem,*hiItem);
			}
		}
	}


	for_i0(k,numItems)
	{
		SetItem(&lvi[k]);
	}

}

ReportCtrl::SwapItems(LVITEM&a,LVITEM&b)
{
	int tmpItemI;
	tmpItemI=a.iItem;
	a.iItem=b.iItem;
	b.iItem=tmpItemI;
}
