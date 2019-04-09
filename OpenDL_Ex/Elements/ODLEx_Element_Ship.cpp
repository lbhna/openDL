#include "stdafx.h"
#include "ODLEx_Element_Ship.h"
#include "./ODLEx_Element_Coordinate.h"


CODLEx_Element_Ship::CODLEx_Element_Ship(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_BodySize.cx			=10;
	m_BodySize.cy			=5;
	m_lHeaderLength			=5;

	LOGPEN	lp;
	lp.lopnColor			=RGB(255,255,255);
	lp.lopnStyle			=PS_SOLID;
	lp.lopnWidth.x			=lp.lopnWidth.y	=2;
	m_pBorderPen			=pCanvas->GetView()->GetResourceManager()->CreatePen(&lp);
	m_CoordType				=ODLSC_COORDINATE;
}

CODLEx_Element_Ship::~CODLEx_Element_Ship()
{
	ODL_SafeRelease(m_pBorderPen);
}
ODL_SHAPE_COORD		CODLEx_Element_Ship::GetCoordinateType()
{
	return m_CoordType;
}
VOID				CODLEx_Element_Ship::SetCoordinateType(ODL_SHAPE_COORD IN coord)
{
	if(m_CoordType == coord)
		return;
	m_CoordType	=coord;
	Invalidate();
}

VOID		CODLEx_Element_Ship::SetBodySize(LONG width,LONG length)
{
	m_BodySize.cx	=length;
	m_BodySize.cy	=width;
	Invalidate();
}

VOID		CODLEx_Element_Ship::SetHeaderLength(LONG IN lLength)
{
	m_lHeaderLength	=lLength;
	Invalidate();
}
VOID		CODLEx_Element_Ship::SetBorderPen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pBorderPen);
	m_pBorderPen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
	Invalidate();
}

BOOL		CODLEx_Element_Ship::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	POINT		center;
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
	pCoord->GetCenter(center);

	//»­´¬-----------------------------------------------------
	m_pBorderPen->Install(hDC);
	POINT	points[5];



	if(m_CoordType == ODLSC_COORDINATE)
	{
		points[0].x		=-m_BodySize.cx/2;
		points[0].y		=-m_BodySize.cy/2;

		points[1].x		=+m_BodySize.cx/2;
		points[1].y		=-m_BodySize.cy/2;

		points[2].x		=+m_BodySize.cx/2+m_lHeaderLength;
		points[2].y		=0;

		points[3].x		=+m_BodySize.cx/2;
		points[3].y		=+m_BodySize.cy/2;

		points[4].x		=-m_BodySize.cx/2;
		points[4].y		=+m_BodySize.cy/2;
		for(LONG i=0;i<5;i++)
		{
			points[i].x	=pCoord->XValueToCoordSpacce(points[i].x);
			points[i].y	=pCoord->YValueToCoordSpacce(points[i].y);
		}
	}
	else
	{
		points[0].x		=center.x-m_BodySize.cx/2;
		points[0].y		=center.y-m_BodySize.cy/2;

		points[1].x		=center.x+m_BodySize.cx/2;
		points[1].y		=center.y-m_BodySize.cy/2;

		points[2].x		=center.x+m_BodySize.cx/2+m_lHeaderLength;
		points[2].y		=center.y;

		points[3].x		=center.x+m_BodySize.cx/2;
		points[3].y		=center.y+m_BodySize.cy/2;

		points[4].x		=center.x-m_BodySize.cx/2;
		points[4].y		=center.y+m_BodySize.cy/2;
	}
	::MoveToEx(hDC,points[0].x,points[0].y,NULL);
	  ::LineTo(hDC,points[1].x,points[1].y);
	  ::LineTo(hDC,points[2].x,points[2].y);
	  ::LineTo(hDC,points[3].x,points[3].y);
	  ::LineTo(hDC,points[4].x,points[4].y);
	  ::LineTo(hDC,points[0].x,points[0].y);
	m_pBorderPen->Uninstall(hDC);
 

	return TRUE;
}
