#ifndef MEM3_H
#define MEM3_H
#include<stdtypes.h>

MemMove_IncludeOnly
(	void*a,void*b,DWORD bufSize,
	bool includeOnly,WORD includeOnlyByre
);
MemMove_OverwriteOnly
(	void*a,void*b,DWORD bufSize,
	bool overwriteOnly,WORD overwriteOnlyByte
);
MemMove_OverwriteOnly_Exclude
(	void*a,void*b,DWORD bufSize,
	bool overwriteOnly,WORD overwriteOnlyByte,
	bool exclude,WORD excludeByte
);


#endif // MEM3_H

