#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Label.h
	created:	2012/03/31
	author:		LB
	purpose:	标牌类
\*********************************************************************/

#include "ODLEx_Element_TextArea.h"

class ODLEX_EXPORT CODLEx_Element_Label :
	public CODL_OverlayElementBase
{
protected:
	POINT				m_AnchorPosition;		//锚点位置
	POINT				m_Pos;
	RECT				m_Rect;
	CODL_Pen*			m_pBorderPen;
	CODL_Brush*			m_pBkBrush;
	DWORD				m_dwMeatusWidth;		//开口宽度
	POINT				m_pMeatusPoints[4];
	LONG				m_lMargin;

	DWORD				m_dwRowCount;
	DWORD				m_dwColCount;
protected:
	BOOL				m_bDraging;
	POINT				m_ptDragOffset;

protected:
	BOOL				m_bShowTitle;
	BOOL				m_bShowBorder;
	CODLEx_Element_TextArea*	m_pTitle;		//
	CODL_ObjListBase	m_theTextList;
public:
	CODLEx_Element_Label(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Label(void);
public:
	virtual BOOL						Init(DWORD IN dwRows,DWORD IN dwCols);
	virtual VOID						SetPos(LONG IN x,LONG IN y);
	virtual POINT*						GetPos(){return &m_Pos;}
	virtual POINT*						GetAnchorPos(){return &m_AnchorPosition;}
	virtual VOID						SetAnchorPos(LONG IN x,LONG IN y);
	virtual VOID						SetBorderStyle(UINT IN uStyle,UINT IN uWidth,COLORREF IN clr);
	virtual VOID						ShowBorder(BOOL IN bShow);
	virtual VOID						SetMargin(LONG IN lMargin){m_lMargin=lMargin;Invalidate();}
	virtual LONG						GetMargin(){return m_lMargin;}
	
	virtual VOID						SetBkColor(COLORREF IN clr);
	virtual COLORREF					GetBkColor();
	
	virtual VOID						SetTitle(LPCSTR IN pTitle);
	virtual VOID						ShowTitle(BOOL IN bShow);

	virtual VOID						SetText(DWORD IN dwRowIndex,DWORD IN dwColIndex, LPCSTR IN pText);
	virtual VOID						SetTextColor(DWORD IN dwRowIndex,DWORD IN dwColIndex,COLORREF IN clr);
	virtual VOID						SetTextFont(DWORD IN dwRowIndex,DWORD IN dwColIndex,LPCSTR IN pFontName,DWORD IN dwFontSize,DWORD IN dwFontWeight);
	virtual VOID						SetTextAlign(DWORD IN dwRowIndex,DWORD IN dwColIndex,UINT IN uAlign);
	virtual VOID						SetTextBkColor(DWORD IN dwRowIndex,DWORD IN dwColIndex,COLORREF IN clr);
	virtual SIZE						GetTextMaxSize(HDC IN hDC);

	virtual CODLEx_Element_TextArea*	GetTitleTextObject();
	virtual CODLEx_Element_TextArea*	GetTextObject(DWORD IN dwRowIndex,DWORD IN dwColIndex);

public:
	virtual VOID						GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL						OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL						OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL						PtInElement(POINT IN pt);
protected:
	virtual BOOL						GetMeatusPoints();

};
