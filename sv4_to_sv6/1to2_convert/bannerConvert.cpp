#include "bannerConvert.h"

#include <codeshortcuts.h>
#include <string.h>

ConvertBanners
(	
	BANNERINFOSTRUCT *s6_bannerInfo,BANNERINFOSTRUCT *s4_bannerInfo		
)
{

	int bI;

	#define NUMBANNERS_SV4 100
	#define NUMBANNERS_SV6 250

	#define sz(a) (sizeof(a))
	#define mm(a,b) (memmove(&(a),&(b),sz((a))))	
	#define ms0(a) (memset(&(a),0,sz(a)))
	#define ms0sz(a,b) (memset(&(a),0,(b)))
	DoConvertBanners:
	{
		memmove
		(	
			s6_bannerInfo,s4_bannerInfo,
			sz(BANNERINFOSTRUCT)*NUMBANNERS_SV4
		);

		for_i
		(	
			bI,NUMBANNERS_SV4,
			(NUMBANNERS_SV6-1),1
		)
		{
			ms0(s6_bannerInfo[bI]);
			s6_bannerInfo[bI].bannerStyle=BANSTYL_UNUSED;
		}
	}
	#undef sz
	#undef mm
	#undef ms0
	#undef ms0sz
}
