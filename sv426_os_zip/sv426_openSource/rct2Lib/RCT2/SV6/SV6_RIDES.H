//SV6_RIDES_H

#ifndef SV6_RIDES_H
#define SV6_RIDES_H

#include <rct_svx.h>


#define RSF_BROKENDOWN	(1<<7)

#ifndef RIDEINSPECTIONFREQUENCY_DEFINED

#ifndef _RCT2_

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

#endif// _RCT2_


#define RIDEINSPECTIONFREQUENCY_DEFINED
#endif


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

		setAfterBreakdown :1,
		unk09 :1,
		crashed :1,
		unk11 :1,
		everBeenOpened :1,
		playMusic :1,
		ridePreserved :1,

		indestructibleTrackPiecesPresent :1,


		unk16 :1,
		unk17 :1,
		trackedRide :1,
		sixFlafsDesign :1,
		unk20 :1,
		unk21 :1,
		unk22 :1,
		unk23 :1;
} 
SV6_RIDESTATUSFLAGS;

typedef struct 
{
/*000 -- Track type*/
BYTE  trackType;
/*001 -- Object ID for vehicle/shop type*/
BYTE  vehiObjID;
/*002 -- ?*/
BYTE  unk0x002[2];
/*004 -- Operating Mode*/
BYTE  opmode;
/*005 -- Color Scheme */
BYTE  colorScheme;
/*006 -- Primary and Trim vehicle colors*/
struct{BYTE primary,trim;} vehicolors1[32];
/*046 -- Reserved for old RCT ride colors?  */
BYTE  unk0x046[3];
/*049 -- Ride Status*/
BYTE  ridestatus;
/*04A -- text string index. if MSB of this word is set, use lower 10 bits for user defined string index*/
SVX__STRING_NAME_OFFSET nameStringIndex;
/*04C -- string numerator*/
long  stringNumerator;
/*050 -- Map (X,Y) of focus tile for Overall View*/
RCTPOINT  overallViewFocus;
/*052 -- Array [4] of map (X,Y)'s of focus tile for stations*/
RCTPOINT  stationFoci[4];
/*05A -- station yheights (1 byte for each section)*/
BYTE  stationHeights[4];
/*05E -- station lengths*/
BYTE  stationLengths[4];
/*062 -- Station signal (one byte for each station) */
BYTE  stationSignal[4];
/*066 -- Train in loading position */
BYTE  trainsInLoadingPos[4];
/*06A -- Four sets of ride Entrance map location (row, col)*/
RCTPOINT rideEntrances[4];
/*072 -- Four sets of ride Exit map location (row, col)*/
RCTPOINT rideExits[4];
/*07A -- Four sprite indexes (2 bytes) of the last guest in the queue line at the respective station */
short  lastQueueGuestIndex[4];
/*082 -- ?*/
BYTE  unk0x082[4];
/*086 -- address of sprite data structure for each train. Set to FF for unavailable train numbers. */
WORD TrainSpriteIndexes[32];
/*0C6 -- DEPARTURE CONTROL FLAGS */
BYTE  DepartureControlFlags;
/*0c7 -- # of stations*/
BYTE  amtStations;
/*0C8 -- # of trains*/
BYTE  amtTrains;
/*0C9 -- # of cars per train*/
BYTE  amtCarsPerTrain;
/*0CA -- ?requested # of trains*/
BYTE  reqAmtTrains;
/*0CB -- ?requested # of cars per train*/
BYTE  reqAmtCarsPerTrain;
/*0CC -- max # of trains*/
BYTE  maxTrains;
/*0CD -- ?*/
BYTE  unk0x0CD[1];
/*0CE -- Minimum Wait Time */
BYTE  minWait;
/*0CF -- Maximum Wait Time */
BYTE  maxWait;
/*0D0 -- Launch speed, etc.*/
BYTE  launchSpeed;
/*0D1 -- ?*/
BYTE  unk0x0D1[3];
/*0D4 -- Index of Data Logging structure (FF if none) */
BYTE  dataLoggingIndex;
/*0D5 -- Special track elements:*/
BYTE  specialTrackElements;
/*0D6 -- ?*/
BYTE  unk0x0D6[2];
/*0D8 -- max speed lower word */
short  maxspeedLo;
/*0DA -- max speed upper word ~2.25 mph per bit */
short  maxspeedHi;
/*0DC -- avg speed lower word */
short  avgspeedLo;
/*0DE -- avg speed upper word ~2.25 mph per bit */
short  avgspeedHi;
/*0E0 -- ?*/
BYTE  unk0x0E0[4];
/*0E4 -- Ride lengths for each respective section*/
long  rideLengths[4];
/*0F4 -- Ride times for each respective section*/
short rideTimes[4];
/*0FC -- Max positive vertical G's (1 bit = 0.01--signed) */
short maxPosVertGs;
/*0FE -- Max negative vertical G's (1 bit = 0.01--signed) */
short maxNegVertGs;
/*100 -- Max lateral G's */
short maxLatGs;
/*102 -- ?*/
BYTE  unk0x102[18];
/*114 -- # of inversions (lower 5 bits)*/
BYTE  inversions;
/*115 -- # of drops (lower 6 bits)*/
BYTE  drops;
/*116 -- ?*/
BYTE  unk0x116[1];
/*117 -- Highest drop height (1 bit ~ 2.45 feet)*/
BYTE  highDrop;
/*118 -- ?*/
BYTE  unk0x118[8];
/*120 -- Count of customers to enter ride/shop in the current customer count timer interval; this value will be inserted into the data queue at the next timer reset--resets to 0 with the timer*/
short  curCustomerCount;
/*122 -- Customer count timer--resets at 1,000 -- see next and previous field*/
short  customerCountTimer;
/*124 -- Data queue of 10 WORDs representing*/
short  lastCustomerCounts[10];
/*138 -- Ticket price (1 bit = 10 cents)*/
short  ticketPrice;
/*13A -- ?*/
BYTE  unk0x13A[6];
/*140 -- Excitement rating (1 bit = 0.01) */
short excitement;
/*142 -- Intensity rating (1 bit = 0.01) */
short intensity;
/*144 -- Nausea rating (1 bit = 0.01) */
short nausea;
/*146 -- ?*/
BYTE  unk0x146[5];
/*14B -- Satisfaction (1 bit = 5%)*/
BYTE satisfaction;
/*14C -- ?*/
BYTE  unk0x14C[1];
/*14D -- ?some sort of flags relating to maintenance?*/
BYTE  unk_maintenanceRelatedFlag;
/*14E -- ?*/
BYTE  unk0x14E[2];
/*150 -- Total Customers*/
long totalCustomers;
/*154 -- Total profit (in dimes)*/
long totalProfit;
/*158 -- popularity (multiply by 4 for percent: (see next two fields)*/
BYTE popularityOutOf25;
/*159 -- counter which increases every time a guest thinks about ride*/
BYTE pop_TotalThoughtCountTo25;
/*15A -- how many positive (ie good) thoughts there are out of the count in 159; this value gets copied to the popularity rating when the above thought count reaches 25*/
BYTE pop_GoodThoughtCountOutOf25;
/*15B -- total guests currently on ride*/
BYTE numGuestsOnRide;
/*15C -- Music being played:*/
BYTE currentMusicPlaying;
/*15D -- ?*/
BYTE  unk0x15D[35];
/*180 -- Absolute month that ride was built in (used for ride age) */
short  absBuiltMonth;
/*182 -- Running cost (multiply by $1.60)*/
short  runningCost;
/*184 -- ?*/
BYTE  unk0x184[9];
/*18D -- mechanic status (if ride is broken down):*/
BYTE  mechanicStatus;
/*18E -- Sprite index of nearest mechanic or one fixing ride*/
WORD nearestHandman_spriteIndex;
/*190 -- ?*/
BYTE  unk0x190[3];
/*193 -- Break Down type:*/
BYTE  breakdownType;
/*194 -- ?*/
BYTE  unk0x194[2];
/*196 -- Reliabilty countdown (steps of 15. When this value resets, reliability decreases by 1*/
BYTE  reliabilityCountdown;
/*197 -- Reliability (bit=percent)*/
BYTE  reliability;
/*198 -- ?? Cheat detection*/
BYTE  unk_cheatDetection;
/*199 -- Downtime (bit=percent)*/
BYTE  downtime;
/*19A -- Inspection Frequency */
BYTE  inspectionFrequency;
/*19B -- Time Since Last Inspection*/
BYTE  timeSinceLastInspection;
/*19C -- Increments in steps of 1 during breakdown.  The value at 1AD seems to increment in one */
BYTE  unk_breakDownTimer;
/*19D -- ?*/
BYTE  unk0x19D[11];
/*1A8 -- On-ride photos sold*/
short  onRidePhotosSold;
/*1AA -- ?*/
BYTE  unk0x1AA[3];
/*1AD -- increments in steps of 2 during breakdown triggers "still hasn't been fixed "message" every time it reaches a multiple of 16 (0x10).*/
BYTE  unk_hasntBeenFixedTimer;
/*1AE -- ?*/
BYTE  unk0x1AE[10];
/*1B8 -- Queue time in minutes*/
BYTE  queuetime;
/*1B9 -- ?*/
BYTE  unk0x1B9[3];
/*1BC -- ride color schemes (spine, rail, supports)*/
BYTE  trackColorSchemes[4][3];
/*1C8 -- music selection:*/
BYTE rideMusic;
/*1C9 -- Station theming:*/
BYTE stationTheme;
/*1CA -- ?*/
BYTE  unk0x1CA[3];
/*1CD -- Lift hill chain speed */
BYTE  liftChainSpeed;
/*1CE -- Amount of guests for which this is their favorite ride*/
short  favRideGuestCount;
/*1D0 -- Ride Status Flags*/
SV6_RIDESTATUSFLAGS rideStatusFlags;
/*1D3 -- ?*/
BYTE  unk0x1D3[1];
/*1D4 -- Seat Colors (if used)*/
BYTE  seatColors[32];
/*1F4 -- ?*/
BYTE  unk0x1F4[3];
/*1F7 -- # of circuits*/
BYTE  numCircuits;
/*1F8 -- ?*/
BYTE  unk0x1F8[8];
/*200 -- # of guests in queue line at station <index> */
BYTE  guestsInQueue[4];
/*204 -- blank*/
BYTE  unk0x204[92];
} RCT2_RIDESTRUCT, RCT2_RIDESTRUCTARRAY[255];

#endif SV6_RIDES_H

