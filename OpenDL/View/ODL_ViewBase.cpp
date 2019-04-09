#include "StdAfx.h"
#include ".\odl_viewbase.h"
#include "../Painter/ODL_GDIPainter.h"
#include "../Canvas/ODL_GDICanvas.h"

CODL_ViewBase::CODL_ViewBase(void)
{
	m_hDeviceWnd		=NULL;				//设备窗体句柄
	m_ViewType			=VIEW_BASE;

	m_BkColor			=RGB(0,0,0);			//背景色
	m_pPainter			=NULL;
	m_PaintRect.left	=0;
	m_PaintRect.right	=0;
	m_PaintRect.top		=0;
	m_PaintRect.bottom	=0;
	m_dwRow				=1;
	m_dwCol				=1;
	m_dwCurFirstCanvasIndex=0;
	m_pCurActiveCanvas	=NULL;
	m_pResourceManager	=new CODL_ResourceManager;

	m_bDraging			=FALSE;	
	m_bDragingChangeSize=FALSE;
	m_DragOffset.x		=0;
	m_DragOffset.y		=0;
	m_dwCanvasMarginSpace =5;
	m_OldWndProc		=NULL;
	m_ViewStyle			=OVS_TILES;
	m_pListener			=NULL;
}

CODL_ViewBase::~CODL_ViewBase(void)
{
	UnhookWndProc();
	ODL_SafeRelease(m_pPainter);
	ODL_SafeRelease(m_pResourceManager);
}

INT		CODL_ViewBase::Create(	HWND			IN hDeviceWnd		,
								COLORREF		IN BkColor)
{
	if(!IsWindow(hDeviceWnd))
		return -1;
	if(m_pPainter != NULL)
		return -2;

	m_hDeviceWnd		=hDeviceWnd;
	m_BkColor			=BkColor;

	m_pPainter		=new CODL_GDIPainter(this);

	GetClientRect(m_hDeviceWnd,&m_PaintRect);
	HookWndProc();

	return m_pPainter->Create(m_hDeviceWnd);

}
INT				CODL_ViewBase::Create(	HWND		IN hDeviceWnd,
										RECT*		IN pPaintRect,
										BOOL		IN bFixedSize,
										COLORREF	IN BkColor)
{

	if(!IsWindow(hDeviceWnd))
		return -1;
	if(m_pPainter != NULL)
		return -2;

	m_hDeviceWnd		=hDeviceWnd;
	m_BkColor			=BkColor;

	m_pPainter			=new CODL_GDIPainter(this);

	m_PaintRect			=*pPaintRect;
	HookWndProc();

	return m_pPainter->Create(m_hDeviceWnd,pPaintRect,bFixedSize);

}


INT		CODL_ViewBase::Create( HDC		IN hDC,
							   HWND		IN hEventWnd,
							   COLORREF	IN BkColor)
{
	if(!IsWindow(hEventWnd))
		return -1;
	if(m_pPainter != NULL)
		return -2;
	m_hDeviceWnd		=hEventWnd;
	m_BkColor			=BkColor;
	m_pPainter			=new CODL_GDIPainter(this);
	GetClientRect(m_hDeviceWnd,&m_PaintRect);
	HookWndProc();

	return m_pPainter->Create(m_hDeviceWnd,hDC);
}
INT		CODL_ViewBase::Create(	HDC			IN hDC,
								HWND		IN hEventWnd,
								RECT*		IN pPaintRect,
								BOOL		IN bFixedSize,
								COLORREF	IN BkColor)
{
	if(!IsWindow(hEventWnd))
		return -1;
	if(m_pPainter != NULL)
		return -2;
	m_hDeviceWnd		=hEventWnd;
	m_BkColor			=BkColor;

	m_pPainter			=new CODL_GDIPainter(this);
	m_PaintRect			=*pPaintRect;
	HookWndProc();

	return m_pPainter->Create(m_hDeviceWnd,pPaintRect,bFixedSize,hDC);
}


