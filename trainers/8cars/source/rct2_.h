#ifndef _RCT2_
#define _RCT2_

//#include <objdat.h>
//#include <windows.h>
#include <stdtypes.h>

#define HIGHFTL 64
#define HIGHFULLFILE 128
#define HIGHFULLREGKEY 256
#define HIGHKEYNAMELENGTH 32
#define HIGHDELIMS 2

#define RCT2REGKEYNAME "Software\\Infogrames"\
	"\\RollerCoaster Tycoon 2 Setup"
#define RCT2REGVALUENAME "Path"

int GetRct2Path(BYTE *path);

#endif //_RCT2_

