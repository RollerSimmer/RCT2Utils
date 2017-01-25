
DWORD numRows,numCols;


short minX,minY,maxX,maxY,i,curX,curY;


if(objType==OT_LARGESCENERY)
{
i=minX=maxX=minY=maxY=0;

while(tp[i].eosTest!=WORD(0xffff))
{
	minX=__min(minX,curX=tp[i].x);
	maxX=__max(maxX,curX);
	minY=__min(minY,curY=tp[i].y);
	maxY=__max(maxY,curY);
	++i;
}


numCols=abs(maxX-minX)/32+1;
numRows=abs(maxY-minY)/32+1;

}

char	sOn[4]="on";
char 	sOff[4]="off";


#ifdef PARSE_SIMPLIFIED
	fprintf(o,"-- datName\r\n");	
#else
	fprintf(o,"datName=");	
#endif

fprintf(o,"\"%8.8s\";\r\n",ofh.filename);

if(objType==OT_LARGESCENERY)
{
#ifdef PARSE_SIMPLIFIED
	fprintf(o,"-- tileDim\r\n{%hd,%hd};\r\n",numCols,numRows);
	fprintf(o,"-- remaps\r\n{");
	#define ln(a,b) \
		fprintf(o,"-- %s\r\n",a);\
		fprintf(o,"%d;\r\n",oh.b)
	#define lf(a,b) \
		fprintf(o,"-- %s\r\n",a);\
		fprintf(o,"%s;\r\n",(oh.flags&&b)?sOn:sOff)
#else
	fprintf(o,"tileDim={%hd,%hd};\r\n",numCols,numRows);
	fprintf(o,"remaps={");
	#define ln(a,b) \
		fprintf(o,"%s=%d;\r\n",a,oh.b)
	#define lf(a,b) \
		fprintf(o,"%s=%s;\r\n",a,(oh.flags&&b)?sOn:sOff)
#endif
}

fprintf(o,"%s,",((oh.flags&&T2_REMAP_1)?sOn:sOff));
fprintf(o,"%s};\r\n",((oh.flags&&T2_REMAP_2)?sOn:sOff));


ln("cursorSel",CursorSel);
ln("buildFee",BuildFee);
ln("removeFee",RemoveFee);
lf("landmark",T2_PHOTOGENIC);

#undef ln
#undef lf
