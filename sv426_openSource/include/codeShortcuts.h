#pragma once

#define for_i0(i,count) \
	for((i)=0;i<(count);i++)
#define for_i_base(i,base,count) \
	for(i=base;i<((base)+(count));i++)
#define for_i_span_std(i,start,end)\
	for(i=start;i<=end;i++)
#define for_i_span(i,start,end,step) \
	for\
	(	(i)=(start);\
		(\
			((step)<0)\
				?((i)>=(end))\
				:((i)<=(end))\
		);\
		(i)+=(step)\
	)

#define MemClr(a) \
	memset(&(a),0,sz((a)))
#define MemClr_v(a,b) \
	memset(&(a),b,sz((a)))

#undef sz
#define sz(a) (sizeof(a))
