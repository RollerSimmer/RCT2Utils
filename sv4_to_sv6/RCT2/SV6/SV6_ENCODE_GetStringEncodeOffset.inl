
char GetStringEncodeOffset
(
	BYTE*ibuf,
	BYTE*jbuf,
	long i,
	long j,
	BYTE*slength
)
{
	
	int a,b,c,d,workLength;
	char soffset,soffsets[0x20];
	BYTE slengthI,slengths[0x20],numMatches;

	int startI,endI;

	#define sl (*slength)

	d=j-i;

	numMatches=0;

	if((d>0)&&(d<=0x20))
	{
		workLength=__min(0x1f,d);

		for(a=0;a<workLength;a++)
		{
			b=0;
			if(ibuf[a]==jbuf[b])
			{
				soffsets[numMatches]=(i+a)-(j+b);
				
				for 
				(
					slengths[numMatches]=0;
					(a<d)
					&&(ibuf[a]==jbuf[b])
					&&(slengths[numMatches]<8);
					a++,
					b++					
				)
				{
					slengths[numMatches]++;
				}
				++numMatches;			
			}			
		}
	}
	
	soffset=0;
	sl=0;

	for(c=0;c<numMatches;c++)
	{
		if(slengths[c]>sl)
		{
			sl=slengths[c];
			soffset=soffsets[c];		
		}
	}

	if(soffset==0)
		sl=1;

	return soffset;

	#undef sl
	
}
