#include "StdAfx.h"
#include ".\odlex_element_histogram.h"


CODLEx_Element_HistogramData::CODLEx_Element_HistogramData(CODLEx_Element_Histogram* pHistogram)
{
  m_pHistogram = pHistogram;
  x = 0.0f;
  y = 0.0f;
  m_pFramePen = NULL;
  m_pBrush = NULL;
}
CODLEx_Element_HistogramData::~CODLEx_Element_HistogramData()
{
  ODL_SafeRelease(m_pBrush);
  ODL_SafeRelease(m_pFramePen);
}
VOID	CODLEx_Element_HistogramData::SetData(FLOAT IN fx, FLOAT IN fy)
{
  x = fx;
  y = fy;
}
VOID	CODLEx_Element_HistogramData::SetFramePen(CODL_Pen* IN pPen)
{
  if(m_pFramePen == pPen)
    return;
  ODL_SafeRelease(m_pBrush);
  m_pFramePen = pPen;
  if(m_pFramePen != NULL)
    m_pFramePen->AddRef();

}
VOID	CODLEx_Element_HistogramData::SetBrush(CODL_Brush* IN pBrush)
{
  if(m_pBrush == pBrush)
    return;
  ODL_SafeRelease(m_pBrush);
  m_pBrush = pBrush;
  if(m_pBrush != NULL)
    m_pBrush->AddRef();
}
VOID	CODLEx_Element_HistogramData::Draw(HDC IN hDC, LONG IN x, LONG IN y, POINT IN center, CODLEx_Element_Coordinate* IN pCoord)
{
  if(m_pFramePen == NULL || m_pBrush == NULL)
    return;

  LONG	bottom = pCoord->YValueToCoordSpacce(0);
  if(pCoord->GetXPerUnitPixels() <= 1)
  {
    m_pFramePen->Install(hDC);
    MoveToEx(hDC, x, bottom, NULL);
    LineTo(hDC, x, y);
    m_pFramePen->Uninstall(hDC);
    return;
  }

  RECT		rect;
  //rect.left = x - (pCoord->GetXPerUnitPixels() / 4)*m_pHistogram->GetSizeScale().x;
  //rect.right = x + (pCoord->GetXPerUnitPixels() / 4)*m_pHistogram->GetSizeScale().x;
  x -= (pCoord->GetXPerUnitPixels() / 4)*(m_pHistogram->GetSizeScale().x-1.0f);

  rect.left = x;
  rect.right = x + (pCoord->GetXPerUnitPixels() / 2)*m_pHistogram->GetSizeScale().x;
  rect.top = y;
  rect.bottom = bottom;

  FillRect(hDC, &rect, m_pBrush->GetBrush());

  m_pFramePen->Install(hDC);

  MoveToEx(hDC, rect.left, rect.top, NULL);
  LineTo(hDC, rect.right, rect.top);
  LineTo(hDC, rect.right, rect.bottom);
  LineTo(hDC, rect.left, rect.bottom);
  LineTo(hDC, rect.left, rect.top);

  m_pFramePen->Uninstall(hDC);

}

//---------------------------------------------------------------------------------------
CODLEx_Element_Histogram::CODLEx_Element_Histogram(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_HISTROGRAM;
  m_vScale      = CODL_Vector2f(1.0f, 1.0f);
  m_vSizeScale  = CODL_Vector2f(1.0f, 1.0f);
  m_DataPosition = NULL;//数据起始位置,相对于坐标原点
}

CODLEx_Element_Histogram::~CODLEx_Element_Histogram(void)
{
	ClearData();
}
BOOL		CODLEx_Element_Histogram::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_DataPosition == NULL)
	{
		m_DataPosition	=m_theDataList.GetFirstPosition();
	}

	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return FALSE;

	POINT			center;
	pCoord->GetCenter(center);

	POSITION		pos		=NULL;
	CODLEx_Element_HistogramData*	pData	=NULL;
	LONG			x,y;
	//-------------------------------------------------------
	pos	=m_DataPosition;
	while( pos != NULL)
	{
		pData	=*m_theDataList.GetAt(pos);

		
		x	= pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
		y	= pCoord->YValueToCoordSpacce(pData->y*m_vScale.y);

		
		if(x > pPaintRect->right)
			break;

		pData->Draw(hDC,x,y,center,pCoord);

		m_theDataList.MoveNext(pos);
	}
	//-------------------------------------------------------
	pos =m_DataPosition;
	while(pos != NULL)
	{
		pData	=*m_theDataList.GetAt(pos);
		
		x	= pCoord->XValueToCoordSpacce(pData->x*m_vScale.x);
		y	= pCoord->YValueToCoordSpacce(pData->y*m_vScale.y);

		if(x < pPaintRect->left)
			break;

		pData->Draw(hDC,x,y,center,pCoord);
		m_theDataList.MovePrev(pos);
	}
	//-------------------------------------------------------


	return TRUE;
}
BOOL		CODLEx_Element_Histogram::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{



	return FALSE;
}
VOID		CODLEx_Element_Histogram::MoveLeft(LONG IN lCount)
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



