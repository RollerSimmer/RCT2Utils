#ifndef SV6_ENCODE_H
#define SV6_ENCODE_H


#include "SV6_ENCODE_DECODE.h"

__declspec(dllexport) 
int EncodeSv6(int encodeType,SV6_FILE*sv6,char *outFileStream,int sv6CompressedSize);
__declspec(dllexport) 
SaveSv6(SV6_FILE*sv6,char *sv6FileName);

#endif //SV6_ENCODE_H
