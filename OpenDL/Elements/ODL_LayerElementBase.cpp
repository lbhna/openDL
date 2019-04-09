#include "stdafx.h"
#include "./ODL_LayerElementBase.h"

CODL_LayerElementBase::CODL_LayerElementBase(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type			=ODL_ELEMENT_LAYER_BASE;
	m_Pos.x			=0;
	m_Pos.y			=0;
	m_Size.cx		=100;
	m_Size.cy		=100;
	m_hBitmap		=NULL;
	m_hBitmapDC		=NULL;
	m_BitmapRect.left=m_BitmapRect.top=m_BitmapRect.right=m_BitmapRect.bottom=0;
	m_bInvalidate	=TRUE;
}
CODL_LayerElementBase::~CODL_LayerElementBase()
{
	ClearChild();
	ODL_SafeDeleteGDIObj(m_hBitmap);
	if(m_hBitmapDC != NULL)
		DeleteDC(m_hBitmapDC);
}
VOID					CODL_LayerElementBase::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate(TRUE);
}
PPOINT					CODL_LayerElementBase::GetPos()
{
	return &m_Pos;
}
VOID					CODL_LayerElementBase::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate(TRUE);
}
PSIZE					CODL_LayerElementBase::GetSize()
{
	return &m_Size;
}
VOID					CODL_LayerElementBase::AddChild(CODL_ElementBase* IN pChild)
{
	m_theChildElements.AddObj(pChild);
}
VOID					CODL_LayerElementBase::DelChild(LONG IN lIndex)
{
	m_theChildElements.DelObj(lIndex);
}
VOID					CODL_LayerElementBase::DelChild(CODL_ElementBase* IN pChild)
{
	m_theChildElements.DelObj(pChild);
}
CODL_ElementBase*		CODL_LayerElementBase::GetChild(LONG IN lIndex)
{
	return (CODL_ElementBase*)m_theChildElements.GetObj(lIndex);
}
LONG					CODL_LayerElementBase::GetChildCount()
{
	return m_theChildElements.GetCount();
}
VOID					CODL_LayerElementBase::ClearChild()
{
	m_theChildElements.Clear();
}
BOOL					CODL_LayerElementBase::Draw(HDC IN hDC,RECT* IN pPaintRect)
{
	m_CurPaintRect.left		=0;
	m_CurPaintRect.top		=0;
	m_CurPaintRect.right	=m_Size.cx;
	m_CurPaintRect.bottom	=m_Size.cy;
	if(IsInvalidate())
	{
		ResetBitmap(hDC);
		SetBkMode(m_hBitmapDC,TRANSPARENT);
		OnDraw(m_hBitmapDC,&m_CurPaintRect);
	}

	m_bInvalidate	=FALSE;
	return BitBlt(hDC,
		m_Pos.x,m_Pos.y,
		m_Size.cx,m_Size.cy,
		m_hBitmapDC,0,0,SRCCOPY);
}
BOOL			CODL_LayerElementBase::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	for(LONG i=0;i<GetChildCount();i++)
	{
		GetChild(i)->Draw(hDC,pPaintRect);
	}
	return TRUE;
}

BOOL					CODL_LayerElementBase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	POINT	pt =*pPoint;
	pt.x -= m_Pos.x;
	pt.y -= m_Pos.y;
	for(LONG i=0;i<GetChildCount();i++)
	{
		if(GetChild(i)->OnWndMsg(message,wParam,lParam,pResult,&pt))
			return TRUE;
	}

	return FALSE;
}
BOOL					CODL_LayerElementBase::IsInvalidate()
{
	if(m_bInvalidate)
		return TRUE;
	for(LONG i=0;i<GetChildCount();i++)
	{
		if(GetChild(i)->IsInvalidate())
			return TRUE;
	}
	return FALSE;
}

BOOL					CODL_LayerElementBase::ResetBitmap(HDC IN hDC)
{
	if( m_CurPaintRect.left		!= m_BitmapRect.left||
		m_CurPaintRect.right	!= m_BitmapRect.right||
		m_CurPaintRect.bottom	!= m_BitmapRect.bottom||
		m_CurPaintRect.top		!= m_BitmapRect.top)
	{
		ODL_SafeDeleteGDIObj(m_hBitmap);
		if(m_hBitmapDC != NULL)
			DeleteDC(m_hBitmapDC);

		m_hBitmapDC	=CreateCompatibleDC(hDC);
		if(m_hBitmapDC == NULL)
			return FALSE;

		m_BitmapRect=m_CurPaintRect;
		m_hBitmap	=CreateCompatibleBitmap(hDC,
			m_BitmapRect.right-m_BitmapRect.left,
			m_BitmapRect.bottom-m_BitmapRect.top);
		if(m_hBitmap == NULL)
			return FALSE;
		SelectObject(m_hBitmapDC,m_hBitmap);
		m_bInvalidate		=TRUE;
	}
	return TRUE;
}


