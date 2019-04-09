#include "StdAfx.h"
#include ".\odlex_element_zoomframe.h"
#include ".\ODLEx_Element_Coordinate.h"

CODLEx_Element_ZoomFrame::CODLEx_Element_ZoomFrame(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_ZOOMFRAME;
	m_pFramePen			=NULL;
	m_ptEnd.x=m_ptEnd.y=m_ptStart.x=m_ptStart.y=0;
	m_pFramePen			=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_DOT,1,RGB(50,255,0));
	m_bZoomInit			=FALSE;
	m_ZIndex			=2;
}

CODLEx_Element_ZoomFrame::~CODLEx_Element_ZoomFrame(void)
{
	ODL_SafeRelease(m_pFramePen);
}
VOID				CODLEx_Element_ZoomFrame::SetParameter(UINT IN nPenStyle,UINT IN nPenWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pFramePen);
	m_pFramePen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(nPenStyle,nPenWidth,clr);
}

BOOL				CODLEx_Element_ZoomFrame::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_pFramePen == NULL)
		return FALSE;
	if(!m_bZoomInit)
		return FALSE;
	m_pFramePen->Install(hDC);

	MoveToEx(hDC,m_ptStart.x,m_ptStart.y,NULL);

	LineTo(hDC,m_ptEnd.x,m_ptStart.y);
	LineTo(hDC,m_ptEnd.x,m_ptEnd.y);
	LineTo(hDC,m_ptStart.x,m_ptEnd.y);
	LineTo(hDC,m_ptStart.x,m_ptStart.y);

	m_pFramePen->Uninstall(hDC);
	return TRUE;
}
VOID				CODLEx_Element_ZoomFrame::OnZoom()
{
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return;

	RECT		rect;
	rect.left	=min(m_ptStart.x,m_ptEnd.x);
	rect.top	=min(m_ptStart.y,m_ptEnd.y);
	rect.right	=max(m_ptStart.x,m_ptEnd.x);
	rect.bottom =max(m_ptStart.y,m_ptEnd.y);
	pCoord->ZoomRect(&rect);
}

BOOL				CODLEx_Element_ZoomFrame::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(IsKeyHoldPress(VK_LSHIFT))
			{
				m_ptStart.x		=pPoint->x;
				m_ptStart.y		=pPoint->y;
				m_bZoomInit		=TRUE;
				return TRUE;
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_bZoomInit)
			{
				m_bZoomInit =FALSE;
				OnZoom();
				Invalidate(TRUE);
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(IsKeyHoldPress(VK_LSHIFT) && m_bZoomInit)
			{
				m_ptEnd.x		=pPoint->x;
				m_ptEnd.y		=pPoint->y;
				Invalidate(TRUE);
				return TRUE;
			}
		}
		break;
	}


	return FALSE;
}

