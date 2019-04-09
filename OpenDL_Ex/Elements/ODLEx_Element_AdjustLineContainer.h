#pragma once
/********************************************************************
	created:	2015/01/08
	filename: 	e:\Open Diagram Library Project\OpenDL_Ex\OLD_AdjustLine_Container.h
	author:		lxh
	purpose:	����������ӽ����߱���߱�ͬ����X����ֵ����
*********************************************************************/

#include "ODLEx_Element_AdjustLine.h"

class ODLEX_EXPORT CODLEx_Element_AdjustLineContainer :
	public CODL_ElementBase
{
protected:
	CODL_ObjListBase			m_theLines;


public:
	CODLEx_Element_AdjustLineContainer(CODL_CanvasBase* IN pCanvas);
	~CODLEx_Element_AdjustLineContainer(void);

	VOID		AddDataLine(CODLEx_Element_AdjustLine* pCaptain);

	CODLEx_Element_AdjustLine*		GetLine(int index);

	int			GetLineIndex(CODLEx_Element_AdjustLine*);

	virtual BOOL	OnDraw(HDC IN hDC,RECT* IN pPaintRect);

	virtual BOOL	OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
};








