#include "stdafx.h"
#include "ODLEx_Element_AdjustLineContainer.h"

CODLEx_Element_AdjustLineContainer::CODLEx_Element_AdjustLineContainer(CODL_CanvasBase* IN pCanvas)
	:CODL_ElementBase(pCanvas)
{
}

CODLEx_Element_AdjustLineContainer::~CODLEx_Element_AdjustLineContainer(void)
{
}

VOID	CODLEx_Element_AdjustLineContainer::AddDataLine(CODLEx_Element_AdjustLine* pLine)
{
	if(pLine == NULL)
		return;
	m_theLines.AddObj(pLine);
}

BOOL	CODLEx_Element_AdjustLineContainer::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	BOOL bRet = FALSE;
	CPoint pt;
	pt.x = pPoint->x;
	pt.y = pPoint->y;
	CODLEx_Element_AdjustLine*	pLine =NULL;
	CODLEx_Element_AdjustLine*	pOtherLine =NULL;

	if(message == WM_LBUTTONDOWN)
	{
		BOOL bHit = FALSE;
		for(LONG i=0;i < m_theLines.GetCount();i++)
		{
			pLine = (CODLEx_Element_AdjustLine*)m_theLines.GetObj(i);
			if(!bHit && pLine->HitTest(pt))
			{
				pLine->OnWndMsg(message,wParam,lParam,pResult,pPoint);
				bHit = TRUE;
			}	
			else
			{
				pLine->CancelSelect(FALSE);
			}
		}
		if(bHit)
			return TRUE;
		//没有选中,会导致加点
		for(LONG j=0;j < m_theLines.GetCount();j++)
		{
			pLine = (CODLEx_Element_AdjustLine*)m_theLines.GetObj(j);
			bRet = pLine->OnWndMsg(message,wParam,lParam,pResult,pPoint)|| bRet;
		}	
		return bRet;
	}
	//其他消息
	for(LONG i=0;i<m_theLines.GetCount();i++)
	{
		pLine	 =(CODLEx_Element_AdjustLine*)m_theLines.GetObj(i);
		int index = pLine->GetSelectIndex();
		CODLEx_CurveData data ;
		if(index >= 0)
		{
			data = *pLine->GetCurveDataData(index);
		}
		//
		if(pLine->OnWndMsg(message,wParam,lParam,pResult,pPoint))
		{
			if(message == WM_MOUSEMOVE)
			{
				for(LONG j=0;j<m_theLines.GetCount();j++)
				{
					pOtherLine	 =(CODLEx_Element_AdjustLine*)m_theLines.GetObj(j);
					if(pOtherLine == pLine)
						continue;;
					CODLEx_CurveData* pOtherData = pOtherLine->GetCurveDataData(index);
					if(pOtherData == NULL)
						ASSERT(FALSE);
					pOtherLine->MoveDataX(pOtherData->x,data.x,TRUE);
				}
				return true;
			}
			else if(message == WM_KEYDOWN && wParam == VK_DELETE)
			{
				for(LONG j=0;j<m_theLines.GetCount();j++)
				{
					pOtherLine	 =(CODLEx_Element_AdjustLine*)m_theLines.GetObj(j);
					if(pOtherLine == pLine)
						continue;	
					pOtherLine->CancelSelect(FALSE);
					pOtherLine->DeleteDataByIndex(index,FALSE);
				}
				return true;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL	CODLEx_Element_AdjustLineContainer::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	CODLEx_Element_AdjustLine* pLine;
	for(LONG j = m_theLines.GetCount()-1;j>=0;j--)
	{
		pLine	 =(CODLEx_Element_AdjustLine*)m_theLines.GetObj(j);
		pLine->Draw(hDC,pPaintRect);
	}
	return true;
}

CODLEx_Element_AdjustLine*		CODLEx_Element_AdjustLineContainer::GetLine(int index)
{
	if(index > m_theLines.GetCount()-1)
		return NULL;
	return (CODLEx_Element_AdjustLine*)m_theLines.GetObj(index);
}

int			CODLEx_Element_AdjustLineContainer::GetLineIndex(CODLEx_Element_AdjustLine* pLine)
{
	for(LONG i=0;i<m_theLines.GetCount();i++)
	{
		if(m_theLines.GetObj(i) == pLine)
			return i;
	}
	return -1;
}
















































