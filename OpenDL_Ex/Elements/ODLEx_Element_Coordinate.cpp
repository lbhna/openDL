#include "StdAfx.h"
#include ".\odlex_element_coordinate.h"
#include "./ODLEx_Element_CanvasTitle.h"

CODLEx_Element_Coordinate::CODLEx_Element_Coordinate(CODL_CanvasBase* IN pCanvas):
CODL_ElementBase(pCanvas)
{
	m_Type						=ODL_ELEMENT_COORD;
	m_CenterOffset.x			=15;
	m_CenterOffset.y			=15;
	m_dwGraduationLength		=5;

	m_pXAxisPen					=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(155,125,0));
	m_pYAxisPen					=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(155,125,0));


	m_fXPixelsPerUnit			=50.0f;		//最小单位多少个象素点
	m_fXUnitValue				=1.0f;		//最小单位值
	m_fXCenterValue				=0.0f;		//X轴中心点对应的值
	m_pXAxisName				=NULL;		//X轴名称

	m_pXAxisNameFont			=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",12);
	m_pXGraduationIndicatePen	=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(155,125,0));
	m_XAxisNameColor			=RGB(50,200,150);	//X轴名称颜色


	m_fYPixelsPerUnit			=50.0f;				//最小单位多少个象素点
	m_fYUnitValue				=1.0f;				//最小单位值
	m_fYCenterValue				=0.0f;				//Y轴中心点对应的值 

	m_pYAxisName				=NULL;
	m_pYAxisNameFont			=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",12);
	m_pYGraduationIndicatePen	=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(155,125,0));
	m_YAxisNameColor			=RGB(50,200,150);


	m_bAxisDraging				=FALSE;
	m_AxisDragOffsetByCenter.x	=0;
	m_AxisDragOffsetByCenter.y	=0;



	m_XGraduationIndicateColor				=RGB(50,200,150);
	m_pXGraduationIndicateFont				=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",9);
	m_dwXGraduationIndicatePrecision		=1;


	m_YGraduationIndicateColor				=RGB(50,200,150);
	m_dwYGraduationIndicatePrecision		=1;
	m_pYGraduationIndicateFont				=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",9);

	m_dwXAxisGraduationCount				=0;
	m_dwYAxisGraduationCount				=0;

	m_bDiagramDraging						=0;
	m_ptStartDragPoint.x	 =m_ptStartDragPoint.y		=0;
	m_vStartDragCenterValue.x=m_vStartDragCenterValue.y	=0.0f;
	m_lXMaxGraduationIndicate				=0;
	m_lXMinGraduationIndicate				=0;
	m_fXCurMaxValue							=0.0f;
	m_fYCurMaxValue							=0.0f;
	m_fXCurMinValue							=0.0f;
	m_fYCurMinValue							=0.0f;

	m_bShowXGrid							=TRUE;
	m_bShowYGrid							=TRUE;
	m_pXGridPen								=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_DOT,1,RGB(55,25,55));;
	m_pYGridPen								=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_DOT,1,RGB(55,25,55));;
	m_fXAxisMinGraduation					=30.0f;	//X轴最小刻度像素
	m_fYAxisMinGraduation					=30.0f;	//Y轴最小刻度像素
	m_bBindStatus							=FALSE;
	m_ZIndex								=-10;



	m_bShowAideYAxis					=FALSE;//是否显示副Y轴
	m_bAideYAxisBindPos					=FALSE;//副Y轴是否绑定位置
	m_fAideYAxisBindPos					=0.0f;
	m_pAideYAxisPen						=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(155,185,0));//副Y轴的画笔
	m_fAideYUnitValue					=1.0f;//副Y轴最小单位值
	m_fAideYCenterValue					=0.0f;//副Y轴中心点对应的值 
	m_fAideYCurMaxValue					=0.0f;//副Y轴当前最大值
	m_fAideYCurMinValue					=0.0f;//副Y轴当前最小值
	m_pAideYAxisName					=NULL;//副Y轴名字
	m_pAideYAxisNameFont				=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",12);//副Y轴名字字体
	m_AideYAxisNameColor				=RGB(50,200,150);//副Y轴名字颜色
	m_fAideYAxisMinGraduation			=30.0f;	//副Y轴最小刻度像素
	m_pAideYGraduationIndicateFont		=pCanvas->GetView()->GetResourceManager()->CreateFont("宋体",9);//副Y轴刻度文字字体
	m_YAideGraduationIndicateColor		=RGB(50,200,150);//副Y轴刻度文字颜色
	m_pAideYGraduationIndicatePen		=pCanvas->GetView()->GetResourceManager()->CreatePen(PS_SOLID,1,RGB(155,185,0));//副Y轴刻度画笔


	m_bShowYAxisAssistText				=FALSE;
	m_fYAxisAssistTextScale				=1.0f;
	m_YAxisAssistTextColor				=RGB(0,200,0);

	m_bMinusXAxis						=FALSE;
	m_bMinusYAxis						=FALSE;
}


