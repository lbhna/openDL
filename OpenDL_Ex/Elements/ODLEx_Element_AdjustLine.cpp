#include "stdafx.h"
#include "./ODLEx_Element_AdjustLine.h"
#include "ODLEx_Element_Coordinate.h"

CODLEx_Element_AdjustLine::CODLEx_Element_AdjustLine(CODL_CanvasBase* IN pCanvas,BOOL bLock):
CODL_ElementBase(pCanvas)
{
	m_pTextFont			=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",12);
	m_TextBkColor		=RGB(0,50,50);
	m_TextColor			=RGB(0,255,255);
	m_dwLastSelect		= -1;
	m_bPressed			=FALSE;
	m_bEnableClickAdd	=TRUE;
	m_dwPointRadius		=8;
	m_pSelectBrush		=NULL;
	m_pLinePen			=NULL;
	m_bMaxX = m_bMinY = m_bMaxY = m_bMinX = FALSE;
	m_fMaxX = m_fMaxY = m_fMinY =  m_fMinX = 0.0;
	m_bLockFirstXatZero	=	bLock;
	m_bFilterLBDBLCLK	 =FALSE;
	m_bTrueFalseStyle	= FALSE;
	m_bXinteger			=FALSE;
	m_bEnable			=FALSE;
	Init();
}

CODLEx_Element_AdjustLine::~CODLEx_Element_AdjustLine()
{
	ODL_SafeRelease(m_pLinePen);
	ODL_SafeRelease(m_pTextFont);
}

VOID		CODLEx_Element_AdjustLine::SetColor(COLORREF IN clr)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,clr);
	ODL_SafeRelease(m_pSelectBrush);
	m_pSelectBrush = GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,clr,NULL);
	Invalidate();
}

VOID		CODLEx_Element_AdjustLine::SetPointRadius(DWORD IN dwRadius)
{

}

BOOL		CODLEx_Element_AdjustLine::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_theDataList.GetLength() == 0)
		return TRUE;
	m_pLinePen->Install(hDC);
	m_theDrawDataList.ClearList();
	POINT pt;
	BOOL bHead = TRUE;
	POSITION pos = m_theDataList.GetFirstPosition();
	while(pos != NULL)
	{
		CODLEx_CurveData* pData = m_theDataList.GetAt(pos);
		if(bHead)
		{
			pt.x = XValueToCoordSpacce(pData->x);
			pt.y = YValueToCoordSpacce(pData->y);
			MoveToEx(hDC,pt.x,pt.y,NULL);
		}
		else
		{
			if(m_bTrueFalseStyle)
			{
				pt.x = XValueToCoordSpacce(pData->x);
				LineTo(hDC,pt.x,pt.y);
				pt.y = YValueToCoordSpacce(pData->y);
				LineTo(hDC,pt.x,pt.y);		
			}
			else
			{
				pt.x = XValueToCoordSpacce(pData->x);
				pt.y = YValueToCoordSpacce(pData->y);
				LineTo(hDC,pt.x,pt.y);
			}
		}
		bHead = FALSE;
		m_theDataList.MoveNext(pos);
		//
		m_theDrawDataList.AddTail(&pt);
	}
	LineTo(hDC,pPaintRect->right,pt.y);
	//
	int off = m_dwPointRadius/2;
	int index = 0;
	pos = m_theDrawDataList.GetFirstPosition();
	while(pos != NULL)
	{
		pt = *m_theDrawDataList.GetAt(pos);
		if(index == m_dwLastSelect)
		{
			RECT rect;
			rect.left = pt.x-off;
			rect.top = pt.y - off;
			rect.right = pt.x + off;
			rect.bottom = pt.y + off;
			FillRect(hDC,&rect,m_pSelectBrush->GetBrush());
		}
		else
		{
			Rectangle(hDC,pt.x-off,pt.y-off,pt.x+off,pt.y+off);
		}
		index++;
		m_theDrawDataList.MoveNext(pos);	
	}
	m_pLinePen->Uninstall(hDC);	
	return TRUE;
}

