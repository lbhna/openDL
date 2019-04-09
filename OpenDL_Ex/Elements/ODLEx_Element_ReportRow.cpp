#include "stdafx.h"
#include "./ODLEx_Element_ReportRow.h"
#include "./ODLEx_Element_Report.h"

CODLEx_Element_ReportRow::CODLEx_Element_ReportRow(CODLEx_Element_Report*IN pReport,CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_pReport				=pReport;
	m_Type					=ODL_ELEMENT_REPORT_ROW;
	m_Pos.x					=m_Pos.y	=0;
	m_Size.cx				=m_Size.cy	=0;

	m_DrawClip.left			=0;
	m_DrawClip.top			=0;
	m_DrawClip.right		=0;
	m_DrawClip.bottom		=0;

	m_lItemsSize			=0;

	m_pDefaultFont			=new CODL_Font("宋体",12);			//默认字体 
	m_pBkBrush				=new CODL_Brush(BS_SOLID,RGB(255,255,255),0);
	m_DefaultTextColor		=RGB(0,0,0);

	m_bShowHorizontalGrid	=TRUE;	//是否显示水平方向网格线
	m_pHorizontalGridPen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(0,0,0));	//水平方向网格线画笔
	m_bShowVerticalGrid		=TRUE;	//是否显示垂直方向网格线
	m_pVerticalGridPen		=m_pCanvas->GetView()->GetResourceManager()->CreatePen(BS_SOLID,1,RGB(0,0,0));//垂直方向网格线画笔

	m_hBitmap				=NULL;
	m_hBitmapDC				=NULL;
	m_BitmapRect.left		=0;
	m_BitmapRect.right		=0;
	m_BitmapRect.top		=0;
	m_BitmapRect.bottom		=0;
}
CODLEx_Element_ReportRow::~CODLEx_Element_ReportRow()
{

	m_theItemsList.Clear();
	if(m_pListener != NULL)
		m_pListener->OnElement_ItemDeleted(GetReport(),this);

	ODL_SafeDeleteGDIObj(m_hBitmap);
	if(m_hBitmapDC != NULL)
		DeleteDC(m_hBitmapDC);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pDefaultFont);
	ODL_SafeRelease(m_pHorizontalGridPen);
	ODL_SafeRelease(m_pVerticalGridPen);
}
CODLEx_Element_ReportRow*						CODLEx_Element_ReportRow::SetItemCount(LONG IN lCount)
{
	if(m_theItemsList.GetCount() == lCount)
		return this;
	if(m_theItemsList.GetCount() > lCount)
	{
		for(LONG i=m_theItemsList.GetCount()-1;i>=lCount;i--)
		{
			m_theItemsList.DelObj(i);
		}
		UpdateItemsSize();
	}
	else
	{
		CODLEx_Element_ReportRow*	pHeader		=GetReport()->GetHeader();
		CODLEx_Element_ReportItem*	pItem		=NULL;
		CODLEx_Element_ReportItem*	p			=NULL;
		for(LONG i=m_theItemsList.GetCount();i<lCount;i++)
		{
			pItem	=new CODLEx_Element_ReportItem(this,m_pCanvas);
			pItem->SetPos(m_lItemsSize,0);
			p =pHeader->GetItem(i);
			pItem->SetSize(p!=NULL?pHeader->GetItem(i)->GetSize()->cx:80,m_Size.cy);
			m_lItemsSize += pItem->GetSize()->cx;

			pItem->SetBkBrush(m_pBkBrush);
			pItem->SetFont(m_pDefaultFont);
			pItem->SetTextColor(m_DefaultTextColor);
			m_theItemsList.AddObj(pItem);
			pItem->Release();
		}
	}
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*						CODLEx_Element_ReportRow::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x	=x;
	m_Pos.y	=y;
	Invalidate();
	return this;
}
POINT*						CODLEx_Element_ReportRow::GetPos()
{
	return &m_Pos;
}
CODLEx_Element_ReportRow*						CODLEx_Element_ReportRow::SetSize(LONG IN cx,LONG IN cy)
{
	if(m_Size.cx == cx && m_Size.cy ==cy)
		return this;
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	CODLEx_Element_ReportItem*	pItem	=NULL;
	for(LONG i=0;i<m_theItemsList.GetCount();i++)
	{
		pItem =(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(i);
		pItem->SetSize(pItem->GetSize()->cx,cy);
	}
	Invalidate();
	return this;
}
SIZE*						CODLEx_Element_ReportRow::GetSize()
{
	return &m_Size;
}

LONG						CODLEx_Element_ReportRow::GetItemTotalSize()
{
	return m_lItemsSize;
}

LONG						CODLEx_Element_ReportRow::GetItemCount()
{
	return m_theItemsList.GetCount();
}
CODLEx_Element_Report*		CODLEx_Element_ReportRow::GetReport()
{
	return m_pReport;
}

CODLEx_Element_ReportItem*	CODLEx_Element_ReportRow::InsertItem(LONG IN lInsertBefore)
{
	CODLEx_Element_ReportItem* pItem	=new CODLEx_Element_ReportItem(this,m_pCanvas);
	pItem->SetPos(m_lItemsSize,0);
	pItem->SetSize(80,m_Size.cy);
	m_lItemsSize += pItem->GetSize()->cx;
	pItem->SetBkBrush(m_pBkBrush);
	pItem->SetFont(m_pDefaultFont);
	pItem->SetTextColor(m_DefaultTextColor);
	m_theItemsList.InsertObj(lInsertBefore,pItem);
	pItem->Release();
	Invalidate();
	return pItem;
}



CODL_DirtyRect&				CODLEx_Element_ReportRow::GetDirtyRect()
{
	return m_DirtyRect;
}
CODLEx_Element_ReportItem*	CODLEx_Element_ReportRow::GetItem(LONG IN lIndex)
{
	return (CODLEx_Element_ReportItem*)m_theItemsList.GetObj(lIndex);
}
BOOL						CODLEx_Element_ReportRow::ChangeItemObject(LONG IN lIndex,CODLEx_Element_ReportItem* IN pItem)
{
	return m_theItemsList.ChangeObject(lIndex,pItem);
}
CODLEx_Element_ReportRow*						CODLEx_Element_ReportRow::SetItemWidth(LONG IN lIndex,LONG IN lWidth)
{
	CODLEx_Element_ReportItem*	pItem =(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(lIndex);
	if(pItem == NULL)
		return this;
	if(pItem->GetSize()->cx == lWidth)
		return this;
	pItem->SetSize(lWidth,pItem->GetSize()->cy);
	if(lIndex>0)lIndex--;	
	for(;lIndex<m_theItemsList.GetCount();lIndex++)
	{
		pItem =(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(lIndex);
		pItem->Invalidate();
	}
	return this;
}
CODLEx_Element_ReportRow*						CODLEx_Element_ReportRow::SetDrawClip(RECT& IN clip)
{
	if(m_DrawClip.left != clip.left ||
		m_DrawClip.right != clip.right||
		m_DrawClip.top != clip.top||
		m_DrawClip.bottom != clip.bottom)
	{
		m_DrawClip	=clip;
		m_DirtyRect.SetRect(m_BitmapRect);
		Invalidate();
	}
	return this;
}


BOOL						CODLEx_Element_ReportRow::Draw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(!IsShow())
		return TRUE;
	if(!ResetBitmapCanvas(hDC,pPaintRect))
		return FALSE;
	if(!OnDraw(m_hBitmapDC,&m_BitmapRect))
		return FALSE;

	BitBlt(
		hDC,
		m_Pos.x,m_Pos.y,
		m_DrawClip.right - m_DrawClip.left,
		m_DrawClip.bottom - m_DrawClip.top,
		m_hBitmapDC,
		m_DrawClip.left,
		m_DrawClip.top,
		SRCCOPY);

	m_DirtyRect.Reset();
	return TRUE;
}
VOID						CODLEx_Element_ReportRow::UpdateItemsDirtyRect(LONG IN lStart,LONG IN lEnd)
{
	m_DirtyRect.Reset();
	CODLEx_Element_ReportItem*	pItem	=NULL;
	RECT			rect;
	for(LONG i=lStart;i<lEnd;i++)
	{
		pItem			=(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(i);
		if(pItem->IsInvalidate())
		{
			pItem->GetRect(rect);
			m_DirtyRect.Add(rect);
		}
	}
}
BOOL						CODLEx_Element_ReportRow::GetNeedDrawItem(LONG& OUT lStart,LONG& OUT lEnd)
{
	lStart	=-1;
	lEnd	=-1;

	CODLEx_Element_ReportItem*	pItem		=NULL;
	LONG						position	=0;
	LONG						i			=0;
	for(i=0;i<m_theItemsList.GetCount();i++)
	{
		pItem	=(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(i);
		position += pItem->GetSize()->cx;
		if(lStart == -1)
		{
			if(m_DrawClip.left <= position)
			{
				lStart	=i;
			}
		}
		else
		{
			lEnd =i+1;
			if( (m_DrawClip.left + m_Size.cx) <= position)
				break;
		}
	}
	if(lStart<0 || lEnd<0)
		return FALSE;

	if(lEnd < 0)
		lEnd	=m_theItemsList.GetCount()-1;
	return TRUE;
}

VOID						CODLEx_Element_ReportRow::Invalidate(BOOL IN bFlushView)
{
	m_bInvalidate		=TRUE;
	for(LONG i=0;i<GetItemCount();i++)
		GetItem(i)->Invalidate();
	GetCanvas()->Invalidate(FALSE);
	if(bFlushView)
		GetCanvas()->GetView()->Invalidate();
}
VOID						CODLEx_Element_ReportRow::SetSelected(BOOL IN bSelect)
{
	if(!IsEnableSelect())
		return;
	for(LONG i=0;i<m_theItemsList.GetCount();i++)
		GetItem(i)->SetSelected(bSelect);
	m_bSelected		=bSelect;
	Invalidate(TRUE);

	if(m_pListener != NULL)
	{
		if(m_bSelected)
			m_pListener->OnElement_ItemSelected(GetReport(),this);
		else
			m_pListener->OnElement_ItemUnselected(GetReport(),this);
	}

}

BOOL						CODLEx_Element_ReportRow::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	LONG lStart,lEnd;
	if(!GetNeedDrawItem(lStart,lEnd))
		return TRUE;//没有需要绘制的项
	if(m_bInvalidate)
	{
		//RECT	UpdateRect;
		//UpdateRect.left		=m_BitmapRect.left	+ m_DrawOffset.x;
		//UpdateRect.top			=m_BitmapRect.top	+ m_DrawOffset.y;
		//UpdateRect.right		=UpdateRect.left	+ m_Size.cx;
		//UpdateRect.bottom		=(m_BitmapRect.bottom-m_BitmapRect.top) - m_DrawOffset.y;

		//m_DirtyRect.SetRect(UpdateRect);
		m_bInvalidate	=FALSE;
		
		//m_pBkBrush->Install(hDC);
		//m_pBkBrush->FillRect(&m_BitmapRect);
		//m_pBkBrush->Uninstall(hDC);

	}
	//else
	//{
	//	UpdateItemsDirtyRect(lStart,lEnd);
	//}
	//if(m_DirtyRect.IsEmpty())//无需绘制
	//	return FALSE;


	CODLEx_Element_ReportItem*	pItem	=NULL;
	for(LONG i=lStart;i<lEnd;i++)
	{
		pItem			=(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(i);
		if(pItem->IsInvalidate())
			pItem->Draw(hDC,pPaintRect);
	}

	
	SIZE size;
	size.cx		=m_BitmapRect.right - m_BitmapRect.left;
	size.cy		=m_BitmapRect.bottom- m_BitmapRect.top;
	if(m_bShowHorizontalGrid)
	{
		m_pHorizontalGridPen->Install(hDC);
		m_pHorizontalGridPen->MoveTo(0,size.cy-1);
		m_pHorizontalGridPen->LineTo(size.cx,size.cy-1);
		m_pHorizontalGridPen->Uninstall(hDC);
	}

	if(m_bShowVerticalGrid)
	{
		m_pVerticalGridPen->Install(hDC);
		LONG x =0;
		for(LONG i=0;i<m_theItemsList.GetCount();i++)
		{
			pItem			=(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(i);
			x	+= pItem->GetSize()->cx;
			m_pVerticalGridPen->MoveTo(x-1,0);
			m_pVerticalGridPen->LineTo(x-1,size.cy);
		}

		m_pVerticalGridPen->Uninstall(hDC);
	}


	return TRUE;
}
BOOL						CODLEx_Element_ReportRow::PtInElement(POINT IN pt)
{
	RECT rect;
	GetRect(rect);
	pt.y += m_DrawClip.top;
	return PtInRect(&rect,pt);
}

BOOL						CODLEx_Element_ReportRow::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(!IsShow())
		return FALSE;
	
	LONG lStart,lEnd;
	if(GetNeedDrawItem(lStart,lEnd))
	{
		POINT	localPoint	=*pPoint;
		localPoint.x-=m_Pos.x;localPoint.x+=m_DrawClip.left;
		localPoint.y-=m_Pos.y;localPoint.y+=m_DrawClip.top;

		for(LONG i=lStart;i<lEnd;i++)
		{
			if(GetItem(i)->OnWndMsg(message,wParam,lParam,pResult,&localPoint))
				return TRUE;
		}
	}
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(PtInElement(*pPoint))
			{				
				if(IsEnableSelect())
					m_pReport->SetCurrentSelect(this);
				return TRUE;
			}
		}
		break;
	case WM_LBUTTONUP:
		{

		}
		break;
	}
	return FALSE;
}
VOID						CODLEx_Element_ReportRow::GetRect(RECT& OUT rect)
{
	rect.left			=m_Pos.x;
	rect.top			=m_Pos.y;
	rect.right			=m_Pos.x	+m_Size.cx;
	rect.bottom			=m_Pos.y	+m_Size.cy;
}
VOID						CODLEx_Element_ReportRow::UpdateItemsSize()
{
	m_lItemsSize		=0;
	CODLEx_Element_ReportItem*	pItem	=NULL;
	for(LONG i=0;i<m_theItemsList.GetCount();i++)
	{
		pItem	=(CODLEx_Element_ReportItem*)m_theItemsList.GetObj(i);
		pItem->SetPos(m_lItemsSize,0);
		m_lItemsSize	+= pItem->GetSize()->cx;
	}
}
BOOL						CODLEx_Element_ReportRow::ResetBitmapCanvas(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT rect;
	GetRect(rect);
	if(m_lItemsSize > (rect.right-rect.left))
		rect.right	=rect.left + m_lItemsSize;

	if( (rect.right		-rect.left)		!= (m_BitmapRect.right	-m_BitmapRect.left)||
		(rect.bottom	-rect.top)		!= (m_BitmapRect.bottom	-m_BitmapRect.top))
	{
		ODL_SafeDeleteGDIObj(m_hBitmap);
		if(m_hBitmapDC != NULL)
			DeleteDC(m_hBitmapDC);

		m_hBitmapDC	=CreateCompatibleDC(hDC);
		if(m_hBitmapDC == NULL)
			return FALSE;
		m_BitmapRect.left	=0;
		m_BitmapRect.top	=0;
		m_BitmapRect.right	=rect.right-rect.left;
		m_BitmapRect.bottom	=rect.bottom-rect.top;

		m_hBitmap	=CreateCompatibleBitmap(hDC,
			m_BitmapRect.right-m_BitmapRect.left,
			m_BitmapRect.bottom-m_BitmapRect.top);
		if(m_hBitmap == NULL)
			return FALSE;

		SelectObject(m_hBitmapDC,m_hBitmap);
		Invalidate();
		return TRUE;
	}
	return TRUE;
}

BOOL				CODLEx_Element_ReportRow::IsShowHorizontalGrid()
{
	return m_bShowHorizontalGrid;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::EnableShowHorizontalGrid(BOOL IN bEnable)
{
	if(m_bShowHorizontalGrid == bEnable)
		return this;
	m_bShowHorizontalGrid	=bEnable;
	Invalidate();
	return this;
}
BOOL				CODLEx_Element_ReportRow::IsShowVerticalGrid()
{
	return m_bShowVerticalGrid;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::EnableShowVerticalGrid(BOOL IN bEnable)
{
	if(m_bShowVerticalGrid == bEnable)
		return this;
	m_bShowVerticalGrid	=bEnable;
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetVerticalGridPen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pVerticalGridPen);
	m_pVerticalGridPen=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetHorizontalGridPen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pHorizontalGridPen);
	m_pHorizontalGridPen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
	Invalidate();
	return this;
}

CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetVerticalGridPen(CODL_Pen* IN pPen)
{
	if(pPen == NULL)
		return this;
	ODL_SafeRelease(m_pVerticalGridPen);
	m_pVerticalGridPen =pPen;
	pPen->AddRef();
	Invalidate();
	return this;

}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetHorizontalGridPen(CODL_Pen* IN pPen)
{
	if(pPen == NULL)
		return this;
	ODL_SafeRelease(m_pHorizontalGridPen);
	m_pHorizontalGridPen =pPen;
	pPen->AddRef();
	Invalidate();
	return this;
}


CODL_Pen*			CODLEx_Element_ReportRow::GetVerticalGridPen()
{
	return m_pVerticalGridPen;
}
CODL_Pen*			CODLEx_Element_ReportRow::GetHorizontalGridPen()
{
	return m_pHorizontalGridPen;
}
CODL_Font*			CODLEx_Element_ReportRow::GetDefaultFont()
{
	return m_pDefaultFont;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetDefaultFont(LOGFONT* IN lf)
{
	m_pDefaultFont->Update(lf);
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetDefaultBkBrush(LOGBRUSH* IN lb)
{
	m_pBkBrush->Update(lb);
	Invalidate();
	return this;
}
CODL_Brush*			CODLEx_Element_ReportRow::GetDefaultBkBrush()
{
	return m_pBkBrush;
}
COLORREF			CODLEx_Element_ReportRow::GetDefaultTextColor()
{
	return m_DefaultTextColor;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetDefaultTextColor(COLORREF IN clr)
{
	m_DefaultTextColor	=clr;
	for(LONG i=0;i<m_theItemsList.GetCount();i++)
		GetItem(i)->SetTextColor(clr);
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetColWidth(LONG IN lCol,LONG IN lWidth)
{
	CODLEx_Element_ReportItem*	pItem =GetItem(lCol);
	if(pItem != NULL)
	{
		pItem->SetWidth(lWidth);
		UpdateItemsSize();
	}
	Invalidate();
	return this;
}
CODLEx_Element_ReportRow*				CODLEx_Element_ReportRow::SetRowHeight(LONG IN lHeight)
{
	for(LONG i=0;i<m_theItemsList.GetCount();i++)
		GetItem(i)->SetHeight(lHeight);
	m_Size.cy =lHeight;
	Invalidate();
	m_pReport->Invalidate();
	return this;
}




