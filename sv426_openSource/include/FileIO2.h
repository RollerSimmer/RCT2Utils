#ifndef _FILEIO2_H_
#define _FILEIO2_H_

#define WIN32_EXTRA_LEAN
//#include <windows.h> 
//#include <afx.h>
#include <shlobj.h>
#include <commdlg.h>
#include <stdMacros.h>

#define FILESTRING_MAXLEN 260
#define FILESTRING_MAXSIZE (FILESTRING_MAXLEN+1) 


int FExist(char *file);

int FSize(char *file);

int GetSaveFileName_Quick
(	
	int filename_size,
	char *filename,
	DWORD flags,
	char *filters,
	char *defExt,
	char *title
);

int ReadOpen
( 
	const char *filenamef
);

int WriteOpen
( 
	const char *filename,
	bool doOverwritePrompt
);

int WriteOpen
( 
	const char *filename
);

int GetFileDirectory(char *directory,char *file,int maxLen);

int QuickRead(void *buffer,const char *filename,int fileOffset,DWORD count);

int QuickWrite(void *buffer,const char *filename,int fileOffset,DWORD count);
int QuickWrite
(	void *buffer,const char *filename,
	int fileOffset,DWORD count,
	bool doOverwritePrompt
);

int ReadTextLine(int fHndl,char*buffer,int maxLen);

int ReadTextLines(int fHndl,int numLines,char*buffer,int maxLen);

bool GetItemIdListFromPath(LPOLESTR path,ITEMIDLIST*&itemIdList);
bool GetItemIdListFromPath(char*path,ITEMIDLIST*&itemIdList);

#define FILENAME_SIZE 512
#define FILENAME_WCHARS (FILENAME_SIZE/sz(short))

typedef struct FILENAME
{
	union
	{
		char name[FILENAME_SIZE]; 
		short wcName[FILENAME_WCHARS]; 
	};
	int __cdecl Scan
	(
		const char *format,
		...
	);
	int __cdecl Format
	(
		const char *format,
		...
	);
	FILENAME Make_DlgGetFileName_Filter(char*desc,char*mask);
	FILENAME Make_DlgGetFileName_Filter(FILENAME,FILENAME);
	ToWideChar();
	FromWideChar();
	bool IsSlashChar(short ch);
	int BrowseForDirectory(char*startPath);
	char operator [](int index);
	struct FILENAME operator =(char*s);
	struct FILENAME operator =(const char*s);
	WORD operator!();// get length
	char*operator~();// get string
	struct FILENAME operator--();//down one directory
	struct FILENAME operator-();//get directory of file
	struct FILENAME operator+();//get file w/o directory
	struct FILENAME operator++();//set to file w/o directory
	struct FILENAME operator>>(FILENAME&fd);//move into subdirectory or file
	struct FILENAME operator>>(char*fd);//move into subdirectory or file
	//struct FILENAME operator<<();
	bool operator==(FILENAME f2);
	bool operator==(char*f2);
}
FILENAME;

FILENAME operator &(FILENAME&fn1,char*s);
FILENAME operator &(FILENAME&fn1,FILENAME&fn2);
FILENAME operator &=(FILENAME&fn1,char*s);
FILENAME operator &=(FILENAME&fn1,FILENAME&fn2);

int BrowseForDirectory(FILENAME&retPath,char*startPath);

int GetSaveFileName_SuperQuick
(	
	FILENAME&filename,
	char*defExt
);

/*
void CSv6ObjExtractDlg::OnButtonExtractdir() 
{
	// TODO: Add your control notification handler code here



	char 
		retPath[MAX_PATH_2],
		retName[MAX_PATH_2];

	typedef ITEMIDLIST 
		ITEMIDLIST_ARRAY[20];

	//ITEMIDLIST 
	//	itemIDlist;
	union 
	{
		ITEMIDLIST_ARRAY *retItemIDlistArray;
		ITEMIDLIST *retItemIDlist;
	};

	BROWSEINFO 
		browseInfo=
		{
			NULL,
			NULL,
			retName,
			"Choose Directory",
			BIF_EDITBOX,

			NULL,
			0,
			0
		};

	browseInfo.pidlRoot=
		NULL;

	retItemIDlist=SHBrowseForFolder(&browseInfo);

	SHGetPathFromIDList
	(
		retItemIDlist,
		retPath
	);


	UpdateData(DDX_GET);
	m_extractDir=retPath;
	UpdateData(DDX_SET);

}
*/



#endif //_FILEIO2_H_
