#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Tips.h
	created:	2012/04/23
	author:		LB
	purpose:	工具条提示
\*********************************************************************/


class ODLEX_EXPORT CODLEx_Element_Tips :
	public CODL_ElementBase
{
protected:
	POINT				m_Pos;
	CHAR*				m_pText;

	CODL_Pen*			m_pBorderPen;
	CODL_Font*			m_pTextFont;
	COLORREF			m_TextColor;
	CODL_Brush*			m_pBkBrush;
public:
	CODLEx_Element_Tips(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Tips(void);
public:
	VOID				SetPos(LONG IN x,LONG IN y);
	VOID				SetText(LPCSTR IN pText);
	VOID				SetTextColor(COLORREF IN clr);
	VOID				SetTextFont(LPCSTR IN pFontName,DWORD IN dwFontSize);
	VOID				SetBorderStyle(UINT IN uPenStyle,UINT IN uWidth,COLORREF IN clr);
	VOID				SetBackgroundStyle(UINT IN uBrushStyle,COLORREF IN clr);
public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};
