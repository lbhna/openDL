#include "StdAfx.h"
#include ".\odl_canvasbase.h"


CODL_CanvasBase::CODL_CanvasBase(CODL_ViewBase* IN pView)
{
	m_pView						=pView;
	m_CanvasType				=CANVAS_BASE;
	m_bInvalidate				=TRUE;
	m_Size.cx	=m_Size.cy		=0;
	m_Pos.x		=m_Pos.y		=0;
	m_pName						=NULL;
	m_hActiveFramePen			=NULL;
	m_hNormalFramePen			=NULL;
	m_bActived					=FALSE;
	m_BkColor					=RGB(0,0,0);
	m_ActiveFrameColor			=RGB(158,158,128);
	m_NormalFrameColor			=RGB(100,100,100);
	m_bMaxisized				=FALSE;
	m_pCoordinate				=NULL;
	m_pDiagramPreview			=NULL;
	m_pCurrentSelected			=NULL;
	m_hMenu						=NULL;
	m_pCrossLine				=NULL;
	m_pZoomFrame				=NULL;
	m_pCanvasTitle				=NULL;

	m_bEnableDoubleClick		=TRUE;
	m_bEnableAutoScroll			=TRUE;
	m_bNeedOrder				=TRUE;
	m_lOldCount					=0;

	m_CurOperatorType			=ODL_OPER_NONE;
	m_uCallbackMessageID		=0;
	m_hCallbackWnd				=NULL;

	m_bSavedState			=FALSE;	
	m_SavedState.pos.x		=0;
	m_SavedState.pos.y		=0;
	m_SavedState.size.cx	=0;
	m_SavedState.size.cy	=0;
	m_pListener				=NULL;



	m_pElementSelectFramePen	=pView->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(255,0,0));
}

CODL_CanvasBase::~CODL_CanvasBase(void)
{
	ODL_SafeRelease(m_pElementSelectFramePen);
	LB_FREE(m_pName);
	ODL_SafeRelease(m_pCanvasTitle);
	ODL_SafeRelease(m_pDiagramPreview);
	ODL_SafeRelease(m_pCoordinate);
	ODL_SafeRelease(m_pZoomFrame);
	ODL_SafeRelease(m_pCrossLine);
	ODL_SafeRelease(m_pCurrentSelected);
	ODL_SafeDeleteGDIObj(m_hActiveFramePen);
	ODL_SafeDeleteGDIObj(m_hNormalFramePen);

}
INT		CODL_CanvasBase::Create(LPCSTR IN pName)
{
	SetName(pName);

	return OnCreate();
}
VOID	CODL_CanvasBase::SetCallbackMessageID(HWND IN hMsgWnd,UINT IN uMsgID)
{
	m_uCallbackMessageID	=uMsgID;
	m_hCallbackWnd			=hMsgWnd;
}

VOID	CODL_CanvasBase::OrderElement()
{//根据图元的z-index 进行排序

	if(!m_bNeedOrder && m_lOldCount == GetCount())
		return;

	m_bNeedOrder	=FALSE;
	m_lOldCount		=GetCount();

	CODL_ElementBase	*pElement1,*pElement2;
	LONG				index=0;
	for(LONG i=0;i<GetCount();i++)
	{
		pElement1	=(CODL_ElementBase*)GetObj(i);
		index		=i;
		for(LONG j=i-1;j>=0;j--)
		{
			pElement2	=(CODL_ElementBase*)GetObj(j);
			if(pElement1->GetZIndex() < pElement2->GetZIndex())
			{
				Swap(index,j);
				index =j;
			}
		}
	}
}
INT		CODL_CanvasBase::OnUpdate()
{
	OrderElement();
	if(m_bInvalidate)
	{
		Draw();
		m_bInvalidate		=FALSE;
	}
	Present();
	return 0;
}
VOID		CODL_CanvasBase::SetName(LPCSTR IN pName)
{
	if(pName == NULL)
		return;
	LB_FREE(m_pName);
	INT	size =(INT)strlen(pName)+1;
	m_pName = (CHAR*)LB_ALLOC(size+1);
	ZeroMemory(m_pName,size);
	strcpy(m_pName,pName);
}
BOOL			CODL_CanvasBase::Active()
{
	CODL_CanvasBase* pOldActive =GetView()->GetActiveCanvas();
	if(pOldActive ==this)
		return FALSE;

	if(pOldActive != NULL)
		pOldActive->Deactive();
	GetView()->SetActiveCanvas(this);

	m_bActived		=TRUE;
	m_bInvalidate	=TRUE;

	SetFocus(GetView()->GetDeviceWnd());

	PostCallbackMessage(CANVAS_CALLBACKMSG_OnActive,(LPARAM)this);
	if(m_pListener != NULL)
	{
		m_pListener->OnCanvas_Actived(this);
	}
	return TRUE;
}
BOOL			CODL_CanvasBase::Deactive()
{
	CODL_CanvasBase* pOldActive =GetView()->GetActiveCanvas();
	if(pOldActive !=this)
		return FALSE;

	GetView()->SetActiveCanvas(NULL);
	m_bActived		=FALSE;
	m_bInvalidate	=TRUE;
	m_bMaxisized	=FALSE;

	PostCallbackMessage(CANVAS_CALLBACKMSG_OnDeactive,(LPARAM)this);
	if(m_pListener != NULL)
	{
		m_pListener->OnCanvas_Deactived(this);
	}
	return TRUE;
}

