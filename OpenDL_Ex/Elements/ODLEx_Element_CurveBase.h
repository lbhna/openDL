#pragma once

/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_CurveBase.h
	created:	2012/03/13
	author:		LB
	purpose:	曲线基类
\*********************************************************************/

class ODLEX_EXPORT CODLEx_CurveData
{
public:
	FLOAT		x;
	FLOAT		y;
	DWORD		flag;
public:
	CODLEx_CurveData()
	{
		x		=0.0f;
		y		=0.0f;
		flag	=0;
	}
	CODLEx_CurveData(FLOAT IN fX,FLOAT IN fY,DWORD IN dwFlag)
	{
		x		=fX;
		y		=fY;
		flag	=dwFlag;
	}
};
class ODLEX_EXPORT CODLEx_Element_CurveBase :
	public CODL_ElementBase
{
protected:
	CODL_Pen*					m_pLinePen;
	CODL_Brush*					m_pSelectBrush;
	CHAR*						m_pName;
	CODL_Font*					m_pNameFont;
protected:
	CODL_Vector2f				m_vScale;
	BOOL						m_bEnableCull;
	BOOL						m_bEnableAutoScroll;
	BOOL						m_bEnableLinkOverflow;//
protected:
	POSITION					m_DataPosition;//数据起始位置,相对于坐标原点
	CODL_ListT<CODLEx_CurveData>m_theDataList;
public:
	CODLEx_Element_CurveBase(CODL_CanvasBase* IN pCanvas,CHAR* IN pName);
	virtual ~CODLEx_Element_CurveBase(void);
public:
	virtual INT			Init(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor);
	VOID				SetLineParameter(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor);
	BOOL				GetLineParameter(UINT& OUT nLineStyle,UINT& OUT nLineWidth,COLORREF& OUT LineColor);
	
	VOID				SetLinePen(LOGPEN* IN lp);
	VOID				SetSelectBtnBrush(LOGBRUSH* IN lb);


	VOID				EnableAutoScroll(BOOL IN bEnable){m_bEnableAutoScroll=bEnable;}
	BOOL				IsEnableAutoScroll(){return m_bEnableAutoScroll;}


	CHAR* 				GetName(){return m_pName;}
	VOID				SetName(CHAR*  IN pName,CHAR* IN pFontName,DWORD IN dwFontSize);

	VOID				EnableCull(BOOL IN bEnable){m_bEnableCull=bEnable;Invalidate(TRUE);}
	BOOL				IsEnableCull(){return m_bEnableCull;}

    
	CODL_Pen*			GetLinePen(){return m_pLinePen;}

	//是否允许画出超限的线
	VOID				EnableLinkOverflow(BOOL IN bEnable);
	BOOL				IsEnableLinkOverflow(){return m_bEnableLinkOverflow;}

public:
	
	
	
	CODL_Vector2f*		GetScale(){return &m_vScale;}
	VOID				SetScale(FLOAT IN xScale,FLOAT IN yScale);

	VOID				AddData(FLOAT IN x,FLOAT IN y,DWORD IN flag=0);

	DWORD				GetDataCount(){return m_theDataList.GetLength();}
	CODLEx_CurveData*	GetData(LONG IN lIndex){return m_theDataList.GetAt(m_theDataList.GetPosByIndex(lIndex));}
	CODLEx_CurveData*	GetLastData(){return m_theDataList.GetAt(m_theDataList.GetLastPosition());}

	VOID				ClearData(){m_DataPosition =NULL;m_theDataList.DestroyList();}

	CODLEx_CurveData*	GetDataByXIndicate(LONG IN lIndicate);
	VOID				AutoScrollCheck();

public:
	virtual VOID		MoveLeft(LONG IN lCount);
	virtual VOID		MoveUp(LONG IN lCount);
public:
	virtual BOOL		PtInElement(POINT IN pt);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	
protected:
	VOID				DrawName(HDC IN hDC,RECT* IN pPaintRect);
	VOID				ScrollProc(LONG IN count);
};
