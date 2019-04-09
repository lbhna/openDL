#pragma once

/********************************************************************\
	filename: 	ODLEx_Element_Compass.h
	created:	2014/10/21
	author:		LB
	purpose:	指北针类
\*********************************************************************/

class ODLEX_EXPORT CODLEx_Element_Compass :
	public CODL_OverlayElementBase
{
protected:
	CODL_Pen*							m_pFramePen;		//边框的画笔
	CODL_Font*							m_pDialTextFont;		//文字字体
	COLORREF							m_DialTextColor;

	CODL_Pen*							m_pNeedlePen;		//指针的画笔

	CODL_Brush*							m_pFillNorthNeedleBrush;
	CODL_Brush*							m_pFillSouthNeedleBrush;

	BOOL								m_bFillDial;
	CODL_Brush*							m_pFillDialBrush;

	BOOL								m_bShowText;


protected:
	SIZE								m_Size;		
	POINT								m_Pos;				//当前位置
	FLOAT								m_fCourse;			//当前朝向
	FLOAT								m_fNeedleAngle;		//指针角度

protected:
	BOOL								m_bEnableAdjustSize;
	BOOL								m_bAdjustSizeing;
	BOOL								m_bEnableDrag;
	POINT								m_ptDragOffset;
	BOOL								m_bDraging;
public:
	CODLEx_Element_Compass(CODL_CanvasBase* IN pCanvas,DWORD IN dwDialRadius,LONG IN x,LONG IN y);
	virtual ~CODLEx_Element_Compass(void);

public:
	COLORREF							GetDialTextColor(){return m_DialTextColor;}
	VOID								SetDialTextColor(COLORREF IN clr);

	FLOAT								GetNeedleAngle(){return m_fNeedleAngle;}
	VOID								SetNeedleAngle(FLOAT IN fAngle);			//设置指针尖角度( 5.0f--75.0f )

	VOID								SetDialTextFontPara(CHAR* IN pFontName,DWORD IN dwSize);
	VOID								GetDialTextFontPara(CHAR* OUT pFontName,DWORD& OUT dwSize);
	VOID								SetDialTextFont(LOGFONT* IN pLf);


	DWORD								GetDialRadius(){return m_Size.cx/2;}
	VOID								SetDialRadius(DWORD IN dwDialRadius);		//设置罗盘半径

	VOID								GetPos(POINT& IN OUT pos){pos=m_Pos;}
	VOID								SetPos(POINT* IN pPos);						//设置罗盘位置
	VOID								SetPos(LONG IN x,LONG IN y);
	VOID								SetSize(LONG IN cx,LONG IN cy);
	VOID								SetSize(SIZE* IN pSize);
	VOID								GetSize(SIZE& IN OUT size){size =m_Size;}

	FLOAT								GetPose(){return m_fCourse;}
	VOID								SetPose(FLOAT IN fCourse);

	VOID								SetDialFramePara(COLORREF IN FrameColor,DWORD IN dwLineWidth,DWORD IN dwPenStyle);	//设置罗盘边框参数
	VOID								GetDialFramePara(COLORREF& OUT FrameColor,DWORD& OUT dwLineWidth,DWORD& OUT dwPenStyle);

	VOID								SetNeedlePara(COLORREF IN clr,DWORD IN dwLineWidth,DWORD IN dwPenStyle);				//设置指针参数
	VOID								GetNeedlePara(COLORREF& OUT clr,DWORD& OUT dwLineWidth,DWORD& OUT dwPenStyle);



	BOOL								IsEnableFillDial(){return m_bFillDial;}
	VOID								EnableFillDial(BOOL IN bEnable);
	VOID								SetFillDialPara(COLORREF IN FillColor,UINT IN uBrushStyle);
	VOID								GetFillDialPara(COLORREF& OUT FillColor,UINT& OUT uBrushStyle);

	VOID								SetFillNorthNeedlePara(COLORREF IN FillColor,UINT IN uBrushStyle);
	VOID								GetFillNorthNeedlePara(COLORREF& OUT FillColor,UINT& OUT uBrushStyle);

	VOID								SetFillSouthNeedlePara(COLORREF IN FillColor,UINT IN uBrushStyle);
	VOID								GetFillSouthNeedlePara(COLORREF& OUT FillColor,UINT& OUT uBrushStyle);

	BOOL								IsEnableShowText(){return m_bShowText;}
	VOID								EnableShowText(BOOL IN bEnableShow);
	VOID								EnableDrag(BOOL IN bEnable){m_bEnableDrag=bEnable;}
	VOID								EnableAdjustSize(BOOL IN bEnable){m_bEnableAdjustSize=bEnable;}
	BOOL								IsEnableAdjustSize(){return m_bEnableAdjustSize;}
	FLOAT								GetEllipseRadius(FLOAT IN fAngle,FLOAT IN fXRadius,FLOAT IN fYRadius);

public:
	virtual RECT*						GetRect(RECT* IN OUT pRec);
	virtual BOOL						PtInAdjustSizeButton(POINT* IN pt);
	virtual VOID						GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL						OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL						OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL						PtInElement(POINT IN pt);

};

