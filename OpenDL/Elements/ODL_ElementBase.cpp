#include "StdAfx.h"
#include ".\odl_elementbase.h"
#include "../Canvas/ODL_CanvasBase.h"
#include "../View/ODL_View.h"
#include "../Base/ODL_Vector2f.h"

CODL_ElementBase::CODL_ElementBase(CODL_CanvasBase* IN pCanvas)
{
	m_Type				=ODL_ELEMENT_BASE;
	m_dwID				=0;
	m_pCanvas			=pCanvas;
	m_bShow				=TRUE;
	ZeroMemory(&m_CurPaintRect,sizeof(m_CurPaintRect));
	m_bSelected			=FALSE;
	m_hMenu				=NULL;
	m_ZIndex			=0;
	m_bInvalidate		=TRUE;
	m_bEnableSelect		=TRUE;
	m_pListener			=NULL;
}

CODL_ElementBase::~CODL_ElementBase(void)
{
}
VOID		CODL_ElementBase::EnableSelect(BOOL IN bEnable)
{
	if(m_bEnableSelect == bEnable)
		return;
	m_bEnableSelect=bEnable;
	if(!m_bEnableSelect)
		m_bSelected=FALSE;
	Invalidate();
}

BOOL		CODL_ElementBase::Draw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(!m_bShow)
		return FALSE;
	m_CurPaintRect	=*pPaintRect; 
	m_bInvalidate	=FALSE;
	return OnDraw(hDC,pPaintRect);
}
BOOL		CODL_ElementBase::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	return TRUE;
}
VOID		CODL_ElementBase::Show(BOOL IN bShow)
{
	m_bShow		=bShow;

	Invalidate();
}
VOID		CODL_ElementBase::Invalidate(BOOL IN bFlushView)
{
	m_bInvalidate		=TRUE;
	GetCanvas()->Invalidate(FALSE);
	if(bFlushView)
		GetCanvas()->GetView()->Invalidate();

}
VOID		CODL_ElementBase::SetSelected(BOOL IN bSelect)
{
	if(!IsEnableSelect())
		return;
	m_bSelected		=bSelect;
	Invalidate(TRUE);

	if(m_pListener != NULL)
	{
		if(m_bSelected)
			m_pListener->OnElement_Selected(this);
		else
			m_pListener->OnElement_Unselected(this);
	}
}
BOOL			CODL_ElementBase::PtInLine(POINT IN pt,POINT IN LineStart,POINT IN LineEnd)
{
	CODL_Vector2f	vPt(pt.x,pt.y);
	CODL_Vector2f	vStart(LineStart.x,LineStart.y),vEnd(LineEnd.x,LineEnd.y);

	CODL_Vector2f	vLen =vStart-vEnd;
	CODL_Vector2f	vLen2=vStart-vPt;
	CODL_Vector2f	vLen3=vEnd-vPt;


	FLOAT	L1=vLen.Length();
	FLOAT	L2=vLen2.Length();
	FLOAT	L3=vLen3.Length();
	FLOAT	L4=fabs(L1 -(L2+L3));

	if( L4 < 0.1f)
	{
		return TRUE;
	}
	return FALSE;

}
VOID			CODL_ElementBase::SetRButtonMenu(HMENU IN hMenu)
{
	m_hMenu		=hMenu;
}
BOOL			CODL_ElementBase::PopupMenu()
{
	if(m_hMenu == NULL)
		return FALSE;
	POINT	point;
	GetCursorPos(&point);
	TrackPopupMenu(m_hMenu,TPM_LEFTALIGN,point.x,point.y,0,GetCanvas()->GetView()->GetDeviceWnd(),NULL);
	return TRUE;
}
VOID			CODL_ElementBase::SetZIndex(LONG IN lIndex)
{
	m_ZIndex=lIndex;
	GetCanvas()->SetOrderFlag(TRUE);
}

VOID				CODL_ElementBase::SetListener(CODL_Listener* IN pListener)
{
	m_pListener		=pListener;
}
BOOL		CODL_ElementBase::IsControlSwitchKeyPressed()
{
	if( ( GetKeyState(VK_LCONTROL) & 0xff00 ) != 0 || ( GetKeyState(VK_RCONTROL) & 0xff00 ) != 0 )
		return TRUE;
	return FALSE;
}
