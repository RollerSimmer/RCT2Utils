#ifndef BITMAP_COMPILE_H
#define BITMAP_COMPILE_H

#include"../stdafx.h"
//#include "../RCT2Landmark_LScen.h"
#include "../RCT2Landmark_LScenDlg.h"
#include<fileio2.h>
#include<rct2lib.h>
#include<bmplib.h>

Bitmap_Compile__ReadFullView
(	WORD width,WORD height,WORD menuWidths[4],WORD menuHgts[4],
	BYTE*menuImgs[4],BYTE*imgData[4],OBJDAT_FILE&odat,
	bool doFlip,
	WORD seeThruColor
);



#endif