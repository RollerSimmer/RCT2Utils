#include <windows.h>
#include "SV6_OBJDAT.H"
#include "../../funcs/rct2funcs.h"
#include <FileIO2.h>
#include <stdlib2.h>

/*
	128 entries for the rides
	252 entries for the small scenery
	128 entries for the large scenery
	128 entries for the walls
	32 entries for the banners
	16 entries for the paths
	15 entries for the path bits
	19 entries for the scenery sets
	1 entry for the park entrance
	1 entry for the water
	1 entry for the "stex" dat file to use
*/

/*

typedef struct
{
	SV6_OBJDAT_HEADER 
		rides[SV6_OBJDAT_NUMENTRIES_RIDES],
		smallScenery[SV6_OBJDAT_NUMENTRIES_SMALLSCENERY],
		largeScenery[SV6_OBJDAT_NUMENTRIES_LARGESCENERY],
		walls[SV6_OBJDAT_NUMENTRIES_WALLS],
		banners[SV6_OBJDAT_NUMENTRIES_BANNERS],
		paths[SV6_OBJDAT_NUMENTRIES_PATHS],
		pathUtilities[SV6_OBJDAT_NUMENTRIES_PATHUTILITIES],
		groups[SV6_OBJDAT_NUMENTRIES_GROUPS],
		entrance[SV6_OBJDAT_NUMENTRIES_ENTRANCE],
		palette[SV6_OBJDAT_NUMENTRIES_PALETTE],
		scenarioText[SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT];
} SV6_OBJDAT_HEADER_BLOCK;
*/

SV6_OBJDAT_HEADER_BLOCK RCT1emulationTable;

SV6_OBJDAT_HEADER_BLOCK_ALT
	*RCT1emulationTableAlt=
		(SV6_OBJDAT_HEADER_BLOCK_ALT*)(&RCT1emulationTable);	

/*

#define SV6_OBJDAT_NUMENTRIES_RIDES 128
#define SV6_OBJDAT_NUMENTRIES_SMALLSCENERY 252 
#define SV6_OBJDAT_NUMENTRIES_LARGESCENERY 128 
#define SV6_OBJDAT_NUMENTRIES_WALLS 128 
#define SV6_OBJDAT_NUMENTRIES_BANNERS 32 
#define SV6_OBJDAT_NUMENTRIES_PATHS 16
#define SV6_OBJDAT_NUMENTRIES_PATHUTILITIES 15
#define SV6_OBJDAT_NUMENTRIES_GROUPS 19  
#define SV6_OBJDAT_NUMENTRIES_ENTRANCE 1 
#define SV6_OBJDAT_NUMENTRIES_PALETTE 1
#define SV6_OBJDAT_NUMENTRIES_SCENARIOTEXT 1 

*/


