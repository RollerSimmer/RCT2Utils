#ifndef ISO_H
#define ISO_H

#include<stdlib.h>

typedef struct 
ISOMETRIC_TILE_VECTOR
{
	short x,y;
	//ISOMETRIC_TILE_VECTOR(){x=0;y=0;}
	ISOMETRIC_TILE_VECTOR Set(short x,short y)
	{
		this->x=x;
		this->y=y;
		return(*this);
	}
	ISOMETRIC_TILE_VECTOR operator*(int scale)
	{	ISOMETRIC_TILE_VECTOR v;
		v.x=x*scale;v.y=y*scale;return v;
	}
	ISOMETRIC_TILE_VECTOR operator/(int scale)
	{	ISOMETRIC_TILE_VECTOR v;
		v.x=x/scale;v.y=y/scale;return v;
	}
	ISOMETRIC_TILE_VECTOR operator+(ISOMETRIC_TILE_VECTOR v2)
	{	ISOMETRIC_TILE_VECTOR v=*this;
		v.x+=v2.x;v.y+=v2.y;return v;
	}
	ISOMETRIC_TILE_VECTOR operator-(ISOMETRIC_TILE_VECTOR v2)
	{	ISOMETRIC_TILE_VECTOR v=*this;
		v.x-=v2.x;v.y-=v2.y;return v;
	}
	ISOMETRIC_TILE_VECTOR operator-()
	{	ISOMETRIC_TILE_VECTOR v=*this;
		v.x=-v.x;v.y=-v.y;return v;
	}
	ISOMETRIC_TILE_VECTOR operator*=(int scale)
	{	return((*this)=(*this)*scale);	}
	ISOMETRIC_TILE_VECTOR operator/=(int scale)
	{	return((*this)=(*this)/scale);	}
	ISOMETRIC_TILE_VECTOR operator+=(ISOMETRIC_TILE_VECTOR v2)
	{	return((*this)=(*this)+v2);	}
	ISOMETRIC_TILE_VECTOR operator-=(ISOMETRIC_TILE_VECTOR v2)
	{	return((*this)=(*this)-v2);	}
	bool operator>=(ISOMETRIC_TILE_VECTOR v)
	{	return((x>=v.x)&&(y>=v.y));	}
	bool operator<=(ISOMETRIC_TILE_VECTOR v)
	{	return((x<=v.x)&&(y<=v.y));	}
	bool InBox(ISOMETRIC_TILE_VECTOR nw,ISOMETRIC_TILE_VECTOR se)
	{	
		ISOMETRIC_TILE_VECTOR
			tse,tnw;

		tnw.Set(__min(se.x,nw.x),__min(se.y,nw.y));
		tse.Set(__max(se.x,nw.x),__max(se.y,nw.y));

		return((*this>=tnw)&&(*this<=tse));	
	}
}
	ISOMETRIC_TILE_VECTOR;
	
#define RCT2__ISO_TILE__XSTEP 32
#define RCT2__ISO_TILE__YSTEP 16
#define TILE_XSTEP RCT2__ISO_TILE__XSTEP
#define TILE_YSTEP RCT2__ISO_TILE__YSTEP

enum
{
	VIEW_SE=0,
	VIEW_NE,
	VIEW_NW,
	VIEW_SW
};

ISOMETRIC_TILE_VECTOR
	isoColInc[4]=
	{
		{TILE_XSTEP,TILE_YSTEP},//SE <o>
		{-TILE_XSTEP,TILE_YSTEP},//NE <o>
		{-TILE_XSTEP,-TILE_YSTEP},//NW <o>
		{TILE_XSTEP,-TILE_YSTEP}//SW <o>
	},
	isoRowInc[4]=
	{
		{-TILE_XSTEP,TILE_YSTEP},//SE <o>
		{-TILE_XSTEP,-TILE_YSTEP},//NE <o>
		{TILE_XSTEP,-TILE_YSTEP},//NW <o>
		{TILE_XSTEP,TILE_YSTEP}//SW <o>
	},
	isoOrigin,
	rotColInc[4]=
	{
		{1,0},//SE <o>
		{0,1},//NE <o>
		{-1,0},//NW <o>
		{0,-1}//SW <o>
	},
	rotRowInc[4]=
	{
		{0,1},//SE <o>
		{-1,0},//NE <o>
		{0,-1},//NW <o>
		{1,0}//SW <o>
	},
	rotOrigin,
	zBakInc[4]=
	{
		{-1,-1},//SE <o>
		{-1,1},//NE <o>
		{1,1},//NW <o>
		{1,-1}//SW <o>
	};



#endif