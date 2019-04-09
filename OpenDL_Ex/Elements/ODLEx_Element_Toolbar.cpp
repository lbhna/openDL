#include "StdAfx.h"
#include ".\odlex_element_toolbar.h"

CODLEx_Element_Toolbar::CODLEx_Element_Toolbar(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_TOOLBAR;
	m_pCurActiveButton	=NULL;
	m_Pos.x =m_Pos.y	=0;
	m_ButtonSize.cx =m_ButtonSize.cy=32;


	m_bDraging			=FALSE;
	m_ptDragOffset.x=m_ptDragOffset.y=0;

	ZeroMemory(&m_BkRect,sizeof(m_BkRect));
	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(200,200,200),NULL);
	m_pDragbarPen		=pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(100,100,100));
	m_bExpand			=TRUE;
	m_ZIndex			=10;
	m_lDragbarWidth		=15;
}

CODLEx_Element_Toolbar::~CODLEx_Element_Toolbar(void)
{
	Clear();
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pDragbarPen);
}
VOID		CODLEx_Element_Toolbar::SetBkColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush	=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(PS_SOLID,clr,NULL);
}

BOOL		CODLEx_Element_Toolbar::AddButton(CODLEx_Element_Button* IN pButton)
{
	if(pButton == NULL)
		return FALSE;
	if(pButton->GetID() ==0)
		return FALSE;
	if(FindButton(pButton->GetID())!=NULL)
		return FALSE;
	m_theButtonList.AddTail(&pButton);
	pButton->AddRef();
	
	RelayoutButton();
	return TRUE;
}

VOID		CODLEx_Element_Toolbar::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	RelayoutButton();
	Invalidate();
}
VOID		CODLEx_Element_Toolbar::SetButtonSize(LONG IN cx,LONG IN cy)
{
	m_ButtonSize.cx		=cx;
	m_ButtonSize.cy		=cy;
	RelayoutButton();
	Invalidate();
}

CODLEx_Element_Button*		CODLEx_Element_Toolbar::GetFirstButton(POSITION& IN pos)
{
	pos		=m_theButtonList.GetFirstPosition();
	
	CODLEx_Element_Button** pNode =m_theButtonList.GetAt(pos);
	if(pNode ==NULL)
		return NULL;
	return *pNode;
}
CODLEx_Element_Button*		CODLEx_Element_Toolbar::GetNextButton(POSITION& IN pos)
{
	m_theButtonList.MoveNext(pos);

	CODLEx_Element_Button** pNode =m_theButtonList.GetAt(pos);
	if(pNode ==NULL)
		return NULL;
	return *pNode;

}
CODLEx_Element_Button*		CODLEx_Element_Toolbar::FindButton(DWORD IN dwBtnID)
{
	POSITION	pos;
	CODLEx_Element_Button*		pButton =GetFirstButton(pos);
	while(pButton != NULL)
	{
		if(pButton->GetID() == dwBtnID)
			return pButton;
		pButton =GetNextButton(pos);
	}
	return NULL;
}
VOID		CODLEx_Element_Toolbar::Clear()
{
	POSITION	pos;
	CODLEx_Element_Button*		pButton =GetFirstButton(pos);
	while(pButton != NULL)
	{
		pButton->Release();
		pButton =GetNextButton(pos);
	}
	m_theButtonList.DestroyList();
}
VOID		CODLEx_Element_Toolbar::RelayoutButton()
{
	POINT		pt	=m_Pos;
	pt.x	+= m_lDragbarWidth;

	m_BkRect.left	=m_Pos.x;
	m_BkRect.top	=m_Pos.y;
	POSITION	pos;
	CODLEx_Element_Button*		pButton =GetFirstButton(pos);
	while(pButton != NULL)
	{
		if(pButton->IsShow())
		{
			pButton->SetSize(m_ButtonSize.cx,m_ButtonSize.cy);
			pButton->SetPos(pt.x,pt.y);
			pt.x += m_ButtonSize.cx +2;
		}
		pButton =GetNextButton(pos);
	}
	m_BkRect.right	=pt.x;
	m_BkRect.bottom	=m_Pos.y + m_ButtonSize.cy;


}
VOID		CODLEx_Element_Toolbar::GetSize(LONG& OUT cx,LONG& OUT cy)
{
	cx	=m_BkRect.right -m_BkRect.left;
	cy	=m_BkRect.bottom-m_BkRect.top;
}

