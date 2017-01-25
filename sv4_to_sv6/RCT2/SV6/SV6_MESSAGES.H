//SV6_MESSAGES.H=symbol

#ifndef SV6_MESSAGES_H
#define SV6_MESSAGES_H

#define RCT2_MSGCOLOR_WHITE		0x90	
#define RCT2_MSGCOLOR_RED		0x91
#define RCT2_MSGCOLOR_GREEN		0x92
#define RCT2_MSGCOLOR_GOLD		0x93
#define RCT2_MSGCOLOR_BROWN		0x94
#define RCT2_MSGCOLOR_GREY		0x95
#define RCT2_MSGCOLOR_BLUE		0x96
#define RCT2_MSGCOLOR_PURPLE	0x97
#define RCT2_MSGCOLOR_BEIGE		0x98
#define RCT2_MSGCOLOR_PINK		0x99
#define RCT2_MSGCOLOR_AGUA		0x9A
#define RCT2_MSGCOLOR_TAN		0x9B
#define RCT2_MSGCOLOR_GREEN2	0x9C

#define RCT2_MSGICON_HIDE		0
#define RCT2_MSGICON_RIDE		1
#define RCT2_MSGICON_PERSON		2
#define RCT2_MSGICON_COINS		3
#define RCT2_MSGICON_BLANK		5
#define RCT2_MSGICON_SCENERY	6
#define RCT2_MSGICON_CROWD		7
#define RCT2_MSGICON_AWARD		8
#define RCT2_MSGICON_GRAPH		9

#define MESSAGESTRUCTSIZE 268
#define NUMMESSAGES 61

#ifndef MESSAGESTRUCT_DEFINED
#define MESSAGESTRUCT_DEFINED

typedef struct
{
	BYTE
		icon,				//000
		fill001;			//001
	short 
		item;				//002
	BYTE 
		fill004[2],			//004
		lettersDisplayed,	//006
		fill007;			//007
	short 
		month,				//008
		day;				//00A			
	BYTE 
		color,				//00C
		text[255];			//00D
}
MESSAGESTRUCT,MESSAGESTRUCTARRAY[NUMMESSAGES];

#endif //MESSAGESTRUCT_DEFINED

#endif //SV6_MESSAGES_H
