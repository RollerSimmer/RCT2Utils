//SV4_RIDES_H

#ifndef SV4_RIDES_H
#define SV4_RIDES_H
#include "../../shared/svx/svx.h"

#define RSF_BROKENDOWN	(1<<7)

#ifndef RIDEINSPECTIONFREQUENCY_DEFINED

typedef enum 
{	
	INSPECT_10MIN	=0,
	INSPECT_20MIN	=1,
	INSPECT_30MIN	=2,
	INSPECT_45MIN	=3,
	INSPECT_1HOUR	=4,
	INSPECT_2HOUR	=5,
	INSPECT_NEVER	=6
}	RIDEINSPECTIONFREQUENCY;

#define RIDEINSPECTIONFREQUENCY_DEFINED
#endif

#define RCT_NUMRIDES 255

typedef struct
{
	BYTE
		trainOnTrack :1,
		tested :1,
		testInProgress :1,
		dontShowRawStats :1,
		doStationPass :1,
		onRidePhoto :1,
		unk06 :1,
		brokenDown :1,
		unk08 :1,
		unk09 :1,
		crashed :1,
		unk11 :1,
		everBeenOpened :1,
		playMusic :1,
		ridePreserved :1,
		indestructibleTrackPiecesPresent :1;
}
SV4_RIDESTATUSFLAGS;

