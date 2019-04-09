#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Coordinate.h
	created:	2012/03/13
	author:		LB
	purpose:	坐标轴类
\*********************************************************************/
typedef struct _AxisGraduationIndicate
{
	LONG		pos;
	FLOAT		value;
}AXISGRADUATIONINDICATE;

typedef struct ODLEX_EXPORT _CoordinateStatus
{
	FLOAT			fCenterXValue;
	FLOAT			fXAxisPixelPerUnit;

	FLOAT			fCenterYValue;
	FLOAT			fYAxisPixelPerUnit;

	POINT			vCenter;
	BOOL			bEnableScroll;
}COORDINATESTATUS;

typedef struct ODLEX_EXPORT _CoordRangeStatus
{
	FLOAT			fMinX;
	FLOAT			fCenterX;
	FLOAT			fMaxX;
	FLOAT			fMinY;
	FLOAT			fCenterY;
	FLOAT			fMaxY;
}COORDRANGESTATUS;

class ODLEX_EXPORT CODLEx_Element_Coordinate :
	public CODL_ElementBase
{
protected:
	POINT				m_CenterOffset;		//坐标原点相对于绘图区域的偏移
	
	DWORD				m_dwGraduationLength;//刻度长

	CODL_Pen*			m_pXAxisPen;		//X轴的画笔
	CODL_Pen*			m_pYAxisPen;		//Y轴的画笔

	
	FLOAT				m_fXPixelsPerUnit;	//最小单位多少个象素点
	FLOAT				m_fXUnitValue;		//最小单位值
	FLOAT				m_fXCenterValue;	//X轴中心点对应的值
	FLOAT				m_fXCurMaxValue;	//X轴最大值 
	FLOAT				m_fXCurMinValue;	//X轴最大值 

	CHAR*				m_pXAxisName;		//X轴名称
	CODL_Font*			m_pXAxisNameFont;	//X轴名称的字体
	COLORREF			m_XAxisNameColor;	//X轴名称颜色

	FLOAT				m_fYPixelsPerUnit;	//最小单位多少个象素点
	FLOAT				m_fYUnitValue;		//最小单位值
	FLOAT				m_fYCenterValue;	//Y轴中心点对应的值 
	FLOAT				m_fYCurMaxValue;
	FLOAT				m_fYCurMinValue;
	CHAR*				m_pYAxisName;
	CODL_Font*			m_pYAxisNameFont;
	COLORREF			m_YAxisNameColor;

	FLOAT				m_fXAxisMinGraduation;	//X轴最小刻度像素
	FLOAT				m_fYAxisMinGraduation;	//Y轴最小刻度像素

	BOOL				m_bMinusXAxis;			//是否反向X轴
	BOOL				m_bMinusYAxis;			//是否反向Y轴
protected:
	COLORREF			m_YAxisAssistTextColor;
	BOOL				m_bShowYAxisAssistText;
	FLOAT				m_fYAxisAssistTextScale;
protected:
	BOOL				m_bShowAideYAxis;					//是否显示副Y轴
	BOOL				m_bAideYAxisBindPos;				//副Y轴是否绑定位置
	FLOAT				m_fAideYAxisBindPos;				//副Y轴绑定在X轴上的位置值
	CODL_Pen*			m_pAideYAxisPen;					//副Y轴的画笔
	FLOAT				m_fAideYUnitValue;					//副Y轴最小单位值
	FLOAT				m_fAideYCenterValue;				//副Y轴中心点对应的值 
	FLOAT				m_fAideYCurMaxValue;				//副Y轴当前最大值
	FLOAT				m_fAideYCurMinValue;				//副Y轴当前最小值
	CHAR*				m_pAideYAxisName;					//副Y轴名字
	CODL_Font*			m_pAideYAxisNameFont;				//副Y轴名字字体
	COLORREF			m_AideYAxisNameColor;				//副Y轴名字颜色
	FLOAT				m_fAideYAxisMinGraduation;			//副Y轴最小刻度像素
	CODL_Font*			m_pAideYGraduationIndicateFont;		//副Y轴刻度文字字体
	COLORREF			m_YAideGraduationIndicateColor;		//副Y轴刻度文字颜色
	CODL_Pen*			m_pAideYGraduationIndicatePen;		//副Y轴刻度画笔

protected:

	CODL_Font*			m_pXGraduationIndicateFont;//X轴刻度文字字体
	CODL_Pen*			m_pXGraduationIndicatePen;
	COLORREF			m_XGraduationIndicateColor;	//X轴刻度文字颜色
	DWORD				m_dwXGraduationIndicatePrecision;//X轴刻度值精度

	CODL_Font*			m_pYGraduationIndicateFont;//Y轴刻度文字字体
	CODL_Pen*			m_pYGraduationIndicatePen;
	COLORREF			m_YGraduationIndicateColor;	//Y轴刻度文字颜色
	DWORD				m_dwYGraduationIndicatePrecision;//Y轴刻度值精度

	DWORD				m_dwXAxisGraduationCount;
	DWORD				m_dwYAxisGraduationCount;

protected:
	BOOL				m_bAxisDraging;
	POINT				m_AxisDragOffsetByCenter;

	BOOL				m_bDiagramDraging;
	CODL_Vector2f		m_vStartDragCenterValue;
	POINT				m_ptStartDragPoint;
protected:
	LONG				m_lXMaxGraduationIndicate;
	LONG				m_lXMinGraduationIndicate;

	COORDRANGESTATUS	m_BindState;	//保存绑定的状态
	BOOL				m_bBindStatus;	//是否绑定状态,绑定状态时画布大小改变不影响坐标轴显示范围

protected:
	BOOL				m_bShowXGrid;
	BOOL				m_bShowYGrid;
	CODL_Pen*			m_pXGridPen;
	CODL_Pen*			m_pYGridPen;
protected:
	CODL_ListT<AXISGRADUATIONINDICATE>		m_theXIndicateList;
	CODL_ListT<AXISGRADUATIONINDICATE>		m_theYIndicateList;
	CODL_ListT<COORDINATESTATUS>			m_theCoordStatusSavedList;
	
public:
	CODLEx_Element_Coordinate(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Coordinate(void);
public:
	VOID				SetCenterOffset(POINT* IN pCenter);
	VOID				SetCenterOffset(LONG IN x,LONG IN y);
	VOID				GetCenterOffset(POINT& OUT centerOffset);
	POINT*				GetCenter(POINT& OUT center);
	
	//设置刻度的长
	VOID				SetGraduationLength(DWORD IN dwLen);
	DWORD				GetGraduationLength(){return m_dwGraduationLength;}

	DWORD				GetXGraduationWidth(){return m_pXGraduationIndicatePen->GetLogPen()->lopnWidth.x;}
	DWORD				GetYGraduationWidth(){return m_pYGraduationIndicatePen->GetLogPen()->lopnWidth.x;}
	
	COLORREF			GetXGraduationColor(){return m_pXGraduationIndicatePen->GetLogPen()->lopnColor;}
	COLORREF			GetYGraduationColor(){return m_pYGraduationIndicatePen->GetLogPen()->lopnColor;}

	VOID				SetXGraduationPara(DWORD IN dwLineWidth,COLORREF IN clr);
	VOID				SetYGraduationPara(DWORD IN dwLineWidth,COLORREF IN clr);
	VOID				SetGraduationPara(LOGPEN* IN pXPen,LOGPEN* IN pYPen);



	COLORREF			GetXAxisColor(){return m_pXAxisPen->GetLogPen()->lopnColor;}
	COLORREF			GetYAxisColor(){return m_pYAxisPen->GetLogPen()->lopnColor;}
	DWORD				GetXAxisWidth(){return m_pXAxisPen->GetLogPen()->lopnWidth.x;}
	DWORD				GetYAxisWidth(){return m_pYAxisPen->GetLogPen()->lopnWidth.x;}

	VOID				SetXAxisPara(DWORD IN dwLineWidth,COLORREF IN clr);
	VOID				SetYAxisPara(DWORD IN dwLineWidth,COLORREF IN clr);
	VOID				SetAxisPara(LOGPEN* IN pXAxisPen,LOGPEN* IN pYAxisPen);


	BOOL				IsMinusXAxis(){return m_bMinusXAxis;}
	BOOL				IsMinusYAxis(){return m_bMinusYAxis;}
	VOID				MinusXAxis(BOOL IN bMinus);
	VOID				MinusYAxis(BOOL IN bMinus);
public:
	COLORREF			GetYAxisAssistTextColor(){return m_YAxisAssistTextColor;}
	VOID				SetYAxisAssistTextColor(COLORREF IN clr){m_YAxisAssistTextColor=clr;Invalidate();}
	BOOL				IsShowYAxisAssistText(){return m_bShowYAxisAssistText;}
	VOID				EnableShowYAxisAssistText(BOOL IN bEnable){m_bShowYAxisAssistText=bEnable;Invalidate();}
	FLOAT				GetYAxisAssistTextScale(){return m_fYAxisAssistTextScale;}
	VOID				SetYAxisAssistTextScale(FLOAT IN fYAxisAssistTextScale){m_fYAxisAssistTextScale=fYAxisAssistTextScale;Invalidate();}

public:
	
	FLOAT				GetXPerUnitPixels(){return m_fXPixelsPerUnit;}
	VOID				SetXPerUnitPixels(FLOAT IN fPixels);
    
	FLOAT				GetXUnitValue(){return m_fXUnitValue;}
	VOID				SetXUnitValue(FLOAT IN fValue);

	FLOAT				GetXCenterUnitValue(){return m_fXCenterValue;}
	VOID				SetXCenterUnitValue(FLOAT IN fValue);

	VOID				SetAxisName(LPCSTR IN pXAxisName,LPCSTR IN pYAxisName);
	VOID				SetAxisNameFont(LOGFONT* IN pXAxisFont,LOGFONT* IN pYAxisFont);
	VOID				SetAxisNameColor(COLORREF IN xAxisClr,COLORREF IN yAxisClr);


	VOID				SetXAxisName(LPCSTR IN pName,COLORREF IN clr,LPCSTR IN pFontName,DWORD IN dwFontSize);

	LPCSTR				GetXAxisName(){return m_pXAxisName;}
	COLORREF			GetXAxisNameColor(){return m_XAxisNameColor;}
	LOGFONT*			GetXAxisNameFont(){return m_pXAxisNameFont->GetLogFont();}

	DWORD				GetXAxisGraduationCount(){return m_dwXAxisGraduationCount;}
	FLOAT				GetXMaxValue(){return m_fXCurMaxValue;}
	FLOAT				GetXMinValue(){return m_fXCurMinValue;}

public:

	FLOAT				GetYPerUnitPixels(){return m_fYPixelsPerUnit;}
	VOID				SetYPerUnitPixels(FLOAT IN fPixels);

	FLOAT				GetYUnitValue(){return m_fYUnitValue;}
	VOID				SetYUnitValue(FLOAT IN fValue);

	FLOAT				GetYCenterUnitValue(){return m_fYCenterValue;}
	VOID				SetYCenterUnitValue(FLOAT IN fValue);

	VOID				SetYAxisName(LPCSTR IN pName,COLORREF IN clr,LPCSTR IN pFontName,DWORD IN dwFontSize);
	LPCSTR				GetYAxisName(){return m_pYAxisName;}
	COLORREF			GetYAxisNameColor(){return m_YAxisNameColor;}
	LOGFONT*			GetYAxisNameFont(){return m_pYAxisNameFont->GetLogFont();}

	DWORD				GetYAxisGraduationCount(){return m_dwYAxisGraduationCount;}

	FLOAT				GetYMaxValue(){return m_fYCurMaxValue;}
	FLOAT				GetYMinValue(){return m_fYCurMinValue;}

public:
	VOID				SetGraduationIndicateFont(LOGFONT* IN pXFont,LOGFONT* IN pYFont);
	VOID				SetGraduationIndicateColor(COLORREF IN xClr,COLORREF IN yClr);

	LOGFONT*			GetXGraduationIndicateFont(){return m_pXGraduationIndicateFont->GetLogFont();}
	VOID				SetXGraduationIndicateFont(LPCSTR IN pFontName,DWORD IN dwFontSize);

	COLORREF			GetXGraduationIndicateColor(){return m_XGraduationIndicateColor;}
	VOID				SetXGraduationIndicateColor(COLORREF IN clr);

	DWORD				GetXGraduationIndicatePrecision(){return m_dwXGraduationIndicatePrecision;}
	VOID				SetXGraduationIndicatePrecision(DWORD IN dwPrecision);


	LOGFONT*			GetYGraduationIndicateFont(){return m_pYGraduationIndicateFont->GetLogFont();}
	VOID				SetYGraduationIndicateFont(LPCSTR IN pFontName,DWORD IN dwFontSize);

	COLORREF			GetYGraduationIndicateColor(){return m_YGraduationIndicateColor;}
	VOID				SetYGraduationIndicateColor(COLORREF IN clr);

	DWORD				GetYGraduationIndicatePrecision(){return m_dwYGraduationIndicatePrecision;}
	VOID				SetYGraduationIndicatePrecision(DWORD IN dwPrecision);


	//与自动合并有关
	VOID				SetMinGraduationValue(FLOAT IN fXValue,FLOAT IN fYValue);
	FLOAT				GetMinGraduationXValue(){return m_fXAxisMinGraduation;}
	FLOAT				GetMinGraduationYValue(){return m_fYAxisMinGraduation;}

public:
	LONG				GetXByGraduationIndicate(LONG IN lGraduationIndicate);
	LONG				GetXMinGraduationIndicate(){return m_lXMinGraduationIndicate;}
	LONG				GetXMaxGraduationIndicate(){return m_lXMaxGraduationIndicate;}


public:
	VOID				SetGridLineSytle(LOGPEN* IN pXPen,LOGPEN* IN pYPen);

	VOID				SetXGridLineStyle(UINT IN uPenStyle,UINT IN uWidth,UINT IN clr);
	VOID				ShowXGrid(BOOL IN bShow);
	
	VOID				SetYGridLineStyle(UINT IN uPenStyle,UINT IN uWidth,UINT IN clr);
	VOID				ShowYGrid(BOOL IN bShow);
public:
	LONG				XValueToCoordSpacce(FLOAT IN ValueX);
	FLOAT				CoordSpaceToXValue(LONG IN PosX);

	LONG				YValueToCoordSpacce(FLOAT IN ValueY);
	FLOAT				CoordSpaceToYValue(LONG IN PosY);



public:
	virtual VOID		MoveLeft(LONG IN lCount);
	virtual VOID		MoveUp(LONG IN lCount);

	virtual VOID		AxisMoveUp(LONG IN lPixels);
	virtual VOID		AxisMoveLeft(LONG IN lPixels);

	virtual VOID		ZoomRect(RECT* IN pRect);
	virtual VOID		AbsLocate(FLOAT IN fXValue,BOOL IN bReturnOrign=FALSE);

	virtual VOID		SaveStatus();	
	virtual VOID		RestoreStatus(LONG IN lIndex);


	//得到当前状态
	virtual VOID		GetStatus(COORDINATESTATUS& OUT status);
	//设置状态
	virtual VOID		SetStatus(COORDINATESTATUS* IN status);
	
	//当画布大小改变时，是否固定坐标轴显示范围，
	virtual VOID		EnableBindStatus(BOOL IN bEnable){m_bBindStatus=bEnable;}

	//设置坐标轴显示范围
	/*该函数依赖于当前画布的大小和标题栏是否显示*/
	BOOL				SetGraduationRange( FLOAT IN fMinX,FLOAT IN fCenterX,FLOAT IN fMaxX,
											FLOAT IN fMinY,FLOAT IN fCenterY,FLOAT IN fMaxY);

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
protected:
	BOOL				StartDragAxis(POINT IN pt);
	BOOL				OnDragAxis(POINT IN pt);
	BOOL				OnEndDragAxis(POINT IN pt);
	BOOL				OnZoomAxis(SHORT IN delta,POINT IN pt);

	BOOL				StartDragDiagram(POINT IN pt);
	BOOL				OnDragDiagram(POINT IN pt);
	BOOL				OnEndDragDiagram(POINT IN pt);

protected:
	VOID				DrawCoordinateAxis(HDC IN hDC,RECT* IN pPaintRect);
	VOID				DrawCoordinateAideAxis(HDC IN hDC,RECT* IN pPaintRect);
	VOID				DrawCoordinateName(HDC IN hDC,RECT* IN pPaintRect);
	virtual VOID		OnPreCanvasSizeChange();//画布大小改变前
	virtual VOID		OnEndCanvasSizeChange();//画布大小改变后

	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);

};