VOID	CODL_CanvasBase::DrawActiveFrame(HDC IN hDC)
{
	HPEN	hOldPen =NULL;
	RECT	rect;
	rect.left	=0;
	rect.top	=0;
	rect.right	=m_Size.cx;
	rect.bottom =m_Size.cy;
	if(IsActive())
	{
		if(m_hActiveFramePen == NULL)
		{
			m_hActiveFramePen =CreatePen(PS_SOLID,2,m_ActiveFrameColor);
		}
		InflateRect(&rect,-1,-1);
		hOldPen =(HPEN)SelectObject(hDC,m_hActiveFramePen);
		if(!IsMaximized()&&m_pView->GetViewStyle()==OVS_CASCADE)
		{
			for(INT i=1;i<=4;i++)
			{
				MoveToEx(hDC,rect.right,rect.bottom-i*3,NULL);
				LineTo(hDC,rect.right-i*3,rect.bottom);			
			}
		}
	}
	else
	{
		if(m_hNormalFramePen == NULL)
		{
			m_hNormalFramePen =CreatePen(PS_SOLID,1,m_NormalFrameColor);
		}
		hOldPen =(HPEN)SelectObject(hDC,m_hNormalFramePen);
		rect.right	-=1;
		rect.bottom	-=1;
	}
	
	MoveToEx(hDC,rect.left,rect.top,NULL);

	LineTo(hDC,rect.right,rect.top);
	LineTo(hDC,rect.right,rect.bottom);
	LineTo(hDC,rect.left,rect.bottom);
	LineTo(hDC,rect.left,rect.top);


	SelectObject(hDC,hOldPen);

}
BOOL			CODL_CanvasBase::PointInCanvas(POINT* IN pt)
{
	if(pt==NULL)
		return FALSE;
	RECT	rect;
	rect.left	=m_Pos.x;
	rect.top	=m_Pos.y;
	rect.right	=m_Pos.x + m_Size.cx;
	rect.bottom	=m_Pos.y + m_Size.cy;

	return PtInRect(&rect,*pt);
}
BOOL			CODL_CanvasBase::PointInCanvasChangeSizeButton(POINT* IN pt)
{
	if(pt==NULL)
		return FALSE;
	RECT	rect;
	rect.right	=m_Pos.x + m_Size.cx;
	rect.bottom	=m_Pos.y + m_Size.cy;
	rect.left	=rect.right	-10;
	rect.top	=rect.bottom-10;

	return PtInRect(&rect,*pt);

}


