#include"../StdAfx.h"
#include "../RCT2Landmark_LScenDlg.h"

#include"Parse_Input.h"
#include<codeshortcuts.h>
//#define SUPER_STRING__C_STRING
#include<superString.h>
//_chdir
#include<direct.h>
#include<stdlib2.h>
#include<BMPLib.h>
#include<malloc.h>

#include"..\bitmap\bitmap_compile.h"

#define f inputFile
#define oh obj.objHeader.typLScen
#define ofh \
	obj.objFileHeader
#define tp obj.optional.largeScenery.tilePos
#define boolStr(a) (a?sOn:sOff)
#define id obj.imageDirectory
#define LINE_MAXLEN 0x1000
#define SECTION_NAME__MAX_LEN 0x40

enum
{
	COMPILE__NO_PROBLEM=0,
	COMPILE__MISMATCHED_IMG_SIZES=1,
	COMPILE__MENU_IMAGE_NO_EXIST=2,
};

static langs[]=
{
	LNG_UKENGLISH,
	LNG_USENGLISH,
	LNG_FRENCH	,
	LNG_DEUTCSH	,
	LNG_SPANISH	,
	LNG_ITALIAN	,
	LNG_DUTCH	,
	LNG_SVERIGE	,
	LNG_KOREAN	,
	LNG_CHINESE1,
	LNG_CHINESE2,
	LNG_PORTUGESE
};

#define NUM_USED_LANGS \
	(sz(langs)/sz(langs[0])) 

bool StrToBool(char*s)
{
	static
	char 
		trueStrs[3][8]=
		{	"on",
			"true",
			"yes"
		},
		falseStrs[3][8]=
		{	"off",
			"false",
			"no"
		};
	int i;

	for_i0(i,3)
	{
		if(stricmp(s,trueStrs[i])==0)
		{
			return true;
		}
		else if(stricmp(s,falseStrs[i])==0)
		{
			return false;
		}		
	}
	return true;
}


Parse_Input__GetStatement(FILE*f,SUPER_STRING&s,char endChar)
{
	char c;
	bool eoff=false;
	//char commentLine[SECTION_NAME__MAX_LEN];

	s="";


	while(!feof(f))
	{
		c=fgetc(f);
		eoff=feof(f);
		if((c=='-')&&(!eoff))
		{
			c=fgetc(f);
			if((c=='-')&&(!feof(f)))//double hyphen "--"
			{
				fscanf
				(	f,"%*[^\r\n] "
					//,commentLine
				);		
			}
			else
			{
				s+='-';
				s+=c;								
			}
		}
		else if((c=='[')&&(!eoff))//section label -- skip
		{
			fscanf(	f," %*s ] ");	
		}
		else if((c==endChar)||eoff)
		{
			if(c==endChar)
			{
				fscanf(f," ");
			}
			break;
		}
		else
		{
			s+=c;
		}
	}
}


bool Parse_Input__GotoSection(FILE*f,char*section)
{
	char sectionName[LINE_MAXLEN];
	SUPER_STRING ssSectionName;
	char c;
	bool eoff;

	
	
	rewind(f);

	while(eoff=!feof(f))
	{
		c=fgetc(f);
		if(c=='[')
		{
			fseek(f,-1,SEEK_CUR);

			fscanf(f," [ %[a-zA-Z_0-9] ] ",sectionName);

			ssSectionName=sectionName;
			if(ssSectionName==section)
			{
				break;				
			}
			else if(ssSectionName==section)
			{
				fseek(f,0,SEEK_END);
			}
		}		
	}	
	return(eoff);
}

