#include "StdAfx.h"
#include "./ODLEx_Element_CrossLine.h"
#include "./ODLEx_Element_Coordinate.h"
#include "./ODLEx_Element_CurveBase.h"


CODLEx_Element_CrossLine::CODLEx_Element_CrossLine(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_pLinePen			=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(255,255,0));
	m_pTextFont			=pCanvas->GetView()->GetResourceManager()->CreateFont("ËÎÌו",12);
	m_TextBkColor		=RGB(0,50,50);
	m_TextColor			=RGB(0,255,255);
	m_lPosition			=0;
	m_Type				=ODL_ELEMENT_CROSSLINE;
	m_bShow				=FALSE;
	m_ZIndex			=1;
}

CODLEx_Element_CrossLine::~CODLEx_Element_CrossLine(void)
{
	ODL_SafeRelease(m_pLinePen);
	ODL_SafeRelease(m_pTextFont);

}
VOID		CODLEx_Element_CrossLine::SetLineParameter(UINT IN nPenStyle,UINT IN nPenWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen =GetCanvas()->GetView()->GetResourceManager()->CreatePen(nPenStyle,nPenWidth,clr);
	Invalidate();
}
VOID		CODLEx_Element_CrossLine::SetTextParameter(LPCSTR IN pFontName,UINT IN nFontSize,COLORREF IN FontColor,COLORREF IN BkColor)
{
	ODL_SafeRelease(m_pTextFont);
	m_TextColor		=FontColor;
	m_TextBkColor	=BkColor;
	m_pTextFont		=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,nFontSize);
	Invalidate();
}

BOOL		CODLEx_Element_CrossLine::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	CODL_ElementBase*	pSelect =GetCanvas()->GetSelected();
	if(pSelect == NULL)
		return FALSE;
	if(pSelect->GetType() != ODL_ELEMENT_CURVE)
		return FALSE;
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return FALSE;
	CODLEx_Element_CurveBase*	pCurve	=(CODLEx_Element_CurveBase*)pSelect;
	CODLEx_CurveData*			pData	=pCurve->GetDataByXIndicate(m_lPosition);
	if(pData == NULL)
	{
		m_lPosition =0;
		return FALSE;
	}

	//-------------------------------------------------------------------------

	m_pLinePen->Install(hDC);


	CODL_Vector2f vScale =*pCurve->GetScale();
	LONG x	= pCoord->XValueToCoordSpacce(pData->x*vScale.x);
	LONG y	= pCoord->YValueToCoordSpacce(pData->y*vScale.y);

	MoveToEx(hDC,pPaintRect->left,y,NULL);
	LineTo(hDC,pPaintRect->right,y);

	MoveToEx(hDC,x,pPaintRect->top,NULL);
	LineTo(hDC,x,pPaintRect->bottom);
	m_pLinePen->Uninstall(hDC);

	//-----------------------------------------------------
	m_pTextFont->Install(hDC);
	LPTEXTMETRIC pMetric	=m_pTextFont->GetTextMetrics();
	COLORREF oldTextColor	=SetTextColor(hDC,m_TextColor);
	COLORREF oldBkColor	=SetBkColor(hDC,m_TextBkColor);
	int oldBkMode			=SetBkMode(hDC,OPAQUE);
	CHAR fmt[64],str[64];
	RECT	rect;
	sprintf(fmt,"%%.%df",pCoord->GetYGraduationIndicatePrecision());
	sprintf(str,fmt,pData->y);

	rect.left	=pPaintRect->left;
	rect.top	=y+1;
	rect.right	=rect.left + pMetric->tmMaxCharWidth*strlen(str);
	rect.bottom =rect.top  + pMetric->tmHeight;
	DrawText(hDC,str,strlen(str),&rect,DT_LEFT|DT_TOP);
	
	sprintf(fmt,"%%.%df",pCoord->GetXGraduationIndicatePrecision());
	sprintf(str,fmt,pData->x);
	rect.left	=x - (pMetric->tmMaxCharWidth*strlen(str))/2;
	rect.bottom =pPaintRect->bottom;
	rect.top	=pPaintRect->bottom-pMetric->tmHeight;
	rect.right	=x + (pMetric->tmMaxCharWidth*strlen(str))/2;
	DrawText(hDC,str,strlen(str),&rect,DT_CENTER|TA_TOP);




	SetTextColor(hDC,oldTextColor);
	SetBkColor(hDC,oldBkColor);
	SetBkMode(hDC,oldBkMode);
	m_pTextFont->Uninstall(hDC);

	return TRUE;
}
BOOL		CODLEx_Element_CrossLine::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(!IsShow())
		return FALSE;
	CODL_ElementBase*	pSelect =GetCanvas()->GetSelected();
	if(pSelect == NULL)
		return FALSE;
	if(pSelect->GetType() != ODL_ELEMENT_CURVE)
		return FALSE;

	switch(message)
	{
	case WM_KEYDOWN:
		{
			if(OnKeyDown(wParam,lParam))
				return TRUE;
		}
		break;
	}

	return FALSE;
}
BOOL		CODLEx_Element_CrossLine::OnKeyDown(WPARAM wp,LPARAM lp)
{
	switch(wp)
	{
	case VK_RIGHT:
	case 'L':
	case 'l':
		{
			CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
			if(pCoord != NULL)
			{
				m_lPosition	 ++;
				if(m_lPosition > pCoord->GetXMaxGraduationIndicate())
				{
					GetCanvas()->MoveLeft(-1);
				}
				Invalidate(TRUE);
				return TRUE;
			}

		}
		break;
	case VK_LEFT:
	case 'j':
	case 'J':
		{
			CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
			if(pCoord != NULL)
			{
				m_lPosition	 --;
				if(m_lPosition < pCoord->GetXMinGraduationIndicate())
				{
					GetCanvas()->MoveLeft(1);
				}
				Invalidate(TRUE);
				return TRUE;
			}

		}
		break;
	}
	return FALSE;
}

VOID		CODLEx_Element_CrossLine::MoveLeft(LONG IN lCount)
{
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return;

	m_lPosition	 += lCount;

	if(m_lPosition < pCoord->GetXMinGraduationIndicate())
		m_lPosition = pCoord->GetXMinGraduationIndicate();
	if(m_lPosition > pCoord->GetXMaxGraduationIndicate())
		m_lPosition =pCoord->GetXMaxGraduationIndicate();
	Invalidate();
}
VOID		CODLEx_Element_CrossLine::SetLinePen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen			=GetCanvas()->GetView()->GetResourceManager()->CreatePen(lp);
	Invalidate();
}
VOID		CODLEx_Element_CrossLine::SetLineFont(LOGFONT* IN lf)
{
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont			=GetCanvas()->GetView()->GetResourceManager()->CreateFont(lf);
	Invalidate();

}
VOID		CODLEx_Element_CrossLine::SetLineTextColor(COLORREF IN clr)
{
	m_TextColor			=clr;
	Invalidate();

}
VOID		CODLEx_Element_CrossLine::SetLineTextBkColor(COLORREF IN clr)
{
	m_TextBkColor		=clr;
	Invalidate();
}




