#include "StdAfx.h"
#include ".\odlex_element_checkbutton.h"

CODLEx_Element_CheckButton::CODLEx_Element_CheckButton(CODL_CanvasBase* IN pCanvas):
CODLEx_Element_Button(pCanvas)
{
	m_Type					=ODL_ELEMENT_CHECK_BUTTON;
	m_bChecked				=FALSE;
	m_bGroupControl			=TRUE;
}

CODLEx_Element_CheckButton::~CODLEx_Element_CheckButton(void)
{
}
VOID				CODLEx_Element_CheckButton::SetChecked(BOOL IN bChecked)
{
	if(m_bChecked == bChecked)
		return;
	m_bChecked	=bChecked;
	Invalidate();
}
BOOL				CODLEx_Element_CheckButton::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rec;
	if(m_bChecked)
		FillRect(hDC,GetRect(&rec),m_pActiveBkBrush->GetBrush());
	else
		FillRect(hDC,GetRect(&rec),m_pBkBrush->GetBrush());

	LONG	x	=m_Pos.x + 2;
	LONG	y	=m_Pos.y + 2;
	if(m_hIcon != NULL)
	{
		DWORD	width	=min(m_Size.cx,m_Size.cy)-4;
		if(m_bChecked)
			x++;
		DrawIconEx(hDC,x,y,m_hIcon,width,width,0,NULL,DI_NORMAL);
		x += width;
	}

	if(m_pTitle != NULL && m_pTitleFont != NULL)
	{
		rec.left	=x + 1;
		rec.top		=m_Pos.y + 2;
		rec.right	=m_Pos.x + m_Size.cx;
		rec.bottom	=m_Pos.y + m_Size.cy;

		m_pTitleFont->Install(hDC);
		SetTextColor(hDC,m_TitleColor);
		SetBkMode(hDC,TRANSPARENT);
		DrawText(hDC,m_pTitle,strlen(m_pTitle),&rec,DT_LEFT|DT_VCENTER);
		m_pTitleFont->Uninstall(hDC);
	}

	if(m_bChecked)
		DrawPushedBorder(hDC);
	else
		DrawNormalBorder(hDC);


	if(m_pTips != NULL)
		m_pTips->Draw(hDC,pPaintRect);

	return TRUE;
}

BOOL		CODLEx_Element_CheckButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(PtInElement(*pPoint))
			{
				m_bPushed	=	TRUE;
				Invalidate(TRUE);
				return TRUE;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if(PtInElement(*pPoint) && m_bPushed)
			{
				m_bPushed =FALSE;
				m_bChecked	=	!m_bChecked;
				Invalidate(TRUE);
				return TRUE;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(m_bPushed)
			{
				if(!PtInElement(*pPoint))
				{
					m_bPushed =FALSE;
					Invalidate(TRUE);
				}
			}
	
			if(!PtInElement(*pPoint))
			{
				if(m_bMouseOver)
				{
					m_bMouseOver =FALSE;
					OnMouseOut();
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
		break;
	}

	return FALSE;
}
