#include "stdafx.h"
#include ".\odlex_element_report.h"

CODLEx_Element_Report::CODLEx_Element_Report(CODL_CanvasBase* IN pCanvas):
CODL_OverlayElementBase(pCanvas)
{
	m_Type						=ODL_ELEMENT_REPORT;

	m_Pos.x						=m_Pos.y	=0;
	m_Size.cx					=200;
	m_Size.cy					=100;
		
	m_bShowHeader				=TRUE;			//是否显示表头

	m_pBkBrush					=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,255,255),0);

	m_pHeader					=new CODLEx_Element_ReportRow(this,m_pCanvas);//表头
	m_pHeader->SetSize(24,24);
	m_pHeader->EnableSelect(FALSE);

	m_pHorizontalScrollbar		=new CODLEx_Element_ScrollBar(m_pCanvas);
	m_pHorizontalScrollbar->SetHorizontal(TRUE);
	m_pHorizontalScrollbar->SetSize(20,20);

	m_pVerticalScrollbar		=new CODLEx_Element_ScrollBar(m_pCanvas);
	m_pVerticalScrollbar->SetHorizontal(FALSE);
	m_pVerticalScrollbar->SetSize(20,20);

	m_bShowHorizontalGrid		=TRUE;
	m_bShowVerticalGrid			=TRUE;

	m_DrawOffset.x				=0;
	m_DrawOffset.y				=0;

	m_pCurrentSelected			=NULL;



	m_ptDragOffset.x			=0;
	m_ptDragOffset.y			=0;

	m_bEnableDrag				=FALSE;
	m_bDraging					=FALSE;

	m_bEnableAdjustSize			=FALSE;
	m_bAdjustSizeing			=FALSE;




}

CODLEx_Element_Report::~CODLEx_Element_Report(void)
{
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pHeader);
	ODL_SafeRelease(m_pHorizontalScrollbar);
	ODL_SafeRelease(m_pVerticalScrollbar);
}
VOID		CODLEx_Element_Report::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	GetRect(boundRect);
}
BOOL					CODLEx_Element_Report::PtInAdjustSizeButton(POINT* IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	GetRect(rect);
	rect.left	=rect.right -5;
	rect.top	=rect.bottom-5;
	return PtInRect(&rect,*pt);
}
BOOL		CODLEx_Element_Report::PtInElement(POINT IN pt)
{
	RECT	rect;
	GetRect(rect);
	return PtInRect(&rect,pt);
}

