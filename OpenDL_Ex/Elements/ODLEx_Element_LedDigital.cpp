#include "stdafx.h"
#include "./ODLEx_Element_LedDigital.h"



CODLEx_Element_LedDigital::CODLEx_Element_LedDigital(CODL_CanvasBase* IN pCanvas):
CODL_OverlayElementBase(pCanvas)
{
	m_Type					=ODL_ELEMENT_LEDDIGITAL;

	m_pBrightBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(0,200,0),0);
	m_pDarkBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(0,55,0),0);
	m_pBkBrush				=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(0,0,0),0);

	m_Pos.x					=0;
	m_Pos.y					=0;
	m_Size.cx				=420;
	m_Size.cy				=40;
	m_lMargin				=5;
	m_lPadding				=5;
	m_strValue				="-12:34:56.7890";
	for(LONG i=0;i<7;i++)
	{
		for(LONG j=0;j<6;j++)
		{
			m_Points[i][j].x=0;
			m_Points[i][j].y=0;
		}
		m_PointsCount[i]=4;
		if(i==3)
			m_PointsCount[i]=6;
	}
	UpdatePoints();

	m_bPushed			=FALSE;
	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;
	m_bEnableDrag		=FALSE;
	m_bDraging			=FALSE;
	m_bEnableAdjustSize	=FALSE;
	m_bAdjustSizeing	=FALSE;


}
CODLEx_Element_LedDigital::~CODLEx_Element_LedDigital()
{
	ODL_SafeRelease(m_pBrightBrush	);
	ODL_SafeRelease(m_pDarkBrush	);
	ODL_SafeRelease(m_pBkBrush		);
}

VOID		CODLEx_Element_LedDigital::SetBrush(LOGBRUSH* IN pBrightBrush,LOGBRUSH* IN pDarkBrush)
{
	ODL_SafeRelease(m_pBrightBrush	);
	ODL_SafeRelease(m_pDarkBrush	);
	m_pBrightBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(pBrightBrush);
	m_pDarkBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(pDarkBrush);

}
VOID		CODLEx_Element_LedDigital::SetBrush(CODL_Brush* IN pBrightBrush,CODL_Brush* IN pDarkBrush)
{
	ODL_SafeRelease(m_pBrightBrush	);
	m_pBrightBrush =pBrightBrush;
	if(m_pBrightBrush != NULL)
		m_pBrightBrush->AddRef();

	ODL_SafeRelease(m_pDarkBrush	);
	m_pDarkBrush =pDarkBrush;
	if(m_pDarkBrush != NULL)
		m_pDarkBrush->AddRef();

}
VOID		CODLEx_Element_LedDigital::SetBkBrush(LOGBRUSH* IN pBkBrush)
{
	ODL_SafeRelease(m_pBkBrush		);
	m_pBkBrush				=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(pBkBrush);
}
VOID		CODLEx_Element_LedDigital::SetBkBrush(CODL_Brush* IN pBkBrush)
{
	ODL_SafeRelease(m_pBkBrush	);
	m_pBkBrush =pBkBrush;
	if(m_pBkBrush != NULL)
		m_pBkBrush->AddRef();

}
LPCSTR		CODLEx_Element_LedDigital::GetValue()
{
	return m_strValue;
}
VOID		CODLEx_Element_LedDigital::SetValue(LPCSTR IN pValues/*0~9/:/.*/)
{
	if(pValues == NULL)
		m_strValue.Empty();
	else
		m_strValue.Format("%s",pValues);
	Invalidate();
}
VOID		CODLEx_Element_LedDigital::SetPos(LONG IN x,LONG IN y)
{
	if(m_Pos.x == x && m_Pos.y ==y)
		return;
	m_Pos.x =x;
	m_Pos.y =y;
	Invalidate();
}
VOID		CODLEx_Element_LedDigital::SetSize(LONG IN cx,LONG IN cy)
{
	if(m_Size.cy != cy)
	{
		m_Size.cx=cx;
		m_Size.cy=cy;
		UpdatePoints();
		Invalidate();
		return;
	}	
	if(m_Size.cx != cx )
	{
		m_Size.cx=cx;
		m_Size.cy=cy;
		Invalidate();
		return;
	}

}
POINT*		CODLEx_Element_LedDigital::GetPos()
{
	return &m_Pos;
}
SIZE*		CODLEx_Element_LedDigital::GetSize()
{
	return &m_Size;
}
VOID		CODLEx_Element_LedDigital::GetRect(RECT& OUT rect)
{
	rect.left		=m_Pos.x;
	rect.top		=m_Pos.y;
	rect.right		=m_Pos.x	+ m_Size.cx;
	rect.bottom		=m_Pos.y	+ m_Size.cy;

}
LONG		CODLEx_Element_LedDigital::GetMargin()
{
	return m_lMargin;
}


