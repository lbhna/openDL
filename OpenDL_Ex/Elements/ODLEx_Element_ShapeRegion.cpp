#include "stdafx.h"
#include "./ODLEx_Element_ShapeRegion.h"


CODLEx_Element_ShapeRegion::CODLEx_Element_ShapeRegion(CODL_CanvasBase* IN pCanvas):
CODLEx_Element_ShapeBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_SHAPE_REGION;
}
CODLEx_Element_ShapeRegion::~CODLEx_Element_ShapeRegion()
{

}


BOOL		CODLEx_Element_ShapeRegion::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	return FALSE;
}
BOOL		CODLEx_Element_ShapeRegion::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{

	return TRUE;
}
