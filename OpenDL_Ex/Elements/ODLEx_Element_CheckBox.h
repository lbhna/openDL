#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_CheckBox.h
	created:	2012/04/23
	author:		LB
	purpose:	¸´Ñ¡¿ò
\*********************************************************************/


class ODLEX_EXPORT CODLEx_Element_CheckBox :
	public CODL_ElementBase
{
protected:
	POINT					m_Pos;
	SIZE					m_Size;

	CHAR*					m_pText;
	COLORREF				m_TextBkColor;
	BOOL					m_bShowTextBkColor;

	BOOL					m_bChecked;

	CODL_Font*				m_pTextFont;
	COLORREF				m_TextColor;

	CODL_Pen*				m_pBlackFramePen;
	CODL_Pen*				m_pWhiteFramePen;
	CODL_Brush*				m_pBkBrush;
	CODL_Brush*				m_pSelectBtnBrush;
	CODL_Brush*				m_pTextBkBrush;

protected:
	POINT					m_ptDragOffset;

	BOOL					m_bEnableAdjustSize;
	BOOL					m_bAdjustSizeing;

	BOOL					m_bEnableDrag;
	BOOL					m_bDraging;
	BOOL					m_bPushed;



public:
	CODLEx_Element_CheckBox(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_CheckBox(void);
public:
	VOID				SetPos(LONG IN x,LONG IN y);
	POINT*				GetPos(){return &m_Pos;}
	VOID				SetSize(LONG IN cx,LONG IN cy);
	SIZE*				GetSize(){return &m_Size;}
	VOID				SetText(LPCSTR IN pText);
	LPCSTR				GetText(){return m_pText;}

	VOID				SetCheck(BOOL IN bCheck);
	BOOL				IsChecked(){return m_bChecked;}

	VOID				SetFont(CHAR* IN pFontName,DWORD IN dwFontSize,COLORREF IN FontColor);
	VOID				SetFont(LOGFONT* IN pLF);

	VOID				SetTextColor(COLORREF IN clr);
	VOID				SetBkColor(COLORREF IN clr);
	VOID				EnableShowBkColor(BOOL IN bShowBkColor);

	VOID				SetCheckBoxFgColor(COLORREF IN clr);
	VOID				SetCheckBoxBkColor(COLORREF IN clr);
	VOID				SetDarkFrameColor(COLORREF IN clr);
	VOID				SetLightFrameColor(COLORREF IN clr);

public:
	virtual RECT*		GetRect(RECT* IN OUT pRec);
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);
	virtual VOID		EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	virtual VOID		EnableAdjustSize(BOOL IN bEnable);
	virtual BOOL		IsEnableAdjustSize(){return m_bEnableAdjustSize;}
	virtual BOOL		PtInElement(POINT IN pt);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);

};
