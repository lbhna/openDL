#include "StdAfx.h"
#include ".\odlex_element_curvebase.h"
#include "./ODLEx_Element_Coordinate.h"
#include "./ODLEx_Element_CanvasTitle.h"
#include <afxtempl.h>

CODLEx_Element_CurveBase::CODLEx_Element_CurveBase(CODL_CanvasBase* IN pCanvas,CHAR* IN pName):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_CURVE;
	m_pName				=NULL;
	m_pLinePen			=NULL;
	m_DataPosition		=NULL;
	m_pSelectBrush		=NULL;
	m_vScale.x			=1.0f;
	m_vScale.y			=1.0f;
	m_pNameFont			=NULL;

	m_bEnableCull		=TRUE;
	m_bEnableAutoScroll =TRUE;

	m_bEnableLinkOverflow=FALSE;

	SetName(pName,"宋体",14);
}

CODLEx_Element_CurveBase::~CODLEx_Element_CurveBase(void)
{
	ODL_SafeRelease(m_pNameFont);
	ODL_SafeRelease(m_pLinePen);
	ODL_SafeDeleteArray(m_pName);
	ClearData();
}
VOID		CODLEx_Element_CurveBase::SetScale(FLOAT IN xScale,FLOAT IN yScale)
{
	m_vScale.x	=xScale;
	m_vScale.y	=yScale;
	Invalidate();
}

INT			CODLEx_Element_CurveBase::Init(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor)
{
	SetLineParameter(nLineStyle,nLineWidth,LineColor);

	COLORREF clr =RGB(255,255,255)- GetCanvas()->GetBkColor();
	m_pSelectBrush =GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,0);

	return 0;
}
VOID		CODLEx_Element_CurveBase::SetLineParameter(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(nLineStyle,nLineWidth,LineColor);

}

VOID		CODLEx_Element_CurveBase::SetLinePen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(lp);

}
VOID		CODLEx_Element_CurveBase::SetSelectBtnBrush(LOGBRUSH* IN lb)
{
	ODL_SafeRelease(m_pSelectBrush);
	m_pSelectBrush=GetCanvas()->GetView()->GetResourceManager()->CreateBrush(lb);
}
BOOL		CODLEx_Element_CurveBase::GetLineParameter(UINT& OUT nLineStyle,UINT& OUT nLineWidth,COLORREF& OUT LineColor)
{
	if(m_pLinePen == NULL)
		return FALSE;

	nLineWidth		=m_pLinePen->GetLogPen()->lopnWidth.x;
	nLineStyle		=m_pLinePen->GetLogPen()->lopnStyle;
	LineColor		=m_pLinePen->GetLogPen()->lopnColor;

	return TRUE;
}
VOID		CODLEx_Element_CurveBase::ScrollProc(LONG IN count)
{
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return;
	POINT				center;
	POSITION			pos		=m_theDataList.GetLastPosition();
	CODLEx_CurveData*	pData	=NULL;
	pCoord->GetCenter(center);
	pData	=m_theDataList.GetAt(pos);
	m_theDataList.MovePrev(pos);
	FLOAT	fLastX =pData->x;
	while(pos != NULL)
	{
		pData	=m_theDataList.GetAt(pos);
		
		if( (fLastX-pData->x) / pCoord->GetXUnitValue() >= count)
		{
			pCoord->AbsLocate(pData->x);
			break;
		}

		m_theDataList.MovePrev(pos);
	}
	
}

VOID		CODLEx_Element_CurveBase::AutoScrollCheck()
{
	if(m_theDataList.IsEmpty())
		return;
	if(!IsEnableAutoScroll())
		return;
	if(!GetCanvas()->IsEnableAutoScroll())
		return;
	if(GetCanvas()->GetSelected() != NULL)
		return;

	CODLEx_CurveData* pData =m_theDataList.GetAt(m_theDataList.GetLastPosition());
	if(pData == NULL)
		return;
	
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return;
	POINT center;
	pCoord->GetCenter(center);
	LONG	x	=pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
	if( x > GetCanvas()->GetSize()->cx)
	{
		LONG	unit_count = (GetCanvas()->GetSize()->cx -center.x) / pCoord->GetXPerUnitPixels();
		unit_count/=2;
		ScrollProc(unit_count);
	}
}