CODLEx_Element_Coordinate::~CODLEx_Element_Coordinate(void)
{
	ODL_SafeDeleteArray(m_pXAxisName);
	ODL_SafeDeleteArray(m_pYAxisName);
	ODL_SafeDeleteArray(m_pAideYAxisName);

	ODL_SafeRelease(m_pXGridPen);
	ODL_SafeRelease(m_pYGridPen);

	ODL_SafeRelease(m_pXAxisPen);
	ODL_SafeRelease(m_pYAxisPen);
	ODL_SafeRelease(m_pAideYAxisPen);
	
	ODL_SafeRelease(m_pXGraduationIndicateFont);
	ODL_SafeRelease(m_pYGraduationIndicateFont);
	ODL_SafeRelease(m_pAideYGraduationIndicateFont);

	ODL_SafeRelease(m_pXAxisNameFont);
	ODL_SafeRelease(m_pYAxisNameFont);
	ODL_SafeRelease(m_pAideYAxisNameFont);

	ODL_SafeRelease(m_pXGraduationIndicateFont);
	ODL_SafeRelease(m_pYGraduationIndicateFont);
	ODL_SafeRelease(m_pAideYGraduationIndicateFont);

}
BOOL		CODLEx_Element_Coordinate::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	RECT			PaintRect = *pPaintRect;
	CODLEx_Element_CanvasTitle* pTitle =(CODLEx_Element_CanvasTitle*)GetCanvas()->GetCanvasTitle();
	if(pTitle != NULL)
	{
		if(pTitle->IsShow())
			PaintRect.top +=pTitle->GetTitleHeight();
	}

	DrawCoordinateAxis(hDC,&PaintRect);
	DrawCoordinateAideAxis(hDC,&PaintRect);
	DrawCoordinateName(hDC,&PaintRect);
	
	
	return TRUE;
}
VOID		CODLEx_Element_Coordinate::DrawCoordinateAxis(HDC IN hDC,RECT* IN pPaintRect)
{

	m_theXIndicateList.ClearList();
	m_theYIndicateList.ClearList();
	
	POINT		center;
	GetCenter(center);

	
	CHAR		Text[64];
	CHAR		Format[64];
	TEXTMETRIC	text_metric;
	RECT		text_rect;
	DWORD		text_len;
	AXISGRADUATIONINDICATE	indicate;

	LONG	i;
	FLOAT	x,prev_x,y,prev_y;



	m_pXAxisPen->Install(hDC);
	m_pXGraduationIndicateFont->Install(hDC);

	//--------------画X轴-----------------------------------
	MoveToEx(hDC,pPaintRect->left,center.y,NULL);
	LineTo(hDC,pPaintRect->right,center.y);
	
	m_pYAxisPen->Uninstall(hDC);
	m_pXGraduationIndicatePen->Install(hDC);

	COLORREF	OldColor	=SetTextColor(hDC,m_XGraduationIndicateColor);
	SetBkMode(hDC,TRANSPARENT);
	GetTextMetrics(hDC,&text_metric);
	sprintf(Format,"%%.%df",m_dwXGraduationIndicatePrecision);


	m_lXMaxGraduationIndicate =0;
	m_lXMinGraduationIndicate =0;
	//画刻度------------------------------------------------
	if(m_bMinusXAxis)
	{
		m_dwXAxisGraduationCount=0;
		i			=-1;
		prev_x		=center.x;
		x			=(FLOAT)center.x + m_fXPixelsPerUnit;
		m_fXCurMinValue		=(FLOAT)i * m_fXUnitValue + m_fXCenterValue;
		while( x < (FLOAT)pPaintRect->right)
		{
			m_fXCurMinValue		=(FLOAT)i * m_fXUnitValue + m_fXCenterValue;
			if( (x - prev_x) >= m_fXAxisMinGraduation)
			{
				if(m_bShowXGrid && m_pXGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,x,pPaintRect->bottom,&oldPt);
					m_pXGridPen->LineTo(hDC,x,pPaintRect->top);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}
				MoveToEx(hDC, x , center.y,NULL);
				LineTo(hDC	, x , center.y - m_dwGraduationLength);
			

				sprintf( Text , Format , m_fXCurMinValue );
				text_len	=strlen(Text);
				text_rect.left	=x - text_len * text_metric.tmMaxCharWidth/2;
				text_rect.right	=x + text_len * text_metric.tmMaxCharWidth/2;
				text_rect.top	=center.y;
				text_rect.bottom =center.y + text_metric.tmHeight;
				DrawText(hDC,Text,text_len,&text_rect,DT_CENTER|DT_VCENTER);
				prev_x =x;
			}

			i --;
			x += m_fXPixelsPerUnit;
			m_dwXAxisGraduationCount++;
			m_lXMaxGraduationIndicate++;

			indicate.pos	=x;
			indicate.value	=m_fXCurMinValue;
			m_theXIndicateList.AddTail(&indicate);
		}
		
		//负区间
		prev_x  =center.x;
		x		=(FLOAT)center.x - m_fXPixelsPerUnit;
		i		=1;
		m_fXCurMaxValue =(FLOAT)i * m_fXUnitValue + m_fXCenterValue ;
		while( x > (FLOAT)pPaintRect->left)
		{
			m_fXCurMaxValue =(FLOAT)i * m_fXUnitValue + m_fXCenterValue ;
			if( (prev_x - x) >= m_fXAxisMinGraduation)
			{
				if(m_bShowXGrid && m_pXGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,x,pPaintRect->bottom,&oldPt);
					m_pXGridPen->LineTo(hDC,x,pPaintRect->top);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}
			
				MoveToEx(hDC, x , center.y , NULL);
				LineTo(hDC,x,center.y-m_dwGraduationLength);
			
				sprintf( Text , Format , m_fXCurMaxValue);
				text_len	=strlen(Text);
				text_rect.left	=x - text_len * text_metric.tmMaxCharWidth/2;
				text_rect.right	=x + text_len * text_metric.tmMaxCharWidth/2;
				text_rect.top	=center.y;
				text_rect.bottom =center.y + text_metric.tmHeight;
				DrawText(hDC,Text,text_len,&text_rect,DT_CENTER|DT_VCENTER);
				prev_x =x;
			}


			i ++;
			x -= m_fXPixelsPerUnit;
			m_dwXAxisGraduationCount++;
			m_lXMinGraduationIndicate--;
		
			indicate.pos	=x;
			indicate.value	=m_fXCurMaxValue;
			m_theXIndicateList.AddHead(&indicate);
		}
	}
	else
	{
		m_dwXAxisGraduationCount=0;
		i			=1;
		prev_x		=center.x;
		x			=(FLOAT)center.x + m_fXPixelsPerUnit;
		m_fXCurMaxValue		=(FLOAT)i * m_fXUnitValue + m_fXCenterValue;
		while( x < (FLOAT)pPaintRect->right)
		{
			m_fXCurMaxValue		=(FLOAT)i * m_fXUnitValue + m_fXCenterValue;
			if( (x - prev_x) >= m_fXAxisMinGraduation)
			{
				if(m_bShowXGrid && m_pXGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,x,pPaintRect->bottom,&oldPt);
					m_pXGridPen->LineTo(hDC,x,pPaintRect->top);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}
				MoveToEx(hDC, x , center.y,NULL);
				LineTo(hDC	, x , center.y - m_dwGraduationLength);
			

				sprintf( Text , Format , m_fXCurMaxValue );
				text_len	=strlen(Text);
				text_rect.left	=x - text_len * text_metric.tmMaxCharWidth/2;
				text_rect.right	=x + text_len * text_metric.tmMaxCharWidth/2;
				text_rect.top	=center.y;
				text_rect.bottom =center.y + text_metric.tmHeight;
				DrawText(hDC,Text,text_len,&text_rect,DT_CENTER|DT_VCENTER);
				prev_x =x;
			}

			i ++;
			x += m_fXPixelsPerUnit;
			m_dwXAxisGraduationCount++;
			m_lXMaxGraduationIndicate++;

			indicate.pos	=x;
			indicate.value	=m_fXCurMaxValue;
			m_theXIndicateList.AddTail(&indicate);
		}
		
		//负区间
		x		=(FLOAT)center.x - m_fXPixelsPerUnit;
		prev_x  =center.x;
		i		=-1;
		m_fXCurMinValue =(FLOAT)i * m_fXUnitValue + m_fXCenterValue ;
		while( x > (FLOAT)pPaintRect->left)
		{
			m_fXCurMinValue =(FLOAT)i * m_fXUnitValue + m_fXCenterValue ;
			if( (prev_x - x) >= m_fXAxisMinGraduation)
			{
				if(m_bShowXGrid && m_pXGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,x,pPaintRect->bottom,&oldPt);
					m_pXGridPen->LineTo(hDC,x,pPaintRect->top);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}
			
				MoveToEx(hDC, x , center.y , NULL);
				LineTo(hDC,x,center.y-m_dwGraduationLength);
			
				sprintf( Text , Format , m_fXCurMinValue);
				text_len	=strlen(Text);
				text_rect.left	=x - text_len * text_metric.tmMaxCharWidth/2;
				text_rect.right	=x + text_len * text_metric.tmMaxCharWidth/2;
				text_rect.top	=center.y;
				text_rect.bottom =center.y + text_metric.tmHeight;
				DrawText(hDC,Text,text_len,&text_rect,DT_CENTER|DT_VCENTER);
				prev_x =x;
			}


			i --;
			x -= m_fXPixelsPerUnit;
			m_dwXAxisGraduationCount++;
			m_lXMinGraduationIndicate--;
		
			indicate.pos	=x;
			indicate.value	=m_fXCurMinValue;
			m_theXIndicateList.AddHead(&indicate);
		}
	}


	//------------------------------------------------------
	m_pXGraduationIndicatePen->Uninstall(hDC);
	m_pXGraduationIndicateFont->Uninstall(hDC);

	//---------------画Y轴----------------------------------
	m_pYAxisPen->Install(hDC);
	m_pYGraduationIndicateFont->Install(hDC);

	MoveToEx(hDC,center.x,pPaintRect->top,NULL);
	LineTo(hDC,center.x,pPaintRect->bottom);

	m_pYAxisPen->Uninstall(hDC);
	//---------------画刻度---------------------------------
	m_pYGraduationIndicatePen->Install(hDC);

	SetTextColor(hDC,m_YGraduationIndicateColor);
	SetBkMode(hDC,TRANSPARENT);
	GetTextMetrics(hDC,&text_metric);
	sprintf(Format,"%%.%df",m_dwYGraduationIndicatePrecision);

	if(m_bMinusYAxis)
	{
		m_dwYAxisGraduationCount	=0;
		prev_y		=center.y;
		y			=(FLOAT)center.y - m_fYPixelsPerUnit;
		i			=-1;
		m_fYCurMinValue		= (FLOAT)i * m_fYUnitValue + m_fYCenterValue;
		while( y > (FLOAT)pPaintRect->top)
		{
			m_fYCurMinValue		= (FLOAT)i * m_fYUnitValue + m_fYCenterValue;
			if( (prev_y -y) >= m_fYAxisMinGraduation)
			{
				if(m_bShowYGrid && m_pYGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,pPaintRect->left,y,&oldPt);
					m_pYGridPen->LineTo(hDC,pPaintRect->right,y);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}

				MoveToEx(hDC, center.x , y,NULL);
				LineTo(hDC	, center.x + m_dwGraduationLength, y );

				sprintf( Text , Format , m_fYCurMinValue);
				text_len			=strlen(Text);
				text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
				text_rect.right		=center.x-1;
				text_rect.top		=y - text_metric.tmHeight/2;
				text_rect.bottom	=y + text_metric.tmHeight/2;
				DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);

				if(m_bShowYAxisAssistText)
				{
					OldColor	=SetTextColor(hDC,m_YAxisAssistTextColor);
					sprintf( Text , Format , m_fYCurMinValue*m_fYAxisAssistTextScale);
					text_len			=strlen(Text);
					text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
					text_rect.top		-=text_metric.tmHeight;
					text_rect.bottom	-=text_metric.tmHeight;
					DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);
					SetTextColor(hDC,OldColor);
				}

				prev_y =y;
			}

			indicate.pos	=y;
			indicate.value	=m_fYCurMinValue;
			m_theYIndicateList.AddTail(&indicate);

			i --;
			y -= m_fYPixelsPerUnit;
			m_dwYAxisGraduationCount++;
		}

		prev_y		=center.y;
		y			=(FLOAT)center.y + m_fYPixelsPerUnit;
		i			=1;
		m_fYCurMaxValue =(FLOAT)i * m_fYUnitValue + m_fYCenterValue;
		while( y < (FLOAT)pPaintRect->bottom)
		{
			m_fYCurMaxValue =(FLOAT)i * m_fYUnitValue + m_fYCenterValue;
			if( (y-prev_y) >= m_fYAxisMinGraduation)
			{
				if(m_bShowYGrid && m_pYGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,pPaintRect->left,y,&oldPt);
					m_pYGridPen->LineTo(hDC,pPaintRect->right,y);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}
				MoveToEx(hDC,center.x,y,NULL);
				LineTo(hDC,center.x+m_dwGraduationLength,y);

				sprintf( Text , Format ,  m_fYCurMaxValue);
				text_len			=strlen(Text);
				text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
				text_rect.right		=center.x-1;
				text_rect.top		=y - text_metric.tmHeight/2;
				text_rect.bottom	=y + text_metric.tmHeight/2;
				DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);

				if(m_bShowYAxisAssistText)
				{
					OldColor	=SetTextColor(hDC,m_YAxisAssistTextColor);
					sprintf( Text , Format , m_fYCurMaxValue*m_fYAxisAssistTextScale);
					text_len			=strlen(Text);
					text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
					text_rect.top		-=text_metric.tmHeight;
					text_rect.bottom	-=text_metric.tmHeight;
					DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);
					SetTextColor(hDC,OldColor);
				}

				prev_y =y;
			}

			indicate.pos	=y;
			indicate.value	=m_fYCurMaxValue;
			m_theYIndicateList.AddHead(&indicate);

			i ++;
			y += m_fYPixelsPerUnit;
			m_dwYAxisGraduationCount++;
		}
	}
	else
	{
		m_dwYAxisGraduationCount	=0;
		y			=(FLOAT)center.y - m_fYPixelsPerUnit;
		prev_y		=center.y;
		i			=1;
		m_fYCurMaxValue		= (FLOAT)i * m_fYUnitValue + m_fYCenterValue;
		while( y > (FLOAT)pPaintRect->top)
		{
			m_fYCurMaxValue		= (FLOAT)i * m_fYUnitValue + m_fYCenterValue;
			if( (prev_y -y) >= m_fYAxisMinGraduation)
			{
				if(m_bShowYGrid && m_pYGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,pPaintRect->left,y,&oldPt);
					m_pYGridPen->LineTo(hDC,pPaintRect->right,y);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}

				MoveToEx(hDC, center.x , y,NULL);
				LineTo(hDC	, center.x + m_dwGraduationLength, y );

				sprintf( Text , Format , m_fYCurMaxValue);
				text_len			=strlen(Text);
				text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
				text_rect.right		=center.x-1;
				text_rect.top		=y - text_metric.tmHeight/2;
				text_rect.bottom	=y + text_metric.tmHeight/2;
				DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);

				if(m_bShowYAxisAssistText)
				{
					OldColor	=SetTextColor(hDC,m_YAxisAssistTextColor);
					sprintf( Text , Format , m_fYCurMaxValue*m_fYAxisAssistTextScale);
					text_len			=strlen(Text);
					text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
					text_rect.top		-=text_metric.tmHeight;
					text_rect.bottom	-=text_metric.tmHeight;
					DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);
					SetTextColor(hDC,OldColor);
				}

				prev_y =y;
			}

			indicate.pos	=y;
			indicate.value	=m_fYCurMaxValue;
			m_theYIndicateList.AddTail(&indicate);

			i ++;
			y -= m_fYPixelsPerUnit;
			m_dwYAxisGraduationCount++;
		}

		y			=(FLOAT)center.y + m_fYPixelsPerUnit;
		prev_y		=center.y;
		i			=-1;
		m_fYCurMinValue =(FLOAT)i * m_fYUnitValue + m_fYCenterValue;
		while( y < (FLOAT)pPaintRect->bottom)
		{
			m_fYCurMinValue =(FLOAT)i * m_fYUnitValue + m_fYCenterValue;
			if( (y-prev_y) >= m_fYAxisMinGraduation)
			{
				if(m_bShowYGrid && m_pYGridPen != NULL)
				{
					POINT oldPt;
					MoveToEx(hDC,pPaintRect->left,y,&oldPt);
					m_pYGridPen->LineTo(hDC,pPaintRect->right,y);
					MoveToEx(hDC,oldPt.x,oldPt.y,NULL);
				}
				MoveToEx(hDC,center.x,y,NULL);
				LineTo(hDC,center.x+m_dwGraduationLength,y);

				sprintf( Text , Format ,  m_fYCurMinValue);
				text_len			=strlen(Text);
				text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
				text_rect.right		=center.x-1;
				text_rect.top		=y - text_metric.tmHeight/2;
				text_rect.bottom	=y + text_metric.tmHeight/2;
				DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);
				if(m_bShowYAxisAssistText)
				{
					OldColor	=SetTextColor(hDC,m_YAxisAssistTextColor);
					sprintf( Text , Format , m_fYCurMinValue*m_fYAxisAssistTextScale);
					text_len			=strlen(Text);
					text_rect.left		=center.x - text_len * text_metric.tmMaxCharWidth;
					text_rect.top		-=text_metric.tmHeight;
					text_rect.bottom	-=text_metric.tmHeight;
					DrawText(hDC,Text,text_len,&text_rect,DT_RIGHT|DT_VCENTER);
					SetTextColor(hDC,OldColor);
				}

				prev_y =y;
			}

			indicate.pos	=y;
			indicate.value	=m_fYCurMinValue;
			m_theYIndicateList.AddHead(&indicate);

			i --;
			y += m_fYPixelsPerUnit;
			m_dwYAxisGraduationCount++;
		}
	}

	//------------------------------------------------------
	m_pYGraduationIndicateFont->Uninstall(hDC);
	m_pYGraduationIndicatePen->Uninstall(hDC);

}
VOID		CODLEx_Element_Coordinate::DrawCoordinateAideAxis(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_bShowAideYAxis)
	{
		if(m_bAideYAxisBindPos)
		{

		}
		else
		{
			LONG	x	=(pPaintRect->right - m_pAideYAxisPen->GetLogPen()->lopnWidth.x)-1;
			m_pAideYAxisPen->Install(hDC);
			MoveToEx(hDC,x,pPaintRect->top,NULL);
			LineTo(hDC,x,pPaintRect->bottom);
			m_pAideYAxisPen->Uninstall(hDC);

		}
	}
}