BOOL		CODLEx_Element_AdjustLine::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(!m_bEnable)
		return FALSE;
	if(m_theDataList.GetLength()== 0 && !m_bEnableClickAdd)
		return FALSE;	

	CODLEx_Element_Coordinate* pCorrd = (CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCorrd == NULL)
		return FALSE;

	BOOL bRet = FALSE;
	POINT	point= *pPoint;
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			bRet = OnLButtonDown(point);
		}
		break;
	case WM_MOUSEMOVE:
		{
			bRet = OnMouseMove(point);
		}
		break;
	case WM_LBUTTONUP:
		{
			bRet = OnLButtonUp();
		}
		break;
	case WM_KEYDOWN:
		{
			bRet = OnKeyDown(message,wParam,lParam);
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			bRet = OnLButtonDBDown(point);
		}
		break;
	default:
		break;
	}
	if(bRet)
	{
		Invalidate(TRUE);
	}
	return bRet;
}


BOOL	CODLEx_Element_AdjustLine::OnLButtonDown(POINT point)
{
	BOOL bNeedPaint = FALSE;
	BOOL bPressedBK = m_bPressed;
	int	 iSelectBK = m_dwLastSelect;
	m_bPressed = FALSE;
	int index = 0;
	CODLEx_CurveData* pData = NULL;
	POSITION pos = m_theDataList.GetFirstPosition();
	while(pos != NULL)
	{
		pData = m_theDataList.GetAt(pos);
		if(InSelect(point,pData,m_ptOffset))
		{
			m_bPressed = TRUE;
			if(index == iSelectBK)
				return TRUE;
			m_dwLastSelect = index;
			bNeedPaint = TRUE;
			break;
		}
		index++;		
		m_theDataList.MoveNext(pos);
	}
	if(!m_bPressed)	//如果没选中
	{
		if(m_bEnableClickAdd)
		{
			m_dwLastSelect= AddValueAtPoint(point);
			m_bPressed = m_dwLastSelect != -1;
			m_ptOffset.x = 0;
			m_ptOffset.y = 0;
			bNeedPaint = TRUE;
		}
		else
		{
			bNeedPaint =  (iSelectBK >=0);	//取消选中
			m_dwLastSelect = -1;
		}
	}

	if(iSelectBK != m_dwLastSelect)
	{
		if(m_dwLastSelect >= 0)
		{
			PostSelectMsg();
		}
		else
		{
			PostUnselectMsg();
		}
	}
	//
	if(m_dwLastSelect != -1)
	{
		m_dwBK_X = GetCurveDataData(m_dwLastSelect)->x;	//备份X坐标
	}
	return bNeedPaint;
}

BOOL	CODLEx_Element_AdjustLine::OnLButtonUp()
{
	BOOL bRet = m_bPressed;
	m_bPressed = FALSE;
	return bRet;
}

BOOL	CODLEx_Element_AdjustLine::OnLButtonDBDown(POINT pt)
{
	return m_bFilterLBDBLCLK;
}

BOOL	CODLEx_Element_AdjustLine::OnMouseMove(POINT point)
{
	if(!m_bPressed || m_dwLastSelect < 0)
		return FALSE;
	//获取鼠标在画布的坐标
	point.x -= m_ptOffset.x;
	point.y -= m_ptOffset.y;
	//
	float Xvalue = CoordSpaceToXValue(point.x);
	float Yvalue = CoordSpaceToYValue(point.y);
	//保存数值
	CODLEx_CurveData* pData = GetCurveDataData(m_dwLastSelect);
	if(!FormatX(Xvalue,m_dwLastSelect,AdjustPointMove))
		return FALSE;
	pData->x = Xvalue;
	pData->y = FormatY(Yvalue);
	//
	m_Msg.type = AdjustPointMove;
	m_Msg.x = pData->x;
	m_Msg.y = pData->y;
	m_Msg.ox = m_dwBK_X;		//移动消息需要上一个位置的X坐标
	m_Msg.pLine = (DWORD)this;
	GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
	//
	m_dwBK_X = pData->x;
	return TRUE;
}