BOOL	CODL_ViewBase::HookWndProc()
{
  m_OldWndProc = (WNDPROC)SetWindowLongPtr(m_hDeviceWnd, GWLP_WNDPROC, (LONG_PTR)dumpWndProc);
  SetWindowLongPtr(m_hDeviceWnd, GWLP_USERDATA, (LONG_PTR)this);
	return TRUE;
}
VOID	CODL_ViewBase::UnhookWndProc()
{
    SetWindowLongPtr(m_hDeviceWnd, GWLP_WNDPROC, (LONG_PTR)m_OldWndProc);
}
LRESULT	CODL_ViewBase::CallOldWndProc(
									   HWND hwnd,
									   UINT uMsg,
									   WPARAM wParam,
									   LPARAM lParam
									   )
{
	return m_OldWndProc(hwnd,uMsg,wParam,lParam);
}
LRESULT CODL_ViewBase::dumpWndProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam
							)
{
	LRESULT		result=0,ret=0;
	CODL_ViewBase* pView =(CODL_ViewBase*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
	if(pView != NULL)
	{
		ret=pView->CallOldWndProc(hwnd,uMsg,wParam,lParam);
		if(uMsg != WM_NCDESTROY && uMsg != WM_DESTROY)
		{
			pView->OnWndMsg(uMsg,wParam,lParam,&result);
		}
	}
	return ret;
}

BOOL	CODL_ViewBase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if(m_pPainter->OnWndMsg(message, wParam, lParam, pResult))
		return TRUE;

	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas != NULL)
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(m_hDeviceWnd,&pt);

		RECT	canvas_rect;
		pActiveCanvas->GetRect(canvas_rect);
		POINT	point;
		point.x		=pt.x - canvas_rect.left	- m_PaintRect.left;
		point.y		=pt.y - canvas_rect.top	- m_PaintRect.top;
		if(pActiveCanvas->OnWndMsg(message, wParam, lParam, pResult,&point))
			return TRUE;
	}


	switch(message)
	{
	case WM_SIZE:
		{
			//更新当前绘图视区域
			m_PaintRect =*m_pPainter->GetPaintRect();
			LayoutCanvas();
			Invalidate();
		}
		break;
	case WM_PAINT:
		{
			if(IsWindowVisible(m_hDeviceWnd))
			{
				m_PaintRect =*m_pPainter->GetPaintRect();
				m_pPainter->OnPreRender();
				m_pPainter->Render();
				m_pPainter->OnEndRender();
			}
		}
		break;
	case WM_KEYDOWN:
		{
			OnKeyDown(wParam,lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			OnLButtonDown(wParam,lParam);
		}
		break;
	case WM_LBUTTONUP:
		{
			OnLButtonUp(wParam,lParam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			OnMouseMove(wParam,lParam);
		}
		break;
	}
	return FALSE;
}
VOID		CODL_ViewBase::Update()
{
	//更新当前绘图视区域
	m_PaintRect =*m_pPainter->GetPaintRect();
	//---------------------------------
	//更新当前所有的画布内容
	OnUpdate();
	//---------------------------------
	if(m_bDraging)
	{
		POINT	point;
		GetCursorPos(&point);
		ScreenToClient(m_hDeviceWnd,&point);
		point.x -= m_PaintRect.left;
		point.y -= m_PaintRect.top;
		DrawDragFrame(point);
	}
}
BOOL		CODL_ViewBase::SetCanvasLayout(DWORD IN dwRow,DWORD IN dwCol)
{
	if(dwCol <= 0 || dwRow <= 0)
		return FALSE;
	if(m_dwCol != dwCol || m_dwRow != dwRow)
	{
		m_dwRow		=dwRow;
		m_dwCol		=dwCol;
		LayoutCanvas();
		Invalidate();
	}
	return TRUE;
}
VOID		CODL_ViewBase::GetCanvasLayout(DWORD& OUT dwRow,DWORD& OUT dwCol)
{
	dwRow		=m_dwRow;
	dwCol		=m_dwCol;
}

BOOL		CODL_ViewBase::LayoutCanvas(BOOL IN bViewStyleChanged)//重新分布画布
{

	DWORD		w			=abs(m_PaintRect.right-m_PaintRect.left);
	DWORD		h			=abs(m_PaintRect.bottom-m_PaintRect.top);

	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas != NULL)
	{
		if(pActiveCanvas->IsMaximized())
		{
			pActiveCanvas->SetPos(0,0);
			pActiveCanvas->SetSize(w,h);			
			return TRUE;
		}
	}
	DWORD		totalColMargin =(m_dwCol+1)*m_dwCanvasMarginSpace;
	if(w <= totalColMargin + m_dwCol*5)
		return FALSE;
	DWORD		totalRowMargin =(m_dwRow+1)*m_dwCanvasMarginSpace;
	if(h <= totalRowMargin + m_dwRow*5)
		return FALSE;
	DWORD		dwWidth		= (w-totalColMargin) / m_dwCol;
	DWORD		dwHeight	= (h-totalRowMargin) / m_dwRow;
	DWORD		endIndex	= min(GetCount(),m_dwCurFirstCanvasIndex+m_dwRow*m_dwCol);

	switch(m_ViewStyle)
	{
	case OVS_TILES:
		{

			DWORD		dwColIndex=0,dwRowIndex=0;
			CODL_CanvasBase*		pCanvas;
			for(DWORD i=m_dwCurFirstCanvasIndex;i<endIndex;)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;
				if(bViewStyleChanged)
					pCanvas->SaveState();

				pCanvas->SetPos(dwColIndex*dwWidth + (dwColIndex+1)*m_dwCanvasMarginSpace,
					dwRowIndex*dwHeight+ (dwRowIndex+1)*m_dwCanvasMarginSpace);

				pCanvas->SetSize(dwWidth,dwHeight);

				i++;
				dwColIndex++;
				if(i!=m_dwCurFirstCanvasIndex && (i-m_dwCurFirstCanvasIndex)%m_dwCol == 0)
				{
					dwRowIndex++;
					dwColIndex = 0;
				}
			}
		}
		break;
	case OVS_CASCADE:
		{
			CODL_CanvasBase*		pCanvas;
			POINT					pos;
			pos.x=pos.y=10;
			for(DWORD i=0;i<GetCount();i++)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;

				if(pCanvas->IsSavedState())
				{
					pCanvas->RestoreState();
				}
				else
				{
					pCanvas->SetPos(&pos);
					pCanvas->SetSize(dwWidth,dwHeight);
					pos.x+=15;
					pos.y+=15;
					if(pos.x>=w||pos.y>=h)
						pos.x=pos.y=10;
				}
			}
		}
		break;
	}


	return TRUE;
}
BOOL		CODL_ViewBase::PageDown()
{
	if(m_ViewStyle!=OVS_TILES)
		return FALSE;
	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas != NULL)
	{
		if(pActiveCanvas->IsMaximized())
		{
			return FALSE;
		}
	}


	DWORD	index =m_dwCurFirstCanvasIndex + (m_dwCol*m_dwRow);
	if( index >= GetCount())
		return FALSE;
	m_dwCurFirstCanvasIndex		=index;
	LayoutCanvas();
	Invalidate();
	return TRUE;
}
BOOL		CODL_ViewBase::PageUp()
{
	if(m_ViewStyle!=OVS_TILES)
		return FALSE;

	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas != NULL)
	{
		if(pActiveCanvas->IsMaximized())
		{
			return FALSE;
		}
	}

	if(m_dwCurFirstCanvasIndex == 0)
		return FALSE;
	if(m_dwCurFirstCanvasIndex <= (m_dwCol*m_dwRow) )
	{
		m_dwCurFirstCanvasIndex =0;
	}
	else
	{
		m_dwCurFirstCanvasIndex -= (m_dwCol*m_dwRow);
	}
	LayoutCanvas();
	Invalidate();
	return TRUE;
}
CODL_CanvasBase*		CODL_ViewBase::GetActiveCanvas()
{
	return m_pCurActiveCanvas;
}
VOID					CODL_ViewBase::SetActiveCanvas(CODL_CanvasBase* IN pCanvas)
{
	m_pCurActiveCanvas = pCanvas;
}
CODL_CanvasBase*		CODL_ViewBase::PointSelectCanvas(POINT IN pt)
{
	POINT	point;
	point.x		=pt.x	- m_PaintRect.left;
	point.y		=pt.y	- m_PaintRect.top;
	CODL_CanvasBase*		pCanvas;
	switch(m_ViewStyle)
	{
	case OVS_TILES:
		{
			DWORD		endIndex	= min(GetCount(),m_dwCurFirstCanvasIndex+m_dwRow*m_dwCol);
			for(DWORD i=m_dwCurFirstCanvasIndex;i<endIndex;i++)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;
				if(pCanvas->PointInCanvas(&point))
					return pCanvas;
			}
		}
		break;
	case OVS_CASCADE:
		{
			for(LONG i=GetCount()-1;i>=0;i--)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;
				if(pCanvas->PointInCanvas(&point))
					return pCanvas;
			}
		}
		break;
	}
	return NULL;
}