Parse_Input__InfoHeader
(	FILE*inputFile,OBJDAT_FILE&obj,
	FILENAME&datFileName
)
{
	char tmpName[9];
	char tmpNameTrim[9];
	char boolVals[2][8];
	WORD numCols,numRows;

	FILENAME newDatFileName;

	union
	{	WORD wordV;BYTE byteV;DWORD dwordV;short shortV;
		char charV,charVals[4];
	};
	SUPER_STRING curStatement;
	SUPER_STRING&cs=curStatement;

	#define ofh obj.objFileHeader
	#define oh obj.objHeader.typLScen

	ofh.flags=0;

	ofh.flagNibbles[0].lo=PROD_CUSTOM;
	ofh.flagNibbles[0].lo=OT_LARGESCENERY;
	ofh.flagBytes[3]=0;

	Parse_Input__GetStatement(f,cs,';');
	{
		sscanf((char*)~cs," \"%8[a-zA-Z_0-9]\" ",tmpName);
		memset(ofh.filename,' ',sz(ofh.filename));
		sscanf(tmpName,"%8c",ofh.filename);

		newDatFileName=~datFileName;

		sscanf(tmpName," %s ",tmpNameTrim);

		--newDatFileName;
		newDatFileName>>tmpNameTrim;
		newDatFileName&=".dat";
		datFileName=~newDatFileName;
	}
	Parse_Input__GetStatement(f,cs,';');
	{
		sscanf((char*)~cs," { %hu , %hu } ",&numCols,&numRows);
		obj.numCols=numCols;
		obj.numRows=numRows;
	}
	Parse_Input__GetStatement(f,cs,';');
	{
		sscanf
		(	(char*)~cs," { %7[a-zA-Z] , %7[a-zA-Z] } ",
			boolVals[0],
			boolVals[1]
		);

		if(StrToBool(boolVals[0]))
			obj.objHeader.typLScen.flags|=T2_REMAP_1;
		else
			obj.objHeader.typLScen.flags&=BYTE(~T2_REMAP_1);
		if(StrToBool(boolVals[1]))
			obj.objHeader.typLScen.flags|=T2_REMAP_2;
		else
			obj.objHeader.typLScen.flags&=BYTE(~T2_REMAP_2);
	}
	Parse_Input__GetStatement(f,cs,';');
	{
		#if 0 
			sscanf
			(	(char*)~cs," %7[a-zA-Z] ",
				enumStr
			);
			oh.CursorSel=GetCursorEnum(enumStr);
		#else
			sscanf
			(	(char*)~cs," %hu ",
				&wordV
			);
			oh.CursorSel=wordV;				
		#endif 
	}
	Parse_Input__GetStatement(f,cs,';');
	{
		sscanf
		(	(char*)~cs," %hd ",
			&shortV
		);
		oh.BuildFee=shortV;
	}
	Parse_Input__GetStatement(f,cs,';');
	{
		sscanf
		(	(char*)~cs," %hd ",
			&shortV
		);
		oh.RemoveFee=shortV;
	}
	Parse_Input__GetStatement(f,cs,';');
	{
		sscanf
		(	(char*)~cs," %7[a-zA-Z] ",
			boolVals[0]
		);

		if(StrToBool(boolVals[0]))
			obj.objHeader.typLScen.flags|=T2_PHOTOGENIC;
		else
			obj.objHeader.typLScen.flags&=BYTE(~T2_PHOTOGENIC);
	}

	#undef ofh
	#undef oh



}



Parse_Input__Names(FILE*f,OBJDAT_FILE&obj)
{
	char tmpName[9];
	char boolVals[2][8];
	WORD numCols,numRows;
	union
	{	WORD wordV;BYTE byteV;DWORD dwordV;short shortV;
		char charV,charVals[4];
	};
	int i,j;

	SUPER_STRING curStatement;
	SUPER_STRING&cs=curStatement;

	#define ofh obj.objFileHeader
	#define oh obj.objHeader.typLScen
	#define ste obj.stringTable[0].entries
	
	for_i0(i,NUM_USED_LANGS)
	{
		Parse_Input__GetStatement(f,cs,';');
		{
			ste[i].lang=
				langs[i];
			sscanf((char*)~cs," \"%[^\"]\" ",ste[i].text);
			cs=ste[i].text;
			if(cs=="#copy_UK#")
			{
				cs=ste[0].text;
				for_i0(j,NUM_USED_LANGS)
				{
					ste[j].lang=langs[j];

					strcpy((char*)ste[j].text,(char*)~cs);
					
				}	
				goto exitLangLoop;
			}
		}
	}
	exitLangLoop:
	ste[NUM_USED_LANGS].lang=BYTE(0xff);

	#undef ste
	#undef ofh
	#undef oh
}

