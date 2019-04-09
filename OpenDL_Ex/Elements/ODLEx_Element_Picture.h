#pragma once
/*====================================================================\
		#创建日期:	2015/02/06
		#文件名  :	ODLEx_Element_Picture
		#作者    :	LBHNA   
		#说明    :	图片类
\====================================================================*/
#include "gdiplus.h"
using namespace Gdiplus;

#include "ODLEx_Element_Tips.h"

class ODLEX_EXPORT CODLEx_Element_Picture :
	public CODL_ElementBase
{
protected:
	POINT						m_Pos;
	SIZE						m_Size;
	FLOAT						m_fCourse;//角度
	CODL_Brush*					m_pBkBrush;
protected:
	CODL_Image*					m_pImage;
	Graphics*					m_pGraphics;
	ImageAttributes				m_ImageAttribute;
	SIZE						m_ImageSize;
	HDC							m_hDeviceDC;
	BOOL						m_bEnableTransparentColor;
	COLORREF					m_TransparentColorLow;
	COLORREF					m_TransparentColorHigh;
	BYTE						m_Alpha;
	ColorMatrix					m_ColorMatrix;

protected:
	BOOL						m_bMouseOver;
	CODLEx_Element_Tips*		m_pTips;
protected:
	POINT						m_ptDragOffset;
	BOOL						m_bEnableDrag;
	BOOL						m_bDraging;
	BOOL						m_bPushed;

	BOOL						m_bEnableAdjustSize;
	BOOL						m_bAdjustSizeing;
	CODL_Pen*					m_pFramePen;

public:
	CODLEx_Element_Picture(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Picture(void);
public:
	PSIZE				GetImageSize();
	PSIZE				GetSize();
	PPOINT				GetPos();
	FLOAT				GetCourse();
	VOID				GetTransparentColor(COLORREF& OUT clrLow,COLORREF& OUT clrHigh);
	BOOL				IsEnableTransparentColor();
	VOID				SetFramePen(LOGPEN* IN lp);
	VOID				SetBkBrush(LOGBRUSH* IN lb);
public:
	VOID				SetPos(POINT& IN pos);
	VOID				SetPos(LONG IN x,LONG IN y);

	VOID				SetAlpha(BYTE IN alpha);
	BYTE				GetAlpha();

	VOID				SetSize(SIZE& IN size);
	VOID				SetSize(LONG IN cx,LONG IN cy);
	VOID				SetSizeMatchedImage();

	VOID				SetTransparentColor(COLORREF OUT clrLow,COLORREF OUT clrHigh);
	VOID				SetCourse(FLOAT IN fCourse);//角度

	VOID				EnableTransparentColor(BOOL IN bEnable);

	VOID				GetRect(RECT& OUT rect);
	VOID				SetTips(LPCSTR IN pText);



public:
	virtual BOOL		SetImage(LPCSTR IN pFileName);
	virtual BOOL		SetImage(LPVOID IN pData,DWORD IN dwDataSize);
	virtual BOOL		SetImage(CODL_Image* IN pImage);

public:
	virtual VOID		EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);
	virtual VOID		EnableAdjustSize(BOOL IN bEnable){m_bEnableAdjustSize=bEnable;}
	virtual BOOL		IsEnableAdjustSize(){return m_bEnableAdjustSize;}


	virtual VOID		OnMouseOver();
	virtual VOID		OnMouseOut();

	virtual BOOL		PtInElement(POINT IN pt);
	virtual VOID		GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
};

