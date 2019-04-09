#include "stdafx.h"
#include "ODLEx_Element_DropPoint.h"
#include "./ODLEx_Element_Coordinate.h"



CODLEx_Element_DropPoint::CODLEx_Element_DropPoint(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_pPointName		=new CHAR[32];
	strcpy(m_pPointName,"落点");
	m_pPointBrush		=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,50,50),NULL);
	
	m_dwPointRadius		=4;
	m_vOffset.x			=0.0f;
	m_vOffset.y			=0.0f;

	m_bShowLabel		=FALSE;	//是否显示标牌
	m_pLabel			=NULL;
	m_bPosChanged		=TRUE;
	m_LabelOffset.x		=50;
	m_LabelOffset.y		=-150;
	m_PointOldPos.x		=0;
	m_PointOldPos.y		=0;
}

CODLEx_Element_DropPoint::~CODLEx_Element_DropPoint()
{
	delete []m_pPointName;
	ODL_SafeRelease(m_pPointBrush);
	ODL_SafeRelease(m_pLabel);
}
VOID				CODLEx_Element_DropPoint::SetPointColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pPointBrush);
	m_pPointBrush		=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,NULL);
	Invalidate();
}
COLORREF			CODLEx_Element_DropPoint::GetPointColor()
{
	return m_pPointBrush->GetLogBrush()->lbColor;
}
VOID				CODLEx_Element_DropPoint::SetDropPointRadius(DWORD IN dwRadius)
{
	m_dwPointRadius		=dwRadius;
	Invalidate();
}
	
VOID				CODLEx_Element_DropPoint::SetDropPointName(CHAR* IN pName)
{
	if(pName == NULL)
		return;

	delete []m_pPointName;
	m_pPointName	=new CHAR[strlen(pName)+1];
	strcpy(m_pPointName,pName);
	Invalidate();
}