VOID		CODLEx_Element_Toolbar::DrawBkground(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_pBkBrush != NULL)
		FillRect(hDC,&m_BkRect,m_pBkBrush->GetBrush());
	if(m_pDragbarPen != NULL)
	{
		m_pDragbarPen->Install(hDC);
		RECT	expand_rect;
		expand_rect.left	=m_Pos.x +2;
		expand_rect.top		=m_Pos.y +2;
		expand_rect.right	=m_Pos.x+m_lDragbarWidth-2;
		expand_rect.bottom	=m_Pos.y+(m_ButtonSize.cy/2)-1;
		if(m_bExpand)
		{
			InflateRect(&expand_rect,-1,-1);

			MoveToEx(hDC,expand_rect.right,expand_rect.top,NULL);
			LineTo(hDC,expand_rect.left,expand_rect.top + (expand_rect.bottom-expand_rect.top)/2);
			LineTo(hDC,expand_rect.right,expand_rect.bottom);
			LineTo(hDC,expand_rect.right,expand_rect.top);
			InflateRect(&expand_rect,-1,-1);
			MoveToEx(hDC,expand_rect.right,expand_rect.top,NULL);
			LineTo(hDC,expand_rect.left,expand_rect.top + (expand_rect.bottom-expand_rect.top)/2);
			LineTo(hDC,expand_rect.right,expand_rect.bottom);
			LineTo(hDC,expand_rect.right,expand_rect.top);
		}
		else
		{
			InflateRect(&expand_rect,-1,-1);
			MoveToEx(hDC,expand_rect.left,expand_rect.top,NULL);
			LineTo(hDC,expand_rect.right,expand_rect.top + (expand_rect.bottom-expand_rect.top)/2);
			LineTo(hDC,expand_rect.left,expand_rect.bottom);
			LineTo(hDC,expand_rect.left,expand_rect.top);
			InflateRect(&expand_rect,-1,-1);
			MoveToEx(hDC,expand_rect.left,expand_rect.top,NULL);
			LineTo(hDC,expand_rect.right,expand_rect.top + (expand_rect.bottom-expand_rect.top)/2);
			LineTo(hDC,expand_rect.left,expand_rect.bottom);
			LineTo(hDC,expand_rect.left,expand_rect.top);
		}
		for(LONG y = m_Pos.y+(m_ButtonSize.cy/2)+1;y<m_Pos.y+m_ButtonSize.cy;y+=2)
		{
			MoveToEx(hDC,m_Pos.x+2,y,NULL);
			LineTo(hDC,m_Pos.x+m_lDragbarWidth-2,y);
		}
		m_pDragbarPen->Uninstall(hDC);
	}
}

