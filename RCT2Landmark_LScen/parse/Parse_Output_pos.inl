if(objType==OT_LARGESCENERY)
{
#undef tp 
#define tp obj.optional.largeScenery.tilePos[i]

i=0;

#ifdef PARSE_SIMPLIFIED
#define TLLE_OUTPUT__FORMAT \
"{%d,%d,%d,"\
"%d,%s,"\
"{%s,%s,%s,%s},"\
"{%s,%s,%s,%s}"\
",%d"\
"},\r\n"

fprintf(o,"{\r\n");
fprintf(o,"-- {col,row,baseHeight,objClearance,hasSupports,quads,walls,ImgClearance}\r\n");

#else
#define TLLE_OUTPUT__FORMAT \
"{row=%d,col=%d,baseHeight=%d,"\
"clearance=%d,hasSupports=%s,"\
"quads={%s,%s,%s,%s},"\
"walls={%s,%s,%s,%s}"\
"};\r\n"

fprintf(o,"tiles=\r\n{\r\n");

#endif



while(tp.eosTest!=WORD(0xffff))
{
	#ifdef PARSE_SIMPLIFIED
		fprintf(o,"-- tile #%d\r\n",i);
	#endif

	fprintf
	(
		o,
		TLLE_OUTPUT__FORMAT,
		#define	TILE_POS__DIV_TO_UNITS
		#ifdef TILE_POS__DIV_TO_UNITS
		tp.x/32,
		tp.y/32,
		#else
		tp.x,
		tp.y,
		#endif
		tp.baseHeight,
		#ifdef TILE_POS__DIV_TO_UNITS
		tp.clearanceHeight/8,
		#else
		tp.clearanceHeight,
		#endif
		boolStr(!tp.noSupports),
		boolStr(tp.quad1),
		boolStr(tp.quad2),
		boolStr(tp.quad3),
		boolStr(tp.quad4),
		boolStr(tp.wall1),
		boolStr(tp.wall2),
		boolStr(tp.wall3),
		boolStr(tp.wall4),
		#ifdef TILE_POS__DIV_TO_UNITS
		tp.clearanceHeight/8
		#else
		tp.clearanceHeight
		#endif
	);

	++i;		
}

fprintf(o,"};\r\n");

#undef tp
}