#ifndef BITMAP_EXTRACT_H
#define BITMAP_EXTRACT_H

#include"../stdafx.h"
//#include "../RCT2Landmark_LScen.h"
#include "../RCT2Landmark_LScenDlg.h"
#include<fileio2.h>
#include<rct2lib.h>
#include<bmplib.h>

Bitmap_Extract(FILENAME&basePath,OBJDAT_FILE&odat,CRCT2Landmark_LScenDlg&dlg);
Bitmap_Extract_TileViews
(	FILENAME&basePath,OBJDAT_FILE&odat,
	CRCT2Landmark_LScenDlg&dlg,
	UINT startImgI,
	bool useImgI,
	bool useColRowRot
);

#endif