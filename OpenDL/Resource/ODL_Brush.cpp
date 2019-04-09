#include "StdAfx.h"
#include ".\odl_brush.h"

CODL_Brush::CODL_Brush(LOGBRUSH* IN pLogBrush)
{
	m_hBrush	=CreateBrushIndirect(pLogBrush);
	m_Brush		=*pLogBrush;
	m_hInstallDC=NULL;
}
CODL_Brush::CODL_Brush(UINT IN lbStyle,COLORREF IN lbColor,DWORD IN lbHatch)
{
	m_Brush.lbStyle		=lbStyle;
	m_Brush.lbColor		=lbColor;
	m_Brush.lbHatch		=lbHatch;
	m_hBrush			=CreateBrushIndirect(&m_Brush);
	m_hInstallDC		=NULL;
}

CODL_Brush::~CODL_Brush(void)
{
	ODL_SafeDeleteGDIObj(m_hBrush);
}
VOID			CODL_Brush::Update(LOGBRUSH* IN pLogBrush)
{
	ODL_SafeDeleteGDIObj(m_hBrush);
	m_hBrush	=CreateBrushIndirect(pLogBrush);
	m_Brush		=*pLogBrush;
}

BOOL			CODL_Brush::FillRect(RECT* IN pRect)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::FillRect(m_hInstallDC,pRect,m_hBrush);
}
BOOL			CODL_Brush::FillRgn(HRGN IN hRgn)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::FillRgn(m_hInstallDC,hRgn,m_hBrush);
}