VOID		CODL_ViewBase::Invalidate()
{
	::InvalidateRect(m_hDeviceWnd,&m_PaintRect,FALSE);
}
CODL_CanvasBase*		CODL_ViewBase::GetCanvasByName(LPCSTR IN pName)
{
	if(pName == NULL)
		return NULL;

	CODL_CanvasBase*	pCanvas =NULL;
	for(LONG i=0;i<GetCount();i++)
	{
		pCanvas =(CODL_CanvasBase*)GetObj(i);
		if(pCanvas == NULL)
			continue;
		if( strcmp(pCanvas->GetName(),pName) == 0 )
		{
			return pCanvas;
		}

	}
	return NULL;
}
BOOL		CODL_ViewBase::AddCanvas(CODL_CanvasBase* IN pCanvas)
{
	if(pCanvas == NULL)
		return FALSE;
	if(pCanvas->GetName() == NULL)
		return FALSE;
	if(GetCanvasByName(pCanvas->GetName()) != NULL)
		return FALSE;
	AddObj(pCanvas);
	if(m_pCurActiveCanvas == NULL)
	{
		pCanvas->Active();
	}
	LayoutCanvas();


	return TRUE;
}	
CODL_CanvasBase*		CODL_ViewBase::AddNewCanvas(LPCSTR IN pName)
{
	if(pName == NULL)
		return NULL;
	if(GetCanvasByName(pName) != NULL)
		return NULL;

	CODL_CanvasBase*	pCanvas =NULL;
	pCanvas		=new CODL_GDICanvas(this);
	if(pCanvas->Create(pName)!=0)
	{
		ODL_SafeRelease(pCanvas);
		return NULL;
	}
	AddObj(pCanvas);
	pCanvas->Active();
	LayoutCanvas();
	return pCanvas;
}

