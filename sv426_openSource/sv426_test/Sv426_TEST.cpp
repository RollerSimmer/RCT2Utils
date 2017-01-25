// SC426_TEST.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include<rct2lib.h>
#include<rct1lib.h>
#include<codeshortcuts.h>
#include"426/mapConvert.h"
#include"426/ConvertParkData.h"

SV4_FILE sv4;
SV6_FILE sv6;


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	HMODULE rct2lib_module=GetModuleHandle("rct2lib.dll");

	InitObjects();

	sv4.OpenSv4("testsv4.SV4");
	sv6.GenNewPark(rct2lib_module);

	{

	memcpy
	(	&sv6.fileDataA.availableItems
		,&RCT1emulationTable
		,sz(SV6_OBJDAT_HEADER_BLOCK_ALT)
	);


	ConvertMap
	(
		sv6.fileDataA.parkMap
		,sv4.fileDataA.parkData.parkMap
		,sv4.fileDataA.parkData.parkSize
	);

	ConvertParkData
	(
		sv6
		,sv4.fileDataA.parkData
	);


	sv6.InitMapPtrs();

	//convert here

	}
	sv6.SaveSv6("testsv6.SV6");

	return 0;
}