SV6_OBJDAT_STRINGTABLE objStrTable=
{
	//rides
		/*0*/ {USED,"SCHT1"}, /*Steel Roller Coaster Train*/
		/*1*/ {USED,"SCHT1"}, /*Steel Roller Coaster Train (facing backwards)*/
		/*2*/ {USED,"PTCT1"}, /*Wooden Roller Coaster Train*/
		/*3*/ {USED,"NEMT"}, /*Inverted Coaster Train*/
		/*4*/ {USED,"ARRSW1"}, /*Suspended Swinging Cars*/
		/*5*/ {USED,"ZLDB"}, /*Ladybird' Cars*/
		/*6*/ {USED,"TOGST"}, /*Stand-Up Roller Coaster Cars*/
		/*7*/ {USED,"ZLDB"}, /*Spinning Cars*/
		/*8*/ {USED,"BATFL"}, /*Single-Person Swinging Chairs*/
		/*9*/ {USED,"SWANS"}, /*Swan Pedal-Boats **/
		/*0A*/ {USED,"MONO1"}, /*Large Monorail Train **/
		/*0B*/ {USED,"CBOAT"}, /*Canoes **/
		/*0C*/ {USED,"RBOAT"}, /*Rowing Boats **/
		/*0D*/ {USED,"NRL"}, /*Steam Train **/
		/*0E*/ {USED,"WMOUSE"}, /*Mouse Cars*/
		/*0F*/ {USED,"BBOAT"}, /*Bumper Boats **/
		/*10*/ {USED,"PTCT2R"}, /*Wooden Roller Coaster Train (backwards)*/
		/*11*/ {USED,"RCKC"}, /*Rocket' Cars*/
		/*12*/ {USED,"STEEP1"}, /*Horses*/
		/*13*/ {USED,"SPCAR"}, /*Sportscars **/
		/*14*/ {USED,"SKYTR"}, /*Lying-Down Swinging Cars*/
		/*15*/ {USED,"SMC2"}, /*Mine Cars*/
		/*16*/ {USED,"ARRSW2"}, /*Suspended Swinging Airplane Cars*/
		/*17*/ {USED,"MONO2"}, /*Small Monorail Cars **/
		/*18*/ {USED,"TRIKE"}, /*Water Tricycles **/
		/*19*/ {USED,"SSC1"}, /*Whoa Belly Car **/
		/*1A*/ {USED,"BOB1"}, /*Bobsleigh Cars*/
		/*1B*/ {USED,"DING1"}, /*Dinghies*/
		/*1C*/ {USED,"OBS1"}, /*Rotating Cabin **/
		/*1D*/ {USED,"AMT1"}, /*Mine Train*/
		/*1E*/ {USED,"CLIFT1"}, /*Chairlift Cars*/
		/*1F*/ {USED,"ARRT1"}, /*Corkscrew Roller Coaster Train*/
		/*20*/ {USED,"STEEP2"}, /*Motorbikes*/
		/*21*/ {USED,"RCR"}, /*Racing Cars **/
		/*22*/ {USED,"TRUCK1"}, /*Trucks **/
		/*23*/ {USED,"KART1"}, /*Go Karts **/
		/*24*/ {USED,"RAPBOAT"}, /*Rapids Boats **/
		/*25*/ {USED,"LFB1"}, /*Log Flume Boats **/
		/*26*/ {USED,"DODG1"}, /*Bumper Cars*/
		/*27*/ {USED,"SWSH1"}, /*Swinging Ship*/
		/*28*/ {USED,"SWSH2"}, /*Swinging Inverter Ship*/
		/*29*/ {USED,"MGR1"}, /*Carousel*/
		/*2A*/ {USED,"FWH1"}, /*Ferris Wheel*/
		/*2B*/ {USED,"SIMPOD"}, /*Simulator Pod*/
		/*2C*/ {USED,"C3D"}, /*Cinema Building*/
		/*2D*/ {USED,"TOPSP1"}, /*Gravitron Car*/
		/*2E*/ {USED,"SRINGS"}, /*Space Rings*/
		/*2F*/ {USED,"REVF1"}, /*Reverse Whoa Belly Car*/
		/*30*/ {USED,"BMVD"}, /*Vertical Roller Coaster Cars*/
		/*31*/ {USED,"CTCAR"}, /*Cat' Cars **/
		/*32*/ {USED,"TWIST1"}, /*Scrambled Eggs Arms and Cars*/
		/*33*/ {USED,"HHBUILD"}, /*Haunted House Building*/
		/*34*/ {USED,"ZLOG"}, /*Log' Cars*/
		/*35*/ {USED,"CIRCUS1"}, /*Circus Tent*/
		/*36*/ {USED,"GTC"}, /*Ghost Train Cars **/
		/*37*/ {USED,"BMSD"}, /*Steel Twister Roller Coaster Train*/
		/*38*/ {USED,"MFT"}, /*Wood Twister Roller Coaster Train*/
		/*39*/ {USED,"SFRIC1"}, /*Wooden Side-Friction Cars*/
		/*3A*/ {USED,"VCR"}, /*Vintage Cars **/
		/*3B*/ {USED,"NRL2"}, /*Steam Train (Covered Cars) **/
		/*3C*/ {USED,"BMSU"}, /*Steel Twister Roller Coaster Train (Stand-up)*/
		/*3D*/ {USED,"BMFL"}, /*Floorless Steel Twister Roller Coaster Train*/
		/*3E*/ {USED,"SMC1"}, /*Steel Mouse Cars*/
		/*3F*/ {USED,"CLIFT2"}, /*Chairlift Cars (Alternative)*/
		/*40*/ {USED,"SMONO"}, /*Suspended Monorail Train **/
		/*41*/ {USED,"HELICAR"}, /*Helicopter Cars **/
		/*42*/ {USED,"VREEL"}, /*Virginia Reel Tubs*/
		/*43*/ {USED,"REVCAR"}, /*Reverser Cars*/
		/*44*/ {USED,"GOLF1"}, /*Golfers **/
		/*45*/ {USED,"SPBOAT"}, /*River Ride Boats*/
		/*46*/ {USED,"VEKST"}, /*Flying Roller Coaster Train*/
		/*47*/ {USED,"BMRB"}, /*Steel Twister Roller Coaster Train (Non-Looping)*/
		/*48*/ {USED,"UTCAR"}, /*Heartline Twister Cars*/
		/*49*/ {USED,"UTCARR"}, /*Heartline Twister Cars (Reversed)*/
		/*4A*/ {UNUSED,""}, /*(reserved)*/
		/*4B*/ {USED,"GDROP1"}, /*Rotodrop/Freefall Car **/
		/*4C*/ {USED,"FSAUC"}, /*Flying Saucers*/
		/*4D*/ {USED,"CHBUILD"}, /*Crooked House Building*/
		/*4E*/ {USED,"MONBK"}, /*Bicycles **/
		/*4F*/ {USED,"ARRT2"}, /*Hypercoaster train*/
		/*50*/ {USED,"NEMT"}, /*4-across inverted coaster train*/
		/*51*/ {USED,"CSTBOAT"}, /*Water coaster boats*/
		/*52*/ {USED,"SLCFO"}, /*Face-off cars*/
		/*53*/ {USED,"JSKI"}, /*Jet Skis **/
		/*54*/ {USED,"RFTBOAT"}, /*Raft boats **/
		/*55*/ {USED,"AML1"}, /*American style steam train **/
		/*56*/ {USED,"THCAR"}, /*Air powered coaster train*/
		/*57*/ {USED,"IVMC1"}, /*Suspended Wild Mouse Cars*/
		/*58*/ {USED,"ENTERP"}, /*Enterprise Wheel*/
		/*59*/ {UNUSED,""}, /**/
		/*5A*/ {USED,"ICECR1"}, /*Ice Cream Stall*/
		/*5B*/ {USED,"CHPSH2"}, /*Fries Stall*/
		/*5C*/ {USED,"DRNKS"}, /*Drink Stall*/
		/*5D*/ {USED,"CNDYF"}, /*Cotton Candy Stall*/
		/*5E*/ {USED,"BURGB"}, /*Burger Bar*/
		/*5F*/ {USED,"BALLN"}, /*Balloon Stall*/
		/*60*/ {USED,"INFOK"}, /*Information Kiosk*/
		/*61*/ {USED,"TLT1"}, /*Bathroom*/
		/*62*/ {USED,"SOUVS"}, /*Souvenir Stall*/
		/*63*/ {USED,"PIZZS"}, /*Pizza Stall*/
		/*64*/ {USED,"POPCS"}, /*Popcorn Stall*/
		/*65*/ {USED,"HOTDS"}, /*Hot Dog Stall*/
		/*66*/ {USED,"SQDST"}, /*Exotic Sea-Food Stall*/
		/*67*/ {USED,"HATST"}, /*Hat Stall*/
		/*68*/ {USED,"TOFFS"}, /*Candy Apple Stand*/
		/*69*/ {USED,"TSHRT"}, /*T-shirt Stall*/
		/*6A*/ {USED,"DOUGH"}, /*Donut Shop*/
		/*6B*/ {USED,"COFFS"}, /*Coffee Shop*/
		/*6C*/ {USED,"CHCKS"}, /*Fried Chicken Stall*/
		/*6D*/ {USED,"LEMST"}, /*Lemonade Stall*/
		/*6E*/ {UNUSED,""}, /**/
		/*6F*/ {UNUSED,""}, /**/
		/*70*/ {UNUSED,""}, /**/
		/*71*/ {UNUSED,""}, /**/
		/*72*/ {UNUSED,""}, /**/
		/*73*/ {UNUSED,""}, /**/
		/*74*/ {UNUSED,""}, /**/
		/*75*/ {UNUSED,""}, /**/
		/*76*/ {UNUSED,""}, /**/
		/*77*/ {UNUSED,""}, /**/
		/*78*/ {UNUSED,""}, /**/
		/*79*/ {UNUSED,""}, /**/
		/*7A*/ {UNUSED,""}, /**/
		/*7B*/ {UNUSED,""}, /**/
		/*7C*/ {UNUSED,""}, /**/
		/*7D*/ {UNUSED,""}, /**/
		/*7E*/ {UNUSED,""}, /**/
		/*7F*/ {UNUSED,""}, /**/
	//smallScenery
		/*00*/ {USED,"TL0"}, /*Tree(tall light green w/bare branches) [33]*/
		/*01*/ {USED,"TL1"}, /*Tree(tall light green big roots ) [30]*/
		/*02*/ {USED,"TL2"}, /*Tree(dark blue-green oval ) [27]*/
		/*03*/ {USED,"TL3"}, /*Tree(tall green plain ) [31]*/
		/*04*/ {USED,"TM0"}, /*Tree(greenyellow short round ) [17]*/
		/*05*/ {USED,"TM1"}, /*Tree(green big roots odd shape ) [20]*/
		/*06*/ {USED,"TM2"}, /*Tree(short green plain ) [22]*/
		/*07*/ {USED,"TM3"}, /*Tree(short green round med roots ) [17]*/
		/*08*/ {USED,"TS0"}, /*tree(roundish larger) [11] Q*/
		/*09*/ {USED,"TS1"}, /*tree (roundish, smaller) [9] Q*/
		/*0A*/ {USED,"TS2"}, /*tree(sm fruit tree ) [10]  Q*/
		/*0B*/ {USED,"TS3"}, /*ornamental tree- teardrop [9] Q*/
		/*0C*/ {USED,"TS4"}, /*ornamental tree- ball [7] Q*/
		/*0D*/ {USED,"TS5"}, /*ornamental tree- cone [8] Q*/
		/*0E*/ {USED,"TS6"}, /*ornamental tree- duck [9] Q*/
		/*0F*/ {USED,"TIC"}, /*Incense Cedar [34]*/
		/*10*/ {USED,"TLC "}, /*Lawson Cypress [25] Q*/
		/*11*/ {USED,"TMC"}, /*Montery Cypress [27]*/
		/*12*/ {USED,"TMP"}, /*Monkey Puzzle [29]*/
		/*13*/ {USED,"TITC"}, /*Italian Cypress [30]*/
		/*14*/ {USED,"TGHC"}, /*Golden Hinoki Cypress [21]*/
		/*15*/ {USED,"TAC"}, /*Arizona Cypress [28] Q*/
		/*16*/ {USED,"TGHC2"}, /*Hiba [16]*/
		/*17*/ {USED,"TCJ "}, /*Common Juniper [16] Q*/
		/*18*/ {USED,"TMBJ"}, /*Meyer's Blue Juniper [14]*/
		/*19*/ {USED,"TCF"}, /*Caucasion Fir [30]*/
		/*1A*/ {USED,"TCL"}, /*Cedar of Lebanon [41]*/
		/*1B*/ {USED,"TRF"}, /*Red Fir (large) [29]*/
		/*1C*/ {USED,"TRF2"}, /*Red Fir (small) [28] Q*/
		/*1D*/ {USED,"TEL"}, /*European Larch [29]*/
		/*1E*/ {USED,"TAP"}, /*Aleppo Pine [20]*/
		/*1F*/ {USED,"TSP"}, /*Scots Pine [39]*/
		/*20*/ {USED,"TMZP"}, /*Montezuma Pine [24]*/
		/*21*/ {USED,"TCRP"}, /*Corsican Pine [33]*/
		/*22*/ {USED,"TBP"}, /*Black Poplar [20]*/
		/*23*/ {USED,"TLP"}, /*Lombardy Poplar [26] Q*/
		/*24*/ {USED,"TWP"}, /*White Poplar [19]*/
		/*25*/ {USED,"TAS"}, /*Aspen [16]*/
		/*26*/ {USED,"TMG"}, /*Magnolia [12]*/
		/*27*/ {USED,"TWW"}, /*Weeping Willow [18]*/
		/*28*/ {USED,"TSB"}, /*Silver Birch [35]*/
		/*29*/ {USED,"TVL"}, /*Voss' Laburnaw [19]*/
		/*2A*/ {USED,"TCT"}, /*Cabbage Tree [20]*/
		/*2B*/ {USED,"TEF"}, /*Elephant Fountain [20]*/
		/*2C*/ {USED,"TAL"}, /*ornamental tree- gator [8] Q*/
		/*2D*/ {USED,"TSQ"}, /*ornamental tree- squirell [9] Q*/
		/*2E*/ {USED,"THT "}, /*ornamental tree- heart [8] Q*/
		/*2F*/ {USED,"TCB "}, /*ornamental tree- club[8] Q*/
		/*30*/ {USED,"TDM "}, /*ornamental tree- diamond[8] Q*/
		/*31*/ {USED,"TSD"}, /*ornamental tree- spade[8] Q*/
		/*32*/ {USED,"TGS"}, /*Giraffe statue [20]*/
		/*33*/ {USED,"TUS"}, /*Unicorn statue [13]*/
		/*34*/ {USED,"TH1"}, /*Cannary Palm [19]*/
		/*35*/ {USED,"TBC "}, /*Cactus (large) [16]*/
		/*36*/ {USED,"TH2"}, /*Palm tree (tall) [38]*/
		/*37*/ {USED,"TPM"}, /*Palm tree(short) [17]*/
		/*38*/ {USED,"TSC"}, /*Cactus (small) [11] Q*/
		/*39*/ {USED,"TG1"}, /*Garden (large)(purple pink sparse) [2] Q*/
		/*3A*/ {USED,"TWF"}, /*Geometric Fountain [19]*/
		/*3B*/ {USED,"TSH0"}, /*bush(small round shrub [4] Q*/
		/*3C*/ {USED,"TSH1"}, /*shrub(shrub bluish green [4] Q*/
		/*3D*/ {USED,"TSH2"}, /*bush(shrub with berries light w/ trunk [ 4] Q*/
		/*3E*/ {USED,"TSH3"}, /*bush(shrub irregular w/berries) [4] Q*/
		/*3F*/ {USED,"TSH4"}, /*shrub(shrub bluish green with berries)[4] Q*/
		/*40*/ {USED,"TSH5"}, /*bush(shrub with berries light tall [4] Q*/
		/*41*/ {USED,"TG2"}, /*Garden (large)(red yellow sparse) [2]*/
		/*42*/ {USED,"TG3"}, /*Garden (large)(purple brown sparse) [2]*/
		/*43*/ {USED,"TG4"}, /*Garden (large)(purple pink dense) [2]*/
		/*44*/ {USED,"TG5"}, /*Garden (large)(red yellow dense) [2]*/
		/*45*/ {USED,"TG6"}, /*Garden (large)(purple brown dense ) [2]*/
		/*46*/ {USED,"TG7"}, /*Garden (large)(white sparse ) [2]*/
		/*47*/ {USED,"TG8"}, /*Garden (large)(light purple sparse ) [2]*/
		/*48*/ {USED,"TG9"}, /*Garden (large)(pink blue sparse ) [2]*/
		/*49*/ {USED,"TG10"}, /*Garden (large)(pink sparse ) [2]*/
		/*4A*/ {USED,"TG11"}, /*Garden (large)(white dense ) [2]*/
		/*4B*/ {USED,"TG12"}, /*Garden (large)(light purple dense ) [2]*/
		/*4C*/ {USED,"TG13"}, /*Garden (large)(pink blue dense ) [2]*/
		/*4D*/ {USED,"TG14"}, /*Garden (large)(pink dense ) [2]*/
		/*4E*/ {USED,"TT1"}, /*Roman Temple [10]*/
		/*4F*/ {USED,"TDF"}, /*Dolphin Fountain [19]*/
		/*50*/ {USED,"TSH"}, /*Horse statue [16]*/
		/*51*/ {USED,"THRS"}, /*Horseman statue [16]*/
		/*52*/ {USED,"TSTD"}, /*Dolphins statue [12]*/
		/*53*/ {USED,"TRMS"}, /*Roman statue male [19]*/
		/*54*/ {USED,"TRWS"}, /*Roman Statue female [19]*/
		/*55*/ {USED,"TRC "}, /*Roman Column [12] Q*/
		/*56*/ {USED,"TQF"}, /*Cupid Fountain [12]*/
		/*57*/ {USED,"TES1"}, /*Egyptian statue [12]*/
		/*58*/ {USED,"TEN "}, /*Cleopatra's Needle [8] Q*/
		/*59*/ {USED,"TERS "}, /*Ruined statue [2] Q*/
		/*5A*/ {USED,"TERB "}, /*Stone block [4] Q*/
		/*5B*/ {USED,"TEP "}, /*Egyptian column [8] Q*/
		/*5C*/ {USED,"TST1"}, /*Tall Toadstool(red, white dots) [14]*/
		/*5D*/ {USED,"TST2"}, /*Medium Toadstool(red, white dots) [11]*/
		/*5E*/ {USED,"TMS1"}, /*Flat White Toadstool(tan) [9]*/
		/*5F*/ {USED,"TAS1"}, /*Candy Tree - Black [15]*/
		/*60*/ {USED,"TAS2"}, /*Candy Tree - Cylinder [12]*/
		/*61*/ {USED,"TAS3"}, /*Candy Tree - Round [13]*/
		/*62*/ {USED,"TST3"}, /*Small Toadstool (tall) [8] Q*/
		/*63*/ {USED,"TST4"}, /*Small Toadstool (flat) [4] Q*/
		/*64*/ {USED,"TST5"}, /*Small Toadstool [5] Q*/
		/*65*/ {USED,"TAS4 "}, /*Candy [8] Q*/
		/*66*/ {USED,"TCY"}, /*Common Yew [18]*/
		/*67*/ {USED,"TBW "}, /*Broken wheel [2] Q*/
		/*68*/ {USED,"TBR1 "}, /*Short Barrel (upright) [3] Q*/
		/*69*/ {USED,"TBR2 "}, /*Short Barrel (on side) [3] Q*/
		/*6A*/ {USED,"TML "}, /*Logs [2] Q*/
		/*6B*/ {USED,"TMW"}, /*Wheels(wagon wheels) [3] Q*/
		/*6C*/ {USED,"TBR3"}, /*Tall Barrel (on side) [3] Q*/
		/*6D*/ {USED,"TBR4"}, /*Tall Barrel (upright) [4] Q*/
		/*6E*/ {USED,"TMJ"}, /*Junk(mine theme) [8]*/
		/*6F*/ {USED,"TBR"}, /*bullrushes [5] Q*/
		/*70*/ {USED,"TMO1"}, /*Martian Equipment(semaphore) [10] Q*/
		/*71*/ {USED,"TMO2"}, /*Martian Tube(light bulb) [14] Q*/
		/*72*/ {USED,"TMO3"}, /*Martian Coil(shuttle cock) [11] Q*/
		/*73*/ {USED,"TMO4"}, /*Martian Tower [35]*/
		/*74*/ {USED,"TMO5"}, /*Martian Pod [13]*/
		/*75*/ {USED,"TWH1"}, /*Wonderland House [10]*/
		/*76*/ {USED,"TWH2"}, /*Pumpkin House [11]*/
		/*77*/ {USED,"TNS"}, /*Norway Spruce [33]*/
		/*78*/ {USED,"TP1"}, /*White Pawn [7] Q*/
		/*79*/ {USED,"TP2"}, /*Black Pawn [7] Q*/
		/*7A*/ {USED,"TK1"}, /*White Knight [8] Q*/
		/*7B*/ {USED,"TK2"}, /*Black Knight [8] Q*/
		/*7C*/ {USED,"TR1"}, /*White Rook [8] Q*/
		/*7D*/ {USED,"TR2"}, /*Black Rook [8] Q*/
		/*7E*/ {USED,"TQ1"}, /*White "Queen" [12] Q*/
		/*7F*/ {USED,"TQ2"}, /*Black "Queen" [12] Q*/
		/*80*/ {USED,"TWN"}, /*Walnut [19]*/
		/*81*/ {USED,"TCE"}, /*Camperdown Elm [14]*/
		/*82*/ {USED,"TCO"}, /*Common Oak [28]*/
		/*83*/ {USED,"THL"}, /*Honey Locust [38]*/
		/*84*/ {USED,"TCC"}, /*Chinese Cedar [32]*/
		/*85*/ {USED,"TB1"}, /*White Bishop [8]*/
		/*86*/ {USED,"TB2"}, /*Black Bishop [8]*/
		/*87*/ {USED,"TK3"}, /*White "King" [12] Q*/
		/*88*/ {USED,"TK4"}, /*Black "King" [12] Q*/
		/*89*/ {USED,"TBN"}, /*Single Bone [8] Q*/
		/*8A*/ {USED,"TBN1"}, /*Rib Cage [6]*/
		/*8B*/ {USED,"TDT1"}, /*Dead Tree (w/twigs )[15]*/
		/*8C*/ {USED,"TDT2"}, /*Dead Tree (forked trunk )[16]*/
		/*8D*/ {USED,"TDT3"}, /*Dead Tree (no twigs )[12]*/
		/*8E*/ {USED,"TMM1"}, /*Mausoleum(round grave monument) [10]*/
		/*8F*/ {USED,"TMM2 "}, /*Graveyard statue (tall) [11] Q*/
		/*90*/ {USED,"TMM3 "}, /*Graveyard statue (short) [8] Q*/
		/*91*/ {USED,"TGS1 "}, /*Gravestone(1) [3] Q*/
		/*92*/ {USED,"TGS2"}, /*Gravestone(2) [3] Q*/
		/*93*/ {USED,"TGS3"}, /*Gravestone(3) [3] Q*/
		/*94*/ {USED,"TGS4"}, /*Gravestone(4) [3] Q*/
		/*95*/ {USED,"TDN4"}, /*Stegasaurus [10]*/
		/*96*/ {USED,"TDN5"}, /*Triceratops [11]*/
		/*97*/ {USED,"TJT1"}, /*Jungle Tree(with vines) [27]*/
		/*98*/ {USED,"TJT2"}, /*Jungle Tree(with vines, tall) [35]*/
		/*99*/ {USED,"TJB1 "}, /*Jungle bush(aloe-like) [8] Q*/
		/*9A*/ {USED,"TTF "}, /*underwater Fountain(built on water) [24]*/
		/*9B*/ {USED,"TF1"}, /*Fruit Tree (A)(yellow fruit) [16]*/
		/*9C*/ {USED,"TF2"}, /*Fruit Tree (B)(orange fruit) [16]*/
		/*9D*/ {USED,"TGE1"}, /*Geometric (Triangle sphere) [12]*/
		/*9E*/ {USED,"TJT3"}, /*Jungle Tree(big trunk few leaves) [23]*/
		/*9F*/ {USED,"TJT4"}, /*Jungle Tree(short big leaves ) [16]*/
		/*A0*/ {USED,"TJP1"}, /*Jungle Plant(large eater) [14]*/
		/*A1*/ {USED,"TJB2 "}, /*Jungle bush(leafy) [9] Q*/
		/*A2*/ {USED,"TGE2"}, /*Geometric (Triangle prism) [12]*/
		/*A3*/ {USED,"TJT5"}, /*Jungle Tree(jungle short small leaves ) [18]*/
		/*A4*/ {USED,"TJB3 "}, /*Jungle bush(leafy tall dark) [12] Q*/
		/*A5*/ {USED,"TJB4 "}, /*Jungle bush(leafy tall light) [9] Q*/
		/*A6*/ {USED,"TJT6"}, /*Jungle Tree [17] Q*/
		/*A7*/ {USED,"TJP2 "}, /*Jungle Plant(small eater) [9] Q*/
		/*A8*/ {USED,"TGE3"}, /*Geometric (Cube) [10]*/
		/*A9*/ {USED,"TCK"}, /*Garden Clock [1]*/
		/*AA*/ {USED,"TGE4"}, /*Geometric (Soccer Ball) [12]*/
		/*AB*/ {USED,"TGE5"}, /*Geometric (Hex Prism) [12]*/
		/*AC*/ {USED,"TG15"}, /*Garden (small)(pink) [2] Q*/
		/*AD*/ {USED,"TG16"}, /*Garden (small)(bright pink) [2] Q*/
		/*AE*/ {USED,"TG17"}, /*Garden (small)(blue) [2] Q*/
		/*AF*/ {USED,"TG18"}, /*Garden (small)(lavender) [2] Q*/
		/*B0*/ {USED,"TG21"}, /*Garden (small)(red) [2] Q*/
		/*B1*/ {USED,"TG20"}, /*Garden (small)(yellow) [2] Q*/
		/*B2*/ {USED,"TG21"}, /*Garden (small)(red&yellow) [2] Q*/
		/*B3*/ {USED,"TSM"}, /*snowman [14]*/
		/*B4*/ {USED,"TIG"}, /*igloo [6]*/
		/*B5*/ {USED,"TCFS"}, /*Caucasian Fir with snow [30]*/
		/*B6*/ {USED,"TRFS"}, /*Red Fir with snow [29]*/
		/*B7*/ {USED,"TRF3"}, /*Red Fir- small with snow [28] Q*/
		/*B8*/ {USED,"TNSS"}, /*Norway Spruce with snow [33]*/
		/*B9*/ {USED,"TCT1"}, /*castle tower round(brown) [27]*/
		/*BA*/ {USED,"TCT2"}, /*castle tower round(grey) [27]*/
		/*BB*/ {USED,"TSF1"}, /*giant snowflake(1) [8] Q*/
		/*BC*/ {USED,"TSF2"}, /*giant snowflake(2) [8] Q*/
		/*BD*/ {USED,"TSF3"}, /*giant snowflake(3) [8] Q*/
		/*BE*/ {USED,"TCN"}, /*cannon [4] Q*/
		/*BF*/ {USED,"TTG"}, /*target [6] Q*/
		/*C0*/ {USED,"TSNC"}, /*log cabin (snow) [12]*/
		/*C1*/ {USED,"TSNB"}, /*giant snowball [10]*/
		/*C2*/ {USED,"TSCP"}, /*space capsule(martian white round w/dish ) [10]*/
		/*C3*/ {USED,"TCD "}, /*cauldron [4] Q*/
		/*C4*/ {USED,"TSG"}, /*swamp goo [1]*/
		/*C5*/ {USED,"TSK"}, /*skull [12]*/
		/*C6*/ {USED,"TGH1 "}, /*bat statue (small) [14] Q*/
		/*C7*/ {USED,"TGH2 "}, /*bat statue [19]*/
		/*C8*/ {USED,"TSMP"}, /*pumpkin(jack o'lantern) [10]*/
		/*C9*/ {USED,"TJF"}, /*jungle flower [12]*/
		/*CA*/ {USED,"TLY"}, /*water lilly [1]*/
		/*CB*/ {USED,"TGC1"}, /*space sculpture [16]*/
		/*CC*/ {USED,"TGC2 "}, /*space sculpture (small) [8] Q*/
		/*CD*/ {USED,"TGG"}, /*gong [8] Q*/
		/*CE*/ {USED,"TSPH"}, /*space house [12]*/
		/*CF*/ {USED,"TOH1"}, /*small chinese house [8]*/
		/*D0*/ {USED,"TOH2"}, /*tall chinese house [35]*/
		/*D1*/ {USED,"TOT1"}, /*asian tree 3 [20]*/
		/*D2*/ {USED,"TOT2"}, /*asian tree 4 [16]*/
		/*D3*/ {USED,"TOS "}, /*dog statue [16] Q*/
		/*D4*/ {USED,"TOT3"}, /*asian tree 1(short,light) [9] Q*/
		/*D5*/ {USED,"TOT4"}, /*asian tree 2(tall,dark) [14] Q*/
		/*D6*/ {USED,"TSC2"}, /*space building [18]*/
		/*D7*/ {USED,"TSP1"}, /*space tree [16]*/
		/*D8*/ {USED,"TOH3"}, /*chinese building(with bell) [14]*/
		/*D9*/ {USED,"TSP2"}, /*space flytrap [20]*/
		/*DA*/ {UNUSED,""}, /**/
		/*DB*/ {UNUSED,""}, /**/
		/*DC*/ {UNUSED,""}, /**/
		/*DD*/ {UNUSED,""}, /**/
		/*DE*/ {UNUSED,""}, /**/
		/*DF*/ {UNUSED,""}, /**/
		/*E0*/ {UNUSED,""}, /**/
		/*E1*/ {UNUSED,""}, /**/
		/*E2*/ {UNUSED,""}, /**/
		/*E3*/ {UNUSED,""}, /**/
		/*E4*/ {UNUSED,""}, /**/
		/*E5*/ {UNUSED,""}, /**/
		/*E6*/ {UNUSED,""}, /**/
		/*E7*/ {UNUSED,""}, /**/
		/*E8*/ {UNUSED,""}, /**/
		/*E9*/ {UNUSED,""}, /**/
		/*EA*/ {UNUSED,""}, /**/
		/*EB*/ {UNUSED,""}, /**/
		/*EC*/ {UNUSED,""}, /**/
		/*ED*/ {UNUSED,""}, /**/
		/*EE*/ {UNUSED,""}, /**/
		/*EF*/ {UNUSED,""}, /**/
		/*F0*/ {UNUSED,""}, /**/
		/*F1*/ {UNUSED,""}, /**/
		/*F2*/ {UNUSED,""}, /**/
		/*F3*/ {UNUSED,""}, /**/
		/*F4*/ {UNUSED,""}, /**/
		/*F5*/ {UNUSED,""}, /**/
		/*F6*/ {UNUSED,""}, /**/
		/*F7*/ {UNUSED,""}, /**/
		/*F8*/ {UNUSED,""}, /**/
		/*F9*/ {UNUSED,""}, /**/
		/*FA*/ {UNUSED,""}, /**/
		/*FB*/ {UNUSED,""}, /**/
	//largeScenery
		/*00*/ {USED,"SCOL "}, /*Roman colosseum [12]*/
		/*01*/ {USED,"SHS1 "}, /*house (townhouse, terraced) [6]*/
		/*02*/ {USED,"SSPX "}, /*Sphinx [8]*/
		/*03*/ {USED,"SHS2 "}, /*house (townhouse, sidewalk) [8]*/
		/*04*/ {USED,"SCLN "}, /*Colonnade [4]*/
		/*05*/ {USED,"SMH1 "}, /*Mine Hut #1 (2x2, two-story cabin w/junk) [4] */
		/*06*/ {USED,"SMH2 "}, /*Mine Hut #2 (2x2, one-story cabin w/junk) [4]*/
		/*07*/ {USED,"SVLC "}, /*Volcano [12]*/
		/*08*/ {USED,"SPYR "}, /*Pyramid [36] Note: the pyramid is "hollow" inside*/
		/*09*/ {USED,"SMN1 "}, /*Mine Shaft [6]*/
		/*0A*/ {USED,"SMB "}, /*Martian Building [4]*/
		/*0B*/ {USED,"SSK1 "}, /*Skeleton [2]*/
		/*0C*/ {USED,"SDN1 "}, /*Dinosaur #1 (T. Rex Brown) [2]*/
		/*0D*/ {USED,"SDN2 "}, /*Dinosaur #2 (T. Rex Green)[2]*/
		/*0E*/ {USED,"SDN3 "}, /*Dinosaur #3(Brontosaurus) [2]*/
		/*0F*/ {USED,"SIP "}, /*ice palace [4]*/
		/*10*/ {USED,"STB1 "}, /*castle tower square brown [1]*/
		/*11*/ {USED,"STB2 "}, /*castle tower tall brown [1]*/
		/*12*/ {USED,"STG1 "}, /*castle tower square grey [1]*/
		/*13*/ {USED,"STG2 "}, /*castle tower tall grey [1]*/
		/*14*/ {USED,"SCT "}, /*tent [1]*/
		/*15*/ {USED,"SOH1 "}, /*medieval house 1(1x1, medieval two-story square, c  )[1]*/
		/*16*/ {USED,"SOH2 "}, /*medieval house 2(1x1, medieval one-story square, c  )[1]*/
		/*17*/ {USED,"SOH3 "}, /*medieval house 3(1x1, medieval two-story round, c  )[1]*/
		/*18*/ {USED,"SGP "}, /*giant pumpkin (2x2, jack o'lantern)[4]*/
		/*19*/ {USED,"SSR "}, /*space rocket (with lauch pad/tower) [4]*/
		/*1A*/ {USED,"STH "}, /*town hall [4]*/
		/*1B*/ {USED,"SAH "}, /*urban house 1 (three-story pink) [4]*/
		/*1C*/ {USED,"SPS "}, /*gas station [4]*/
		/*1D*/ {USED,"SPG "}, /*pagoda [4]*/
		/*1E*/ {USED,"SOB "}, /*office block [4]*/
		/*1F*/ {USED,"SAH2 "}, /*urban house 2 (green w/round porch) [4]*/
		/*20*/ {USED,"SST "}, /*satellite [4]*/
		/*21*/ {USED,"SSH "}, /*space capsule [1]*/
		/*22*/ {USED,"SAH3 "}, /*tenement [1]*/
		/*23*/ {UNUSED,""}, /**/
		/*24*/ {UNUSED,""}, /**/
		/*25*/ {UNUSED,""}, /**/
		/*26*/ {UNUSED,""}, /**/
		/*27*/ {UNUSED,""}, /**/
		/*28*/ {UNUSED,""}, /**/
		/*29*/ {UNUSED,""}, /**/
		/*2A*/ {UNUSED,""}, /**/
		/*2B*/ {UNUSED,""}, /**/
		/*2C*/ {UNUSED,""}, /**/
		/*2D*/ {UNUSED,""}, /**/
		/*2E*/ {UNUSED,""}, /**/
		/*2F*/ {UNUSED,""}, /**/
		/*30*/ {UNUSED,""}, /**/
		/*31*/ {UNUSED,""}, /**/
		/*32*/ {UNUSED,""}, /**/
		/*33*/ {UNUSED,""}, /**/
		/*34*/ {UNUSED,""}, /**/
		/*35*/ {UNUSED,""}, /**/
		/*36*/ {UNUSED,""}, /**/
		/*37*/ {UNUSED,""}, /**/
		/*38*/ {UNUSED,""}, /**/
		/*39*/ {UNUSED,""}, /**/
		/*3A*/ {UNUSED,""}, /**/
		/*3B*/ {UNUSED,""}, /**/
		/*3C*/ {UNUSED,""}, /**/
		/*3D*/ {UNUSED,""}, /**/
		/*3E*/ {UNUSED,""}, /**/
		/*3F*/ {UNUSED,""}, /**/
		/*40*/ {UNUSED,""}, /**/
		/*41*/ {UNUSED,""}, /**/
		/*42*/ {UNUSED,""}, /**/
		/*43*/ {UNUSED,""}, /**/
		/*44*/ {UNUSED,""}, /**/
		/*45*/ {UNUSED,""}, /**/
		/*46*/ {UNUSED,""}, /**/
		/*47*/ {UNUSED,""}, /**/
		/*48*/ {UNUSED,""}, /**/
		/*49*/ {UNUSED,""}, /**/
		/*4A*/ {UNUSED,""}, /**/
		/*4B*/ {UNUSED,""}, /**/
		/*4C*/ {UNUSED,""}, /**/
		/*4D*/ {UNUSED,""}, /**/
		/*4E*/ {UNUSED,""}, /**/
		/*4F*/ {UNUSED,""}, /**/
		/*50*/ {UNUSED,""}, /**/
		/*51*/ {UNUSED,""}, /**/
		/*52*/ {UNUSED,""}, /**/
		/*53*/ {UNUSED,""}, /**/
		/*54*/ {UNUSED,""}, /**/
		/*55*/ {UNUSED,""}, /**/
		/*56*/ {UNUSED,""}, /**/
		/*57*/ {UNUSED,""}, /**/
		/*58*/ {UNUSED,""}, /**/
		/*59*/ {UNUSED,""}, /**/
		/*5A*/ {UNUSED,""}, /**/
		/*5B*/ {UNUSED,""}, /**/
		/*5C*/ {UNUSED,""}, /**/
		/*5D*/ {UNUSED,""}, /**/
		/*5E*/ {UNUSED,""}, /**/
		/*5F*/ {UNUSED,""}, /**/
		/*60*/ {UNUSED,""}, /**/
		/*61*/ {UNUSED,""}, /**/
		/*62*/ {UNUSED,""}, /**/
		/*63*/ {UNUSED,""}, /**/
		/*64*/ {UNUSED,""}, /**/
		/*65*/ {UNUSED,""}, /**/
		/*66*/ {UNUSED,""}, /**/
		/*67*/ {UNUSED,""}, /**/
		/*68*/ {UNUSED,""}, /**/
		/*69*/ {UNUSED,""}, /**/
		/*6A*/ {UNUSED,""}, /**/
		/*6B*/ {UNUSED,""}, /**/
		/*6C*/ {UNUSED,""}, /**/
		/*6D*/ {UNUSED,""}, /**/
		/*6E*/ {UNUSED,""}, /**/
		/*6F*/ {UNUSED,""}, /**/
		/*70*/ {UNUSED,""}, /**/
		/*71*/ {UNUSED,""}, /**/
		/*72*/ {UNUSED,""}, /**/
		/*73*/ {UNUSED,""}, /**/
		/*74*/ {UNUSED,""}, /**/
		/*75*/ {UNUSED,""}, /**/
		/*76*/ {UNUSED,""}, /**/
		/*77*/ {UNUSED,""}, /**/
		/*78*/ {UNUSED,""}, /**/
		/*79*/ {UNUSED,""}, /**/
		/*7A*/ {UNUSED,""}, /**/
		/*7B*/ {UNUSED,""}, /**/
		/*7C*/ {UNUSED,""}, /**/
		/*7D*/ {UNUSED,""}, /**/
		/*7E*/ {UNUSED,""}, /**/
		/*7F*/ {UNUSED,""}, /**/
	//walls
		/*00*/ {USED,"WMF"}, /*mesh fence*/
		/*01*/ {USED,"WHG"}, /*hedge*/
		/*02*/ {USED,"WSW"}, /*white railing*/
		/*03*/ {USED,"WFW1"}, /*wood panel fence*/
		/*04*/ {USED,"WPF"}, /*barb wire fence*/
		/*05*/ {USED,"WSW1"}, /*railing*/
		/*06*/ {USED,"WBR1"}, /*brick wall*/
		/*07*/ {USED,"WBR2"}, /*stone wall*/
		/*08*/ {USED,"WCH"}, /*conifer hedge*/
		/*09*/ {USED,"WC3"}, /*roman column wall*/
		/*0A*/ {USED,"WC7"}, /*castle tall with window brown*/
		/*0B*/ {USED,"WC11"}, /*castle tall with gate grey*/
		/*0C*/ {USED,"WC15"}, /*creepy gate*/
		/*0D*/ {UNUSED,""}, /**/
		/*0E*/ {UNUSED,""}, /**/
		/*0F*/ {UNUSED,""}, /**/
		/*10*/ {USED,"WMFG"}, /*mesh fence with gate (not available to user)*/
		/*11*/ {USED,"WHGG"}, /*hedge with gate (not available to user)*/
		/*12*/ {USED,"WSWG"}, /*white railing with gate (not available to user)*/
		/*13*/ {USED,"WFWG"}, /*wood panel fence with gate (not available to user)*/
		/*14*/ {USED,"WPFG"}, /*barb wire fence with gate (not available to user)*/
		/*15*/ {USED,"WSW2"}, /*iron railing with gate (not available to user)*/
		/*16*/ {USED,"WBRG"}, /*brick wall with gate (not available to user)*/
		/*17*/ {USED,"WBR3"}, /*stone wall with gate (not available to user)*/
		/*18*/ {USED,"WCHG"}, /*conifer hedge with gate (not available to user)*/
		/*19*/ {USED,"WC4"}, /*castle wall tall brown*/
		/*1A*/ {USED,"WC8"}, /*castle wall medium brown*/
		/*1B*/ {USED,"WC12"}, /*castel wall tall with window grey*/
		/*1C*/ {USED,"WC16"}, /*barb fence with snow*/
		/*1D*/ {UNUSED,""}, /**/
		/*1E*/ {UNUSED,""}, /**/
		/*1F*/ {UNUSED,""}, /**/
		/*20*/ {USED,"WRW"}, /*roman wall*/
		/*21*/ {USED,"WCW1"}, /*blue playing cards*/
		/*22*/ {USED,"WMW"}, /*martian wall*/
		/*23*/ {USED,"WPW1"}, /*wood post fence*/
		/*24*/ {USED,"WWTW"}, /*primitive wood fence - tall*/
		/*25*/ {USED,"WGW2"}, /*leaded glass*/
		/*26*/ {USED,"WFW1"}, /*white wood panel fence*/
		/*27*/ {USED,"WPW3"}, /*wooden fence*/
		/*28*/ {USED,"WC1"}, /*castle wall short brown*/
		/*29*/ {USED,"WC5"}, /*castle wall tall with cross brown*/
		/*2A*/ {USED,"WC9"}, /*castle wall tall grey*/
		/*2B*/ {USED,"WC13"}, /*castle wall medium grey*/
		/*2C*/ {USED,"WC17"}, /*wooden fence with snow*/
		/*2D*/ {UNUSED,""}, /**/
		/*2E*/ {UNUSED,""}, /**/
		/*2F*/ {UNUSED,""}, /**/
		/*30*/ {USED,"WEW"}, /*egyptian wall*/
		/*31*/ {USED,"WCW2"}, /*red playing card wall*/
		/*32*/ {USED,"WALLGL16"}, /*plate glass*/
		/*33*/ {USED,"WPW2"}, /*red-wood post fence*/
		/*34*/ {USED,"WMWW "}, /*primitive wood fence - short*/
		/*35*/ {USED,"WBW"}, /*bone fence*/
		/*36*/ {USED,"WFW1"}, /*red-wood panel fence*/
		/*37*/ {USED,"WJF"}, /*jungle fence*/
		/*38*/ {USED,"WC2"}, /*castle wall short grey*/
		/*39*/ {USED,"WC6"}, /*castle wall tall with gate brown*/
		/*3A*/ {USED,"WC10"}, /*castle wall tall with cross grey*/
		/*3B*/ {USED,"WC14"}, /*creepy wall*/
		/*3C*/ {USED,"WC18"}, /*post fence with snow*/
		/*3D*/ {UNUSED,""}, /**/
		/*3E*/ {UNUSED,""}, /**/
		/*3F*/ {UNUSED,""}, /**/
		/*40*/ {UNUSED,""}, /**/
		/*41*/ {UNUSED,""}, /**/
		/*42*/ {UNUSED,""}, /**/
		/*43*/ {UNUSED,""}, /**/
		/*44*/ {UNUSED,""}, /**/
		/*45*/ {UNUSED,""}, /**/
		/*46*/ {UNUSED,""}, /**/
		/*47*/ {UNUSED,""}, /**/
		/*48*/ {UNUSED,""}, /**/
		/*49*/ {UNUSED,""}, /**/
		/*4A*/ {UNUSED,""}, /**/
		/*4B*/ {UNUSED,""}, /**/
		/*4C*/ {UNUSED,""}, /**/
		/*4D*/ {UNUSED,""}, /**/
		/*4E*/ {UNUSED,""}, /**/
		/*4F*/ {UNUSED,""}, /**/
		/*50*/ {UNUSED,""}, /**/
		/*51*/ {UNUSED,""}, /**/
		/*52*/ {UNUSED,""}, /**/
		/*53*/ {UNUSED,""}, /**/
		/*54*/ {UNUSED,""}, /**/
		/*55*/ {UNUSED,""}, /**/
		/*56*/ {UNUSED,""}, /**/
		/*57*/ {UNUSED,""}, /**/
		/*58*/ {UNUSED,""}, /**/
		/*59*/ {UNUSED,""}, /**/
		/*5A*/ {UNUSED,""}, /**/
		/*5B*/ {UNUSED,""}, /**/
		/*5C*/ {UNUSED,""}, /**/
		/*5D*/ {UNUSED,""}, /**/
		/*5E*/ {UNUSED,""}, /**/
		/*5F*/ {UNUSED,""}, /**/
		/*60*/ {UNUSED,""}, /**/
		/*61*/ {UNUSED,""}, /**/
		/*62*/ {UNUSED,""}, /**/
		/*63*/ {UNUSED,""}, /**/
		/*64*/ {UNUSED,""}, /**/
		/*65*/ {UNUSED,""}, /**/
		/*66*/ {UNUSED,""}, /**/
		/*67*/ {UNUSED,""}, /**/
		/*68*/ {UNUSED,""}, /**/
		/*69*/ {UNUSED,""}, /**/
		/*6A*/ {UNUSED,""}, /**/
		/*6B*/ {UNUSED,""}, /**/
		/*6C*/ {UNUSED,""}, /**/
		/*6D*/ {UNUSED,""}, /**/
		/*6E*/ {UNUSED,""}, /**/
		/*6F*/ {UNUSED,""}, /**/
		/*70*/ {UNUSED,""}, /**/
		/*71*/ {UNUSED,""}, /**/
		/*72*/ {UNUSED,""}, /**/
		/*73*/ {UNUSED,""}, /**/
		/*74*/ {UNUSED,""}, /**/
		/*75*/ {UNUSED,""}, /**/
		/*76*/ {UNUSED,""}, /**/
		/*77*/ {UNUSED,""}, /**/
		/*78*/ {UNUSED,""}, /**/
		/*79*/ {UNUSED,""}, /**/
		/*7A*/ {UNUSED,""}, /**/
		/*7B*/ {UNUSED,""}, /**/
		/*7C*/ {UNUSED,""}, /**/
		/*7D*/ {UNUSED,""}, /**/
		/*7E*/ {UNUSED,""}, /**/
		/*7F*/ {UNUSED,""}, /**/
	//banners
		/*00*/ {USED,"BN1"}, /*standard*/
		/*01*/ {USED,"BN2"}, /*jungle(wooden)*/
		/*02*/ {USED,"BN3"}, /*classical*/
		/*03*/ {USED,"BN4"}, /*egyptian*/
		/*04*/ {USED,"BN5"}, /*mining*/
		/*05*/ {USED,"BN6"}, /*prehistoric(bone)*/
		/*06*/ {USED,"BN7"}, /*asian*/
		/*07*/ {USED,"BN8"}, /*snowy*/
		/*08*/ {USED,"BN9"}, /*space*/
		/*09*/ {UNUSED,""}, /**/
		/*0A*/ {UNUSED,""}, /**/
		/*0B*/ {UNUSED,""}, /**/
		/*0C*/ {UNUSED,""}, /**/
		/*0D*/ {UNUSED,""}, /**/
		/*0E*/ {UNUSED,""}, /**/
		/*0F*/ {UNUSED,""}, /**/
		/*10*/ {UNUSED,""}, /**/
		/*11*/ {UNUSED,""}, /**/
		/*12*/ {UNUSED,""}, /**/
		/*13*/ {UNUSED,""}, /**/
		/*14*/ {UNUSED,""}, /**/
		/*15*/ {UNUSED,""}, /**/
		/*16*/ {UNUSED,""}, /**/
		/*17*/ {UNUSED,""}, /**/
		/*18*/ {UNUSED,""}, /**/
		/*19*/ {UNUSED,""}, /**/
		/*1A*/ {UNUSED,""}, /**/
		/*1B*/ {UNUSED,""}, /**/
		/*1C*/ {UNUSED,""}, /**/
		/*1D*/ {UNUSED,""}, /**/
		/*1E*/ {UNUSED,""}, /**/
		/*1F*/ {UNUSED,""}, /**/
	//paths
		/*00*/ {USED,"TARMAC"}, /*light blue*/
		/*01*/ {USED,"PATHSPCE"}, /*red*/
		/*02*/ {USED,"TARMACB"}, /*yellow*/
		/*03*/ {USED,"TARMACG"}, /*light green*/
		/*04*/ {USED,"PATHDIRT"}, /*yellow*/
		/*05*/ {USED,"PATHASH"}, /*yellow*/
		/*06*/ {USED,"PATHCRZY"}, /*yellow*/
		/*07*/ {USED,"ROAD"}, /*no*/
		/*08*/ {USED,"JATLPTHT"}, /*bright orange*/
		/*09*/ {USED,"JATLPBLK"}, /*grey*/
		/*0A*/ {USED,"JATLPTR2"}, /*pink*/
		/*0B*/ {USED,"JATLPPCH"}, /*lime green*/
		/*0C*/ {UNUSED,""}, /**/
		/*0D*/ {UNUSED,""}, /**/
		/*0E*/ {UNUSED,""}, /**/
		/*0F*/ {UNUSED,""}, /**/
	//pathUtilities
		/*00*/ {USED,"LAMP1"}, /*single lamps*/
		/*01*/ {USED,"LAMP2"}, /*triple lamps*/
		/*02*/ {USED,"LITTER1"}, /*litter bins*/
		/*03*/ {USED,"BENCH1"}, /*benches*/
		/*04*/ {USED,"JUMPFNT1"}, /*jumping fountains*/
		/*05*/ {USED,"LAMP3"}, /*egyptian lamps*/
		/*06*/ {USED,"LAMP4"}, /*martian lamps*/
		/*07*/ {USED,"JUMPSNW1"}, /*jumping snowballs*/
		/*08*/ {UNUSED,""}, /**/
		/*09*/ {UNUSED,""}, /**/
		/*0A*/ {UNUSED,""}, /**/
		/*0B*/ {UNUSED,""}, /**/
		/*0C*/ {UNUSED,""}, /**/
		/*0D*/ {UNUSED,""}, /**/
		/*0E*/ {UNUSED,""}, /**/
	//groups
		/*00*/ {USED,"SCGFENCE"}, /*Fences and Walls*/
		/*01*/ {USED,"SCGGARDN"}, /*Gardens*/
		/*02*/ {USED,"SCGSHRUB"}, /*Shrubs and Ornaments*/
		/*03*/ {USED,"SCGPATHX"}, /*Signs and Items for Footpaths*/
		/*04*/ {USED,"SCGTREES"}, /*Trees*/
		/*05*/ {USED,"SCGWALLS"}, /*Walls and Roofs*/
		/*06*/ {USED,"SCGABSTR"}, /*Abstract Themeing*/
		/*07*/ {USED,"SCGCLASS"}, /*Classical/Roman Themeing*/
		/*08*/ {USED,"SCGEGYPT"}, /*Egyptian Themeing*/
		/*09*/ {USED,"SCGHALLO"}, /*Creepy Themeing*/
		/*0A*/ {USED,"SCGJUNGL"}, /*Jungle Themeing*/
		/*0B*/ {USED,"SCGJURAS"}, /*Jurassic Themeing*/
		/*0C*/ {USED,"SCGMART"}, /*Martian Themeing*/
		/*0D*/ {USED,"SCGMEDIE"}, /*Medieval Themeing*/
		/*0E*/ {USED,"SCGMINE"}, /*Mine Themeing*/
		/*0F*/ {USED,"SCGORIEN"}, /*Pagoda Themeing*/
		/*10*/ {USED,"SCGSNOW"}, /*Snow and Ice Themeing*/
		/*11*/ {USED,"SCGSPACE"}, /*Space Themeing*/
		/*12*/ {USED,"SCGSPOOK"}, /*Spooky Themeing*/
	//entrance
		/*00*/ {USED,"PKENT1 "}, /*Traditional Park Entrance */
	//palette
		/*00*/ {USED,"WTRCYAN "}, /*Natural Water */
	//scenarioText
		/*00*/ {UNUSED,""}, /**/
};

