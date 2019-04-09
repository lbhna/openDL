#include "stdafx.h"
#include "./ODLEx_Element_ShapeRectangle.h"
#include "./ODLEx_Element_Coordinate.h"



CODLEx_Element_ShapeRectangle::CODLEx_Element_ShapeRectangle(CODL_CanvasBase* IN pCanvas):
CODLEx_Element_ShapeBase(pCanvas)
{
	m_Type					=ODL_ELEMENT_SHAPE_RECTANGLE;
	m_bRoundRect		=FALSE;

}
CODLEx_Element_ShapeRectangle::~CODLEx_Element_ShapeRectangle()
{

}
VOID				CODLEx_Element_ShapeRectangle::SetPos(FLOAT IN x,FLOAT IN y)
{
	m_vPos.x			=x;
	m_vPos.y			=y;
	Invalidate();
}
CODL_Vector2f*		CODLEx_Element_ShapeRectangle::GetPos()
{
	return &m_vPos;
}
VOID				CODLEx_Element_ShapeRectangle::SetSize(FLOAT IN cx,FLOAT IN cy)
{
	m_vSize.x	=cx;
	m_vSize.y	=cy;
}
CODL_Vector2f*		CODLEx_Element_ShapeRectangle::GetSize()
{
	return &m_vSize;
}
BOOL				CODLEx_Element_ShapeRectangle::IsRoundRect()
{
	return m_bRoundRect;
}
VOID				CODLEx_Element_ShapeRectangle::EnableRoundRect(BOOL IN bEnable)
{
	if(m_bRoundRect	== bEnable)
		return;
	m_bRoundRect	=bEnable;
	Invalidate();
}
VOID				CODLEx_Element_ShapeRectangle::SetRoundSize(FLOAT IN cx,FLOAT IN cy)
{
	m_vRoundSize.x	=cx;
	m_vRoundSize.y	=cy;
	Invalidate();
}
CODL_Vector2f*		CODLEx_Element_ShapeRectangle::GetRoundSize()
{
	return &m_vRoundSize;
}