typedef struct 
{
	/*000 -- ride type (FF if not used)*/
	BYTE trackType;
	/*001 -- vehicle type*/
	BYTE vehiObjID;
	/*002 -- bit 0 = train(s) on track, bit 1 = tested; bit 2 = test in progress; bit 3 = don't show raw stats; bit 4 = pass through station without stopping; bit 5 = On-Ride photo; bit 6 = ?; bit 7 = broken down; bit 10 = crashed; bit 12 = ever been opened; bit 13 = play music; bit 14 = construction/demolition prohibited (indestructible ride); bit 15 = demolition prohibited (used when there are indestructible track pieces)*/
	SV4_RIDESTATUSFLAGS rideStatusFlags;
	/*004 -- operating mode*/
	BYTE opmode;
	/*005 -- color scheme (in original RCT code)*/
	BYTE colorScheme;
	/*006 -- body and trim colors*/
	struct{BYTE primary,trim;} vehicolors1[12];
	/*01E -- Track primary, secondary, and support colors (original RCT)*/
	BYTE  unk0x01E[3];
	/*021 -- ride status - 0 = closed, 1 = open, 2 = test*/
	BYTE ridestatus;
	/*022 -- text string index .if MSB of this word is set, use lower 10 bits for user defined string index*/
	WORD nameStringIndex;
	/*024 -- string numerator (all 4 bytes for guest #, two bytes for "rides been on" etc.) 026 is ride # if generic name used*/
	DWORD stringNumerator;
	/*028 -- Final station entry segment(row, col)*/
	RCTPOINT  overallViewFocus;
	/*02A -- four sets of row-col bytes for station departure segments*/
	RCTPOINT  stationFoci[4];
	/*032 -- Station height (one byte for each station)*/
	BYTE  stationHeights[4];
	/*036 -- Station length (one byte for each station)*/
	BYTE  stationLengths[4];
	/*03A -- Station signal (one byte for each station) [80 = green light, the lower nibble specifies if train moving through signal, waiting for departure control, track not clear, etc.]*/
	BYTE  stationSignal[4];
	/*03E -- train in loading position (FF = none) (4 stations)*/
	BYTE  trainsInLoadingPos[4];
	/*042 -- four sets of ride Entrance map location (row, col)*/
	RCTPOINT rideEntrances[4];
	/*04A -- four sets of ride Exit map location (row, col)*/
	RCTPOINT rideExits[4];
	/*052 -- index (2 bytes) of last peep in queue line at station (4 stations)*/
	short  lastQueueGuestIndex[4];
	/*05A -- Num of peeps in queue line (one byte for each station)*/
	BYTE guestsInQueue[4];
	/*05E -- address of sprite data structure for each train. Set to FF for unavailable train numbers.*/
	WORD  TrainSpriteIndexes[12];
	/*076 -- departure flags*/
	BYTE  DepartureControlFlags;
	/*077 -- # of stations*/
	BYTE  amtStations;
	/*078 -- # of trains*/
	BYTE  amtTrains;
	/*079 -- # of cars per train*/
	BYTE  amtCarsPerTrain;
	/*07A -- ?*/
	BYTE  unk0x07A[2];
	/*07C -- max # of trains for current # of cars*/
	BYTE  maxTrains;
	/*07D --  ?*/
	BYTE  unk0x07D[1];
	/*07E -- minimum wait time*/
	BYTE  minWait;
	/*07F -- maximum wait time*/
	BYTE  maxWait;
	/*080 -- speed of powered launch/laps/#peeps*/
	BYTE  launchSpeed;
	/*081 -- ?*/
	BYTE  unk0x081[3];
	/*084 -- index of Data Logging structure (FF if none)*/
	BYTE  dataLoggingIndex;
	/*085 -- special track elements: bits 0 through 4: number of helix sections; bit 5= spinning tunnel,water splash, rapids; bit 6= log reverser,waterfall; bit 7= whirlpool*/
	BYTE  specialTrackElements;
	/*086 -- ?*/
	BYTE  unk0x086[2];
	/*088 -- max speed lower word*/
	short  maxspeedLo;
	/*08A -- max speed upper word ~2.25 mph per bit*/
	short  maxspeedHi;
	/*08C -- avg speed lower word*/
	short  avgspeedLo;
	/*08E -- avg speed upper word ~2.25 mph per bit*/
	short  avgspeedHi;
	/*090 -- ?*/
	BYTE  unk0x090[4];
	/*094 -- ride length (1st section) - use upper word*/
	long  rideLengths[4];



	/*0A4 -- ride time (1st section)*/
	short rideTimes[4];



	/*0AC -- Maximum positive G force*/
	short maxPosVertGs;
	/*0AE -- Maximum negative G force*/
	short maxNegVertGs;
	/*0B0 -- Maximum lateral G force*/
	short maxLatGs;
	/*0B2 -- ?*/
	BYTE  unk0x0B2[12];
	/*0BE -- ?related to "curvature" of track*/
	WORD unk_curvatureRelated;
	/*0C0 -- ?*/
	BYTE  unk0x0C0[2];
	/*0C2 -- ?*/
	BYTE  unk0x0C2[2];
	/*0C4 --  num of inversions (lower 5 bits)*/
	BYTE  inversions;
	/*0C5 -- num of drops (lower six bits)*/
	BYTE  drops;
	/*0C6 -- ?*/
	BYTE  unk0x0C6[1];
	/*0C7 -- max drop height (in 1/3 meters ~ 1 ft)*/
	BYTE  highDrop;
	/*0C8 -- underground track length?*/
	long  unk_undergroundTrackLength;
	/*0CC -- ?*/
	BYTE  unk0x0CC[2];
	/*0CE -- ?*/
	BYTE  unk0x0CE[1];
	/*0CF -- ?*/
	BYTE  unk0x0CF[1];
	/*0D0 -- Count of customers to enter ride/shop in the current customer count timer interval*/
	short  curCustomerCount;
	/*0D2 -- Customer count timer--resets at 1*/
	short  customerCountTimer;
	/*0D4 -- last customer counts [10][2]*/
	short  lastCustomerCounts[10];
	/*0E8 -- ticket price*/
	short  ticketPrice;
	/*0EA -- ?*/
	BYTE  unk0x0EA[6];
	/*0F0 -- Excitement (divide by 100)*/
	short excitement;
	/*0F2 -- Intensity (divide by 100)*/
	short intensity;
	/*0F4 -- Nausea (divide by 100)*/
	short nausea;
	/*0F6 -- ?*/
	BYTE  unk0x0F6[4];
	/*0FA -- satisfaction (multiply by 5%) (-1 for unknown)*/
	BYTE  satisfaction;
	/*0FB -- ?*/
	BYTE  unk0x0FB[5];
	/*100 -- total customers*/
	long totalCustomers;
	/*104 -- total profit*/
	long totalProfit;
	/*108 -- popularity (multiply by 4)*/
	BYTE curPopularity;
	/*109 -- number of guests "thinking" about ride*/
	BYTE guestThoughtCount;
	/*10A -- how many positive (ie good) thoughts there are out of the count in 159 copied to the popularity rating when the above thought count reaches 25 */
	BYTE  guestGoodThoughtCount;
	/*10B -- #people on ride*/
	BYTE  numGuestsOnRide;
	/*10C -- ?*/
	BYTE  unk0x10C[36];
	/*130 -- Month of construction (used to determine ride age)*/
	short  absBuiltMonth;
	/*132 -- running cost (multiply by $1.60)*/
	short  runningCost;
	/*134 -- ?*/
	BYTE  unk0x134[15];
	/*143 -- Break Down type: -1=not broken, 0="safety cut-out", 1="restraints stuck closed", 2="restraints stuck open", 3="doors stuck closed", 4="doors stuck open", 5="vehicle malfunction", 6="station brakes failure", 7="control failure"*/
	BYTE breakdownType;
	/*144 -- ?*/
	BYTE  unk0x144[2];
	/*146 -- Reliability count down - when zero, Reliability is decremented*/
	BYTE reliabilityCountdown;
	/*147 -- Reliability (%)*/
	BYTE reliability;
	/*148 -- Cheat detection flag?*/
	BYTE fill148;
	/*149 -- down time (%)*/
	BYTE downtime;
	/*14A -- Inspection interval (0 = 10 min, 1 = 20 min, 2 = 30 min, 3 = 45 min, 4 = 1 hr, 5 = 2 hr, 6 = never) */
	BYTE inspectionFrequency;
	/*14B -- time since last inspection (minutes)*/
	BYTE timeSinceLastInspection;
	/*14C -- ?*/
	BYTE  unk0x14C[20];
	/*160 -- Income per hour*/
	long hourlyIncome;
	/*164 -- profit*/
	long profit;
	/*168 -- queue time*/
	BYTE queuetime;
	/*169 -- ?*/
	BYTE  unk0x169[3];
	/*16C -- track color schemes*/
	BYTE trackColorSchemes[4][3];
	/*178 -- music selection (00=Dodgems, 01=Fairground organ, 02=Roman Fanfare, 03=Oriental, 04=Martian, 05=Jungle Drums, 06=Egyptian, 07=Toyland, 08=?, 09=Space, 0A=Horror, 0B=Techno, 0C=Gentle, 0D=summer, 0E=water, 0F=Wild West, 10=Jurassic, 11=Rock, 12=Ragtime, 13=Fantasy*/
	BYTE rideMusic;
	/*179 -- station theming (00=standard, 01=wooden, 02=canvas tent, 03=castle[grey], 04=castle[brown], 05=jungle, 06=log cabin, 07=classical, 08=abstract, 09=snow, 0A=pagoda, 0B=space)*/
	BYTE stationTheme;
	/*17A -- blank*/
	BYTE unk0x17A[230];
} SV4_RIDESTRUCT, SV4_RIDESTRUCTARRAY[255];

#endif SV4_RIDES_H

