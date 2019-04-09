#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_CurveCase.h
	created:	2012/04/25
	author:		LB
	purpose:	ÇúÏßµÄÍ¼ÀýÀà
\*********************************************************************/
#include "ODLEx_Element_CurveBase.h"

class ODLEX_EXPORT CODLEx_Element_CurveCase :
	public CODL_ElementBase
{
protected:
	POINT						m_Pos;
	SIZE						m_Size;
	RECT						m_BoxRect;
	RECT						m_TextRect;
	CODLEx_Element_CurveBase*	m_pCurve;
	CODL_Font*					m_pFont;
	COLORREF					m_TextColor;
	COLORREF					m_SelectTextColor;
	LONG						m_LineLength;

	CODL_Brush*					m_pBkBrush;
	CODL_Brush*					m_pSelectBtnBrush;
	CODL_Pen*					m_pBlackFramePen;
	CODL_Pen*					m_pWhiteFramePen;

	DWORD						m_dwXPrecision;
	DWORD						m_dwYPrecision;

	BOOL						m_bShowLastDataText;
public:
	CODLEx_Element_CurveCase(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_CurveCase(void);
public:
	virtual VOID		Init(HDC IN hDC,CODLEx_Element_CurveBase* IN pCanvas);
	SIZE*				GetSize(){return &m_Size;}
	VOID				SetPos(LONG IN x,LONG IN y){m_Pos.x =x;m_Pos.y =y;Invalidate();}
	POINT*				GetPos(){return &m_Pos;}
	VOID				SetCaseLineLength(LONG IN lLen);
	
	VOID				SetFont(LPCSTR IN pFontName,UINT IN uFontSize);
	VOID				SetColor(COLORREF IN normalColor,COLORREF IN selectedColor);
	VOID				SetPrecision(DWORD IN dwXPrecision,DWORD IN dwYPrecision);
	VOID				EnableShowLastDataText(BOOL IN bEnable){m_bShowLastDataText=bEnable;}
public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
};
