#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_TextArea.h
	created:	2012/03/31
	author:		LB
	purpose:	文本区域类
\*********************************************************************/

class ODLEX_EXPORT CODLEx_Element_TextArea :
	public CODL_OverlayElementBase
{
protected:
	CODL_Pen*				m_pBorderPen;
	CODL_Brush*				m_pBkBrush;
	CODL_Font*				m_pFont;
	COLORREF				m_TextColor;

	LONG					m_lMargin;
	POINT					m_Pos;
	SIZE					m_Size;
	BOOL					m_bFixedSize;

	CHAR*					m_pText;
	BOOL					m_bShowBorder;
	BOOL					m_bShowBkColor;
	UINT					m_uTextAlign;
	

protected:
	BOOL					m_bEnableDrag;
	BOOL					m_bDraging;
	POINT					m_ptDragOffset;
	BOOL					m_bEnableAdjustSize;
	BOOL					m_bAdjustSizeing;
	BOOL					m_bPushed;
public:
	CODLEx_Element_TextArea(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_TextArea(void);
public:
	virtual VOID			SetPos(LONG IN x,LONG IN y);
	virtual LPPOINT			GetPos(){return &m_Pos;}
	virtual VOID			SetSize(LONG IN cx,LONG IN cy);
	virtual PSIZE			GetSize(){return &m_Size;}
	virtual BOOL			IsFixedSize(){return m_bFixedSize;}
	virtual VOID			EnableFixedSize(BOOL IN bEnable){m_bFixedSize=bEnable;Invalidate();}
	virtual VOID			SetTextColor(COLORREF IN clr);
	virtual COLORREF		GetTextColor();
	virtual VOID			SetMargin(LONG IN lMargin){m_lMargin=lMargin;Invalidate();}
	virtual LONG			GetMargin(){return m_lMargin;}
	virtual VOID			SetText(LPCSTR IN pText);
	virtual LPCSTR			GetText(){return m_pText;}
	virtual VOID			SetTextFont(LPCSTR IN pFontName,DWORD IN dwFontSize,DWORD IN dwFontWeight=500);
	virtual VOID			SetTextFont(LOGFONT* IN pLf);
	virtual LOGFONT* 		GetTextFont(){return m_pFont->GetLogFont();}
	virtual VOID			SetTextAlign(UINT IN uAlign);
	virtual VOID			SetBkColor(COLORREF IN clr);
	virtual VOID			SetBorder(COLORREF IN borderColor,DWORD IN dwBorderWidth,DWORD IN dwBorderStyle=PS_SOLID);
	virtual VOID			GetRect(HDC IN hDC,RECT* OUT pRect);
	virtual VOID			EnableShowBorder(BOOL IN bEnable);
	virtual VOID			EnableShowBkColor(BOOL IN bEnable);
	virtual VOID			EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	virtual VOID			EnableAdjustSize(BOOL IN bEnable);
	virtual BOOL			IsEnableAdjustSize(){return m_bEnableAdjustSize;}
	virtual BOOL			PtInAdjustSizeButton(POINT* IN pt);
public:
	virtual VOID			GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL			PtInElement(POINT IN pt);
	virtual BOOL			OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL			OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);

};
