#include "StdAfx.h"
#include ".\odlex_element_button.h"

CODLEx_Element_Button::CODLEx_Element_Button(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_BUTTON;

	m_pNormalPen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(100,100,100));
	m_pHighlightPen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(250,250,250));
	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(200,200,200),NULL);
	m_pActiveBkBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(150,150,150),NULL);
	m_Pos.x		=m_Pos.y	=0;
	m_Size.cx	=m_Size.cy	=16;

	m_bPushed			=FALSE;
	m_hIcon				=NULL;
	m_pTitleFont		=NULL;
	m_pTitle			=NULL;
	m_TitleColor		=RGB(0,0,0);
	m_pClickedCallbackFunction	=NULL;
	m_CallbackUserData	=0;
	m_bEnable			=TRUE;
	m_bMouseOver		=FALSE;
	m_pTips				=NULL;

	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;

	m_bEnableAdjustSize	=FALSE;
	m_bAdjustSizeing	=FALSE;

	m_bEnableDrag		=FALSE;
	m_bDraging			=FALSE;
	m_dwTextAlign		=DT_LEFT|DT_VCENTER;



}

CODLEx_Element_Button::~CODLEx_Element_Button(void)
{
	ODL_SafeRelease(m_pTips);
	ODL_SafeRelease(m_pNormalPen);
	ODL_SafeRelease(m_pHighlightPen);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pActiveBkBrush);
	ODL_SafeRelease(m_pTitleFont);
	ODL_SafeDeleteArray(m_pTitle);
}
INT			CODLEx_Element_Button::SetParameter(DWORD IN borderWidth ,COLORREF IN borderColor,COLORREF IN borderHighlightColor,COLORREF IN bkColor,COLORREF IN activeBkColor)
{
	ODL_SafeRelease(m_pNormalPen);
	ODL_SafeRelease(m_pHighlightPen);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pActiveBkBrush);
	m_pNormalPen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,borderWidth,borderColor);
	m_pHighlightPen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,borderWidth,borderHighlightColor);
	m_pBkBrush			=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,bkColor,NULL);
	m_pActiveBkBrush	=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,activeBkColor,NULL);
	Invalidate();
	return 0;
}
VOID		CODLEx_Element_Button::SetClickedCallback(BTN_CLICKED_CALLBACK IN callbackFunction,DWORD_PTR IN UserData)
{
	m_pClickedCallbackFunction	=callbackFunction;
	m_CallbackUserData			=UserData;
}

RECT*		CODLEx_Element_Button::GetRect(RECT* IN OUT pRec)
{
	pRec->left	=m_Pos.x;
	pRec->top	=m_Pos.y;
	pRec->right	=m_Pos.x	+ m_Size.cx;
	pRec->bottom =m_Pos.y	+ m_Size.cy;
	return pRec;
}
BOOL		CODLEx_Element_Button::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	return PtInRect(GetRect(&rect),pt);
}
VOID		CODLEx_Element_Button::SetIcon(HICON IN hIcon)
{
	m_hIcon		=hIcon;
	Invalidate();
}
VOID		CODLEx_Element_Button::SetTitle(LPCSTR IN pTitle,LPCSTR IN pTitleFontName,DWORD IN dwFontSize,COLORREF IN TitleColor)
{
	ODL_SafeDeleteArray(m_pTitle);
	ODL_SafeRelease(m_pTitleFont);
	if(pTitle == NULL || pTitleFontName == NULL)
		return;

	m_pTitle	=new CHAR[strlen(pTitle)+1];
	strcpy(m_pTitle,pTitle);
	m_pTitleFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pTitleFontName,dwFontSize);
	m_TitleColor	=TitleColor;
	Invalidate();
}
VOID		CODLEx_Element_Button::SetTextAlign(DWORD IN dwAlign)
{
	m_dwTextAlign	=dwAlign;
	Invalidate();
}

VOID		CODLEx_Element_Button::SetTitle(LPCSTR IN pTitle)
{
	ODL_SafeDeleteArray(m_pTitle);
	m_pTitle	=new CHAR[strlen(pTitle)+1];
	strcpy(m_pTitle,pTitle);
	Invalidate();
}
VOID		CODLEx_Element_Button::SetTitleFont(LOGFONT* IN lf)
{
	ODL_SafeRelease(m_pTitleFont);
	m_pTitleFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont(lf);
	Invalidate();

}
VOID		CODLEx_Element_Button::SetTitleColor(COLORREF IN clr)
{
	m_TitleColor =clr;
	Invalidate();
}