VOID		CODLEx_Element_CurveBase::AddData(FLOAT IN x,FLOAT IN y,DWORD IN flag)
{
	CODLEx_CurveData	data(x,y,flag);
	m_theDataList.AddTail(&data);
	if(IsShow())
		AutoScrollCheck();
}
VOID		CODLEx_Element_CurveBase::MoveLeft(LONG IN lCount)
{
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*) ( GetCanvas()->GetCoordinate() );
	if(pCoord == NULL)
		return;

	if(lCount > 0)
	{
		for(LONG i=0;i<lCount;i++)
		{
			m_theDataList.MovePrev(m_DataPosition);
		}
	}
	else
	{
		for(LONG i=0;i<abs(lCount);i++)
		{
			m_theDataList.MoveNext(m_DataPosition);
		}
	}
	Invalidate();
}
VOID		CODLEx_Element_CurveBase::MoveUp(LONG IN lCount)
{

}
VOID		CODLEx_Element_CurveBase::DrawName(HDC IN hDC,RECT* IN pPaintRect)
{
	if(!IsSelected())
		return;
	if(m_pName == NULL || m_pNameFont == NULL)
		return;

	m_pNameFont->Install(hDC);
	RECT	rec;
	rec.top		=pPaintRect->top;
	rec.bottom	=pPaintRect->top + m_pNameFont->GetTextMetrics()->tmHeight;
	rec.left	=pPaintRect->right- m_pNameFont->GetTextMetrics()->tmAveCharWidth*strlen(m_pName)-5;
	rec.right	=pPaintRect->right;

	m_pNameFont->SetTextColor(m_pLinePen->GetLogPen()->lopnColor);
	m_pNameFont->DrawText(&rec,m_pName,DT_VCENTER|DT_LEFT);

	m_pLinePen->Install(hDC);
	LONG x =rec.left-5;
	LONG y =rec.top + m_pNameFont->GetTextMetrics()->tmHeight/2;
	MoveToEx(hDC,x,y,NULL);
	LineTo(hDC,x-15,y);

	m_pLinePen->Uninstall(hDC);
	m_pNameFont->Uninstall(hDC);

}
typedef CArray<ODL_POINT,ODL_POINT>		POINTS_ARRAY,*PPOINTS_ARRAY;

