#ifndef RCTFUNCS_H
#define RCTFUNCS_H

int GetRctPath(char *path);

typedef enum
{
	FAT_LOAD,
	FAT_SAVE,
} RCT_FILE_ACCESSTYPE;

typedef enum
{
	FT_SC4,
	FT_SV4
} RCT_FILETYPE;

int BrowseRctFile(int accessType, char *retFilename, int fileType);

#endif //RCTFUNCS_H