BOOL		CODLEx_Element_ShapeRectangle::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(!IsShow())
		return FALSE;

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
			if(IsControlSwitchKeyPressed()&&IsSelected())
			{

				POINT pos;

				if(PtInAdjustSizeButton(pPoint)&&m_bEnableAdjustSize)
				{
					switch(m_Coordinate)
					{
					case ODLSC_COORDINATE:
						{
							CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
							if(pCoord == NULL)
								return FALSE;
							RECT	rect;
							GetRect(rect);
							pos.x =rect.right;
							pos.y =rect.bottom;
						}
						break;
					default:
						{
							pos.x	=m_vPos.x+m_vSize.x;
							pos.y	=m_vPos.y+m_vSize.y;
						}
						break;
					}
					m_bAdjustSizeing	=TRUE;
					m_ptDragOffset.x	=pos.x - pPoint->x;
					m_ptDragOffset.y	=pos.y - pPoint->y;
					::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
					return TRUE;
				}		

				if(PtInElement(*pPoint)&&m_bEnableDrag)
				{
					switch(m_Coordinate)
					{
					case ODLSC_COORDINATE:
						{
							CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
							if(pCoord == NULL)
								return FALSE;
							pos.x =pCoord->XValueToCoordSpacce(m_vPos.x);
							pos.y =pCoord->YValueToCoordSpacce(m_vPos.y);
						}
						break;
					default:
						{
							pos.x	=m_vPos.x;
							pos.y	=m_vPos.y;
						}
						break;
					}
					m_bDraging	=TRUE;
					m_ptDragOffset.x	=pos.x - pPoint->x;
					m_ptDragOffset.y	=pos.y - pPoint->y;
					return TRUE;			
				}


			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_bDraging)
			{
				m_bDraging	=FALSE;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_PosChanged(this);
				return TRUE;
			}
			if(m_bAdjustSizeing)
			{
				m_bAdjustSizeing	=FALSE;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_SizeChanged(this);
				return TRUE;
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!IsSelected())
				break;
			POINT pos;
			if(m_bDraging)
			{
				pos.x		=pPoint->x + m_ptDragOffset.x;
				pos.y		=pPoint->y + m_ptDragOffset.y;
				switch(m_Coordinate)
				{
				case ODLSC_COORDINATE:
					{
						CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
						if(pCoord == NULL)
							return FALSE;

						m_vPos.x =pCoord->CoordSpaceToXValue(pos.x);
						m_vPos.x =(LONG)(m_vPos.x/pCoord->GetXUnitValue()) * pCoord->GetXUnitValue();

						m_vPos.y =pCoord->CoordSpaceToYValue(pos.y);
						m_vPos.y =(LONG)(m_vPos.y/pCoord->GetYUnitValue()) * pCoord->GetYUnitValue();
					}
					break;
				default:
					{
						m_vPos.x =pos.x;
						m_vPos.y =pos.y;
					}
					break;
				}

				Invalidate(TRUE);
				return TRUE;
			}

			if(m_bAdjustSizeing)
			{
				pos.x		=pPoint->x + m_ptDragOffset.x ;
				pos.y		=pPoint->y + m_ptDragOffset.y;				
				switch(m_Coordinate)
				{
				case ODLSC_COORDINATE:
					{
						CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
						if(pCoord == NULL)
							return FALSE;
					
						CODL_Vector2f vPos;
						vPos.x	=pCoord->CoordSpaceToXValue(pos.x);
						vPos.y	=pCoord->CoordSpaceToYValue(pos.y);

						if(pCoord->IsMinusXAxis())
						{
							if(vPos.x > (m_vPos.x-1.0f*pCoord->GetXUnitValue()) )
							{
								m_bAdjustSizeing=FALSE;
								Invalidate(TRUE);
								return TRUE;
							}
						}
						else
						{
							if(vPos.x < (m_vPos.x+1.0f*pCoord->GetXUnitValue()) )
							{
								m_bAdjustSizeing=FALSE;
								Invalidate(TRUE);
								return TRUE;
							}
						}

						if(pCoord->IsMinusYAxis())
						{
							if(vPos.y < (m_vPos.y+1.0f*pCoord->GetYUnitValue()) )
							{
								m_bAdjustSizeing=FALSE;
								Invalidate(TRUE);
								return TRUE;
							}

						}
						else
						{
							if(vPos.y > (m_vPos.y-1.0f*pCoord->GetYUnitValue()) )
							{
								m_bAdjustSizeing=FALSE;
								Invalidate(TRUE);
								return TRUE;
							}
						}


						m_vSize.x	=fabs(vPos.x - m_vPos.x);
						m_vSize.y	=fabs(vPos.y - m_vPos.y);
					}
					break;
				default:
					{
						if(pos.x < (m_vPos.x+2) || pos.y< (m_vPos.y+2) )
						{
							m_bAdjustSizeing=FALSE;
							Invalidate(TRUE);
							return TRUE;
						}
						m_vSize.x	=pos.x - m_vPos.x;
						m_vSize.y	=pos.y - m_vPos.y;
					}
					break;
				}
				Invalidate(TRUE);
				::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
				return TRUE;
			}

			if(m_bEnableAdjustSize&&IsControlSwitchKeyPressed())
			{
				if(PtInAdjustSizeButton(pPoint))
					::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
			}
		}
		break;

	case WM_KEYDOWN:
		{
			if(!IsSelected())
				break;
			CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
			if(pCoord == NULL)
				return FALSE;

			switch(wParam)
			{
			case VK_LEFT:
				{
					switch(m_Coordinate)
					{
					case ODLSC_COORDINATE:
						{
							m_vPos.x -=pCoord->GetXUnitValue();
						}
						break;
					default:
						{
							m_vPos.x -=1;
						}
						break;
					}

					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			case VK_RIGHT:
				{
					switch(m_Coordinate)
					{
					case ODLSC_COORDINATE:
						{
							m_vPos.x +=pCoord->GetXUnitValue();

						}
						break;
					default:
						{
							m_vPos.x +=1;

						}
						break;
					}
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			case VK_UP:
				{
					switch(m_Coordinate)
					{
					case ODLSC_COORDINATE:
						{
							m_vPos.y -=pCoord->GetYUnitValue();
						}
						break;
					default:
						{
							m_vPos.y -=1;
						}
						break;
					}
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
				break;
			case VK_DOWN:
				{
					switch(m_Coordinate)
					{
					case ODLSC_COORDINATE:
						{
							m_vPos.x +=pCoord->GetXUnitValue();
							m_vPos.y +=pCoord->GetYUnitValue();
						}
						break;
					default:
						{
							m_vPos.x +=1;
							m_vPos.y +=1;
						}
						break;
					}
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
BOOL		CODLEx_Element_ShapeRectangle::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rect;
	GetRect(rect);
	if(m_bStroke)
		m_pStrokePen->Install(hDC);
	else
		SelectObject(hDC,GetStockObject(NULL_PEN));
	if(m_bFill)
		m_pFillBrush->Install(hDC);
	else
		SelectObject(hDC,GetStockObject(NULL_BRUSH));

	SIZE	roundSize;
	if(!m_bRoundRect)
	{
		roundSize.cx	=0;
		roundSize.cy	=0;
	}
	else
	{
		roundSize.cx	=m_vRoundSize.x;
		roundSize.cy	=m_vRoundSize.y;
		switch(m_Coordinate)
		{
		case ODLSC_COORDINATE:
			{
				CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
				if(pCoord != NULL)
				{
					roundSize.cx	=(m_vRoundSize.x/pCoord->GetXUnitValue())*pCoord->GetXPerUnitPixels();
					roundSize.cy	=(m_vRoundSize.y/pCoord->GetYUnitValue())*pCoord->GetYPerUnitPixels();
				}
			}
			break;
		case ODLSC_SCREEN:
			{
			}
			break;
		}
	}

	RoundRect(hDC,rect.left,rect.top,rect.right,rect.bottom,roundSize.cx,roundSize.cy);

	if(m_bStroke)
		m_pStrokePen->Uninstall(hDC);
	if(m_bFill)
		m_pFillBrush->Uninstall(hDC);

	if(IsSelected() )
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
VOID		CODLEx_Element_ShapeRectangle::GetRect(RECT& OUT rect)
{
	rect.left	=0;
	rect.top	=0;
	rect.right	=0;
	rect.bottom	=0;
	switch(m_Coordinate)
	{
	case ODLSC_COORDINATE:
		{
			CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
			if(pCoord != NULL)
			{
				if(pCoord->IsMinusXAxis())
				{
					rect.left	=pCoord->XValueToCoordSpacce(m_vPos.x);
					rect.right	=pCoord->XValueToCoordSpacce(m_vPos.x - m_vSize.x);
				}
				else
				{
					rect.left	=pCoord->XValueToCoordSpacce(m_vPos.x);
					rect.right	=pCoord->XValueToCoordSpacce(m_vPos.x + m_vSize.x);
				}

				if(pCoord->IsMinusYAxis())
				{
					rect.top	=pCoord->YValueToCoordSpacce(m_vPos.y);
					rect.bottom	=pCoord->YValueToCoordSpacce(m_vPos.y + m_vSize.y);
				}
				else
				{
					rect.top	=pCoord->YValueToCoordSpacce(m_vPos.y);
					rect.bottom	=pCoord->YValueToCoordSpacce(m_vPos.y - m_vSize.y);
				}

			}
		}
		break;
	case ODLSC_SCREEN:
		{
			rect.left	=m_vPos.x ;
			rect.top	=m_vPos.y ;
			rect.right	=m_vPos.x + m_vSize.x;
			rect.bottom	=m_vPos.y + m_vSize.y;

		}
		break;
	}
}

BOOL		CODLEx_Element_ShapeRectangle::PtInAdjustSizeButton(POINT* IN pt)
{
	RECT	rect;
	GetRect(rect);

	rect.top	=rect.bottom-5;
	rect.left	=rect.right-5;
	return PtInRect(&rect,*pt);

}

VOID				CODLEx_Element_ShapeRectangle::SetShapeCoordinate(ODL_SHAPE_COORD IN coord)
{
	if(m_Coordinate == coord)
		return;
	if(m_Coordinate == ODLSC_SCREEN)
	{
		CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
		if(pCoord != NULL)
		{
			m_vPos.x		=pCoord->CoordSpaceToXValue(m_vPos.x);
			m_vPos.y		=pCoord->CoordSpaceToYValue(m_vPos.y);
			m_vSize.x		=(m_vSize.x/pCoord->GetXPerUnitPixels())*pCoord->GetXUnitValue();
			m_vSize.y		=(m_vSize.y/pCoord->GetYPerUnitPixels())*pCoord->GetYUnitValue();
		}

	}
	else
	{
		CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
		if(pCoord != NULL)
		{
			m_vPos.x		=pCoord->XValueToCoordSpacce(m_vPos.x);
			m_vPos.y		=pCoord->YValueToCoordSpacce(m_vPos.y);
			m_vSize.x		=(m_vSize.x/pCoord->GetXUnitValue())*pCoord->GetXPerUnitPixels();
			m_vSize.y		=(m_vSize.y/pCoord->GetYUnitValue())*pCoord->GetYPerUnitPixels();
		}
	}
	m_Coordinate	=coord;
	Invalidate();
}

VOID		CODLEx_Element_ShapeRectangle::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	GetRect(boundRect);
	InflateRect(&boundRect,1,1);
}


BOOL		CODLEx_Element_ShapeRectangle::PtInElement(POINT IN pt)
{
	RECT	rect;
	GetRect(rect);
	return PtInRect(&rect,pt);
}