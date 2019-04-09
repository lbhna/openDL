#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Histogram.h
	created:	2012/03/30
	author:		LB
	purpose:	柱状图
\*********************************************************************/
#include "./ODLEx_Element_Coordinate.h"

class ODLEX_EXPORT CODLEx_Element_Histogram;
class ODLEX_EXPORT CODLEx_Element_HistogramData
{
public:	
	FLOAT						x,y;

protected:
	CODL_Pen*					m_pFramePen;
	CODL_Brush*					m_pBrush;
  CODLEx_Element_Histogram*   m_pHistogram;
public:
  CODLEx_Element_HistogramData(CODLEx_Element_Histogram* pHistogram);
  ~CODLEx_Element_HistogramData();
  VOID	SetData(FLOAT IN fx, FLOAT IN fy);
  VOID	SetFramePen(CODL_Pen* IN pPen);
  VOID	SetBrush(CODL_Brush* IN pBrush);
  VOID	Draw(HDC IN hDC, LONG IN x, LONG IN y, POINT IN center, CODLEx_Element_Coordinate* IN pCoord);

};

class ODLEX_EXPORT CODLEx_Element_Histogram :
	public CODL_ElementBase
{

protected:
	BOOL										m_bEnableAutoScroll;
	CODL_Vector2f								m_vScale;
  CODL_Vector2f           m_vSizeScale;
	POSITION									m_DataPosition;//数据起始位置,相对于坐标原点
	CODL_ListT<CODLEx_Element_HistogramData*>	m_theDataList;
public:
	CODLEx_Element_Histogram(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Histogram(void);
public:
	VOID						SetScale(FLOAT IN x,FLOAT IN y);
  VOID            SetSizeScale(FLOAT IN x, FLOAT IN y);
  const CODL_Vector2f&  GetSizeScale()
  {
    return m_vSizeScale;
  }
  const CODL_Vector2f&  GetScale()
  {
    return m_vScale;
  }
	VOID						AddData(FLOAT IN x,FLOAT IN y,CODL_Pen* IN pFramePen,CODL_Brush* IN pBrush);
	VOID						AddData(FLOAT IN x,FLOAT IN y,LOGPEN* IN lp,LOGBRUSH* IN lb);
	VOID						AddData(FLOAT IN x,FLOAT IN y,COLORREF IN clrFrame=RGB(255,0,0),COLORREF IN clrBk=RGB(0,255,0));
	VOID						ClearData();
	VOID						AutoScrollCheck();
	VOID						EnableAutoScroll(BOOL IN bEnable){m_bEnableAutoScroll=bEnable;}
	BOOL						IsEnableAutoScroll(){return m_bEnableAutoScroll;}
public:
	virtual BOOL				OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL				OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
protected:
	VOID						MoveLeft(LONG IN lCount);
	VOID						ScrollProc(LONG IN count);
};
