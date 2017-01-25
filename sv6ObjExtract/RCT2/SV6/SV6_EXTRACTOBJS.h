
#ifndef SV6_EXTRACTOBJS_H
#define SV6_EXTRACTOBJS_H

#include <windows.h>
#include <FileIO2.h>
#include <stdlib2.h>
#include "SV6_DECODE.h"
#include <string.h>
#include <stdio.h>

#define sz(a) (sizeof(a))

MakeDatName(char *fullDatName,SV6_OBJDAT_HEADER *datHeader,char *baseDir);
int ExtractImportObjects
(	
	void*inBufferP,
	int i,
	int objsLeft,
	char*extractDir,
	CSv6ObjExtractDlg_type *dlg
);

ExtractSv6Objs
(	SV6_FILE*sv6,char *inFileStream,int sv6CompressedSize,
	char *extractDir,
	CSv6ObjExtractDlg_type *dlg
);

ExtractSv6Objects
(	
	char *sv6FileName,
	char *extractDir,
	CSv6ObjExtractDlg_type *dlg
);
#undef sz

#endif //SV6_EXTRACTOBJS_H
