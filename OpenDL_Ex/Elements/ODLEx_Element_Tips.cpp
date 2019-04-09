#include "stdafx.h"
#include ".\odlex_element_tips.h"

CODLEx_Element_Tips::CODLEx_Element_Tips(CODL_CanvasBase* IN pCanvas)
:CODL_ElementBase(pCanvas)
{
	m_Type			=ODL_ELEMENT_TIPS;

	m_Pos.x			=0;
	m_Pos.y			=0;
	m_pText			=NULL;

	m_pBorderPen	=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(55,55,55));
	m_pTextFont		=pCanvas->GetView()->GetResourceManager()->CreateFont("ËÎÌו",12);
	m_TextColor		=RGB(25,25,55);
	m_pBkBrush		=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(225,225,155),0);
	

	m_bShow			=FALSE;
	
}

CODLEx_Element_Tips::~CODLEx_Element_Tips(void)
{
	ODL_SafeDeleteArray(m_pText);
	ODL_SafeRelease(m_pBorderPen);
	ODL_SafeRelease(m_pTextFont);
	ODL_SafeRelease(m_pBkBrush);
}
VOID				CODLEx_Element_Tips::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();

}
VOID				CODLEx_Element_Tips::SetText(LPCSTR IN pText)
{
	StringSet(m_pText ,pText);
	Invalidate();
}

VOID				CODLEx_Element_Tips::SetTextColor(COLORREF IN clr)
{
	m_TextColor		=clr;
	Invalidate();
}
VOID				CODLEx_Element_Tips::SetTextFont(LPCSTR IN pFontName,DWORD IN dwFontSize)
{
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize);
	Invalidate();
}
VOID				CODLEx_Element_Tips::SetBorderStyle(UINT IN uPenStyle,UINT IN uWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pBorderPen);
	m_pBorderPen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(uPenStyle,uWidth,clr);
	Invalidate();
}

VOID				CODLEx_Element_Tips::SetBackgroundStyle(UINT IN uBrushStyle,COLORREF IN clr)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush		=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(uBrushStyle,clr,0);
	Invalidate();
}

BOOL				CODLEx_Element_Tips::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rect,text_rect;
	m_pTextFont->Install(hDC);
	::SetTextColor(hDC,m_TextColor);
	::SetBkMode(hDC,TRANSPARENT);

	::DrawText(hDC,m_pText,strlen(m_pText),&text_rect,DT_CALCRECT);
	rect.left	=m_Pos.x ;
	rect.top	=m_Pos.y ;
	rect.right	=m_Pos.x + (text_rect.right-text_rect.left);
	rect.bottom	=m_Pos.y + (text_rect.bottom-text_rect.top);

	InflateRect(&rect,3+m_pBorderPen->GetLogPen()->lopnWidth.x,3+m_pBorderPen->GetLogPen()->lopnWidth.x);
	if(rect.right > pPaintRect->right)
		OffsetRect(&rect,pPaintRect->right-rect.right,0);
	if(rect.left < pPaintRect->left)
		OffsetRect(&rect,pPaintRect->left-rect.left,0);


	FillRect(hDC,&rect,m_pBkBrush->GetBrush());
	m_pBorderPen->Install(hDC);
	MoveToEx(hDC,rect.left,rect.bottom,NULL);
	LineTo(hDC,rect.right,rect.bottom);
	LineTo(hDC,rect.right,rect.top);
	m_pBorderPen->Uninstall(hDC);
	
	InflateRect(&rect,-3,-3);
	::DrawText(hDC,m_pText,strlen(m_pText),&rect,DT_CENTER|DT_VCENTER);
	m_pTextFont->Uninstall(hDC);

	return TRUE;
}

