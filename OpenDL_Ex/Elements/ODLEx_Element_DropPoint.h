#pragma once
/********************************************************************\
	filename: 	ODLEx_Element_DropPoint.h
	created:	2014/10/24
	author:		LB
	purpose:	落点类
\*********************************************************************/
#include "./ODLEx_Element_Label.h"

class ODLEX_EXPORT CODLEx_Element_DropPoint:
	public CODL_ElementBase,
	public CODL_Listener
{
protected:
	CODL_Brush*					m_pPointBrush;
	DWORD						m_dwPointRadius;
	CODL_Vector2f				m_vOffset;
	CHAR*						m_pPointName;

	BOOL						m_bPosChanged;
	BOOL						m_bShowLabel;	//是否显示标牌
	POINT						m_LabelOffset;
	POINT						m_PointOldPos;
	CODLEx_Element_Label*		m_pLabel;
public:
	CODLEx_Element_DropPoint(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_DropPoint();

public:
	VOID				SetPointColor(COLORREF IN clr);
	COLORREF			GetPointColor();


	POINT*				GetLabelOffset();
	VOID				SetLabelOffset(LONG IN x,LONG IN y);

	VOID				SetDropPointRadius(DWORD IN dwRadius);
	DWORD				GetDropPointRadius(){return m_dwPointRadius;}

	VOID				SetDropPointName(CHAR* IN pName);
	CHAR*				GetDropPointName(){return m_pPointName;}

	VOID				SetOffset(FLOAT IN fAt/*前向为正*/,FLOAT IN fLeft/*(Y轴向上为正的情况下左向为正）*/);
	CODL_Vector2f*		GetOffset(){return &m_vOffset;}

	VOID				GetDropPointRect(RECT& OUT rect);
	
	VOID				ShowLabel(BOOL IN bShow);

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
public:
	virtual VOID		OnElement_PosChanged(CODL_ElementBase* IN pElement);

};
