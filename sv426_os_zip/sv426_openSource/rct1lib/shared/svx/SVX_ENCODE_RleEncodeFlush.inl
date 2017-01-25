long RleEncodeFlush
(	
	BYTE rleType,
	BYTE *ebuf,
	long encdI,
	BYTE rleLength,
	BYTE*rleData
)
{
	if(rleType==REPEAT)
	{
		if(rleLength>1)
		{	ebuf[encdI++]=BYTE(1-rleLength);	}
		else if(rleLength==1)
		{	ebuf[encdI++]=0;	}
		ebuf[encdI++]=rleData[0];
	}
	else if(rleType==STREAM)
	{
		if(rleLength>0)
		{
			ebuf[encdI++]=BYTE(rleLength-1);
			memcpy(&ebuf[encdI],&rleData[0],rleLength);
			encdI+=rleLength;				
		}
	}
	return encdI;
}
