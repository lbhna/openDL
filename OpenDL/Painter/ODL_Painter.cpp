#include "StdAfx.h"
#include ".\odl_painter.h"


CODL_Painter::CODL_Painter(CODL_ViewBase* IN pView)
{
	m_PainterType			=PAINTER_BASE;
	m_pView					=pView;
	m_hDeviceWnd			=0;
	m_PaintRect.left		=0;
	m_PaintRect.right		=0;
	m_PaintRect.top			=0;
	m_PaintRect.bottom		=0;
	m_rectEdgeSpace.left	=0;
	m_rectEdgeSpace.right	=0;
	m_rectEdgeSpace.top		=0;
	m_rectEdgeSpace.bottom	=0;
}

CODL_Painter::~CODL_Painter(void)
{

}


