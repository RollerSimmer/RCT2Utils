#pragma once

#define RCT_SVX

const BYTE RCTX_BYTE_EMPTY=0xff;
const BYTE RCTX_WORD_EMPTY=0xffff;
const BYTE RCTX_DWORD_EMPTY=0xffffffff;

typedef struct
{	WORD absmonth,day;	
} DATESTRUCT;

typedef struct{BYTE x,y;}RCTPOINT;

typedef struct
{
short
	WeatherTimer; 	
BYTE
	CurrentWeather,
	TargetWeather,
	CurrentTemp,
	TargetTemperature,
	Lightning,
	TargetLightning, 
	Shade,
	TargetShade,
	Rain,
	TargetRain;
}
	WEATHER;

typedef struct
{	short x,y;
	BYTE z,direction;
} 
	ENTRYPOINTSTRUCT;

typedef struct
{	short x,y,z;
	BYTE direction;
} MAINENTRANCE_LOCATIONSTRUCT;

typedef struct
{
	BYTE 
		weeksRemaining:4,
		unk4:4;
}ADVERT_BYTE;

typedef enum
{
	BANSTYL_STANDARD=0,
	BANSTYL_JUNGLE=1,
	BANSTYL_CLASSICAL=2,
	BANSTYL_EGYPTIAN=3,
	BANSTYL_MINING=4,
	BANSTYL_DINOBONE=5,
	BANSTYL_ASIAN=6,
	BANSTYL_SNOW=7,
	BANSTYL_SPACE=8,
	BANSTYL_UNUSED=0xff,
} BANNERSTYLE;

typedef struct
{
	BYTE 
		bannerStyle,
		noEntry;
	WORD
		stringIndex;
	BYTE 
		color,
		textColor,
		fill0x06[2];
}BANNERINFOSTRUCT;

typedef struct
{
	WORD
		awardWasWon,
		awardID;
}PARKAWARDSTRUCT;

typedef enum
{
	ANIM_RIDEENTRANCE=0,
	ANIM_EMPTY_FIRSTFREE=1,
	ANIM_SCENERY=2,
	ANIM_PARKENTRY=3,
	ANIM_RAPIDSRIDE_WATERFALL=4,
	ANIM_RAPIDSRIDE_RAPIDS=5,
	ANIM_RAPIDS=6,
	ANIM_RAPIDSRIDE_WHIRLPOOL=7,
	ANIM_SPINNINGTUNNEL=8,
	ANIM_GHOSTTRAIN_CARS_WINDOWS=9,
	ANIM_BANNER=0X0A,
} ANIMATION_OBJECTCODE;

typedef struct
{
	BYTE
		height,
		objectCode;
	WORD
		x,y;	
} ANIMATIONOBJECTLOCATION;

#define SPRITETYPES 6

typedef union
{	struct 
	{	unsigned short  
			nextFreeSprite,
			firstVehicle,
			firstPerson,
			firstFloat,
			firstJunk,
			firstOversizedRideCar,			
			availSprites,
			vehiCount, 
			peopleCount,
			floatingCount,
			junkCount,
			oversizedCount;
	} statsA;
	unsigned short statsB[2][SPRITETYPES];
} SPRITESTATS;


typedef enum
{		SPR_FREE=0,SPR_VEHI,SPR_PERSON,
		SPR_FLOAT,SPR_JUNK,SPR_OVERSIZED
}
SPRITETYPE;

#define MESSAGESTRUCTSIZE 268
#define NUMMESSAGES 61

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

typedef enum
{	RCT_EAST,
	RCT_SOUTH,
	RCT_WEST,
	RCT_NORTH
} RCT_DIRECTION;

//#if!defined(RCT2_CHUNK__H)

typedef enum
{
	ET_LITERAL,
	ET_RLE,
	ET_RLE_STRING,
	ET_ROTATE_1357,
	ET_AUTODETECT=0xff,
}
SVX_ENCODETYPE;

typedef struct
{
	BYTE encodeType;
	DWORD chunkSize_Encoded;
} SVX_CHUNKHEADER;

typedef union
{
	struct
	{
		WORD
		ofs:10,
		unk:5,
		isString:1;	
	};

	WORD v;
}
SVX__STRING_NAME_OFFSET;


//#endif

