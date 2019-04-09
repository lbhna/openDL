#include "StdAfx.h"
#include ".\odl_font.h"


CODL_Font::CODL_Font(LOGFONT* IN pLF)
{
	m_hInstallDC	=NULL;
	m_hFont			=CreateFontIndirect(pLF);
	m_hOldFont		=NULL;
	m_Font			=*pLF;
	ZeroMemory(&m_TextMetrics,sizeof(m_TextMetrics));
}
CODL_Font::CODL_Font(CHAR* IN pFontName,DWORD IN dwHeight,DWORD IN dwWeight,DWORD IN dwWidth)
{
	m_hInstallDC			=NULL;
	ZeroMemory(&m_Font,sizeof(m_Font));
	m_Font.lfCharSet		=DEFAULT_CHARSET;
	strcpy(m_Font.lfFaceName,pFontName);
	m_Font.lfHeight			=dwHeight;
	m_Font.lfWeight			=dwWeight;
	m_Font.lfWidth			=dwWidth;

	m_hFont			=CreateFontIndirect(&m_Font);
	m_hOldFont		=NULL;
	ZeroMemory(&m_TextMetrics,sizeof(m_TextMetrics));
}

CODL_Font::~CODL_Font(void)
{
	ODL_SafeDeleteGDIObj(m_hFont);
}
VOID			CODL_Font::Update(LOGFONT* IN pLF)
{
	ODL_SafeDeleteGDIObj(m_hFont);
	m_hFont			=CreateFontIndirect(pLF);
	m_Font			=*pLF;
	ZeroMemory(&m_TextMetrics,sizeof(m_TextMetrics));
}

HFONT			CODL_Font::Install(HDC IN hDC)
{
	m_hInstallDC		=hDC;
	m_hOldFont			=(HFONT)SelectObject(hDC,m_hFont);
	::GetTextMetrics(hDC,&m_TextMetrics);
	return m_hOldFont;
}
HFONT			CODL_Font::Uninstall(HDC IN hDC)
{
	m_hInstallDC	=NULL;
	return (HFONT)SelectObject(hDC,m_hOldFont);
}
BOOL			CODL_Font::operator==(LOGFONT& lf)
{
	return (memcmp(&m_Font,&lf,sizeof(m_Font))==0);
}
LPTEXTMETRIC	CODL_Font::GetTextMetrics()
{
	return &m_TextMetrics;
}
BOOL			CODL_Font::GetTextRect(LPCSTR IN pText,RECT* OUT pRect)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	if(::GetTextMetrics(m_hInstallDC,&m_TextMetrics))
		return FALSE;
	pRect->left		=0;
	pRect->top		=0;
	LONG len		=strlen(pText);
	pRect->right	=len*m_TextMetrics.tmAveCharWidth;
	pRect->bottom	=len*m_TextMetrics.tmHeight;
	return TRUE;
}

BOOL			CODL_Font::TextOut(LONG IN x,LONG IN y,LPCSTR IN pText)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::TextOut(m_hInstallDC,x,y,pText,strlen(pText));
}
BOOL			CODL_Font::DrawText(RECT* IN pRect,LPCSTR IN pText,UINT IN align)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::DrawText(m_hInstallDC,pText,strlen(pText),pRect,align);
}
BOOL			CODL_Font::SetTextAlign(UINT IN align)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::SetTextAlign(m_hInstallDC,align);
}
BOOL			CODL_Font::SetTextColor(COLORREF IN clr)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::SetTextColor(m_hInstallDC,clr);

}
BOOL			CODL_Font::SetBkColor(COLORREF IN clr)
{
	if(m_hInstallDC == NULL)
		return FALSE;
	return ::SetBkColor(m_hInstallDC,clr);
}
