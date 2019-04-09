#include "StdAfx.h"
#include ".\odlex_element_label.h"

CODLEx_Element_Label::CODLEx_Element_Label(CODL_CanvasBase* IN pCanvas):
CODL_OverlayElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_LABEL;
	SetZIndex(10);

	m_AnchorPosition.x	=0;		//ÃªµãÎ»ÖÃ
	m_AnchorPosition.y	=0;
	m_Pos.x				=0;
	m_Pos.y				=0;

	m_Rect.left			=0;
	m_Rect.top			=0;
	m_Rect.right		=0;
	m_Rect.bottom		=0;

	m_dwRowCount		=0;
	m_dwColCount		=0;

	m_pBorderPen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(0,0,0));
	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,255,255),NULL);
	m_dwMeatusWidth		=16;

	m_pTitle			=new CODLEx_Element_TextArea(pCanvas);		//
	m_bShowTitle		=FALSE;
	m_bShowBorder		=FALSE;
	m_lMargin			=2;

	m_bDraging			=FALSE;
	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;

	ZeroMemory(m_pMeatusPoints,sizeof(m_pMeatusPoints));

}

CODLEx_Element_Label::~CODLEx_Element_Label(void)
{
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pBorderPen);
	ODL_SafeDelete(m_pTitle);
	m_theTextList.Clear();

}
BOOL						CODLEx_Element_Label::Init(DWORD IN dwRows,DWORD IN dwCols)
{
	m_theTextList.Clear();
	m_dwRowCount	=dwRows;
	m_dwColCount	=dwCols;

	CODLEx_Element_TextArea*	pText =NULL;
	for(DWORD i=0;i<m_dwRowCount*m_dwColCount;i++)
	{
		pText	=new CODLEx_Element_TextArea(GetCanvas());
		m_theTextList.AddObj(pText);
		pText->Release();
	}

	return TRUE;
}
VOID						CODLEx_Element_Label::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
}
VOID						CODLEx_Element_Label::SetAnchorPos(LONG IN x,LONG IN y)
{
	m_AnchorPosition.x	=x;
	m_AnchorPosition.y	=y;
	Invalidate();
}

VOID						CODLEx_Element_Label::SetBorderStyle(UINT IN uStyle,UINT IN uWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pBorderPen);
	m_pBorderPen		=GetCanvas()->GetView()->GetResourceManager()->CreatePen(uStyle,uWidth,clr);
	Invalidate();
}
VOID						CODLEx_Element_Label::ShowBorder(BOOL IN bShow)
{
	m_bShowBorder	=bShow;
	Invalidate();
}

VOID						CODLEx_Element_Label::SetBkColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush			=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,NULL);
	Invalidate();
}
COLORREF					CODLEx_Element_Label::GetBkColor()
{
	if(m_pBkBrush == NULL)
		return RGB(0,0,0);
	return m_pBkBrush->GetLogBrush()->lbColor;
}

VOID						CODLEx_Element_Label::SetTitle(LPCSTR IN pTitle)
{
	if(m_pTitle == NULL)
		m_pTitle =new CODLEx_Element_TextArea(GetCanvas());
	m_pTitle->SetText(pTitle);
	Invalidate();
}
VOID						CODLEx_Element_Label::ShowTitle(BOOL IN bShow)
{
	m_bShowTitle =bShow;
	Invalidate();
}

VOID						CODLEx_Element_Label::SetText(DWORD IN dwRowIndex,DWORD IN dwColIndex, LPCSTR IN pText)
{
	CODLEx_Element_TextArea*	pTextObj =GetTextObject(dwRowIndex,dwColIndex);
	if(pTextObj == NULL)
		return ;

	pTextObj->SetText(pText);
	Invalidate();
}
VOID						CODLEx_Element_Label::SetTextColor(DWORD IN dwRowIndex,DWORD IN dwColIndex,COLORREF IN clr)
{
	CODLEx_Element_TextArea*	pTextObj =GetTextObject(dwRowIndex,dwColIndex);
	if(pTextObj == NULL)
		return ;
	pTextObj->SetTextColor(clr);
	Invalidate();
}

VOID						CODLEx_Element_Label::SetTextFont(DWORD IN dwRowIndex,DWORD IN dwColIndex,LPCSTR IN pFontName,DWORD IN dwFontSize,DWORD IN dwFontWeight)
{
	CODLEx_Element_TextArea*	pTextObj =GetTextObject(dwRowIndex,dwColIndex);
	if(pTextObj == NULL)
		return ;
	pTextObj->SetTextFont(pFontName,dwFontSize,dwFontWeight);
	Invalidate();
}

