#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include"../stdafx.h"
#include<rct2lib.h>
#include<fileio2.h>

#include"parse.h"

Parse_Input
(	FILE*inputFile,OBJDAT_FILE&obj,
	FILENAME&datFileName,
	FILENAME&rlpFileName,
	CRCT2Landmark_LScenDlg&dlg
);

#endif //PARSE_OUTPUT_H
