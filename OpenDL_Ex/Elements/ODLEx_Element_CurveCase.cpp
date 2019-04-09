#include "stdafx.h"
#include ".\odlex_element_curvecase.h"

CODLEx_Element_CurveCase::CODLEx_Element_CurveCase(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_CURVECASE;
	m_Pos.x				=0;
	m_Pos.y				=0;
	m_Size.cx			=0;
	m_Size.cy			=0;
	m_pCurve			=NULL;
	m_pFont				=pCanvas->GetView()->GetResourceManager()->CreateFont("ËÎÌו",12);
	m_TextColor			=RGB(255,255,200);
	m_SelectTextColor	=RGB(55,255,255);

	m_LineLength		=30;
	m_BoxRect.left		=0;
	m_BoxRect.top		=0;
	m_BoxRect.right		=0;
	m_BoxRect.bottom	=0;
	m_TextRect.left		=0;
	m_TextRect.top		=0;
	m_TextRect.right	=0;
	m_TextRect.bottom	=0;

	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(200,200,200),0);
	m_pSelectBtnBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(55,55,200),0);
	m_pBlackFramePen	=pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(255,255,255));
	m_pWhiteFramePen	=pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(0,0,0));

	m_dwXPrecision		=1;
	m_dwYPrecision		=1;
	m_bShowLastDataText	=TRUE;
}

CODLEx_Element_CurveCase::~CODLEx_Element_CurveCase(void)
{
	ODL_SafeRelease(m_pCurve);
	ODL_SafeRelease(m_pFont);

	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pSelectBtnBrush);
	ODL_SafeRelease(m_pBlackFramePen);
	ODL_SafeRelease(m_pWhiteFramePen);

}
VOID		CODLEx_Element_CurveCase::Init(HDC IN hDC,CODLEx_Element_CurveBase* IN pCurve)
{
	ODL_SafeRelease(m_pCurve);
	m_pCurve	=pCurve;
	if(m_pCurve == NULL)
		return;
	
	m_pCurve->AddRef();

	CHAR format[64],str[64];

	if(m_bShowLastDataText && m_pCurve->GetDataCount()>0)
	{
		sprintf(format,"%%s (x:%%.%df,y:%%.%df)",m_dwXPrecision,m_dwYPrecision);
		sprintf(str,format,m_pCurve->GetName(),m_pCurve->GetLastData()->x,m_pCurve->GetLastData()->y);
	}
	else
	{
		sprintf(str,"%s",m_pCurve->GetName());
	}
	m_pFont->Install(hDC);
	m_Size.cx	=m_pFont->GetTextMetrics()->tmHeight +2+ m_LineLength +2+ strlen(str)*(m_pFont->GetTextMetrics()->tmAveCharWidth);
	m_Size.cy	=m_pFont->GetTextMetrics()->tmHeight;
	m_pFont->Uninstall(hDC);

}
VOID		CODLEx_Element_CurveCase::SetCaseLineLength(LONG IN lLen)
{
	m_LineLength =lLen;
	Invalidate();
}

VOID		CODLEx_Element_CurveCase::SetFont(LPCSTR IN pFontName,UINT IN uFontSize)
{
	ODL_SafeRelease(m_pFont);
	m_pFont				=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,uFontSize);
	Invalidate();
}
VOID		CODLEx_Element_CurveCase::SetColor(COLORREF IN normalColor,COLORREF IN selectedColor)
{
	m_TextColor			=normalColor;
	m_SelectTextColor	=selectedColor;
	Invalidate();
}
VOID		CODLEx_Element_CurveCase::SetPrecision(DWORD IN dwXPrecision,DWORD IN dwYPrecision)
{
	m_dwXPrecision		=dwXPrecision;
	m_dwYPrecision		=dwYPrecision;
	Invalidate();
}

