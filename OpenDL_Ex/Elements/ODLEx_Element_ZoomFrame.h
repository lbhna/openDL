#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_ZoomFrame.h
	created:	2012/03/14
	author:		LB
	purpose:	·Å´ó¿ò
\*********************************************************************/


class ODLEX_EXPORT CODLEx_Element_ZoomFrame :
	public CODL_ElementBase
{
protected:
	CODL_Pen*			m_pFramePen;

	BOOL				m_bZoomInit;
	POINT				m_ptStart;
	POINT				m_ptEnd;
public:
	CODLEx_Element_ZoomFrame(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ZoomFrame(void);
public:
	VOID				SetParameter(UINT IN nPenStyle,UINT IN nPenWidth,COLORREF IN clr);
public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
protected:
	VOID				OnZoom();
};
