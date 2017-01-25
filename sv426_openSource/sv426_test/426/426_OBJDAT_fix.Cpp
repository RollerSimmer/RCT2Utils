#include <windows.h>
#include "SV6_OBJDAT_fix.h"
#include "../../funcs/rct2funcs.h"
#include <FileIO2.h>
#include <stdlib2.h>

/*
	128 entries for the rides
	252 entries for the small scenery
	128 entries for the large scenery
	128 entries for the walls
	32 entries for the banners
	16 entries for the paths
	15 entries for the path bits
	19 entries for the scenery sets
	1 entry for the park entrance
	1 entry for the water
	1 entry for the "stex" dat file to use
*/

/*

typedef struct
{
	SV6_OBJDAT_HEADER 
		rides[SV6_OBJDAT_NUMENTRIES_RIDES],
		smallScenery[SV6_OBJDAT_NUMENTRIES_SMALLSCENERY],
		largeScenery[SV6_OBJDAT_NUMENTRIES_LARGESCENERY],
		walls[SV6_OBJDAT_NUMENTRIES_WALLS],
		banners[SV6_OBJDAT_NUMENTRIES_BANNERS],
		paths[SV6_OBJDAT_NUMENTRIES_PATHS],
 		pathUtilities[SV6_OBJDAT_NUMENTRIES_PATHUTILITIES],
		groups[SV6_OBJDAT_NUMENTRIES_GROUPS],
		entrance[SV6_OBJDAT_NUMENTRIES_ENTRANCE],
		palette[SV6_OBJDAT_NUMENTRIES_PALETTE],
		scenarioText[SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT];
} SV6_OBJDAT_HEADER_BLOCK;
*/

/*

#define SV6_OBJDAT_NUMENTRIES_RIDES 128
#define SV6_OBJDAT_NUMENTRIES_SMALLSCENERY 252 
#define SV6_OBJDAT_NUMENTRIES_LARGESCENERY 128 
#define SV6_OBJDAT_NUMENTRIES_WALLS 128 
#define SV6_OBJDAT_NUMENTRIES_BANNERS 32 
#define SV6_OBJDAT_NUMENTRIES_PATHS 16
#define SV6_OBJDAT_NUMENTRIES_PATHUTILITIES 15
#define SV6_OBJDAT_NUMENTRIES_GROUPS 19  
#define SV6_OBJDAT_NUMENTRIES_ENTRANCE 1 
#define SV6_OBJDAT_NUMENTRIES_PALETTE 1
#define SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT 1 

*/

#define DATEXT ".DAT"
#define DATHEADER_FILEOFFSET 0

#define RCT2_DWORD_EMPTY ((DWORD)(0xFFFFFFFF))

FixObjects(SV6_OBJDAT_HEADER_BLOCK*sv6ObjBlock)
{
	//Init object table based off datnames
	int 
		i,j,fh,bytesRead;
	DWORD 
		curFlags,
		var_RCT2_DWORD_EMPTY;
		
	char 
		path[FILESTRING_MAXSIZE],
		curFilename[FILESTRING_MAXSIZE],
		curDatName[16],
		curDatName_inStruct[16],
		aStr[32];

	SV6_OBJDAT_HEADER_BLOCK_ALT 
		*sv6ObjBlockAlt=(SV6_OBJDAT_HEADER_BLOCK_ALT*)sv6ObjBlock;

	GetRct2Path(path);
	strcat(path,"\\ObjData\\");

	#define curObj (sv6ObjBlockAlt->objs[i])
	#define curTblEntry (objStrTable[i])
	#define sz(a) sizeof(a)
	#define ms0(a) (memset(&(a),0,sz(a)))

	j=SV6_OBJDAT_NUMENTRIES_ALL;

	for(i=0;i<SV6_OBJDAT_NUMENTRIES_ALL;i++)
	{
		curFlags=curObj.flags;
		var_RCT2_DWORD_EMPTY=RCT2_DWORD_EMPTY;
		if(curObj.flags!=RCT2_DWORD_EMPTY)
		{
			ms0(curDatName_inStruct);

			memcpy
			(	
				curDatName_inStruct,
				curObj.filename,
				sz(curObj.filename)
			);
			trim_spec(curDatName,curDatName_inStruct," \t\xA0");

			//strcpy(curDatName,curTblEntry.objName);
			strcat(curDatName,DATEXT);
			strcpy(curFilename,path);
			strcat(curFilename,curDatName);

			
			if(FExist(curFilename))
			{
				bytesRead=
				QuickRead
				(	&curObj,curFilename,DATHEADER_FILEOFFSET,sizeof(curObj)
				);
			}
		}
		else 
		{
			i=i+0;



		}
	}

	#undef ms0
	#undef sz
	#undef curObj //(RCT1emulationTableAlt->objs[i])
	#undef curTblEntry //(objStrTable[i])

}
