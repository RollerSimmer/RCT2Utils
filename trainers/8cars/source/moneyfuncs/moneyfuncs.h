//moneyfuncs.h

#ifndef _MONEYFUNCS_
#define _MONEYFUNCS_


typedef enum 
{	F_MONEY,
	F_LOAN,
	F_HIGHLOAN,
	F_CHECKSUM1,
	F_CHECKSUM2,
}FINANCEID;

int IncCash(int addval,int roundflag,int roundunit);
int ReadFinance(FINANCEID financeID);
int IncCashCustom();

#endif //_MONEYFUNCS_
