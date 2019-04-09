#pragma once
#include "./ODL_ElementBase.h"

/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Elements\ODL_OverlayElementBase.h
	created:	2012/04/13
	author:		LB
	purpose:	有透明效果的图元基类
\*********************************************************************/

class ODL_EXPORT CODL_OverlayElementBase :
	public CODL_ElementBase
{
protected:
	HBITMAP				m_hBitmap;
	HDC					m_hBitmapDC;
	RECT				m_BitmapRect;
	BYTE				m_Alpha;
public:
	CODL_OverlayElementBase(CODL_CanvasBase* IN pCanvas);
	virtual ~CODL_OverlayElementBase(void);
public:
	BYTE				GetAlpha(){return m_Alpha;}
	VOID				SetAlpha(BYTE IN Alpha){m_Alpha=Alpha;Invalidate();}
public:
	virtual VOID		GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL		Draw(HDC IN hDC,RECT* IN pPaintRect);
protected:
	virtual BOOL		ResetAlphaBitmap(HDC IN hDC,RECT* IN pPaintRect);
};
