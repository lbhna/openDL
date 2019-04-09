#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Resource\ODL_ResourceManager.h
	created:	2012/02/24
	author:		LB
	purpose:	资源管理器类
\*********************************************************************/

#include "../Base/ODL_ObjListBase.h"
#include "./ODL_Pen.h"
#include "./ODL_Font.h"
#include "./ODL_Brush.h"

class ODL_EXPORT CODL_ResourceManager:
	public CODL_ObjBase
{
protected:
	CODL_ObjListBase			m_theFontList;
	CODL_ObjListBase			m_thePenList;
	CODL_ObjListBase			m_theBrushList;

public:
	CODL_ResourceManager(void);
	virtual ~CODL_ResourceManager(void);
public:
	
	CODL_Pen*			CreatePen(UINT IN nPenStyle,UINT IN nPenWidth,COLORREF IN PenColor);
	CODL_Pen*			CreatePen(LOGPEN* IN pLP);
	VOID				ClearPen();
	
	CODL_Brush*			CreateBrush(LOGBRUSH* IN pLB);
	CODL_Brush*			CreateBrush(UINT IN lbStyle,COLORREF IN lbColor,DWORD IN lbHatch);
	VOID				ClearBrush();

	CODL_Font*			CreateFont(LOGFONT* IN pLF);
	CODL_Font*			CreateFont(CHAR* IN pFontName,DWORD IN dwHeight,DWORD IN dwWeight=500,DWORD IN dwWidth=0);
	VOID				ClearFont();


};
