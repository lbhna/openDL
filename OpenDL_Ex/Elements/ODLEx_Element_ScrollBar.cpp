#include "stdafx.h"
#include "./ODLEx_Element_ScrollBar.h"



CODLEx_Element_ScrollBar::CODLEx_Element_ScrollBar(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type					=ODL_ELEMENT_SCROLLBAR;
	m_pScrollCallback		=NULL;
	m_CallbackUserData		=0;
	m_Pos.x					=0;
	m_Pos.y					=0;
	m_Size.cx				=20;
	m_Size.cy				=100;
	m_bDragingScrollBar		=FALSE;
	m_pArrowBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(0,20,50),0);

	m_pSpinBarBrightBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(100,200,200),0);
	m_pSpinBarNormalBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(80,150,150),0);
	m_pSpinBarDarkBrush		=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(10,50,50),0);

	m_pScrollBarBrightBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(100,200,200),0);
	m_pScrollBarNormalBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(80,150,150),0);
	m_pScrollBarDarkBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(10,50,50),0);

	m_pBackBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_HATCHED,RGB(55,125,125),HS_CROSS);

	ZeroMemory(&m_BackRect,sizeof(m_BackRect));
	ZeroMemory(m_SpinRect,sizeof(m_SpinRect));
	ZeroMemory(&m_ScrollBarRect,sizeof(m_ScrollBarRect));
	ZeroMemory(&m_ScrollBarActiveRect,sizeof(m_ScrollBarActiveRect));

	m_bHorizontal	=FALSE;	//是否是水平方向
	m_lPosition		=0;
	m_lMaxPosition	=100;
	m_lPageSize		=50;	//一页大小

	m_ptDragOffset.x		=0;
	m_ptDragOffset.y		=0;
	m_bSpinIsPressed[0]		=FALSE;
	m_bSpinIsPressed[1]		=FALSE;
	m_lTimerCounter			=0;
}
CODLEx_Element_ScrollBar::~CODLEx_Element_ScrollBar()
{
	ODL_SafeRelease(m_pArrowBrush);
	ODL_SafeRelease(m_pSpinBarNormalBrush);
	ODL_SafeRelease(m_pScrollBarNormalBrush);
	ODL_SafeRelease(m_pSpinBarBrightBrush);
	ODL_SafeRelease(m_pSpinBarDarkBrush);
	ODL_SafeRelease(m_pScrollBarBrightBrush);
	ODL_SafeRelease(m_pScrollBarDarkBrush);
	ODL_SafeRelease(m_pBackBrush);
}
VOID		CODLEx_Element_ScrollBar::SetScrollCallbackFunction(SCROLL_CALLBACK IN pCallback,DWORD_PTR IN dwUserData)
{
	m_pScrollCallback	=pCallback;
	m_CallbackUserData	=dwUserData;
}
VOID		CODLEx_Element_ScrollBar::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
}
PPOINT		CODLEx_Element_ScrollBar::GetPos()
{
	return &m_Pos;
}
VOID		CODLEx_Element_ScrollBar::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
}
PSIZE		CODLEx_Element_ScrollBar::GetSize()
{
	return &m_Size;
}
VOID		CODLEx_Element_ScrollBar::SetPageSize(LONG IN lSize)
{
	m_lPageSize	=lSize;
	if(m_lPosition > (m_lMaxPosition-m_lPageSize))
		m_lPosition =(m_lMaxPosition-m_lPageSize);
	if(m_lPosition<0)
		m_lPosition=0;
	Invalidate();
}
LONG		CODLEx_Element_ScrollBar::GetPageSize()
{
	return m_lPageSize;
}
VOID		CODLEx_Element_ScrollBar::SetPosition(LONG IN lPosition)
{
	m_lPosition	=lPosition;
	if(m_lPosition > (m_lMaxPosition-m_lPageSize))
		m_lPosition =(m_lMaxPosition-m_lPageSize);
	if(m_lPosition<0)
		m_lPosition=0;
	Invalidate();
}
LONG		CODLEx_Element_ScrollBar::GetPosition()
{
	return m_lPosition;
}
VOID		CODLEx_Element_ScrollBar::SetMaxPosition(LONG IN lMaxPosition)
{
	m_lMaxPosition	=lMaxPosition;
	Invalidate();
}
LONG		CODLEx_Element_ScrollBar::GetMaxPosition()
{
	return m_lMaxPosition;
}

