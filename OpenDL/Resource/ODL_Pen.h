#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Resource\ODL_Pen.h
	created:	2012/03/09
	author:		LB
	purpose:	统一管理的画笔类
\*********************************************************************/

#include "../Base/ODL_ObjBase.h"


class ODL_EXPORT CODL_Pen :
	public CODL_ObjBase
{
protected:
	HPEN			m_hPen;
	HPEN			m_hOldPen;
	LOGPEN			m_Pen;
	HDC				m_hInstallDC;
public:
	CODL_Pen(LOGPEN* IN pLogPen);
	CODL_Pen(UINT IN nPenStyle,UINT IN nWidth,COLORREF IN PenColor);
	virtual ~CODL_Pen(void);
public:
	HPEN			GetPen(){return m_hPen;}
	LOGPEN*			GetLogPen(){return &m_Pen;}
	VOID			Update(LOGPEN* IN pLogPen);
public:
	HPEN			Install(HDC IN hDC)
	{
		m_hOldPen	=(HPEN)SelectObject(hDC,m_hPen);
		m_hInstallDC=hDC;
		return m_hOldPen;
	}
	HPEN			Uninstall(HDC IN hDC)
	{
		m_hInstallDC	=NULL;
		return (HPEN)SelectObject(hDC,m_hOldPen);
	}
	BOOL			operator==(LOGPEN& lp)
	{
		return (memcmp(&lp,&m_Pen,sizeof(m_Pen)) == 0);
	}
	BOOL			MoveTo(LONG IN x,LONG IN y);
	BOOL			LineTo(LONG IN x,LONG IN y);
	BOOL			LineTo(HDC IN hDC,LONG IN x,LONG IN y);
	BOOL			DrawRect(RECT* IN pRect);
	BOOL			DrawSquare(POINT* IN center,LONG IN cx,LONG IN cy);
};
