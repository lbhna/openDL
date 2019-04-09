#include "stdafx.h"
#include "ODLEx_Element_Picture.h"


CODLEx_Element_Picture::CODLEx_Element_Picture(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type				=ODL_ELEMENT_PICTURE;
	m_ImageSize.cx		=0;
	m_ImageSize.cy		=0;
	m_TransparentColorLow	=RGB(0,255,0);
	m_TransparentColorHigh	=RGB(0,255,0);


	m_pImage			=NULL;
	m_pGraphics			=NULL;
	m_ImageAttribute.ClearColorKey();
	m_hDeviceDC			=NULL;
	m_Pos.x	=m_Pos.y	=0;
	m_Size.cx=m_Size.cy	=32;
	m_fCourse			=0.0f;


	m_pBkBrush			=pCanvas->GetView()->GetResourceManager()->CreateBrush(BS_SOLID,RGB(150,150,150),0);
	m_pFramePen			=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,2,RGB(50,50,50));

	ZeroMemory(&m_ColorMatrix,sizeof(m_ColorMatrix));
	m_ColorMatrix.m[0][0]	=1.0f;
	m_ColorMatrix.m[1][1]	=1.0f;
	m_ColorMatrix.m[2][2]	=1.0f;
	m_ColorMatrix.m[3][3]	=1.0f;
	m_ColorMatrix.m[4][4]	=1.0f;


	m_bPushed			=FALSE;
	m_bMouseOver		=FALSE;
	m_pTips				=NULL;
	m_ptDragOffset.x	=0;
	m_ptDragOffset.y	=0;
	m_bEnableDrag		=FALSE;
	m_bDraging			=FALSE;
	m_bEnableAdjustSize	=FALSE;
	m_bAdjustSizeing	=FALSE;

}


CODLEx_Element_Picture::~CODLEx_Element_Picture(void)
{
	ODL_SafeRelease(m_pImage);
	ODL_SafeDelete(m_pGraphics);
	ODL_SafeRelease(m_pBkBrush);
	ODL_SafeRelease(m_pFramePen);
	ODL_SafeRelease(m_pTips);
}

VOID		CODLEx_Element_Picture::SetAlpha(BYTE IN alpha)
{
	if(m_Alpha == alpha)
		return;
	m_Alpha		=alpha;

	m_ColorMatrix.m[3][3]	=(FLOAT)m_Alpha/255.0f;
	m_ImageAttribute.SetColorMatrix(&m_ColorMatrix);

	Invalidate();
}
BYTE		CODLEx_Element_Picture::GetAlpha()
{
	return m_Alpha;
}
PSIZE		CODLEx_Element_Picture::GetImageSize()
{
	return &m_ImageSize;
}
PSIZE		CODLEx_Element_Picture::GetSize()
{
	return &m_Size;
}
PPOINT		CODLEx_Element_Picture::GetPos()
{
	return &m_Pos;
}
FLOAT		CODLEx_Element_Picture::GetCourse()
{
	return m_fCourse;
}
VOID		CODLEx_Element_Picture::GetTransparentColor(COLORREF& OUT clrLow,COLORREF& OUT clrHigh)
{
	clrLow	=m_TransparentColorLow;
	clrHigh	=m_TransparentColorHigh;
}
VOID		CODLEx_Element_Picture::EnableTransparentColor(BOOL IN bEnable)
{
	m_bEnableTransparentColor	=bEnable;
	if(m_bEnableTransparentColor)
	{
		m_ImageAttribute.SetColorKey(m_TransparentColorLow,m_TransparentColorHigh);
	}
	else
	{
		m_ImageAttribute.ClearColorKey();
	}
	Invalidate();
}
BOOL		CODLEx_Element_Picture::IsEnableTransparentColor()
{
	return m_bEnableTransparentColor;
}
VOID		CODLEx_Element_Picture::SetFramePen(LOGPEN* IN lp)
{
	ODL_SafeRelease(m_pFramePen);
	m_pFramePen			=m_pCanvas->GetView()->GetResourceManager()->CreatePen(lp);
}
VOID		CODLEx_Element_Picture::SetBkBrush(LOGBRUSH* IN lb)
{
	ODL_SafeRelease(m_pBkBrush);
	m_pBkBrush			=m_pCanvas->GetView()->GetResourceManager()->CreateBrush(lb);
}

VOID		CODLEx_Element_Picture::SetPos(POINT& IN pos)
{
	m_Pos	=pos;
	Invalidate();
}
VOID		CODLEx_Element_Picture::SetPos(LONG IN x,LONG IN y)
{
	m_Pos.x		=x;
	m_Pos.y		=y;
	Invalidate();
}
VOID		CODLEx_Element_Picture::SetSize(SIZE& IN size)
{
	m_Size	=size;
	Invalidate();
}
VOID		CODLEx_Element_Picture::SetSizeMatchedImage()
{
	if(m_pImage == NULL)
		return;
	m_Size.cx	=m_pImage->GetWidth();
	m_Size.cy	=m_pImage->GetHeight();
	Invalidate();
}

