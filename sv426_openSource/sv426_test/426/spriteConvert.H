#ifndef SPRITECONVERT_H
#define SPRITECONVERT_H

#include <stdtypes.h>

#include "../rct2/sv6/SV6_SPRITES.H"
#include "../rct1/sv4/SV4_SPRITES.H"

ConvertSprites
(	
	SV6_SPRITESTRUCTARRAY*sv6sprts,SV4_SPRITESTRUCTARRAY*sv4sprts,
	SPRITESTATS*sv6stats,SPRITESTATS*sv4stats
);


#endif //SPRITECONVERT_H