VOID		CODLEx_Element_Coordinate::SetCenterOffset(POINT* IN pCenter)
{
	if(pCenter == NULL)
		return;
	m_CenterOffset.x	=pCenter->x;
	m_CenterOffset.y	=pCenter->y;
	GetCanvas()->Invalidate(TRUE);
}
VOID		CODLEx_Element_Coordinate::SetCenterOffset(LONG IN x,LONG IN y)
{
	m_CenterOffset.x	=x;
	m_CenterOffset.y	=y;
	GetCanvas()->Invalidate(TRUE);
}
VOID		CODLEx_Element_Coordinate::GetCenterOffset(POINT& OUT centerOffset)
{
	centerOffset	=m_CenterOffset;
}

POINT*		CODLEx_Element_Coordinate::GetCenter(POINT& OUT center)
{
	center.x		=m_CurPaintRect.left	+ m_CenterOffset.x;
	center.y		=m_CurPaintRect.bottom	- m_CenterOffset.y;
	return &center;
}

VOID		CODLEx_Element_Coordinate::SetXPerUnitPixels(FLOAT IN fPixels)
{
	m_fXPixelsPerUnit	=fPixels;
	GetCanvas()->Invalidate(TRUE);
}
VOID		CODLEx_Element_Coordinate::SetXUnitValue(FLOAT IN fValue)
{
	m_fXUnitValue	=fValue;
	GetCanvas()->Invalidate(TRUE);
}
VOID		CODLEx_Element_Coordinate::SetXCenterUnitValue(FLOAT IN fValue)
{
	m_fXCenterValue		=fValue;
	GetCanvas()->Invalidate(TRUE);
}
VOID		CODLEx_Element_Coordinate::SetAxisName(LPCSTR IN pXAxisName,LPCSTR IN pYAxisName)
{
	DWORD			size	=strlen(pXAxisName)+1;
	m_pXAxisName		=new CHAR[size];
	ZeroMemory(m_pXAxisName,size);
	strcpy(m_pXAxisName,pXAxisName);


	size	=strlen(pYAxisName)+1;
	m_pYAxisName	=new CHAR[size];
	ZeroMemory(m_pYAxisName,size);
	strcpy(m_pYAxisName,pYAxisName);
	Invalidate(FALSE);
	GetCanvas()->Invalidate(FALSE);

}
VOID		CODLEx_Element_Coordinate::SetAxisNameFont(LOGFONT* IN pXAxisFont,LOGFONT* IN pYAxisFont)
{
	ODL_SafeRelease(m_pXAxisNameFont);
	m_pXAxisNameFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pXAxisFont);
	ODL_SafeRelease(m_pYAxisNameFont);
	m_pYAxisNameFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pYAxisFont);
	Invalidate(FALSE);
	GetCanvas()->Invalidate(FALSE);

}
VOID		CODLEx_Element_Coordinate::SetAxisNameColor(COLORREF IN xAxisClr,COLORREF IN yAxisClr)
{
	m_XAxisNameColor	=xAxisClr;
	m_YAxisNameColor	=yAxisClr;
	Invalidate(FALSE);
	GetCanvas()->Invalidate(FALSE);
}



