#pragma once

short rct1shopTrack_MapTable[]=
{
/*0x1C -- Ice Cream Stall*/ 0x60,
/*0x1D -- Fries Stall*/ 0x61,
/*0x1E -- Drink Stall*/ 0x62,
/*0x1F -- Cotton Candy Stall*/ 0x63,
/*0x20 -- Burger Bar*/ 0x64,
/*0x22 -- Balloon Stall*/ 0x65,
/*0x23 -- Information Kiosk*/ 0x66,
/*0x24 -- Bathroom*/ 0x67,
/*0x2B -- Souvenir Stall*/ 0x68,
/*0x2D -- Pizza Stall*/ 0x69,
/*0x30 -- Popcorn Stall*/ 0x6A,
/*0x37 -- Hot Dog Stall*/ 0x6B,
/*0x38 -- Exotic Sea-Food Stall*/ 0x6C,
/*0x39 -- Hat Stall*/ 0x6D,
/*0x3A -- Candy Apple Stand*/ 0x6E,
/*0x4E -- T-shirt Stall*/ 0x6F,
/*0x50 -- Donut Shop*/ 0x70,
/*0x52 -- Coffee Shop*/ 0x71,
/*0x53 -- Fried Chicken Stall*/ 0x72,
/*0x54 -- Lemonade Stall*/ 0x73
};

const int 
NUM_RCT1_SHOPS
=sizeof(rct1shopTrack_MapTable)
/sizeof(rct1shopTrack_MapTable[0])
;

short rct1shopTrack_MapTable_indexConvert(int i)
{
switch(i)
{
case 0x1C:return(0);
case 0x1D:return(1);
case 0x1E:return(2);
case 0x1F:return(3);
case 0x20:return(4);
case 0x22:return(5);
case 0x23:return(6);
case 0x24:return(7);
case 0x2B:return(8);
case 0x2D:return(9);
case 0x30:return(10);
case 0x37:return(11);
case 0x38:return(12);
case 0x39:return(13);
case 0x3A:return(14);
case 0x4E:return(15);
case 0x50:return(16);
case 0x52:return(17);
case 0x53:return(18);
case 0x54:return(19);
}
return(NUM_RCT1_SHOPS);
}


typedef struct
{
	short mapIndex;
	bool isShop;
	bool allTrackConvertsSame;
}
RCT1_TRACK_TYPE_CONVERT_TABLE;

