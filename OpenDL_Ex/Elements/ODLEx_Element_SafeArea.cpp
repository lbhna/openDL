#include "StdAfx.h"
#include "ODLEx_Element_SafeArea.h"
#include "ODLEx_Element_Coordinate.h"

CODLEx_Element_SafeArea::CODLEx_Element_SafeArea(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type					=ODL_ELEMENT_SAFEAREA;
		
	m_fXMinValue			=0.0f;
	m_bShowXDownLimitLine	=FALSE;
	
	m_fXMaxValue			=0.0f;
	m_bShowXUpLimitLine		=FALSE;
	
	m_fYMinVlue				=0.0f;
	m_bShowYDownLimitLine	=FALSE;
	
	m_fYMaxValue			=0.0f;
	m_bShowYUpLimitLine		=FALSE;
	
	m_pLinePen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(255,100,0));
	m_pFont			=pCanvas->GetView()->GetResourceManager()->CreateFont("ËÎÌו",14);	
	m_TextColor		=RGB(255,0,255);
	m_TextBkColor	=RGB(0,50,50);
	m_bShowText		=TRUE;
	
}
CODLEx_Element_SafeArea::~CODLEx_Element_SafeArea(void)
{
	ODL_SafeRelease(m_pLinePen);
	ODL_SafeRelease(m_pFont);
}
VOID			CODLEx_Element_SafeArea::SetXMinValue(FLOAT IN fValue)
{
	m_fXMinValue	=fValue;
	Invalidate();	
}
VOID			CODLEx_Element_SafeArea::ShowXDownlimitLine(BOOL IN bShow)
{
	m_bShowXDownLimitLine =bShow;
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetXMaxValue(FLOAT IN fValue)
{
	m_fXMaxValue	=fValue;
	Invalidate();	
}
VOID			CODLEx_Element_SafeArea::ShowXUplimitLine(BOOL IN bShow)
{
	m_bShowXUpLimitLine		=bShow;
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetYMinValue(FLOAT IN fValue)
{
	m_fYMinVlue		=fValue;
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::ShowYDownlimitLine(BOOL IN bShow)
{	
	m_bShowYDownLimitLine =bShow;
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetYMaxValue(FLOAT IN fValue)
{
	m_fYMaxValue	=fValue;
	Invalidate();
}

VOID			CODLEx_Element_SafeArea::ShowYUplimitLine(BOOL IN bShow)
{
	m_bShowYUpLimitLine		=bShow;
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetLineStyle(UINT IN uLineWidth,COLORREF IN clr,UINT IN uLineStyle)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(uLineStyle,uLineWidth,clr);
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetFont(LPCSTR IN pFontName,DWORD IN dwFontSize,COLORREF IN clr,COLORREF IN bkClr)
{
	ODL_SafeRelease(m_pFont);
	m_pFont		=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize);
	m_TextColor	=clr;
	m_TextBkColor=bkClr;
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetLinePen(LOGPEN* IN pPen)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(pPen);
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetTextFont(LOGFONT* IN pLf)
{
	ODL_SafeRelease(m_pFont);
	m_pFont			=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pLf);
	Invalidate();
}
VOID			CODLEx_Element_SafeArea::SetColor(COLORREF IN clr,COLORREF IN bkClr)
{
	m_TextColor	=clr;
	m_TextBkColor=bkClr;
	Invalidate();
}
BOOL			CODLEx_Element_SafeArea::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return FALSE;
	POINT			center;
	pCoord->GetCenter(center);
	
	
	LONG	x,y;
	m_pLinePen->Install(hDC);
	m_pFont->Install(hDC);
	int oldMode =SetBkMode(hDC,OPAQUE);
	SetTextColor(hDC,m_TextColor);
	SetBkColor(hDC,m_TextBkColor);

	LPTEXTMETRIC	pTextMetric	=m_pFont->GetTextMetrics();
	RECT			textRect;
	CHAR			str[32];
	if(m_bShowXDownLimitLine)
	{
		x	= pCoord->XValueToCoordSpacce( m_fXMinValue);
		
		if(x > pPaintRect->left && x< pPaintRect->right)
		{
			SetBkMode(hDC,TRANSPARENT);
			MoveToEx(hDC,x,pPaintRect->top,NULL);
			LineTo(hDC,x,pPaintRect->bottom);
			SetBkMode(hDC,OPAQUE);

			if(m_bShowText)
			{
				sprintf(str,"%.2f",m_fXMinValue);
				textRect.left  =x+1;
				textRect.top	=pPaintRect->top;
				textRect.bottom =textRect.top + pTextMetric->tmHeight;
				textRect.right	=textRect.left + pTextMetric->tmMaxCharWidth*strlen(str);
				DrawText(hDC,str,strlen(str),&textRect,DT_LEFT|DT_VCENTER);
			}
		}
	}
	if(m_bShowXUpLimitLine)
	{
		x	= pCoord->XValueToCoordSpacce( m_fXMaxValue);
		if(x > pPaintRect->left && x< pPaintRect->right)
		{
			SetBkMode(hDC,TRANSPARENT);
			MoveToEx(hDC,x,pPaintRect->top,NULL);
			LineTo(hDC,x,pPaintRect->bottom);
			SetBkMode(hDC,OPAQUE);
			if(m_bShowText)
			{
				sprintf(str,"%.2f",m_fXMaxValue);
				textRect.left  =x+1;
				textRect.top	=pPaintRect->top;
				textRect.bottom =textRect.top + pTextMetric->tmHeight;
				textRect.right	=textRect.left + pTextMetric->tmMaxCharWidth*strlen(str);
				DrawText(hDC,str,strlen(str),&textRect,DT_LEFT|DT_VCENTER);
			}
		}
	}

	if(m_bShowYDownLimitLine)
	{
		y	= pCoord->YValueToCoordSpacce( m_fYMinVlue);
		if(y>0 && y<pPaintRect->bottom && y> pPaintRect->top)
		{
			SetBkMode(hDC,TRANSPARENT);
			MoveToEx(hDC,pPaintRect->left,y,NULL);
			LineTo(hDC,pPaintRect->right,y);
			SetBkMode(hDC,OPAQUE);

			if(m_bShowText)
			{
				sprintf(str,"%.2f",m_fYMinVlue);
				textRect.right  =pPaintRect->right;
				textRect.top	=y+1;
				textRect.bottom =textRect.top + pTextMetric->tmHeight;
				textRect.left	=textRect.right - pTextMetric->tmMaxCharWidth*strlen(str);
				DrawText(hDC,str,strlen(str),&textRect,DT_RIGHT|DT_VCENTER);
			}
			
		}
	}
	if(m_bShowYUpLimitLine)
	{
		y	= pCoord->YValueToCoordSpacce( m_fYMaxValue);

		if(y>0 && y<pPaintRect->bottom && y> pPaintRect->top)
		{
			SetBkMode(hDC,TRANSPARENT);
			MoveToEx(hDC,pPaintRect->left,y,NULL);
			LineTo(hDC,pPaintRect->right,y);
			SetBkMode(hDC,OPAQUE);
	
			if(m_bShowText)
			{
				sprintf(str,"%.2f",m_fYMaxValue);
				textRect.right  =pPaintRect->right;
				textRect.top	=y+1;
				textRect.bottom =textRect.top + pTextMetric->tmHeight;
				textRect.left	=textRect.right - pTextMetric->tmMaxCharWidth*strlen(str);
				DrawText(hDC,str,strlen(str),&textRect,DT_RIGHT|DT_VCENTER);
			}
		}
	}


	SetBkMode(hDC,oldMode);
	m_pFont->Uninstall(hDC);
	m_pLinePen->Uninstall(hDC);
	return TRUE;
}
