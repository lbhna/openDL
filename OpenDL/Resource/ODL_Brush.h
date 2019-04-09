#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Resource\ODL_Brush.h
	created:	2012/03/09
	author:		LB
	purpose:	统一管理的画刷类
\*********************************************************************/


#include "../Base/ODL_ObjBase.h"

class ODL_EXPORT CODL_Brush :
	public CODL_ObjBase
{
protected:
	HBRUSH			m_hBrush;
	HBRUSH			m_hOldBrush;
	LOGBRUSH		m_Brush;
	HDC				m_hInstallDC;
public:
	CODL_Brush(LOGBRUSH* IN pLogBrush);
	CODL_Brush(UINT IN lbStyle,COLORREF IN lbColor,DWORD IN lbHatch);

	virtual ~CODL_Brush(void);
public:
	LOGBRUSH*		GetLogBrush(){return &m_Brush;}
	HBRUSH			GetBrush(){return m_hBrush;}
	VOID			Update(LOGBRUSH* IN pLogBrush);
public:
	HBRUSH			Install(HDC IN hDC)
	{
		m_hInstallDC	=hDC;
		m_hOldBrush		=(HBRUSH)SelectObject(hDC,m_hBrush);
		return m_hOldBrush;
	}
	HBRUSH			Uninstall(HDC IN hDC)
	{
		m_hInstallDC	=NULL;
		return (HBRUSH)SelectObject(hDC,m_hOldBrush);
	}

	BOOL			operator==(LOGBRUSH& v)
	{
		return (memcmp(&m_Brush,&v,sizeof(m_Brush))==0);
	}

	BOOL			FillRect(RECT* IN pRect);
	BOOL			FillRgn(HRGN IN hRgn);

};
