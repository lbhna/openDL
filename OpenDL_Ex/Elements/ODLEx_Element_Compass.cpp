#include "stdafx.h"
#include "ODLEx_Element_Compass.h"


CODLEx_Element_Compass::CODLEx_Element_Compass(CODL_CanvasBase* IN pCanvas,DWORD IN dwDialRadius,LONG IN x,LONG IN y):
	CODL_OverlayElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_COMPASS;
	m_Alpha				=200;
	SetZIndex(20);

	m_Size.cx			=dwDialRadius*2;
	if(m_Size.cx < 20)
		m_Size.cx=20;
	m_Size.cy			=m_Size.cx;

	m_Pos.x				=x;
	m_Pos.y				=y;
	m_fCourse			=0.0f;

	m_pFramePen			=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,2,RGB(110,110,155));		//边框的画笔
	m_pDialTextFont		=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",9);
	m_DialTextColor		=RGB(50,50,255);
	m_pNeedlePen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(0,0,55));		//边框的画笔
	m_pFillNorthNeedleBrush=pCanvas->GetView()->GetResourceManager()->CreateBrush(PS_SOLID,RGB(255,80,80),NULL);
	m_pFillSouthNeedleBrush=pCanvas->GetView()->GetResourceManager()->CreateBrush(PS_SOLID,RGB(200,200,200),NULL);
	m_bFillDial			=TRUE;
	m_pFillDialBrush	=pCanvas->GetView()->GetResourceManager()->CreateBrush(PS_SOLID,RGB(150,150,150),NULL);
	m_fNeedleAngle		=25.0f;
	
	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;
	m_bDraging			=FALSE;
	m_bAdjustSizeing	=FALSE;

	m_bShowText			=TRUE;
	m_bEnableAdjustSize	=TRUE;
	m_bEnableDrag		=TRUE;
	m_bEnableSelect		=TRUE;

}

CODLEx_Element_Compass::~CODLEx_Element_Compass(void)
{
	ODL_SafeRelease(m_pFramePen);
	ODL_SafeRelease(m_pDialTextFont);
	ODL_SafeRelease(m_pNeedlePen);
	ODL_SafeRelease(m_pFillNorthNeedleBrush);
	ODL_SafeRelease(m_pFillSouthNeedleBrush);
	ODL_SafeRelease(m_pFillDialBrush);
}
VOID								CODLEx_Element_Compass::SetDialTextFontPara(CHAR* IN pFontName,DWORD IN dwSize)
{

	ODL_SafeRelease(m_pDialTextFont);
	m_pDialTextFont	=m_pCanvas->GetView()->GetResourceManager()->CreateFont(pFontName,dwSize);
	Invalidate();
}
VOID								CODLEx_Element_Compass::SetNeedleAngle(FLOAT IN fAngle)
{
	m_fNeedleAngle	=fAngle;
	if(m_fNeedleAngle>75.0f)	m_fNeedleAngle=75.0f;
	if(m_fNeedleAngle<5.0f)		m_fNeedleAngle=5.0f;

	Invalidate();
}

VOID								CODLEx_Element_Compass::GetDialTextFontPara(CHAR* OUT pFontName,DWORD& OUT dwSize)
{
	strcpy(pFontName,m_pDialTextFont->GetLogFont()->lfFaceName);
	dwSize	=m_pDialTextFont->GetLogFont()->lfHeight;
}
VOID								CODLEx_Element_Compass::SetDialTextFont(LOGFONT* IN pLf)
{
	ODL_SafeRelease(m_pDialTextFont);
	m_pDialTextFont	=m_pCanvas->GetView()->GetResourceManager()->CreateFont(pLf);
	Invalidate();

}

VOID								CODLEx_Element_Compass::SetDialTextColor(COLORREF IN clr)
{
	if(m_DialTextColor == clr)
		return;
	m_DialTextColor=clr;
	Invalidate();
}

