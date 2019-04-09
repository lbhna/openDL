#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Elements\ODL_ElementBase.h
	created:	2012/02/21
	author:		LB
	purpose:	图元基类
\*********************************************************************/

#include "../Base/ODL_ObjBase.h"
#include "../Base/ODL_Listener.h"
#include "../Canvas/ODL_CanvasBase.h"




class ODL_EXPORT CODL_CanvasBase;
class ODL_EXPORT CODL_ElementBase :
	public CODL_ObjBase
{
protected:
	CODL_CanvasBase*	m_pCanvas;
	LONG				m_ZIndex;
	DWORD				m_dwID;

	BOOL				m_bShow;
	RECT				m_CurPaintRect;
	ODL_ELEMENT_TYPE	m_Type;
	BOOL				m_bSelected;
	BOOL				m_bEnableSelect;

	BOOL				m_bInvalidate;
	
	HMENU				m_hMenu;

	CODL_Listener*		m_pListener;
protected:

public:
	CODL_ElementBase(CODL_CanvasBase* IN pCanvas);
	virtual ~CODL_ElementBase(void);
public:
	CODL_CanvasBase*	GetCanvas(){return m_pCanvas;}
	RECT*				GetPaintRect(){return &m_CurPaintRect;}
	ODL_ELEMENT_TYPE	GetType(){return m_Type;}

	VOID				SetRButtonMenu(HMENU IN hMenu);
	BOOL				PopupMenu();

	LONG				GetZIndex(){return m_ZIndex;}
	VOID				SetZIndex(LONG IN lIndex);


	VOID				SetID(DWORD IN dwID){m_dwID =dwID;}
	DWORD				GetID(){return m_dwID;}
public:
	static BOOL			PtInLine(POINT IN pt,POINT IN LineStart,POINT IN LineEnd);
public:
	virtual VOID		SetListener(CODL_Listener* IN pListener);
	virtual	BOOL		IsEnableSelect(){return m_bEnableSelect;}
	virtual VOID		EnableSelect(BOOL IN bEnable);
	virtual BOOL		Draw(HDC IN hDC,RECT* IN pPaintRect);
	virtual VOID		Invalidate(BOOL IN bFlushView=FALSE);
	virtual BOOL		IsInvalidate(){return m_bInvalidate;}
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual VOID		Show(BOOL IN bShow);
	virtual BOOL		IsShow(){return m_bShow;}
	virtual VOID		MoveLeft(LONG IN lCount){};
	virtual VOID		MoveUp(LONG IN lCount){};
	virtual VOID		SetSelected(BOOL IN bSelect);
	virtual BOOL		IsSelected(){return m_bSelected;}
	virtual BOOL		PtInElement(POINT IN pt){return FALSE;}
	virtual BOOL		IsControlSwitchKeyPressed();
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint){return FALSE;}
	virtual VOID		OnPreCanvasSizeChange(){}//画布大小改变前
	virtual VOID		OnEndCanvasSizeChange(){}//画布大小改变后
};

