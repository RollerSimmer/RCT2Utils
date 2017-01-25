 /*
The "String Compression" technique is decoded as follows: read a byte - if it is FF then
copy the next byte to the output; otherwise, the lower three bits indicate the length (add 1)
of a string (already in the output data) to be copied. The upper five bits are then shifted
right (by 3) to become an offset to the beginning of the string to be copied. The shifted
value has thirtytwo subtracted from it to create the offset. For example, A5 would indicate
a string of 6 bytes to be copied; the string begins twelve bytes before the current position. 


value	description
FF		one byte
0-FE	bit		span	description
		0		3		length-1 of data to copy
		3		5		offset+32 of string to be copied
*/

#include <string.h>
#include <io.h>
#include <FCNTL.H>
#include <share.h>
#include <errno.h>
#include <direct.h>
#include <stdlib.h> 
#include <fileio2.h>

#include "rctFuncs.h"
//#include <stdlib2.h>

#define HIGHFTL 64
#define HIGHFULLFILE 128
#define HIGHFULLREGKEY 256
#define HIGHKEYNAMELENGTH 32
#define HIGHDELIMS 2

#define RCTREGKEYNAME \
	"HKEY_LOCAL_MACHINE\\SOFTWARE\\FISH Technology Group\\RollerCoaster Tycoon Setup"
#define RCTREGVALUENAME "Path"

int GetRctPath(char *path)
{
	char *chp=RCTREGKEYNAME;
	HKEY  hkey;
	DWORD 
		size=HIGHFULLFILE,
		datatype=REG_SZ;

	if
	(	RegOpenKeyEx
		(	HKEY_LOCAL_MACHINE,RCTREGKEYNAME,0,
			KEY_QUERY_VALUE,&hkey
		)
		==ERROR_SUCCESS
	)
	{	if(RegQueryValueEx(hkey,RCTREGVALUENAME,NULL,&datatype,(BYTE*)path,&size))
			return FALSE;
		return TRUE;
	}
	else 
		return FALSE;
}

int BrowseRctFile(int accessType, char *retFilename, int fileType)
{
	int error;
	OPENFILENAME  ofn;
	char 
		filetitle[HIGHFTL]="",
		filename[HIGHFULLFILE]="",
		filepath[HIGHFULLFILE]="",
		title[64],
		*filter,
		*defExt;

	DWORD 
		flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_LONGNAMES;
	
	GetRctPath(filepath);
	
	switch(fileType)
	{
	case FT_SV4: 
		filter="RCT Park(*.sv4)\0*.sv4\0\0"; 
		defExt="SV4"; 
		strcat(filepath,"\\Saved Games");
		break;
	case FT_SC4: 
		filter="RCT Scenario(*.sc4)\0*.sc4\0\0"; 
		defExt="SC4"; 
		strcat(filepath,"\\Scenarios");
		break;
	default:
		return FALSE;
		break;
	}

	switch(accessType)
	{
	case FAT_LOAD:
		strcpy(title,"Select file");
	case FAT_SAVE:
		strcpy(title,"Select file");
	}

	if 
	(	
		GetSaveFileName_Quick
		(	
			HIGHFULLFILE,
			filename,
			flags,
			filter,
			defExt,
			title
		)
	) 
	{	
		strncpy(retFilename,filename,HIGHFULLFILE-1);
		return TRUE;
	}
	else 	
	{	error=CommDlgExtendedError();
		return FALSE;
	}

}