VOID								CODLEx_Element_Compass::SetDialRadius(DWORD IN dwDialRadius)
{
	m_Size.cx=m_Size.cy=dwDialRadius;
	Invalidate();
}
VOID								CODLEx_Element_Compass::SetPos(POINT* IN pPos)
{
	SetPos(pPos->x,pPos->y);
}
VOID								CODLEx_Element_Compass::SetPos(LONG IN x,LONG IN y)
{
	if(m_Pos.x==x&&m_Pos.y==y)
		return;
	m_Pos.x=x;
	m_Pos.y=y;
	Invalidate();
}
VOID								CODLEx_Element_Compass::SetSize(LONG IN cx,LONG IN cy)
{
	if(m_Size.cx==cx&&m_Size.cy==cy)
		return;
	m_Size.cx=cx;
	m_Size.cy=cy;
	Invalidate();

}
VOID								CODLEx_Element_Compass::SetSize(SIZE* IN pSize)
{
	SetSize(pSize->cx,pSize->cy);
}
VOID								CODLEx_Element_Compass::SetPose(FLOAT IN fCourse)
{
	m_fCourse	=fCourse;
	while(m_fCourse>180.0f)
		m_fCourse-=360.0f;
	while(m_fCourse<-180.0f)
		m_fCourse+=360.0f;

	Invalidate();
}

VOID								CODLEx_Element_Compass::SetDialFramePara(COLORREF IN FrameColor,DWORD IN dwLineWidth,DWORD IN dwPenStyle)
{
	ODL_SafeRelease(m_pFramePen);
	m_pFramePen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(dwPenStyle,dwLineWidth,FrameColor);
	Invalidate();
}

VOID								CODLEx_Element_Compass::GetDialFramePara(COLORREF& OUT FrameColor,DWORD& OUT dwLineWidth,DWORD& OUT dwPenStyle)
{
	FrameColor	=m_pFramePen->GetLogPen()->lopnColor;
	dwLineWidth=m_pFramePen->GetLogPen()->lopnWidth.x;
	dwPenStyle=m_pFramePen->GetLogPen()->lopnStyle;
}
VOID								CODLEx_Element_Compass::SetNeedlePara(COLORREF IN clr,DWORD IN dwLineWidth,DWORD IN dwPenStyle)
{
	ODL_SafeRelease(m_pNeedlePen);
	m_pNeedlePen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(dwPenStyle,dwLineWidth,clr);
	Invalidate();
}
VOID								CODLEx_Element_Compass::GetNeedlePara(COLORREF& OUT clr,DWORD& OUT dwLineWidth,DWORD& OUT dwPenStyle)
{
	clr	=m_pNeedlePen->GetLogPen()->lopnColor;
	dwLineWidth=m_pNeedlePen->GetLogPen()->lopnWidth.x;
	dwPenStyle=m_pNeedlePen->GetLogPen()->lopnStyle;
}

VOID								CODLEx_Element_Compass::EnableFillDial(BOOL IN bEnable)
{
	if(m_bFillDial==bEnable)
		return;
	m_bFillDial=bEnable;
	Invalidate();
}

VOID								CODLEx_Element_Compass::SetFillDialPara(COLORREF IN FillColor,UINT IN uBrushStyle)
{
	ODL_SafeRelease(m_pFillDialBrush);
	m_pFillDialBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(uBrushStyle,FillColor,NULL);
	Invalidate();
}

VOID								CODLEx_Element_Compass::GetFillDialPara(COLORREF& OUT FillColor,UINT& OUT uBrushStyle)
{
	FillColor	=m_pFillDialBrush->GetLogBrush()->lbColor;
	uBrushStyle=m_pFillDialBrush->GetLogBrush()->lbStyle;
}


VOID								CODLEx_Element_Compass::SetFillNorthNeedlePara(COLORREF IN FillColor,UINT IN uBrushStyle)
{
	ODL_SafeRelease(m_pFillNorthNeedleBrush);
	m_pFillNorthNeedleBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(uBrushStyle,FillColor,NULL);
	Invalidate();

}