VOID		CODLEx_Element_Picture::SetSize(LONG IN cx,LONG IN cy)
{
	m_Size.cx	=cx;
	m_Size.cy	=cy;
	Invalidate();
}
VOID		CODLEx_Element_Picture::SetTransparentColor(COLORREF OUT clrLow,COLORREF OUT clrHigh)
{
	m_TransparentColorLow	=clrLow;
	m_TransparentColorHigh	=clrHigh;
	if(m_bEnableTransparentColor)
	{
		m_ImageAttribute.SetColorKey(m_TransparentColorLow,m_TransparentColorHigh);
		Invalidate();
	}

}

VOID		CODLEx_Element_Picture::SetCourse(FLOAT IN fCourse)
{
	m_fCourse	=fCourse;
	Invalidate();
}
BOOL		CODLEx_Element_Picture::SetImage(LPCSTR IN pFileName)
{
	ODL_SafeRelease(m_pImage);
	m_pImage	=new CODL_Image();
	if(!m_pImage->Load(pFileName))
	{
		ODL_SafeRelease(m_pImage);
		return FALSE;
	}
	Invalidate();
	return TRUE;
}
BOOL		CODLEx_Element_Picture::SetImage(LPVOID IN pData,DWORD IN dwDataSize)
{
	ODL_SafeRelease(m_pImage);
	m_pImage	=new CODL_Image();
	if(!m_pImage->Load(pData,dwDataSize))
	{
		ODL_SafeRelease(m_pImage);
		return FALSE;
	}

	Invalidate();
	return TRUE;
}
BOOL		CODLEx_Element_Picture::SetImage(CODL_Image* IN pImage)
{
	if(m_pImage == pImage)
		return TRUE;
	ODL_SafeRelease(m_pImage);
	m_pImage =pImage;
	if(m_pImage != NULL)
		m_pImage->AddRef();
	Invalidate();
	return TRUE;
}

VOID		CODLEx_Element_Picture::GetRect(RECT& OUT rect)
{
	if(fabs(m_fCourse)<0.00001f)
	{
		rect.left	=m_Pos.x;
		rect.top	=m_Pos.y;
		rect.right	=m_Pos.x + m_Size.cx;
		rect.bottom	=m_Pos.y + m_Size.cy;
		return;
	}
	Gdiplus::Matrix mt;
	PointF			center(m_Pos.x,m_Pos.y);
	mt.RotateAt(m_fCourse,center);

	Gdiplus::PointF	vCenter(m_Pos.x + (m_Size.cx*0.5),m_Pos.y + (m_Size.cy*0.5));
	Gdiplus::PointF	point[4],vMin,vMax;

	point[0].X	=vCenter.X - m_Size.cx*.5f;
	point[0].Y	=vCenter.Y - m_Size.cy*.5f;		
	point[1].X	=vCenter.X + m_Size.cx*.5f;
	point[1].Y	=vCenter.Y - m_Size.cy*.5f;
	point[2].X	=vCenter.X + m_Size.cx*.5f;
	point[2].Y	=vCenter.Y + m_Size.cy*.5f;
	point[3].X	=vCenter.X - m_Size.cx*.5f;
	point[3].Y	=vCenter.Y + m_Size.cy*.5f;
	mt.TransformPoints(point,4);

	vMin	=point[0];
	vMax	=point[0];

	for(DWORD i=1;i<4;i++)
	{
		if(vMin.X > point[i].X)vMin.X =point[i].X;
		if(vMin.Y > point[i].Y)vMin.Y =point[i].Y;

		if(vMax.X < point[i].X)vMax.X =point[i].X;
		if(vMax.Y < point[i].Y)vMax.Y =point[i].Y;
	}
	rect.left		=vMin.X;
	rect.top		=vMin.Y;
	rect.right		=vMax.X;
	rect.bottom		=vMax.Y;


}

