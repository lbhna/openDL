#pragma once

/*====================================================================\
		#创建日期:	2015/07/09
		#文件名  :	ODLEx_Element_LedDigital
		#作者    :	LBHNA   
		#说明    :	LED数字显示控件
\====================================================================*/





class ODLEX_EXPORT CODLEx_Element_LedDigital:
	public CODL_OverlayElementBase
{
protected:
	CODL_Brush*					m_pBrightBrush;
	CODL_Brush*					m_pDarkBrush;
	CODL_Brush*					m_pBkBrush;

protected:
	POINT						m_Pos;
	SIZE						m_Size;
	CString						m_strValue;
	LONG						m_lMargin;
	LONG						m_lPadding;

	POINT						m_Points[7][6];
	LONG						m_PointsCount[7];
protected:
	POINT						m_ptDragOffset;
	BOOL						m_bEnableDrag;
	BOOL						m_bDraging;
	BOOL						m_bEnableAdjustSize;
	BOOL						m_bAdjustSizeing;
	BOOL						m_bPushed;
public:
	CODLEx_Element_LedDigital(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_LedDigital();
public:
	VOID				SetBrush(LOGBRUSH* IN pBrightBrush,LOGBRUSH* IN pDarkBrush);
	VOID				SetBrush(CODL_Brush* IN pBrightBrush,CODL_Brush* IN pDarkBrush);
	VOID				SetBkBrush(LOGBRUSH* IN pBkBrush);
	VOID				SetBkBrush(CODL_Brush* IN pBkBrush);
	LPCSTR				GetValue();
	VOID				SetValue(LPCSTR IN pValues/*0~9/-/:/.*/);
	VOID				SetPos(LONG IN x,LONG IN y);
	VOID				SetSize(LONG IN cx,LONG IN cy);
	POINT*				GetPos();
	SIZE*				GetSize();
	VOID				GetRect(RECT& OUT rect);
	LONG				GetMargin();
	VOID				SetMargin(LONG IN lMargin);
	LONG				GetPadding();
	VOID				SetPadding(LONG IN lPadding);
public:
	virtual VOID		GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual VOID		EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	virtual VOID		EnableAdjustSize(BOOL IN bEnable);
	virtual BOOL		IsEnableAdjustSize(){return m_bEnableAdjustSize;}
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);
	virtual BOOL		PtInElement(POINT IN pt);

protected:
	VOID				UpdatePoints();
	VOID				DrawLedDigital(HDC IN hDC,POINT* IN Pos,CHAR IN ch);
};