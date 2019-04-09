#pragma once

/*====================================================================\
		#创建日期:	2015/05/12
		#文件名  :	ODLEx_Element_ReportRow
		#作者    :	LBHNA   
		#说明    :	报表行类
\====================================================================*/
#include "ODLEx_Element_ReportItem.h"

class ODLEX_EXPORT CODLEx_Element_Report;
class ODLEX_EXPORT CODLEx_Element_ReportRow:
	public CODL_ElementBase
{
protected:
	CODLEx_Element_Report*			m_pReport;
	POINT							m_Pos;
	SIZE							m_Size;
	CODL_DirtyRect					m_DirtyRect;
	CODL_ObjListBase				m_theItemsList;
	RECT							m_DrawClip;			//
	LONG							m_lItemsSize;			//项长度和
	COLORREF						m_DefaultTextColor;		//默认文本颜色
	CODL_Font*						m_pDefaultFont;			//默认字体 

	BOOL							m_bShowHorizontalGrid;	//是否显示水平方向网格线
	CODL_Pen*						m_pHorizontalGridPen;	//水平方向网格线画笔
	BOOL							m_bShowVerticalGrid;	//是否显示垂直方向网格线
	CODL_Pen*						m_pVerticalGridPen;		//垂直方向网格线画笔
	CODL_Brush*						m_pBkBrush;

protected:
	HBITMAP							m_hBitmap;
	HDC								m_hBitmapDC;
	RECT							m_BitmapRect;
public:
	CODLEx_Element_ReportRow(CODLEx_Element_Report*IN pReport,CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ReportRow();

public:
	CODLEx_Element_ReportRow*		SetPos(LONG IN x,LONG IN y);
	POINT*							GetPos();
	CODLEx_Element_ReportRow*		SetSize(LONG IN cx,LONG IN cy);
	SIZE*							GetSize();
	LONG							GetItemTotalSize();
	CODLEx_Element_Report*			GetReport();

	CODLEx_Element_ReportRow*		SetItemCount(LONG IN lCount);
	LONG							GetItemCount();
	CODLEx_Element_ReportItem*		InsertItem(LONG IN lInsertBefore);

	CODLEx_Element_ReportItem*		GetItem(LONG IN lIndex);
	BOOL							ChangeItemObject(LONG IN lIndex,CODLEx_Element_ReportItem* IN pItem);
	CODLEx_Element_ReportRow*		SetItemWidth(LONG IN lIndex,LONG IN lWidth);

	BOOL							IsShowHorizontalGrid();
	BOOL							IsShowVerticalGrid();

	CODLEx_Element_ReportRow*		EnableShowHorizontalGrid(BOOL IN bEnable);
	CODLEx_Element_ReportRow*		EnableShowVerticalGrid(BOOL IN bEnable);
	CODLEx_Element_ReportRow*		SetVerticalGridPen(LOGPEN* IN lp);
	CODLEx_Element_ReportRow*		SetHorizontalGridPen(LOGPEN* IN lp);
	CODLEx_Element_ReportRow*		SetVerticalGridPen(CODL_Pen* IN pPen);
	CODLEx_Element_ReportRow*		SetHorizontalGridPen(CODL_Pen* IN pPen);



	CODL_Pen*						GetVerticalGridPen();
	CODL_Pen*						GetHorizontalGridPen();

	CODL_Font*						GetDefaultFont();
	CODLEx_Element_ReportRow*		SetDefaultFont(LOGFONT* IN lf);
	COLORREF						GetDefaultTextColor();
	CODLEx_Element_ReportRow*		SetDefaultTextColor(COLORREF IN clr);

	CODLEx_Element_ReportRow*		SetDefaultBkBrush(LOGBRUSH* IN lb);
	CODL_Brush*						GetDefaultBkBrush();
	
	CODL_DirtyRect&					GetDirtyRect();
	CODLEx_Element_ReportRow*		SetDrawClip(RECT& IN clip);

	CODLEx_Element_ReportRow*		SetColWidth(LONG IN lCol,LONG IN lWidth);
	CODLEx_Element_ReportRow*		SetRowHeight(LONG IN lHeight);
public:
	virtual BOOL					Draw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL					OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL					OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual VOID					GetRect(RECT& OUT rect);
	virtual VOID					UpdateItemsSize();

	virtual VOID					Invalidate(BOOL IN bFlushView=FALSE);
	virtual VOID					SetSelected(BOOL IN bSelect);
	virtual BOOL					PtInElement(POINT IN pt);
protected:
	virtual BOOL					ResetBitmapCanvas(HDC IN hDC,RECT* IN pPaintRect);
	virtual	VOID					UpdateItemsDirtyRect(LONG IN lStart,LONG IN lEnd);
	virtual BOOL					GetNeedDrawItem(LONG& OUT lStart,LONG& OUT lEnd);


};