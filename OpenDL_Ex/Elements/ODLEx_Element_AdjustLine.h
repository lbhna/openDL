#pragma once
/********************************************************************\
	filename: 	ODLEx_Element_AdjustLine.h
	created:	2014/10/28
	author:		LB
	purpose:	可调整的曲线类
\*********************************************************************/
#include "ODLEx_Element_CurveBase.h"

#define		AdjustPointAdd			0
#define		AdjustPointMove			1
#define		AdjustPointDelete		2
#define		AdjustPointSelect		3


#define		ADJUSTLINE_MSG		(CANVAS_CALLBACKMSG_USER+1)

struct		OLD_ADJUSTLINE_MSG
{
	DWORD			type;	//上面定义的几个消息类型
	DWORD			x;		//x值
	float			y;		//y值
	DWORD			ox;		//旧x值,move有效
	DWORD			pLine;	//本线指针
};

class ODLEX_EXPORT CODLEx_Element_AdjustLine:public CODL_ElementBase
{
protected:
	//绘图参数
	CODL_Pen*					m_pLinePen;
	CODL_Brush*					m_pSelectBrush;
	DWORD						m_dwPointRadius;	//
	CODL_Font*					m_pTextFont;
	DWORD						m_TextBkColor;
	DWORD						m_TextColor;

	//配置参数
	BOOL						m_bFilterLBDBLCLK;//过滤掉双击事件
		 
	BOOL						m_bMinX;
	BOOL						m_bMaxX;
	BOOL						m_bMinY;
	BOOL						m_bMaxY;
	float						m_fMinX;
	float						m_fMaxX;
	float						m_fMaxY;
	float						m_fMinY;

	BOOL						m_bEnableClickAdd;		//自动加点
	BOOL						m_bLockFirstXatZero;	//首点X始终在是0
	BOOL						m_bTrueFalseStyle;
	BOOL						m_bXinteger;
	BOOL						m_bEnable;	

	//临时变量
	INT							m_dwLastSelect;		//
	BOOL						m_bPressed;
	POINT						m_ptOffset;
	DWORD						m_dwBK_X;			//

public:
	CODLEx_Element_AdjustLine(CODL_CanvasBase* IN pCanvas,BOOL bLockFirstXatZero);
	virtual ~CODLEx_Element_AdjustLine();

public:
	VOID				SetColor(COLORREF IN clr);

	VOID				SetPointRadius(DWORD IN dwRadius);
	DWORD				GetPointRadius(){return m_dwPointRadius;}
	CODLEx_CurveData*	AddData(FLOAT IN x,FLOAT IN y);
	VOID				MoveDataX(FLOAT IN x,FLOAT newX,BOOL bNotify =FALSE);//注意越界
	VOID				DeleteDataByX(DWORD X,BOOL bNotify = FALSE);
	CODLEx_CurveData*	GetCurveDataData(INT index);
	VOID				DeleteDataByIndex(INT index,BOOL bNotify = FALSE);
	VOID				CancelSelect(BOOL bNofity);
	//
	BOOL				HitTest(CPoint& pt);
	int					GetSelectIndex();
	BOOL				CanDelectSelect();
	BOOL				IsMovingPoint();

	//
	VOID				Clear();
	VOID				ClearMinMaxLimit();
	VOID				SetMinX(float fMinX);
	VOID				SetMaxX(float fMaxX);
	VOID				SetMinY(float fMinY);
	VOID				SetMaxY(float fMaxY);


	//点击加点
	VOID				EnableClickAdd(BOOL bEnable);	
	//第一点x锁定0
	VOID				EnableFirstZeroLock(BOOL bEnable);
	//过滤双击事件
	void				EnableLBDClickFliter(BOOL bEnable);
	//Y值只有0，1
	VOID				EnableTrueFalseStyle(BOOL bEnable);
	//X都取整数
	VOID				EnableXinteger(BOOL bEnable);

	//操作总开关
	VOID				EnableOperator(BOOL bEnable);

	//
	VOID				SetLineParameter(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor);




protected:
	OLD_ADJUSTLINE_MSG	m_Msg,m_Msg2;
	CODL_ListT<POINT>			m_theDrawDataList;
	CODL_ListT<CODLEx_CurveData>m_theDataList;

	void				Init();
	BOOL				InSelect(POINT pt,CODLEx_CurveData*  pData,POINT& offset);
	RECT				GetDropPointRect(CODLEx_CurveData* pData);

	INT					AddValueAtPoint(POINT pt);

	BOOL				FormatX(float& x,int index,DWORD style);
	FLOAT				FormatY(float& y);
	BOOL				IsXinLimitRange(float x);
	
	int					XValueToCoordSpacce(float x);
	int					YValueToCoordSpacce(float y);
	float				CoordSpaceToXValue(int x);
	float				CoordSpaceToYValue(int y);
	void				PostUnselectMsg();
	VOID				PostSelectMsg();
	

protected:
	BOOL				OnLButtonDown(POINT pt);
	BOOL				OnLButtonUp();
	BOOL				OnMouseMove(POINT pt);
	BOOL				OnLButtonDBDown(POINT pt);
	BOOL				OnKeyDown(UINT message, WPARAM wParam, LPARAM lParam);

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
};