VOID		CODLEx_Element_Histogram::ScrollProc(LONG IN count)
{
	CODLEx_Element_Coordinate*	pCoord =(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return;
	POINT				center;
	POSITION			pos		=m_theDataList.GetLastPosition();
	CODLEx_Element_HistogramData*		pData	=NULL;
	pCoord->GetCenter(center);
	pData	=*m_theDataList.GetAt(pos);
	m_theDataList.MovePrev(pos);
	FLOAT	fLastX =pData->x;
	while(pos != NULL)
	{
		pData	=*m_theDataList.GetAt(pos);
		
		if( (fLastX-pData->x) / pCoord->GetXUnitValue() >= count)
		{
			pCoord->AbsLocate(pData->x);
			break;
		}
		
		m_theDataList.MovePrev(pos);
	}
	
}
VOID		CODLEx_Element_Histogram::SetScale(FLOAT IN x,FLOAT IN y)
{
	m_vScale.x	=x;
	m_vScale.y	=y;
	Invalidate();
}
VOID     CODLEx_Element_Histogram::SetSizeScale(FLOAT IN x, FLOAT IN y)
{
  m_vSizeScale.x = x;
  m_vSizeScale.y = y;
  Invalidate();
}

VOID		CODLEx_Element_Histogram::AutoScrollCheck()
{
	if(m_theDataList.IsEmpty())
		return;
	if(!IsEnableAutoScroll())
		return;
	if(!GetCanvas()->IsEnableAutoScroll())
		return;
	if(GetCanvas()->GetSelected() != NULL)
		return;
	
	CODLEx_Element_HistogramData* pData =*m_theDataList.GetAt(m_theDataList.GetLastPosition());
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


VOID		CODLEx_Element_Histogram::AddData(FLOAT IN x,FLOAT IN y,CODL_Pen* IN pFramePen,CODL_Brush* IN pBrush)
{

	CODLEx_Element_HistogramData*	pData	=new CODLEx_Element_HistogramData(this);
	pData->SetData(x,y);
	pData->SetFramePen(pFramePen);
	pData->SetBrush(pBrush);
	m_theDataList.AddTail(&pData);
	if(IsShow())
		AutoScrollCheck();

}
VOID		CODLEx_Element_Histogram::AddData(FLOAT IN x,FLOAT IN y,LOGPEN* IN lp,LOGBRUSH* IN lb)
{
	CODL_Pen*	pPen	=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
	CODL_Brush*	pBrush	=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(lb);
	AddData(x,y,pPen,pBrush);
	pPen->Release();
	pBrush->Release();
}
VOID		CODLEx_Element_Histogram::AddData(FLOAT IN x,FLOAT IN y,COLORREF IN clrFrame,COLORREF IN clrBk)
{
	LOGPEN	lp;
	lp.lopnColor	=clrFrame;
	lp.lopnStyle	=PS_SOLID;
	lp.lopnWidth.x	=1;
	lp.lopnWidth.y	=1;
	LOGBRUSH lb;
	lb.lbStyle	=BS_SOLID;
	lb.lbHatch	=0;
	lb.lbColor	=clrBk;
	AddData(x,y,&lp,&lb);
}
VOID		CODLEx_Element_Histogram::ClearData()
{
	CODLEx_Element_HistogramData*	pData=NULL;
	POSITION						pos	=m_theDataList.GetFirstPosition();
	while( pos != NULL)
	{
		pData	=*m_theDataList.GetAt(pos);
		delete pData;
		m_theDataList.MoveNext(pos);
	}
	m_theDataList.DestroyList();
	m_DataPosition	=NULL;
}