VOID		CODLEx_Element_Coordinate::SetXAxisName(LPCSTR IN pName,COLORREF IN clr,LPCSTR IN pFontName,DWORD IN dwFontSize)
{	
	m_XAxisNameColor	=clr;
	ODL_SafeDeleteArray(m_pXAxisName);
	if(pName == NULL)
		return;
	DWORD			size	=strlen(pName)+1;
	m_pXAxisName		=new CHAR[size];
	ZeroMemory(m_pXAxisName,size);
	strcpy(m_pXAxisName,pName);
	
	ODL_SafeRelease(m_pXAxisNameFont);
	m_pXAxisNameFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize);
	GetCanvas()->Invalidate(FALSE);
}

VOID		CODLEx_Element_Coordinate::SetYPerUnitPixels(FLOAT IN fPixels)
{
	m_fYPixelsPerUnit	=fPixels;
	GetCanvas()->Invalidate(TRUE);
}

VOID		CODLEx_Element_Coordinate::SetYUnitValue(FLOAT IN fValue)
{
	m_fYUnitValue		=fValue;
	GetCanvas()->Invalidate(TRUE);
}

VOID		CODLEx_Element_Coordinate::SetYCenterUnitValue(FLOAT IN fValue)
{
	m_fYCenterValue		=fValue;
	GetCanvas()->Invalidate(TRUE);
}

VOID		CODLEx_Element_Coordinate::SetYAxisName(LPCSTR IN pName,COLORREF IN clr,LPCSTR IN pFontName,DWORD IN dwFontSize)
{
	ODL_SafeDeleteArray(m_pYAxisName);
	m_YAxisNameColor	=clr;
	if(pName == NULL)
		return;
	DWORD	size	=strlen(pName)+1;
	m_pYAxisName	=new CHAR[size];
	ZeroMemory(m_pYAxisName,size);
	strcpy(m_pYAxisName,pName);

	ODL_SafeRelease(m_pYAxisNameFont);
	m_pYAxisNameFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize);

	GetCanvas()->Invalidate(FALSE);
}


VOID		CODLEx_Element_Coordinate::MoveLeft(LONG IN lCount)
{
	m_fXCenterValue		-= ((FLOAT)lCount*m_fXUnitValue);
	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnCoordinate_DiagramDragEnd(this);

}
VOID		CODLEx_Element_Coordinate::MoveUp(LONG IN lCount)
{
	m_fYCenterValue		-= ((FLOAT)lCount*m_fYUnitValue);
	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnCoordinate_DiagramDragEnd(this);
}
VOID		CODLEx_Element_Coordinate::AxisMoveUp(LONG IN lPixels)
{
	m_CenterOffset.y	+= lPixels;
	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnCoordinate_DragEnd(this);
}

