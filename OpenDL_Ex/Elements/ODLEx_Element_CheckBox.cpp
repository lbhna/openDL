#include "stdafx.h"
#include ".\odlex_element_checkbox.h"

CODLEx_Element_CheckBox::CODLEx_Element_CheckBox(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_CHECKBOX;
	m_pText				=NULL;
	m_Pos.x				=0;
	m_Pos.y				=0;
	m_Size.cx			=12;
	m_Size.cy			=12;
	m_TextColor			=RGB(0,0,0);
	

	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(150,150,150),0);
	m_pSelectBtnBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(55,55,255),0);
	m_pBlackFramePen	=pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(55,55,55));
	m_pWhiteFramePen	=pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(255,255,255));
	m_pTextFont			=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",14);
	m_bChecked			=FALSE;
	
	m_TextBkColor		=RGB(200,200,200);

	m_pTextBkBrush		=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,m_TextBkColor,0);

	m_bShowTextBkColor	=TRUE;
	m_pText				=NULL;


	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;
	m_bEnableAdjustSize	=FALSE;
	m_bAdjustSizeing	=FALSE;
	m_bEnableDrag		=FALSE;
	m_bDraging			=FALSE;
	m_bPushed			=FALSE;
}

CODLEx_Element_CheckBox::~CODLEx_Element_CheckBox(void)
{
	ODL_SafeRelease(m_pTextBkBrush);;
	ODL_SafeRelease(m_pBkBrush);;
	ODL_SafeRelease(m_pSelectBtnBrush);;
	ODL_SafeRelease(m_pBlackFramePen);;
	ODL_SafeRelease(m_pWhiteFramePen);;

	ODL_SafeDeleteArray(m_pText);

}
VOID				CODLEx_Element_CheckBox::SetTextColor(COLORREF IN clr)
{
	m_TextColor		=clr;
	Invalidate();
}

VOID				CODLEx_Element_CheckBox::SetBkColor(COLORREF IN clr)
{
	m_TextBkColor		=clr;
	ODL_SafeRelease(m_pTextBkBrush);
	m_pTextBkBrush		=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,m_TextBkColor,0);
	Invalidate();
}	
VOID				CODLEx_Element_CheckBox::EnableShowBkColor(BOOL IN bShowBkColor)
{	
	m_bShowTextBkColor	=bShowBkColor;
	Invalidate();
}
VOID				CODLEx_Element_CheckBox::SetDarkFrameColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pBlackFramePen);;
	m_pBlackFramePen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,clr);
	Invalidate();
}
VOID				CODLEx_Element_CheckBox::SetLightFrameColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pWhiteFramePen);;
	m_pWhiteFramePen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,clr);
	Invalidate();
}

VOID				CODLEx_Element_CheckBox::SetCheckBoxFgColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pSelectBtnBrush);
	m_pSelectBtnBrush	=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,0);
	Invalidate();
}
VOID				CODLEx_Element_CheckBox::SetCheckBoxBkColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,0);
	Invalidate();
}

VOID				CODLEx_Element_CheckBox::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
}

VOID				CODLEx_Element_CheckBox::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
}
VOID				CODLEx_Element_CheckBox::SetText(LPCSTR IN pText)
{
	if(pText == NULL)
		return;
	ODL_SafeDeleteArray(m_pText);
	m_pText =new CHAR [strlen(pText)+1];
	strcpy(m_pText,pText);
	Invalidate();
}

VOID				CODLEx_Element_CheckBox::SetCheck(BOOL IN bCheck)
{	
	if(m_bChecked == bCheck)
		return;
	m_bChecked	=bCheck;
	Invalidate();
}

VOID				CODLEx_Element_CheckBox::SetFont(CHAR* IN pFontName,DWORD IN dwFontSize,COLORREF IN FontColor)
{
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont			=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pFontName,dwFontSize);
	m_TextColor			=FontColor;
	Invalidate();
}
VOID				CODLEx_Element_CheckBox::SetFont(LOGFONT* IN pLF)
{
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont			=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pLF);
	Invalidate();
}