VOID		CODLEx_Element_Report::GetRect(RECT& OUT rect)
{
	rect.left	=m_Pos.x;
	rect.top	=m_Pos.y;

	rect.right	=m_Pos.x + m_Size.cx;
	rect.bottom =m_Pos.y + m_Size.cy;
}	
VOID		CODLEx_Element_Report::GetClientRect(RECT& OUT rect)
{
	rect.left	=m_Pos.x;
	rect.top	=m_Pos.y;
	if(m_bShowHeader)
		rect.top	+=m_pHeader->GetSize()->cy;
	rect.right	=rect.left	+(m_Size.cx - m_pVerticalScrollbar->GetSize()->cx );
	rect.bottom	=rect.top	+(m_Size.cy	- m_pHorizontalScrollbar->GetSize()->cy);
	if(m_bShowHeader)
		rect.bottom	-=m_pHeader->GetSize()->cy;
}
VOID		CODLEx_Element_Report::GetNeedDrawRow(LONG& OUT lStart,LONG& OUT lEnd)
{
	lStart =-1;
	lEnd	=-1;

	LONG						offset	=0	,i=0;
	CODLEx_Element_ReportRow*	pRow	=NULL;
	
	for(i=0;i<m_theRowsList.GetCount();i++)
	{
		pRow			=(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
		offset		+= pRow->GetSize()->cy;
		if(offset > m_DrawOffset.y)
		{
			lStart	=i;
			break;
		}
	}
	if(lStart == -1)
		return;

	RECT	clientRect;
	GetClientRect(clientRect);
	LONG lBottomPosition	=clientRect.bottom;
	offset	=0;
	if(m_bShowHeader)
	{
		lBottomPosition+=m_pHeader->GetSize()->cy;
		offset=m_pHeader->GetSize()->cy;
	}

	for(;i<m_theRowsList.GetCount();i++)
	{
		pRow			=(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
		offset			+= pRow->GetSize()->cy;
		lEnd			=i+1;
		if(offset >= lBottomPosition)
			break;
	}
}

VOID		CODLEx_Element_Report::RecalcLayout()
{
	POINT	pt;
	pt.x	=m_Pos.x;
	pt.y	=m_Pos.y;
	if(m_bShowHeader)
	{
		m_pHeader->SetPos(pt.x,pt.y);
		m_pHeader->SetSize(m_Size.cx-m_pVerticalScrollbar->GetSize()->cx,m_pHeader->GetSize()->cy);
		pt.y += m_pHeader->GetSize()->cy;
	}
	RECT	clientRect;
	GetClientRect(clientRect);

	SIZE	totalSize;
	totalSize.cx	=0;
	totalSize.cy	=0;
	CODLEx_Element_ReportRow*	pRow =NULL;
	for(LONG i=0;i<m_theRowsList.GetCount();i++)
	{
		pRow			=(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
		pRow->Show(FALSE);
		pRow->SetSize(m_Size.cx-m_pVerticalScrollbar->GetSize()->cx,pRow->GetSize()->cy);
		pt.y			+= pRow->GetSize()->cy;
		totalSize.cx	=pRow->GetItemTotalSize();
		totalSize.cy	+= pRow->GetSize()->cy;
	}
	m_pHorizontalScrollbar->SetPos(m_Pos.x,(m_Pos.y+m_Size.cy) - m_pHorizontalScrollbar->GetSize()->cy);
	m_pHorizontalScrollbar->SetSize(m_Size.cx-m_pVerticalScrollbar->GetSize()->cx,m_pHorizontalScrollbar->GetSize()->cy);
	m_pHorizontalScrollbar->SetMaxPosition(totalSize.cx);
	m_pHorizontalScrollbar->SetPageSize(clientRect.right-clientRect.left);

	m_pVerticalScrollbar->SetPos((m_Pos.x +m_Size.cx) - m_pVerticalScrollbar->GetSize()->cx,m_Pos.y);
	m_pVerticalScrollbar->SetSize( m_pVerticalScrollbar->GetSize()->cx,m_Size.cy-m_pHorizontalScrollbar->GetSize()->cy);
	m_pVerticalScrollbar->SetMaxPosition(totalSize.cy);
	m_pVerticalScrollbar->SetPageSize(clientRect.bottom-clientRect.top);
}
BOOL		CODLEx_Element_Report::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rect;
	GetRect(rect);
	RECT	clientRect;
	GetClientRect(clientRect);
	if(m_bInvalidate)
		RecalcLayout();
	m_pBkBrush->Install(hDC);
	m_pBkBrush->FillRect(&rect);
	m_pBkBrush->Uninstall(hDC);
	m_DrawOffset.x	=m_pHorizontalScrollbar->GetPosition();
	m_DrawOffset.y	=m_pVerticalScrollbar->GetPosition();

	LONG						offset	=0		,i=0;
	CODLEx_Element_ReportRow*	pRow	=NULL;
	RECT						clip;
	POINT	pt;
	pt.x	=m_Pos.x;
	pt.y	=m_Pos.y;
	if(m_bShowHeader)
	{
		m_pHeader->SetPos(pt.x,pt.y);
		clip.left	=m_DrawOffset.x;
		clip.right	=clip.left+m_pHeader->GetSize()->cx;
		if(clip.right > m_pHeader->GetItemTotalSize())
			clip.right = m_pHeader->GetItemTotalSize();
		clip.top	=0;
		clip.bottom =m_pHeader->GetSize()->cy;
		if(clip.bottom > (clientRect.bottom-clientRect.top)+m_pHeader->GetSize()->cy)
			clip.bottom =(clientRect.bottom-clientRect.top)+m_pHeader->GetSize()->cy;

		m_pHeader->SetDrawClip(clip);
		m_pHeader->Draw(hDC,pPaintRect);
		pt.y	+= m_pHeader->GetSize()->cy;
	}
	if(pt.y < clientRect.bottom)
	{
		LONG lBottomPosition	=clientRect.bottom;
		for(i=0;i<m_theRowsList.GetCount();i++)
		{
			pRow			=(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
			offset		+= pRow->GetSize()->cy;
			if(offset > m_DrawOffset.y)
			{
				pRow->SetPos(pt.x,pt.y);
				pRow->Show(TRUE);

				clip.left	=m_DrawOffset.x;
				clip.right	=clip.left+pRow->GetSize()->cx;
				if(clip.right > pRow->GetItemTotalSize())
					clip.right = pRow->GetItemTotalSize();

				clip.top	=pRow->GetSize()->cy -(offset - m_DrawOffset.y);
				clip.bottom =pRow->GetSize()->cy;
				if( (pt.y+(clip.bottom-clip.top)) > lBottomPosition)
				{
					clip.bottom -=(pt.y+(clip.bottom-clip.top)) - lBottomPosition;
				}



				pRow->SetDrawClip(clip);
				pRow->Draw(hDC,pPaintRect);
				pt.y	+= clip.bottom-clip.top;
				i++;
				break;
			}
		}

		for(;i<m_theRowsList.GetCount();i++)
		{
			pRow			=(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
			pRow->SetPos(pt.x,pt.y);
			pRow->Show(TRUE);
			pt.y	+= pRow->GetSize()->cy;

			clip.left	=m_DrawOffset.x;
			clip.right	=clip.left+pRow->GetSize()->cx;
			if(clip.right > pRow->GetItemTotalSize())
				clip.right = pRow->GetItemTotalSize();

			if(pt.y >= lBottomPosition)
			{
				clip.top	=0;
				clip.bottom =pRow->GetSize()->cy -(pt.y - lBottomPosition);

				pRow->SetDrawClip(clip);

				pRow->Draw(hDC,pPaintRect);
				break;
			}
			else
			{
				clip.top	=0;
				clip.bottom =pRow->GetSize()->cy;
				pRow->SetDrawClip(clip);

				pRow->Draw(hDC,pPaintRect);
			}
		}
	}


	m_pHorizontalScrollbar->Draw(hDC,pPaintRect);
	m_pVerticalScrollbar->Draw(hDC,pPaintRect);


	m_bInvalidate=FALSE;




	if(IsSelected())
	{
		RECT BoundRect;
		GetRect(BoundRect);
		m_pCanvas->GetElementSelectFramePen()->Install(hDC);
			m_pCanvas->GetElementSelectFramePen()->DrawRect(&BoundRect);
		if(m_bEnableAdjustSize)
		for(INT i=1;i<=7;i++)
		{
			MoveToEx(hDC,BoundRect.right,BoundRect.bottom-i,NULL);
			LineTo(hDC,BoundRect.right-i,BoundRect.bottom);			
		}
		m_pCanvas->GetElementSelectFramePen()->Uninstall(hDC);
	}

	return TRUE;
}
BOOL		CODLEx_Element_Report::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(!IsShow())
		return FALSE;
	if(IsControlSwitchKeyPressed())
	{
		switch(message)
		{
		case WM_RBUTTONDOWN:
			{
				if(!IsSelected())
					break;
				if(!PtInElement(*pPoint))
					break;
				if(PopupMenu())
					return TRUE;
			}
			break;
		case WM_LBUTTONDOWN:
			{
				if(!IsSelected())
					break;
				//只有在Ctrl键按下的情况下才可以进行下列操作
				if(m_bEnableAdjustSize)
				{
					if(PtInAdjustSizeButton(pPoint))
					{
						m_bAdjustSizeing		=TRUE;
						m_ptDragOffset.x		=(m_Pos.x+m_Size.cx) - pPoint->x;
						m_ptDragOffset.y		=(m_Pos.y+m_Size.cy) - pPoint->y;
						::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
						return TRUE;
					}
				}

				if(m_bEnableDrag)
				{
					if(!PtInElement(*pPoint))
						break;
					m_bDraging	=TRUE;
					m_ptDragOffset.x	=m_Pos.x - pPoint->x;
					m_ptDragOffset.y	=m_Pos.y - pPoint->y;
					return TRUE;
				}
				
			}
			break;
		case WM_LBUTTONUP:
			{
				if(m_bAdjustSizeing)
				{
					m_bAdjustSizeing	=FALSE;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_SizeChanged(this);
					return TRUE;
				}
				if(m_bDraging)
				{
					m_bDraging	=FALSE;
					Invalidate(TRUE);
					if(m_pListener != NULL)
						m_pListener->OnElement_PosChanged(this);
					return TRUE;
				}
			}
			break;
		case WM_MOUSEMOVE:
			{
				if(!IsSelected())
					break;

				if(m_bAdjustSizeing)
				{
					POINT	pos;
					pos.x		=pPoint->x + m_ptDragOffset.x;
					pos.y		=pPoint->y + m_ptDragOffset.y;
					if(pos.x < (m_Pos.x+m_pVerticalScrollbar->GetSize()->cx*3) ||
						pos.y< (m_Pos.y+m_pHorizontalScrollbar->GetSize()->cy*3) )
					{
						m_bAdjustSizeing=FALSE;
						Invalidate(TRUE);
						return TRUE;
					}
					m_Size.cx	=(pos.x - m_Pos.x);
					m_Size.cy	=(pos.y - m_Pos.y);
					Invalidate(TRUE);
					::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
					return TRUE;
				}
				if(m_bDraging)
				{
					m_Pos.x		=pPoint->x + m_ptDragOffset.x;
					m_Pos.y		=pPoint->y + m_ptDragOffset.y;
					Invalidate(TRUE);
					return TRUE;
				}

				if(m_bEnableAdjustSize)
				{
					if(PtInAdjustSizeButton(pPoint))
						::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
				}
			}
			break;
		}
		return FALSE;
	}

	if(message == WM_KEYDOWN &&IsSelected())
	{
		switch(wParam)
		{
		case VK_LEFT:
			{
				m_Pos.x--;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_PosChanged(this);
				return TRUE;
			}
			break;
		case VK_RIGHT:
			{
				m_Pos.x++;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_PosChanged(this);
				return TRUE;
			}
			break;
		case VK_UP:
			{
				m_Pos.y--;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_PosChanged(this);
				return TRUE;
			}
			break;
		case VK_DOWN:
			{
				m_Pos.y++;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_PosChanged(this);
				return TRUE;
			}
			break;
		}
	}


	m_bDraging			=FALSE;
	m_bAdjustSizeing	=FALSE;

	if(m_pHorizontalScrollbar->OnWndMsg(message,wParam,lParam,pResult,pPoint))
	{
		m_DrawOffset.x	=m_pHorizontalScrollbar->GetPosition();
		Invalidate();
		return TRUE;
	}
	if(m_pVerticalScrollbar->OnWndMsg(message,wParam,lParam,pResult,pPoint))
	{
		m_DrawOffset.y	=m_pVerticalScrollbar->GetPosition();
		Invalidate();
		return TRUE;
	}
	if(!PtInElement(*pPoint))
		return FALSE;
	
	
	if(m_pHeader->OnWndMsg(message,wParam,lParam,pResult,pPoint))
		return TRUE;

	CODLEx_Element_ReportRow*	pRow	=NULL;
	LONG lStart,lEnd;
	GetNeedDrawRow(lStart,lEnd);
	for(LONG i=lStart;i<lEnd;i++)
	{
		pRow			=(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
		if(pRow->OnWndMsg(message,wParam,lParam,pResult,pPoint))
			return TRUE;
	}
	
	switch(message)
	{
	case WM_MOUSEWHEEL:
		{
			SHORT	delta	=HIWORD(wParam);
			m_pVerticalScrollbar->SetPosition(m_pVerticalScrollbar->GetPosition()-delta);
			Invalidate(TRUE);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
CODLEx_Element_Report*			CODLEx_Element_Report::SetPos(LONG IN x,LONG IN y)
{
	if(m_Pos.x == x && m_Pos.y == y)
		return this;
	m_Pos.x	=x;
	m_Pos.y	=y;
	Invalidate();
	return this;
}
POINT*							CODLEx_Element_Report::GetPos()
{
	return &m_Pos;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetSize(LONG IN cx,LONG IN cy)
{
	if(m_Size.cx == cx && m_Size.cy == cy)
		return this;
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
	return this;
}
SIZE*							CODLEx_Element_Report::GetSize()
{
	return &m_Size;
}
CODLEx_Element_Report*			CODLEx_Element_Report::SetRows(LONG IN lRows)
{
	LONG lCount		=m_theRowsList.GetCount();
	if(lCount == lRows)
		return this;
	LONG lCols	=m_pHeader->GetItemCount();

	CODLEx_Element_ReportRow*	pRow;
	if(lCount < lRows)
	{
		for(;lCount<lRows;lCount++)
		{
			pRow	=new CODLEx_Element_ReportRow(this,m_pCanvas);
			pRow->SetItemCount(lCols);
			pRow->SetSize(m_Size.cx,16);
			for(LONG i=0;i<lCols;i++)
			{
				pRow->SetItemWidth(i,m_pHeader->GetItem(i)->GetSize()->cx);
			}

			m_theRowsList.AddObj(pRow);
			pRow->Release();
		}
	}
	else
	{
		for(; lCount > lRows;lCount--)
		{
			DeleteRow(lCount-1);
		}
	}
	RecalcLayout();
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::DeleteRow(LONG IN lIndex)
{
	if(m_pCurrentSelected == m_theRowsList.GetObj(lIndex))
		m_pCurrentSelected = NULL;
	m_theRowsList.DelObj(lIndex);
	return this;
}

CODLEx_Element_Report*							CODLEx_Element_Report::SetCols(LONG IN lCols)
{
	if(m_pHeader->GetItemCount() == lCols)
		return this;
	m_pHeader->SetItemCount(lCols);

	CODLEx_Element_ReportRow*	pRow;
	for(LONG i=0;i<m_theRowsList.GetCount();i++)
	{
		pRow	 =(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
		pRow->SetItemCount(lCols);
	}
	RecalcLayout();
	Invalidate();

	return this;
}
LONG							CODLEx_Element_Report::GetRows()
{
	return m_theRowsList.GetCount();
}
LONG							CODLEx_Element_Report::GetCols()
{
	return m_pHeader->GetItemCount();
}
CODLEx_Element_Report*			CODLEx_Element_Report::ShowHeader(BOOL IN bShow)
{
	if(m_bShowHeader== bShow)
		return this;
	m_bShowHeader	=bShow;
	m_pHeader->Show(bShow);
	Invalidate();
	return this;
}
BOOL							CODLEx_Element_Report::IsShowHeader()
{
	return m_pHeader->IsShow();
}
CODLEx_Element_Report*			CODLEx_Element_Report::SetBkBrush(LOGBRUSH* IN lb)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush	=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(lb);
	Invalidate();
	return this;
}
CODL_Brush*						CODLEx_Element_Report::GetBkBrush()
{
	return m_pBkBrush;
}




CODLEx_Element_ScrollBar*		CODLEx_Element_Report::GetHorizontalScrollBar()
{
	return m_pHorizontalScrollbar;
}
CODLEx_Element_ScrollBar*		CODLEx_Element_Report::GetVerticalScrollBar()
{
	return m_pVerticalScrollbar;
}
CODLEx_Element_ReportRow*		CODLEx_Element_Report::GetHeader()
{
	return m_pHeader;
}
CODLEx_Element_ReportRow*		CODLEx_Element_Report::GetRow(LONG IN lRow)
{
	return (CODLEx_Element_ReportRow*)m_theRowsList.GetObj(lRow);
}
CODLEx_Element_ReportItem*		CODLEx_Element_Report::GetItem(LONG IN lRow,LONG IN lCol)
{
	CODLEx_Element_ReportRow*	pRow =GetRow(lRow);
	if(pRow != NULL)
		return pRow->GetItem(lCol);
	return NULL;
}
CODLEx_Element_ReportRow*		CODLEx_Element_Report::GetCurrentSelect()
{
	return m_pCurrentSelected;
}
VOID							CODLEx_Element_Report::SetCurrentSelect(CODLEx_Element_ReportRow* IN pRow)
{
	if(m_pCurrentSelected == pRow)
		return ;
	if(m_pCurrentSelected != NULL)
		m_pCurrentSelected->SetSelected(FALSE);

	m_pCurrentSelected	=pRow;

	if(m_pCurrentSelected != NULL)
		m_pCurrentSelected->SetSelected(TRUE);
}
CODLEx_Element_Report*							CODLEx_Element_Report::EnsureVisible(LONG IN lRowIndex,LONG IN lColIndex)
{
	if(lRowIndex >= m_theRowsList.GetCount())
		lRowIndex =m_theRowsList.GetCount()-1;
	if(lColIndex >= m_pHeader->GetItemCount())
		lColIndex =m_pHeader->GetItemCount()-1;

	LONG i=0;
	LONG x=0;
	LONG y=0;

	for(i=0;i<lRowIndex;i++)
		y += GetRow(i)->GetSize()->cy;

	for(i=0;i<lColIndex;i++)
		x += m_pHeader->GetItem(i)->GetSize()->cx;

	m_pHorizontalScrollbar->SetPosition(x);
	m_pVerticalScrollbar->SetPosition(y);

	Invalidate(TRUE);
	return this;
}

CODLEx_Element_Report*							CODLEx_Element_Report::SetRowBkBrush(LONG IN lRow,LOGBRUSH* IN lb)
{
	CODLEx_Element_ReportRow*	pRow	=GetRow(lRow);
	if(pRow == NULL)
		return this;
	pRow->SetDefaultBkBrush(lb);
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetColBkBrush(LONG IN lCol,LOGBRUSH* IN lb)
{
	CODLEx_Element_ReportItem*	pItem =NULL;
	for(LONG i=0;i<GetRows();i++)
	{
		pItem	=GetRow(i)->GetItem(lCol);
		if(pItem == NULL)
			return this;
		pItem->SetBkBrush(lb);
	}
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetRowFont(LONG IN lRow,LOGFONT* IN lf)
{
	CODLEx_Element_ReportRow*	pRow	=GetRow(lRow);
	if(pRow == NULL)
		return this;
	pRow->SetDefaultFont(lf);
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetColFont(LONG IN lCol,LOGFONT* IN lf)
{
	CODLEx_Element_ReportItem*	pItem =NULL;
	for(LONG i=0;i<GetRows();i++)
	{
		pItem	=GetRow(i)->GetItem(lCol);
		if(pItem == NULL)
			return this;
		pItem->SetFont(lf);
	}
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetRowTextColor(LONG IN lRow,COLORREF IN clr)
{
	CODLEx_Element_ReportRow*	pRow	=GetRow(lRow);
	if(pRow == NULL)
		return this;
	pRow->SetDefaultTextColor(clr);
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetColTextColor(LONG IN lCol,COLORREF IN clr)
{
	CODLEx_Element_ReportItem*	pItem =NULL;
	for(LONG i=0;i<GetRows();i++)
	{
		pItem	=GetRow(i)->GetItem(lCol);
		if(pItem == NULL)
			return this;
		pItem->SetTextColor(clr);
	}
	Invalidate();
	return this;
}



CODLEx_Element_ReportRow*		CODLEx_Element_Report::InsertRow(LONG IN lInsertBefore)
{
	CODLEx_Element_ReportRow*	pNewRow		=new CODLEx_Element_ReportRow(this,m_pCanvas);

	pNewRow->SetItemCount(m_pHeader->GetItemCount());
	for(LONG i=0;i<m_pHeader->GetItemCount();i++)
		pNewRow->SetItemWidth(i,m_pHeader->GetItem(i)->GetSize()->cx);

	m_theRowsList.InsertObj(lInsertBefore,pNewRow);
	pNewRow->Release();
	return pNewRow;
}
CODLEx_Element_Report*							CODLEx_Element_Report::InsertCol(LONG IN lInsertBefore)
{
	CODLEx_Element_ReportRow*	pRow;
	m_pHeader->InsertItem(lInsertBefore);
	for(LONG i=0;i<m_theRowsList.GetCount();i++)
	{
		pRow	 =(CODLEx_Element_ReportRow*)m_theRowsList.GetObj(i);
		pRow->InsertItem(lInsertBefore);
	}
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetRowHeight(LONG IN lRow,LONG IN lHeight)
{
	CODLEx_Element_ReportRow*	pRow =GetRow(lRow);
	if(pRow != NULL)
	{
		pRow->SetRowHeight(lHeight);
		Invalidate();
	}
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetColWidth(LONG IN lCol,LONG IN lWidth)
{
	m_pHeader->SetColWidth(lCol,lWidth);
	for(LONG i=0;i<GetRows();i++)
		GetRow(i)->SetColWidth(lCol,lWidth);
	Invalidate();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::EnableShowHorizontalGrid(BOOL IN bEnable)
{
	m_pHeader->EnableShowHorizontalGrid(bEnable);
	for(LONG i=0;i<GetRows();i++)
		GetRow(i)->EnableShowHorizontalGrid(bEnable);
	Invalidate();
	return this;

}
CODLEx_Element_Report*							CODLEx_Element_Report::EnableShowVerticalGrid(BOOL IN bEnable)
{
	m_pHeader->EnableShowVerticalGrid(bEnable);
	for(LONG i=0;i<GetRows();i++)
		GetRow(i)->EnableShowVerticalGrid(bEnable);
	Invalidate();
	return this;

}
CODLEx_Element_Report*							CODLEx_Element_Report::SetVerticalGridPen(LOGPEN* IN lp)
{
	CODL_Pen*	pPen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
	m_pHeader->SetVerticalGridPen(pPen);
	for(LONG i=0;i<GetRows();i++)
		GetRow(i)->SetVerticalGridPen(pPen);
	Invalidate();
	pPen->Release();
	return this;
}
CODLEx_Element_Report*							CODLEx_Element_Report::SetHorizontalGridPen(LOGPEN* IN lp)
{
	CODL_Pen*	pPen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
	m_pHeader->SetHorizontalGridPen(pPen);
	for(LONG i=0;i<GetRows();i++)
		GetRow(i)->SetHorizontalGridPen(pPen);
	Invalidate();
	pPen->Release();
	return this;
}






