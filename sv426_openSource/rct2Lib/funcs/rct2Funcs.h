#ifndef RCT2FUNCS_H
#define RCT2FUNCS_H

#ifndef dllPort
	#define dllPort __declspec(dllexport)
#endif

dllPort
int GetRct2Path(char *path);

typedef enum
{
	FAT_LOAD,
	FAT_SAVE,
} RCT2_FILE_ACCESSTYPE;

#ifndef _RCT2_
typedef enum
{
	FT_RCT2_OBJDAT,
	FT_SC6,
	FT_SV6
} RCT2_FILETYPE;
#endif//ndef _RCT2_

dllPort
int BrowseRct2File(int accessType, char *retFilename, int fileType);

#endif //RCT2FUNCS_H