SV6_OBJDAT_HEADER redWater;

#define PATH_CONVERT_TABLE__NUM_ENTRIES 0x17

SV6_PATH_RCT1_TO_RCT2_MAPSTRUCT pathConvertTable[PATH_CONVERT_TABLE__NUM_ENTRIES]=
{
		/*00*/ {QUEUE,0x01,"TARMAC  "},  /*blue gueue*/
		/*01*/ {QUEUE,0x02,"PATHSPCE"},  /*red gueue*/
		/*02*/ {QUEUE,0x05,"PATHDIRT"},  /*yellow gueue*/
		/*03*/ {QUEUE,0x0C,"JATLPPCH"},  /*green gueue*/
		/*04*/ {PATH,0x01,"TARMAC  "},  /*grey tarmac*/
		/*05*/ {PATH,0x02,"PATHSPCE"},  /*red tarmac*/
		/*06*/ {PATH,0x03,"TARMACB "},  /*brown tarmac*/
		/*07*/ {PATH,0x04,"TARMACG "},  /*green tarmac*/
		/*08*/ {PATH,0x05,"PATHDIRT"},  /*dirt*/
		/*09*/ {PATH,0x06,"PATHASH "},  /*black dirt*/
		/*0A*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*0B*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*0C*/ {PATH,0x07,"PATHCRZY"},  /*crazy tile*/
		/*0D*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*0E*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*0F*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*10*/ {PATH,0x08,"ROAD    "},  /*road*/
		/*11*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*12*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*13*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /**/
		/*14*/ {PATH,0x09,"JATLPTHT"},  /*tile*/
		/*15*/ {PATH,0x0A,"JATLPBLK"},  /*grey tile*/
		/*16*/ {PATH,0x0B,"JATLPTR2"},  /*red tile*/
};