VOID		CODLEx_Element_ScrollBar::UpdateAllRect()
{
	m_BackRect.left		=m_Pos.x;
	m_BackRect.top		=m_Pos.y;
	m_BackRect.right	=m_Pos.x + m_Size.cx;
	m_BackRect.bottom	=m_Pos.y + m_Size.cy;

	LONG	spinSize;
	if(m_bHorizontal)
	{
		spinSize =m_Size.cy;
	}
	else
	{
		spinSize =m_Size.cx;
	}
	m_SpinRect[0].left		=m_Pos.x;
	m_SpinRect[0].top		=m_Pos.y;
	m_SpinRect[0].right		=m_SpinRect[0].left + spinSize;
	m_SpinRect[0].bottom	=m_SpinRect[0].top  + spinSize;

	m_SpinRect[1].right		=m_BackRect.right;
	m_SpinRect[1].bottom	=m_BackRect.bottom;
	m_SpinRect[1].left		=m_SpinRect[1].right -spinSize;
	m_SpinRect[1].top		=m_SpinRect[1].bottom-spinSize;


	SIZE	scrollSize;
	ZeroMemory(&m_ScrollBarRect,sizeof(m_ScrollBarRect));
	if(m_lMaxPosition > m_lPageSize)
	{
		FLOAT	fPercent	=1.0f/((FLOAT)m_lMaxPosition/(FLOAT)m_lPageSize);
		FLOAT	fScale		=1.0f;
		if(m_bHorizontal)
		{
			scrollSize.cy			=m_Size.cy;
			scrollSize.cx			=(m_Size.cx-spinSize*2) * fPercent+0.5f;
			if(scrollSize.cx<5)
				scrollSize.cx=5;
		
			fScale					=(FLOAT)(m_Size.cx-spinSize*2/*-scrollSize.cx*/)/(FLOAT)m_lMaxPosition;

			m_ScrollBarRect.left	=m_Pos.x+spinSize + fScale*m_lPosition+0.5f; 
			m_ScrollBarRect.top		=m_Pos.y;
			m_ScrollBarRect.right	=m_ScrollBarRect.left	+ scrollSize.cx;
			m_ScrollBarRect.bottom	=m_ScrollBarRect.top	+ scrollSize.cy;

		}
		else
		{
			scrollSize.cy	=(m_Size.cy-spinSize*2)* fPercent+0.5f;
			if(scrollSize.cy<5)
				scrollSize.cy=5;
			scrollSize.cx	=m_Size.cx ;
		
			fScale					=(FLOAT)(m_Size.cy-spinSize*2 /*-scrollSize.cy*/)/(FLOAT)m_lMaxPosition;
			m_ScrollBarRect.left	=m_Pos.x; 
			m_ScrollBarRect.top		=m_Pos.y+spinSize + fScale*m_lPosition+0.5f;
			m_ScrollBarRect.right	=m_ScrollBarRect.left	+ scrollSize.cx;
			m_ScrollBarRect.bottom	=m_ScrollBarRect.top	+ scrollSize.cy;


		}

	}

	m_ScrollBarActiveRect		=m_BackRect;
	if(m_bHorizontal)
	{
		m_ScrollBarActiveRect.left	+= spinSize;
		m_ScrollBarActiveRect.right	-= spinSize;
	}
	else
	{
		m_ScrollBarActiveRect.top	+= spinSize;
		m_ScrollBarActiveRect.bottom-= spinSize;
	}
}

