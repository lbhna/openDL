#include "StdAfx.h"
#include ".\odl_overlayelementbase.h"

#pragma  comment(lib,"MSIMG32.LIB")


CODL_OverlayElementBase::CODL_OverlayElementBase(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type			=ODL_ELEMENT_OVERLAY_BASE;
	m_hBitmap		=NULL;
	m_hBitmapDC		=NULL;
	ZeroMemory(&m_BitmapRect,sizeof(m_BitmapRect));
	m_Alpha			=255;

}

CODL_OverlayElementBase::~CODL_OverlayElementBase(void)
{
	ODL_SafeDeleteGDIObj(m_hBitmap);
	if(m_hBitmapDC != NULL)
		DeleteDC(m_hBitmapDC);

}
VOID		CODL_OverlayElementBase::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	boundRect	=*pPaintRect;
}


BOOL		CODL_OverlayElementBase::Draw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(!IsShow())
		return FALSE;

	if(m_Alpha >= 255 )
	{//完全不透明，不需要做透明处理
		return OnDraw(hDC,pPaintRect);
	}
	else
	{//需要透明处理
		if(!ResetAlphaBitmap(hDC,pPaintRect))
			return FALSE;

		if(!BitBlt(m_hBitmapDC,
			0,0,
			m_BitmapRect.right-m_BitmapRect.left,
			m_BitmapRect.bottom-m_BitmapRect.top,
			hDC,
			m_BitmapRect.left,
			m_BitmapRect.top,
			SRCCOPY))
			return FALSE;

		POINT	oldWndOrg;
		SetWindowOrgEx(m_hBitmapDC,m_BitmapRect.left,m_BitmapRect.top,&oldWndOrg);
		SetBkMode(m_hBitmapDC,TRANSPARENT);
	
		if(!OnDraw(m_hBitmapDC,pPaintRect))
		{
			SetWindowOrgEx(m_hBitmapDC,oldWndOrg.x,oldWndOrg.y,NULL);
			return FALSE;
		}
		SetWindowOrgEx(m_hBitmapDC,oldWndOrg.x,oldWndOrg.y,NULL);

		BLENDFUNCTION	bf;
		bf.BlendOp		= 0;
		bf.AlphaFormat	= 0;
		bf.BlendFlags	= 0;
		bf.SourceConstantAlpha	= 255 - (255-m_Alpha)%256;

		return AlphaBlend(hDC,
			m_BitmapRect.left,
			m_BitmapRect.top,
			m_BitmapRect.right-m_BitmapRect.left,
			m_BitmapRect.bottom-m_BitmapRect.top,
			m_hBitmapDC,
			0,
			0,
			m_BitmapRect.right-m_BitmapRect.left,
			m_BitmapRect.bottom-m_BitmapRect.top,
			bf);
	}

	return FALSE;
}

BOOL		CODL_OverlayElementBase::ResetAlphaBitmap(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT boundRect;
	GetElementBound(hDC,pPaintRect,boundRect);

	if( boundRect.left != m_BitmapRect.left||
		boundRect.right!= m_BitmapRect.right||
		boundRect.bottom!=m_BitmapRect.bottom||
		boundRect.top!=m_BitmapRect.top)
	{
		ODL_SafeDeleteGDIObj(m_hBitmap);
		if(m_hBitmapDC != NULL)
			DeleteDC(m_hBitmapDC);

		m_hBitmapDC	=CreateCompatibleDC(hDC);
		if(m_hBitmapDC == NULL)
			return FALSE;

		m_BitmapRect		=boundRect;
		m_hBitmap	=CreateCompatibleBitmap(hDC,
			m_BitmapRect.right-m_BitmapRect.left,
			m_BitmapRect.bottom-m_BitmapRect.top);
		if(m_hBitmap == NULL)
			return FALSE;

		SelectObject(m_hBitmapDC,m_hBitmap);
		m_bInvalidate		=TRUE;
		return TRUE;
	}
	return TRUE;
}