Parse_Input__Pos(FILE*f,OBJDAT_FILE&obj)
{
	char tmpName[9];
	char boolVals[2][8];
	//WORD numTiles;
	union
	{	WORD wordV;BYTE byteV;DWORD dwordV;short shortV;
		char charV,string16v[16];
		long longV;

	};
	int i;
	DWORD p,q;
	char retDelim;

	SUPER_STRING curStatement,&cs=curStatement;
	SUPER_STRING curLine,&l=curLine;
	SUPER_STRING curToken,&ct=curToken;
	
	#define ofh obj.objFileHeader
	#define oh obj.objHeader.typLScen
	#define ste obj.stringTable[0].entries
	#define doEndCheck \
		if(p>!cs) \
			goto ParseDone
	#define ctp \
		obj.optional.largeScenery.tilePos[i]
	#define cth \
		obj.lscen_tileHeights[i]
	#define scanPosToken_SNum(a,b,c)\
		ct=cs.GetToken(p,a,retDelim);\
		doEndCheck;\
		sscanf((char*)~ct," %ld ",&longV);\
		ctp.b=longV;\
		SkipTokenAndDelim(a,c)
	#define scanPosToken_SNum_B(a,b,c)\
		ct=cs.GetToken(p,a,retDelim);\
		doEndCheck;\
		sscanf((char*)~ct," %ld ",&longV);\
		b=longV;\
		SkipTokenAndDelim(a,c)
	#define scanPosToken_Bool(a,b,c)\
		ct=cs.GetToken(p,a,retDelim);\
		doEndCheck;\
		sscanf((char*)~ct," %5[a-zA-Z_] ",string16v);\
		ctp.b=StrToBool(string16v);\
		SkipTokenAndDelim(a,c)
	#define SkipTokenAndDelim(a,b)\
		if(cs[p]==b)\
			++p;\
		else\
		{\
			ct=cs.GetToken(p,a,retDelim);\
			if(retDelim==b)\
				++p;\
		}\
		doEndCheck

	obj.numTiles=obj.numCols*obj.numRows;
	if(obj.numTiles==0)
	{
		obj.numTiles=255;
	}

	Parse_Input__GetStatement(f,cs,';');
	{
		p=0;

		SkipTokenAndDelim("{",'{');

		for_i0(i,obj.numTiles)
		{
			//{0,0,0,8,on,{on,off,on,on},{on,on,on,on}};
			SkipTokenAndDelim("{",'{');
			
			scanPosToken_SNum(",",x,',');
			scanPosToken_SNum(",",y,',');
			scanPosToken_SNum(",",baseHeight,',');
			scanPosToken_SNum(",",clearanceHeight,',');
			if((ctp.y==-1)||(ctp.y==-1)) //eos
			{
				ctp.eosTest=WORD(0xffff);
				obj.numTiles=i;
				goto ParseDone;
			}
			ctp.x*=32;
			ctp.y*=32;
			ctp.clearanceHeight*=8;
			ctp.clearanceHeight=__min(ctp.clearanceHeight,BYTE(0xf8));

			scanPosToken_Bool(",",noSupports,',');
			ctp.noSupports=!ctp.noSupports;

			SkipTokenAndDelim("{",'{');

			scanPosToken_Bool(",",quad1,',');
			scanPosToken_Bool(",",quad2,',');
			scanPosToken_Bool(",",quad3,',');
			scanPosToken_Bool("}",quad4,'}');

			SkipTokenAndDelim("{",'{');

			scanPosToken_Bool(",",wall1,',');
			scanPosToken_Bool(",",wall2,',');
			scanPosToken_Bool(",",wall3,',');
			scanPosToken_Bool("}",wall4,'}');

			SkipTokenAndDelim(",",',');
			scanPosToken_SNum_B("}",cth,'}');
			if(cth==BYTE(0xff)){cth=ctp.clearanceHeight;}
			else{cth*=8;cth=__min(cth,BYTE(0xf8));}

			SkipTokenAndDelim(",",',');

		}
		i=obj.numTiles;
		ctp.eosTest=WORD(0xffff);
	}
	ParseDone:;

	#undef ctp
	#undef scanPosToken_SNum
	#undef scanPosToken_Bool
	#undef SkipTokenAndDelim
	#undef breakIfDone
	#undef ste
	#undef ofh
	#undef oh
}

