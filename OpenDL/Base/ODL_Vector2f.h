#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Base\ODL_Vector2f.h
	created:	2012/03/13
	author:		LB
	purpose:	二维向量类
\*********************************************************************/
#include "GlobalDefine.h"
#include <math.h>

class ODL_EXPORT CODL_Vector2f
{
public:
	FLOAT			x;
	FLOAT			y;
public:
	CODL_Vector2f(void);
	CODL_Vector2f(FLOAT IN X,FLOAT IN Y);
	~CODL_Vector2f(void);
public:
	CODL_Vector2f operator-(){return CODL_Vector2f(-x,-y);}
	CODL_Vector2f operator=(CODL_Vector2f& v) {x =v.x;y=v.y;return *this;}

	CODL_Vector2f operator+(CODL_Vector2f v){ return CODL_Vector2f(x+v.x,y+v.y);}
	CODL_Vector2f operator-(CODL_Vector2f v){ return CODL_Vector2f(x-v.x,y-v.y);}
	CODL_Vector2f operator*(CODL_Vector2f v){ return CODL_Vector2f(x*v.x,y*v.y);}
	CODL_Vector2f operator/(CODL_Vector2f v){ return CODL_Vector2f(x/v.x,y/v.y);}

	CODL_Vector2f operator+(FLOAT v){ return CODL_Vector2f(x + v,y + v);}
	CODL_Vector2f operator-(FLOAT v){ return CODL_Vector2f(x - v,y - v);}
	CODL_Vector2f operator*(FLOAT v){ return CODL_Vector2f(x * v,y * v);}
	CODL_Vector2f operator/(FLOAT v){ return CODL_Vector2f(x / v,y / v);}


	void operator+=(CODL_Vector2f v){ x += v.x;y += v.y;}
	void operator-=(CODL_Vector2f v){ x -= v.x;y -= v.y;}
	void operator*=(CODL_Vector2f v){ x *= v.x;y *= v.y;}
	void operator/=(CODL_Vector2f v){ x /= v.x;y /= v.y;}

	void operator+=(FLOAT v){ x += v;y += v;}
	void operator-=(FLOAT v){ x -= v;y -= v;}
	void operator*=(FLOAT v){ x *= v;y *= v;}
	void operator/=(FLOAT v){ x /= v;y /= v;}

public:
	FLOAT		SqrtLength()
	{
		return x*x + y*y;
	}
	FLOAT		Length()
	{
		return sqrt(x*x+y*y);
	}
	BOOL		Normalize()
	{
		float length =Length();
		if( fabs(length) < 1e-38 )
			return FALSE;
		float lenrcp = 1.0f/length;
		x = x * lenrcp;
		y = y * lenrcp;
		return TRUE;
	}
	BOOL		Normalize(CODL_Vector2f& OUT v)
	{
		float length =Length();
		if( fabs(length) < 1e-38 )
			return FALSE;
		float lenrcp = 1.0f/length;
		v.x = x * lenrcp;
		v.y = y * lenrcp;
		return TRUE;
	}

	FLOAT		Dot(CODL_Vector2f& IN v)
	{
		return (x*v.y - y*v.x);
	}

	CODL_Vector2f	GetCross()
	{
		CODL_Vector2f	tmp(x,y);
		tmp.Normalize();
		return CODL_Vector2f(tmp.y,-tmp.x);
	}
public:
	BOOL	f_equal(FLOAT f1, FLOAT f2)
	{
		return (fabs(f1 - f2) < 1e-4f); 
	}
	BOOL operator==(CODL_Vector2f &v) 
	{ 
		return (f_equal(x, v.x) && f_equal(y, v.y)); 
	} 
	BOOL operator>(CODL_Vector2f &v) 
	{ 
		return (x > v.x || (f_equal(x, v.x) && y > v.y)); 
	} 
	FLOAT operator^(CODL_Vector2f &v) 
	{ 
		return Dot(v);
	} 
};
