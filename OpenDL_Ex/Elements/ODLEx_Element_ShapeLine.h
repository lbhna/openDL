#pragma once

/*====================================================================\
		#创建日期:	2015/06/02
		#文件名  :	ODLEx_Element_ShapeLine
		#作者    :	LBHNA   
		#说明    :	矢量线类
\====================================================================*/
#include "./ODLEx_Element_ShapeBase.h"


class ODLEX_EXPORT CODLEx_Element_ShapeLine:
	public CODLEx_Element_ShapeBase
{
protected:
	CODL_Vector2f		m_vStart;
	CODL_Vector2f		m_vEnd;
	POINT				m_ptStartOffset;
	POINT				m_ptEndOffset;


	BOOL				m_bAdjustStartPoint;

public:
	CODLEx_Element_ShapeLine(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ShapeLine();
public:
	VOID				SetStartPoint(FLOAT IN x,FLOAT IN y);
	CODL_Vector2f*		GetStartPoint();
	VOID				SetEndPoint(FLOAT IN x,FLOAT IN y);
	CODL_Vector2f*		GetEndPoint();
	VOID				GetPoint(POINT& OUT start,POINT& OUT end);
public:
	virtual VOID		SetShapeCoordinate(ODL_SHAPE_COORD IN coord);	
	virtual VOID		GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL		PtInElement(POINT IN pt);
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};