BOOL	CODLEx_Element_AdjustLine::OnKeyDown(UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = FALSE;
	if(m_dwLastSelect >= 0)
	{
		if(wParam == VK_DELETE)
		{
			DeleteDataByIndex(m_dwLastSelect,TRUE);
			m_dwLastSelect = -1;
			m_bPressed = FALSE;
			bRet =true;
		}
	}
	return bRet;
}


INT	CODLEx_Element_AdjustLine::AddValueAtPoint(POINT pt)
{
	float Xvalue = CoordSpaceToXValue(pt.x);
	float Yvalue = CoordSpaceToYValue(pt.y);
	CODLEx_CurveData data;
	data.x = Xvalue;
	data.y = Yvalue;
	if(m_theDataList.GetLength() ==0)
	{
		if(!FormatX(data.x,0,AdjustPointAdd))
			return -1;
		FormatY(data.y);
		CODLEx_CurveData* pData = AddData(data.x,data.y);
		m_Msg.type = AdjustPointAdd;
		m_Msg.x = pData->x;
		m_Msg.y = pData->y;
		m_Msg.ox = pData->x;
		m_Msg.pLine = (DWORD)this;
		GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
		return 0;
	}
	//
	if(!IsXinLimitRange(Xvalue))
		return -1;
	int index = 0;
	CODLEx_CurveData* pPreData = NULL;
	//计算新点应该插入的位置
	CODLEx_CurveData* pData =NULL;
	POSITION insert_pos = NULL;
	POSITION pos = m_theDataList.GetFirstPosition();
	while(pos != NULL)
	{
		pData = m_theDataList.GetAt(pos);
		if(pData->x > Xvalue)
		{
			break;
		}
		index++;
		pPreData = pData;
		insert_pos = pos;
		m_theDataList.MoveNext(pos);
	}
	//格式化XY值
	if(!FormatX(data.x,index,AdjustPointAdd))	//
		return -1;
	FormatY(data.y);
	m_theDataList.InsertNode(&data,insert_pos);	//插在之后
	//
	pData = m_theDataList[index];
	m_Msg.type = AdjustPointAdd;
	m_Msg.x = pData->x;
	m_Msg.y = pData->y;
	m_Msg.ox = pData->x;
	m_Msg.pLine = (DWORD)this;
	GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
	return index;
}

CODLEx_CurveData*	CODLEx_Element_AdjustLine::AddData(FLOAT IN x,FLOAT IN y)
{
	if(m_theDataList.GetLength() == 0)
	{
		if(m_bLockFirstXatZero)
			x = 0;
	}
	//
	CODLEx_CurveData	data(x,y,0);
	//
	CODLEx_CurveData* pData = NULL;
	int index = 0;
	POSITION pos = m_theDataList.GetFirstPosition();
	while(pos != NULL)
	{
		pData = m_theDataList.GetAt(pos);
		if(pData->x > x)
		{
			if(index <= 0)
			{
				m_theDataList.AddHead(&data);
			}
			else
			{
				m_theDataList.InsertNodeInIndex(&data,index-1);
			}
			if(m_dwLastSelect >= index)
			{
				m_dwLastSelect++;
			}
			return GetCurveDataData(index);
		}
		m_theDataList.MoveNext(pos);
		index++;
	}
	return m_theDataList.AddTail(&data);
}

