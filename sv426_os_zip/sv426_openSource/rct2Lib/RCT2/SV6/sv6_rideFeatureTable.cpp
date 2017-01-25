#include<windows.h>
#include"../../resource.h"
#include"sv6.h"
#include"codeshortcuts.h"

void*GetCustResourceBufr(int rsrcID,char*rsrcType)
{
	HGLOBAL hResData;
	HRSRC hResInfo;
	HMODULE hMod;
	int err;

	void*rsrcBuf;

	hMod=GetModuleHandle("rct2Lib.dll");

	hResInfo
		=
	FindResource(hMod,MAKEINTRESOURCE(rsrcID),rsrcType);		
	if(!hResInfo)
	{
		err=GetLastError();

	};
	hResData=LoadResource(hMod,hResInfo);
	return(LockResource(hResData));
}

dllPort 
int	
SV6_FILE
::
SetAllTrackFeatures()
{
	int i;
	typedef BYTE RFRT[0x5b][4];
	RFRT*rfrtBuf=
	(RFRT*)
		GetCustResourceBufr(IDR_RIDE_FEATURE_TABLE1,"RIDE_FEATURE_TABLE");


	for_i0(i,2)
	{
		memcpy
		(
			&(this->fileDataA.parkData.rideFeatureTable[i])
			,
			&rfrtBuf[i]
			,
			sz(rfrtBuf[i])
		);
	}

	return(true);

}

dllPort 
int	
SV6_FILE
::
SetTrackFeatures(short trackIndex)
{

	return(true);
}