BOOL		CODLEx_Element_CurveBase::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_pLinePen == NULL)
		return FALSE;
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*) ( GetCanvas()->GetCoordinate() );
	if(pCoord == NULL)
		return FALSE;
	if(m_theDataList.IsEmpty())
		return TRUE;

	LONG	lMinY=pPaintRect->top;
	CODLEx_Element_CanvasTitle* pTitle =(CODLEx_Element_CanvasTitle*)(GetCanvas()->GetCanvasTitle());
	if(pTitle != NULL)
	{
		if(pTitle->IsShow())
		{
			lMinY =pPaintRect->top + pTitle->GetTitleHeight();
		}
	}

	m_pLinePen->Install(hDC);
	LONG width	=m_pLinePen->GetLogPen()->lopnWidth.x;
	width += 2;

	POINT				center;
	CODLEx_CurveData*	pData;
	POSITION	pos		=m_DataPosition;
	if(pos == NULL)
	{
		pos				=m_theDataList.GetFirstPosition();
		m_DataPosition	=pos;
	}
	if(m_DataPosition != NULL)
	{
		pData	=m_theDataList.GetAt(m_DataPosition);
		if(pData->x < pCoord->GetXCenterUnitValue())
		{
			while(pData != NULL)
			{
				if(pData->x >= pCoord->GetXCenterUnitValue())
					break;
				m_theDataList.MoveNext(m_DataPosition);
				pData	=m_theDataList.GetAt(m_DataPosition);
			}
			if(m_DataPosition == NULL)
				m_DataPosition =m_theDataList.GetLastPosition();
		}
		else if(pData->x > pCoord->GetXCenterUnitValue())
		{
			while(pData != NULL)
			{
				if(pData->x <= pCoord->GetXCenterUnitValue())
					break;
				m_theDataList.MovePrev(m_DataPosition);
				pData	=m_theDataList.GetAt(m_DataPosition);
			}	
			if(m_DataPosition == NULL)
				m_DataPosition =m_theDataList.GetFirstPosition();
		}
	}
	pos		=m_DataPosition;


	pCoord->GetCenter(center);

	LONG	x	=center.x;
	LONG	y	=center.y;
	BOOL	bLocated =FALSE;
	POINTS_ARRAY				thePolyLine;
	ODL_POINT	cur_pt;
	RECT	cut_rect	=*pPaintRect;
	cut_rect.top		=lMinY+1;
	cut_rect.bottom		-=1;

	//正区间
	bLocated =FALSE;
	while( pos != NULL)
	{
		pData	=m_theDataList.GetAt(pos);
		
		x	= pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
		y	= pCoord->YValueToCoordSpacce(pData->y*m_vScale.y);

		if(m_bEnableCull)
		{
			if( x > pPaintRect->right)
				break;
		}

		if(m_bEnableLinkOverflow)
		{
			cur_pt.x =x;
			cur_pt.y =y;
			cur_pt.flag=pData->flag;
			thePolyLine.Add(cur_pt);
		}
		else
		{
			if(bLocated)
			{
				if(pData->flag ==1)
				{
					MoveToEx(hDC,x,y,NULL);
				}
				else if(pData->flag == 0)
				{
					LineTo(hDC,x,y);
				}
			}
			else
			{
				MoveToEx(hDC,x,y,NULL);
				bLocated =TRUE;
			}
			if(IsSelected())
			{

				RECT rec;
				rec.left	=x -width;
				rec.right	=x +width;
				rec.top		=y -width;
				rec.bottom	=y +width;
				FillRect(hDC,&rec,m_pSelectBrush->GetBrush());
			}
		}
		m_theDataList.MoveNext(pos);
	}

	//负区间
	bLocated=FALSE;
	pos		=m_DataPosition;
	while( pos != NULL)
	{
		pData	=m_theDataList.GetAt(pos);
		
		x	= pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
		y	= pCoord->YValueToCoordSpacce(pData->y*m_vScale.y);
		if(m_bEnableCull)
		{
			if(x < pPaintRect->left)
				break;
		}		
		
		if(m_bEnableLinkOverflow)
		{
			cur_pt.x =x;
			cur_pt.y =y;
			cur_pt.flag=pData->flag;
			thePolyLine.InsertAt(0,cur_pt);
		}
		else
		{
			if(bLocated)
			{
				if(pData->flag ==1)
				{
					MoveToEx(hDC,x,y,NULL);
				}
				else if(pData->flag == 0)
				{
					LineTo(hDC,x,y);
				}
			}
			else
			{
				MoveToEx(hDC,x,y,NULL);
				bLocated =TRUE;
			}

			if(IsSelected())
			{
				RECT rec;
				rec.left	=x -width;
				rec.right	=x +width;
				rec.top		=y -width;
				rec.bottom	=y +width;
				FillRect(hDC,&rec,m_pSelectBrush->GetBrush());
			}
		}
		m_theDataList.MovePrev(pos);
	}

	if(m_bEnableLinkOverflow)
	{
		ODL_POINT*	pResultPoints	=NULL;
		DWORD	dwCount			=CODL_Tools::RectCutPolyLine(&cut_rect,thePolyLine.GetData(),thePolyLine.GetSize(),&pResultPoints);
		for(DWORD i=0;i<dwCount;i++)
		{
			x =pResultPoints[i].x;
			y =pResultPoints[i].y;

			if(i==0)
				MoveToEx(hDC,x,y,NULL);
			else
			{
				if(pResultPoints[i].flag==0)
					LineTo(hDC,x,y);
				else
					MoveToEx(hDC,x,y,NULL);
			}

			if(IsSelected())
			{

				RECT rec;
				rec.left	=x -width;
				rec.right	=x +width;
				rec.top		=y -width;
				rec.bottom	=y +width;
				FillRect(hDC,&rec,m_pSelectBrush->GetBrush());
			}

		}
		ODL_SafeDeleteArray(pResultPoints);
	}
	m_pLinePen->Uninstall(hDC);

	//-------------------------------------------------
	//DrawName(hDC,pPaintRect);
	return TRUE;
}