VOID	CODLEx_Element_AdjustLine::MoveDataX(FLOAT IN x,FLOAT newX,BOOL bNotify)
{
	POSITION pos = m_theDataList.GetFirstPosition();
	CODLEx_CurveData* pData = NULL;
	while(pos != NULL)
	{
		pData = m_theDataList.GetAt(pos);
		if(pData->x == x)
		{
			//
			m_Msg.type = AdjustPointMove;
			m_Msg.x = newX;
			m_Msg.y = pData->y;
			m_Msg.ox = x;
			m_Msg.pLine = (DWORD)this;
			GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
			//
			pData->x = newX;
			Invalidate();

			return;
		}
		m_theDataList.MoveNext(pos);
	}
}


VOID	CODLEx_Element_AdjustLine::DeleteDataByIndex(INT index,BOOL bNotify)
{
	if(index < 0 || index > m_theDataList.GetLength()-1)
		return;
	BOOL bAdjustHead = FALSE;
	if(index ==0  && m_bLockFirstXatZero)
	{
		bAdjustHead =TRUE;
	}
	if(bNotify)
	{
		CODLEx_CurveData*pData = m_theDataList[index];
		m_Msg.type = AdjustPointDelete;
		m_Msg.x = pData->x;
		m_Msg.y = pData->y;
		m_Msg.ox =  pData->x;
		m_Msg.pLine = (DWORD)this;
		GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
	}
	m_theDataList.DelNodeByIndex(index);
	//如果锁定第一点X为0，第二点移到X=0处
	if(bAdjustHead && m_bLockFirstXatZero)
	{
		CODLEx_CurveData* pData = GetCurveDataData(0);
		if(pData == NULL)
			return;
		m_Msg2.type = AdjustPointMove;
		m_Msg2.x = 0;
		m_Msg2.y = pData->y;
		m_Msg2.ox = pData->x;
		m_Msg2.pLine = (DWORD)this;
		GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg2);
		pData->x = 0;
	}
}

VOID	CODLEx_Element_AdjustLine::DeleteDataByX(DWORD X,BOOL bNotify)
{
	int index = 0;
	POSITION pos = m_theDataList.GetFirstPosition();
	CODLEx_CurveData* pData = NULL;
	while(pos != NULL)
	{
		pData = m_theDataList.GetAt(pos);
		if((DWORD)pData->x == X)
		{
			DeleteDataByIndex(index,bNotify);
			return;
		}
		m_theDataList.MoveNext(pos);
		index++;
	}
}

CODLEx_CurveData*	CODLEx_Element_AdjustLine::GetCurveDataData(INT index)
{
	if(index >= m_theDataList.GetLength())
		return NULL;
	return m_theDataList.GetAt(m_theDataList.GetPosByIndex(index));
}

BOOL	CODLEx_Element_AdjustLine::InSelect(POINT pt,CODLEx_CurveData*  pData,POINT& offset)
{
	RECT	rect;
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
	POINT	point;
	point.x	= pCoord->XValueToCoordSpacce(pData->x);
	point.y	= pCoord->YValueToCoordSpacce(pData->y);
	rect.left	=point.x-m_dwPointRadius;
	rect.top	=point.y-m_dwPointRadius;
	rect.right	=point.x+m_dwPointRadius;
	rect.bottom	=point.y+m_dwPointRadius;	
	//
	BOOL bRet =   PtInRect(&rect,pt);
	if(bRet)
	{
		offset.x = pt.x - (rect.left + rect.right)/2;
		offset.y = pt.y - (rect.top + rect.bottom)/2;
	}
	return bRet;
}

RECT CODLEx_Element_AdjustLine::GetDropPointRect(CODLEx_CurveData* pData)
{
	RECT rect;
	POINT		pt;	
	int off = m_dwPointRadius/2;
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)m_pCanvas->GetCoordinate();
	pt.x	= pCoord->XValueToCoordSpacce(pData->x);
	pt.y	= pCoord->YValueToCoordSpacce(pData->y);
	rect.left	=pt.x-off;
	rect.top	=pt.y-off;
	rect.right	=pt.x+off;
	rect.bottom	=pt.y+off;			
	return rect;
}

