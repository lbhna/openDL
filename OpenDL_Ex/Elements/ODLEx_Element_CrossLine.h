#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_CrossLine.h
	created:	2012/03/23
	author:		LB
	purpose:	Ê®×ÖÏßÀà
\*********************************************************************/

class ODLEX_EXPORT CODLEx_Element_CrossLine :
	public CODL_ElementBase
{
protected:
	CODL_Pen*			m_pLinePen;
	CODL_Font*			m_pTextFont;
	COLORREF			m_TextColor;
	COLORREF			m_TextBkColor;
	LONG				m_lPosition;

public:
	CODLEx_Element_CrossLine(CODL_CanvasBase* IN pCanvas);
	~CODLEx_Element_CrossLine(void);
public:
	VOID				SetLineParameter(UINT IN nPenStyle,UINT IN nPenWidth,COLORREF IN clr);
	VOID				SetTextParameter(LPCSTR IN pFontName,UINT IN nFontSize,COLORREF IN FontColor,COLORREF IN BkColor);

	VOID				SetLinePen(LOGPEN* IN lp);
	VOID				SetLineFont(LOGFONT* IN lf);
	VOID				SetLineTextColor(COLORREF IN clr);
	VOID				SetLineTextBkColor(COLORREF IN clr);

public:
	virtual VOID		MoveLeft(LONG IN lCount);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
protected:
	BOOL				OnKeyDown(WPARAM wp,LPARAM lp);
};