VOID			CODL_ViewBase::OnKeyDown(WPARAM IN wp,LPARAM IN lp)
{
	switch(wp)
	{
	case VK_PRIOR:
		{
			PageUp();
		}
		break;
	case VK_NEXT:
		{
			PageDown();
		}
		break;
	default:
		break;
	}
}
VOID			CODL_ViewBase::OnLButtonDown(WPARAM IN wp,LPARAM IN lp)
{

	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas != NULL)
	{
		if(pActiveCanvas->IsMaximized())
			return;
	}

	POINTS	pt	=MAKEPOINTS(lp);
	
	POINT	point;
	point.x		=pt.x	- m_PaintRect.left;
	point.y		=pt.y	- m_PaintRect.top;

	CODL_CanvasBase*		pCanvas;
	switch(m_ViewStyle)
	{
	case OVS_TILES:
		{
			DWORD		endIndex	= min(GetCount(),m_dwCurFirstCanvasIndex+m_dwRow*m_dwCol);
			for(DWORD i=m_dwCurFirstCanvasIndex;i<endIndex;i++)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;
				if(pCanvas->PointInCanvas(&point))
				{
					pCanvas->Active();
					Invalidate();
					break;
				}
			}
			if( ( GetKeyState(VK_LCONTROL) & 0xff00 ) != 0 || ( GetKeyState(VK_RCONTROL) & 0xff00 ) != 0 )
			{
				pCanvas		=GetActiveCanvas();
				if(pCanvas != NULL)
				{
					if(!pCanvas->IsMaximized())
					{
						m_bDraging	=TRUE;
						m_DragOffset.x	=pCanvas->GetPos()->x - point.x;
						m_DragOffset.y	=pCanvas->GetPos()->y - point.y;	
					}
				}
			}



		}
		break;
	case OVS_CASCADE:
		{
			for(LONG i=GetCount()-1;i>=0;i--)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;
				if(pCanvas->PointInCanvas(&point))
				{
					pCanvas->SaveState();
					SetCanvasTopLayer(pCanvas);
					pCanvas->Active();
					Invalidate();
					break;
				}
			}

			if( ( GetKeyState(VK_LCONTROL) & 0xff00 ) != 0 || ( GetKeyState(VK_RCONTROL) & 0xff00 ) != 0)
			{
				pCanvas		=GetActiveCanvas();
				if(pCanvas != NULL)
				{
					if(!pCanvas->IsMaximized()&&pCanvas->PointInCanvas(&point))
					{
						m_bDraging	=TRUE;
						if(pCanvas->PointInCanvasChangeSizeButton(&point))
						{
							m_bDragingChangeSize=TRUE;
							m_DragOffset.x	=(pCanvas->GetPos()->x+pCanvas->GetSize()->cx) - point.x;
							m_DragOffset.y	=(pCanvas->GetPos()->y+pCanvas->GetSize()->cy) - point.y;
							::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
						}
						else
						{
							m_DragOffset.x	=pCanvas->GetPos()->x - point.x;
							m_DragOffset.y	=pCanvas->GetPos()->y - point.y;	
						}
					}
				}
			}


		}
		break;
	}


}
VOID			CODL_ViewBase::OnLButtonUp(WPARAM IN wp,LPARAM IN lp)
{
	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas != NULL)
	{
		if(pActiveCanvas->IsMaximized())
			return;
	}

	POINTS	pt	=MAKEPOINTS(lp);
	POINT	point;
	point.x		=pt.x	- m_PaintRect.left;
	point.y		=pt.y	- m_PaintRect.top;

	if(m_bDraging)
	{
		OnEndDrag(point);
		m_bDraging	=FALSE;
		m_bDragingChangeSize=FALSE;
		Invalidate();
	}

}