VOID	CODLEx_Element_AdjustLine::Clear()
{
	m_dwLastSelect = -1;
	m_bPressed = FALSE;
	m_theDataList.ClearList();
	Invalidate();
}


VOID	CODLEx_Element_AdjustLine::ClearMinMaxLimit()
{
	m_bMaxY = m_bMaxX = m_bMinX = m_bMaxY = FALSE;
}

VOID	CODLEx_Element_AdjustLine::SetMinX(float fMinX)
{
	m_fMinX = fMinX;
	m_bMinX = TRUE;
}

VOID	CODLEx_Element_AdjustLine::SetMaxX(float fMaxX)
{
	m_fMaxX = fMaxX;
	m_bMaxX = TRUE;
}

VOID	CODLEx_Element_AdjustLine::SetMinY(float fMinY)
{
	m_fMinY = fMinY;
	m_bMinY = TRUE;
}

VOID	CODLEx_Element_AdjustLine::SetMaxY(float fMaxY)
{
	m_fMaxY = fMaxY;
	m_bMaxY = TRUE;
}

VOID	CODLEx_Element_AdjustLine::EnableClickAdd(BOOL bEnable)
{
	m_bEnableClickAdd = bEnable;
}

VOID	CODLEx_Element_AdjustLine::EnableFirstZeroLock(BOOL bEnable)
{
	m_bLockFirstXatZero = bEnable;
}

void	CODLEx_Element_AdjustLine::EnableLBDClickFliter(BOOL bFilter)
{
	m_bFilterLBDBLCLK = bFilter;
}


VOID	CODLEx_Element_AdjustLine::EnableTrueFalseStyle(BOOL bEnable)
{
	m_bTrueFalseStyle = bEnable;
}

VOID	CODLEx_Element_AdjustLine::EnableXinteger(BOOL bEnable)
{
	m_bXinteger = bEnable;
}


VOID	CODLEx_Element_AdjustLine::EnableOperator(BOOL bEnable)
{
	m_bEnable = bEnable;
	if(!m_bEnable && m_dwLastSelect != -1)
	{
		m_dwLastSelect = -1;
		PostUnselectMsg();
	}
}

int		CODLEx_Element_AdjustLine::XValueToCoordSpacce(float x)
{
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return 0;
	return pCoord->XValueToCoordSpacce(x);
}

int	CODLEx_Element_AdjustLine::YValueToCoordSpacce(float y)
{
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return 0;
	return pCoord->YValueToCoordSpacce(y);
}

float	CODLEx_Element_AdjustLine::CoordSpaceToXValue(int x)
{
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return 0;
	return pCoord->CoordSpaceToXValue(x);
}

float	CODLEx_Element_AdjustLine::CoordSpaceToYValue(int y)
{
	CODLEx_Element_Coordinate*	pCoord	=(CODLEx_Element_Coordinate*)GetCanvas()->GetCoordinate();
	if(pCoord == NULL)
		return 0;
	return pCoord->CoordSpaceToYValue(y);
}

void	CODLEx_Element_AdjustLine::Init()
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(200,100,100));
	ODL_SafeRelease(m_pSelectBrush);
	m_pSelectBrush = GetCanvas()->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(255,0,0),NULL);
}

VOID		CODLEx_Element_AdjustLine::SetLineParameter(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor)
{
	ODL_SafeRelease(m_pLinePen);
	m_pLinePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(nLineStyle,nLineWidth,LineColor);
}

BOOL	CODLEx_Element_AdjustLine::IsXinLimitRange(float x)
{
	if(m_bMinX)
	{
		if(x < m_fMinX)
			return FALSE;
	}
	if(m_bMaxX)
	{
		if(x > m_fMaxX)
			return FALSE;
	}
	if(m_bLockFirstXatZero)
	{
		if(x <= 0)
			return FALSE;
	}
	return TRUE;
}