VOID		CODLEx_Element_LedDigital::SetMargin(LONG IN lMargin)
{
	if(m_lMargin == lMargin)
		return;
	m_lMargin	=lMargin;
	Invalidate();
}
LONG		CODLEx_Element_LedDigital::GetPadding()
{
	return m_lPadding;
}
VOID		CODLEx_Element_LedDigital::SetPadding(LONG IN lPadding)
{
	if(m_lPadding == lPadding)
		return;
	m_lPadding =lPadding;
	UpdatePoints();
	Invalidate();
}

VOID		CODLEx_Element_LedDigital::DrawLedDigital(HDC IN hDC,POINT* IN Pos,CHAR IN ch)
{
	POINT Points[7][6];
	LONG i,j;
	for( i=0;i<7;i++)
	{
		for( j=0;j<6;j++)
		{
			Points[i][j].x=m_Points[i][j].x+Pos->x;
			Points[i][j].y=m_Points[i][j].y+Pos->y+m_lPadding;
		}
	}
	BOOL	bBright[7];
	for( i=0;i<7;i++)
		bBright[i]=FALSE;
	switch(ch)
	{
	case '0':
		{
			bBright[0]=TRUE;
			bBright[1]=TRUE;
			bBright[2]=TRUE;
			bBright[4]=TRUE;
			bBright[5]=TRUE;
			bBright[6]=TRUE;
		}
		break;
	case '1':
		{
			bBright[2]=TRUE;
			bBright[5]=TRUE;
		}
		break;
	case '2':
		{
			bBright[0]=TRUE;
			bBright[2]=TRUE;
			bBright[3]=TRUE;
			bBright[4]=TRUE;
			bBright[6]=TRUE;
		}
		break;
	case '3':
		{
			bBright[0]=TRUE;
			bBright[2]=TRUE;
			bBright[3]=TRUE;
			bBright[5]=TRUE;
			bBright[6]=TRUE;

		}
		break;
	case '4':
		{
			bBright[1]=TRUE;
			bBright[2]=TRUE;
			bBright[3]=TRUE;
			bBright[5]=TRUE;
		}
		break;
	case '5':
		{
			bBright[0]=TRUE;
			bBright[1]=TRUE;
			bBright[3]=TRUE;
			bBright[5]=TRUE;
			bBright[6]=TRUE;
		}
		break;
	case '6':
		{
			bBright[0]=TRUE;
			bBright[1]=TRUE;
			bBright[3]=TRUE;
			bBright[4]=TRUE;
			bBright[5]=TRUE;
			bBright[6]=TRUE;
		}
		break;
	case '7':
		{
			bBright[0]=TRUE;
			bBright[2]=TRUE;
			bBright[5]=TRUE;
		}
		break;
	case '8':
		{
			bBright[0]=TRUE;
			bBright[1]=TRUE;
			bBright[2]=TRUE;
			bBright[3]=TRUE;
			bBright[4]=TRUE;
			bBright[5]=TRUE;
			bBright[6]=TRUE;
		}
		break;
	case '9':
		{
			bBright[0]=TRUE;
			bBright[1]=TRUE;
			bBright[2]=TRUE;
			bBright[3]=TRUE;
			bBright[5]=TRUE;
			bBright[6]=TRUE;
		}
		break;
	case '-':
		{
			bBright[3]=TRUE;
		}
		break;
	case ':':
		{
			LONG	h		=m_Size.cy-m_lPadding*2;
			LONG w =h/2;

			RECT rect;
			rect.left =Pos->x+w/2;
			rect.right=Pos->x+w/2 +1;
			rect.top	=Pos->y+h/4+m_lPadding;
			rect.bottom =rect.top+1;
			InflateRect(&rect,h/10,h/10);
			m_pBrightBrush->Install(hDC);
			SelectObject(hDC,(HGDIOBJ)NULL_PEN);
			Ellipse(hDC,rect.left,rect.top,rect.right,rect.bottom);
			m_pBrightBrush->Uninstall(hDC);

			rect.left =Pos->x+w/2;
			rect.right=Pos->x+w/2 +1;
			rect.top	=Pos->y+h - h/4 +m_lPadding;
			rect.bottom =rect.top+1;
			InflateRect(&rect,h/10,h/10);

			m_pBrightBrush->Install(hDC);
			SelectObject(hDC,(HGDIOBJ)NULL_PEN);
			Ellipse(hDC,rect.left,rect.top,rect.right,rect.bottom);
			m_pBrightBrush->Uninstall(hDC);

			return;

		}
		break;
	case '.':
		{
			LONG	h		=m_Size.cy-m_lPadding*2;
			LONG	w		=h/2;

			RECT rect;
			rect.left =Pos->x+w/2;
			rect.right=Pos->x+w/2 +1;
			rect.top	=Pos->y+h - h/5 +m_lPadding;
			rect.bottom =rect.top+1;
			InflateRect(&rect,h/10,h/10);


			m_pBrightBrush->Install(hDC);
			SelectObject(hDC,(HGDIOBJ)NULL_PEN);
			Ellipse(hDC,rect.left,rect.top,rect.right,rect.bottom);
			m_pBrightBrush->Uninstall(hDC);

			return;
		}
		break;
	default:
		break;
	}

	m_pBrightBrush->Install(hDC);
	for( i=0;i<7;i++)
	{
		if(!bBright[i])
			continue;
		HRGN hRgn =::CreatePolygonRgn(Points[i],m_PointsCount[i],ALTERNATE);
		if(hRgn != NULL)
		{
			m_pBrightBrush->FillRgn(hRgn);
			DeleteObject(hRgn);
		}
	}
	m_pBrightBrush->Uninstall(hDC);

	m_pDarkBrush->Install(hDC);
	for( i=0;i<7;i++)
	{
		if(bBright[i])
			continue;
		HRGN hRgn =::CreatePolygonRgn(Points[i],m_PointsCount[i],ALTERNATE);
		if(hRgn != NULL)
		{
			m_pDarkBrush->FillRgn(hRgn);
			DeleteObject(hRgn);
		}
	}
	m_pDarkBrush->Uninstall(hDC);

}
VOID		CODLEx_Element_LedDigital::UpdatePoints()
{
	LONG		h		=m_Size.cy-m_lPadding*2;
	LONG		w		=h/10;

	m_Points[0][0].x	=0;
	m_Points[0][0].y	=0;
	m_Points[0][1].x	=(h)/2;
	m_Points[0][1].y	=0;
	m_Points[0][2].x	=m_Points[0][1].x - w;
	m_Points[0][2].y	=w;
	m_Points[0][3].x	=w;
	m_Points[0][3].y	=w;

	m_Points[1][0].x	=0;
	m_Points[1][0].y	=w/2;
	m_Points[1][1].x	=m_Points[1][0].x+w;
	m_Points[1][1].y	=m_Points[1][0].y+w;
	m_Points[1][2].x	=m_Points[1][1].x;
	m_Points[1][2].y	=(h/2)-w;
	m_Points[1][3].x	=0;
	m_Points[1][3].y	=m_Points[1][2].y + w;

	m_Points[2][0].x	=(h/2)-w;
	m_Points[2][0].y	=w+w/2;
	m_Points[2][1].x	=m_Points[2][0].x+w;
	m_Points[2][1].y	=m_Points[2][0].y-w;	
	m_Points[2][2].x	=m_Points[2][1].x;
	m_Points[2][2].y	=(h/2);	
	m_Points[2][3].x	=m_Points[2][0].x;
	m_Points[2][3].y	=m_Points[2][2].y - w;

	m_Points[3][0].x	=w/2;
	m_Points[3][0].y	=h/2;
	m_Points[3][1].x	=w;
	m_Points[3][1].y	=m_Points[3][0].y-w/2;
	m_Points[3][2].x	=h/2-w;
	m_Points[3][2].y	=m_Points[3][1].y;	
	m_Points[3][3].x	=h/2-w/2;;
	m_Points[3][3].y	=m_Points[3][2].y+w/2;
	m_Points[3][4].x	=m_Points[3][2].x;
	m_Points[3][4].y	=m_Points[3][2].y+w;
	m_Points[3][5].x	=m_Points[3][1].x;
	m_Points[3][5].y	=m_Points[3][4].y;

	m_Points[4][0].x	=0;
	m_Points[4][0].y	=(h/2);	
	m_Points[4][1].x	=w;
	m_Points[4][1].y	=m_Points[4][0].y+w;
	m_Points[4][2].x	=m_Points[4][1].x;
	m_Points[4][2].y	=h-w-w/2;
	m_Points[4][3].x	=0;
	m_Points[4][3].y	=m_Points[4][2].y + w;

	m_Points[5][0].x	=(h/2)-w;
	m_Points[5][0].y	=m_Points[4][1].y;
	m_Points[5][1].x	=(h/2);
	m_Points[5][1].y	=m_Points[4][0].y;
	m_Points[5][2].x	=m_Points[5][1].x;
	m_Points[5][2].y	=h-w/2;
	m_Points[5][3].x	=m_Points[5][0].x;
	m_Points[5][3].y	=m_Points[5][2].y - w;

	m_Points[6][0].x	=w;
	m_Points[6][0].y	=h-w;
	m_Points[6][1].x	=(h/2)-w;
	m_Points[6][1].y	=m_Points[6][0].y;
	m_Points[6][2].x	=(h/2);
	m_Points[6][2].y	=h;
	m_Points[6][3].x	=0;
	m_Points[6][3].y	=m_Points[6][2].y;


}
BOOL		CODLEx_Element_LedDigital::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT rect;
	GetRect(rect);
	m_pBkBrush->Install(hDC);
	m_pBkBrush->FillRect(&rect);
	m_pBkBrush->Uninstall(hDC);

	POINT	pt;
	pt.x =m_Pos.x+m_lPadding;
	pt.y =m_Pos.y;
	LONG h =m_Size.cy -m_lPadding*2;
	for(LONG i=0;i<m_strValue.GetLength();i++)
	{
		if( (pt.x + h/2) > (m_Pos.x+m_Size.cx) )
			break;
		DrawLedDigital(hDC,&pt,m_strValue.GetAt(i));
		pt.x += h/2 +m_lMargin;
	}




	if(IsSelected())
	{
		m_pCanvas->GetElementSelectFramePen()->Install(hDC);
		
		m_pCanvas->GetElementSelectFramePen()->DrawRect(&rect);
		if(m_bEnableAdjustSize)
		{
			for(INT i=1;i<=7;i++)
			{
				MoveToEx(hDC,rect.right,rect.bottom-i,NULL);
				LineTo(hDC,rect.right-i,rect.bottom);			
			}
		}
		m_pCanvas->GetElementSelectFramePen()->Uninstall(hDC);
	}
	return TRUE;
}

BOOL			CODLEx_Element_LedDigital::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	GetRect(rect);
	return PtInRect(&rect,pt);
}
VOID			CODLEx_Element_LedDigital::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	GetRect(boundRect);
	InflateRect(&boundRect,5,5);
}
BOOL			CODLEx_Element_LedDigital::PtInAdjustSizeButton(POINT* IN pt)
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

BOOL			CODLEx_Element_LedDigital::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
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
					UpdatePoints();
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
VOID			CODLEx_Element_LedDigital::EnableAdjustSize(BOOL IN bEnable)
{
	m_bEnableAdjustSize	=bEnable;
}

