#include "stdafx.h"
#include "./ODLEx_Element_ShapeLine.h"
#include "./ODLEx_Element_Coordinate.h"

CODLEx_Element_ShapeLine::CODLEx_Element_ShapeLine(CODL_CanvasBase* IN pCanvas):
CODLEx_Element_ShapeBase(pCanvas)
{
	m_Type					=ODL_ELEMENT_SHAPE_LINE;
	m_bAdjustStartPoint		=TRUE;
	m_ptStartOffset.x		=0;
	m_ptStartOffset.y		=0;
	m_ptEndOffset.x			=0;
	m_ptEndOffset.y			=0;
}
CODLEx_Element_ShapeLine::~CODLEx_Element_ShapeLine()
{

}
BOOL		CODLEx_Element_ShapeLine::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
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
			if(IsControlSwitchKeyPressed()&&IsSelected())
			{
				POINT	start,end;
				GetPoint(start,end);
				if(PtInAdjustSizeButton(pPoint)&&m_bEnableAdjustSize)
				{
					m_bAdjustSizeing	=TRUE;
					if(m_bAdjustStartPoint)
					{
						m_ptDragOffset.x	=start.x - pPoint->x;
						m_ptDragOffset.y	=start.y - pPoint->y;
					}
					else
					{
						m_ptDragOffset.x	=end.x - pPoint->x;
						m_ptDragOffset.y	=end.y - pPoint->y;
					}

					::SetCursor(::LoadCursor(NULL,IDC_SIZEALL));
					return TRUE;
				}
				if(PtInElement(*pPoint)&&m_bEnableDrag)
				{
					m_bDraging	=TRUE;
					m_ptStartOffset.x	=start.x	- pPoint->x;
					m_ptStartOffset.y	=start.y	- pPoint->y;
					m_ptEndOffset.x		=end.x		- pPoint->x;
					m_ptEndOffset.y		=end.y		- pPoint->y;
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
			if(m_bDraging)
			{
				POINT start,end;
				start.x		=pPoint->x + m_ptStartOffset.x;
				start.y		=pPoint->y + m_ptStartOffset.y;

				end.x		=pPoint->x + m_ptEndOffset.x;
				end.y		=pPoint->y + m_ptEndOffset.y;
				switch(m_Coordinate)
				{
				case ODLSC_COORDINATE:
					{
						CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
						if(pCoord == NULL)
							return FALSE;
						m_vStart.x =pCoord->CoordSpaceToXValue(start.x);
						m_vStart.x =(LONG)(m_vStart.x/pCoord->GetXUnitValue()) * pCoord->GetXUnitValue();
						m_vStart.y =pCoord->CoordSpaceToYValue(start.y);
						m_vStart.y =(LONG)(m_vStart.y/pCoord->GetYUnitValue()) * pCoord->GetYUnitValue();

						m_vEnd.x =pCoord->CoordSpaceToXValue(end.x);
						m_vEnd.x =(LONG)(m_vEnd.x/pCoord->GetXUnitValue()) * pCoord->GetXUnitValue();
						m_vEnd.y =pCoord->CoordSpaceToYValue(end.y);
						m_vEnd.y =(LONG)(m_vEnd.y/pCoord->GetYUnitValue()) * pCoord->GetYUnitValue();
					}
					break;
				default:
					{
						m_vStart.x	=start.x;
						m_vStart.y	=start.y;
						m_vEnd.x	=end.x;
						m_vEnd.y	=end.y;
					}
					break;
				}

				Invalidate(TRUE);
				return TRUE;
			}


			if(m_bAdjustSizeing)
			{
				POINT	pos;
				pos.x		=pPoint->x + m_ptDragOffset.x;
				pos.y		=pPoint->y + m_ptDragOffset.y;	

				CODL_Vector2f vPos;
				switch(m_Coordinate)
				{
				case ODLSC_COORDINATE:
					{
						CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
						if(pCoord == NULL)
							return FALSE;

						vPos.x	=pCoord->CoordSpaceToXValue(pos.x);
						vPos.y	=pCoord->CoordSpaceToYValue(pos.y);
					}
					break;
				default:
					{
						vPos.x	=pos.x;
						vPos.y	=pos.y;
					}
					break;
				}
				if(m_bAdjustStartPoint)
					m_vStart	=vPos;
				else
					m_vEnd		=vPos;

				Invalidate(TRUE);
				::SetCursor(::LoadCursor(NULL,IDC_SIZEALL));
				return TRUE;
			}

			if(m_bEnableAdjustSize&&IsControlSwitchKeyPressed())
			{
				if(PtInAdjustSizeButton(pPoint))
					::SetCursor(::LoadCursor(NULL,IDC_SIZEALL));
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
							m_vStart.x -=pCoord->GetXUnitValue();
							m_vEnd.x -=pCoord->GetXUnitValue();
						}
						break;
					default:
						{
							m_vStart.x -=1;
							m_vEnd.x -=1;
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
							m_vStart.x	+=pCoord->GetXUnitValue();
							m_vEnd.x	+=pCoord->GetXUnitValue();

						}
						break;
					default:
						{
							m_vStart.x +=1;
							m_vEnd.x +=1;

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
							m_vStart.y	-=pCoord->GetYUnitValue();
							m_vEnd.y	-=pCoord->GetYUnitValue();
						}
						break;
					default:
						{
							m_vStart.y	-=1;
							m_vEnd.y	-=1;
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
							m_vStart.y	 +=pCoord->GetXUnitValue();
							m_vEnd.y	 +=pCoord->GetYUnitValue();
						}
						break;
					default:
						{
							m_vStart.y	 +=1;
							m_vEnd.y	 +=1;
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
BOOL		CODLEx_Element_ShapeLine::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	POINT	start,end;
	GetPoint(start,end);

	m_pStrokePen->Install(hDC);
	::MoveToEx(hDC,start.x,start.y,NULL);
	::LineTo(hDC,end.x,end.y);
	m_pStrokePen->Uninstall(hDC);

	if(IsSelected())
	{
		LONG size =(m_pStrokePen->GetLogPen()->lopnWidth.x +3);
		m_pCanvas->GetElementSelectFramePen()->Install(hDC);
		m_pCanvas->GetElementSelectFramePen()->DrawSquare(&start	,size,size);
		m_pCanvas->GetElementSelectFramePen()->DrawSquare(&end		,size,size);
		m_pCanvas->GetElementSelectFramePen()->Uninstall(hDC);
	}

	return TRUE;
}	
VOID				CODLEx_Element_ShapeLine::SetStartPoint(FLOAT IN x,FLOAT IN y)
{
	m_vStart.x	=x;
	m_vStart.y	=y;
	Invalidate();
}
CODL_Vector2f*		CODLEx_Element_ShapeLine::GetStartPoint()
{
	return &m_vStart;
}
VOID				CODLEx_Element_ShapeLine::SetEndPoint(FLOAT IN x,FLOAT IN y)
{
	m_vEnd.x	=x;
	m_vEnd.y	=y;
	Invalidate();
}
CODL_Vector2f*		CODLEx_Element_ShapeLine::GetEndPoint()
{
	return &m_vEnd;
}
VOID				CODLEx_Element_ShapeLine::GetPoint(POINT& OUT start,POINT& OUT end)
{
	start.x=start.y=end.x=end.y=0;

	switch(m_Coordinate)
	{
	case ODLSC_COORDINATE:
		{
			CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
			if(pCoord != NULL)
			{
				start.x		=pCoord->XValueToCoordSpacce(m_vStart.x);
				end.x		=pCoord->XValueToCoordSpacce(m_vEnd.x);			
				start.y		=pCoord->YValueToCoordSpacce(m_vStart.y);
				end.y		=pCoord->YValueToCoordSpacce(m_vEnd.y);
			}
		}
		break;
	case ODLSC_SCREEN:
		{
			start.x		=m_vStart.x;
			start.y		=m_vStart.y;
			end.x		=m_vEnd.x;
			end.y		=m_vEnd.y;
		}
		break;
	}
}
VOID				CODLEx_Element_ShapeLine::SetShapeCoordinate(ODL_SHAPE_COORD IN coord)
{
	if(m_Coordinate == coord)
		return;
	if(m_Coordinate == ODLSC_SCREEN)
	{
		CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
		if(pCoord != NULL)
		{
			m_vStart.x		=pCoord->CoordSpaceToXValue(m_vStart.x);
			m_vEnd.x		=pCoord->CoordSpaceToXValue(m_vEnd.x);			
			m_vStart.y		=pCoord->CoordSpaceToYValue(m_vStart.y);
			m_vEnd.y		=pCoord->CoordSpaceToYValue(m_vEnd.y);
		}

	}
	else
	{
		CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
		if(pCoord != NULL)
		{
			m_vStart.x		=pCoord->XValueToCoordSpacce(m_vStart.x);
			m_vEnd.x		=pCoord->XValueToCoordSpacce(m_vEnd.x);			
			m_vStart.y		=pCoord->YValueToCoordSpacce(m_vStart.y);
			m_vEnd.y		=pCoord->YValueToCoordSpacce(m_vEnd.y);
		}
	}
	m_Coordinate	=coord;

	Invalidate();
}
VOID				CODLEx_Element_ShapeLine::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	POINT	start,end;
	GetPoint(start,end);
	boundRect.left	=boundRect.right	=start.x;
	boundRect.top	=boundRect.bottom	=start.y;

	if(boundRect.left>end.x)
		boundRect.left =end.x;
	if(boundRect.right<end.x)
		boundRect.right=end.x;
	if(boundRect.top>end.y)
		boundRect.top=end.y;
	if(boundRect.bottom<end.y)
		boundRect.bottom=end.y;
}

BOOL				CODLEx_Element_ShapeLine::PtInElement(POINT IN pt)
{
	POINT	start,end;
	GetPoint(start,end);
	return PtInLine(pt,start,end);
}
BOOL		CODLEx_Element_ShapeLine::PtInAdjustSizeButton(POINT* IN pt)
{
	POINT	start,end;
	GetPoint(start,end);
	LONG size =(m_pStrokePen->GetLogPen()->lopnWidth.x +3)/2;

	RECT	r1,r2;
	r1.left		=start.x-size;
	r1.right	=start.x+size;
	r1.top		=start.y-size;
	r1.bottom	=start.y+size;
	if(PtInRect(&r1,*pt))
	{
		m_bAdjustStartPoint	=TRUE;
		return TRUE;
	}
	r2.left		=end.x-size;
	r2.right	=end.x+size;
	r2.top		=end.y-size;
	r2.bottom	=end.y+size;
	if(PtInRect(&r2,*pt))
	{
		m_bAdjustStartPoint	=FALSE;
		return TRUE;
	}
	return FALSE;
}
