#include "moneyfuncs.h"
#include "..\rct2.h"
#include "..\8cars.h"
#include <math.h>
#include <string.h>
//#include "TEXTINPUT.H"

//moneyfuncs.c

int ReadFinance(FINANCEID financeID)
{	int finance=0;
	
	switch(financeID)
	{
	case F_MONEY:
		WinRead(mainWindow,RCT2_TITLE,&finance,RCT2_ADDR_MONEY,4);
		break;
	case F_LOAN:
		WinRead(mainWindow,RCT2_TITLE,&finance,RCT2_ADDR_LOAN,4);
		break;
	case F_HIGHLOAN:
		WinRead(mainWindow,RCT2_TITLE,&finance,RCT2_ADDR_HIGHLOAN,4);
		break;
	case F_CHECKSUM1:
		WinRead(mainWindow,RCT2_TITLE,&finance,RCT2_ADDR_FINANCHECKSUM1,4);
		break;
	case F_CHECKSUM2:
		WinRead(mainWindow,RCT2_TITLE,&finance,RCT2_ADDR_FINANCHECKSUM2,4);
		break;
	}

	return finance;

}

int ChangeMoney(int newval)
{
	long money,loan,highloan,checksum1,checksum2;

	money=newval;
	WinRead(mainWindow,RCT2_TITLE,&loan,RCT2_ADDR_LOAN,4);
	WinRead(mainWindow,RCT2_TITLE,&highloan,RCT2_ADDR_HIGHLOAN,4);

	/*
	1st financial checksum:
			[ 70093A minus cash, ror 5, 
			minus loan, ror
			7, add maxloan, ror 3 ] 
	*/

	//calc checksum1

	__asm
	{
		mov eax,70093Ah
		sub eax,money
		ror eax,5
		sub eax,loan
		ror eax,7
		add eax,highloan
		ror eax,3
		mov checksum1,eax
	}

	
	/*
	2nd financial checksum:
			cash ror thirteen, 
			xor 0F4EC9621
	*/

	//calc checksum2
	__asm
	{
		mov eax,money
		ror eax,13
		xor eax,0F4EC9621h
		mov checksum2,eax 
	}

//	softice rules

/*
	umm... rotate the amount of money(dword) by 0D and xor 
	by F4EC9621 then store it in 013587F8... that works for me 
*/
	WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_MONEY,&money,4);
	WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_FINANCHECKSUM1,&checksum1,4);
	WinWrite(mainWindow,RCT2_TITLE,RCT2_ADDR_FINANCHECKSUM2,&checksum2,4);

}

int IncCash(int addval,int roundflag,int roundunit)
{	int money,moneymod;
	roundunit=abs(roundunit);
	money=ReadFinance(F_MONEY);
	money+=addval;
	if(roundflag)
	{	moneymod=money%roundunit;
		if (abs(moneymod)>=(roundunit/2))
			money=money/roundunit*(roundunit+1);
		else 
			money=money/roundunit*roundunit;		
	}
	ChangeMoney(money);
}

int IncCashCustom()
{
	char *chp,tmpstr[17];
	int cashAmt;

	if(	(chp=TextInputBox(hinst,mainWindow,
				tmpstr,
				"Enter cash sum (negative reduces):","",16)
		)!=NULL
	)
	{
		//strcpy(tmpstr,chp);
		IncCash(cashAmt=atoi(tmpstr),FALSE,0);
	}
}

