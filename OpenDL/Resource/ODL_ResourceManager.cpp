#include "StdAfx.h"
#include ".\odl_resourcemanager.h"

CODL_ResourceManager::CODL_ResourceManager(void)
{
}

CODL_ResourceManager::~CODL_ResourceManager(void)
{
	ClearFont();
	ClearBrush();
	ClearPen();
}
CODL_Pen*			CODL_ResourceManager::CreatePen(UINT IN nPenStyle,UINT IN nPenWidth,COLORREF IN PenColor)
{
	LOGPEN	lp;
	lp.lopnColor	=PenColor;
	lp.lopnStyle	=nPenStyle;
	lp.lopnWidth.x	=nPenWidth;
	lp.lopnWidth.y	=0;

	return CreatePen(&lp);
}
CODL_Pen*			CODL_ResourceManager::CreatePen(LOGPEN* IN pLP)
{
	CODL_Pen*	pPen ;
	for(LONG i=0;i<m_thePenList.GetCount();i++)
	{
		pPen	=(CODL_Pen*)m_thePenList.GetObj(i);
		if(*pPen == *pLP)
		{
			pPen->AddRef();
			return pPen;
		}
	}

	pPen	=new CODL_Pen(pLP);
	m_thePenList.AddObj(pPen);
	return pPen;
}
VOID				CODL_ResourceManager::ClearPen()
{
	m_thePenList.Clear();
}

CODL_Brush*			CODL_ResourceManager::CreateBrush(LOGBRUSH* IN pLB)
{
	CODL_Brush*		pBrush;
	for(LONG i=0;i<m_theBrushList.GetCount();i++)
	{
		pBrush	=(CODL_Brush*)m_theBrushList.GetObj(i);
		if(*pBrush == *pLB)
		{
			pBrush->AddRef();
			return pBrush;
		}
	}
	pBrush	=new CODL_Brush(pLB);
	
	m_theBrushList.AddObj(pBrush);

	return pBrush;
}
CODL_Brush*			CODL_ResourceManager::CreateBrush(UINT IN lbStyle,COLORREF IN lbColor,DWORD IN lbHatch)
{
	LOGBRUSH	lb;
	lb.lbColor	=lbColor;
	lb.lbHatch	=lbHatch;
	lb.lbStyle	=lbStyle;
	return CreateBrush(&lb);
}
VOID				CODL_ResourceManager::ClearBrush()
{
	m_theBrushList.Clear();
}

CODL_Font*			CODL_ResourceManager::CreateFont(LOGFONT* IN pLF)
{
	CODL_Font*		pFont;
	for(LONG i=0;i<m_theFontList.GetCount();i++)
	{
		pFont	=(CODL_Font*)m_theFontList.GetObj(i);
		if(*pFont == *pLF)
		{
			pFont->AddRef();
			return pFont;
		}
	}
	pFont	=new CODL_Font(pLF);
	m_theFontList.AddObj(pFont);

	return pFont;
}
CODL_Font*			CODL_ResourceManager::CreateFont(CHAR* IN pFontName,DWORD IN dwHeight,DWORD IN dwWeight,DWORD IN dwWidth)
{
	LOGFONT		lf;
	ZeroMemory(&lf,sizeof(lf));
	lf.lfCharSet	=DEFAULT_CHARSET;
	strcpy(lf.lfFaceName,pFontName);
	lf.lfWidth		=dwWidth;
	lf.lfHeight		=dwHeight;
	lf.lfWeight		=dwWeight;

	return CreateFont(&lf);
}
VOID				CODL_ResourceManager::ClearFont()
{
	m_theFontList.Clear();
}