enum
{
	HUE_GREY=0,
	HUE_GOLD,
	HUE_TAN,
	HUE_YELLOW,
	HUE_BRICKRED,
	HUE_PUKEGREEN,
	HUE_OLIVEGREEN,
	HUE_LIMEGREEN,
	HUE_PEACH,
	HUE_INDIGO,
	HUE_BLUE,
	HUE_SEAFOAMGREEN,
	HUE_PURPLE,
	HUE_RED,
	HUE_ORANGE,
	HUE_TEAL,
	HUE_PINK,
	HUE_REMAP2=HUE_PINK,
	HUE_RUSTBROWN,
	HUE_REMAP1,
	HUE__NUM_HUES,
};

const BYTE HUE__SPAN_SZ=12;

struct remapSpecStruct
{
	BYTE baseIndex;
	bool isUsed;
}
remaps[2][HUE__NUM_HUES]=
{
	{
		{10,false},
		{22,false},
		{34,false},
		{46,false},
		{58,false},
		{70,false},
		{82,false},
		{94,false},
		{106,false},
		{118,false},
		{130,false},
		{142,false},
		{154,false},
		{166,false},
		{178,false},
		{190,false},
		{202,false},
		{214,false},
		{243,false},
	},
	{
		{10,false},
		{22,false},
		{34,false},
		{46,false},
		{58,false},
		{70,false},
		{82,false},
		{94,false},
		{106,false},
		{118,false},
		{130,false},
		{142,false},
		{154,false},
		{166,false},
		{178,false},
		{190,false},
		{202,false},
		{214,false},
		{243,false},
	},
};

#if 1
ReadTileBmp_Remap
(	DWORD flags,
	IMG_256&curImg,
	remapSpecStruct*remaps1,
	remapSpecStruct*remaps2
)
{
	IMG_256&ci=curImg;

	int x,y,i,j;
	BYTE*p;

	for_i0(y,ci.h)
	{
	for_i0(x,ci.w)
	{
		p=&ci.pix(x,y);
		for_i0(i,HUE__NUM_HUES)
		{
			if(remaps1[i].isUsed||remaps2[i].isUsed)
			{
				if
				(	
					(flags&&T2_REMAP_1)
					&&
					remaps1[i].isUsed
					&&
					inrange
					(	*p,
						remaps1[i].baseIndex,
						remaps1[i].baseIndex+HUE__SPAN_SZ-1
					)
				)
				{
					*p-=remaps1[i].baseIndex;
					*p+=remaps1[HUE_REMAP1].baseIndex;
					goto ExitHueRound;				
				}
				else if
				(	
					(flags&&T2_REMAP_2)
					&&
					remaps2[i].isUsed
					&&
					inrange
					(	*p,
						remaps2[i].baseIndex,
						remaps2[i].baseIndex+HUE__SPAN_SZ-1
					)
				)
				{
					*p-=remaps2[i].baseIndex;
					*p+=remaps2[HUE_REMAP2].baseIndex;
					goto ExitHueRound;				
				}
			}
		}//for_i0(i,HUE__NUM_HUES)
		ExitHueRound:;
	}
	}
//inrange(int n,int l,int h);

}



ReadTileBmp
(	int imgI,
	OBJDAT_FILE&obj,
	short xofs,short yofs,
	remapSpecStruct*remaps1,
	remapSpecStruct*remaps2,
	FILENAME&curBmpPath
)
{
	union
	{
		IMG_256	curImg,ci;
	};
	union
	{
		BITMAP_256_HEADER bmpH,bh;
	};		
	BITMAPINFOHEADER&bmih=bmpH.bmiHeader;

	if(LoadBitmap_256(&bmpH,&ci.imgData,~curBmpPath))
	{
		ci.w=bmih.biSizeImage/bmih.biHeight;
		ci.h=bmih.biHeight;
		ci.Flip();

		ReadTileBmp_Remap
		(	obj.objHeader.typLScen.flags,
			ci,remaps1,remaps2
		);

		#if 1
		obj.AddImage(imgI,xofs,yofs,ci,IMG_IF_IMAGEDATA,0);
		#else
		obj.AddImage(imgI,xofs,yofs,ci,IMG_IF_IMAGEDATA_COMPACT,0);
		#endif
		ci.ImgFree();
	}
}
#endif



