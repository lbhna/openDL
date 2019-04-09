#include "stdafx.h"
#include "./ODLEx_Element_ShapeBase.h"

CODLEx_Element_ShapeBase::CODLEx_Element_ShapeBase(CODL_CanvasBase* IN pCanvas):
CODL_OverlayElementBase(pCanvas)
{
	m_Type					=ODL_ELEMENT_SHAPEBASE;
	m_Coordinate			=ODLSC_COORDINATE;																					//ÊÇÆÁÄ»×ø±ê¿Õ¼ä

	m_bStroke				=TRUE;																					//ÊÇ·ñÃè±ß
	m_pStrokePen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(0,255,0));		//Ãè±ß»­±Ê
	m_bFill					=FALSE;																					//ÊÇ·ñÌî³ä
	m_pFillBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,255,255),0);;		//Ìî³ä»­Ë¢


	m_ptDragOffset.x		=m_ptDragOffset.y	=0;
	m_bEnableDrag			=FALSE;
	m_bDraging				=FALSE;
	m_bEnableAdjustSize		=FALSE;
	m_bAdjustSizeing		=FALSE;


}
CODLEx_Element_ShapeBase::~CODLEx_Element_ShapeBase()
{
	ODL_SafeRelease(m_pStrokePen);
	ODL_SafeRelease(m_pFillBrush);
}
ODL_SHAPE_COORD		CODLEx_Element_ShapeBase::GetShapeCoordinate()
{
	return m_Coordinate;
}

BOOL				CODLEx_Element_ShapeBase::IsEnableStroke()
{
	return m_bStroke;
}
VOID				CODLEx_Element_ShapeBase::EnableStroke(BOOL IN bEnable)
{
	if(m_bStroke	== bEnable)
		return;
	m_bStroke	=bEnable;
	Invalidate();
}
BOOL				CODLEx_Element_ShapeBase::IsEnableFill()
{
	return m_bFill;
}
VOID				CODLEx_Element_ShapeBase::EnableFill(BOOL IN bEnable)
{
	if(m_bFill	== bEnable)
		return;
	m_bFill	=bEnable;
	Invalidate();
}
VOID				CODLEx_Element_ShapeBase::SetStokePen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pStrokePen);
	m_pStrokePen		=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);	
	Invalidate();
}
VOID				CODLEx_Element_ShapeBase::SetFillBrush(LOGBRUSH* IN lb)
{
	ODL_SafeRelease(m_pFillBrush);
	m_pFillBrush		=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(lb);		//Ìî³ä»­Ë¢
	Invalidate();
}
BOOL		CODLEx_Element_ShapeBase::PtInAdjustSizeButton(POINT* IN pt)
{
	return FALSE;
}
VOID		CODLEx_Element_ShapeBase::EnableAdjustSize(BOOL IN bEnable)
{
	m_bEnableAdjustSize=bEnable;
}
BOOL		CODLEx_Element_ShapeBase::IsEnableAdjustSize()
{
	return m_bEnableAdjustSize;
}
VOID		CODLEx_Element_ShapeBase::EnableDrag(BOOL IN bEnable)
{
	m_bEnableDrag=bEnable;
}
