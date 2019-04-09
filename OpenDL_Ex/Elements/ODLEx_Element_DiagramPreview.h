#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_DiagramPreview.h
	created:	2012/04/20
	author:		LB
	purpose:	图例
\*********************************************************************/

class ODLEX_EXPORT CODLEx_Element_DiagramPreview :
	public CODL_OverlayElementBase
{
protected:
	POINT				m_Pos;
	SIZE				m_Size;
	LONG				m_lLineBlank;
	LONG				m_lMargin;
	BOOL				m_bDraging;
	POINT				m_DragOffset;
	CODL_Brush*			m_pBrush;


	LONG				m_lTitleHeight;

	BOOL				m_bNeedResetCase;
	CODL_ObjListBase	m_CaseList;
	SIZE				m_CaseSize;
	BOOL				m_bShowLastDataText;

public:
	CODLEx_Element_DiagramPreview(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_DiagramPreview();
public:
	VOID				SetBkColor(COLORREF IN clr);
	VOID				SetPos(LONG IN x,LONG IN y);
	POINT*				GetPos(){return &m_Pos;}
	VOID				EnableShowLastDataText(BOOL IN bEnable);
	BOOL				IsEnableShowLastDataText(){return m_bShowLastDataText;}
public:
	//设置图例颜色（正常色，选中色)
	VOID				SetCaseTextColor(COLORREF IN normalColor,COLORREF IN selectedColor);
	//设置图例字体
	VOID				SetCaseFont(LPCSTR IN pFontName,UINT IN uFontSize);
	//设置图例线长
	VOID				SetCaseLineLength(LONG IN lLen);
	
public:
	virtual VOID		GetElementBound(HDC IN hDC,RECT* IN pPaintRect,RECT& OUT boundRect);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual VOID		Invalidate(BOOL IN bFlushView=FALSE);
	virtual BOOL		PtInElement(POINT IN pt);
protected:
	VOID				Reset(HDC IN hDC);

};
