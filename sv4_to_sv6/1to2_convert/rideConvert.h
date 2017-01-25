#ifndef RIDECONVERT_H
#define RIDECONVERT_H

#include<stdtypes.h>
#include "../rct2/sv6/SV6_RIDES.H"
#include "../rct1/sv4/SV4_RIDES.H"

ConvertRides
(	
	RCT2_RIDESTRUCTARRAY *s6_rides,SV4_RIDESTRUCTARRAY *s4_rides,
	WORD *s6_numRideStructsUsed,WORD s4_numRideStructsUsed
);





#endif //RIDECONVERT_H