BOOL		CODLEx_Element_Toolbar::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	DrawBkground(hDC,pPaintRect);

	/////////////////////////////////////////////////////////////
	POSITION	pos;
	CODLEx_Element_Button*		pButton =GetFirstButton(pos);
	while(pButton != NULL)
	{
		pButton->Draw(hDC,pPaintRect);
		pButton =GetNextButton(pos);
	}



	return TRUE;
}
BOOL		CODLEx_Element_Toolbar::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	POSITION	pos;
	CODLEx_Element_Button*		pButton =GetFirstButton(pos);
	while(pButton != NULL)
	{
		if(pButton->GetType() != ODL_ELEMENT_CHECK_BUTTON  || message == WM_MOUSEMOVE)
		{
			if(pButton->OnWndMsg(message,  wParam,  lParam,  pResult, pPoint))
				return TRUE;
		}
		pButton =GetNextButton(pos);
	}

	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(PtInDragBar(pPoint))
			{
				m_bDraging	=TRUE;
				m_ptDragOffset.x	=m_Pos.x - pPoint->x;
				m_ptDragOffset.y	=m_Pos.y - pPoint->y;
				return TRUE;
			}
			if(PtInExpandBar(pPoint))
			{
				m_bExpand =!m_bExpand;
				pButton =GetFirstButton(pos);
				while(pButton != NULL)
				{
					pButton->Show(m_bExpand);
					pButton =GetNextButton(pos);
				}
				RelayoutButton();
				Invalidate(TRUE);
				return TRUE;
			}
			pButton =GetFirstButton(pos);
			while(pButton != NULL)
			{
				if(pButton->GetType() == ODL_ELEMENT_CHECK_BUTTON)	
				{
					if(pButton->PtInElement(*pPoint))
					{
						m_pCurActiveButton = pButton;
						return TRUE;
					}
				}
				pButton =GetNextButton(pos);
			}
	


		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_bDraging)
			{
				m_bDraging	=FALSE;
				POINT pt;
				pt.x	=pPoint->x + m_ptDragOffset.x;
				pt.y	=pPoint->y + m_ptDragOffset.y;
				SetPos(pt.x,pt.y);
				Invalidate(TRUE);
				return TRUE;
			}

			pButton =GetFirstButton(pos);
			while(pButton != NULL)
			{
				if(pButton->PtInElement(*pPoint))
				{
					if(pButton->GetType() == ODL_ELEMENT_CHECK_BUTTON)	
					{
						if(m_pCurActiveButton == pButton)
							OnButtonClicked(pButton);
					}
					else
					{
						OnButtonClicked(pButton);
					}
					return TRUE;
				}
				pButton =GetNextButton(pos);
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			if(m_bDraging)
			{
				POINT pt;
				pt.x	=pPoint->x + m_ptDragOffset.x;
				pt.y	=pPoint->y + m_ptDragOffset.y;
				SetPos(pt.x,pt.y);
				Invalidate(TRUE);
				return TRUE;
			}



		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			pButton =GetFirstButton(pos);
			while(pButton != NULL)
			{//¹ýÂËµôË«»÷ÏûÏ¢
				if(pButton->PtInElement(*pPoint))
					return TRUE;
				pButton =GetNextButton(pos);
			}
		}
		break;
	}


	return FALSE;
}
VOID		CODLEx_Element_Toolbar::OnButtonClicked(CODLEx_Element_Button* IN pButton)
{
	POSITION	pos;
	CODLEx_Element_Button*		p =GetFirstButton(pos);
	CODLEx_Element_CheckButton* pCheckBtn;
	while(p != NULL)
	{
		if(p->GetType() == ODL_ELEMENT_CHECK_BUTTON && p->GetType() == pButton->GetType())
		{
			pCheckBtn =(CODLEx_Element_CheckButton*)p;
			if(pCheckBtn == pButton)
				pCheckBtn->SetChecked(!pCheckBtn->IsChecked());
			else
			{	
				if(pCheckBtn->IsGroupControl() && ((CODLEx_Element_CheckButton*)pButton)->IsGroupControl())
					pCheckBtn->SetChecked(FALSE);
			}
		}

		p =GetNextButton(pos);
	}
	Invalidate(TRUE);
}
BOOL		CODLEx_Element_Toolbar::PtInDragBar(POINT* IN pt)
{
	RECT		rect;
	rect.left	=m_Pos.x;
	rect.top	=m_Pos.y + (m_ButtonSize.cy/2);
	rect.right	=m_Pos.x + m_lDragbarWidth;
	rect.bottom	=m_Pos.y + m_ButtonSize.cy;
	return PtInRect(&rect,*pt);
}
BOOL		CODLEx_Element_Toolbar::PtInExpandBar(POINT* IN pt)
{
	RECT	expand_rect;
	expand_rect.left	=m_Pos.x +2;
	expand_rect.top		=m_Pos.y +2;
	expand_rect.right	=m_Pos.x+m_lDragbarWidth-2;
	expand_rect.bottom	=m_Pos.y+(m_ButtonSize.cy/2)-1;
	return PtInRect(&expand_rect,*pt);
}
