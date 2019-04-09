#pragma once
/*====================================================================\
		#创建日期:	2015/02/11
		#文件名  :	ODLEx_Element_ScrollBar
		#作者    :	LBHNA   
		#说明    :	滚动条类
\====================================================================*/


class ODLEX_EXPORT CODLEx_Element_ScrollBar:
	public CODL_ElementBase
{
protected:
	POINT				m_Pos;
	SIZE				m_Size;
	CODL_Brush*			m_pArrowBrush;

	CODL_Brush*			m_pSpinBarBrightBrush;
	CODL_Brush*			m_pSpinBarNormalBrush;
	CODL_Brush*			m_pSpinBarDarkBrush;
	
	CODL_Brush*			m_pScrollBarBrightBrush;
	CODL_Brush*			m_pScrollBarNormalBrush;
	CODL_Brush*			m_pScrollBarDarkBrush;

	CODL_Brush*			m_pBackBrush;

protected:
	RECT				m_BackRect;
	RECT				m_ScrollBarActiveRect;
	BOOL				m_bSpinIsPressed[2];
	RECT				m_SpinRect[2];
	RECT				m_ScrollBarRect;
	BOOL				m_bDragingScrollBar;
	POINT				m_ptDragOffset;
	
	BOOL				m_bHorizontal;	//是否是水平方向
	LONG				m_lPageSize;	//一页大小
	LONG				m_lPosition;	//滚动条当前位置
	LONG				m_lMaxPosition;	//最大位置
	LONG				m_lTimerCounter;

protected:
	SCROLL_CALLBACK		m_pScrollCallback;
	DWORD_PTR			m_CallbackUserData;

public:
	CODLEx_Element_ScrollBar(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ScrollBar();
public:
	VOID				SetPos(LONG IN x,LONG IN y);
	PPOINT				GetPos();
	VOID				SetSize(LONG IN cx,LONG IN cy);
	PSIZE				GetSize();

	VOID				SetPageSize(LONG IN lSize);
	LONG				GetPageSize();
	VOID				SetPosition(LONG IN lPosition);
	LONG				GetPosition();
	VOID				SetMaxPosition(LONG IN lMaxPosition);
	LONG				GetMaxPosition();

	BOOL				IsHorizontal();
	VOID				SetHorizontal(BOOL IN bHorizontal);

	VOID				SetArrowBrush(CODL_Brush* IN pBrush);
	VOID				SetSpinBarBrightBrush(CODL_Brush* IN pBrush);
	VOID				SetSpinBarNormalBrush(CODL_Brush* IN pBrush);
	VOID				SetSpinBarDarkBrush(CODL_Brush* IN pBrush);
	VOID				SetScrollBarBrightBrush(CODL_Brush* IN pBrush);
	VOID				SetScrollBarNormalBrush(CODL_Brush* IN pBrush);
	VOID				SetScrollBarDarkBrush(CODL_Brush* IN pBrush);
	VOID				SetBackBrush(CODL_Brush* IN pBrush);

	CODL_Brush*			GetArrowBrush();
	CODL_Brush*			GetSpinBarBrightBrush();
	CODL_Brush*			GetSpinBarNormalBrush();
	CODL_Brush*			GetSpinBarDarkBrush();
	CODL_Brush*			GetScrollBarBrightBrush();
	CODL_Brush*			GetScrollBarNormalBrush();
	CODL_Brush*			GetScrollBarDarkBrush();
	CODL_Brush*			GetBackBrush();

	VOID				SetScrollCallbackFunction(SCROLL_CALLBACK IN pCallback,DWORD_PTR IN dwUserData);

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);

protected:
	virtual VOID		UpdateAllRect();
	virtual VOID		OnDrawBackBar(HDC IN hDC,RECT* IN pPaintRect);
	virtual	VOID		OnDrawSpinButton(HDC IN hDC,RECT* IN pPaintRect);
	virtual VOID		OnDrawScrollBar(HDC IN hDC,RECT* IN pPaintRect);
	VOID				DrawTriangle(HDC IN hDC,RECT* IN rect,CODL_Brush* IN pBrush,BOOL IN bHorizontal,BOOL IN bInvertDirect);

protected:
	static VOID	CALLBACK SpinHoldPressTimer(HWND IN hWnd, UINT IN msg, UINT_PTR IN id, DWORD IN time);
	VOID				OnTimer();
	VOID				NotifyCallback();
};
