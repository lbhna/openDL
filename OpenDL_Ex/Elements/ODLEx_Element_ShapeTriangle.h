#pragma once

/*====================================================================\
		#��������:	2015/06/02
		#�ļ���  :	ODLEx_Element_ShapeTriangle
		#����    :	LBHNA   
		#˵��    :	ʸ����������
\====================================================================*/
#include "./ODLEx_Element_ShapeBase.h"


class ODLEX_EXPORT CODLEx_Element_ShapeTriangle:
	public CODLEx_Element_ShapeBase
{
public:
	CODLEx_Element_ShapeTriangle(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ShapeTriangle();

public:
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};