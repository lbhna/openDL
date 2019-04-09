#include "StdAfx.h"
#include ".\odl_pen.h"

CODL_Pen::CODL_Pen(LOGPEN* IN pLogPen)
{
	m_hPen			=CreatePenIndirect(pLogPen);
	m_Pen			=*pLogPen;
	m_hInstallDC	=NULL;
}
CODL_Pen::CODL_Pen(UINT IN nPenStyle,UINT IN nWidth,COLORREF IN PenColor)
{
	m_Pen.lopnColor		=PenColor;
	m_Pen.lopnStyle		=nPenStyle;
	m_Pen.lopnWidth.x	=nWidth;
	m_Pen.lopnWidth.y	=0;
	m_hPen	=CreatePenIndirect(&m_Pen);
	m_hInstallDC		=NULL;
}
CODL_Pen::~CODL_Pen(void)
{
	ODL_SafeDeleteGDIObj(m_hPen);
}
VOID		CODL_Pen::Update(LOGPEN* IN pLogPen)
{
	ODL_SafeDeleteGDIObj(m_hPen);
	m_hPen			=CreatePenIndirect(pLogPen);
	m_Pen			=*pLogPen;
}

BOOL		CODL_Pen::MoveTo(LONG IN x,LONG IN y)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::MoveToEx(m_hInstallDC,x,y,NULL);
}
BOOL		CODL_Pen::LineTo(LONG IN x,LONG IN y)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::LineTo(m_hInstallDC,x,y);
}
BOOL		CODL_Pen::LineTo(HDC IN hDC,LONG IN x,LONG IN y)
{
	HDC		hInstallDC =m_hInstallDC;
	Install(hDC);
	::LineTo(hDC,x,y);
	Uninstall(hDC);
	m_hInstallDC		=hInstallDC;
	return TRUE;
}

BOOL		CODL_Pen::DrawRect(RECT* IN pRect)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	BOOL bRet =TRUE;
	bRet =bRet && ::MoveToEx(m_hInstallDC,pRect->left,pRect->top,NULL);
	bRet =bRet && ::LineTo(m_hInstallDC,pRect->right,pRect->top);
	bRet =bRet && ::LineTo(m_hInstallDC,pRect->right,pRect->bottom);
	bRet =bRet && ::LineTo(m_hInstallDC,pRect->left,pRect->bottom);
	bRet =bRet && ::LineTo(m_hInstallDC,pRect->left,pRect->top);
	
	return bRet;
}
BOOL		CODL_Pen::DrawSquare(POINT* IN center,LONG IN cx,LONG IN cy)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	POINT	pt;
	pt.x	=center->x-cx/2;
	pt.y	=center->y-cy/2;


	LONG	y=0;
	while(y<cy)
	{
		::MoveToEx(m_hInstallDC,pt.x,pt.y+y,NULL);
		::LineTo(m_hInstallDC,pt.x+cx,pt.y+y);
		y+=m_Pen.lopnWidth.x;
	}

	return TRUE;
}
