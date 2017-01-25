typedef struct
{
/*0x000000 -- game time day, counts in steps of 4. when this 16 bit value cycles, a month will have passed.*/
SV4_TIMEDATA time;
/*0x000010 -- contains the game map. See the discussion below. The spatial dimensions used in the game are: one tile has 10 square meters of area; the height marks in the game are 4/3 meters (internal units are 1/3 meters).*/
SV4_PARKMAPDATABLOCK parkMap;
/*0x060010 -- an incrementing counter, two upper bits not used - not used as a trigger as far as I can tell*/
DWORD spriteTimer;
/*0x060014 -- sprite data structures. Each structure has 256 bytes. There are 5,000 sprite structures. Items stored in these structures include peeps (guest and staff) and ride vehicles. Ducks are also stored here. The vomit sprites are also stored here even though th*/
SV4_SPRITESTRUCTARRAY sprites;
/*0x198814 -- Sprite# of next sprite object to be added.*/
SPRITESTATS spriteStats;
/*0x19882C -- Offset of park name in name string array - only use the lower 10 bits (the MSB is set if there is a string entry).*/
SVX__STRING_NAME_OFFSET parkNameOffset;
/*0x19882E -- ?*/
BYTE unk0x19882E[6];
/*0x198834 -- Cash amount (divide by 10 for dollars etc.)*/
DWORD money;
/*0x198838 -- Loan amount (divide by 10 for dollars etc.)*/
DWORD loan;
/*0x19883C -- bit 0: Park status: 0 = closed, 1 = open; bit 2 set to prohibit land modification; bit 3 set to prohibit removing trees/scenery; bit 4 is set to "show real names"; bit 5 set to prohibit building above tree level; bit 6 set to indicate "low intensity peep*/
SV4_PARKSTATUS parkStatus;
/*0x198840 -- Park entry fee*/
WORD admissionFee;
/*0x198842 -- Park Entry Point #1: X (32 per tile)*/
MAINENTRANCE_LOCATIONSTRUCT mainParkEntry;
/*0x198849 -- ?*/
BYTE unk0x198849[1];
/*0x19884A -- Peep Entry Point #1: X (32 per tile)*/
ENTRYPOINTSTRUCT peepMapEntryPoints[2];
/*0x198856 -- ???*/
BYTE unk0x198856[1];
/*0x198857 -- Research rate: 0 = none, 1 = minimum, 2 = normal, 3 = maximum*/
BYTE researchRate;
/*0x198858 -- ???*/
BYTE unk0x198858[4];
/*0x19885C -- Rides Menu*/
BYTE ridesMenu[32];
/*0x19887C -- Vehicle Menu (similar to above ride menu - one bit for each vehicle)*/
BYTE vehicleMenu[32];
/*0x19889C -- Ride feature 1 table = 89 (decimal) structures of 4 bytes for each ride.*/
BYTE rideFeatureTable[2][128][4];
/*0x198C9C -- Number of guests in park*/
WORD numGuestsInPark;
/*0x198C9E -- ?*/
BYTE unk0x198C9E[2];
/*0x198CA0 -- budgetVals [14][8][4]*/
DWORD budgetVals[2][14][8];
/*0x199020 -- ?number of guests in park*/
DWORD unk_numGuestsInPark;
/*0x199024 -- ?*/
BYTE unk0x199024[1];
/*0x199025 -- color for handymen*/
BYTE handmanColor;
/*0x199026 -- color for mechanics*/
BYTE mechanicColor;
/*0x199027 -- color for security guards*/
BYTE securityColor;
/*0x199028 -- Scenery Menu*/
BYTE sceneryMenu[128];
/*0x1990A8 -- banner menu items: bit 0=standard, 1=jungle, 2=roman, 3=egyptian, 4=mining, 5=jurrasic, 6=asian,7=snow*/
BYTE bannerMenu[2];
/*0x1990AA -- ?*/
BYTE unk0x1990AA[94];
/*0x199108 -- current park rating*/
WORD curParkRating;
/*0x19910A -- historical park rating (for curve) the low byte is in 19910A through 199129 while the high byte is in 19912A through 199149. an FF indicates 'not used'*/
WORD histParkRating[32];
/*0x19914A -- Research selection: bit 0=Rollercoasters, bit 1 = Thrill rides, bit 2 = Gentle rides, bit 3 = Shops/stalls, bit 4 = Theming, bit 5 = Ride improvements*/
BYTE researchSelection;
/*0x19914B -- research progress description: 0=initial research, 1=designing, 2=completing*/
BYTE researchProgress;
/*0x19914C -- last development - research item*/
BYTE lastDevelopment_Item;
/*0x19914D -- last development - corresponding ride*/
BYTE lastDevelopment_ride;
/*0x19914E -- last development - research category*/
BYTE lastDevelopment_category;
/*0x19914F -- last development - flag*/
BYTE lastDevelopment_flag;
/*0x199150 -- Research items. up to 200 entries of 5 bytes each. Not used in LL (goto 199C9C for LL)*/
BYTE researchItems[1000];
/*0x199538 -- next development - research item*/
BYTE nextDevelopment_Item;
/*0x199539 -- next development - corresponding ride*/
BYTE nextDevelopment_ride;
/*0x19953A -- next development - research category*/
BYTE nextDevelopment_category;
/*0x19953B -- next development - flag*/
BYTE nextDevelopment_flag;
/*0x19953C -- ?*/
BYTE unk0x19953C[2];
/*0x19953E -- ?*/
BYTE unk0x19953E[4];
/*0x199542 -- Cheat detection: count of owned land*/
WORD cheat_ownedLandCount;
/*0x199544 -- ?*/
BYTE unk0x199544[2];
/*0x199546 -- ?*/
BYTE unk0x199546[2];
/*0x199548 -- Max loan amount (divide by 10 to get dollars, etc)*/
DWORD maxLoan;
/*0x19954C -- cash in pocket for new guests*/
WORD newGuest_cash;
/*0x19954E -- avg hunger of newly generated guests.*/
BYTE newGuest_thirst;
/*0x19954F -- avg thirst of newly generated guests.*/
BYTE newGuest_hunger;
/*0x199550 -- scenario goal: 1 = #peeps (& park rating), 2 = park value, 3 = have fun!, 4 = competition, 5 = ten different coasters with excitement at least 6.00, 6 = maintain park rating & #peeps, 7 = monthly ride income, 8 = ten different coasters with excitement a*/
BYTE scenarioGoal;
/*0x199551 -- number of years to reach goal (10 for competitions)*/
BYTE scenarioTimeLimit_inYears;
/*0x199552 -- ?*/
BYTE unk0x199552[2];
/*0x199554 -- money (park value/ride income) goal / coaster excitement goal (only for goal type 9)*/
DWORD scenarioGoal_dwordValue;
/*0x199558 -- #peeps goal / minimum coaster length (meters)*/
WORD scenarioGoal_wordValue;
/*0x19955A -- Advertising, 1 byte for each type, lower 4 bits indicate weeks remaining.*/
ADVERT_BYTE advertising[20];
/*0x19956E -- 1 Byte for each type of advertising, indicates the ride/food associated with the advertising that displays it.*/
BYTE advertisingItems[6];
/*0x199574 -- ?*/
BYTE unk0x199574[16];
/*0x199584 -- 128 DWords (previous cash values)*/
DWORD prevCashVals[128];
/*0x199784 -- Recent change in cash*/
DWORD recentCashChange;
/*0x199788 -- previous recent change in cash multiplied by 7(?)*/
DWORD recentCashChange_x7;
/*0x19978C -- sum of "recent changes in cash"*/
DWORD recentCashChanges_sum;
/*0x199790 -- ?*/
BYTE unk0x199790[2];
/*0x199792 -- ?*/
BYTE unk0x199792[2];
/*0x199794 -- 128 DWords: Weekly Profit over time*/
DWORD weeklyProfitHistory[128];
/*0x199994 -- Park value*/
DWORD parkValue;
/*0x199998 -- 128 DWords: Park Value over time*/
DWORD parkValueHistory[128];
/*0x199B98 -- scenario objective value at completion Note: MSB set to indicated objective not met; if bit 0 set - failed objective*/
DWORD scenarioObjectiveValAtCompletion;
/*0x199B9C -- number of admissions*/
DWORD totalAdmissions;
/*0x199BA0 -- income from admissions*/
DWORD admissionIncome;
/*0x199BA4 -- Company Value [cash + park value - loan]*/
DWORD companyValue;
/*0x199BA8 -- ?*/
BYTE unk0x199BA8[16];
/*0x199BB8 -- park awards - four structures of 4 bytes each. Each structure consists of two words. The first word is a flag to indicate if there is an award(zero=no, nonzero = yes); the second word indicates the award/string as follows: 0=most untidy, 1=tidiest, 2=bes*/
PARKAWARDSTRUCT parkAwards[4];
/*0x199BC8 -- Price for purchasing land (div by 10 for dollars)*/
WORD landPurchaseCost;
/*0x199BCA -- Price for buying Construction Rights (div by 10 for dollars)*/
WORD rightsPurchaseCost;
/*0x199BCC -- ?*/
BYTE unk0x199BCC[2];
/*0x199BCE -- ?*/
BYTE unk0x199BCE[2];
/*0x199BD0 -- contains 58 BB C3 00 if error detected????*/
DWORD ifError_contains0x00C3BB58;
/*0x199BD4 -- user name (null terminated string)*/
char userName[64];
/*0x199C14 -- Version number of game - convert to decimal: first digit is major version number; next two digits are minor version number; last three digits are revision number.*/
DWORD RCT2version;
/*0x199C18 -- company value at scenario completion*/
DWORD companyValue_atScenarioCompletion;
/*0x199C1C -- 1st financial checksum [ 70093A minus cash, ror 5, minus loan, ror 7, add maxloan, ror 3 ]*/
DWORD financialChecksum_1;
/*0x199C20 -- number of ride structures used*/
WORD numRideStructsUsed;
/*0x199C22 -- negative of number of rides available (for cheat detection)*/
WORD cheat_negNumRidesAvail;
/*0x199C24 -- max number of tiles(land) allowed to own (for cheat detection)*/
short cheat_maxOwnedTilesAllowed;
/*0x199C26 -- negative of max number of tiles allowed to own*/
short cheat_maxOwnedTilesAllowed_neg;
/*0x199C28 -- 3rd financial checksum: [cash - loan - all values in monthly expense/income table.]*/
DWORD financialChecksum_3_unused;
/*0x199C2C -- Scenario Slot Number Checksum*/
DWORD checksum_scenarioSlotNumber;
/*0x199C30 -- Name of winner; if not won or unknown, the character '?' is used*/
char winnerName[32];
/*0x199C50 -- 2nd financial checksum [ cash ror thirteen, xor 0F4EC9621 ]*/
DWORD financialChecksum_2;
/*0x199C54 -- (copyright notice in SC4 files)*/
char copyrightNotice[40];
/*0x199C7C -- 0 in SV4 files, FED3 in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_FED3inSC4;
/*0x199C7E -- 0 in SV4 files, F318 in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_F318inSC4;
/*0x199C80 -- 0 in SV4 files, B218 in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_B218inSC4;
/*0x199C82 -- 0 in SV4 files, 458A in SC4 files (for cheat detection)*/
WORD cheat_0inSV4_458AinSC4;
/*0x199C84 -- ?*/
BYTE unk0x199C84[2];
/*0x199C86 -- ?*/
BYTE unk0x199C86[2];
/*0x199C88 -- meaning unknown, 32*(park_size - 1)*/
WORD unk_32_x_par_parkSize_minus_1_par;
/*0x199C8A -- meaning unknown, value in 199C88 plus 011E*/
WORD unk_value_at_0x272478_plus_011E;
/*0x199C8C -- park size (visible tiles per edge +2)*/
WORD parkSize;
/*0x199C8E -- meaning unknown, value in 199C88 minus 1 (except full size park in which case the value is 0FFF)*/
WORD unk_value_at_0x272478_minus_1_except_fullSizePark;
/*0x199C90 -- same price*/
DWORD samePrice_1;
/*0x199C94 -- ?*/
BYTE unk0x199C94[2];
/*0x199C96 -- ?*/
BYTE unk0x199C96[3];
/*0x199C99 -- Water color (0=normal, 1=red)*/
BYTE waterColor;
/*0x199C9A -- ?*/
BYTE unk0x199C9A[2];
/*0x199C9C -- Research items in LL only*/
BYTE researchItems2[900];
/*0x19A020 -- ? (blank)*/
BYTE unk0x19A020[5468];
/*0x19B57C -- banner info. 100 sets of 8 byte structures(byte 0: 0=standard, 1=jungle(wooden), 2=classical, 3=egyptian, 4=mining, 5=prehistoric(bone), 6=asian, 7=snowy, 8=space,FF= unused; byte1: 0=normal, 1=no entry; bytes 2,3: string index; byte 4: color; byte 5: te*/
BANNERINFOSTRUCT bannerInfo[100];
/*0x19B89C -- 1024 Null terminated Name strings for park, rides, peeps, etc. Each string is allocated 32 bytes. Names are entered starting at the last location (1A387C) and new names are entered in preceeding slots as the user creates them.*/
char nameStrings[1024][32];
/*0x1A389C -- a game time counter - used to trigger various events*/
DWORD gameTimeCounter;
/*0x1A38A0 -- Ride structure. 255 structures of 608 bytes each*/
SV4_RIDESTRUCTARRAY rides;
/*0x1C9640 -- a game time counter - not used as a trigger for any events as far as I can tell*/
WORD gameTimeCounter2;
/*0x1C9642 -- Horizontal view position (0000 to 1FFF, negated depending on Viewing angle)*/
WORD horzViewPos;
/*0x1C9644 -- Vertical view position (0000 to 1FFF, negated depending on Viewing angle)*/
WORD vertViewPos;
/*0x1C9646 -- Viewing Zoom factor (0 = closest, 1 = medium, 2 = far)*/
BYTE zoomFactor;
/*0x1C9647 -- Viewing angle (0 = from NE, 1 = from NW, 2 = from SW, 3 = from SE) [note: horizontal and vertical view position will be positive or negative depending on the view angle as indicated below:*/
BYTE viewingAngle;
/*0x1C9648 -- Animation object locations [1000][6]*/
ANIMATIONOBJECTLOCATION animationObjectLocations[1000];
/*0x1CADB8 -- number of animation objects (Park/Ride entry, queue & banner, fountains, etc) points*/
DWORD numAnimationObjects;
/*0x1CADBC -- ?*/
BYTE unk0x1CADBC[12];
/*0x1CADC8 -- progression of scrolling text (start point of scrolling text)*/
WORD scrollingTextProgression;
/*0x1CADCA -- ?*/
BYTE unk0x1CADCA[4];
/*0x1CADCE -- ?*/
BYTE unk0x1CADCE[2];
/*0x1CADD0 -- ?*/
BYTE unk0x1CADD0[116];
/*0x1CAE44 -- Data Logging - 8 structures of 19,212 bytes each (graphic charts for G's, etc on rides)*/
BYTE dataLogging[8][19212];
/*0x1F06A4 -- next guest number*/
DWORD nextGuestNumber;
/*0x1F06A8 -- another game counter, two upper bits always zero*/
WORD gameTimeCounter3;
/*0x1F06AA -- Patrol areas [116][32][4]*/
BYTE patrolAreas[116][32][4];
/*0x1F40AA -- Staff type covered patrol areas [4][32][4]*/
BYTE staffTypePatrolAreas[4][32][4];
/*0x1F42AA -- Patrol area flags [116] -- For each byte: Bit 0 is set if there is */
BYTE patrolArea_flags[116];
/*0x1F431E -- ? - has the value 01*/
BYTE unk0x1F431E[1];
/*0x1F431F -- ? - has the value 01*/
BYTE unk0x1F431F[1];
/*0x1F4320 -- ? - has the value 01*/
BYTE unk0x1F4320[1];
/*0x1F4321 -- ? - has the value 01*/
BYTE unk0x1F4321[1];
/*0x1F4322 -- ?*/
BYTE unk0x1F4322[8];
/*0x1F432A -- climate (0=wet, 1=normal, 2=dry, 3=cold)*/
BYTE climate;
/*0x1F432B -- ? - usu has the value 05 but a few scenarios have the value 0B*/
BYTE unk_usually_5_but_someScenarios_8;
/*0x1F432C -- weather timer - count down from 1920*/
WEATHER weather;
/*0x1F4338 -- Message area. 61 messages. Each message structure uses 268 bytes. Current message at 1F4338, then put into last spot (1F8208) and others are moved up.*/
MESSAGESTRUCTARRAY messages;
/*0x1F8314 -- Scenario name (not park name)*/
char scenarioName2[62];
/*0x1F8352 -- Scenario slot number*/
WORD scenarioSlot;
/*0x1F8354 -- scenario flags (expansion packs only) bit 12: error while loading*/
DWORD scenarioFlags;
/*0x1F8356 -- Unknown flags*/
WORD unk_flags1;
/*0x1F8358 -- Unknown counter*/
WORD unk_counter1;
/*0x1F835C -- ?*/
BYTE unk0x1F835C[428];
/*0x1F8508 -- these last four bytes of the file contain an additional checksum in CF/AA and LL saved games. This is in addition to the checksum added after the file is RLE encoded. This was not present in the original RCT files. This checksum is calculated by starting*/
DWORD extraFileChecksum;
}
SV4_PARKDATA;
