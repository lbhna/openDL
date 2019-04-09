#include "stdafx.h"
#include "ODLEx_Element_ReportItem.h"
#include "ODLEx_Element_ReportRow.h"
#include "ODLEx_Element_Report.h"




CODLEx_Element_ReportItem::CODLEx_Element_ReportItem(CODLEx_Element_ReportRow*pRow,CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type						=ODL_ELEMENT_REPORT_ITEM;
	m_pReportRow				=pRow;
	m_Pos.x						=0;
	m_Pos.y						=0;
	m_Size.cx					=64;
	m_Size.cy					=16;
	m_pText						=new CHAR[1];
	m_pText[0]					=0;
	m_pBkBrush					=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,255,255),0);
	m_pSelectBkBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(55,55,255),0);
	m_pPushedBkBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(200,200,200),0);
	m_pTextFont					=m_pCanvas->GetView()->GetResourceManager()->CreateFont("ËÎÌו",12);
	m_TextColor					=RGB(0,0,0);
	m_SelectTextColor			=RGB(255,255,255);
	m_Padding.left				=2;		
	m_Padding.top				=1;
	m_Padding.right				=2;
	m_Padding.bottom			=1;	
	m_uTextAlign				=DT_LEFT|DT_VCENTER|DT_SINGLELINE;


	m_bShowBorder				=FALSE;
	m_LightBorderColor			=RGB(255,255,255);
	m_DarkBorderColor			=RGB(125,125,125);
	m_dwBorderSize				=2;
	m_bEnableClicked			=FALSE;
	m_pLightBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,m_dwBorderSize,m_LightBorderColor);
	m_pDarkBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,m_dwBorderSize,m_DarkBorderColor);
	m_bPushed					=FALSE;

	m_bGradientFill				=FALSE;
	for(LONG i=0;i<6;i++)
	{
		m_Vertexs[i].Alpha			=0xff;
		m_Vertexs[i].Red			=0xff;
		m_Vertexs[i].Green			=0xff;
		m_Vertexs[i].Blue			=0xff;
		m_Vertexs[i].x				=0;
		m_Vertexs[i].y				=0;
	}

	m_bAdjustWidth					=FALSE;
	m_bAdjustHeight					=FALSE;
	m_lAdjustOffset					=0;

	m_pImageList					=NULL;
	m_lImageIndex					=-1;
	m_lSelectedImageIndex			=-1;
	m_nImageDrawStyle				=ILD_TRANSPARENT;


}
CODLEx_Element_ReportItem::~CODLEx_Element_ReportItem()
{
	if(m_pListener != NULL)
		m_pListener->OnElement_ItemDeleted(GetReportRow()->GetReport(),this);

	ODL_SafeDeleteArray(m_pText);
	ODL_SafeRelease(m_pImageList);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pSelectBkBrush);
	ODL_SafeRelease(m_pPushedBkBrush);
	ODL_SafeRelease(m_pTextFont);
	ODL_SafeRelease(m_pDarkBorderPen);
	ODL_SafeRelease(m_pLightBorderPen);
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetText(LPCSTR IN pText)
{
	if(pText == NULL)
		return this;
	ODL_SafeDeleteArray(m_pText);
	size_t	len		=strlen(pText);
	m_pText =new CHAR[len+1];
	strcpy(m_pText,pText);
	m_pText[len]=0;
	Invalidate();
	return this;
}
LPCSTR		CODLEx_Element_ReportItem::GetText()
{
	return m_pText;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x				=x;
	m_Pos.y				=y;
	Invalidate();
	return this;
}
POINT*		CODLEx_Element_ReportItem::GetPos()
{
	return &m_Pos;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetWidth(LONG IN cx)
{
	m_Size.cx	=cx;
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetHeight(LONG IN cy)
{
	m_Size.cy	=cy;
	Invalidate();
	return this;
}

SIZE*		CODLEx_Element_ReportItem::GetSize()
{
	return &m_Size;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetBkBrush(LOGBRUSH* IN pBrush)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush	=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(pBrush);
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetBkBrush(UINT IN lbStyle,COLORREF IN lbColor,UINT_PTR IN lbHatch)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush	=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(lbStyle,lbColor,lbHatch);
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetBkBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL || m_pBkBrush == pBrush)
		return this;
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush	=pBrush;
	m_pBkBrush->AddRef();
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetSelectBkBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL || m_pSelectBkBrush == pBrush)
		return this;
	ODL_SafeRelease(m_pSelectBkBrush);
	m_pSelectBkBrush	=pBrush;
	m_pSelectBkBrush->AddRef();
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetPushedBkBrush(CODL_Brush* IN pBrush)
{
	if(pBrush == NULL || m_pPushedBkBrush == pBrush)
		return this;
	ODL_SafeRelease(m_pPushedBkBrush);
	m_pPushedBkBrush	=pBrush;
	m_pPushedBkBrush->AddRef();
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetPushedBkBrush(LOGBRUSH* IN pBrush)
{
	ODL_SafeRelease(m_pPushedBkBrush);
	m_pPushedBkBrush	=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(pBrush);
	Invalidate();
	return this;
}

CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetFont(LPCSTR IN pFontFaceName,UINT IN uFontSize)
{
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont	=m_pCanvas->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontFaceName,uFontSize);
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetFont(LOGFONT* IN lf)
{
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont	=m_pCanvas->GetView()->GetResourceManager()->CreateFont(lf);
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetFont(CODL_Font*	IN pFont)
{
	if(pFont == NULL || m_pTextFont == pFont)
		return this;
	ODL_SafeRelease(m_pTextFont);
	m_pTextFont	=pFont;
	m_pTextFont->AddRef();
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetTextColor(COLORREF IN clr)
{
	if(m_TextColor == clr)
		return this;
	m_TextColor	=clr;
	Invalidate();
	return this;
}
COLORREF	CODLEx_Element_ReportItem::GetTextColor()
{
	return m_TextColor;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetSelectTextColor(COLORREF IN clr)
{
	if(m_SelectTextColor == clr)
		return this;
	m_SelectTextColor	=clr;
	Invalidate();
	return this;
}
COLORREF	CODLEx_Element_ReportItem::GetSelectTextColor()
{
	return m_SelectTextColor;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetTextAlign(UINT IN lAlign)
{
	if(m_uTextAlign == lAlign)
		return this;
	m_uTextAlign	=lAlign;
	Invalidate();
	return this;
}
UINT		CODLEx_Element_ReportItem::GetTextAlign()
{
	return m_uTextAlign;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetTextPadding(LONG IN left,LONG IN top,LONG IN right,LONG IN bottom)
{
	m_Padding.left	=left;
	m_Padding.right	=right;
	m_Padding.top	=top;
	m_Padding.bottom=bottom;
	Invalidate();
	return this;
}
RECT*		CODLEx_Element_ReportItem::GetTextPadding()
{
	return &m_Padding;
}
VOID		CODLEx_Element_ReportItem::GetRect(RECT& OUT rect)
{
	rect.left		=m_Pos.x;
	rect.right		=m_Pos.x + m_Size.cx;
	rect.top		=m_Pos.y;
	rect.bottom		=m_Pos.y + m_Size.cy;
}
BOOL		CODLEx_Element_ReportItem::PtInElement(POINT IN pt)
{
	RECT	rect;
	GetRect(rect);
	return PtInRect(&rect,pt);
}
VOID		CODLEx_Element_ReportItem::SetSelected(BOOL IN bSelect)
{
	if(!IsEnableSelect())
		return;
	m_bSelected		=bSelect;
	Invalidate(TRUE);

	if(m_pListener != NULL)
	{
		if(m_bSelected)
			m_pListener->OnElement_ItemSelected(GetReportRow()->GetReport(),this);
		else
			m_pListener->OnElement_ItemUnselected(GetReportRow()->GetReport(),this);
	}
}



BOOL		CODLEx_Element_ReportItem::DrawBackGround(HDC IN hDC,RECT* IN bkRect)
{
	RECT rect;
	GetRect(rect);
	if(m_bGradientFill)
	{
		::GradientFill(hDC,m_Vertexs,6,NULL,0,GRADIENT_FILL_TRIANGLE); 
	}
	else
	{
		if(m_bPushed)
		{
			m_pPushedBkBrush->Install(hDC);
			m_pPushedBkBrush->FillRect(bkRect);
			m_pPushedBkBrush->Uninstall(hDC);
		}
		else
		{
			if(m_bSelected)
			{
				m_pSelectBkBrush->Install(hDC);
				m_pSelectBkBrush->FillRect(bkRect);
				m_pSelectBkBrush->Uninstall(hDC);
			}
			else
			{
				m_pBkBrush->Install(hDC);
				m_pBkBrush->FillRect(bkRect);
				m_pBkBrush->Uninstall(hDC);
			}
		}
	}

	if(m_bShowBorder)
	{
		rect.bottom--;
		rect.right--;
		if(m_bPushed)
		{
			m_pDarkBorderPen->Install(hDC);
			m_pDarkBorderPen->MoveTo(rect.right,rect.top);
			m_pDarkBorderPen->LineTo(rect.left,rect.top);
			m_pDarkBorderPen->LineTo(rect.left,rect.bottom);
			m_pDarkBorderPen->Uninstall(hDC);

			m_pLightBorderPen->Install(hDC);
			m_pLightBorderPen->MoveTo(rect.left,rect.bottom);
			m_pLightBorderPen->LineTo(rect.right,rect.bottom);
			m_pLightBorderPen->LineTo(rect.right,rect.top);
			m_pLightBorderPen->Uninstall(hDC);
		}
		else
		{
			m_pLightBorderPen->Install(hDC);
			m_pLightBorderPen->MoveTo(rect.right,rect.top);
			m_pLightBorderPen->LineTo(rect.left,rect.top);
			m_pLightBorderPen->LineTo(rect.left,rect.bottom);
			m_pLightBorderPen->Uninstall(hDC);

			m_pDarkBorderPen->Install(hDC);
			m_pDarkBorderPen->MoveTo(rect.left,rect.bottom);
			m_pDarkBorderPen->LineTo(rect.right,rect.bottom);
			m_pDarkBorderPen->LineTo(rect.right,rect.top);
			m_pDarkBorderPen->Uninstall(hDC);
		}


	}


	return TRUE;
}
BOOL		CODLEx_Element_ReportItem::DrawContents(HDC IN hDC,RECT* IN txtRect)
{
	if(m_pImageList != NULL)
	{
		LONG index =m_lImageIndex;
		if(IsSelected()&&m_lSelectedImageIndex!=-1)
			index =m_lSelectedImageIndex;

		SIZE imageSize;
		m_pImageList->GetImageSize(index,imageSize.cx,imageSize.cy);

		POINT pt;
		pt.x	=txtRect->left;		
		if((m_uTextAlign&DT_VCENTER)!=0)
		{
			pt.y =txtRect->top + ((txtRect->bottom-txtRect->top)-imageSize.cy)/2;
		}
		else if((m_uTextAlign&DT_BOTTOM)!=0)
		{
			pt.y	=txtRect->bottom-imageSize.cy;
		}
		else
		{
			pt.y	=txtRect->top;
		}

		txtRect->left += imageSize.cx;
		m_pImageList->DrawEx(hDC,index,pt,imageSize,CLR_NONE,CLR_NONE,m_nImageDrawStyle);
	}



	if(m_bSelected)
		::SetTextColor(hDC,m_SelectTextColor);
	else
		::SetTextColor(hDC,m_TextColor);
	::SetBkMode(hDC,TRANSPARENT);
	m_pTextFont->Install(hDC);
	::DrawText(hDC,m_pText,strlen(m_pText),txtRect,m_uTextAlign);
	m_pTextFont->Uninstall(hDC);
	return TRUE;
}

BOOL		CODLEx_Element_ReportItem::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rect;
	GetRect(rect);
	DWORD	dwBorderSize =m_bShowBorder?m_dwBorderSize:0;

	SIZE	size;
	
	size.cx		=m_pReportRow->GetVerticalGridPen()->GetLogPen()->lopnWidth.x/2;
	size.cy		=m_pReportRow->GetHorizontalGridPen()->GetLogPen()->lopnWidth.x/2;

	DrawBackGround(hDC,&rect);
	rect.left		+= m_Padding.left+dwBorderSize+size.cx;
	rect.top		+= m_Padding.top+dwBorderSize+size.cy;
	rect.right		-= m_Padding.right+dwBorderSize+size.cx;
	if(rect.right < rect.left)
		rect.right =rect.left;
	rect.bottom	-=m_Padding.bottom+dwBorderSize+size.cy;
	if(rect.bottom<rect.top)
		rect.bottom	=rect.top;	


	DrawContents(hDC,&rect);

	return TRUE;
}
BOOL	CODLEx_Element_ReportItem::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			RECT	rect;
			GetRect(rect);

			RECT	rightRect,bottomRect;
			rightRect	=rect;
			bottomRect	=rect;

			LONG size =2;
			if(m_pReportRow->GetHorizontalGridPen()->GetLogPen()->lopnWidth.x/2 > size)
				size =m_pReportRow->GetHorizontalGridPen()->GetLogPen()->lopnWidth.x/2;

			bottomRect.top	=bottomRect.bottom-size;
			bottomRect.bottom+=size;

			if(m_pReportRow->GetVerticalGridPen()->GetLogPen()->lopnWidth.x/2 > size)
				size =m_pReportRow->GetVerticalGridPen()->GetLogPen()->lopnWidth.x/2;
			rightRect.left	=rightRect.right-size;
			rightRect.right+=size;

			if(PtInRect(&rightRect,*pPoint))
			{
				m_bAdjustWidth	=TRUE;
				m_lAdjustOffset	=pPoint->x-rect.right;
				::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
				return TRUE;
			}
			else if(PtInRect(&bottomRect,*pPoint))
			{
				m_bAdjustHeight	=TRUE;
				m_lAdjustOffset	=pPoint->y-rect.bottom;
				::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
				return TRUE;
			}
			else if(IsEnableClicked())
			{
				if(PtInRect(&rect,*pPoint))
				{
					m_bPushed	=TRUE;
					Invalidate();
					m_pReportRow->GetReport()->Invalidate(TRUE);
					return TRUE;
				}
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_bAdjustWidth)
			{
				m_bAdjustWidth	=FALSE;
				if(m_pListener != NULL)
					m_pListener->OnElement_ItemSizeChanged(GetReportRow()->GetReport(),this);
			}
			if(m_bAdjustHeight)
			{
				m_bAdjustHeight	=FALSE;
				if(m_pListener != NULL)
					m_pListener->OnElement_ItemSizeChanged(GetReportRow()->GetReport(),this);
			}
			if(m_bPushed)
			{
				m_bPushed	=FALSE;
				if(m_pListener != NULL)
					m_pListener->OnElement_ItemClicked(GetReportRow()->GetReport(),this);
				Invalidate();
				m_pReportRow->GetReport()->Invalidate(TRUE);
				return TRUE;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(m_bAdjustWidth)
			{
				LONG w	=(pPoint->x-m_lAdjustOffset)-m_Pos.x;
				if(w < 10)
				{
					w	=10;
					m_bAdjustWidth=FALSE;
				}
				m_pReportRow->GetReport()->SetColWidth(GetObjListIndex(),w);
				::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
				m_pReportRow->Invalidate(TRUE);
				return TRUE;
			}
			else if(m_bAdjustHeight)
			{
				LONG h	=(pPoint->y-m_lAdjustOffset)-m_Pos.y;
				if(h < 10)
				{
					h	=10;
					m_bAdjustHeight=FALSE;
				}
				m_pReportRow->SetRowHeight(h);
				::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
				m_pReportRow->Invalidate(TRUE);
				return TRUE;
			}
			else
			{
				RECT	rect;
				GetRect(rect);

				RECT	rightRect,bottomRect;
				rightRect	=rect;
				bottomRect	=rect;

				bottomRect.top	=bottomRect.bottom-2;
				bottomRect.bottom+=2;

				rightRect.left	=rightRect.right-2;
				rightRect.right+=2;

				if(PtInRect(&rightRect,*pPoint))
				{
					::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
					return TRUE;
				}
				else if(PtInRect(&bottomRect,*pPoint))
				{
					::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
					return TRUE;
				}

			}

		}
		break;
	}
	return FALSE;
}

BOOL		CODLEx_Element_ReportItem::IsEnableClicked()
{
	return m_bEnableClicked;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::EnableClicked(BOOL IN bEnable)
{
	m_bEnableClicked	=bEnable;
	return this;
}
BOOL		CODLEx_Element_ReportItem::IsShowBorder()
{
	return m_bShowBorder;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::ShowBorder(BOOL IN bShow)
{
	if(m_bShowBorder == bShow)
		return this;
	m_bShowBorder	=bShow;
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetBorderColor(COLORREF IN lightColor,COLORREF IN darkColor)
{
	if(m_LightBorderColor == lightColor && m_DarkBorderColor == darkColor)
		return this;
	m_LightBorderColor		=lightColor;
	m_DarkBorderColor		=darkColor;
	ODL_SafeRelease(m_pDarkBorderPen);
	ODL_SafeRelease(m_pLightBorderPen);
	m_pLightBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,m_dwBorderSize,m_LightBorderColor);
	m_pDarkBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,m_dwBorderSize,m_DarkBorderColor);
	Invalidate();
	return this;
}

CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetBorderSize(DWORD IN dwBorderSize)
{
	if(m_dwBorderSize == dwBorderSize)
		return this;
	m_dwBorderSize	=dwBorderSize;
	ODL_SafeRelease(m_pDarkBorderPen);
	ODL_SafeRelease(m_pLightBorderPen);
	m_pLightBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,m_dwBorderSize,m_LightBorderColor);
	m_pDarkBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,m_dwBorderSize,m_DarkBorderColor);
	Invalidate();
	return this;
}
CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetBorderPen(LOGPEN* IN pLightPen,LOGPEN* IN pDarkPen)
{
	ODL_SafeRelease(m_pDarkBorderPen);
	ODL_SafeRelease(m_pLightBorderPen);
	m_pLightBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(pLightPen);
	m_pDarkBorderPen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(pDarkPen);
	Invalidate();
	return this;
}



CODLEx_Element_ReportItem*		CODLEx_Element_ReportItem::SetImage(CODL_ImageList* IN pImageList,LONG IN lImageIndex,UINT IN nDrawStyle,LONG IN lSelectedImageIndex)
{
	ODL_SafeRelease(m_pImageList);
	m_pImageList	=pImageList;
	if(m_pImageList != NULL)
	{
		m_pImageList->AddRef();
		m_lImageIndex			=lImageIndex;
		m_lSelectedImageIndex	=lSelectedImageIndex;
		m_nImageDrawStyle		=nDrawStyle;
	}
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportItem::GetReportRow()
{
	return m_pReportRow;
}



