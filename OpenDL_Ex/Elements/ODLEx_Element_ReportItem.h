#pragma once

/*====================================================================\
		#创建日期:	2015/05/14
		#文件名  :	ODLEx_Element_ReportItem
		#作者    :	LBHNA   
		#说明    :	报表中的项
\====================================================================*/


class ODLEX_EXPORT CODLEx_Element_ReportRow;
class ODLEX_EXPORT CODLEx_Element_ReportItem:
	public CODL_ElementBase
{
protected:
	CODLEx_Element_ReportRow*	m_pReportRow;

	POINT						m_Pos;
	SIZE						m_Size;
	CHAR*						m_pText;
	CODL_Brush*					m_pBkBrush;
	CODL_Brush*					m_pSelectBkBrush;
	CODL_Brush*					m_pPushedBkBrush;

	CODL_Font*					m_pTextFont;
	COLORREF					m_TextColor;
	COLORREF					m_SelectTextColor;

	RECT						m_Padding;		
	UINT						m_uTextAlign;	


	BOOL						m_bEnableClicked;
	BOOL						m_bPushed;
	BOOL						m_bShowBorder;
	COLORREF					m_LightBorderColor;
	COLORREF					m_DarkBorderColor;
	DWORD						m_dwBorderSize;
	CODL_Pen*					m_pLightBorderPen;
	CODL_Pen*					m_pDarkBorderPen;
protected:
	CODL_ImageList*				m_pImageList;
	LONG						m_lImageIndex;
	LONG						m_lSelectedImageIndex;
	UINT						m_nImageDrawStyle;
protected:
	
	BOOL						m_bGradientFill;
	TRIVERTEX					m_Vertexs[6];
protected:
	LONG						m_lAdjustOffset;
	BOOL						m_bAdjustWidth;
	BOOL						m_bAdjustHeight;
public:
	CODLEx_Element_ReportItem(CODLEx_Element_ReportRow* IN pRow,CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ReportItem();

public:
	CODLEx_Element_ReportItem*					SetText(LPCSTR IN pText);
	LPCSTR										GetText();
	CODLEx_Element_ReportItem*					SetPos(LONG IN x,LONG IN y);
	POINT*										GetPos();
	CODLEx_Element_ReportItem*					SetSize(LONG IN cx,LONG IN cy);
	SIZE*										GetSize();
	CODLEx_Element_ReportItem*					SetWidth(LONG IN cx);
	CODLEx_Element_ReportItem*					SetHeight(LONG IN cy);

	CODLEx_Element_ReportItem*					SetBkBrush(LOGBRUSH* IN pBrush);
	CODLEx_Element_ReportItem*					SetBkBrush(UINT IN lbStyle,COLORREF IN lbColor,UINT_PTR IN lbHatch);
	CODLEx_Element_ReportItem*					SetBkBrush(CODL_Brush* IN pBrush);
	
	CODLEx_Element_ReportItem*					SetSelectBkBrush(CODL_Brush* IN pBrush);
	
	CODLEx_Element_ReportItem*					SetPushedBkBrush(CODL_Brush* IN pBrush);
	CODLEx_Element_ReportItem*					SetPushedBkBrush(LOGBRUSH* IN pBrush);

	CODLEx_Element_ReportItem*					SetImage(CODL_ImageList* IN pImageList,LONG IN lImageIndex,UINT IN nDrawStyle=ILD_NORMAL,LONG IN lSelectedImageIndex=-1);

	CODLEx_Element_ReportItem*					SetFont(LPCSTR IN pFontFaceName,UINT IN uFontSize);
	CODLEx_Element_ReportItem*					SetFont(LOGFONT* IN lf);
	CODLEx_Element_ReportItem*					SetFont(CODL_Font*	IN pFont);

	CODLEx_Element_ReportItem*					SetTextColor(COLORREF IN clr);
	COLORREF									GetTextColor();
	CODLEx_Element_ReportItem*					SetSelectTextColor(COLORREF IN clr);
	COLORREF									GetSelectTextColor();

	CODLEx_Element_ReportItem*					SetTextAlign(UINT IN lAlign);
	UINT										GetTextAlign();

	CODLEx_Element_ReportItem*					SetTextPadding(LONG IN left,LONG IN top,LONG IN right,LONG IN bottom);
	RECT*										GetTextPadding();


	BOOL										IsEnableClicked();
	CODLEx_Element_ReportItem*					EnableClicked(BOOL IN bEnable);
	BOOL										IsShowBorder();
	CODLEx_Element_ReportItem*					ShowBorder(BOOL IN bShow);
	CODLEx_Element_ReportItem*					SetBorderColor(COLORREF IN lightColor,COLORREF IN darkColor);
	CODLEx_Element_ReportItem*					SetBorderSize(DWORD IN dwBorderSize);
	CODLEx_Element_ReportItem*					SetBorderPen(LOGPEN* IN pLightPen,LOGPEN* IN pDarkPen);

	CODLEx_Element_ReportRow*					GetReportRow();
public:
	virtual BOOL								OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL								OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual VOID								SetSelected(BOOL IN bSelect);

	virtual VOID								GetRect(RECT& OUT rect);
	virtual BOOL								PtInElement(POINT IN pt);
protected:
	virtual BOOL								DrawBackGround(HDC IN hDC,RECT* IN bkRect);
	virtual BOOL								DrawContents(HDC IN hDC,RECT* IN txtRect);
};