#pragma once
/*====================================================================\
		#创建日期:	2015/05/12
		#文件名  :	ODL_DirtyRect
		#作者    :	LBHNA   
		#说明    :	脏矩形类
\====================================================================*/

#include "GlobalDefine.h"

class ODL_EXPORT CODL_DirtyRect
{
protected:
	RECT				m_Rect;
public:
	CODL_DirtyRect();
	~CODL_DirtyRect(){}
public:
	VOID				SetRect(RECT& IN rect);
	VOID				SetRect(LONG IN left,LONG IN top,LONG IN right,LONG IN bottom);

	BOOL				IsEmpty();
	VOID				Reset();
	VOID				Add(RECT& IN rect);
	VOID				Add(CODL_DirtyRect& IN rect);
	VOID				GetIntersect(RECT& IN rect,RECT& OUT result);
	VOID				GetIntersect(CODL_DirtyRect& IN rect,RECT& OUT result);
	RECT*				GetRect();
	LONG				Width();
	LONG				Height();
	LONG				left();
	LONG				right();
	LONG				top();
	LONG				bottom();
};