#pragma once

/*====================================================================\
		#创建日期:	2015/06/02
		#文件名  :	ODLEx_Element_ShapeRectangle
		#作者    :	LBHNA   
		#说明    :	矢量矩形类
\====================================================================*/

#include "./ODLEx_Element_ShapeBase.h"

class ODLEX_EXPORT CODLEx_Element_ShapeRectangle:
	public CODLEx_Element_ShapeBase
{
protected:
	CODL_Vector2f		m_vPos;
	CODL_Vector2f		m_vSize;

	BOOL				m_bRoundRect;
	CODL_Vector2f		m_vRoundSize;

	
public:
	CODLEx_Element_ShapeRectangle(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ShapeRectangle();

	
public:
	VOID				SetPos(FLOAT IN x,FLOAT IN y);
	CODL_Vector2f*		GetPos();
	VOID				SetSize(FLOAT IN cx,FLOAT IN cy);
	CODL_Vector2f*		GetSize();
	BOOL				IsRoundRect();
	VOID				EnableRoundRect(BOOL IN bEnable);
	VOID				SetRoundSize(FLOAT IN cx,FLOAT IN cy);
	CODL_Vector2f*		GetRoundSize();

	VOID				GetRect(RECT& OUT rect);


public:
	virtual VOID		SetShapeCoordinate(ODL_SHAPE_COORD IN coord);	
	virtual VOID		GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);
	virtual BOOL		PtInElement(POINT IN pt);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};