BOOL		CODLEx_Element_Button::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rec;
	if(m_bPushed)
		FillRect(hDC,GetRect(&rec),m_pActiveBkBrush->GetBrush());
	else
		FillRect(hDC,GetRect(&rec),m_pBkBrush->GetBrush());
	DWORD penSize =m_pNormalPen->GetLogPen()->lopnWidth.x;
	LONG	x	=m_Pos.x + penSize;
	LONG	y	=m_Pos.y + penSize;
	if(m_hIcon != NULL)
	{
		DWORD	width	=min(m_Size.cx,m_Size.cy)-penSize*2;
		if(m_bPushed)
			x++;
		DrawIconEx(hDC,x,y,m_hIcon,width,width,0,NULL,DI_NORMAL);
		x += width;
	}

	if(m_pTitle != NULL && m_pTitleFont != NULL)
	{
		rec.left	=x + 1;
		rec.top		=y + 1;
		rec.right	=rec.left + (m_Size.cx - 2*penSize)-1;
		rec.bottom	=rec.top  + (m_Size.cy - 2*penSize)-1;

		m_pTitleFont->Install(hDC);
		SetTextColor(hDC,m_TitleColor);
		SetBkMode(hDC,TRANSPARENT);
		DrawText(hDC,m_pTitle,strlen(m_pTitle),&rec,m_dwTextAlign);
		m_pTitleFont->Uninstall(hDC);
	}
	
	if(m_bPushed)
		DrawPushedBorder(hDC);
	else
		DrawNormalBorder(hDC);



	if(IsSelected())
	{
		RECT rect;
		GetRect(&rect);
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


	if(m_pTips != NULL)
		m_pTips->Draw(hDC,pPaintRect);



	return TRUE;
}
BOOL		CODLEx_Element_Button::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
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
			if(!PtInElement(*pPoint))
				break;
			if(!IsControlSwitchKeyPressed())
			{
				m_bPushed =TRUE;
				Invalidate(TRUE);
				return TRUE;
			}
			else
			{
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
				if(PtInElement(*pPoint) && m_bPushed)
				{
					m_bPushed =FALSE;
					Invalidate(TRUE);

					return OnClicked();
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
				if(!PtInElement(*pPoint))
				{
					if(m_bMouseOver)
					{
						m_bMouseOver =FALSE;
						OnMouseOut();
					}
					if(m_bPushed)
					{
						m_bPushed =FALSE;
						Invalidate(TRUE);
					}
				}
				else
				{
					if(!m_bMouseOver)
					{
						m_bMouseOver =TRUE;
						OnMouseOver();
					}
				}
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
VOID		CODLEx_Element_Button::OnMouseOver()
{
	if(!IsEnable())
		return ;
	if(m_pTips != NULL)
	{
		RECT	rect;
		GetRect(&rect);
		m_pTips->SetPos(rect.left,rect.bottom+10);
		m_pTips->Show(TRUE);
		Invalidate(TRUE);
	}

	
}
VOID		CODLEx_Element_Button::OnMouseOut()
{
	if(!IsEnable())
		return ;
	if(m_pTips != NULL)
	{
		m_pTips->Show(FALSE);
		Invalidate(TRUE);
	}
}

VOID		CODLEx_Element_Button::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnElement_PosChanged(this);
}
VOID		CODLEx_Element_Button::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnElement_SizeChanged(this);

}
VOID		CODLEx_Element_Button::DrawNormalBorder(HDC IN hDC)
{
	m_pHighlightPen->Install(hDC);
	MoveToEx(hDC,m_Pos.x + m_Size.cx,m_Pos.y,NULL);
	LineTo(hDC,m_Pos.x,m_Pos.y);
	LineTo(hDC,m_Pos.x,m_Pos.y+m_Size.cy);
	m_pHighlightPen->Uninstall(hDC);


	m_pNormalPen->Install(hDC);
	MoveToEx(hDC,m_Pos.x+m_Size.cx,m_Pos.y,NULL);
	LineTo(hDC,m_Pos.x+m_Size.cx,m_Pos.y+m_Size.cy);
	LineTo(hDC,m_Pos.x,m_Pos.y+m_Size.cy);
	m_pNormalPen->Uninstall(hDC);

}
VOID		CODLEx_Element_Button::DrawPushedBorder(HDC IN hDC)
{
	m_pNormalPen->Install(hDC);
	MoveToEx(hDC,m_Pos.x + m_Size.cx,m_Pos.y,NULL);
	LineTo(hDC,m_Pos.x,m_Pos.y);
	LineTo(hDC,m_Pos.x,m_Pos.y+m_Size.cy);
	m_pNormalPen->Uninstall(hDC);


	m_pHighlightPen->Install(hDC);
	MoveToEx(hDC,m_Pos.x+m_Size.cx,m_Pos.y,NULL);
	LineTo(hDC,m_Pos.x+m_Size.cx,m_Pos.y+m_Size.cy);
	LineTo(hDC,m_Pos.x,m_Pos.y+m_Size.cy);
	m_pHighlightPen->Uninstall(hDC);
}
BOOL		CODLEx_Element_Button::OnClicked()
{	
	if(!IsEnable())
		return FALSE;

	if(m_pClickedCallbackFunction != NULL)
	{
		m_pClickedCallbackFunction(GetID(),m_CallbackUserData);
		return TRUE;
	}
	if(m_pListener != NULL)
		m_pListener->OnElement_Clicked(this);
	return FALSE;
}
VOID		CODLEx_Element_Button::SetTips(CODLEx_Element_Tips* IN pTips)
{
	ODL_SafeRelease(m_pTips);
	m_pTips = pTips;
	if(m_pTips!=NULL)
		m_pTips->AddRef();
	
}
VOID		CODLEx_Element_Button::SetTips(LPCSTR IN pText)
{
	ODL_SafeRelease(m_pTips);
	if(pText == NULL)
		return;
	if(strlen(pText)==0)
		return;
	m_pTips =new CODLEx_Element_Tips(GetCanvas());
	m_pTips->SetText(pText);

}
BOOL		CODLEx_Element_Button::PtInAdjustSizeButton(POINT* IN pt)
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
VOID		CODLEx_Element_Button::EnableAdjustSize(BOOL IN bEnable)
{
	m_bEnableAdjustSize	=bEnable;
}