VOID		CODLEx_Element_Coordinate::AxisMoveLeft(LONG IN lPixels)
{
	m_CenterOffset.x	-= lPixels;
	Invalidate();

	if(m_pListener != NULL)
		m_pListener->OnCoordinate_DragEnd(this);

}
VOID		CODLEx_Element_Coordinate::ZoomRect(RECT* IN pRect)
{
	SaveStatus();

	FLOAT	fMinValue=0.0f,fMaxValue=0.0f;
	DWORD	dwCount		=0;

	AXISGRADUATIONINDICATE	* pIndicate=NULL;
	POSITION	pos =m_theXIndicateList.GetFirstPosition();
	while(pos != NULL)
	{
		pIndicate =m_theXIndicateList.GetAt(pos);
		if(pIndicate->pos >= pRect->left)
		{
			fMinValue = pIndicate->value;
			m_theXIndicateList.MoveNext(pos);
			break;
		}
		
		m_theXIndicateList.MoveNext(pos);
	}

	while(pos != NULL)
	{
		pIndicate =m_theXIndicateList.GetAt(pos);
		if(pIndicate->pos > pRect->right)
		{
			break;
		}
		
		fMaxValue	= pIndicate->value;
		dwCount		++;
		m_theXIndicateList.MoveNext(pos);
	}

	GetCanvas()->EnableAutoScroll(FALSE);

	POINT center;
	GetCenter(center);
	m_fXPixelsPerUnit	= (GetCanvas()->GetSize()->cx-center.x)/(dwCount+1);
	if(m_fXPixelsPerUnit <1.0f)
		m_fXPixelsPerUnit=1.0f;

	AbsLocate(fMinValue,TRUE);
	
}
VOID		CODLEx_Element_Coordinate::AbsLocate(FLOAT IN fXValue,BOOL IN bReturnOrign)
{
	if(bReturnOrign)
	{
		m_CenterOffset.x	=20;
		m_CenterOffset.y	=20;
	}
	m_fXCenterValue		=fXValue;
	Invalidate(TRUE);

	if(m_pListener != NULL)
		m_pListener->OnCoordinate_StatusChanged(this);

}
VOID		CODLEx_Element_Coordinate::SaveStatus()
{
	COORDINATESTATUS	status;
	status.fCenterXValue		=m_fXCenterValue;
	status.fCenterYValue		=m_fYCenterValue;
	status.fXAxisPixelPerUnit	=m_fXPixelsPerUnit;
	status.fYAxisPixelPerUnit	=m_fYPixelsPerUnit;
	status.vCenter.x			=m_CenterOffset.x;
	status.vCenter.y			=m_CenterOffset.y;
	status.bEnableScroll		=GetCanvas()->IsEnableAutoScroll();
	m_theCoordStatusSavedList.AddTail(&status);
	
}
VOID		CODLEx_Element_Coordinate::RestoreStatus(LONG IN lIndex)
{

	if(lIndex<0 || lIndex>= m_theCoordStatusSavedList.GetLength())
		return;

	COORDINATESTATUS*	pStatus		=m_theCoordStatusSavedList.GetAt(m_theCoordStatusSavedList.GetPosByIndex(lIndex));
	if(pStatus== NULL)
		return;
	
	m_fXCenterValue		=pStatus->fCenterXValue;
	m_fYCenterValue		=pStatus->fCenterYValue;
	m_fXPixelsPerUnit	=pStatus->fXAxisPixelPerUnit;
	m_fYPixelsPerUnit	=pStatus->fYAxisPixelPerUnit;
	m_CenterOffset		=pStatus->vCenter;
	
	GetCanvas()->EnableAutoScroll(pStatus->bEnableScroll);

	Invalidate();

	if(m_pListener != NULL)
		m_pListener->OnCoordinate_StatusChanged(this);

}
//得到当前状态
VOID		CODLEx_Element_Coordinate::GetStatus(COORDINATESTATUS& OUT status)
{
	status.fCenterXValue		=m_fXCenterValue;
	status.fCenterYValue		=m_fYCenterValue;
	status.fXAxisPixelPerUnit	=m_fXPixelsPerUnit;
	status.fYAxisPixelPerUnit	=m_fYPixelsPerUnit;
	status.vCenter.x			=m_CenterOffset.x;
	status.vCenter.y			=m_CenterOffset.y;
	status.bEnableScroll		=GetCanvas()->IsEnableAutoScroll();

}
//设置状态
VOID		CODLEx_Element_Coordinate::SetStatus(COORDINATESTATUS* IN status)
{
	m_fXCenterValue		=status->fCenterXValue;
	m_fYCenterValue		=status->fCenterYValue;
	m_fXPixelsPerUnit	=status->fXAxisPixelPerUnit;
	m_fYPixelsPerUnit	=status->fYAxisPixelPerUnit;
	m_CenterOffset		=status->vCenter;

	GetCanvas()->EnableAutoScroll(status->bEnableScroll);

	Invalidate();
	if(m_pListener != NULL)
		m_pListener->OnCoordinate_StatusChanged(this);

}

VOID		CODLEx_Element_Coordinate::SetGraduationLength(DWORD IN dwLen)
{
	m_dwGraduationLength	=dwLen;
	Invalidate();
}

VOID		CODLEx_Element_Coordinate::SetXGraduationIndicateColor(COLORREF IN clr)
{

	m_XGraduationIndicateColor	=clr;
	Invalidate();
}

VOID		CODLEx_Element_Coordinate::SetXGraduationIndicatePrecision(DWORD IN dwPrecision)
{
	m_dwXGraduationIndicatePrecision	=dwPrecision;
	if(m_dwXGraduationIndicatePrecision<0)
		m_dwXGraduationIndicatePrecision=0;
	if(m_dwXGraduationIndicatePrecision>8)
		m_dwXGraduationIndicatePrecision=8;
	Invalidate();
}


VOID		CODLEx_Element_Coordinate::SetYGraduationIndicateColor(COLORREF IN clr)
{
	m_YGraduationIndicateColor	=clr;
	Invalidate();
}

VOID		CODLEx_Element_Coordinate::SetYGraduationIndicatePrecision(DWORD IN dwPrecision)
{
	m_dwYGraduationIndicatePrecision	=dwPrecision;
	if(m_dwYGraduationIndicatePrecision<0)
		m_dwYGraduationIndicatePrecision=0;
	if(m_dwYGraduationIndicatePrecision>8)
		m_dwYGraduationIndicatePrecision=8;

	Invalidate();
}

