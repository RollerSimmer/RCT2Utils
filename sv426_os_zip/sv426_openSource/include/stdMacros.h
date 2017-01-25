//#include <stdMacros.h>

#if !defined STDMACROS_H
#define STDMACROS_H

#define sz(a) sizeof(a)
#define EvenUp(a)\
	((a)&1?(a)+1:(a))
#define EvenDown(a)\
	((a)&1?(a)-1:(a))
#define RoundUp(n,base)\
	(((n)+((base)-1))/(base)*(base))
#define RoundDown(n,base)\
	((n)/(base)*(base))

#define DDX_GET true
#define DDX_SET false

#endif //!defined STDMACROS_H

