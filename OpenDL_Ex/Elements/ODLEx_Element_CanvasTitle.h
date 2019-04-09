#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_CanvasTitle.h
	created:	2012/04/27
	author:		LB
	purpose:	画布的标题栏类
\*********************************************************************/


class ODLEX_EXPORT CODLEx_Element_CanvasTitle :
	public CODL_ElementBase
{
protected:
	POINT					m_Pos;
	CODL_Pen*				m_pBorderPen;
	CODL_Brush*				m_pBkBrush;
	CODL_Font*				m_pFont;
	COLORREF				m_TitleColor;
	RECT					m_TitleRect;
	BOOL					m_bFixHeight;
	LONG					m_lTitleHeight;
public:
	CODLEx_Element_CanvasTitle(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_CanvasTitle(void);
public:
	VOID					SetPos(LONG IN x,LONG IN y);
	VOID					SetBorderStyle(UINT IN uStyle,UINT IN uWidth,COLORREF IN clr);
	VOID					SetBackgroundStyle(UINT IN uStyle,UINT IN uHatch,COLORREF IN clr);
	VOID					SetFont(CHAR* pFontName,DWORD IN dwSize,DWORD IN dwWeight=500);
	VOID					SetFont(LOGFONT* IN pLf);
	VOID					SetTitleColor(COLORREF IN clr);
	VOID					SetTitleHeight(LONG IN lHeight,BOOL IN bFixed);//如果bFixed为TRUE，则完全按设定值为高度，如果为FALSE，则高度小于字体高度时自动适应字体

public:
	const LPPOINT			GetPos();
	const LPLOGPEN			GetBorderStyle();
	const LPLOGBRUSH		GetBackgroundStyle();
	const LPLOGFONT			GetFont();
	COLORREF				GetTitleColor();
	LONG					GetTitleHeight();

public:
	virtual BOOL			OnDraw(HDC IN hDC,RECT* IN pPaintRect);
};