VOID						CODLEx_Element_Label::SetTextAlign(DWORD IN dwRowIndex,DWORD IN dwColIndex,UINT IN uAlign)
{
	CODLEx_Element_TextArea*	pTextObj =GetTextObject(dwRowIndex,dwColIndex);
	if(pTextObj == NULL)
		return ;
	pTextObj->SetTextAlign(uAlign);
	Invalidate();
}

VOID						CODLEx_Element_Label::SetTextBkColor(DWORD IN dwRowIndex,DWORD IN dwColIndex,COLORREF IN clr)
{
	CODLEx_Element_TextArea*	pTextObj =GetTextObject(dwRowIndex,dwColIndex);
	if(pTextObj == NULL)
		return ;
	pTextObj->SetBkColor(clr);
	Invalidate();
}


CODLEx_Element_TextArea*	CODLEx_Element_Label::GetTitleTextObject()
{
	return m_pTitle;
}

CODLEx_Element_TextArea*	CODLEx_Element_Label::GetTextObject(DWORD IN dwRowIndex,DWORD IN dwColIndex)
{
	if(dwRowIndex >= m_dwRowCount || dwColIndex >= m_dwColCount )
		return NULL;

	return (CODLEx_Element_TextArea*)m_theTextList[dwRowIndex*m_dwColCount + dwColIndex];
}

SIZE				CODLEx_Element_Label::GetTextMaxSize(HDC IN hDC)
{
	SIZE						size		={0,0};
	CODLEx_Element_TextArea*	pTextObj	=NULL;
	RECT						rect		={0,0,0,0};

	for(DWORD i=0;i<m_dwRowCount;i++)
	{
		for(DWORD j=0;j<m_dwColCount;j++)
		{
			pTextObj	=GetTextObject(i,j);
			if(pTextObj != NULL)
			{
				pTextObj->EnableFixedSize(FALSE);
				pTextObj->GetRect(hDC,&rect);
				pTextObj->EnableFixedSize(TRUE);

				if(size.cx < rect.right-rect.left)
					size.cx =rect.right-rect.left;
				if(size.cy < rect.bottom-rect.top)
					size.cy =rect.bottom-rect.top;
			}
		}
	}

	return size;
}

BOOL				CODLEx_Element_Label::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	title_rect;
	SIZE	text_size	=GetTextMaxSize(hDC);
	m_Rect.left		=m_Pos.x;
	m_Rect.top		=m_Pos.y;
	m_Rect.bottom	=m_Pos.y + text_size.cy*m_dwRowCount +m_lMargin*2;
	m_Rect.right	=m_Pos.x + text_size.cx*m_dwColCount +m_lMargin*2;
	if(m_bShowTitle)
	{
		m_pTitle->GetRect(hDC,&title_rect);
		m_Rect.bottom += title_rect.bottom-title_rect.top;
	}


	
	RECT	rec =m_Rect;
	if(m_bShowBorder)
	{
		m_pBorderPen->Install(hDC);
		MoveToEx(hDC,m_Rect.left,m_Rect.top,NULL);
		LineTo(hDC,m_Rect.right,m_Rect.top);
		LineTo(hDC,m_Rect.right,m_Rect.bottom);
		LineTo(hDC,m_Rect.left,m_Rect.bottom);
		LineTo(hDC,m_Rect.left,m_Rect.top);
		m_pBorderPen->Uninstall(hDC);
		
		LONG ext=m_pBorderPen->GetLogPen()->lopnWidth.x/2;
		if(ext<=0)ext=1;

		rec.left+=ext;
		rec.top +=ext;
	}

	if(GetMeatusPoints())
	{
		HRGN hRgn	=CreatePolygonRgn(m_pMeatusPoints,4,WINDING);
		FillRgn(hDC,hRgn,m_pBkBrush->GetBrush());
		DeleteObject(hRgn);
		m_pBorderPen->Install(hDC);
		Polygon(hDC,m_pMeatusPoints,4);
		m_pBorderPen->Uninstall(hDC);
		FillRect(hDC,&rec,m_pBkBrush->GetBrush());
	}
	else
	{
		FillRect(hDC,&rec,m_pBkBrush->GetBrush());
	}
	

	//draw contents

	DWORD	dwRowIndex =0;
	DWORD	dwColIndex =0;
	LONG	top		   =m_lMargin;
	CODLEx_Element_TextArea*	pTextObj	=NULL;
	if(m_bShowTitle)
	{
		m_pTitle->EnableFixedSize(TRUE);
		m_pTitle->SetPos(m_Pos.x + m_lMargin +dwColIndex*text_size.cx, m_Pos.y + m_lMargin);
		m_pTitle->SetSize(text_size.cx*m_dwColCount , title_rect.bottom-title_rect.top);
		top +=title_rect.bottom-title_rect.top;
		m_pTitle->Draw(hDC,pPaintRect);
	}

	for(DWORD i=0;i<m_dwRowCount;i++)
	{
		dwColIndex =0;
		for(DWORD j=0;j<m_dwColCount;j++)
		{
			pTextObj	=GetTextObject(i,j);
			if(pTextObj == NULL)
				continue;
			pTextObj->EnableFixedSize(TRUE);
			pTextObj->SetPos(m_Pos.x + m_lMargin +dwColIndex*text_size.cx, m_Pos.y + top + text_size.cy*dwRowIndex);

			pTextObj->SetSize(text_size.cx , text_size.cy);
			pTextObj->Draw(hDC,pPaintRect);
			dwColIndex++;
		}
		dwRowIndex ++;
	}




	return TRUE;
}
BOOL				CODLEx_Element_Label::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	return PtInRect(&m_Rect,pt);
}