#define ofh obj.objFileHeader
#define oh obj.objHeader.typLScen
#define ste obj.stringTable[0].entries
#undef doEndCheck 
#define doEndCheck \
	if(0){} 
#define scanToken_SNum(a,b,c)\
	ct=cs.GetToken(p,a,retDelim);\
	doEndCheck;\
	sscanf((char*)~ct," %ld ",&longV);\
	b=longV;\
	SkipPast(c)
#define scanToken_Bool(a,b,c)\
	ct=cs.GetToken(p,a,retDelim);\
	doEndCheck;\
	sscanf((char*)~ct," %5[a-zA-Z_] ",string16v);\
	b=StrToBool(string16v);\
	SkipPast(c)
#define scanToken_Str(a,b,c)\
	ct=cs.GetToken(p,a,retDelim);\
	doEndCheck;\
	sscanf((char*)~ct," \"%[^\"]\" ",string256v);\
	b=string256v;\
	SkipPast(c)
#define SkipPast(a)\
	while(cs[p++]!=a)\
	{	if(p>!cs)\
			break;\
	}
#define scanStatement_Str(b)\
	sscanf((char*)~cs," \"%[^\"]\" ",string256v);\
	b=string256v
	


Parse_Input__Images__Remaps
(	FILE*f,OBJDAT_FILE&obj,
	WORD&seeThruColor,
	WORD&numRemaps
)
{
	numRemaps=HUE__NUM_HUES;

	short i,j;
	DWORD p;


	//WORD numTiles;
	union
	{	WORD wordV;BYTE byteV;DWORD dwordV;short shortV;
		char charV,
			string16v[16],
			string256v[256];
		long longV;

	};
	char retDelim;
	SUPER_STRING curStatement,&cs=curStatement;
	SUPER_STRING curLine,&l=curLine;
	SUPER_STRING curToken,&ct=curToken;
	FILENAME curBmpName,curBmpPath;

	for_i0(i,2)
	{
		Parse_Input__GetStatement(f,cs,'}');
		p=0;
		SkipPast('{');
		for_i0(j,numRemaps)
		{
			if(j<(numRemaps-1))
			{
				scanToken_Bool(",",remaps[i][j].isUsed,',');
			}
			else
			{
				scanToken_Bool("}",remaps[i][j].isUsed,'}');
			}
		}
		Parse_Input__GetStatement(f,cs,';');
	}
}

Parse_Input__Images_Tile
(	FILE*f,OBJDAT_FILE&obj,
	FILENAME&bmpDir
)
{
	//do code
	short xofs,yofs;
	WORD seeThruColor;

	char tmpName[9];
	char boolVals[2][8];
	//WORD numTiles;
	union
	{	WORD wordV;BYTE byteV;DWORD dwordV;short shortV;
		char charV,
			string16v[16],
			string256v[256];
		long longV;

	};
	int i,j;
	DWORD p,q,
		numImages;
	char retDelim;

	SUPER_STRING curStatement,&cs=curStatement;
	SUPER_STRING curLine,&l=curLine;
	SUPER_STRING curToken,&ct=curToken;
	FILENAME curBmpName,curBmpPath;

	WORD numRemaps;

	#if 1

	obj.ClearImages();

	i=0;
	obj.numTiles=obj.numCols*obj.numRows;
	if(obj.numTiles==0)
		obj.GetNumTiles();

	numImages=(obj.numTiles+1)*4;


	Parse_Input__GetStatement(f,cs,';');
	sscanf((char*)~cs," %ld ",&longV);
	seeThruColor=longV;


	Parse_Input__Images__Remaps
	(	
		f,
		obj,
		seeThruColor,
		numRemaps		
	);

	

	for_i0(i,numImages)
	{
		Parse_Input__GetStatement(f,cs,'}');
		{
			p=0;
			if(i==0)
				SkipPast('{');
			SkipPast('{');

			scanToken_SNum(",",xofs,',');
			scanToken_SNum(",",yofs,',');
			scanToken_Str("}",curBmpName,'}');
			
			DoReadBmp:
			{
				_chdir(~bmpDir);
				curBmpPath=curBmpName;
				#if 1
				ReadTileBmp
				(	i,
					obj,xofs,yofs,
					remaps[0],remaps[1],					
					curBmpPath				
				);
				#endif
			}

		}
		if(i<(numImages-1))
			Parse_Input__GetStatement(f,cs,',');
	}

	#endif
	
}