BOOL		CODLEx_Element_Picture::PtInElement(POINT IN pt)
{
	if(!IsShow())
		return FALSE;
	if(fabs(m_fCourse)<0.00001f)
	{
		RECT	rect;
		GetRect(rect);
		if(PtInRect(&rect,pt))
			return TRUE;
		return FALSE;
	}


	Gdiplus::Matrix mt;
	PointF			center(m_Pos.x,m_Pos.y);
	mt.RotateAt(m_fCourse,center);

	Gdiplus::PointF	vCenter(m_Pos.x + (m_Size.cx*0.5),m_Pos.y + (m_Size.cy*0.5));
	Gdiplus::PointF	point[4],vMin,vMax;

	point[0].X	=vCenter.X - m_Size.cx*.5f;
	point[0].Y	=vCenter.Y - m_Size.cy*.5f;		
	point[1].X	=vCenter.X + m_Size.cx*.5f;
	point[1].Y	=vCenter.Y - m_Size.cy*.5f;
	point[2].X	=vCenter.X + m_Size.cx*.5f;
	point[2].Y	=vCenter.Y + m_Size.cy*.5f;
	point[3].X	=vCenter.X - m_Size.cx*.5f;
	point[3].Y	=vCenter.Y + m_Size.cy*.5f;
	mt.TransformPoints(point,4);


	POINT	pos[4];
	pos[0].x=point[0].X;
	pos[1].x=point[1].X;
	pos[2].x=point[2].X;
	pos[3].x=point[3].X;
	pos[0].y=point[0].Y;
	pos[1].y=point[1].Y;
	pos[2].y=point[2].Y;
	pos[3].y=point[3].Y;
	HRGN rgn	=CreatePolygonRgn(pos,4,ALTERNATE);
	BOOL bRet	=PtInRegion(rgn,pt.x,pt.y);
	DeleteObject(rgn);

	return bRet;
}
VOID		CODLEx_Element_Picture::GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect)
{
	GetRect(boundRect);
}
BOOL		CODLEx_Element_Picture::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_hDeviceDC != hDC )
	{
		m_hDeviceDC		=hDC;
		ODL_SafeDelete(m_pGraphics);
		m_pGraphics		=new Graphics(m_hDeviceDC);
	}
	
	if(m_pImage != NULL)
	{
		Rect DstRect;
		DstRect.X		=m_Pos.x;
		DstRect.Y		=m_Pos.y;
		DstRect.Width	=m_Size.cx;
		DstRect.Height	=m_Size.cy;
		m_pGraphics->TranslateTransform(m_Pos.x,m_Pos.y);
		m_pGraphics->RotateTransform(m_fCourse);
		m_pGraphics->TranslateTransform(-m_Pos.x,-m_Pos.y);
		m_pGraphics->DrawImage(m_pImage->GetImageObject(),DstRect,0,0,m_pImage->GetWidth(),m_pImage->GetHeight(),UnitPixel,&m_ImageAttribute);
		m_pGraphics->ResetTransform();
	}
	else
	{
		RECT DstRect;
		DstRect.left		=m_Pos.x;
		DstRect.top			=m_Pos.y;
		DstRect.right		=m_Pos.x + m_Size.cx;
		DstRect.bottom		=m_Pos.y + m_Size.cy;
		m_pBkBrush->Install(hDC);
		m_pBkBrush->FillRect(&DstRect);
		m_pBkBrush->Uninstall(hDC);
		m_pFramePen->Install(hDC);
		m_pFramePen->DrawRect(&DstRect);
		m_pFramePen->Uninstall(hDC);
	}

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
	if(m_pTips != NULL)
		m_pTips->Draw(hDC,pPaintRect);

	return TRUE;
}
VOID		CODLEx_Element_Picture::SetTips(LPCSTR IN pText)
{
	ODL_SafeRelease(m_pTips);
	if(pText == NULL)
		return;
	if(strlen(pText)==0)
		return;

	m_pTips =new CODLEx_Element_Tips(GetCanvas());
	m_pTips->SetText(pText);

}
BOOL		CODLEx_Element_Picture::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
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
			if(!IsControlSwitchKeyPressed())
			{
				if(!PtInElement(*pPoint))
					break;
				m_bPushed =TRUE;
				return TRUE;
			}
			else
			{
				if(!IsSelected())
					break;
				//只有在Ctrl键按下的情况下才可以进行下列操作
				if(m_bEnableAdjustSize && fabs(m_fCourse)<0.000001f)
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
		}
		break;
	case WM_LBUTTONUP:
		{
			if(!IsControlSwitchKeyPressed())
			{
				m_bDraging			=FALSE;
				if(PtInElement(*pPoint) && m_bPushed)
				{
					m_bPushed =FALSE;
					if(m_pListener!=NULL)
						m_pListener->OnElement_Clicked(this);
					return TRUE;
				}

			}
			else
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
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(!IsControlSwitchKeyPressed())
			{
				if(!PtInElement(*pPoint))
				{
					if(m_bMouseOver)
					{
						m_bMouseOver =FALSE;
						OnMouseOut();
						return TRUE;
					}
				}
				else
				{
					if(!m_bMouseOver)
					{
						m_bMouseOver =TRUE;
						OnMouseOver();
						return TRUE;
					}
				}
			}
			else
			{
				if(!IsSelected())
					break;

				if(m_bAdjustSizeing)
				{
					POINT	pos;
					pos.x		=pPoint->x + m_ptDragOffset.x;
					pos.y		=pPoint->y + m_ptDragOffset.y;
					if(pos.x < (m_Pos.x+5) || pos.y< (m_Pos.y+5) )
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
VOID		CODLEx_Element_Picture::OnMouseOver()
{
	if(m_pTips != NULL)
	{
		RECT	rect;
		GetRect(rect);
		m_pTips->SetPos(rect.left,rect.bottom+10);
		m_pTips->Show(TRUE);
		Invalidate(TRUE);
	}
}
VOID		CODLEx_Element_Picture::OnMouseOut()
{
	if(m_pTips != NULL)
	{
		m_pTips->Show(FALSE);
		Invalidate(TRUE);
	}
}
BOOL		CODLEx_Element_Picture::PtInAdjustSizeButton(POINT* IN pt)
{
	if(!IsShow())
		return FALSE;
	RECT	rect;
	GetRect(rect);
	rect.left	=rect.right -5;
	rect.top	=rect.bottom-5;
	return PtInRect(&rect,*pt);
}