BOOL				CODLEx_Element_Label::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(!PtInElement(*pPoint))
				break;
			m_bDraging	=TRUE;
			m_ptDragOffset.x	=m_Pos.x - pPoint->x;
			m_ptDragOffset.y	=m_Pos.y - pPoint->y;
			return TRUE;
		}
		break;
	case WM_LBUTTONUP:
		{
			if(!m_bDraging)
				break;
			if(m_pListener != NULL)
				m_pListener->OnElement_PosChanged(this);

			m_bDraging	=FALSE;
			Invalidate(TRUE);
			return TRUE;
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!m_bDraging)
				break;
			
			m_Pos.x		=pPoint->x + m_ptDragOffset.x;
			m_Pos.y		=pPoint->y + m_ptDragOffset.y;

			Invalidate(TRUE);
			return TRUE;
		}
		break;
	}


	return FALSE;
}
BOOL				CODLEx_Element_Label::GetMeatusPoints()
{
	if(PtInRect(&m_Rect,m_AnchorPosition))
		return FALSE;

	CODL_Vector2f	vCenter(m_Rect.left + (m_Rect.right-m_Rect.left)/2 , m_Rect.top + (m_Rect.bottom-m_Rect.top)/2 );
	CODL_Vector2f	vAnchor(m_AnchorPosition.x,m_AnchorPosition.y);
	CODL_LineStrip	line(vAnchor,vCenter);


	CODL_Vector2f	vDirect =line.GetCrossVector();
	CODL_Vector2f	v1		=vCenter - vDirect*(FLOAT)(m_dwMeatusWidth/2);
	CODL_Vector2f	v2		=vCenter + vDirect*(FLOAT)(m_dwMeatusWidth/2);
	
	
	m_pMeatusPoints[0]		=m_AnchorPosition;
	m_pMeatusPoints[1].x	=v1.x;
	m_pMeatusPoints[1].y	=v1.y;
	m_pMeatusPoints[2].x	=v2.x;
	m_pMeatusPoints[2].y	=v2.y;
	m_pMeatusPoints[3]		=m_pMeatusPoints[0];


	
	return TRUE;
}

VOID				CODLEx_Element_Label::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	RECT	title_rect;
	SIZE	text_size	=GetTextMaxSize(hDC);
	m_Rect.left		=m_Pos.x;
	m_Rect.top		=m_Pos.y;
	m_Rect.bottom	=m_Pos.y + text_size.cy*m_dwRowCount +m_lMargin*2;
	m_Rect.right	=m_Pos.x + text_size.cx*m_dwColCount +m_lMargin*2;
	if(m_bShowTitle)
	{
		m_pTitle->GetRect(hDC,&title_rect);
		m_Rect.bottom += title_rect.bottom-title_rect.top;
	}



	POINT	maxPt,minPt;
	maxPt.x		=m_Rect.left;
	maxPt.y		=m_Rect.top;
	minPt.x		=m_Rect.left;
	minPt.y		=m_Rect.top;

	maxPt.x		=max(maxPt.x,m_AnchorPosition.x);
	maxPt.y		=max(maxPt.y,m_AnchorPosition.y);
	maxPt.x		=max(maxPt.x,m_Rect.right);
	maxPt.y		=max(maxPt.y,m_Rect.bottom);
	
	minPt.x		=min(minPt.x,m_AnchorPosition.x);
	minPt.y		=min(minPt.y,m_AnchorPosition.y);
	minPt.x		=min(minPt.x,m_Rect.right);
	minPt.y		=min(minPt.y,m_Rect.bottom);

	boundRect.left	=minPt.x;
	boundRect.top	=minPt.y;

	boundRect.right =maxPt.x;
	boundRect.bottom=maxPt.y;

	InflateRect(&boundRect,5,5);
}