//move，index为move的点索引
//add，即将把x插入到index的前面。返回false则无法插入。
BOOL	CODLEx_Element_AdjustLine::FormatX(float& x,int index,DWORD style)
{
	BOOL bOK = TRUE;
	if(m_bLockFirstXatZero && index == 0)
	{
		x = 0;
	}
	else
	{
		//限制X值
		CODLEx_CurveData* pPreData = GetCurveDataData(index-1);
		CODLEx_CurveData* pNextData = GetCurveDataData(style==AdjustPointAdd?index:index+1);
		if(m_bXinteger)
		{
			if(pPreData != NULL)
			{
				if(x < pPreData->x+1)
				{
					x = pPreData->x+1;
				}
			}
			if(pNextData != NULL)
			{
				if( x > pNextData->x-1)	//
				{
					if(pNextData->x - pPreData->x < 1.5)
					{
						return FALSE;
					}
					x = pNextData->x-1;
				}
			}
			x = (INT)(x+0.5);
		}
		//X最小值限制
		if(m_bMinX)
		{
			if(x < m_fMinX)
				x = m_fMinX;		
		}	
		if(pPreData != NULL)
		{
			if(x <= pPreData->x)
				x = pPreData->x + (m_bXinteger!=0?1.0:0.001);
		}	
		//X最大值限制
		if(m_bMaxX)
		{
			if(x > m_fMaxX)
				x = m_fMaxX;		
		}
		if(pNextData != NULL)
		{
			if(x > pNextData->x)
				x = pNextData->x - m_bXinteger?1.0:0.001;
		}
	}
	//
	return TRUE;
}

FLOAT	CODLEx_Element_AdjustLine::FormatY(float& y)
{
	if(m_bTrueFalseStyle)
	{
		y = y>0.5?1:0;
		return y;
	}
	if(m_bMinY)
	{
		if(y < m_fMinY)
			y = m_fMinY;
	}
	//Y最大值限制
	if(m_bMaxY)
	{
		if(y > m_fMaxY)
			y = m_fMaxY;
	}
	return y;
}

VOID	CODLEx_Element_AdjustLine::CancelSelect(BOOL bNofity)
{
	if(m_dwLastSelect < 0)
		return;
	m_dwLastSelect = -1;
	if(bNofity)
	{
		PostUnselectMsg();
	}
}

VOID	CODLEx_Element_AdjustLine::PostUnselectMsg()
{
	m_Msg.type = AdjustPointSelect;
	m_Msg.x = -1;
	m_Msg.y = 0;
	m_Msg.ox = -1;
	m_Msg.pLine = (DWORD)this;
	GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
}

VOID	CODLEx_Element_AdjustLine::PostSelectMsg()
{
	CODLEx_CurveData* pData = GetCurveDataData(m_dwLastSelect);
	if(pData == NULL)
		return;
	m_Msg.x = pData->x;
	m_Msg.y = pData->y;
	m_Msg.ox = pData->x;
	m_Msg.pLine = (DWORD)this;
	GetCanvas()->PostCallbackMessage(ADJUSTLINE_MSG,(WPARAM)&m_Msg);
}

BOOL	CODLEx_Element_AdjustLine::HitTest(CPoint& pt)
{
	int index = -1;
	CPoint offset;
	POSITION pos = m_theDataList.GetPosByIndex(0);
	while(pos != NULL)
	{
		index++;	
		CODLEx_CurveData* pData = m_theDataList.GetAt(pos);
		if(InSelect(pt,pData,offset))
		{
			return TRUE;
		}
		m_theDataList.MoveNext(pos);
	}
	return FALSE;
}


int		CODLEx_Element_AdjustLine::GetSelectIndex()
{
	return m_dwLastSelect;
}


BOOL	CODLEx_Element_AdjustLine::CanDelectSelect()
{
	if(m_dwLastSelect < 0)
		return FALSE;
	return TRUE;	
}

BOOL	CODLEx_Element_AdjustLine::IsMovingPoint()
{
	return m_dwLastSelect >= 0  && m_bPressed;	
}






















