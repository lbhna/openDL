#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_SafeArea.h
	created:	2012/04/19
	author:		LB
	purpose:	数据安全区域类
\*********************************************************************/

class ODLEX_EXPORT CODLEx_Element_SafeArea :
	public CODL_ElementBase
{
protected:
	FLOAT			m_fXMinValue;
	BOOL			m_bShowXDownLimitLine;

	FLOAT			m_fXMaxValue;
	BOOL			m_bShowXUpLimitLine;

	FLOAT			m_fYMinVlue;
	BOOL			m_bShowYDownLimitLine;

	FLOAT			m_fYMaxValue;
	BOOL			m_bShowYUpLimitLine;

	CODL_Pen*		m_pLinePen;
	CODL_Font*		m_pFont;
	COLORREF		m_TextColor;
	COLORREF		m_TextBkColor;
	
	BOOL			m_bShowText;
public:
	CODLEx_Element_SafeArea(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_SafeArea(void);
public:
	VOID			SetXMinValue(FLOAT IN fValue);
	VOID			ShowXDownlimitLine(BOOL IN bShow);

	VOID			SetXMaxValue(FLOAT IN fValue);
	VOID			ShowXUplimitLine(BOOL IN bShow);

	VOID			SetYMinValue(FLOAT IN fValue);
	VOID			ShowYDownlimitLine(BOOL IN bShow);

	VOID			SetYMaxValue(FLOAT IN fValue);
	VOID			ShowYUplimitLine(BOOL IN bShow);

	VOID			SetLineStyle(UINT IN uLineWidth,COLORREF IN clr,UINT IN uLineStyle=PS_SOLID);
	VOID			SetFont(LPCSTR IN pFontName,DWORD IN dwFontSize,COLORREF IN clr,COLORREF IN bkClr=RGB(0,0,0));

	VOID			SetLinePen(LOGPEN* IN pPen);
	VOID			SetTextFont(LOGFONT* IN pLf);
	VOID			SetColor(COLORREF IN clr,COLORREF IN bkClr=RGB(0,0,0));


	VOID			ShowText(BOOL IN bShow){m_bShowText=bShow;Invalidate();}
	

public:
	virtual BOOL	OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};
