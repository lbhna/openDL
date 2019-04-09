#include "StdAfx.h"
#include ".\odl_gdicanvas.h"
#include "../Painter/ODL_GDIPainter.h"
#include "../Elements/ODL_ElementBase.h"


CODL_GDICanvas::CODL_GDICanvas(CODL_ViewBase* IN pView):CODL_CanvasBase(pView)
{
	m_CanvasType			=CANVAS_GDI;
	m_hDrawDC				=NULL;
	m_hBitmap				=NULL;

}

CODL_GDICanvas::~CODL_GDICanvas(void)
{
	ODL_SafeDeleteGDIObj(m_hBitmap);
	if(m_hDrawDC != NULL)
		DeleteDC(m_hDrawDC);
}

INT				CODL_GDICanvas::SetSize(PSIZE IN pSize)
{
	if(pSize == NULL)
		return -1;
	if(m_Size.cx != pSize->cx || m_Size.cy != pSize->cy || m_hDrawDC == NULL)
	{
		CODL_ElementBase*	pElement	=NULL;
		for(LONG i=0;i<GetCount();i++)
		{
			pElement	=(CODL_ElementBase*)GetObj(i);
			pElement->OnPreCanvasSizeChange();
		}
		m_Size	=*pSize;
		ResetCanvas();
		PostCallbackMessage(CANVAS_CALLBACKMSG_OnSizeChanged,(LPARAM)this);
		if(m_pListener != NULL)
		{
			m_pListener->OnCanvas_SizeChanged(this);
		}
		for(LONG i=0;i<GetCount();i++)
		{
			pElement	=(CODL_ElementBase*)GetObj(i);
			pElement->OnEndCanvasSizeChange();
		}
	}
	return 0;
}
INT				CODL_GDICanvas::SetSize(DWORD IN cx,DWORD IN cy)
{
	if(m_Size.cx != cx || m_Size.cy != cy || m_hDrawDC == NULL)
	{
		CODL_ElementBase*	pElement	=NULL;
		for(LONG i=0;i<GetCount();i++)
		{
			pElement	=(CODL_ElementBase*)GetObj(i);
			pElement->OnPreCanvasSizeChange();
		}
		m_Size.cx =cx;
		m_Size.cy =cy;
		ResetCanvas();
		
		PostCallbackMessage(CANVAS_CALLBACKMSG_OnSizeChanged,(LPARAM)this);
		if(m_pListener != NULL)
		{
			m_pListener->OnCanvas_SizeChanged(this);
		}
		for(LONG i=0;i<GetCount();i++)
		{
			pElement	=(CODL_ElementBase*)GetObj(i);
			pElement->OnEndCanvasSizeChange();
		}

	}
	return 0;
}

INT				CODL_GDICanvas::Draw()
{
	if(m_hDrawDC == NULL)
		return -1;
	ClearCanvas(m_hDrawDC);
	CODL_ElementBase*	pElement	=NULL;
	RECT				PaintRect;
	PaintRect.left		=0;
	PaintRect.top		=0;
	PaintRect.right		=m_Size.cx;
	PaintRect.bottom	=m_Size.cy;
	if(!IsMaximized())
		InflateRect(&PaintRect,-2,-2);
	for(LONG i=0;i<GetCount();i++)
	{
		pElement	=(CODL_ElementBase*)GetObj(i);
		pElement->Draw(m_hDrawDC,&PaintRect);
	}
	//------------------------------
	if( m_pView->GetCount() > 1 && !IsMaximized())
		DrawActiveFrame(m_hDrawDC);
	return 0;
}
INT				CODL_GDICanvas::Present()
{
	CODL_GDIPainter*	pPainter	=(CODL_GDIPainter*)m_pView->GetPainter();
	HDC		hDC =pPainter->GetDC();
	BitBlt(hDC,m_Pos.x,m_Pos.y,m_Size.cx,m_Size.cy,m_hDrawDC,0,0,SRCCOPY);
	pPainter->ReleaseDC(hDC);
	return 0;
}
BOOL			CODL_GDICanvas::ResetCanvas()
{
	if(m_hBitmap != NULL)
		DeleteObject(m_hBitmap);
	if(m_hDrawDC != NULL)
		DeleteDC(m_hDrawDC);
	HDC		hDC	=m_pView->GetPainter()->GetDC();
	if(hDC == NULL)
		return FALSE;

	m_hDrawDC	=CreateCompatibleDC(hDC);
	if(m_hDrawDC == NULL)
		return FALSE;

	m_hBitmap	=CreateCompatibleBitmap(hDC,m_Size.cx,m_Size.cy);
	if(m_hBitmap == NULL)
		return FALSE;
	SelectObject(m_hDrawDC,m_hBitmap);
	m_pView->GetPainter()->ReleaseDC(hDC);
	Invalidate(TRUE);	
	return TRUE;
}
BOOL			CODL_GDICanvas::SaveToBmpFile(LPCSTR IN pFileName)
{
	return SaveDCToBmpFile(m_hDrawDC,m_hBitmap,m_Size.cx,m_Size.cy,pFileName);
}
BOOL			CODL_GDICanvas::SaveToClipboard()
{
	return SaveDCToClipboard(m_hDrawDC,m_hBitmap,m_Size.cx,m_Size.cy);
}
