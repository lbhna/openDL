#include "stdafx.h"
#include "ODLEx_Element_DiagramPreview.h"
#include "ODLEx_Element_CurveBase.h"
#include "ODLEx_Element_CurveCase.h"

CODLEx_Element_DiagramPreview::CODLEx_Element_DiagramPreview(CODL_CanvasBase* IN pCanvas):
CODL_OverlayElementBase(pCanvas)
{
	m_Pos.x				=0;
	m_Pos.y				=0;
	m_Size.cx			=0;
	m_Size.cy			=0;
	m_CaseSize.cx		=0;
	m_CaseSize.cy		=0;
	m_bDraging			=FALSE;
	m_DragOffset.x		=0;
	m_DragOffset.y		=0;
	m_Alpha				=155;
	m_pBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(100,100,100),0);
	m_bNeedResetCase	=TRUE;

	m_lLineBlank		=5;
	m_lMargin			=5;
	m_bEnableSelect		=FALSE;
	m_lTitleHeight		=5;
	m_bShowLastDataText	=TRUE;
}

CODLEx_Element_DiagramPreview::~CODLEx_Element_DiagramPreview()
{
	m_CaseList.Clear();
	ODL_SafeRelease(m_pBrush);
}
VOID		CODLEx_Element_DiagramPreview::SetBkColor(COLORREF IN clr)
{
	m_pBrush			=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,0);
}
VOID		CODLEx_Element_DiagramPreview::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
}
VOID		CODLEx_Element_DiagramPreview::EnableShowLastDataText(BOOL IN bEnable)
{
	if(m_bShowLastDataText == bEnable)
		return;
	m_bShowLastDataText	=bEnable;
	
	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		pCase->EnableShowLastDataText(m_bShowLastDataText);
	}

}

VOID		CODLEx_Element_DiagramPreview::Reset(HDC IN hDC)
{
	m_CaseList.Clear();

	CODLEx_Element_CurveCase*	pCase		=NULL;
	CODL_ElementBase*			pElement	=NULL;
	CODLEx_Element_CurveBase*	pCurve		=NULL;
	for(LONG i=0;i<GetCanvas()->GetCount();i++)
	{
		pElement	=(CODL_ElementBase*)GetCanvas()->GetObj(i);
		if(pElement->GetType() == ODL_ELEMENT_CURVE)
		{
			pCurve	=(CODLEx_Element_CurveBase*)pElement;
			pCase	=new CODLEx_Element_CurveCase(GetCanvas());
			pCase->Init(hDC,pCurve);
			pCase->EnableShowLastDataText(m_bShowLastDataText);
			m_CaseList.AddObj(pCase);
			pCase->Release();
		}
	}

}

BOOL		CODLEx_Element_DiagramPreview::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_bNeedResetCase)
	{
		Reset(hDC);
		m_bNeedResetCase=FALSE;
	}

	RECT bound;
	GetElementBound(hDC,pPaintRect,bound);

	FillRect(hDC,&bound,m_pBrush->GetBrush());
	
	POINT	pos;
	pos.x	=m_Pos.x + m_lMargin;
	pos.y	=m_Pos.y + m_lMargin + m_lTitleHeight;


	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		pCase->SetPos(pos.x,pos.y);
		pCase->Draw(hDC,pPaintRect);

		pos.y += m_CaseSize.cy + m_lLineBlank;
	}

	return TRUE;
}
BOOL		CODLEx_Element_DiagramPreview::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		if(pCase->OnWndMsg(message,wParam,lParam,pResult,pPoint))
			return TRUE;
	}
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			if(!PtInElement(*pPoint))
				return FALSE;
			if(!m_bDraging)
			{
				m_bDraging =TRUE;
				m_DragOffset.x	=m_Pos.x - pPoint->x;
				m_DragOffset.y	=m_Pos.y - pPoint->y;
				return TRUE;
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			if(!PtInElement(*pPoint))
				return FALSE;
			if(m_bDraging)
			{
				m_bDraging	=FALSE;
				return TRUE;
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!m_bDraging)
				return FALSE;
			
			SetPos(pPoint->x + m_DragOffset.x , pPoint->y + m_DragOffset.y);

			return TRUE;
		}
		break;
	}

	return FALSE;

}
VOID		CODLEx_Element_DiagramPreview::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	SIZE	size;
	size.cx		=size.cy	=0;

	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		size.cx	=max(size.cx,pCase->GetSize()->cx);
		size.cy =max(size.cy,pCase->GetSize()->cy);
	}

	m_CaseSize		=size;

	boundRect.left	=m_Pos.x;
	boundRect.right =m_Pos.x + size.cx + m_lMargin*2;
	boundRect.top	=m_Pos.y;
	boundRect.bottom=m_Pos.y + size.cy*m_CaseList.GetCount() + m_lLineBlank*(m_CaseList.GetCount()-1) + m_lMargin*2;

	boundRect.bottom+=m_lTitleHeight;

	m_Size.cx		=boundRect.right-boundRect.left;
	m_Size.cy		=boundRect.bottom-boundRect.top;
}
VOID		CODLEx_Element_DiagramPreview::Invalidate(BOOL IN bFlushView)
{
	m_bInvalidate		=TRUE;
	m_bNeedResetCase	=TRUE;
	GetCanvas()->Invalidate(FALSE);
	if(bFlushView)
		GetCanvas()->GetView()->Invalidate();

}
BOOL		CODLEx_Element_DiagramPreview::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	rect.left	=m_Pos.x;
	rect.right	=m_Pos.x+m_Size.cx;
	rect.top	=m_Pos.y;
	rect.bottom	=m_Pos.y+m_Size.cy;
	return PtInRect(&rect,pt);
}	//设置图例颜色（正常色，选中色)
VOID				CODLEx_Element_DiagramPreview::SetCaseTextColor(COLORREF IN normalColor,COLORREF IN selectedColor)
{
	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		pCase->SetColor(normalColor,selectedColor);
	}
	Invalidate();
}
//设置图例字体
VOID				CODLEx_Element_DiagramPreview::SetCaseFont(LPCSTR IN pFontName,UINT IN uFontSize)
{
	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		pCase->SetFont(pFontName,uFontSize);
	}
	Invalidate();
}
//设置图例线长
VOID				CODLEx_Element_DiagramPreview::SetCaseLineLength(LONG IN lLen)
{
	CODLEx_Element_CurveCase* pCase =NULL;
	for(LONG i=0;i<m_CaseList.GetCount();i++)
	{
		pCase	=(CODLEx_Element_CurveCase*)m_CaseList.GetObj(i);
		pCase->SetCaseLineLength(lLen);
	}
	Invalidate();
}
