#ifndef ANIMATIONCONVERT_H
#define ANIMATIONCONVERT_H

#include<stdtypes.h>
#include "../rct2/sv6/SV6.H"

ConvertAnimationObjects
(
	DWORD *s6_numAnimationObjects,DWORD s4_numAnimationObjects,
	ANIMATIONOBJECTLOCATION *s6_animationObjectLocations,
	ANIMATIONOBJECTLOCATION *s4_animationObjectLocations,
	short *s6_parkEntriesXpos,
	short *s6_parkEntriesYpos,
	short *s6_parkEntriesZpos,
	BYTE *s6_parkEntriesUsedFlag			
);

#endif //ANIMATIONCONVERT_H
