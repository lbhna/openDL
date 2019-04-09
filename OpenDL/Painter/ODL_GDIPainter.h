#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Painter\ODL_GDIPainter.h
	created:	2012/02/23
	author:		LB
	purpose:	使用GDI技术的画家类
\*********************************************************************/

#include "./ODL_Painter.h"

class ODL_EXPORT CODL_GDIPainter :
	public CODL_Painter
{
protected:
	HDC					m_hDrawDC;
	HBITMAP				m_hBitmap;
	HPEN				m_hRectPen;
	HDC					m_hDeviceDC;
public:
	CODL_GDIPainter(CODL_ViewBase* IN pView);
	virtual ~CODL_GDIPainter(void);
public:
	virtual INT			Create(HWND IN hWnd,HDC IN hDC=NULL);
	virtual INT			Create(HWND IN hWnd,RECT* IN pPaintRect,BOOL IN bFixedSize=FALSE,HDC IN hDC=NULL);
	virtual VOID		SetPaintRect(RECT* IN pPaintRect);
	virtual HDC			GetDC();
	virtual VOID		ReleaseDC(HDC IN hDC);
	virtual VOID		OnPreRender();
	virtual VOID		OnEndRender();

	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual VOID		DrawRect(RECT* IN pRect,DWORD IN dwSize,COLORREF IN clr);
	virtual VOID		Render();
	virtual BOOL		SaveToBmpFile(LPCSTR IN pFileName);
	virtual BOOL		SaveToClipboard();

protected:
	INT					ResetPainterArea(RECT IN rect);
};

