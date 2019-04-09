#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Painter\ODL_Painter.h
	created:	2012/02/23
	author:		LB
	purpose:	»­¼Ò»ùÀà
\*********************************************************************/

#include "../View/ODL_ViewBase.h"

class ODL_EXPORT CODL_ViewBase;
class ODL_EXPORT CODL_Painter :
	public CODL_ObjBase
{
protected:

	PAINTER_TYPE		m_PainterType;
	HWND				m_hDeviceWnd;
	RECT				m_PaintRect;
	CODL_ViewBase*		m_pView;
	RECT				m_rectEdgeSpace;
	BOOL				m_bFixedSize;
public:
	CODL_Painter(CODL_ViewBase* IN pView);
	virtual ~CODL_Painter(void);
public:
	RECT*				GetPaintRect(){return &m_PaintRect;}
	PAINTER_TYPE		GetType(){return m_PainterType;}
	HWND				GetDeviceWnd(){return m_hDeviceWnd;}
	CODL_ViewBase*		GetView(){return m_pView;}

public:
	virtual INT			Create(HWND IN hWnd,HDC IN hDC=NULL)=0;
	virtual INT			Create(HWND IN hWnd,RECT* IN pPaintRect,BOOL IN bFixedSize=FALSE,HDC IN hDC=NULL)=0;
	virtual VOID		SetPaintRect(RECT* IN pPaintRect)=0;

	virtual HDC			GetDC()=0;
	virtual VOID		ReleaseDC(HDC IN hDC)=0;

	virtual VOID		OnPreRender()=0;
	virtual VOID		OnEndRender()=0;
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)=0;
	virtual VOID		Render()=0;
	virtual BOOL		SaveToBmpFile(LPCSTR IN pFileName)=0;
	virtual BOOL		SaveToClipboard()=0;

public:
	virtual VOID		DrawRect(RECT* IN pRect,DWORD IN dwSize,COLORREF IN clr)=0;
};

