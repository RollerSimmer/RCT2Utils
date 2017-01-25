#ifndef PARSE_OUTPUT_H
#define PARSE_OUTPUT_H

#include"../stdafx.h"
#include "../RCT2Landmark_LScen.h"
#include "../RCT2Landmark_LScenDlg.h"
#include<rct2lib.h>

#include"parse.h"

Parse_Output
(	FILE*outputFile,OBJDAT_FILE&obj,
	UINT startImgI,
	bool useImgI,
	bool useColRowRot,
	CRCT2Landmark_LScenDlg&dlg
);

#endif //PARSE_OUTPUT_H