RCT1_TRACK_TYPE_CONVERT_TABLE
rct1TrackTypeConvertTable[]
=
{
/*0x0 --  Wooden Roller Coaster*/
{0x34,0,1},
/*0x1 --  Stand-Up Steel Roller Coaster*/
{0x1,0,1},
/*0x2 --  Suspended Roller Coaster*/
{0x2,0,1},


/*0x3 --  Inverted Roller Coaster*/
{0x3,0,1},
/*0x4 --  Steel Mini Roller Coaster*/
{0x4,0,0},

/*0x5 --  Miniature Railroad*/
{0x5,0,1},



/*0x6 --  Monorail*/
{0x6,0,1},


/*0x7 --  Suspended Single-Rail Roller Coaster*/
{0x7,0,1},

/*0x8 --  Boat Hire*/
{0x8,0,1},





/*0x9 --  Wooden Crazy Rodent Roller Coaster*/
{0x9,0,1},

/*0x0A --  Single-Rail Roller Coaster*/
{0x0A,0,1},


/*0x0B --  Car Ride*/
{0x0B,0,1},





/*0x0C -- Whoa Belly*/
{0x0C,0,1},
/*0x0D -- Bobsled Roller Coaster*/
{0x0D,0,1},

/*0x0E -- Observation Tower*/
{0x0E,0,1},

/*0x0F -- Steel Roller Coaster*/
{0x0F,0,1},
/*0x10 -- Water Slide*/
{0x10,0,1},
/*0x11 --  Mine Train Roller Coaster*/
{0x11,0,1},
/*0x12 --  Chairlift*/
{0x12,0,1},

/*0x13 --  Steel Corkscrew Roller Coaster*/
{0x13,0,1},

/*0x14 --  Hedge Maze*/
{0x14,0,1},
/*0x15 --  Spiral Slide */
{0x15,0,1},
/*0x16 --  Go Karts*/
{0x16,0,1},
/*0x17 --  Log Flume*/
{0x17,0,1},
/*0x18 --  River Rapids*/
{0x18,0,1},
/*0x19 --  Bumper Cars */
{0x19,0,1},
/*0x1A --  Swinging Ship */
{0x1A,0,1},
/*0x1B -- Swinging Inverter Ship*/
{0x1B,0,1},
/*0x1C -- Ice Cream Stall */
{0x20,1,0},
/*0x1D -- Fries Stall */
{0x20,1,0},
/*0x1E -- Drink Stall */
{0x20,1,0},
/*0x1F -- Cotton Candy Stall */
{0x20,1,0},
/*0x20 -- Burger Bar */
{0x20,1,0},
/*0x21 -- Merry-Go-Round */
{0x21,0,1},
/*0x22 -- Balloon Stall */
{0x20,1,0},
/*0x23 -- Information Kiosk */
{0x20,1,0},
/*0x24 -- Bathroom */
{0x20,1,0},
/*0x25 -- Ferris Wheel */
{0x25,0,1},
/*0x26 -- Motion Simulator*/
{0x26,0,1},
/*0x27 -- 3D Cinema*/
{0x27,0,1},
/*0x28 -- Gravitron */
{0x28,0,1},
/*0x29 -- Space Rings*/
{0x29,0,1},
/*0x2A -- Reverse Whoa Belly Roller Coaster*/
{0x2A,0,1},
/*0x2B -- Souvenir Stall */
{0x20,1,0},
/*0x2C -- Vertical Roller Coaster*/
{0x2C,0,1},
/*0x2D -- Pizza Stall */
{0x20,1,0},
/*0x2E -- Scrambled Eggs */
{0x2E,0,1},

/*0x2F -- Haunted House */
{0x2F,0,1},
/*0x30 -- Popcorn Stall */
{0x20,1,0},
/*0x31 -- Circus Show */
{0x31,0,1},
/*0x32 -- Ghost Train */
{0x32,0,1},

/*0x33 --  Steel Twister Roller Coaster */
{0x33,0,1},




/*0x34 -- Wooden Twister Roller Coaster*/
{0x34,0,1},



/*0x35 --  Wooden Side-Friction Roller Coaster*/
{0x35,0,1},
/*0x36 -- Steel Wild Mouse Roller Coaster  */
{0x36,0,1},


/*0x37 --  Hot Dog Stall */
{0x20,1,0},
/*0x38 --  Exotic Sea-Food Stall */
{0x20,1,0},
/*0x39 --  Hat Stall */
{0x20,1,0},
/*0x3A --  Candy Apple Stand */
{0x20,1,0},
/*0x3B --  Virginia Reel */
{0x3B,0,1},
/*0x3C --  River Ride */
{0x3C,0,1},
/*0x3D --  Cycle Monorail */
{0x3D,0,1},
/*0x3E --  Flying Roller Coaster */
{0x3E,0,1},
/*0x3F --  Suspended Monorail */
{0x3F,0,1},
/*0x40 -- (reserved) */
{0x40,0,1},
/*0x41 --  Wooden Reverser Roller Coaster */
{0x41,0,1},
/*0x42 --  Heartline Twister Roller Coaster */
{0x42,0,1},

/*0x43 --  Miniature Golf */
{0x43,0,1},
/*0x44 --  (reserved)*/
{0x44,0,1},
/*0x45 --  Roto-Drop */
{0x45,0,1},
/*0x46 -- Flying Saucers */
{0x46,0,1},
/*0x47 -- Crooked House */
{0x47,0,1},
/*0x48 --  Cycle Railway */
{0x48,0,1},
/*0x49 --  Suspended Looping Roller Coaster */
{0x49,0,1},


/*0x4A --  Water Coaster*/
{0x4A,0,1},
/*0x4B --  Air Powered Vertical Coaster */
{0x4B,0,1},
/*0x4C --  Inverted Wild Mouse Coaster */
{0x4C,0,1},
/*0x4D -- Jet Skis */
{0x8,0,1},
/*0x4E --  T-shirt Stall */
{0x20,1,0},
/*0x4F --  Raft Ride */
{0x4F,0,1},
/*0x50 --  Doughnut Shop */
{0x20,1,0},
/*0x51 --  Enterprise */
{0x51,0,1},
/*0x52 --  Coffee Shop */
{0x20,1,0},
/*0x53 --  Fried Chicken Stall */
{0x20,1,0},
/*0x54 --  Lemonade Stall */
{0x20,1,0},
/*0x55 --  */
{0x55,0,1},
/*0x56 --  */
{0x56,0,1},
/*0x57 --  */
{0x57,0,1},


/*0x58 --  */
{0x58,0,1},
/*0x59 -- */
{0x59,0,1},
/*0x5A --  */
{0x5A,0,1}
}
;

short rct1shop_trackIDTable[NUM_RCT1_SHOPS]
=
{
/*0x1C -- Ice Cream Stall*/ 0x1C ,
/*0x1D -- Fries Stall*/ 0x1C ,
/*0x1E -- Drink Stall*/ 0x1E,
/*0x1F -- Cotton Candy Stall*/ 0x1C ,
/*0x20 -- Burger Bar*/ 0x1C ,
/*0x22 -- Balloon Stall*/ 0x1C ,
/*0x23 -- Information Kiosk*/ 0x23,
/*0x24 -- Bathroom*/ 0x24,
/*0x2B -- Souvenir Stall*/ 0x20,
/*0x2D -- Pizza Stall*/ 0x1C ,
/*0x30 -- Popcorn Stall*/ 0x1C ,
/*0x37 -- Hot Dog Stall*/ 0x1C ,
/*0x38 -- Exotic Sea-Food Stall*/ 0x1C ,
/*0x39 -- Hat Stall*/ 0x20,
/*0x3A -- Candy Apple Stand*/ 0x1C ,
/*0x4E -- T-shirt Stall*/ 0x20,
/*0x50 -- Donut Shop*/ 0x1C ,
/*0x52 -- Coffee Shop*/ 0x1E,
/*0x53 -- Fried Chicken Stall*/ 0x1C ,
/*0x54 -- Lemonade Stall*/ 0x1E
}
;

short GetMiniCoasterTrack(short v)
{
switch(v)
{
//ladybird
case 0x05:
//log
case 0x34:
	return(0x04);
//rocket
case 0x11:
//
default:
	return(0x57);
}
}