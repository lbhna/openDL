#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_Coordinate.h
	created:	2012/03/13
	author:		LB
	purpose:	��������
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
	POINT				m_CenterOffset;		//����ԭ������ڻ�ͼ�����ƫ��
	
	DWORD				m_dwGraduationLength;//�̶ȳ�

	CODL_Pen*			m_pXAxisPen;		//X��Ļ���
	CODL_Pen*			m_pYAxisPen;		//Y��Ļ���

	
	FLOAT				m_fXPixelsPerUnit;	//��С��λ���ٸ����ص�
	FLOAT				m_fXUnitValue;		//��С��λֵ
	FLOAT				m_fXCenterValue;	//X�����ĵ��Ӧ��ֵ
	FLOAT				m_fXCurMaxValue;	//X�����ֵ 
	FLOAT				m_fXCurMinValue;	//X�����ֵ 

	CHAR*				m_pXAxisName;		//X������
	CODL_Font*			m_pXAxisNameFont;	//X�����Ƶ�����
	COLORREF			m_XAxisNameColor;	//X��������ɫ

	FLOAT				m_fYPixelsPerUnit;	//��С��λ���ٸ����ص�
	FLOAT				m_fYUnitValue;		//��С��λֵ
	FLOAT				m_fYCenterValue;	//Y�����ĵ��Ӧ��ֵ 
	FLOAT				m_fYCurMaxValue;
	FLOAT				m_fYCurMinValue;
	CHAR*				m_pYAxisName;
	CODL_Font*			m_pYAxisNameFont;
	COLORREF			m_YAxisNameColor;

	FLOAT				m_fXAxisMinGraduation;	//X����С�̶�����
	FLOAT				m_fYAxisMinGraduation;	//Y����С�̶�����

	BOOL				m_bMinusXAxis;			//�Ƿ���X��
	BOOL				m_bMinusYAxis;			//�Ƿ���Y��
protected:
	COLORREF			m_YAxisAssistTextColor;
	BOOL				m_bShowYAxisAssistText;
	FLOAT				m_fYAxisAssistTextScale;
protected:
	BOOL				m_bShowAideYAxis;					//�Ƿ���ʾ��Y��
	BOOL				m_bAideYAxisBindPos;				//��Y���Ƿ��λ��
	FLOAT				m_fAideYAxisBindPos;				//��Y�����X���ϵ�λ��ֵ
	CODL_Pen*			m_pAideYAxisPen;					//��Y��Ļ���
	FLOAT				m_fAideYUnitValue;					//��Y����С��λֵ
	FLOAT				m_fAideYCenterValue;				//��Y�����ĵ��Ӧ��ֵ 
	FLOAT				m_fAideYCurMaxValue;				//��Y�ᵱǰ���ֵ
	FLOAT				m_fAideYCurMinValue;				//��Y�ᵱǰ��Сֵ
	CHAR*				m_pAideYAxisName;					//��Y������
	CODL_Font*			m_pAideYAxisNameFont;				//��Y����������
	COLORREF			m_AideYAxisNameColor;				//��Y��������ɫ
	FLOAT				m_fAideYAxisMinGraduation;			//��Y����С�̶�����
	CODL_Font*			m_pAideYGraduationIndicateFont;		//��Y��̶���������
	COLORREF			m_YAideGraduationIndicateColor;		//��Y��̶�������ɫ
	CODL_Pen*			m_pAideYGraduationIndicatePen;		//��Y��̶Ȼ���

protected:

	CODL_Font*			m_pXGraduationIndicateFont;//X��̶���������
	CODL_Pen*			m_pXGraduationIndicatePen;
	COLORREF			m_XGraduationIndicateColor;	//X��̶�������ɫ
	DWORD				m_dwXGraduationIndicatePrecision;//X��̶�ֵ����

	CODL_Font*			m_pYGraduationIndicateFont;//Y��̶���������
	CODL_Pen*			m_pYGraduationIndicatePen;
	COLORREF			m_YGraduationIndicateColor;	//Y��̶�������ɫ
	DWORD				m_dwYGraduationIndicatePrecision;//Y��̶�ֵ����

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

	COORDRANGESTATUS	m_BindState;	//����󶨵�״̬
	BOOL				m_bBindStatus;	//�Ƿ��״̬,��״̬ʱ������С�ı䲻Ӱ����������ʾ��Χ

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
	
	//���ÿ̶ȵĳ�
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


	//���Զ��ϲ��й�
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


	//�õ���ǰ״̬
	virtual VOID		GetStatus(COORDINATESTATUS& OUT status);
	//����״̬
	virtual VOID		SetStatus(COORDINATESTATUS* IN status);
	
	//��������С�ı�ʱ���Ƿ�̶���������ʾ��Χ��
	virtual VOID		EnableBindStatus(BOOL IN bEnable){m_bBindStatus=bEnable;}

	//������������ʾ��Χ
	/*�ú��������ڵ�ǰ�����Ĵ�С�ͱ������Ƿ���ʾ*/
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
	virtual VOID		OnPreCanvasSizeChange();//������С�ı�ǰ
	virtual VOID		OnEndCanvasSizeChange();//������С�ı��

	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);

};
