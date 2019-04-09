#pragma once

/*====================================================================\
		#创建日期:	2015/06/02
		#文件名  :	ODLEx_Element_ShapeRegion
		#作者    :	LBHNA   
		#说明    :	矢量区域类
\====================================================================*/

#include "./ODLEx_Element_ShapeBase.h"

class ODLEX_EXPORT CODLEx_Element_ShapeRegion:
	public CODLEx_Element_ShapeBase
{
protected:
	CODL_Vector2f*				m_pPoints;
	DWORD						m_dwPointCount;

public:
	CODLEx_Element_ShapeRegion(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ShapeRegion();
	

public:
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};