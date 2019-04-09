#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Button.h
	created:	2012/03/23
	author:		LB
	purpose:	按钮类
\*********************************************************************/
#include "ODLEx_Element_Tips.h"



class ODLEX_EXPORT CODLEx_Element_Button :
	public CODL_ElementBase
{
protected:
	CODL_Pen*				m_pNormalPen;
	CODL_Pen*				m_pHighlightPen;
	CODL_Brush*				m_pBkBrush;
	CODL_Brush*				m_pActiveBkBrush;


	POINT					m_Pos;		//按钮位置
	SIZE					m_Size;		//按钮大小

	BOOL					m_bPushed;	//是否被按下
	BOOL					m_bEnable;

	HICON					m_hIcon;
	CHAR*					m_pTitle;
	COLORREF				m_TitleColor;
	CODL_Font*				m_pTitleFont;
	DWORD					m_dwTextAlign;

protected:
	BOOL					m_bMouseOver;
	CODLEx_Element_Tips*	m_pTips;
protected:
	POINT					m_ptDragOffset;

	BOOL					m_bEnableAdjustSize;
	BOOL					m_bAdjustSizeing;

	BOOL					m_bEnableDrag;
	BOOL					m_bDraging;


protected:
	BTN_CLICKED_CALLBACK	m_pClickedCallbackFunction;
	DWORD_PTR				m_CallbackUserData;
public:
	CODLEx_Element_Button(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Button(void);
public:
	INT					SetParameter(DWORD IN borderWidth ,COLORREF IN borderColor,COLORREF IN borderHighlightColor,COLORREF IN bkColor,COLORREF IN activeBkColor);
	VOID				SetClickedCallback(BTN_CLICKED_CALLBACK IN callbackFunction,DWORD_PTR IN UserData=0);
	DWORD				GetTextAlign(){return m_dwTextAlign;}
	VOID				SetTextAlign(DWORD IN dwAlign);

	VOID				SetTitle(LPCSTR IN pTitle);
	VOID				SetTitleFont(LOGFONT* IN lf);
	VOID				SetTitleColor(COLORREF IN clr);

	VOID				SetTitle(LPCSTR IN pTitle,LPCSTR IN pTitleFontName,DWORD IN dwFontSize,COLORREF IN TitleColor);
	VOID				SetIcon(HICON IN hIcon);
	VOID				Enable(BOOL IN bEnable){m_bEnable=bEnable;Invalidate();}
	BOOL				IsEnable(){return m_bEnable;}
	CODLEx_Element_Tips*GetTips(){return m_pTips;}
	VOID				SetTips(CODLEx_Element_Tips* IN pTips);
	VOID				SetTips(LPCSTR IN pText);

public:
	virtual VOID		SetPos(LONG IN x,LONG IN y);
	virtual VOID		SetSize(LONG IN cx,LONG IN cy);
	virtual POINT*		GetPos(){return &m_Pos;}
	virtual SIZE*		GetSize(){return &m_Size;}
	virtual RECT*		GetRect(RECT* IN OUT pRec);
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);

	virtual VOID		EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	virtual VOID		EnableAdjustSize(BOOL IN bEnable);
	virtual BOOL		IsEnableAdjustSize(){return m_bEnableAdjustSize;}


public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL		PtInElement(POINT IN pt);
protected:
	virtual VOID		DrawNormalBorder(HDC IN hDC);
	virtual VOID		DrawPushedBorder(HDC IN hDC);
protected:
	virtual BOOL		OnClicked();
	virtual VOID		OnMouseOver();
	virtual VOID		OnMouseOut();

};
