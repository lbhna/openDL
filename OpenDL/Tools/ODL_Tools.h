#pragma once
#include "../Base/ODL_Vector2f.h"

/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Tools\ODL_Tools.h
	created:	2012/04/12
	author:		LB
	purpose:	��ع��ߺ���
\*********************************************************************/
#define DOUBLE_PI			3.1415926535897932




typedef struct _ODL_POINT
{
	LONG	x;
	LONG	y;
	DWORD	flag;
}ODL_POINT;

class ODL_EXPORT CODL_LineStrip
{//�߶���
public:
	CODL_Vector2f		StartPoint;
	CODL_Vector2f		EndPoint;
public:
	CODL_LineStrip()
	{
	}
	CODL_LineStrip(POINT start,POINT end)
	{
		StartPoint.x	=start.x;
		StartPoint.y	=start.y;
		EndPoint.x		=end.x;
		EndPoint.y		=end.y;
	}
	CODL_LineStrip(CODL_Vector2f start,CODL_Vector2f end)
	{
		StartPoint.x	=start.x;
		StartPoint.y	=start.y;
		EndPoint.x		=end.x;
		EndPoint.y		=end.y;
	}
	void				SetPoint(CODL_Vector2f start,CODL_Vector2f end)
	{
		StartPoint.x	=start.x;
		StartPoint.y	=start.y;
		EndPoint.x		=end.x;
		EndPoint.y		=end.y;
	}
	CODL_Vector2f		GetVector()
	{
		CODL_Vector2f	v;
		v =EndPoint - StartPoint;
		v.Normalize();
		return v;
	}
	CODL_Vector2f		GetCrossVector()
	{//�õ���������
		CODL_Vector2f	v;
		v =EndPoint - StartPoint;
		return v.GetCross();
	}
	FLOAT				Length()
	{//�õ��߶γ���
		CODL_Vector2f	v;
		v =EndPoint - StartPoint;
		return v.Length();
	}
	BOOL				IsValid()
	{
		return !(StartPoint == EndPoint);
	}
	BOOL				operator==(CODL_LineStrip& v)
	{
		return (StartPoint == v.StartPoint && EndPoint == v.EndPoint);
	}
	FLOAT				Dot(CODL_LineStrip& v)
	{
		CODL_Vector2f	v1 =GetVector();
		CODL_Vector2f	v2 =v.GetVector();
		return v1.Dot(v2);
	}
};

struct  ODL_EXPORT LINE
{//�߶νṹ
	ODL_POINT	start;
	ODL_POINT	end;
};
class ODL_EXPORT CODL_Tools
{
public:
	CODL_Tools(void);
	~CODL_Tools(void);

public:
	static BOOL		GetLineIntersectRect(LINE IN OUT *pLine,RECT IN *pCutRect);
	static BOOL		IsIntersectRect(LINE IN *pLine,RECT IN *pRect);//�ж����Ƿ�������ཻ
	static LONG		PointInLine(LINE IN *pLine,POINT IN *pPoint);//����0 ��point���߶��ϣ�-1����1����
	static void		InsertCutRectPoint(RECT IN *pCutRect,LINE IN *pLine,POINT IN *pPoint,LONG IN OUT &result_count);
	static DWORD	RectCutPolyLine(RECT IN *pCutRect,ODL_POINT IN *pPointArray,LONG IN lPointCount,ODL_POINT IN OUT **pResultPoint);

	static VOID		AngleToDirect(DOUBLE IN fAngle,CODL_Vector2f& IN OUT vAt,CODL_Vector2f& IN OUT vRight);		//�Ƕ�ת��������
	static DOUBLE	DirectToAngle(CODL_Vector2f IN vAt);								//��������ת�Ƕ�
	static VOID		RotateVectorCoord(CODL_Vector2f& IN OUT vec,DOUBLE IN fAngle);
	static VOID		RotateVectorNormal(CODL_Vector2f& IN OUT vec,DOUBLE IN fAngle);

	static LPWSTR	WideChar(LPCSTR IN pStr);
	static LPSTR	MultiChar(LPCWSTR IN pStr);
};