BOOL				CODLEx_Element_CheckBox::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	BoxRect,BoundRect;
	BoxRect.left		=m_Pos.x+1;
	BoxRect.top			=m_Pos.y+1;
	BoxRect.right		=m_Pos.x + m_Size.cy-1;
	BoxRect.bottom		=m_Pos.y + m_Size.cy-1;
	

	BoundRect.left		=m_Pos.x;
	BoundRect.top		=m_Pos.y;
	BoundRect.right		=m_Pos.x + m_Size.cx ;
	BoundRect.bottom	=m_Pos.y + m_Size.cy ;


	if(m_bShowTextBkColor)
	{
		FillRect(hDC,&BoundRect,m_pTextBkBrush->GetBrush());
	}
	

	FillRect(hDC,&BoxRect,m_pBkBrush->GetBrush());

	m_pBlackFramePen->Install(hDC);
	MoveToEx(hDC,BoxRect.left,BoxRect.bottom,NULL);
	LineTo(hDC,BoxRect.left,BoxRect.top);
	LineTo(hDC,BoxRect.right,BoxRect.top);
	m_pBlackFramePen->Uninstall(hDC);

	m_pWhiteFramePen->Install(hDC);
	MoveToEx(hDC,BoxRect.right,BoxRect.top,NULL);
	LineTo(hDC,BoxRect.right,BoxRect.bottom);
	LineTo(hDC,BoxRect.left,BoxRect.bottom);
	m_pWhiteFramePen->Uninstall(hDC);

	
	if(m_bChecked)
	{
		InflateRect(&BoxRect,-(BoxRect.right-BoxRect.left)/4,-(BoxRect.bottom-BoxRect.top)/4);
		OffsetRect(&BoxRect,1,1);
		FillRect(hDC,&BoxRect,m_pSelectBtnBrush->GetBrush());
	}


	if(m_pText != NULL)
	{
		m_pTextFont->Install(hDC);
		SetBkMode(hDC,TRANSPARENT);
		RECT	textRect;
		textRect		=	BoundRect;
		textRect.left +=	m_Size.cy +2;
		InflateRect(&textRect,-1,-1);
		::SetTextColor(hDC,m_TextColor);
		DrawText(hDC,m_pText,strlen(m_pText),&textRect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

		m_pTextFont->Uninstall(hDC);
	}


	if(IsSelected())
	{
		m_pCanvas->GetElementSelectFramePen()->Install(hDC);
			m_pCanvas->GetElementSelectFramePen()->DrawRect(&BoundRect);
		if(m_bEnableAdjustSize)
		for(INT i=1;i<=7;i++)
		{
			MoveToEx(hDC,BoundRect.right,BoundRect.bottom-i,NULL);
			LineTo(hDC,BoundRect.right-i,BoundRect.bottom);			
		}
		m_pCanvas->GetElementSelectFramePen()->Uninstall(hDC);
	}

	return TRUE;
}
BOOL				CODLEx_Element_CheckBox::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
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
			if(!IsControlSwitchKeyPressed())
			{
				RECT rect;
				rect.left	=m_Pos.x;
				rect.top	=m_Pos.y;
				rect.right	=m_Pos.x + m_Size.cy;
				rect.bottom	=m_Pos.y + m_Size.cy;
				if(PtInRect(&rect,*pPoint))
				{
					m_bPushed	=TRUE;
					return TRUE;
				}
			}
			else
			{
				if(!PtInElement(*pPoint))
					break;
				if(!IsSelected())
					break;
				//只有在Ctrl键按下的情况下才可以进行下列操作
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
		}
		break;
	case WM_LBUTTONUP:
		{
			if(!IsControlSwitchKeyPressed())
			{
				m_bAdjustSizeing	=FALSE;
				m_bDraging			=FALSE;
				RECT rect;
				rect.left	=m_Pos.x;
				rect.top	=m_Pos.y;
				rect.right	=m_Pos.x + m_Size.cy;
				rect.bottom	=m_Pos.y + m_Size.cy;
				if(PtInRect(&rect,*pPoint)&&m_bPushed)
				{
					m_bPushed	=FALSE;
					SetCheck(!IsChecked());
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_Clicked(this);
					return TRUE;
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
				if(!IsSelected())
					break;
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
RECT*		CODLEx_Element_CheckBox::GetRect(RECT* IN OUT pRec)
{
	pRec->left	=m_Pos.x;
	pRec->top	=m_Pos.y;
	pRec->right	=m_Pos.x	+ m_Size.cx;
	pRec->bottom =m_Pos.y	+ m_Size.cy;
	return pRec;
}

BOOL		CODLEx_Element_CheckBox::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	return PtInRect(GetRect(&rect),pt);
}
BOOL		CODLEx_Element_CheckBox::PtInAdjustSizeButton(POINT* IN pt)
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
VOID		CODLEx_Element_CheckBox::EnableAdjustSize(BOOL IN bEnable)
{
	m_bEnableAdjustSize	=bEnable;

}
