

//mem2.h
#if !defined MEM2_H
#define MEM2_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __cplusplus
	#define bool short
	#define false 0
	#define true 1
#endif


#include <stddef.h>

//#define NULL 0
//Compare characters in two buffers, ignoring mask character in 2nd buffer
int memxcmp(const void *buf1,const void *buf2,int useMask,char mask,size_t count);

//bool PointerInHeap(void*p);

#define _FREE_BLOCK		0
#define _NORMAL_BLOCK	1
#define _CRT_BLOCK		2
#define _IGNORE_BLOCK	3
#define _CLIENT_BLOCK	4
#define _MAX_BLOCKS		5

#define nNoMansLandSize 4

typedef struct MEMBLOCKHEADER
{
	struct MEMBLOCKHEADER * pBlockHeaderNext;
	struct MEMBLOCKHEADER * pBlockHeaderPrev;
	char *                      szFileName;
	int                         nLine;
	size_t                      nDataSize;
	int                         nBlockUse;
	long                        lRequest;
	unsigned char               gap[nNoMansLandSize];
	/* followed by:
	 *  unsigned char           data[nDataSize];
	 *  unsigned char           anotherGap[nNoMansLandSize];
	 */
} MEMBLOCKHEADER;

#define pHdr(pbData) (((MEMBLOCKHEADER*)pbData)-1)

#define _BLOCK_TYPE_IS_VALID(use) \
(\
	((use)==_NORMAL_BLOCK)\
	||((use)==_FREE_BLOCK)\
	||((use)==_CRT_BLOCK)\
	||((use)==_IGNORE_BLOCK)\
	||((use)==_CLIENT_BLOCK)\
	||((use)==_MAX_BLOCKS)\
)
#define _BLOCK_TYPE_IS_USED(use) \
(\
	((use)==_NORMAL_BLOCK)\
	||((use)==_CRT_BLOCK)\
	||((use)==_CLIENT_BLOCK)\
)

bool BlockInHeap(void*b);


#ifdef __cplusplus
}
#endif

#endif MEM2_H
