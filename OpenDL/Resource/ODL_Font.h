#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Resource\ODL_Font.h
	created:	2012/03/09
	author:		LB
	purpose:	统一管理的字体对象
\*********************************************************************/

#include "..\Base\ODL_ObjBase.h"

class ODL_EXPORT CODL_Font :
	public CODL_ObjBase
{
protected:
	HFONT			m_hFont;
	HFONT			m_hOldFont;
	LOGFONT			m_Font;
	TEXTMETRIC		m_TextMetrics;
	HDC				m_hInstallDC;
public:
	CODL_Font(LOGFONT* IN pLF);
	CODL_Font(CHAR* IN pFontName,DWORD IN dwHeight,DWORD IN dwWeight=500,DWORD IN dwWidth=0);
	virtual ~CODL_Font(void);
public:
	VOID			Update(LOGFONT* IN pLF);
	HFONT			Install(HDC IN hDC);
	HFONT			Uninstall(HDC IN hDC);	
	HFONT			GetFont(){return m_hFont;}
	LOGFONT*		GetLogFont(){return &m_Font;}
	LPTEXTMETRIC	GetTextMetrics();
public:
	BOOL			operator==(LOGFONT& lf);
public:
	BOOL			SetTextAlign(UINT IN align);
	BOOL			SetTextColor(COLORREF IN clr);
	BOOL			SetBkColor(COLORREF IN clr);
	BOOL			GetTextRect(LPCSTR IN pText,RECT* OUT pRect);
	BOOL			TextOut(LONG IN x,LONG IN y,LPCSTR IN pText);
	BOOL			DrawText(RECT* IN pRect,LPCSTR IN pText,UINT IN align);
};
