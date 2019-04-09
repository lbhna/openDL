#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Report.h
	created:	2012/04/23
	author:		LB
	purpose:	列表控件
\*********************************************************************/

#include "ODLEx_Element_ReportRow.h"
#include "ODLEx_Element_ScrollBar.h"

class ODLEX_EXPORT CODLEx_Element_Report :
	public CODL_OverlayElementBase
{
protected:
	POINT							m_Pos;
	SIZE							m_Size;

	BOOL							m_bShowHeader;			//是否显示表头
	POINT							m_DrawOffset;

	BOOL							m_bShowHorizontalGrid;
	BOOL							m_bShowVerticalGrid;

	CODL_Brush*						m_pBkBrush;
protected:
	POINT							m_ptDragOffset;
	BOOL							m_bEnableDrag;
	BOOL							m_bDraging;

	BOOL							m_bEnableAdjustSize;
	BOOL							m_bAdjustSizeing;
protected:
	CODLEx_Element_ReportRow*		m_pHeader;				//表头
	CODL_ObjListBase				m_theRowsList;			//表体
	CODLEx_Element_ScrollBar*		m_pHorizontalScrollbar;
	CODLEx_Element_ScrollBar*		m_pVerticalScrollbar;
	CODLEx_Element_ReportRow*		m_pCurrentSelected;

public:
	CODLEx_Element_Report(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Report(void);

public:
	CODLEx_Element_Report*			SetPos(LONG IN x,LONG IN y);
	POINT*							GetPos();
	CODLEx_Element_Report*			SetSize(LONG IN cx,LONG IN cy);
	SIZE*							GetSize();
	CODLEx_Element_Report*			SetRows(LONG IN lRows);
	CODLEx_Element_Report*			SetCols(LONG IN lCols);
	LONG							GetRows();
	LONG							GetCols();

	CODLEx_Element_Report*			ShowHeader(BOOL IN bShow);
	BOOL							IsShowHeader();
	CODLEx_Element_Report*			SetBkBrush(LOGBRUSH* IN lb);
	CODL_Brush*						GetBkBrush();

	CODLEx_Element_Report*			EnableShowHorizontalGrid(BOOL IN bEnable);
	CODLEx_Element_Report*			EnableShowVerticalGrid(BOOL IN bEnable);
	CODLEx_Element_Report*			SetVerticalGridPen(LOGPEN* IN lp);
	CODLEx_Element_Report*			SetHorizontalGridPen(LOGPEN* IN lp);

public:

	CODLEx_Element_ScrollBar*		GetHorizontalScrollBar();
	CODLEx_Element_ScrollBar*		GetVerticalScrollBar();
	CODLEx_Element_ReportRow*		GetHeader();
	CODLEx_Element_ReportRow*		GetRow(LONG IN lRow);
	CODLEx_Element_ReportItem*		GetItem(LONG IN lRow,LONG IN lCol);

	CODLEx_Element_ReportRow*		GetCurrentSelect();
	VOID							SetCurrentSelect(CODLEx_Element_ReportRow* IN pRow);

	CODLEx_Element_Report*			EnsureVisible(LONG IN lRowIndex,LONG IN lColIndex=0);

	CODLEx_Element_Report*			SetRowBkBrush(LONG IN lRow,LOGBRUSH* IN lb);
	CODLEx_Element_Report*			SetColBkBrush(LONG IN lCol,LOGBRUSH* IN lb);
	CODLEx_Element_Report*			SetRowFont(LONG IN lRow,LOGFONT* IN lf);
	CODLEx_Element_Report*			SetColFont(LONG IN lCol,LOGFONT* IN lf);
	CODLEx_Element_Report*			SetRowTextColor(LONG IN lRow,COLORREF IN clr);
	CODLEx_Element_Report*			SetColTextColor(LONG IN lCol,COLORREF IN clr);

	CODLEx_Element_Report*			SetRowHeight(LONG IN lRow,LONG IN lHeight);
	CODLEx_Element_Report*			SetColWidth(LONG IN lCol,LONG IN lWidth);






	CODLEx_Element_ReportRow*		InsertRow(LONG IN lInsertBefore);
	CODLEx_Element_Report*			DeleteRow(LONG IN lIndex);
	CODLEx_Element_Report*			InsertCol(LONG IN lInsertBefore);
public:
	virtual VOID					GetClientRect(RECT& OUT rect);
	virtual VOID					GetRect(RECT& OUT rect);
	virtual BOOL					OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL					OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual VOID					GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);

	virtual VOID					EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	virtual BOOL					PtInAdjustSizeButton(POINT* IN pt);
	virtual VOID					EnableAdjustSize(BOOL IN bEnable){m_bEnableAdjustSize=bEnable;}
	virtual BOOL					IsEnableAdjustSize(){return m_bEnableAdjustSize;}
	virtual BOOL					PtInElement(POINT IN pt);

protected:
	virtual	VOID					RecalcLayout();
	VOID							GetNeedDrawRow(LONG& OUT lStart,LONG& OUT lEnd);
};