BOOL		CODLEx_Element_CurveCase::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_pCurve == NULL)
		return FALSE;
	m_pFont->Install(hDC);
	
	RECT box_rect;
	box_rect.left	=m_Pos.x;
	box_rect.top	=m_Pos.y;
	box_rect.right	=m_Pos.x + m_pFont->GetTextMetrics()->tmHeight;
	box_rect.bottom =m_Pos.y + m_pFont->GetTextMetrics()->tmHeight;
	m_BoxRect		=box_rect;

	m_pBlackFramePen->Install(hDC);
	MoveToEx(hDC,box_rect.right,box_rect.top,NULL);
	LineTo(hDC,box_rect.right,box_rect.bottom);
	LineTo(hDC,box_rect.left,box_rect.bottom);
	m_pBlackFramePen->Uninstall(hDC);

	FillRect(hDC,&box_rect,m_pBkBrush->GetBrush());
	m_pWhiteFramePen->Install(hDC);
	MoveToEx(hDC,box_rect.left,box_rect.bottom,NULL);
	LineTo(hDC,box_rect.left,box_rect.top);
	LineTo(hDC,box_rect.right,box_rect.top);
	m_pWhiteFramePen->Uninstall(hDC);


	if(m_pCurve->IsShow())
	{
		InflateRect(&box_rect,-(box_rect.right-box_rect.left)/4,-(box_rect.bottom-box_rect.top)/4);
		OffsetRect(&box_rect,1,1);
		FillRect(hDC,&box_rect,m_pSelectBtnBrush->GetBrush());
	}

	CHAR format[64],str[64];
	if(m_bShowLastDataText && m_pCurve->GetDataCount()>0)
	{
		sprintf(format,"%%s (x:%%.%df,y:%%.%df)",m_dwXPrecision,m_dwYPrecision);
		sprintf(str,format,m_pCurve->GetName(),m_pCurve->GetLastData()->x,m_pCurve->GetLastData()->y);
	}
	else
	{
		sprintf(str,"%s",m_pCurve->GetName());
	}

	POINT		start;
	start.x		=m_BoxRect.right + 2;
	start.y		=m_BoxRect.top  + (m_BoxRect.bottom-m_BoxRect.top)/2;
	
	m_pCurve->GetLinePen()->Install(hDC);
	MoveToEx(hDC,start.x,start.y,NULL);
	LineTo(hDC,start.x + m_LineLength,start.y);
	m_pCurve->GetLinePen()->Uninstall(hDC);
	
	
	m_TextRect.left		=m_BoxRect.right + 2 + m_LineLength + 2;
	m_TextRect.top		=m_BoxRect.top;
	m_TextRect.bottom	=m_BoxRect.bottom;
	m_TextRect.right	=m_TextRect.left + strlen(str)*(m_pFont->GetTextMetrics()->tmAveCharWidth);

	m_Size.cx			=m_pFont->GetTextMetrics()->tmHeight +2+ m_LineLength +2+ strlen(str)*(m_pFont->GetTextMetrics()->tmAveCharWidth);
	m_Size.cy			=m_pFont->GetTextMetrics()->tmHeight;

	if(m_pCurve->IsSelected())
		SetTextColor(hDC,m_SelectTextColor);
	else
		SetTextColor(hDC,m_TextColor);
	SetBkMode(hDC,TRANSPARENT);
	DrawText(hDC,(LPCSTR)str,strlen(str),&m_TextRect,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	m_pFont->Uninstall(hDC); 
	return TRUE;
}
BOOL		CODLEx_Element_CurveCase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(PtInRect(&m_BoxRect,*pPoint))
			{
				m_pCurve->Show(!m_pCurve->IsShow());
				Invalidate(TRUE);
				return TRUE;
			}
			if(PtInRect(&m_TextRect,*pPoint))
			{
				if(m_pCurve->IsShow())
				{
					m_pCurve->SetSelected(TRUE);
					GetCanvas()->SetSelected(m_pCurve);
					Invalidate(TRUE);
					return TRUE;

				}
			}


		}
		break;
	
	}

	return FALSE;
}
