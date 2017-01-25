#include "animationConvert.h"
#include <codeshortcuts.h>
#include <string.h>

ConvertAnimationObjects
(
	DWORD *s6_numAnimationObjects,DWORD s4_numAnimationObjects,
	ANIMATIONOBJECTLOCATION *s6_animationObjectLocations,
	ANIMATIONOBJECTLOCATION *s4_animationObjectLocations,
	short *s6_parkEntriesXpos,
	short *s6_parkEntriesYpos,
	short *s6_parkEntriesZpos,
	BYTE *s6_parkEntriesUsedFlag			
)
{
	#define MAXPARKENTRIES 4

	#define NUMANIMATIONS_SV6 2000
	#define NUMANIMATIONS_SV4 1000
	#define PE_USED 1

	short a6I,a4I,pe6I;

	#define sz(a) (sizeof(a))
	#define mm(a,b) (memmove(&(a),&(b),sz((a))))	
	#define ms0(a) (memset(&(a),0,sz(a)))
	#define ms0sz(a,b) (memset(&(a),0,(b)))
	DoConvertAnimations:
	{

		mm((*s6_numAnimationObjects),s4_numAnimationObjects);

		memset
		(	
			s6_animationObjectLocations,0,
			sz(*s6_animationObjectLocations)*NUMANIMATIONS_SV6			
		);

		memmove
		(	
			s6_animationObjectLocations,
			s4_animationObjectLocations,
			sz(ANIMATIONOBJECTLOCATION)//*s4_numAnimationObjects
		);

		pe6I=0;

		ms0sz(s6_parkEntriesUsedFlag[0],MAXPARKENTRIES*sz(s6_parkEntriesUsedFlag[0]));

		for_i0(a6I,NUMANIMATIONS_SV6)
		{
			switch(s6_animationObjectLocations[a6I].objectCode)
			{
			case ANIM_PARKENTRY:

				s6_parkEntriesXpos[pe6I]=s6_animationObjectLocations[a6I].x;
				s6_parkEntriesYpos[pe6I]=s6_animationObjectLocations[a6I].y;
				s6_parkEntriesZpos[pe6I]=s6_animationObjectLocations[a6I].height;
				s6_parkEntriesUsedFlag[pe6I]=PE_USED;
				
				pe6I++;
				if(pe6I>=MAXPARKENTRIES)
					goto ExitFor1;
				break;
			case ANIM_RIDEENTRANCE:
			case ANIM_EMPTY_FIRSTFREE:
			case ANIM_SCENERY:
			case ANIM_RAPIDSRIDE_WATERFALL:
			case ANIM_RAPIDSRIDE_RAPIDS:
			case ANIM_RAPIDS:
			case ANIM_RAPIDSRIDE_WHIRLPOOL:
			case ANIM_SPINNINGTUNNEL:
			case ANIM_GHOSTTRAIN_CARS_WINDOWS:
			case ANIM_BANNER:
			default:
				break;
			}

		}
		ExitFor1:
		;
	}
	#undef sz
	#undef mm
	#undef ms0
	#undef ms0sz
}

