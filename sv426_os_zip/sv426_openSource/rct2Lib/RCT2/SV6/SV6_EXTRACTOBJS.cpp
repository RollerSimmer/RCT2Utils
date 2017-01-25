#if 0
#include "../../stdafx.h"
#include "../../sv6ObjExtract.h"
#include "../../sv6ObjExtractDlg.h"

#include <FileIO2.h>
#include <stdlib2.h>
#include <string.h>
#include <stdio.h>

#include "SV6_EXTRACTOBJS.h"


#define sz(a) (sizeof(a))

#define Progress(a,b) (ProgressMsg(dlg,(a),(b)))

ProgressMsg
(
	CSv6ObjExtractDlg_type*dlg,
	char*format,char*s
)
{
	char message[512];
	sprintf(message,format,s);
	dlg->ProgressMessage(message);	
}

MakeDatName(char *fullDatName,SV6_OBJDAT_HEADER *datHeader,char *baseDir)
{
	#define OBJX_FORMAT "obj%05.5d.DAT" 
	char 
		name[16],
		path[0x180],
		basePath[0x180];
	int i;

	memset(name,0,sz(name));
	memcpy(name,datHeader->filename,sz(datHeader->filename));
	strtok(name," ");
	strcat(name,".DAT");
	strcpy(path,baseDir);
	switch(path[__max(strlen(path),1)-1])
	{
	case '\\':
	case '/':
		break;
	default:
		strcat(path,"\\");
		break;
	}
	strcpy(basePath,path);
	strcat(path,name);

	i=0;

	while((FExist(path)&&(i<100000)))
	{
		strcpy(path,basePath);
		sprintf(name,OBJX_FORMAT,i);
		strcat(path,name);
		++i;
	}
	if(FExist(path))
		path[0]=0;

	strcpy(fullDatName,path);	
}


int ExtractImportObjects
(	
	void*inBufferP,
	int i,
	int objsLeft,
	char*extractDir,
	CSv6ObjExtractDlg_type *dlg
)
{
	int j;

	char 
		tmpPath[0x180];

	SV6_OBJDAT_HEADER_AND_CHUNK_HEADER
		*imporObjBlock=
			(SV6_OBJDAT_HEADER_AND_CHUNK_HEADER*)
			inBufferP;

	#define iob (*imporObjBlock)
	#define bytBuf ((BYTE*)inBufferP)
	DoImportObjectSkip:
	{
		j=0;


		//imporObjBlock->
		while(objsLeft>0)
		{
			MakeDatName
			(
				tmpPath,
				&(iob.objHeader),
				extractDir
			);
			Progress("Extracting DAT\r\n\"%s\"",tmpPath);
			QuickWrite
			(
				&iob,tmpPath,0,
				sz(iob)+iob.chunkHeader.chunkSize_Encoded
			);

			j+=sz(iob);
			j+=iob.chunkHeader.chunkSize_Encoded;
			imporObjBlock=
				(SV6_OBJDAT_HEADER_AND_CHUNK_HEADER*)
				&bytBuf[j];
			objsLeft--;
		}
		
		i+=j;
	}
	#undef bytBuf
	#undef iob

	return i;
	
}

//#include "SV6_DECODE_DecodeSv6Chunk.inl"


ExtractSv6Objs
(	SV6_FILE*sv6,char *inFileStream,int sv6CompressedSize,
	char *extractDir,
	CSv6ObjExtractDlg_type *dlg
)
{
	DWORD i=0,chunkI;

	#define s (sv6->fileDataA)
	#define chunkAtI (*((SV6_CHUNK*)(&inFileStream[i])))
	#define ifs inFileStream
	#define cc chunkAtI
	#define cch \
		(cc.header)
	#define equ(a,b) (memmove(a,b,sz(a)))
	#define mm(a,b,c) (memmove(a,b,c))
	#define ms0_v(a) (memset(&(a),0,sz(a)))

	
	DoExtractSv6Objs:
	{
		ms0_v(s);
		chunkI=0;

		i=DecodeSv6Chunk(&s.header_header,((BYTE*)(&s.header)),sz(s.header),&cc.header,(BYTE*)(&cc.buffer),i);
		chunkI++;

		i=
			ExtractImportObjects
			(	
				&cc,i,
				s.header.numImbeddedCustomObjs,
				extractDir,
				dlg
			);

		s.header.numImbeddedCustomObjs=0;
	}
	#undef ms0_v
	#undef mm
	#undef equ
	#undef cc
	#undef cch
	#undef ifs
	#undef chunkAtI
	#undef s
}

ExtractSv6Objects
(	
	char *sv6FileName,
	char *extractDir,
	CSv6ObjExtractDlg_type *dlg
)
{
	SV6_FILE*sv6=(SV6_FILE*)malloc(sz(SV6_FILE));

	int sv6CompressedSize;
	char *inFileStream;

	if(FExist(sv6FileName))
	{
		Progress("Opening SV6 file\r\n\"%s\"",sv6FileName);

		sv6CompressedSize=FSize(sv6FileName);
		inFileStream=(char*)malloc(sv6CompressedSize);

		QuickRead(inFileStream,sv6FileName,0,sv6CompressedSize);

		ExtractSv6Objs
		(	sv6,inFileStream,sv6CompressedSize,extractDir,
			dlg
		);

		Progress("\"%s\"\r\nextracted",sv6FileName);
		
		free(inFileStream);
	}	

	free(sv6);

}

#undef sz


#endif