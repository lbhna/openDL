#include "StdAfx.h"
#include "./ODL_DirtyRect.h"


CODL_DirtyRect::CODL_DirtyRect()
{
	Reset();
}
BOOL				CODL_DirtyRect::IsEmpty()
{
	return (m_Rect.right-m_Rect.left)==0 && (m_Rect.bottom-m_Rect.top)==0;
}
VOID				CODL_DirtyRect::SetRect(RECT& IN rect)
{
	m_Rect	=rect;
}

VOID				CODL_DirtyRect::SetRect(LONG IN left,LONG IN top,LONG IN right,LONG IN bottom)
{
	m_Rect.left		=left;
	m_Rect.right	=right;

	m_Rect.top		=top;
	m_Rect.bottom	=bottom;
}

VOID				CODL_DirtyRect::Reset()
{
	m_Rect.left		=0;
	m_Rect.right	=0;
	m_Rect.top		=0;
	m_Rect.bottom	=0;
}
VOID				CODL_DirtyRect::Add(RECT& IN rect)
{
	RECT	result;
	::UnionRect(&result,&m_Rect,&rect);
	m_Rect	=result;
}

VOID				CODL_DirtyRect::Add(CODL_DirtyRect& IN rect)
{
	Add(*rect.GetRect());
}
VOID				CODL_DirtyRect::GetIntersect(CODL_DirtyRect& IN rect,RECT& OUT result)
{
	return GetIntersect(*rect.GetRect(),result);
}


VOID				CODL_DirtyRect::GetIntersect(RECT& IN rect,RECT& OUT result)
{
	::IntersectRect(&result,&m_Rect,&rect);
}
RECT*				CODL_DirtyRect::GetRect()
{
	return &m_Rect;
}
LONG				CODL_DirtyRect::Width()
{
	return m_Rect.right-m_Rect.left;
}
LONG				CODL_DirtyRect::Height()
{
	return m_Rect.bottom-m_Rect.top;
}
LONG				CODL_DirtyRect::left()
{
	return m_Rect.left;
}
LONG				CODL_DirtyRect::right()
{
	return m_Rect.right;
}
LONG				CODL_DirtyRect::top()
{
	return m_Rect.top;
}
LONG				CODL_DirtyRect::bottom()
{
	return m_Rect.bottom;
}