BOOL		CODLEx_Element_ScrollBar::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	UpdateAllRect();
	OnDrawBackBar(hDC,pPaintRect);
	OnDrawSpinButton(hDC,pPaintRect);
	OnDrawScrollBar(hDC,pPaintRect);
	return TRUE;
}
VOID		CODLEx_Element_ScrollBar::OnDrawBackBar(HDC IN hDC,RECT* IN pPaintRect)
{
	FillRect(hDC,&m_BackRect,m_pBackBrush->GetBrush());
}
VOID		CODLEx_Element_ScrollBar::OnDrawSpinButton(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT rect;
	if(m_bSpinIsPressed[0])
	{
		FillRect(hDC,&m_SpinRect[0],m_pSpinBarDarkBrush->GetBrush());
		rect		=m_SpinRect[0];
		rect.left	+= 1;
		rect.top	+= 1;
		FillRect(hDC,&rect,m_pSpinBarBrightBrush->GetBrush());

		rect.right	-=1;
		rect.bottom -=1;
		FillRect(hDC,&rect,m_pSpinBarNormalBrush->GetBrush());
	}
	else
	{
		FillRect(hDC,&m_SpinRect[0],m_pSpinBarBrightBrush->GetBrush());
		rect		=m_SpinRect[0];
		rect.left	+= 1;
		rect.top	+= 1;
		FillRect(hDC,&rect,m_pSpinBarDarkBrush->GetBrush());
		
		rect.right	-=1;
		rect.bottom -=1;
		FillRect(hDC,&rect,m_pSpinBarNormalBrush->GetBrush());
	}
	if(m_bSpinIsPressed[1])
	{
		FillRect(hDC,&m_SpinRect[1],m_pSpinBarDarkBrush->GetBrush());
		rect		=m_SpinRect[1];
		rect.left	+= 1;
		rect.top	+= 1;
		FillRect(hDC,&rect,m_pSpinBarBrightBrush->GetBrush());

		rect.right	-=1;
		rect.bottom -=1;
		FillRect(hDC,&rect,m_pSpinBarNormalBrush->GetBrush());
	}
	else
	{
		FillRect(hDC,&m_SpinRect[1],m_pSpinBarBrightBrush->GetBrush());
		rect		=m_SpinRect[1];
		rect.left	+= 1;
		rect.top	+= 1;
		FillRect(hDC,&rect,m_pSpinBarDarkBrush->GetBrush());

		rect.right	-=1;
		rect.bottom -=1;
		FillRect(hDC,&rect,m_pSpinBarNormalBrush->GetBrush());


	}
	LONG lInflate =(m_SpinRect[0].right-m_SpinRect[0].left)*0.2f;

	rect	=m_SpinRect[0];
	InflateRect(&rect,-lInflate,-lInflate);
	DrawTriangle(hDC,&rect,m_pArrowBrush,m_bHorizontal,FALSE);
	rect	=m_SpinRect[1];
	InflateRect(&rect,-lInflate,-lInflate);
	DrawTriangle(hDC,&rect,m_pArrowBrush,m_bHorizontal,TRUE);



}
VOID		CODLEx_Element_ScrollBar::OnDrawScrollBar(HDC IN hDC,RECT* IN pPaintRect)
{
	FillRect(hDC,&m_ScrollBarRect,m_pScrollBarBrightBrush->GetBrush());
	RECT rect =m_ScrollBarRect;
	rect.left	+= 1;
	rect.top	+= 1;
	FillRect(hDC,&rect,m_pScrollBarDarkBrush->GetBrush());
	
	rect.right	-=1;
	rect.bottom -=1;
	FillRect(hDC,&rect,m_pScrollBarNormalBrush->GetBrush());
}