WORD 
Parse_Input__Images_Full
(	FILE*f,OBJDAT_FILE&obj,
	FILENAME&bmpDir
)
{
	WORD retVal=COMPILE__NO_PROBLEM;
	short xofs,yofs;
	WORD seeThruColor;
	

	char tmpName[9];
	char boolVals[2][8];
	//WORD numTiles;
	union
	{	WORD wordV;BYTE byteV;DWORD dwordV;short shortV;
		char charV,
			string16v[16],
			string256v[256];
		long longV;

	};
	int i,j;
	DWORD p,q,
		numImages;
	char retDelim;
	BITMAPINFOHEADER*bmih;

	SUPER_STRING curStatement,&cs=curStatement;
	SUPER_STRING curLine,&l=curLine;
	SUPER_STRING curToken,&ct=curToken;
	FILENAME curBmpName,bmpPaths[4],menuBmpPaths[4];

	WORD numRemaps=HUE__NUM_HUES;

	WORD view;
	BYTE
		*imgData[4],*menuImgs[4];
	WORD widths[4];
	WORD hgts[4];
	WORD maxHgt;
	WORD maxWdt;

	BITMAP_256_HEADER bmp[4],menuBmps[4];
	IMG_256 curImg;

	WORD menuWidths[4],menuHeights[4];

	bool sameSize;

	sameSize=true;

	maxHgt=maxWdt=0;

	for_i0(view,4)
	{
		imgData[view]=NULL;
	}


	Parse_Input__GetStatement(f,cs,';');
	sscanf((char*)~cs," %ld ",&longV);
	seeThruColor=longV;

	Parse_Input__Images__Remaps
	(	
		f,
		obj,
		seeThruColor,
		numRemaps		
	);

	_heapset(0);

	for_i0(view,4)
	{
		Parse_Input__GetStatement(f,cs,';');

		p=0;
		scanStatement_Str(curBmpName);

		menuBmpPaths[view]=bmpDir;
		menuBmpPaths[view]>>curBmpName;

		if(LoadBitmap_256(&menuBmps[view],&menuImgs[view],~menuBmpPaths[view]))
		{

			bmih=&(menuBmps[view].bmiHeader);

			menuHeights[view]=bmih->biHeight;
			menuWidths[view]=bmih->biSizeImage/bmih->biHeight;

		}
		else
		{
			return(COMPILE__MENU_IMAGE_NO_EXIST);
		}
	}

	for_i0(view,4)
	{
		Parse_Input__GetStatement(f,cs,';');

		p=0;
		scanStatement_Str(curBmpName);

		bmpPaths[view]=bmpDir;
		bmpPaths[view]>>curBmpName;

		LoadBitmap_256(&bmp[view],&imgData[view],~bmpPaths[view]);

		hgts[view]=bmp[view].bmiHeader.biHeight;
		widths[view]=
			bmp[view].bmiHeader.biSizeImage
			/bmp[view].bmiHeader.biHeight;

		
		if(view>0)
		{
			sameSize=
				(	
				sameSize
				&&
				(
				(hgts[view]==hgts[view-1])
				&&
				(widths[view]==widths[view-1])					
				)
				);

			maxWdt=__max(maxWdt,widths[view]);
			maxHgt=__max(maxHgt,hgts[view]);

			if(!sameSize)
			{
				retVal=COMPILE__MISMATCHED_IMG_SIZES;
				goto skipCompileFullViews;
			}

		}
	}

	for_i0(view,4)
	{
		curImg.Set
		(	maxWdt,maxHgt,
			imgData[view]
		);				

		ReadTileBmp_Remap
		(	obj.objHeader.typLScen.flags,
			curImg,
			remaps[0],
			remaps[1]
		);

		curImg.Set
		(	menuWidths[view],menuHeights[view],
			menuImgs[view]
		);				

		ReadTileBmp_Remap
		(	obj.objHeader.typLScen.flags,
			curImg,
			remaps[0],
			remaps[1]
		);


	}

	#if 1
	Bitmap_Compile__ReadFullView
	(	maxWdt,maxHgt,menuWidths,menuHeights,
		menuImgs,imgData,obj,
		true,
		seeThruColor
	);
	#endif

	skipCompileFullViews:

	for_i0(view,4)
	{		
		if(menuImgs[view]!=NULL)
			free(menuImgs[view]);
		if(imgData[view]!=NULL)
			free(imgData[view]);
	}
	return retVal;
}