VOID		CODLEx_Element_CurveBase::SetName(CHAR*  IN pName,CHAR* IN pFontName,DWORD IN dwFontSize)
{
	ODL_SafeDeleteArray(m_pName);
	DWORD	size= strlen(pName);
	m_pName		=new CHAR[size+1];
	ZeroMemory(m_pName,size);
	strcpy(m_pName,pName);

	ODL_SafeRelease(m_pNameFont);
	m_pNameFont		=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pFontName,dwFontSize);
	Invalidate();

}
BOOL		CODLEx_Element_CurveBase::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*) ( GetCanvas()->GetCoordinate() );
	if(pCoord == NULL)
		return FALSE;
	if(m_theDataList.IsEmpty())
		return FALSE;

	POINT				center;
	CODLEx_CurveData*	pData;
	POSITION	pos		=m_DataPosition;
	if(pos == NULL)
	{
		pos				=m_theDataList.GetFirstPosition();
		m_DataPosition	=pos;
	}


	pCoord->GetCenter(center);


	POINT	start,end;
	BOOL	bLocated =FALSE;
	while( pos != NULL)
	{
		pData	=m_theDataList.GetAt(pos);

		end.x	= pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
		end.y	= pCoord->YValueToCoordSpacce(pData->y*m_vScale.y);

		if(bLocated)
		{
			if(CODL_ElementBase::PtInLine(pt,start,end))
				return TRUE;
		}
		else
		{
			bLocated =TRUE;
		}
		if( end.x > m_CurPaintRect.right)
			break;
		start =end;
		m_theDataList.MoveNext(pos);
	}

	bLocated=FALSE;
	pos		=m_DataPosition;
	while( pos != NULL)
	{
		pData	=m_theDataList.GetAt(pos);

		end.x	= pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
		end.y	= pCoord->YValueToCoordSpacce(pData->y*m_vScale.y);
		if(bLocated)
		{
			if(CODL_ElementBase::PtInLine(pt,start,end))
				return TRUE;
		}
		else
		{
			bLocated =TRUE;
		}
		if( end.x > m_CurPaintRect.right)
			break;
		start =end;
		m_theDataList.MovePrev(pos);
	}



	return FALSE;
}
BOOL		CODLEx_Element_CurveBase::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	switch(message)
	{
	case WM_RBUTTONDOWN:
		{
			if(IsSelected())
			{
				if(!IsControlSwitchKeyPressed())
					return FALSE;
				POINT	point;
				POINTS	pt	=MAKEPOINTS(lParam);
				point.x		=pt.x;
				point.y		=pt.y;
				if(PtInElement(*pPoint))
				{
					PopupMenu();
					return TRUE;
				}
			}

		}
		break;
	}
	return FALSE;
}
CODLEx_CurveData*CODLEx_Element_CurveBase::GetDataByXIndicate(LONG IN lIndicate)
{
	POSITION pos =m_DataPosition;
	if(lIndicate > 0)
	{
		for(LONG i=0;i<lIndicate;i++)
		{
			m_theDataList.MoveNext(pos);
		}
	}
	else
	{
		for(LONG i=0;i<abs(lIndicate);i++)
		{
			m_theDataList.MovePrev(pos);
		}
	}

	return m_theDataList.GetAt(pos);
}
VOID				CODLEx_Element_CurveBase::EnableLinkOverflow(BOOL IN bEnable)
{
	m_bEnableLinkOverflow	=bEnable;
	Invalidate();
}