VOID			CODL_ViewBase::OnMouseMove(WPARAM IN wp,LPARAM IN lp)
{
	POINTS	pt	=MAKEPOINTS(lp);

	POINT	point;
	point.x		=pt.x	- m_PaintRect.left;
	point.y		=pt.y	- m_PaintRect.top;

	BOOL bLAlt	=(GetKeyState(VK_LCONTROL) & 0xff00 ) != 0;
	BOOL bRAlt	=(GetKeyState(VK_RCONTROL) & 0xff00 ) != 0;
	if( (bLAlt||bRAlt) )
	{
		CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
		if(pActiveCanvas == NULL)
			return;
		if(pActiveCanvas->IsMaximized())
			return;
		if(pActiveCanvas->PointInCanvasChangeSizeButton(&point)||
			m_bDragingChangeSize)
		{
			::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
		}
		if(m_bDraging)
			Invalidate();		
	}

}
VOID			CODL_ViewBase::DrawDragFrame(POINT IN pt)
{
	CODL_CanvasBase*	pCanvas		=GetActiveCanvas();
	if(pCanvas == NULL)
		return;
	if(pCanvas->IsMaximized())
		return;
	RECT	rect;

	switch(m_ViewStyle)
	{
	case OVS_TILES:
		{
			rect.left	=pt.x + m_DragOffset.x;
			rect.top	=pt.y + m_DragOffset.y;
			rect.right	=rect.left + pCanvas->GetSize()->cx;
			rect.bottom =rect.top  + pCanvas->GetSize()->cy;
		}
		break;
	case OVS_CASCADE:
		{
			if(m_bDragingChangeSize)
			{
				rect.left	=pCanvas->GetPos()->x;
				rect.top	=pCanvas->GetPos()->y;
				rect.right	=pt.x + m_DragOffset.x;
				rect.bottom	=pt.y + m_DragOffset.y;

				if(rect.right <rect.left+10)
					rect.right=rect.left+10;
				if(rect.bottom<rect.top+10)
					rect.bottom=rect.top+10;

				pCanvas->SetSize(rect.right-rect.left,rect.bottom-rect.top);
			}
			else
			{
				rect.left	=pt.x + m_DragOffset.x;
				rect.top	=pt.y + m_DragOffset.y;
				rect.right	=rect.left + pCanvas->GetSize()->cx;
				rect.bottom =rect.top  + pCanvas->GetSize()->cy;
				pCanvas->SetPos(rect.left,rect.top);
			}
			pCanvas->OnUpdate();
		}
		break;
	}
	InflateRect(&rect,-1,-1);
	m_pPainter->DrawRect(&rect,2,RGB(155,155,100));
}
VOID			CODL_ViewBase::OnEndDrag(POINT IN pt)
{
	CODL_CanvasBase*	pActiveCanvas		=GetActiveCanvas();
	if(pActiveCanvas == NULL)
		return;
	if(pActiveCanvas->IsMaximized())
		return;


	switch(m_ViewStyle)
	{
	case OVS_TILES:
		{
			RECT	rect,CanvasRect,inRect;
			rect.left	=pt.x + m_DragOffset.x;
			rect.top	=pt.y + m_DragOffset.y;
			rect.right	=rect.left + pActiveCanvas->GetSize()->cx;
			rect.bottom =rect.top  + pActiveCanvas->GetSize()->cy;

			DWORD		endIndex	= min(GetCount(),m_dwCurFirstCanvasIndex+m_dwRow*m_dwCol);
			CODL_CanvasBase*		pCanvas;
			for(DWORD i=m_dwCurFirstCanvasIndex;i<endIndex;i++)
			{
				pCanvas		=(CODL_CanvasBase*)GetObj(i);
				if(pCanvas == NULL)
					continue;
				if(pCanvas == pActiveCanvas)
					continue;

				pCanvas->GetRect(CanvasRect);
				if(IntersectRect(&inRect,&rect,&CanvasRect))
				{
					if( (inRect.right-inRect.left)*(inRect.bottom-inRect.top) > (CanvasRect.right-CanvasRect.left)*(CanvasRect.bottom-CanvasRect.top)*0.5f )
					{
						Swap(pCanvas,pActiveCanvas);
						LayoutCanvas();
						Invalidate();
						if(m_pListener != NULL)
						{
							m_pListener->OnCanvas_Swaped(pActiveCanvas,pCanvas);
						}
						break;
					}
				}	
			}
		}
		break;
	case OVS_CASCADE:
		{
			RECT	rect;
			if(m_bDragingChangeSize)
			{
				rect.left	=pActiveCanvas->GetPos()->x;
				rect.top	=pActiveCanvas->GetPos()->y;
				rect.right	=pt.x + m_DragOffset.x;
				rect.bottom	=pt.y + m_DragOffset.y;

				if(rect.right <rect.left+10)
					rect.right=rect.left+10;
				if(rect.bottom<rect.top+10)
					rect.bottom=rect.top+10;

				pActiveCanvas->SetSize(rect.right-rect.left,rect.bottom-rect.top);
			}
			else
			{
				rect.left	=pt.x + m_DragOffset.x;
				rect.top	=pt.y + m_DragOffset.y;
				rect.right	=rect.left + pActiveCanvas->GetSize()->cx;
				rect.bottom =rect.top  + pActiveCanvas->GetSize()->cy;
				pActiveCanvas->SetPos(rect.left,rect.top);
			}

			pActiveCanvas->SaveState();
			LayoutCanvas();
			Invalidate();
		}
		break;
	}


}
BOOL			CODL_ViewBase::SaveToBmpFile(LPCSTR IN pFileName)
{
	return m_pPainter->SaveToBmpFile(pFileName);
}
BOOL			CODL_ViewBase::SaveToClipboard()
{
	return m_pPainter->SaveToClipboard();
}
VOID			CODL_ViewBase::SetViewStyle(ODL_VIEW_STYLE IN style)
{
	if(m_ViewStyle == style)
		return;
	m_ViewStyle	=style;
	LayoutCanvas(TRUE);
	Invalidate();

	if(m_pListener != NULL)
	{
		m_pListener->OnView_StyleChanged(this);
	}

}
VOID			CODL_ViewBase::SetCanvasTopLayer(CODL_CanvasBase* IN pCanvas)
{
	if(pCanvas == NULL || m_ViewStyle != OVS_CASCADE)
		return;
	pCanvas->AddRef();
	DelObj(pCanvas);
	AddCanvas(pCanvas);
	
	pCanvas->Release();

	if(m_pListener != NULL)
	{
		m_pListener->OnCanvas_ToTopLayer(pCanvas);
	}
}
VOID			CODL_ViewBase::SetPaintRect(RECT* IN pPaintRect)
{
	m_PaintRect			=*pPaintRect;
	m_pPainter->SetPaintRect(pPaintRect);
	Invalidate();
}
VOID			CODL_ViewBase::SetListener(CODL_Listener* IN pListener)
{
	m_pListener		=pListener;
}