BOOL		CODLEx_Element_Coordinate::StartDragAxis(POINT IN pt)
{
	if(IsKeyHoldPress('A')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS)
	{
		m_bAxisDraging		=TRUE;
		POINT	center;
		GetCenter(center);
		m_AxisDragOffsetByCenter.x	=center.x-pt.x;
		m_AxisDragOffsetByCenter.y	=center.y-pt.y;
		return TRUE;
	}
	else if(IsKeyHoldPress('X')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS_X)
	{
		m_bAxisDraging		=TRUE;
		POINT	center;
		GetCenter(center);
		m_AxisDragOffsetByCenter.x	=center.x-pt.x;
		m_AxisDragOffsetByCenter.y	=center.y-pt.y;
		return TRUE;
	}
	else if(IsKeyHoldPress('Y')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS_Y)
	{
		m_bAxisDraging		=TRUE;
		POINT	center;
		GetCenter(center);
		m_AxisDragOffsetByCenter.x	=center.x-pt.x;
		m_AxisDragOffsetByCenter.y	=center.y-pt.y;
		return TRUE;
	}
	return FALSE;
}
BOOL		CODLEx_Element_Coordinate::OnDragAxis(POINT IN pt)
{
	if(!m_bAxisDraging)
		return FALSE;

	if(IsKeyHoldPress('A')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS)
	{
		POINT	center;
		center.x	=pt.x + m_AxisDragOffsetByCenter.x;
		center.y	=pt.y + m_AxisDragOffsetByCenter.y;

		m_CenterOffset.x	=center.x - m_CurPaintRect.left;
		m_CenterOffset.y	=m_CurPaintRect.bottom - center.y;

		Invalidate(TRUE);

		return TRUE;
	}
	else if(IsKeyHoldPress('Y')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS_Y)
	{
		POINT	center;
		center.x	=pt.x + m_AxisDragOffsetByCenter.x;
		//center.y	=pt.y + m_AxisDragOffsetByCenter.y;

		m_CenterOffset.x	=center.x - m_CurPaintRect.left;
		//m_CenterOffset.y	=m_CurPaintRect.bottom - center.y;

		Invalidate(TRUE);
		return TRUE;
	}
	else if(IsKeyHoldPress('X')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS_X)
	{
		POINT	center;
		//center.x	=pt.x + m_AxisDragOffsetByCenter.x;
		center.y	=pt.y + m_AxisDragOffsetByCenter.y;

		//m_CenterOffset.x	=center.x - m_CurPaintRect.left;
		m_CenterOffset.y	=m_CurPaintRect.bottom - center.y;

		Invalidate(TRUE);

		return TRUE;
	}

	return FALSE;
}
BOOL		CODLEx_Element_Coordinate::OnEndDragAxis(POINT IN pt)
{
	if(!m_bAxisDraging)
		return FALSE;
	if(IsKeyHoldPress('A')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS)
	{
		POINT	center;
		center.x	=pt.x + m_AxisDragOffsetByCenter.x;
		center.y	=pt.y + m_AxisDragOffsetByCenter.y;

		m_CenterOffset.x	=center.x - m_CurPaintRect.left;
		m_CenterOffset.y	=m_CurPaintRect.bottom - center.y;

		Invalidate(TRUE);
		m_bAxisDraging	=FALSE;
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_DragEnd(this);
		return TRUE;
	}
	else if(IsKeyHoldPress('Y')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS_Y)
	{
		POINT	center;
		center.x	=pt.x + m_AxisDragOffsetByCenter.x;
		//center.y	=pt.y + m_AxisDragOffsetByCenter.y;

		m_CenterOffset.x	=center.x - m_CurPaintRect.left;
		//m_CenterOffset.y	=m_CurPaintRect.bottom - center.y;
		Invalidate(TRUE);
		m_bAxisDraging	=FALSE;
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_DragEnd(this);
		return TRUE;

	}
	else if(IsKeyHoldPress('X')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_AXIS_X)
	{
		POINT	center;
		//center.x	=pt.x + m_AxisDragOffsetByCenter.x;
		center.y	=pt.y + m_AxisDragOffsetByCenter.y;

		//m_CenterOffset.x	=center.x - m_CurPaintRect.left;
		m_CenterOffset.y	=m_CurPaintRect.bottom - center.y;

		Invalidate(TRUE);
		m_bAxisDraging	=FALSE;
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_DragEnd(this);
		return TRUE;

	}
	return FALSE;
}
BOOL		CODLEx_Element_Coordinate::OnZoomAxis(SHORT IN delta,POINT IN pt)
{
	delta /= 120;
	if(IsKeyHoldPress('A')||GetCanvas()->GetCurrentOperation() == ODL_OPER_SCALE_AXIS)
	{
		m_fXPixelsPerUnit		+= delta;
		if(m_fXPixelsPerUnit > (m_CurPaintRect.right-m_CurPaintRect.left)/4)
			m_fXPixelsPerUnit	=(m_CurPaintRect.right-m_CurPaintRect.left)/4;
		if(m_fXPixelsPerUnit < 1.0f)
			m_fXPixelsPerUnit =1.0f;

		m_fYPixelsPerUnit		+= delta;
		if(m_fYPixelsPerUnit > (m_CurPaintRect.bottom-m_CurPaintRect.top)/4)
			m_fYPixelsPerUnit = (m_CurPaintRect.bottom-m_CurPaintRect.top)/4;
		if(m_fYPixelsPerUnit < 1.0f)
			m_fYPixelsPerUnit =1.0f;

		Invalidate(TRUE);

		if(m_pListener != NULL)
			m_pListener->OnCoordinate_ZoomChanged(this);

		return TRUE;
	}
	else if(IsKeyHoldPress('X')||GetCanvas()->GetCurrentOperation() == ODL_OPER_SCALE_AXIS_X)
	{
		
		m_fXPixelsPerUnit		+= delta;
		if(m_fXPixelsPerUnit > (m_CurPaintRect.right-m_CurPaintRect.left)/4)
			m_fXPixelsPerUnit	=(m_CurPaintRect.right-m_CurPaintRect.left)/4;
		if(m_fXPixelsPerUnit < 1.0f)
			m_fXPixelsPerUnit =1.0f;
		
		Invalidate(TRUE);
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_ZoomChanged(this);
		return TRUE;
	}
	else if(IsKeyHoldPress('Y')||GetCanvas()->GetCurrentOperation() == ODL_OPER_SCALE_AXIS_Y)
	{
		
		m_fYPixelsPerUnit		+= delta;
		if(m_fYPixelsPerUnit > (m_CurPaintRect.bottom-m_CurPaintRect.top)/4)
			m_fYPixelsPerUnit = (m_CurPaintRect.bottom-m_CurPaintRect.top)/4;

		if(m_fYPixelsPerUnit < 1.0f)
			m_fYPixelsPerUnit =1.0f;
		
		Invalidate(TRUE);
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_ZoomChanged(this);
		return TRUE;
	}
	else
	{
		m_fXPixelsPerUnit		+= delta;
		if(m_fXPixelsPerUnit > (m_CurPaintRect.right-m_CurPaintRect.left)/4)
			m_fXPixelsPerUnit	=(m_CurPaintRect.right-m_CurPaintRect.left)/4;
		if(m_fXPixelsPerUnit < 1.0f)
			m_fXPixelsPerUnit =1.0f;

		Invalidate(TRUE);
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_ZoomChanged(this);
		return TRUE;
	}


	return FALSE;
}
BOOL		CODLEx_Element_Coordinate::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	POINT	point =*pPoint;
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
		
			if(StartDragAxis(point))
				return TRUE;
			if(StartDragDiagram(point))
				return TRUE;
		}
		break;
	case WM_LBUTTONUP:
		{
			if(OnEndDragAxis(point))
			{
				if(m_pListener != NULL)
					m_pListener->OnCoordinate_DragEnd(this);
				return TRUE;
			}
			if(OnEndDragDiagram(point))
			{
				if(m_pListener != NULL)
					m_pListener->OnCoordinate_DiagramDragEnd(this);
				return TRUE;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(OnDragAxis(point))
				return TRUE;
			if(OnDragDiagram(point))
				return TRUE;

		}
		break;
	case WM_MOUSEWHEEL:
		{
			SHORT	delta	=HIWORD(wParam);
			if(OnZoomAxis(delta,point))
			{
				if(m_pListener != NULL)
					m_pListener->OnCoordinate_ZoomChanged(this);
				return TRUE;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				{
					if(!m_theCoordStatusSavedList.IsEmpty())
					{
						RestoreStatus(m_theCoordStatusSavedList.GetLength()-1);
						m_theCoordStatusSavedList.DelTail();
						if(m_pListener != NULL)
							m_pListener->OnCoordinate_StatusChanged(this);
						return TRUE;
					}
				}
				break;
			}
		}
		break;
	default:
		break;
	}
	return FALSE;
}

BOOL		CODLEx_Element_Coordinate::StartDragDiagram(POINT IN pt)
{
	if(IsKeyHoldPress('D')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_DIAGRAM)
	{
		m_bDiagramDraging	=TRUE;
		m_ptStartDragPoint	=pt;
		m_vStartDragCenterValue.x	=m_fXCenterValue;
		m_vStartDragCenterValue.y	=m_fYCenterValue;
		return TRUE;
	}
	return FALSE;
}
BOOL		CODLEx_Element_Coordinate::OnDragDiagram(POINT IN pt)
{
	if(!m_bDiagramDraging)
		return FALSE;
	if(IsKeyHoldPress('D')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_DIAGRAM)
	{
		LONG	x =pt.x - m_ptStartDragPoint.x;
		LONG	y =pt.y - m_ptStartDragPoint.y;


		m_fXCenterValue	=m_vStartDragCenterValue.x - (LONG)( ( (float)x / m_fXPixelsPerUnit ) +0.5f);


		Invalidate(TRUE);


		return TRUE;
	}

	return FALSE;
}