VOID				CODLEx_Element_DropPoint::SetOffset(FLOAT IN fAt/*前向为正*/,FLOAT IN fLeft/*左向为正*/)
{
	m_vOffset.x		=fAt;
	m_vOffset.y		=fLeft;

	m_bPosChanged	=TRUE;
	if(m_pLabel != NULL)
	{
		char info[32];
		
		sprintf(info,"%.2f米",m_vOffset.y);
		m_pLabel->SetText(0,1,info);
		
		sprintf(info,"%.2f米",m_vOffset.x);
		m_pLabel->SetText(1,1,info);
	}
	Invalidate();
}
BOOL		CODLEx_Element_DropPoint::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT	rect;
	GetDropPointRect(rect);
	if(m_pLabel != NULL)
	{
		m_pLabel->SetAnchorPos(m_PointOldPos.x,m_PointOldPos.y);
		if(m_bPosChanged)
		{
			m_pLabel->SetPos(m_PointOldPos.x+m_LabelOffset.x,m_PointOldPos.y+m_LabelOffset.y);	
			m_bPosChanged=FALSE;
		}	
	}

	


	//画点-----------------------------------------------------
	m_pPointBrush->Install(hDC);
	SelectObject(hDC,(HGDIOBJ)NULL_BRUSH);
	
	Ellipse(hDC,rect.left,rect.top,rect.right,rect.bottom);
	
	m_pPointBrush->Uninstall(hDC);
	//-----------------------------------------------------
	
	return TRUE;
}
BOOL		CODLEx_Element_DropPoint::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_MOUSEMOVE:
		{
			
		}
		break;
	case WM_LBUTTONDOWN:
		{
			RECT	rect;
			GetDropPointRect(rect);
			if(PtInRect(&rect,*pPoint))
			{
				if(m_bShowLabel)
				{
					ShowLabel(FALSE);					
				}
				else
				{
					ShowLabel(TRUE);
				}
				Invalidate(TRUE);
				return TRUE;
			}
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			RECT	rect;
			GetDropPointRect(rect);
			if(PtInRect(&rect,*pPoint))
			{
				m_bPosChanged=TRUE;
				m_LabelOffset.x		=50;
				m_LabelOffset.y		=-150;
				ShowLabel(m_bShowLabel);	
				Invalidate(TRUE);
				return TRUE;			
			}	
		}
		break;
	}
	return FALSE;
}
VOID		CODLEx_Element_DropPoint::GetDropPointRect(RECT& OUT rect)
{
	POINT		pt;	
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
	
	pt.x	= pCoord->XValueToCoordSpacce(m_vOffset.x);
	pt.y	= pCoord->YValueToCoordSpacce(m_vOffset.y);
	
	rect.left	=pt.x-m_dwPointRadius;
	rect.top	=pt.y-m_dwPointRadius;
	rect.right	=pt.x+m_dwPointRadius;
	rect.bottom	=pt.y+m_dwPointRadius;	


	if(m_PointOldPos.x != pt.x || m_PointOldPos.y != pt.y)
	{
		m_PointOldPos.x =pt.x;
		m_PointOldPos.y	=pt.y;
		m_bPosChanged	=TRUE;
	}
	
}
VOID		CODLEx_Element_DropPoint::ShowLabel(BOOL IN bShow)
{
	POINT		center;
	POINT		pt;	
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
	pt.x	= pCoord->XValueToCoordSpacce(m_vOffset.x);
	pt.y	= pCoord->YValueToCoordSpacce(m_vOffset.y);

	
	if(m_pLabel == NULL)
	{
		m_pLabel	=new CODLEx_Element_Label(m_pCanvas);
		m_pCanvas->AddObj(m_pLabel);
		m_pLabel->SetListener(this);

		m_pLabel->Init(2,2);

		for(DWORD i=0;i<2;i++)
		{
			for(DWORD j=0;j<2;j++)
			{
				m_pLabel->SetTextFont(i,j,"宋体",12,500);
				m_pLabel->SetTextColor(i,j,RGB(50,50,250));
			}
		}
		m_pLabel->SetAlpha(185);//透明度
		m_pLabel->SetZIndex(100);//图层号
		m_pLabel->SetBkColor(RGB(255,220,150));
		m_pLabel->SetBorderStyle(PS_SOLID,1,RGB(200,255,255));
	}	
	m_pLabel->SetAnchorPos(pt.x,pt.y);

	if(m_bPosChanged)
	{
		m_pLabel->SetPos(pt.x+m_LabelOffset.x,pt.y+m_LabelOffset.y);	
	}
	

	m_bShowLabel	=bShow;
	m_pLabel->Show(m_bShowLabel);

	m_pLabel->ShowTitle(TRUE);
	
	m_pLabel->SetTitle(m_pPointName);

	char info[32];
	m_pLabel->SetText(0,0,"横向偏移量");
	
	sprintf(info,"%.2f米",m_vOffset.y);
	m_pLabel->SetText(0,1,info);

	m_pLabel->SetText(1,0,"纵向偏移量");

	sprintf(info,"%.2f米",m_vOffset.x);
	m_pLabel->SetText(1,1,info);
	
}
VOID			CODLEx_Element_DropPoint::OnElement_PosChanged(CODL_ElementBase* IN pElement)
{
	if(m_pLabel != pElement || m_pLabel == NULL)
		return;

	POINT		pt;	
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
	pt.x	= pCoord->XValueToCoordSpacce(m_vOffset.x);
	pt.y	= pCoord->YValueToCoordSpacce(m_vOffset.y);

	m_LabelOffset.x		=m_pLabel->GetPos()->x - pt.x;
	m_LabelOffset.y		=m_pLabel->GetPos()->y - pt.y;
	m_bPosChanged		=TRUE;
}
POINT*				CODLEx_Element_DropPoint::GetLabelOffset()
{
	return &m_LabelOffset;
}
VOID				CODLEx_Element_DropPoint::SetLabelOffset(LONG IN x,LONG IN y)
{
	if(m_LabelOffset.x == x && m_LabelOffset.y == y)
		return ;
	m_LabelOffset.x =x;
	m_LabelOffset.y =y;
	m_bPosChanged		=TRUE;
	Invalidate();
}
