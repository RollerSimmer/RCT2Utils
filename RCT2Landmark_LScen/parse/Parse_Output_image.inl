
#include"Parse_Output_image_remap.inl"

#ifdef PARSE_SIMPLIFIED
#define iFl(a,b) fprintf(o,"\"%s%s.bmp\";\r\n",a,b,a,b)
#else
#define iFl(a,b) fprintf(o,"%s%s=\"%s%s.bmp\";\r\n",a,b,a,b)
#endif

#define FULL_VIEW_FILE__PREFIX "view"
#define MENU__PREFIX "menu"

fprintf(o,"-- menu images\r\n");

iFl(MENU__PREFIX,"SE");
iFl(MENU__PREFIX,"NE");
iFl(MENU__PREFIX,"NW");
iFl(MENU__PREFIX,"SW");

fprintf(o,"-- full views\r\n");

iFl(FULL_VIEW_FILE__PREFIX,"SE");
iFl(FULL_VIEW_FILE__PREFIX,"NE");
iFl(FULL_VIEW_FILE__PREFIX,"NW");
iFl(FULL_VIEW_FILE__PREFIX,"SW");
		
#undef iFl

fprintf(o,"\r\n[Images_Tile]\r\n\r\n");

#include"Parse_Output_image_remap.inl"

#define ti (i/4-1)
#define tRot (i%4)
#define tp obj.optional.largeScenery.tilePos[ti]

#ifdef PARSE_SIMPLIFIED
	#define fpf_head \
		if(useImgI)\
			fprintf(o,"-- Image #%d\r\n",i);\
		else if(useColRowRot&&(obj.objType==OT_LARGESCENERY))\
		{\
			if(i>=4)\
				fprintf\
				(	o,"-- Col=%d, Row=%d, Rotation=%d\r\n",\
					tp.x/32,tp.y/32,tRot\
				);\
			else\
				fprintf(o,"-- Menu, Rotation=%d\r\n",i);\
		}\
		else\
			fprintf(o,"-- Tile #%d, View %s\r\n",i/4,dir[i%4]);\
		fprintf\
		(\
			o,
#else 
	#define fpf_head \
		fprintf\
		(\
			o,
#endif


#define fpf_foot \
		,\
		id[i].xofs,\
		id[i].yofs,\
		~curBmpName\
	);

#ifdef PARSE_SIMPLIFIED
	#define OUTPUT__TILE_IMAGE__FORMAT \
		"{%hd,%hd,\"%s\"},\r\n"
#else
	#define OUTPUT__TILE_IMAGE__FORMAT \
		"{xOfs=%d,yOfs=%d,bitmapName=\"%s\"},\r\n"
#endif

#define fpf \
	fpf_head \
	OUTPUT__TILE_IMAGE__FORMAT \
	fpf_foot

#ifndef PARSE_SIMPLIFIED
fprintf(o,"tileImages=\r\n");
#else
fprintf(o,"-- tileImages: {xOfs,yOfs,bitmapName}\r\n");
#endif

fprintf(o,"{\r\n");

FILENAME curBmpName;

char dir[4][3]=
{
	"SW",
	"SE",
	"NE",
	"NW",
};

i=0;
while(i<obj.numImages)
{
	if(useImgI)
	{
		sprintf(~curBmpName,"img%04.4d",i+startImgI);
	}
	else if(useColRowRot&&(obj.objType==OT_LARGESCENERY))
	{
		if(i>=4)
			sprintf(~curBmpName,"%02.2d_%02.2d_%02.2d",tp.x/32,tp.y/32,tRot);
		else
			sprintf(~curBmpName,"menu_%02.2d",tRot);

	}
	else
	{
		sprintf(~curBmpName,"Tl%04.4d",i/4);
		curBmpName&=dir[i%4];
	}
	curBmpName&=".bmp";
	fpf;
	++i;
}

#undef tRot
#undef ti
#undef tp// optional

fprintf(o,"};\r\n");

#undef OUTPUT__TILE_IMAGE__FORMAT
#undef fpf_head 
#undef fpf_foot 
#undef fpf

#if(PARSE_OUTPUT_IMAGE__DO_IMAGEDIRECTORY)

fprintf(o,"\r\n[imgDir]\r\n\r\n");
fprintf(o,"-- Image directory dump, not used by compiler\r\n\r\n");

i=0;
while(i<obj.numImages)
{
	fprintf
	(
		o,
		"index=%d,"
		"startAddress=0x%X,"
		"xofs=%d,"
		"yofs=%d,"
		"width=%d,"
		"height=%d,"
		"unused=%d,"
		"flags=%d"
		"\r\n",

		i,	
		id[i].startaddress,
		id[i].xofs,
		id[i].yofs,
		id[i].width,
		id[i].height,
		id[i].unused,
		id[i].flags
	);
	++i;
}

#endif