BOOL		CODLEx_Element_Coordinate::OnEndDragDiagram(POINT IN pt)
{
	if(!m_bDiagramDraging)
		return FALSE;
	if(IsKeyHoldPress('D')||GetCanvas()->GetCurrentOperation() == ODL_OPER_DRAG_DIAGRAM)
	{
		m_bDiagramDraging =FALSE;

		LONG	x =pt.x - m_ptStartDragPoint.x;
		LONG	y =pt.y - m_ptStartDragPoint.y;


		m_fXCenterValue	=m_vStartDragCenterValue.x - (LONG)( ( (float)x / m_fXPixelsPerUnit ) +0.5f);


		Invalidate(TRUE);
		if(m_pListener != NULL)
			m_pListener->OnCoordinate_DiagramDragEnd(this);

		return TRUE;	
	}
	return FALSE;

}
LONG		CODLEx_Element_Coordinate::GetXByGraduationIndicate(LONG IN lGraduationIndicate)
{
	POINT center;
	GetCenter(center);
	return (LONG) ( center.x + (lGraduationIndicate*m_fXPixelsPerUnit) );
}
VOID		CODLEx_Element_Coordinate::SetXGraduationPara(DWORD IN dwLineWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pXGraduationIndicatePen);
	m_pXGraduationIndicatePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,dwLineWidth,clr);
	Invalidate();

}
VOID		CODLEx_Element_Coordinate::SetYGraduationPara(DWORD IN dwLineWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pYGraduationIndicatePen);
	m_pYGraduationIndicatePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,dwLineWidth,clr);
	Invalidate();
}
VOID		CODLEx_Element_Coordinate::SetGraduationPara(LOGPEN* IN pXPen,LOGPEN* IN pYPen)
{
	ODL_SafeRelease(m_pXGraduationIndicatePen);
	m_pXGraduationIndicatePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(pXPen);
	ODL_SafeRelease(m_pYGraduationIndicatePen);
	m_pYGraduationIndicatePen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(pYPen);
	Invalidate();
}




VOID		CODLEx_Element_Coordinate::SetXAxisPara(DWORD IN dwLineWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pXAxisPen);
	m_pXAxisPen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,dwLineWidth,clr);
	Invalidate();
}
VOID		CODLEx_Element_Coordinate::SetYAxisPara(DWORD IN dwLineWidth,COLORREF IN clr)
{
	ODL_SafeRelease(m_pYAxisPen);
	m_pYAxisPen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(PS_SOLID,dwLineWidth,clr);
	Invalidate();
}
VOID		CODLEx_Element_Coordinate::SetAxisPara(LOGPEN* IN pXAxisPen,LOGPEN* IN pYAxisPen)
{
	ODL_SafeRelease(m_pYAxisPen);
	ODL_SafeRelease(m_pXAxisPen);
	m_pXAxisPen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(pXAxisPen);
	m_pYAxisPen	=GetCanvas()->GetView()->GetResourceManager()->CreatePen(pYAxisPen);
	Invalidate();
}


VOID		CODLEx_Element_Coordinate::MinusXAxis(BOOL IN bMinus)
{
	if(m_bMinusXAxis == bMinus)
		return;
	m_bMinusXAxis =bMinus;
	Invalidate();
}
VOID		CODLEx_Element_Coordinate::MinusYAxis(BOOL IN bMinus)
{
	if(m_bMinusYAxis == bMinus)
		return;
	m_bMinusYAxis =bMinus;
	Invalidate();
}
VOID		CODLEx_Element_Coordinate::SetGraduationIndicateFont(LOGFONT* IN pXFont,LOGFONT* IN pYFont)
{
	ODL_SafeRelease(m_pXGraduationIndicateFont);
	m_pXGraduationIndicateFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pXFont);
	ODL_SafeRelease(m_pYGraduationIndicateFont);
	m_pYGraduationIndicateFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont(pYFont);
	Invalidate();

}
VOID		CODLEx_Element_Coordinate::SetGraduationIndicateColor(COLORREF IN xClr,COLORREF IN yClr)
{
	m_XGraduationIndicateColor	=xClr;
	m_YGraduationIndicateColor	=yClr;
	Invalidate();
}



VOID		CODLEx_Element_Coordinate::SetXGraduationIndicateFont(LPCSTR IN pFontName,DWORD IN dwFontSize)
{
	ODL_SafeRelease(m_pXGraduationIndicateFont);
	m_pXGraduationIndicateFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize);
	Invalidate();
}
VOID		CODLEx_Element_Coordinate::SetYGraduationIndicateFont(LPCSTR IN pFontName,DWORD IN dwFontSize)
{
	ODL_SafeRelease(m_pYGraduationIndicateFont);
	m_pYGraduationIndicateFont	=GetCanvas()->GetView()->GetResourceManager()->CreateFont((CHAR*)pFontName,dwFontSize);
	Invalidate();
}


VOID		CODLEx_Element_Coordinate::DrawCoordinateName(HDC IN hDC,RECT* IN pPaintRect)
{
	if(m_pYAxisName != NULL && m_pYAxisNameFont != NULL)
	{
		m_pYAxisNameFont->Install(hDC);

		COLORREF	OldColor		=SetTextColor(hDC,m_YAxisNameColor);
		INT			iBkMode			=SetBkMode(hDC,TRANSPARENT);
		
		RECT	 rec;
		TEXTMETRIC	metric;
		GetTextMetrics(hDC,&metric);

		if(m_bMinusYAxis)
		{
			rec.left	=m_CenterOffset.x+m_dwGraduationLength;
			rec.bottom	=pPaintRect->bottom;		
			rec.top		=rec.bottom - metric.tmHeight;
			rec.right	=rec.left+ strlen(m_pYAxisName)*metric.tmMaxCharWidth;

		}
		else
		{
			rec.left	=m_CenterOffset.x+m_dwGraduationLength;
			rec.top		=pPaintRect->top;	
			rec.bottom	=rec.top + metric.tmHeight;
			rec.right	=rec.left+ strlen(m_pYAxisName)*metric.tmMaxCharWidth;
		}
		DrawText(hDC,m_pYAxisName,strlen(m_pYAxisName),&rec,DT_LEFT|DT_VCENTER);




		m_pYAxisNameFont->Uninstall(hDC);
		SetTextColor(hDC,OldColor);
		SetBkMode(hDC,iBkMode);
	}


	if(m_pXAxisName != NULL && m_pXAxisNameFont != NULL)
	{
		m_pXAxisNameFont->Install(hDC);
		COLORREF	OldColor		=SetTextColor(hDC,m_XAxisNameColor);
		INT			iBkMode			=SetBkMode(hDC,TRANSPARENT);

		TEXTMETRIC	metric;
		GetTextMetrics(hDC,&metric);

		RECT	 rec;
		if(m_bMinusXAxis)
		{
			rec.left	=pPaintRect->left;
			rec.right	=rec.left + strlen(m_pXAxisName)*metric.tmMaxCharWidth;
		
			rec.bottom	=pPaintRect->bottom -m_CenterOffset.y;
			rec.top		=rec.bottom - metric.tmHeight-m_dwGraduationLength;

			DrawText(hDC,m_pXAxisName,strlen(m_pXAxisName),&rec,DT_LEFT|DT_TOP);
		}
		else
		{
			rec.right	=pPaintRect->right;
			rec.left	=rec.right- strlen(m_pXAxisName)*metric.tmMaxCharWidth;
	
			rec.bottom	=pPaintRect->bottom -m_CenterOffset.y;
			rec.top		=rec.bottom - metric.tmHeight-m_dwGraduationLength;
			DrawText(hDC,m_pXAxisName,strlen(m_pXAxisName),&rec,DT_RIGHT|DT_TOP);
		}



		m_pXAxisNameFont->Uninstall(hDC);

		SetTextColor(hDC,OldColor);
		SetBkMode(hDC,iBkMode);

	}

}
VOID				CODLEx_Element_Coordinate::SetGridLineSytle(LOGPEN* IN pXPen,LOGPEN* IN pYPen)
{
	ODL_SafeRelease(m_pXGridPen);
	m_pXGridPen =GetCanvas()->GetView()->GetResourceManager()->CreatePen(pXPen);
	ODL_SafeRelease(m_pYGridPen);
	m_pYGridPen =GetCanvas()->GetView()->GetResourceManager()->CreatePen(pYPen);
	Invalidate();
}

