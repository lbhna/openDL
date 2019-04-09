#include "StdAfx.h"
#include ".\odlex_element_textarea.h"

CODLEx_Element_TextArea::CODLEx_Element_TextArea(CODL_CanvasBase* IN pCanvas):
CODL_OverlayElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_TEXTAREA;
	m_pBorderPen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(0,0,0));
	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,255,255),NULL);
	m_pFont				=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",12);

	m_TextColor			=RGB(155,0,0);
	m_Pos.x		=m_Pos.y=0;
	m_pText			=NULL;

	m_bShowBorder		=TRUE;
	m_bShowBkColor		=TRUE;

	m_uTextAlign		=DT_CENTER|DT_VCENTER;

	m_lMargin			=2;
	m_Size.cx =m_Size.cy=1;
	m_bFixedSize		=FALSE;

	m_bEnableDrag		=FALSE;
	m_bDraging			=FALSE;
	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;

	m_Alpha				=255;
	m_bEnableSelect		=FALSE;

	m_bEnableAdjustSize	=FALSE;
	m_bAdjustSizeing	=FALSE;
	m_bPushed			=FALSE;
}

CODLEx_Element_TextArea::~CODLEx_Element_TextArea(void)
{
	ODL_SafeRelease(m_pBorderPen);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pFont);
	ODL_SafeDeleteArray(m_pText);

}
VOID			CODLEx_Element_TextArea::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();

	if(m_pListener != NULL)
		m_pListener->OnElement_PosChanged(this);

}
VOID			CODLEx_Element_TextArea::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnElement_SizeChanged(this);

}
VOID			CODLEx_Element_TextArea::SetText(LPCSTR IN pText)
{
	StringSet(m_pText ,pText);
	Invalidate();
}
VOID			CODLEx_Element_TextArea::SetTextFont(LPCSTR IN pFontName,DWORD IN dwFontSize,DWORD IN dwFontWeight)
{
	ODL_SafeRelease(m_pFont);
	m_pFont		=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize,dwFontWeight);
	Invalidate();
}

VOID			CODLEx_Element_TextArea::SetTextFont(LOGFONT* IN pLf)
{
	ODL_SafeRelease(m_pFont);
	m_pFont		=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pLf);
	Invalidate();
}

VOID			CODLEx_Element_TextArea::SetTextAlign(UINT IN uAlign)
{
	m_uTextAlign		=uAlign;
	Invalidate();
}
VOID			CODLEx_Element_TextArea::SetTextColor(COLORREF IN clr)
{
	m_TextColor		=clr;
	Invalidate();
}
COLORREF		CODLEx_Element_TextArea::GetTextColor()
{
	return m_TextColor;
}

VOID			CODLEx_Element_TextArea::SetBkColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush	=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,NULL);
	Invalidate();
}
VOID			CODLEx_Element_TextArea::SetBorder(COLORREF IN borderColor,DWORD IN dwBorderWidth,DWORD IN dwBorderStyle)
{
	ODL_SafeRelease(m_pBorderPen);
	m_pBorderPen=GetCanvas()->GetView()->GetResourceManager()->CreatePen(dwBorderStyle,dwBorderWidth,borderColor);
	Invalidate();
}
VOID			CODLEx_Element_TextArea::GetRect(HDC IN hDC,RECT* OUT pRect)
{

	DWORD			dwWidth	=m_pBorderPen->GetLogPen()->lopnWidth.x;
	if(m_bFixedSize)
	{
		pRect->left		=m_Pos.x;
		pRect->top		=m_Pos.y;
		pRect->right	=m_Pos.x + m_Size.cx;
		pRect->bottom	=m_Pos.y + m_Size.cy;
		return;
	}
	else
	{
		m_pFont->Install(hDC);
		LPTEXTMETRIC	metric	=m_pFont->GetTextMetrics();
		m_pFont->Uninstall(hDC);

		INT				len		=strlen(m_pText);
		pRect->left		=m_Pos.x;
		pRect->top		=m_Pos.y;
		pRect->right	=metric->tmAveCharWidth*len + m_Pos.x + m_lMargin*2 + dwWidth*2;
		pRect->bottom	=metric->tmHeight + m_Pos.y + m_lMargin*2 + dwWidth*2;

		m_Size.cx	=pRect->right	-pRect->left;
		m_Size.cy	=pRect->bottom	-pRect->top;

	}
}
VOID			CODLEx_Element_TextArea::EnableShowBorder(BOOL IN bEnable)
{
	m_bShowBorder		=bEnable;
}
VOID			CODLEx_Element_TextArea::EnableShowBkColor(BOOL IN bEnable)
{
	m_bShowBkColor		=bEnable;
}
BOOL			CODLEx_Element_TextArea::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rect,textRect;
	GetRect(hDC,&rect);
	SIZE	margin;

	margin.cx =margin.cy =m_lMargin;

	if(m_bShowBkColor)
	{
		if(m_pBkBrush != NULL)
			FillRect(hDC,&rect,m_pBkBrush->GetBrush());
	}
	if(m_bShowBorder)
	{
		if(m_pBorderPen != NULL)
		{
			m_pBorderPen->Install(hDC);
			MoveToEx(hDC,rect.left,rect.top,NULL);
			LineTo(hDC,rect.right,rect.top);
			LineTo(hDC,rect.right,rect.bottom);
			LineTo(hDC,rect.left,rect.bottom);
			LineTo(hDC,rect.left,rect.top);
			m_pBorderPen->Uninstall(hDC);

			margin.cx += m_pBorderPen->GetLogPen()->lopnWidth.x;
			margin.cy += m_pBorderPen->GetLogPen()->lopnWidth.x;
		}
	}

	textRect	=rect;
	InflateRect(&textRect,-margin.cx,-margin.cy);

	if(m_pFont != NULL)
		m_pFont->Install(hDC);
	int			oldMode		=::SetBkMode(hDC,TRANSPARENT);
	COLORREF	oldColor	=::SetTextColor(hDC,m_TextColor);
	
	DrawText(hDC,m_pText,strlen(m_pText),&textRect,m_uTextAlign);

	::SetBkMode(hDC,oldMode);
	::SetTextColor(hDC,oldColor);
	if(m_pFont != NULL)
		m_pFont->Uninstall(hDC);


	if(IsSelected())
	{
		m_pCanvas->GetElementSelectFramePen()->Install(hDC);
			m_pCanvas->GetElementSelectFramePen()->DrawRect(&rect);
		if(m_bEnableAdjustSize)
		for(INT i=1;i<=7;i++)
		{
			MoveToEx(hDC,rect.right,rect.bottom-i,NULL);
			LineTo(hDC,rect.right-i,rect.bottom);			
		}
		m_pCanvas->GetElementSelectFramePen()->Uninstall(hDC);
	}
	return TRUE;
}
BOOL			CODLEx_Element_TextArea::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	rect.left	=m_Pos.x;
	rect.top	=m_Pos.y;
	rect.right	=m_Pos.x + m_Size.cx;
	rect.bottom =m_Pos.y + m_Size.cy;
	return PtInRect(&rect,pt);
}
VOID			CODLEx_Element_TextArea::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	boundRect.left	=m_Pos.x;
	boundRect.top	=m_Pos.y;
	boundRect.right	=m_Pos.x + m_Size.cx;
	boundRect.bottom =m_Pos.y + m_Size.cy;
	InflateRect(&boundRect,5,5);
}
BOOL			CODLEx_Element_TextArea::PtInAdjustSizeButton(POINT* IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	rect.right	=m_Pos.x + m_Size.cx;
	rect.bottom =m_Pos.y + m_Size.cy;
	rect.left	=rect.right -5;
	rect.top	=rect.bottom-5;
	return PtInRect(&rect,*pt);
}

