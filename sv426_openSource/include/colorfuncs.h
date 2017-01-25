#ifndef _COLORFUNCS_
#define _COLORFUNCS_
// HEADER 
#include <stdtypes.h>

typedef struct
{	BYTE red,green,blue;
} RGB;

typedef struct
{	BYTE hue,saturation,lightness;
} HSL;

WORD HueToRGB(WORD n1,WORD n2,WORD hue);
HSL RGBtoHSL(HSL *hsl,RGB *rgb);
RGB HSLtoRGB(RGB *rgb,HSL *hsl);

#define HSLMAX 255
#define RGBMAX 255

// /HEADER 
#endif // _COLORFUNCS_