VOID				CODLEx_Element_Coordinate::SetXGridLineStyle(UINT IN uPenStyle,UINT IN uWidth,UINT IN clr)
{
	ODL_SafeRelease(m_pXGridPen);
	m_pXGridPen =GetCanvas()->GetView()->GetResourceManager()->CreatePen(uPenStyle,uWidth,clr);
	Invalidate();
}
VOID				CODLEx_Element_Coordinate::ShowXGrid(BOOL IN bShow)
{
	m_bShowXGrid	=bShow;
	Invalidate();
}

VOID				CODLEx_Element_Coordinate::SetYGridLineStyle(UINT IN uPenStyle,UINT IN uWidth,UINT IN clr)
{
	ODL_SafeRelease(m_pYGridPen);
	m_pYGridPen =GetCanvas()->GetView()->GetResourceManager()->CreatePen(uPenStyle,uWidth,clr);
	Invalidate();
}
VOID				CODLEx_Element_Coordinate::ShowYGrid(BOOL IN bShow)
{
	m_bShowYGrid	=bShow;
	Invalidate();
}
VOID				CODLEx_Element_Coordinate::SetMinGraduationValue(FLOAT IN fXValue,FLOAT IN fYValue)
{
	m_fXAxisMinGraduation					=fXValue;	//X轴最小刻度像素
	m_fYAxisMinGraduation					=fYValue;	//Y轴最小刻度像素
	Invalidate();
}
BOOL				CODLEx_Element_Coordinate::SetGraduationRange(FLOAT IN fMinX,FLOAT IN fCenterX,FLOAT IN fMaxX,
																  FLOAT IN fMinY,FLOAT IN fCenterY,FLOAT IN fMaxY)
{
	if( fabs(fMaxX - fMinX) < 1.0f || fabs(fMaxY-fMinY) < 1.0f )
	{
		return FALSE;
	}

	LONG								lCanvasTitleHeight	=0;
	CODLEx_Element_CanvasTitle*			pCanvasTitle		=(CODLEx_Element_CanvasTitle*)GetCanvas()->GetCanvasTitle();
	if(pCanvasTitle!=NULL)
	{
		if(pCanvasTitle->IsShow())
		{
			lCanvasTitleHeight	=pCanvasTitle->GetTitleHeight();
		}
	}
	
	SIZE	CanvasSize	=*GetCanvas()->GetSize();
	CanvasSize.cy	-=lCanvasTitleHeight;


	float	MaxXValue	=fabs(fMaxX-fMinX);
	float	MaxYValue	=fabs(fMaxY-fMinY);

	DWORD	XCount		=(MaxXValue / m_fXUnitValue)+1;
	DWORD	YCount		=(MaxYValue / m_fYUnitValue)+1;

	m_fXCenterValue		=fCenterX;
	m_fYCenterValue		=fCenterY;
	POINT	center;
	center.x	=(LONG)(( (m_fXCenterValue-fMinX)/MaxXValue )*(float)CanvasSize.cx);
	center.y	=(LONG)(( (m_fYCenterValue-fMinY)/MaxYValue )*(float)CanvasSize.cy);

	//////////////////////////
	m_CenterOffset		=center;
	m_fXPixelsPerUnit	=(float)CanvasSize.cx/(float)XCount;
	m_fYPixelsPerUnit	=(float)CanvasSize.cy/(float)YCount;
	
	
	Invalidate();
	return TRUE;
}
VOID		CODLEx_Element_Coordinate::OnPreCanvasSizeChange()//画布大小改变前
{
	if(m_bBindStatus)
	{
		m_BindState.fMinX	=GetXMinValue();
		m_BindState.fCenterX=GetXCenterUnitValue();
		m_BindState.fMaxX	=GetXMaxValue();
		m_BindState.fMinY	=GetYMinValue();
		m_BindState.fCenterY=GetYCenterUnitValue();
		m_BindState.fMaxY	=GetYMaxValue();
	
	}
}
VOID		CODLEx_Element_Coordinate::OnEndCanvasSizeChange()//画布大小改变后
{
	if(m_bBindStatus)
	{
		SetGraduationRange(		
						m_BindState.fMinX,
						m_BindState.fCenterX,
						m_BindState.fMaxX,
						m_BindState.fMinY,
						m_BindState.fCenterY,
						m_BindState.fMaxY);
	}
}

LONG				CODLEx_Element_Coordinate::XValueToCoordSpacce(FLOAT IN ValueX)
{
	POINT center;
	GetCenter(center);
	LONG PosX =0;
	if(m_bMinusXAxis)
		PosX	= center.x - ( ( (ValueX-GetXCenterUnitValue()) / GetXUnitValue()) * GetXPerUnitPixels() );
	else
		PosX	= center.x + ( ( (ValueX-GetXCenterUnitValue()) / GetXUnitValue()) * GetXPerUnitPixels() );
	return PosX;
}
FLOAT				CODLEx_Element_Coordinate::CoordSpaceToXValue(LONG IN PosX)
{
	POINT center;
	GetCenter(center);
	FLOAT ValueX =0.0f;
	if(m_bMinusXAxis)
		ValueX	=GetXCenterUnitValue() - ((PosX-center.x)/GetXPerUnitPixels())*GetXUnitValue();
	else
		ValueX	=GetXCenterUnitValue() + ((PosX-center.x)/GetXPerUnitPixels())*GetXUnitValue();
	return ValueX;
}

LONG				CODLEx_Element_Coordinate::YValueToCoordSpacce(FLOAT IN ValueY)
{
	POINT center;
	LONG PosY	=0;
	GetCenter(center);
	if(m_bMinusYAxis)
		PosY	= center.y + ( ( (ValueY-GetYCenterUnitValue()) / GetYUnitValue()) * GetYPerUnitPixels() );
	else
		PosY	= center.y - ( ( (ValueY-GetYCenterUnitValue()) / GetYUnitValue()) * GetYPerUnitPixels() );
	return PosY;
}
FLOAT				CODLEx_Element_Coordinate::CoordSpaceToYValue(LONG IN PosY)
{
	POINT center;
	GetCenter(center);	
	FLOAT ValueY=0.0f;
	if(m_bMinusYAxis)
		ValueY =GetYCenterUnitValue() + ((PosY-center.y)/GetYPerUnitPixels())*GetYUnitValue() ;
	else
		ValueY =GetYCenterUnitValue() - ((PosY-center.y)/GetYPerUnitPixels())*GetYUnitValue() ;
	return ValueY;
}











