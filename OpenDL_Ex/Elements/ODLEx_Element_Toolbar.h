#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Toolbar.h
	created:	2012/03/23
	author:		LB
	purpose:	工具条类
\*********************************************************************/
#include "ODLEx_Element_CheckButton.h"

class ODLEX_EXPORT CODLEx_Element_Toolbar :
	public CODL_ElementBase
{
protected:
	CODLEx_Element_Button*						m_pCurActiveButton;
	CODL_ListT<CODLEx_Element_Button*>			m_theButtonList;

	POINT										m_Pos;
	SIZE										m_ButtonSize;


	RECT										m_BkRect;
	COLORREF									m_BkColor;
	CODL_Brush*									m_pBkBrush;
	CODL_Pen*									m_pDragbarPen;
	LONG										m_lDragbarWidth;

protected:
	BOOL										m_bDraging;
	POINT										m_ptDragOffset;
	BOOL										m_bExpand;
public:
	CODLEx_Element_Toolbar(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Toolbar(void);
public:
	VOID							SetPos(LONG IN x,LONG IN y);
	POINT*							GetPos(){return &m_Pos;}
	VOID							SetButtonSize(LONG IN cx,LONG IN cy);
	SIZE*							GetButtonSize(){return &m_ButtonSize;}

	BOOL							AddButton(CODLEx_Element_Button* IN pButton);
	CODLEx_Element_Button*			GetFirstButton(POSITION& IN pos);
	CODLEx_Element_Button*			GetNextButton(POSITION& IN pos);
	CODLEx_Element_Button*			FindButton(DWORD IN dwBtnID);
	VOID							Clear();

	VOID							SetBkColor(COLORREF IN clr);
	VOID							GetSize(LONG& OUT cx,LONG& OUT cy);


public:
	virtual BOOL					OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL					OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
protected:
	virtual VOID					OnButtonClicked(CODLEx_Element_Button* IN pButton);
	virtual VOID					RelayoutButton();
protected:
	BOOL							PtInDragBar(POINT* IN pt);
	VOID							DrawBkground(HDC IN hDC,RECT* IN pPaintRect);
	BOOL							PtInExpandBar(POINT* IN pt);
};
