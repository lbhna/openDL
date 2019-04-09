#pragma once
#include "./ODL_ElementBase.h"
/*====================================================================\
		#创建日期:	2015/02/11
		#文件名  :	ODL_LayerElementBase
		#作者    :	LBHNA   
		#说明    :	有层属性的元素基类
\====================================================================*/

class ODL_EXPORT CODL_LayerElementBase:
	public CODL_ElementBase
{
protected:
	POINT					m_Pos;
	SIZE					m_Size;
	HBITMAP					m_hBitmap;
	HDC						m_hBitmapDC;
	RECT					m_BitmapRect;
	CODL_ObjListBase		m_theChildElements;
public:
	CODL_LayerElementBase(CODL_CanvasBase* IN pCanvas);
	virtual ~CODL_LayerElementBase();
public:
	virtual VOID			SetPos(LONG IN x,LONG IN y);
	PPOINT					GetPos();
	virtual VOID			SetSize(LONG IN cx,LONG IN cy);
	PSIZE					GetSize();
public:
	virtual	VOID			AddChild(CODL_ElementBase* IN pChild);
	virtual VOID			DelChild(LONG IN lIndex);
	virtual VOID			DelChild(CODL_ElementBase* IN pChild);
	virtual CODL_ElementBase*GetChild(LONG IN lIndex);
	virtual LONG			GetChildCount();
	virtual VOID			ClearChild();
public:
	virtual BOOL			IsInvalidate();
	virtual BOOL			Draw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL			OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL			OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
protected:
	BOOL					ResetBitmap(HDC IN hDC);

};