VOID			CODL_CanvasBase::ClearCanvas(HDC IN hCanvasDC)
{
	::SetBkColor(hCanvasDC, m_BkColor);
	RECT	rect;
	rect.left	=0;
	rect.top	=0;
	rect.right	=m_Size.cx;
	rect.bottom =m_Size.cy;
	::ExtTextOut(hCanvasDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
}
VOID			CODL_CanvasBase::SetActiveFrameColor(COLORREF IN clr)
{
	m_ActiveFrameColor =clr;
	m_bInvalidate=TRUE;
	ODL_SafeDeleteGDIObj(m_hActiveFramePen);
}
VOID			CODL_CanvasBase::SetNormalFrameColor(COLORREF IN clr)
{
	m_NormalFrameColor =clr;
	m_bInvalidate=TRUE;
	ODL_SafeDeleteGDIObj(m_hNormalFramePen);
}
VOID			CODL_CanvasBase::GetRect(RECT& OUT rect)
{
	rect.left	=m_Pos.x;
	rect.top	=m_Pos.y;
	rect.right	=m_Pos.x + m_Size.cx;
	rect.bottom =m_Pos.y + m_Size.cy;
}
VOID			CODL_CanvasBase::MoveLeft(LONG IN lCount)
{
	CODL_ElementBase*	pElement	=NULL;
	for(LONG i=0;i<GetCount();i++)
	{
		pElement	=(CODL_ElementBase*)GetObj(i);
		pElement->MoveLeft(lCount);
	}
	GetView()->Invalidate();
}
VOID			CODL_CanvasBase::MoveUp(LONG IN lCount)
{
	CODL_ElementBase*	pElement	=NULL;
	for(LONG i=0;i<GetCount();i++)
	{
		pElement	=(CODL_ElementBase*)GetObj(i);
		pElement->MoveUp(lCount);
	}
	GetView()->Invalidate();
}

BOOL			CODL_CanvasBase::OnKeydown(WPARAM IN wParam,LPARAM IN lParam)
{
	switch(wParam)
	{
	case VK_LEFT:
	case 'j':
	case 'J':
		{
			if(GetSelected() != NULL)
				return FALSE;
			MoveLeft(-1);
			return TRUE;

		}
		break;
	case VK_RIGHT:
	case 'L':
	case 'l':
		{
			if(GetSelected() != NULL)
				return FALSE;
			MoveLeft(1);
			return TRUE;
		}
		break;
	case VK_UP:
	case 'i':
	case 'I':
		{
			if(GetSelected() != NULL)
				return FALSE;
			MoveUp(1);
			return TRUE;
		}
		break;
	case VK_DOWN:
	case 'K':
	case 'k':
		{
			if(GetSelected() != NULL)
				return FALSE;
			MoveUp(-1);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
BOOL			CODL_CanvasBase::OnLButtonDown(POINT* IN pPoint)
{
	
	return FALSE;
}
BOOL			CODL_CanvasBase::OnRButtonDown(POINT* IN pPoint)
{
	if(IsActive())
	{
		PopupRButtonMenu();
	}
	return FALSE;
}

BOOL			CODL_CanvasBase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
		{
			POINTS		pt		=MAKEPOINTS(lParam);
			POINT		point;
			point.x		=pt.x - m_pView->GetPaintRect()->left;
			point.y		=pt.y - m_pView->GetPaintRect()->top;
			if(!PointInCanvas(&point))
				return FALSE;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS		pt		=MAKEPOINTS(lParam);
			POINT		point;
			point.x		=pt.x - m_pView->GetPaintRect()->left;
			point.y		=pt.y - m_pView->GetPaintRect()->top;
			if(!PointInCanvas(&point))
				return FALSE;
			CODL_ElementBase*	pElement	=NULL;
			if(  ( GetKeyState(VK_LCONTROL) & 0xff00 ) != 0 || ( GetKeyState(VK_RCONTROL) & 0xff00 ) != 0 )
			{//只有在Ctrl键按下的情况下才可以进行下列操作
				for(LONG i=GetCount()-1;i>=0;i--)
				{
					pElement	=(CODL_ElementBase*)GetObj(i);
					if(pElement->IsShow())
					{
						if(pElement->IsEnableSelect() && pElement->PtInElement(*pPoint))
						{
							if(pElement->IsSelected())
								break;
							SetSelected(pElement);
							return TRUE;
						}
					}
				}
			}
			else
			{
				SetSelected(NULL);	
			}
		}
		break;
	}

	if(IsActive())
	{
		CODL_ElementBase*	pElement	=NULL;
		for(LONG i=GetCount()-1;i>=0;i--)
		{
			pElement	=(CODL_ElementBase*)GetObj(i);
			if(pElement->IsShow())
			{
				if(pElement->OnWndMsg(message,wParam,lParam,pResult,pPoint))
					return TRUE;
			}
		}
	}


	switch(message)
	{
	case WM_LBUTTONDBLCLK:
		{
			return OnLButtonDBClick(pPoint);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			return OnLButtonDown(pPoint);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			return OnRButtonDown(pPoint);
		}
		break;
	case WM_KEYDOWN:
		{
			if(IsActive())
			{
				return OnKeydown(wParam,lParam);
			}
		}
		break;
	}
	return FALSE;
}		
VOID			CODL_CanvasBase::SetMaximized(BOOL IN bMax)
{
	m_bMaxisized	=bMax; 
	if(!m_bMaxisized)
		Deactive();
	Invalidate(TRUE);
}

BOOL			CODL_CanvasBase::OnLButtonDBClick(POINT* IN pPoint)
{
	if(!m_bEnableDoubleClick)
		return FALSE;
	m_bMaxisized =!m_bMaxisized;
	if(!m_bMaxisized)
		Deactive();
	Invalidate(TRUE);
	GetView()->LayoutCanvas();
	GetView()->Invalidate();
	return TRUE;
}
void			CODL_CanvasBase::SetCoordinate(CODL_ElementBase* IN pCoord)
{
	if(pCoord == NULL)
		return;
	ODL_SafeRelease(m_pCoordinate);
	m_pCoordinate =pCoord;
	m_pCoordinate->AddRef();
}
VOID			CODL_CanvasBase::Invalidate(BOOL IN bResetAllElements)
{
	m_bInvalidate	=TRUE;
	if(bResetAllElements)
	{
		CODL_ElementBase* pElement;
		for(LONG i=0;i<GetCount();i++)
		{
			pElement	=(CODL_ElementBase*)GetObj(i);
			pElement->Invalidate();
		}

	}


}
void			CODL_CanvasBase::SetSelected(CODL_ElementBase* IN pElement)
{
	BOOL bNeedRedraw =FALSE;
	if(m_pCurrentSelected != NULL)
	{
		m_pCurrentSelected->SetSelected(FALSE);
		m_pCurrentSelected->Release();
		bNeedRedraw =TRUE;
	}
	m_pCurrentSelected =pElement;
	if(m_pCurrentSelected != NULL)
	{
		m_pCurrentSelected->SetSelected(TRUE);
		m_pCurrentSelected->AddRef();
		bNeedRedraw =TRUE;

		if(m_pCrossLine != NULL)
			m_pCrossLine->Show(TRUE);
	}
	else
	{
		if(m_pCrossLine != NULL)
			m_pCrossLine->Show(FALSE);
	}
	if(bNeedRedraw)
		GetView()->Invalidate();

	Invalidate(FALSE);
}
VOID			CODL_CanvasBase::PopupRButtonMenu()
{
	if(m_hMenu == NULL)
		return;
	POINT	point;
	GetCursorPos(&point);
	TrackPopupMenu(m_hMenu,TPM_LEFTALIGN,point.x,point.y,0,GetView()->GetDeviceWnd(),NULL);

}
void			CODL_CanvasBase::SetZoomFrame(CODL_ElementBase* IN pZoomFrame)
{
	if(pZoomFrame == NULL)
		return;
	ODL_SafeRelease(m_pZoomFrame);
	m_pZoomFrame =pZoomFrame;
	m_pZoomFrame->AddRef();
}
void			CODL_CanvasBase::SetCrossLine(CODL_ElementBase* IN pCrossLine)
{
	if(pCrossLine == NULL)
		return;
	ODL_SafeRelease(m_pCrossLine);
	m_pCrossLine =pCrossLine;
	m_pCrossLine->AddRef();
}
void			CODL_CanvasBase::SetDiagramPreview(CODL_ElementBase* IN pPreview)
{
	if(pPreview == NULL)
		return;
	ODL_SafeRelease(m_pDiagramPreview);
	m_pDiagramPreview =pPreview;
	m_pDiagramPreview->AddRef();
}
void			CODL_CanvasBase::SetCanvasTitle(CODL_ElementBase* IN pTitle)
{
	if(pTitle == NULL)
		return;
	ODL_SafeRelease(m_pCanvasTitle);
	m_pCanvasTitle =pTitle;
	m_pCanvasTitle->AddRef();
}
VOID			CODL_CanvasBase::PostCallbackMessage(WPARAM wp,LPARAM lp)
{
	if(m_uCallbackMessageID		== 0)
		return;

	PostMessage(m_hCallbackWnd,m_uCallbackMessageID,wp,lp);
}
LRESULT			CODL_CanvasBase::SendCallbackMessage(WPARAM wp,LPARAM lp)
{
	if(m_uCallbackMessageID		== 0)
		return 0;
	return SendMessage(m_hCallbackWnd,m_uCallbackMessageID,wp,lp);
}

VOID			CODL_CanvasBase::SetPos(PPOINT IN pPoint)
{
	SetPos(pPoint->x,pPoint->y);
}
VOID			CODL_CanvasBase::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x=x;
	m_Pos.y=y;

	if(m_pListener != NULL && m_pView->GetViewStyle() == OVS_CASCADE)
	{
		m_pListener->OnCanvas_PosChanged(this);
	}
}
CODL_Pen*		CODL_CanvasBase::GetElementSelectFramePen()
{
	return m_pElementSelectFramePen;
}
VOID			CODL_CanvasBase::SetElementSelectFramePen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pElementSelectFramePen);
	m_pElementSelectFramePen	=GetView()->GetResourceManager()->CreatePen(lp);
}


VOID			CODL_CanvasBase::SaveState()
{
	m_bSavedState	=TRUE;
	m_SavedState.pos		=m_Pos;
	m_SavedState.size		=m_Size;
}
VOID			CODL_CanvasBase::RestoreState()
{
	if(m_bSavedState)
	{
		SetPos(&m_SavedState.pos);
		SetSize(&m_SavedState.size);
	}
}

VOID	CODL_CanvasBase::EnableDoubleClick(BOOL bEnable)
{
	m_bEnableDoubleClick = bEnable;
}
BOOL	CODL_CanvasBase::IsEnableDoubleClick()
{
	return m_bEnableDoubleClick;
}
VOID	CODL_CanvasBase::SetListener(CODL_Listener* IN pListener)
{
	m_pListener		=pListener;
}

