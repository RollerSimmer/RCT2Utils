#include "spriteConvert.H"
#include <codeShortcuts.h>

#include <memory.h>
#include <string.h>

ConvertSprites
(	
	SV6_SPRITESTRUCTARRAY*sv6sprts,SV4_SPRITESTRUCTARRAY*sv4sprts,
	SPRITESTATS*sv6stats,SPRITESTATS*sv4stats
)
{

	WORD i,prevI;

	#define sz(a) (sizeof(a))
	#define RCT_WORD_EMPTY ((WORD)(0xFFFF))
	#define RCT_BYTE_EMPTY ((BYTE)(0xFF))

	memset(sv6sprts,0,sz(*sv6sprts));
	memmove(sv6sprts,sv4sprts,sz(*sv4sprts));
	memmove(sv6stats,sv4stats,sz(*sv4stats));


	#define freeCount \
		(sv6stats->statsA.availSprites)
	#define nextFree \
		(sv6stats->statsA.nextFreeSprite)

	#define s6 (*sv6sprts)
	#define s4 (*sv4sprts)
	CompleteChain:
	{
		i=nextFree;

		while (i!=RCT_WORD_EMPTY);
		{
			i=s6[i].nextInClass;
		}

		s6[i].nextInClass=SV4_NUMSPRITES;
		prevI=i;
		i=s6[i].nextInClass;

		while((i<SV6_NUMSPRITES)&&(i!=RCT_WORD_EMPTY))
		{
			s6[i].spriteID=RCT_BYTE_EMPTY;
			s6[i].prevInClass=prevI;
			s6[i].spriteIndex=i;			

			if((i+1)<SV6_NUMSPRITES)
			{							
				s6[i].nextInClass=i+1;
			}
			else
			{
				s6[i].nextInClass=RCT_WORD_EMPTY;
			}
			prevI=i;
			i=s6[i].nextInClass;
		}

		freeCount+=(SV6_NUMSPRITES-SV4_NUMSPRITES);
	}
	#undef s6
	#undef s4

	#undef freeCount
	#undef nextFree 

	#undef sz
}
