#include"Parse_Output.h"
#include<codeshortcuts.h>

enum
{
	SECTION__INFO_HEADER=0,
	SECTION_NAMES,
	SECTION_POS,
	SECTION_IMAGES,
	SECTION_END,
	NUM_SECTIONS
};

Parse_Output
(	FILE*outputFile,OBJDAT_FILE&obj,
	UINT startImgI,
	bool useImgI,
	bool useColRowRot,
	CRCT2Landmark_LScenDlg&dlg
)
{
	int objType=obj.objType;


	#define o outputFile
	#define oh obj.objHeader.typLScen
	#define ofh \
		obj.objFileHeader
	#define tp obj.optional.largeScenery.tilePos
	#define boolStr(a) (a?sOn:sOff)
	#define id obj.imageDirectory

	dlg.ProgressInit(0,NUM_SECTIONS,0,1);
	fprintf(o,"\r\n[infoHeader]\r\n\r\n");
	#include"Parse_Output_infoHeader.inl"
	dlg.Progress();
	
	fprintf(o,"\r\n[names]\r\n\r\n");
	#define ste obj.stringTable[0].entries

	#include"Parse_Output_names.inl"
	dlg.Progress();
	

	#undef ste

	fprintf(o,"\r\n[pos]\r\n\r\n");

	#include"Parse_Output_pos.inl"
	dlg.Progress();

	fprintf(o,"\r\n[Images_Full]\r\n\r\n");

	#define PARSE_OUTPUT_IMAGE__DO_IMAGEDIRECTORY 1

	#include"Parse_Output_image.inl"
	dlg.Progress();

	#undef PARSE_OUTPUT_IMAGE__DO_IMAGEDIRECTORY
	#undef oh// obj.objHeader.typLScen
	#undef o// outputFile
	#undef tp
	#undef boolStr
	dlg.Progress();

}