VOID								CODLEx_Element_Compass::GetFillNorthNeedlePara(COLORREF& OUT FillColor,UINT& OUT uBrushStyle)
{
	FillColor	=m_pFillNorthNeedleBrush->GetLogBrush()->lbColor;
	uBrushStyle=m_pFillNorthNeedleBrush->GetLogBrush()->lbStyle;

}


VOID								CODLEx_Element_Compass::SetFillSouthNeedlePara(COLORREF IN FillColor,UINT IN uBrushStyle)
{
	ODL_SafeRelease(m_pFillSouthNeedleBrush);
	m_pFillSouthNeedleBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(uBrushStyle,FillColor,NULL);
	Invalidate();

}

VOID								CODLEx_Element_Compass::GetFillSouthNeedlePara(COLORREF& OUT FillColor,UINT& OUT uBrushStyle)
{
	FillColor	=m_pFillSouthNeedleBrush->GetLogBrush()->lbColor;
	uBrushStyle=m_pFillSouthNeedleBrush->GetLogBrush()->lbStyle;

}
VOID	CODLEx_Element_Compass::EnableShowText(BOOL IN bEnableShow)
{
	if(bEnableShow != m_bShowText)
	{
		m_bShowText	=bEnableShow;
		Invalidate();
	}
}

VOID	CODLEx_Element_Compass::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	boundRect.left		=(m_Pos.x-m_Size.cx/2)-1;
	boundRect.right		=(m_Pos.x+m_Size.cx/2)+1;
	boundRect.top		=(m_Pos.y-m_Size.cy/2)-1;
	boundRect.bottom	=(m_Pos.y+m_Size.cy/2)+1;

}
BOOL	CODLEx_Element_Compass::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	HGDIOBJ	hOldBrush;
	int			oldMode		=::SetBkMode(hDC,TRANSPARENT);
	SetTextColor(hDC,m_DialTextColor);
	m_pDialTextFont->Install(hDC);
	m_pFramePen->Install(hDC);
	RECT	FrameRect;
	GetElementBound(hDC,pPaintRect,FrameRect);
	if(m_bFillDial)
		m_pFillDialBrush->Install(hDC);
	else
		hOldBrush	=SelectObject(hDC,(HGDIOBJ)NULL_BRUSH);
	Ellipse(hDC,FrameRect.left,FrameRect.top,FrameRect.right,FrameRect.bottom);
	if(m_bFillDial)
		m_pFillDialBrush->Uninstall(hDC);
	else
		SelectObject(hDC,hOldBrush);

	m_pFramePen->Uninstall(hDC);



	//------------------------------------------------------------
	CODL_Vector2f	vCenter(m_Pos.x,m_Pos.y);
	CODL_Vector2f	vAt,vRight;
	CODL_Vector2f	vPos[4];
	POINT			vRgn[3];
	FLOAT			fLength,fWidth;
	FLOAT			fRadius		=GetEllipseRadius(m_fCourse,m_Size.cx/2.0f,m_Size.cy/2.0f);
	fLength			=(FLOAT)fRadius*0.7f;

	fWidth			=fLength*tan((m_fNeedleAngle*0.5f)/180.0f*DOUBLE_PI);

	CODL_Tools::AngleToDirect(-m_fCourse,vAt,vRight);
	vPos[0]			=vCenter -vRight*fWidth;
	vPos[1]			=vCenter +vAt*fLength;
	vPos[2]			=vCenter +vRight*fWidth;
	vPos[3]			=vCenter -vAt*fLength;
	//------------------------------------------------------------
	m_pNeedlePen->Install(hDC);
	vRgn[0].x	=vPos[0].x;vRgn[0].y=vPos[0].y;
	vRgn[1].x	=vPos[1].x;vRgn[1].y=vPos[1].y;
	vRgn[2].x	=vPos[2].x;vRgn[2].y=vPos[2].y;
	m_pFillNorthNeedleBrush->Install(hDC);
	Polygon(hDC,vRgn,3);
	m_pFillNorthNeedleBrush->Uninstall(hDC);
	//------------------------------------------------------------
	vRgn[0].x	=vPos[0].x;vRgn[0].y=vPos[0].y;
	vRgn[1].x	=vPos[2].x;vRgn[1].y=vPos[2].y;
	vRgn[2].x	=vPos[3].x;vRgn[2].y=vPos[3].y;
	m_pFillSouthNeedleBrush->Install(hDC);
	Polygon(hDC,vRgn,3);
	Ellipse(hDC,vCenter.x-fWidth*0.5f,vCenter.y-fWidth*0.5f,vCenter.x+fWidth*0.5f,vCenter.y+fWidth*0.5f);
	m_pFillSouthNeedleBrush->Uninstall(hDC);
	//------------------------------------------------------------
	if(m_bShowText)
	{
		TEXTMETRIC metric;
		GetTextMetrics(hDC,&metric);
		DWORD			dwTextWidth		=metric.tmMaxCharWidth;
		DWORD			dwTextHeight		=metric.tmHeight;
		RECT			rect;

		rect.left		=vCenter.x-dwTextWidth;
		rect.top		=vCenter.y-m_Size.cy*0.5f;
		rect.right		=rect.left+dwTextWidth*2;
		rect.bottom		=rect.top+dwTextHeight;
		DrawText(hDC,"北",2,&rect,DT_CENTER|DT_VCENTER);

		rect.left		=vCenter.x-dwTextWidth;
		rect.top		=vCenter.y+m_Size.cy*0.5f-dwTextHeight;
		rect.right		=rect.left+dwTextWidth*2;
		rect.bottom		=rect.top+dwTextHeight;
		DrawText(hDC,"南",2,&rect,DT_CENTER|DT_VCENTER);

		rect.left		=vCenter.x-m_Size.cx*0.5f;
		rect.top		=vCenter.y-dwTextHeight/2;
		rect.right		=rect.left+dwTextWidth*2;
		rect.bottom		=rect.top+dwTextHeight;
		DrawText(hDC,"西",2,&rect,DT_CENTER|DT_VCENTER);

		rect.left		=vCenter.x+m_Size.cx*0.5f-dwTextWidth*2;
		rect.top		=vCenter.y-dwTextHeight/2;
		rect.right		=rect.left+dwTextWidth*2;
		rect.bottom		=rect.top+dwTextHeight;
		DrawText(hDC,"东",2,&rect,DT_CENTER|DT_VCENTER);
	}


	m_pNeedlePen->Uninstall(hDC);
	m_pDialTextFont->Uninstall(hDC);
	::SetBkMode(hDC,oldMode);



	if(IsSelected())
	{
		RECT rect;
		GetRect(&rect);
		m_pCanvas->GetElementSelectFramePen()->Install(hDC);
			m_pCanvas->GetElementSelectFramePen()->DrawRect(&rect);
		if(m_bEnableAdjustSize)
		for(INT i=1;i<=7;i++)
		{
			MoveToEx(hDC,rect.right,rect.bottom-i,NULL);
			LineTo(hDC,rect.right-i,rect.bottom);			
		}
		m_pCanvas->GetElementSelectFramePen()->Uninstall(hDC);
	}


	return TRUE;
}
BOOL	CODLEx_Element_Compass::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	
	switch(message)
	{
	case WM_RBUTTONDOWN:
		{
			if(!IsSelected())
				break;
			if(!IsControlSwitchKeyPressed() || !PtInElement(*pPoint))
				break;
			if(PopupMenu())
				return TRUE;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if(IsControlSwitchKeyPressed()&&IsSelected())
			{
				if(PtInAdjustSizeButton(pPoint)&&m_bEnableAdjustSize)
				{
					m_bAdjustSizeing		=TRUE;
					m_ptDragOffset.x		=(m_Pos.x+m_Size.cx/2) - pPoint->x;
					m_ptDragOffset.y		=(m_Pos.y+m_Size.cy/2) - pPoint->y;
					::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
					return TRUE;
				}
				if(PtInElement(*pPoint)&&m_bEnableDrag)
				{
					m_bDraging	=TRUE;
					m_ptDragOffset.x	=m_Pos.x - pPoint->x;
					m_ptDragOffset.y	=m_Pos.y - pPoint->y;
					return TRUE;			
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_bDraging)
			{
				m_bDraging	=FALSE;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_PosChanged(this);
				return TRUE;
			}
			if(m_bAdjustSizeing)
			{
				m_bAdjustSizeing	=FALSE;
				Invalidate(TRUE);
				if(m_pListener != NULL)
					m_pListener->OnElement_SizeChanged(this);
				return TRUE;
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!IsSelected())
				break;
			if(m_bDraging)
			{
				m_Pos.x		=pPoint->x + m_ptDragOffset.x;
				m_Pos.y		=pPoint->y + m_ptDragOffset.y;
				Invalidate(TRUE);
				return TRUE;
			}

			if(m_bAdjustSizeing)
			{
				POINT	pos;
				pos.x		=pPoint->x + m_ptDragOffset.x;
				pos.y		=pPoint->y + m_ptDragOffset.y;
				if(pos.x < (m_Pos.x+10) || pos.y< (m_Pos.y+10) )
				{
					m_bAdjustSizeing=FALSE;
					Invalidate(TRUE);
					return TRUE;
				}

				m_Size.cx	=(pos.x - m_Pos.x)*2;
				m_Size.cy	=(pos.y - m_Pos.y)*2;


				Invalidate(TRUE);
				::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
				return TRUE;
			}

			if(m_bEnableAdjustSize&&IsControlSwitchKeyPressed())
			{
				if(PtInAdjustSizeButton(pPoint))
					::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
			}



		}
		break;

	case WM_KEYDOWN:
		{
			if(!IsSelected())
				break;

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
		break;
	}

	return FALSE;
}
BOOL	CODLEx_Element_Compass::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	POINT	point;
	point.x		=pt.x	- m_Pos.x;
	point.y		=pt.y	- m_Pos.y;
	FLOAT		a=m_Size.cx/2.0f;
	FLOAT		b=m_Size.cy/2.0f;

	FLOAT val	=(FLOAT)(point.x*point.x)/(a*a) +(FLOAT)(point.y*point.y)/(b*b);
	return (val <1.0f);
}
RECT*	CODLEx_Element_Compass::GetRect(RECT* IN OUT pRec)
{
	pRec->left		=m_Pos.x-m_Size.cx/2;
	pRec->top		=m_Pos.y-m_Size.cy/2;

	pRec->right		=m_Pos.x+m_Size.cx/2;
	pRec->bottom	=m_Pos.y+m_Size.cy/2;
	return pRec;
}

BOOL	CODLEx_Element_Compass::PtInAdjustSizeButton(POINT* IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	rect.right	=m_Pos.x + m_Size.cx/2;
	rect.bottom =m_Pos.y + m_Size.cy/2;
	rect.left	=rect.right -5;
	rect.top	=rect.bottom-5;
	return PtInRect(&rect,*pt);
}
FLOAT		CODLEx_Element_Compass::GetEllipseRadius(FLOAT IN fAngle,FLOAT IN fXRadius,FLOAT IN fYRadius)
{
	FLOAT	angle	=fAngle;
	while(angle <0.0f)
		angle += 360.0f;
	while(angle >360.0f)
		angle -= 360.0f;
	while(angle > 90.0f)
		angle -=180.0f;

	FLOAT	radius;
	if(angle > 0.0f)
		radius	=fYRadius + (fXRadius-fYRadius)*(angle/90.0f);
	else
		radius	=fXRadius + (fYRadius-fXRadius)*((90.0f+angle)/90.0f);

	return radius;
}