BOOL			CODLEx_Element_TextArea::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_RBUTTONDOWN:
		{
			if(!IsSelected())
				break;
			if(!IsControlSwitchKeyPressed() || !PtInElement(*pPoint))
				break;
			if(PopupMenu())
				return TRUE;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			m_bPushed	=FALSE;
			if(!PtInElement(*pPoint))
				break;
			if(IsControlSwitchKeyPressed())
			{//只有在Ctrl键按下的情况下才可以进行下列操作
				if(!IsSelected())
					break;
				if(m_bEnableAdjustSize)
				{
					if(PtInAdjustSizeButton(pPoint))
					{
						m_bAdjustSizeing		=TRUE;
						m_ptDragOffset.x		=(m_Pos.x+m_Size.cx) - pPoint->x;
						m_ptDragOffset.y		=(m_Pos.y+m_Size.cy) - pPoint->y;
						::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
						return TRUE;
					}
				}
				if(m_bEnableDrag)
				{
					m_bDraging	=TRUE;
					m_ptDragOffset.x	=m_Pos.x - pPoint->x;
					m_ptDragOffset.y	=m_Pos.y - pPoint->y;
					return TRUE;

				}
			}
			else
			{
				m_bPushed	=TRUE;
				return TRUE;
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			if(!IsControlSwitchKeyPressed())
			{
				if(m_bPushed)
				{
					m_bPushed	=FALSE;
					if(m_pListener != NULL && PtInElement(*pPoint))
					{
						m_pListener->OnElement_Clicked(this);
						return TRUE;
					}
				}
			}
			else
			{
				if(m_bAdjustSizeing)
				{
					m_bAdjustSizeing	=FALSE;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_SizeChanged(this);
					return TRUE;
				}
				if(m_bDraging)
				{
					m_bDraging	=FALSE;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!IsControlSwitchKeyPressed())
			{

			}
			else
			{
				if(m_bAdjustSizeing)
				{
					POINT	pos;
					pos.x		=pPoint->x + m_ptDragOffset.x;
					pos.y		=pPoint->y + m_ptDragOffset.y;
					if(pos.x < (m_Pos.x+5) || pos.y< (m_Pos.y+5) )
					{
						m_bAdjustSizeing=FALSE;
						Invalidate(TRUE);
						return TRUE;
					}

					m_Size.cx	=pos.x - m_Pos.x;
					m_Size.cy	=pos.y - m_Pos.y;
					Invalidate(TRUE);
					::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
					return TRUE;
				}
				if(m_bDraging)
				{
					m_Pos.x		=pPoint->x + m_ptDragOffset.x;
					m_Pos.y		=pPoint->y + m_ptDragOffset.y;
					Invalidate(TRUE);
					return TRUE;
				}

				if(m_bEnableAdjustSize)
				{
					if(PtInAdjustSizeButton(pPoint))
						::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
				}
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
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			case VK_RIGHT:
				{
					m_Pos.x++;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			case VK_UP:
				{
					m_Pos.y--;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			case VK_DOWN:
				{
					m_Pos.y++;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			}
		}
		break;
	}

	return FALSE;
}
VOID			CODLEx_Element_TextArea::EnableAdjustSize(BOOL IN bEnable)
{
	m_bEnableAdjustSize	=bEnable;
}

