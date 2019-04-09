#include "stdafx.h"
#include "./ODLEx_Element_ShapeTriangle.h"



CODLEx_Element_ShapeTriangle::CODLEx_Element_ShapeTriangle(CODL_CanvasBase* IN pCanvas):
CODLEx_Element_ShapeBase(pCanvas)
{
	m_Type			=ODL_ELEMENT_SHAPE_TRIANGLE;
}
CODLEx_Element_ShapeTriangle::~CODLEx_Element_ShapeTriangle()
{

}
BOOL		CODLEx_Element_ShapeTriangle::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	return FALSE;
}
BOOL		CODLEx_Element_ShapeTriangle::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	return TRUE;
}