//#undef ctp
#undef scanToken_SNum
#undef scanToken_Bool
#undef scanToken_Str
#undef SkipPast
#undef breakIfDone
#undef ste
#undef ofh
#undef oh

enum
{
	SECTION__INFO_HEADER=0,
	SECTION_NAMES,
	SECTION_POS,
	SECTION_IMAGES,
	SECTION_END,
	NUM_SECTIONS
};


Parse_Input
(	FILE*inputFile,OBJDAT_FILE&obj,
	FILENAME&datFileName,
	FILENAME&rlpFileName,
	CRCT2Landmark_LScenDlg&dlg
)
{
	SUPER_STRING curLine,&cl=curLine;
	FILENAME bmpDir;
	WORD retVal;
	//char*tmpLineBuff=(char*)malloc(LINE_MAXLEN);

	FILENAME outDatFileName;

	bmpDir=rlpFileName;
	--bmpDir;

	outDatFileName=rlpFileName;
	outDatFileName;
	
	//fprintf(o,"\r\n[infoHeader]\r\n\r\n");

	dlg.AddOutputLine("Parsing\r\n");
	dlg.ProgressInit(0,NUM_SECTIONS,0,1);
	
	if(Parse_Input__GotoSection(f,"InfoHeader"))
	{
		dlg.AddOutputLine("Processing info header\r\n");
		Parse_Input__InfoHeader(f,obj,outDatFileName);
		datFileName=outDatFileName;
		dlg.DataSet();
	}
	dlg.Progress();

	if(Parse_Input__GotoSection(f,"Names"))
	{
		dlg.AddOutputLine("Processing names\r\n");
		Parse_Input__Names(f,obj);
	}
	dlg.Progress();

	if(Parse_Input__GotoSection(f,"pos"))
	{
		dlg.AddOutputLine("Processing positions\r\n");
		Parse_Input__Pos(f,obj);
	}
	dlg.Progress();

	if(Parse_Input__GotoSection(f,"Images_Full"))
	{
		//Parse_Input__Images_Full is incomplete
		dlg.AddOutputLine("Processing full images\r\n");
		retVal=Parse_Input__Images_Full(f,obj,bmpDir);

		switch(retVal)
		{
		case COMPILE__MISMATCHED_IMG_SIZES:
			dlg.AddOutputLine("\t* Error * Mismatched full-view image sizes\r\n");
		case COMPILE__MENU_IMAGE_NO_EXIST:
			dlg.AddOutputLine("\t* Error * One or menu images do not exist\r\n");
		}
	}
	else if(Parse_Input__GotoSection(f,"Images_Tile"))
	{
		//Parse_Input__Images_Tile is incomplete
		
		dlg.AddOutputLine("Processing tile images\r\n");
		Parse_Input__Images_Tile(f,obj,bmpDir);
		
	}
	else 
	{
		dlg.AddOutputLine("\t* Warning * No image area\r\n");
	}
	dlg.Progress();

	dlg.AddOutputLine("Through parsing\r\n");
	
	//free(tmpLineBuff);

	#if 1
	obj.SortLScenTiles();
	#endif
	dlg.Progress();


}


#undef PARSE_OUTPUT_IMAGE__DO_IMAGEDIRECTORY
#undef oh// obj.objHeader.typLScen
#undef o// outputFile
#undef tp
#undef boolStr