#define PATH_ADD_CONVERT_TABLE__NUM_ENTRIES 0x0F

SV6_PATH_RCT1_TO_RCT2_MAPSTRUCT pathAddConvertTable[PATH_ADD_CONVERT_TABLE__NUM_ENTRIES]=
{
	/*00*/ {EMPTYENTRY,0xFFFFFFFF,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"}, /*nothing*/
	/*01*/ {PATHADD,0x01,"LAMP1   "},  /*single lamps*/
	/*02*/ {PATHADD,0x02,"LAMP2   "},  /*triple lamps*/
	/*03*/ {PATHADD,0x03,"LITTER1 "},  /*litter bins*/
	/*04*/ {PATHADD,0x04,"BENCH1  "},  /*benches*/
	/*05*/ {PATHADD,0x05,"JUMPFNT1"},  /*jumping fountains*/
	/*06*/ {PATHADD,0x06,"LAMP3   "},  /*egyptian lamps*/
	/*07*/ {PATHADD,0x07,"LAMP4   "},  /*martian lamps*/
	/*08*/ {PA_VANDALIZED,0x01,"LAMP1   "},  /*vandalized single lamps*/
	/*09*/ {PA_VANDALIZED,0x02,"LAMP2   "},  /*vandalized triple lamps*/
	/*0A*/ {PA_VANDALIZED,0x03,"LITTER1 "},  /*vandalized liter bins*/
	/*0B*/ {PA_VANDALIZED,0x04,"BENCH1  "},  /*vandalized benches*/
	/*0C*/ {PA_VANDALIZED,0x06,"LAMP3   "},  /*vandalized egyptian lamps*/
	/*0D*/ {PA_VANDALIZED,0x07,"LAMP4   "},  /*vandalized martian lamps*/
	/*0E*/ {PATHADD,0x08,"JUMPSNW1"},  /*jumping snowballs*/
};

#define DATEXT ".DAT"
#define DATHEADER_FILEOFFSET 0

InitObjects()
{
	//Init object table based off datnames
	int 
		i,j,fh,bytesRead;
		
	char 
		path[FILESTRING_MAXSIZE],
		curFilename[FILESTRING_MAXSIZE],
		curDatName[16],
		aStr[32];

	GetRct2Path(path);
	strcat(path,"\\ObjData\\");

	#define curObj (RCT1emulationTableAlt->objs[i])
	#define curTblEntry (objStrTable[i])

	j=SV6_OBJDAT_NUMENTRIES_ALL;

	for(i=0;i<SV6_OBJDAT_NUMENTRIES_ALL;i++)
	{
		if(curTblEntry.usedFlag==USED)
		{
			trim_spec(curDatName,curTblEntry.objName," \t\xA0");

			//strcpy(curDatName,curTblEntry.objName);
			strcat(curDatName,DATEXT);
			strcpy(curFilename,path);
			strcat(curFilename,curDatName);

			
			if(FExist(curFilename))
			{
				bytesRead=
				QuickRead
				(	&curObj,curFilename,DATHEADER_FILEOFFSET,sizeof(curObj)
				);
			}
			else 
			{
				goto SetBlank;				
			}
		}
		else
		SetBlank:
		{
			memset(&curObj,0xff,sizeof(curObj));
		}		
	}

	RedWater_Set:
	{
		trim_spec(curDatName,"WTRRED"," \t\xA0");

		//strcpy(curDatName,curTblEntry.objName);
		strcat(curDatName,DATEXT);
		strcpy(curFilename,path);
		strcat(curFilename,curDatName);

		if(FExist(curFilename))
		{
			bytesRead=
			QuickRead
			(	&redWater,curFilename,DATHEADER_FILEOFFSET,sizeof(redWater)
			);
		}
		else 
		{
			memset(&redWater,0xff,sizeof(redWater));
		}

	}

	#undef curObj //(RCT1emulationTableAlt->objs[i])
	#undef curTblEntry //(objStrTable[i])

}
