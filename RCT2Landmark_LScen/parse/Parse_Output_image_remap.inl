
#ifndef PARSE_SIMPLIFIED
fprintf(o,"transparentColor=");
#endif
fprintf(o,"0;\r\n");

#ifndef PARSE_SIMPLIFIED
fprintf(o,"remaps1=");
#else 
fprintf
(	o,
	"-- remap1 & remap2: {grey,grey,gold,tan,yellow,brickRed,pukeGreen,"
	"oliveGreen,limeGreen,peach,indigo,blue,seaFoamGreen,"
	"purple,red,orange,teal,pink,rustBrown,remap1}\r\n"
);
#endif
fprintf(o,"{off,off,off,off,off,off,off,off,off,off,off,off,off,off,off,off,off,off,on};\r\n");

#ifndef PARSE_SIMPLIFIED
fprintf(o,"remaps2=");
#endif
fprintf(o,"{off,off,off,off,off,off,off,off,off,off,off,off,off,off,off,off,on,off,off};\r\n");