VOID		CODLEx_Element_ScrollBar::DrawTriangle(HDC IN hDC,RECT* IN rect,CODL_Brush* IN pBrush,BOOL IN bHorizontal,BOOL IN bInvertDirect)
{
	POINT	pt[4];
	if(bHorizontal)
	{
		if(bInvertDirect)
		{
			pt[0].x		=rect->right;
			pt[0].y		=rect->top + (rect->bottom-rect->top)/2;

			pt[1].x		=rect->left;
			pt[1].y		=rect->top;

			pt[2].x		=rect->left;
			pt[2].y		=rect->bottom;

		}
		else
		{
			pt[0].x		=rect->left;
			pt[0].y		=rect->top + (rect->bottom-rect->top)/2;

			pt[1].x		=rect->right;
			pt[1].y		=rect->top;

			pt[2].x		=rect->right;
			pt[2].y		=rect->bottom;

		}
	}
	else
	{
		if(bInvertDirect)
		{
			pt[0].x		=rect->left + (rect->right-rect->left)/2;
			pt[0].y		=rect->bottom;

			pt[1].x		=rect->left;
			pt[1].y		=rect->top;

			pt[2].x		=rect->right;
			pt[2].y		=rect->top;

		}
		else
		{
			pt[0].x		=rect->left + (rect->right-rect->left)/2;
			pt[0].y		=rect->top;

			pt[1].x		=rect->left;
			pt[1].y		=rect->bottom;

			pt[2].x		=rect->right;
			pt[2].y		=rect->bottom;


		}
	}
	HRGN	hRgn	=CreatePolygonRgn(pt,3,ALTERNATE);
	FillRgn(hDC,hRgn,pBrush->GetBrush());
	DeleteObject(hRgn);
}
BOOL		CODLEx_Element_ScrollBar::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(m_lPageSize > m_lMaxPosition)
		return FALSE;

	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(PtInRect(&m_SpinRect[0],*pPoint))
			{
				m_bSpinIsPressed[0]=TRUE;
				m_bSpinIsPressed[1]=FALSE;
				m_lTimerCounter		=1;
				Invalidate(TRUE);
				::SetTimer(m_pCanvas->GetView()->GetDeviceWnd(),(UINT_PTR)this,500,(TIMERPROC)SpinHoldPressTimer);
				return TRUE;
			}
			if(PtInRect(&m_SpinRect[1],*pPoint))
			{
				m_bSpinIsPressed[1]=TRUE;
				m_bSpinIsPressed[0]=FALSE;
				m_lTimerCounter		=1;
				Invalidate(TRUE);
				::SetTimer(m_pCanvas->GetView()->GetDeviceWnd(),(UINT_PTR)this,500,(TIMERPROC)SpinHoldPressTimer);
				return TRUE;
			}
			if(PtInRect(&m_ScrollBarRect,*pPoint))
			{
				m_bDragingScrollBar	=TRUE;
				m_ptDragOffset.x	=pPoint->x - m_ScrollBarRect.left;
				m_ptDragOffset.y	=pPoint->y - m_ScrollBarRect.top;
				return TRUE;
			}
			if(PtInRect(&m_BackRect,*pPoint))
				return TRUE;
			
		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_bSpinIsPressed[0] || m_bSpinIsPressed[1] || m_bDragingScrollBar)
			{
				if(m_bSpinIsPressed[0])
					m_lPosition--;
				if(m_bSpinIsPressed[1])
					m_lPosition++;
				if(m_lPosition<0)
					m_lPosition=0;
				if(m_lPosition>(m_lMaxPosition-m_lPageSize))
					m_lPosition=(m_lMaxPosition-m_lPageSize);

				m_bDragingScrollBar		=FALSE;
				m_bSpinIsPressed[0]		=FALSE;
				m_bSpinIsPressed[1]		=FALSE;
				
				::KillTimer(m_pCanvas->GetView()->GetDeviceWnd(),(UINT_PTR)this);
				Invalidate(TRUE);

				NotifyCallback();
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			if(m_bDragingScrollBar)
			{
				SIZE	size;
				size.cx		=m_ScrollBarRect.right	-m_ScrollBarRect.left;
				size.cy		=m_ScrollBarRect.bottom	-m_ScrollBarRect.top;

				m_ScrollBarRect.left	=pPoint->x-m_ptDragOffset.x;
				m_ScrollBarRect.top		=pPoint->y-m_ptDragOffset.y;
				
				if(m_ScrollBarRect.left < m_ScrollBarActiveRect.left)
					m_ScrollBarRect.left =m_ScrollBarActiveRect.left;
				if(m_ScrollBarRect.left+size.cx > m_ScrollBarActiveRect.right)
					m_ScrollBarRect.left =m_ScrollBarActiveRect.right-size.cx;



				if(m_ScrollBarRect.top < m_ScrollBarActiveRect.top)
					m_ScrollBarRect.top =m_ScrollBarActiveRect.top;
				if(m_ScrollBarRect.top+size.cy > m_ScrollBarActiveRect.bottom)
					m_ScrollBarRect.top =m_ScrollBarActiveRect.bottom-size.cy;

				m_ScrollBarRect.right	=m_ScrollBarRect.left	+size.cx;
				m_ScrollBarRect.bottom	=m_ScrollBarRect.top	+size.cy;

				if(m_bHorizontal)
				{
					LONG	pos		=m_ScrollBarRect.left-m_Pos.x-m_Size.cy;					
					FLOAT	fScale	=(FLOAT)(m_Size.cx-m_Size.cy*2/*-size.cx*/)/(FLOAT)m_lMaxPosition;
					m_lPosition	=pos/fScale+0.5f;

				}
				else
				{
					LONG	pos		=m_ScrollBarRect.top-m_Pos.y-m_Size.cx;					
					FLOAT	fScale	=(FLOAT)(m_Size.cy-m_Size.cx*2/*-size.cy*/)/(FLOAT)m_lMaxPosition;
					m_lPosition	=pos/fScale+0.5f;
				}
				Invalidate(TRUE);
				NotifyCallback();
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(!IsSelected())
				break;

			switch(wParam)
			{
			case VK_LEFT:
				{
					m_Pos.x--;
					Invalidate(TRUE);
					return TRUE;
				}
				break;
			case VK_RIGHT:
				{
					m_Pos.x++;
					Invalidate(TRUE);
					return TRUE;
				}
				break;
			case VK_UP:
				{
					m_Pos.y--;
					Invalidate(TRUE);
					return TRUE;
				}
				break;
			case VK_DOWN:
				{
					m_Pos.y++;
					Invalidate(TRUE);
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

VOID CALLBACK	 CODLEx_Element_ScrollBar::SpinHoldPressTimer(HWND IN hWnd, UINT IN msg, UINT_PTR IN id, DWORD IN time)
{
	if(msg != WM_TIMER)
		return;
	CODLEx_Element_ScrollBar*	pObj	=(CODLEx_Element_ScrollBar*)id;
	if(id == NULL)
		return;
	::KillTimer(hWnd,id);
	pObj->OnTimer();
	::SetTimer(hWnd,id,50,(TIMERPROC)CODLEx_Element_ScrollBar::SpinHoldPressTimer);
}
VOID			CODLEx_Element_ScrollBar::OnTimer()
{

	if(m_bSpinIsPressed[0])
		m_lPosition-=m_lTimerCounter;
	if(m_bSpinIsPressed[1])
		m_lPosition+=m_lTimerCounter;
	if(m_lPosition<0)
		m_lPosition=0;
	if(m_lPosition>(m_lMaxPosition-m_lPageSize))
		m_lPosition=(m_lMaxPosition-m_lPageSize);
	m_lTimerCounter++;

	Invalidate(TRUE);

	NotifyCallback();
}
BOOL				CODLEx_Element_ScrollBar::IsHorizontal()
{
	return m_bHorizontal;
}
VOID				CODLEx_Element_ScrollBar::SetHorizontal(BOOL IN bHorizontal)
{
	m_bHorizontal	=bHorizontal;
	Invalidate();
}
VOID				CODLEx_Element_ScrollBar::SetArrowBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pArrowBrush);
	m_pArrowBrush	=pBrush;
	m_pArrowBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetSpinBarBrightBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pSpinBarBrightBrush);
	m_pSpinBarBrightBrush	=pBrush;
	m_pSpinBarBrightBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetSpinBarNormalBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pSpinBarNormalBrush);
	m_pSpinBarNormalBrush	=pBrush;
	m_pSpinBarNormalBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetSpinBarDarkBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pSpinBarDarkBrush);
	m_pSpinBarDarkBrush	=pBrush;
	m_pSpinBarDarkBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetScrollBarBrightBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pScrollBarBrightBrush);
	m_pScrollBarBrightBrush	=pBrush;
	m_pScrollBarBrightBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetScrollBarNormalBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pScrollBarNormalBrush);
	m_pScrollBarNormalBrush	=pBrush;
	m_pScrollBarNormalBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetScrollBarDarkBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pScrollBarDarkBrush);
	m_pScrollBarDarkBrush	=pBrush;
	m_pScrollBarDarkBrush->AddRef();
	Invalidate();
}

VOID				CODLEx_Element_ScrollBar::SetBackBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL)
		return;
	ODL_SafeRelease(m_pBackBrush);
	m_pBackBrush	=pBrush;
	m_pBackBrush->AddRef();
	Invalidate();
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetArrowBrush()
{
	return m_pArrowBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetSpinBarBrightBrush()
{
	return m_pSpinBarBrightBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetSpinBarNormalBrush()
{
	return m_pSpinBarNormalBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetSpinBarDarkBrush()
{
	return m_pSpinBarDarkBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetScrollBarBrightBrush()
{
	return m_pScrollBarBrightBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetScrollBarNormalBrush()
{
	return m_pScrollBarNormalBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetScrollBarDarkBrush()
{
	return m_pScrollBarDarkBrush;
}
CODL_Brush*			CODLEx_Element_ScrollBar::GetBackBrush()
{
	return m_pBackBrush;
}
VOID				CODLEx_Element_ScrollBar::NotifyCallback()
{
	if(m_pScrollCallback == NULL)
		return;
	m_pScrollCallback(GetID(),m_lPosition,m_lMaxPosition,m_lPageSize,m_CallbackUserData);
}
