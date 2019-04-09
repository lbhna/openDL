#include "stdafx.h"
#include ".\odlex_element_canvastitle.h"

CODLEx_Element_CanvasTitle::CODLEx_Element_CanvasTitle(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_CANVASTITLE;
	m_pBorderPen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(50,200,50));
	m_pBkBrush			=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(0,0,0),0);
	m_pFont				=GetCanvas()->GetView()->GetResourceManager()->CreateFont("黑体",18);
	m_TitleColor		=RGB(50,180,50);
	m_TitleRect.left	=0;
	m_TitleRect.right	=0;
	m_TitleRect.top		=0;
	m_TitleRect.bottom	=0;
	m_ZIndex			=2;
	m_Pos.x				=0;
	m_Pos.y				=0;

	m_bFixHeight		=TRUE;
	m_lTitleHeight		=32;

}

CODLEx_Element_CanvasTitle::~CODLEx_Element_CanvasTitle(void)
{
	ODL_SafeRelease(m_pBorderPen);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pFont);

}
VOID			CODLEx_Element_CanvasTitle::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
}

BOOL			CODLEx_Element_CanvasTitle::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	LONG	h	=m_lTitleHeight;

	m_pFont->Install(hDC);
	if(!m_bFixHeight)
	{
		h =m_pFont->GetTextMetrics()->tmHeight;
		h+=4;
		if(h<m_lTitleHeight)
			h=m_lTitleHeight;
	}


	m_TitleRect.left	=m_Pos.x;
	m_TitleRect.top		=m_Pos.y;
	m_TitleRect.bottom	=pPaintRect->top + h;
	m_TitleRect.right	=pPaintRect->right;

	FillRect(hDC,&m_TitleRect,m_pBkBrush->GetBrush());
	m_pBorderPen->Install(hDC);
	m_pBorderPen->DrawRect(&m_TitleRect);
	m_pBorderPen->Uninstall(hDC);

	SetTextColor(hDC,m_TitleColor);
	SetBkMode(hDC,TRANSPARENT);
	m_pFont->DrawText(&m_TitleRect,GetCanvas()->GetName(),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pFont->Uninstall(hDC);

	return TRUE;
}
VOID			CODLEx_Element_CanvasTitle::SetBorderStyle(UINT IN uStyle,UINT IN uWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pBorderPen);
	m_pBorderPen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(uStyle,uWidth,clr);
	Invalidate();
}
VOID			CODLEx_Element_CanvasTitle::SetBackgroundStyle(UINT IN uStyle,UINT IN uHatch,COLORREF IN clr)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush			=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(uStyle,clr,uHatch);
	Invalidate();
}
VOID			CODLEx_Element_CanvasTitle::SetFont(CHAR* pFontName,DWORD IN dwSize,DWORD IN dwWeight)
{
	ODL_SafeRelease(m_pFont);
	m_pFont				=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pFontName,dwSize,dwWeight);
	Invalidate();
}
VOID			CODLEx_Element_CanvasTitle::SetFont(LOGFONT* IN pLf)
{
	ODL_SafeRelease(m_pFont);
	m_pFont				=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pLf);
	Invalidate();
}

VOID			CODLEx_Element_CanvasTitle::SetTitleColor(COLORREF IN clr)
{
	m_TitleColor	=clr;
	Invalidate();
}
VOID			CODLEx_Element_CanvasTitle::SetTitleHeight(LONG IN lHeight,BOOL IN bFixed)//如果bFixed为TRUE，则完全按设定值为高度，如果为FALSE，则高度小于字体高度时自动适应字体
{
	m_lTitleHeight	=lHeight;
	m_bFixHeight	=bFixed;
	Invalidate();
}
LONG			CODLEx_Element_CanvasTitle::GetTitleHeight()
{
	if(m_bFixHeight)
		return m_lTitleHeight;
	return (m_TitleRect.bottom-m_TitleRect.top);
}

const LPLOGPEN		CODLEx_Element_CanvasTitle::GetBorderStyle()
{
	return m_pBorderPen->GetLogPen();
}
const LPLOGBRUSH		CODLEx_Element_CanvasTitle::GetBackgroundStyle()
{
	return m_pBkBrush->GetLogBrush();
}

const LPLOGFONT		CODLEx_Element_CanvasTitle::GetFont()
{
	return m_pFont->GetLogFont();
}
COLORREF		CODLEx_Element_CanvasTitle::GetTitleColor()
{
	return m_TitleColor;
}












