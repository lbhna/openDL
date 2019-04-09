#include "StdAfx.h"
#include ".\odl_gdipainter.h"


CODL_GDIPainter::CODL_GDIPainter(CODL_ViewBase* IN pView):
CODL_Painter(pView)
{
	m_PainterType				=PAINTER_GDI;
	m_hDrawDC					=NULL;
	m_hBitmap					=NULL;
	m_hRectPen					=NULL;
	m_hDeviceDC					=NULL;
	m_bFixedSize				=FALSE;
}

CODL_GDIPainter::~CODL_GDIPainter(void)
{
	ODL_SafeDeleteGDIObj(m_hRectPen);
	ODL_SafeDeleteGDIObj(m_hBitmap);


	if(m_hDrawDC != NULL)
		DeleteDC(m_hDrawDC);

}
INT			CODL_GDIPainter::Create(HWND IN hWnd,HDC IN hDC)
{
	if(!IsWindow(hWnd))
		return -1;

	m_hDeviceWnd		=hWnd;
	m_hDeviceDC			=hDC;
	RECT	rect;
	GetClientRect(m_hDeviceWnd,&rect);
	ResetPainterArea(rect);
	m_rectEdgeSpace.left	=0;
	m_rectEdgeSpace.right	=0;
	m_rectEdgeSpace.top		=0;
	m_rectEdgeSpace.bottom	=0;

	return 0;
}
VOID		CODL_GDIPainter::SetPaintRect(RECT* IN pPaintRect)
{
	if(!IsWindow(m_hDeviceWnd))
		return;
	RECT	rect;
	GetClientRect(m_hDeviceWnd,&rect);
	m_rectEdgeSpace.left	=pPaintRect->left		-rect.left		;
	m_rectEdgeSpace.top		=pPaintRect->top		-rect.top		;
	m_rectEdgeSpace.right	=pPaintRect->right		-rect.right		;
	m_rectEdgeSpace.bottom	=pPaintRect->bottom	-rect.bottom	;
	ResetPainterArea(*pPaintRect);
}

INT			CODL_GDIPainter::Create(HWND IN hWnd,RECT* IN pPaintRect,BOOL IN bFixedSize,HDC IN hDC)
{
	if(!IsWindow(hWnd))
		return -1;

	m_hDeviceWnd		=hWnd;
	m_hDeviceDC			=hDC;

	RECT	rect;
	GetClientRect(m_hDeviceWnd,&rect);

	m_rectEdgeSpace.left	=pPaintRect->left		-rect.left		;
	m_rectEdgeSpace.top		=pPaintRect->top		-rect.top		;
	m_rectEdgeSpace.right	=pPaintRect->right		-rect.right		;
	m_rectEdgeSpace.bottom	=pPaintRect->bottom	-rect.bottom	;
	m_bFixedSize			=bFixedSize;
	ResetPainterArea(*pPaintRect);
	return 0;
}


HDC			CODL_GDIPainter::GetDC()
{
	return m_hDrawDC;
}
VOID		CODL_GDIPainter::ReleaseDC(HDC IN hDC)
{

}
BOOL		CODL_GDIPainter::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
	case WM_SIZE:
		{
			if(!m_bFixedSize)
			{
				RECT	rect;
				GetClientRect(m_hDeviceWnd,&rect);
				rect.left		+= m_rectEdgeSpace.left	;
				rect.right		+= m_rectEdgeSpace.right	;
				rect.top		+= m_rectEdgeSpace.top		;
				rect.bottom		+= m_rectEdgeSpace.bottom	;
				ResetPainterArea(rect);
			}
		}
		break;
	}

	return FALSE;
}
VOID		CODL_GDIPainter::OnPreRender()
{
	//Ìî³ä±³¾°É«
	RECT rect;
	rect.left		=0;
	rect.top		=0;
	rect.right		=m_PaintRect.right-m_PaintRect.left;
	rect.bottom		=m_PaintRect.bottom-m_PaintRect.top;

	::SetBkColor(m_hDrawDC, m_pView->GetBackColor());
	::ExtTextOut(m_hDrawDC, 0,0, ETO_OPAQUE, &rect, NULL, 0, NULL);
}
VOID		CODL_GDIPainter::OnEndRender()
{
	HDC		hWndDC	=::GetDC(m_hDeviceWnd);
	BitBlt(hWndDC,m_PaintRect.left,m_PaintRect.top,abs(m_PaintRect.right-m_PaintRect.left),abs(m_PaintRect.bottom-m_PaintRect.top),m_hDrawDC,0,0,SRCCOPY);
	::ReleaseDC(m_hDeviceWnd,hWndDC);

}

INT		CODL_GDIPainter::ResetPainterArea(RECT IN rect)
{
	if(rect.left != m_PaintRect.left ||
		rect.right != m_PaintRect.right ||
		rect.top != m_PaintRect.top ||
		rect.bottom != m_PaintRect.bottom ||
		m_hDrawDC == NULL)
	{
		if(m_hBitmap != NULL)
			DeleteObject(m_hBitmap);
		if(m_hDrawDC != NULL)
			DeleteDC(m_hDrawDC);
	
		m_PaintRect		=rect;
		SIZE	newSize;
		newSize.cx	=abs(m_PaintRect.right-m_PaintRect.left);
		newSize.cy	=abs(m_PaintRect.bottom-m_PaintRect.top);


		HDC		hWndDC	=::GetDC(m_hDeviceWnd);
		if(hWndDC == NULL)
			return -2;
		HDC		hDC =hWndDC;
		if(m_hDeviceDC != NULL)
			hDC =m_hDeviceDC;

		m_hDrawDC	=CreateCompatibleDC(hDC);
		if(m_hDrawDC == NULL)
			return -3;
		m_hBitmap	=CreateCompatibleBitmap(hDC,newSize.cx,newSize.cy);
		if(m_hBitmap == NULL)
			return -4;
		SelectObject(m_hDrawDC,m_hBitmap);

		::ReleaseDC(m_hDeviceWnd,hWndDC);
	}
	return 0;
}
VOID		CODL_GDIPainter::DrawRect(RECT* IN pRect,DWORD IN dwSize,COLORREF IN clr)
{
	if(m_hRectPen == NULL)
	{
		m_hRectPen=CreatePen(PS_SOLID,dwSize,clr);
	}

	HPEN	hOldPen =(HPEN)SelectObject(m_hDrawDC,m_hRectPen);
	MoveToEx(m_hDrawDC,pRect->left,pRect->top,NULL);
	LineTo(m_hDrawDC,pRect->right,pRect->top);
	LineTo(m_hDrawDC,pRect->right,pRect->bottom);
	LineTo(m_hDrawDC,pRect->left,pRect->bottom);
	LineTo(m_hDrawDC,pRect->left,pRect->top);
	SelectObject(m_hDrawDC,hOldPen);

}
VOID		CODL_GDIPainter::Render()
{
	GetView()->Update();
}

BOOL			CODL_GDIPainter::SaveToBmpFile(LPCSTR IN pFileName)
{
	DWORD				width	=abs(m_PaintRect.right-m_PaintRect.left);
	DWORD				height	=abs(m_PaintRect.bottom-m_PaintRect.top);
	return SaveDCToBmpFile(m_hDrawDC,m_hBitmap,width,height,pFileName);
}
BOOL			CODL_GDIPainter::SaveToClipboard()
{
	DWORD				width	=abs(m_PaintRect.right-m_PaintRect.left);
	DWORD				height	=abs(m_PaintRect.bottom-m_PaintRect.top);
	return SaveDCToClipboard(m_hDrawDC,m_hBitmap,width,height);

}

