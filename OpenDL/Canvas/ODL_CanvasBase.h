#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Canvas\ODL_CanvasBase.h
	created:	2012/02/21
	author:		LB
	purpose:	画布基类 一块画布里有N个图元
\*********************************************************************/
#include "../Base/ODL_ObjListBase.h"
#include "../View/ODL_ViewBase.h"
#include "../Elements/ODL_ElementBase.h"

typedef enum ODL_EXPORT _CANVAS_MSG_WPARA_TYPE
{//画布回调的消息第一个参数的函义
	//------------------------------------------------
	CANVAS_CALLBACKMSG_OnSizeChanged	=0,
	CANVAS_CALLBACKMSG_OnActive,
	CANVAS_CALLBACKMSG_OnDeactive,

	//------------------------------------------------
	CANVAS_CALLBACKMSG_USER				=0x50000000,

	//------------------------------------------------
	CANVAS_MSG_wpara_forcedword			=0x7fffffff,
}CANVAS_MSG_WPARA_TYPE;

typedef struct ODL_EXPORT _ODL_CANVAS_STATE
{
	POINT			pos;
	SIZE			size;
}ODL_CANVAS_STATE;


class ODL_EXPORT CODL_ObjListBase;
class ODL_EXPORT CODL_ElementBase;
class ODL_EXPORT CODL_ViewBase;
class ODL_EXPORT CODL_CanvasBase :
	public CODL_ObjListBase
{
protected:
	CODL_ViewBase*			m_pView;
	CODL_Listener*			m_pListener;

	CANVAS_TYPE				m_CanvasType;
	ODL_OPERATION_TYPE		m_CurOperatorType;
	BOOL					m_bInvalidate;
	SIZE					m_Size;	//画布大小
	POINT					m_Pos;	//画布在视中的位置
	CHAR*					m_pName;//画布名称

	BOOL					m_bActived;	//是否是激活状态
	BOOL					m_bMaxisized;
	BOOL					m_bEnableDoubleClick;

	HMENU					m_hMenu;
	HWND					m_hCallbackWnd;			//回调窗口句柄 
	UINT					m_uCallbackMessageID;//回调消息ID

	CODL_Pen*				m_pElementSelectFramePen;
protected:
	COLORREF				m_BkColor;
	COLORREF				m_ActiveFrameColor;
	COLORREF				m_NormalFrameColor;

protected:
	HPEN					m_hActiveFramePen;
	HPEN					m_hNormalFramePen;
protected:
	CODL_ElementBase*		m_pCoordinate;		//坐标轴
	CODL_ElementBase*		m_pCurrentSelected;	//当前选择的图元
	CODL_ElementBase*		m_pZoomFrame;		//当前选择框对象
	CODL_ElementBase*		m_pCrossLine;		//当前十字线对象
	CODL_ElementBase*		m_pDiagramPreview;	//当前图例对象
	CODL_ElementBase*		m_pCanvasTitle;		//标题栏对象


protected:
	BOOL					m_bNeedOrder;
	LONG					m_lOldCount;
	BOOL					m_bEnableAutoScroll;

protected:
	BOOL					m_bSavedState;
	ODL_CANVAS_STATE		m_SavedState;
public:
	CODL_CanvasBase(CODL_ViewBase* IN pView);
	virtual ~CODL_CanvasBase(void);
public:
	virtual INT					Create(LPCSTR IN pName);
	virtual INT					OnCreate(){return 0;}
	virtual INT					SetSize(PSIZE IN pSize)=0;
	virtual INT					SetSize(DWORD IN cx,DWORD IN cy)=0;
	virtual INT					Draw()=0;
	virtual INT					Present()=0;
	virtual BOOL				ResetCanvas()=0;
	virtual VOID				ClearCanvas(HDC IN hCanvasDC);
	virtual HDC					GetDC()=0;
	virtual VOID				ReleaseDC(HDC IN hDC)=0;
	virtual VOID				SetCallbackMessageID(HWND IN hMsgWnd,UINT IN uMsgID);

public:
	virtual INT					OnUpdate();
public:
	PPOINT						GetPos(){return &m_Pos;}
	VOID						SetPos(PPOINT IN pPoint);
	VOID						SetPos(LONG IN x,LONG IN y);
	
	CODL_Pen*					GetElementSelectFramePen();
	VOID						SetElementSelectFramePen(LOGPEN* IN lp);

	VOID						SaveState();
	VOID						RestoreState();
	BOOL						IsSavedState(){return m_bSavedState;}

	VOID						SetCurrentOperation(ODL_OPERATION_TYPE IN op){m_CurOperatorType=op;}

	ODL_OPERATION_TYPE			GetCurrentOperation(){return m_CurOperatorType;}


	COLORREF					GetBkColor(){return m_BkColor;}
	COLORREF					GetActiveFrameColor(){return m_ActiveFrameColor;}
	COLORREF					GetNormalFrameColor(){return m_NormalFrameColor;}
	VOID						SetBkColor(COLORREF IN clr){m_BkColor =clr;m_bInvalidate=TRUE;}
	VOID						SetActiveFrameColor(COLORREF IN clr);
	VOID						SetNormalFrameColor(COLORREF IN clr);

	VOID						SetRButtonMenu(HMENU IN hMenu){m_hMenu =hMenu;}

	BOOL						IsEnableAutoScroll(){return m_bEnableAutoScroll;}
	VOID						EnableAutoScroll(BOOL IN bEnable){m_bEnableAutoScroll=bEnable;}

	VOID						EnableDoubleClick(BOOL bEnable);
	BOOL						IsEnableDoubleClick();


	BOOL						IsInvalidate(){return m_bInvalidate;}
	virtual VOID				Invalidate(BOOL IN bResetAllElements);
	
	PSIZE						GetSize(){return &m_Size;}
	VOID						GetRect(RECT& OUT rect);
	
	CANVAS_TYPE					GetType(){return m_CanvasType;}
	
	CODL_ViewBase*				GetView(){return m_pView;}

	LPCSTR						GetName(){return m_pName;}
	VOID						SetName(LPCSTR IN pName);

	BOOL						IsMaximized(){return m_bMaxisized;}
	VOID						SetMaximized(BOOL IN bMax);

	VOID						SetListener(CODL_Listener* IN pListener);

	virtual void				SetSelected(CODL_ElementBase* IN pElement);
	virtual CODL_ElementBase*	GetSelected(){return m_pCurrentSelected;}

	virtual void				SetCoordinate(CODL_ElementBase* IN pCoord);
	virtual CODL_ElementBase*	GetCoordinate(){return m_pCoordinate;}

	virtual void				SetZoomFrame(CODL_ElementBase* IN pZoomFrame);
	virtual CODL_ElementBase*	GetZoomFrame(){return m_pZoomFrame;}
	virtual void				SetCrossLine(CODL_ElementBase* IN pCrossLine);
	virtual CODL_ElementBase*	GetCrossLine(){return m_pCrossLine;}
	virtual	void				SetDiagramPreview(CODL_ElementBase* IN pPreview);
	virtual CODL_ElementBase*	GetDiagramPreview(){return m_pDiagramPreview;}

	virtual void				SetCanvasTitle(CODL_ElementBase* IN pTitle);
	virtual CODL_ElementBase*	GetCanvasTitle(){return m_pCanvasTitle;}

	virtual BOOL				IsActive(){return m_bActived;}
	
	virtual BOOL				Active();
	virtual BOOL				Deactive();

	virtual BOOL				PointInCanvas(POINT* IN pt);
	virtual BOOL				PointInCanvasChangeSizeButton(POINT* IN pt);
	virtual VOID				OnLostDevice(){};
	virtual VOID				OnResetDevice(){};

	virtual VOID				MoveLeft(LONG IN lCount);
	virtual VOID				MoveUp(LONG IN lCount);

	virtual VOID				SetOrderFlag(BOOL IN bOrder){m_bNeedOrder=bOrder;}

	virtual BOOL				SaveToBmpFile(LPCSTR IN pFileName)=0;
	virtual BOOL				SaveToClipboard()=0;
	virtual VOID				PostCallbackMessage(WPARAM wp,LPARAM lp);
	virtual LRESULT				SendCallbackMessage(WPARAM wp,LPARAM lp);

public:
	virtual BOOL				OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL				OnLButtonDBClick(POINT* IN pPoint);
	virtual BOOL				OnKeydown(WPARAM IN wParam,LPARAM IN lParam);
	virtual BOOL				OnLButtonDown(POINT* IN pPoint);
	virtual BOOL				OnRButtonDown(POINT* IN pPoint);
protected:
	virtual VOID				DrawActiveFrame(HDC IN hDC);
	virtual VOID				OrderElement();
	VOID						PopupRButtonMenu();
	

};


