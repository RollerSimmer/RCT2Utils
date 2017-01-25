#ifndef SVX_H
#define SVX_H

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
}WEATHER;

typedef struct
{	short x,y;
	BYTE z,direction;
} ENTRYPOINTSTRUCT;

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

#endif //SVX_H
