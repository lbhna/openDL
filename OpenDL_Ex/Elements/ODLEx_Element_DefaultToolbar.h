#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_DefaultToolbar.h
	created:	2012/03/26
	author:		LB
	purpose:	默认的工具条
\*********************************************************************/

#include "./ODLEx_Element_Toolbar.h"


class ODLEX_EXPORT CODLEx_Element_DefaultToolbar :
	public CODLEx_Element_Toolbar
{
public:
	CODLEx_Element_DefaultToolbar(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_DefaultToolbar(void);
public:
	INT				Init(DWORD IN dwBtnWidth,DWORD IN dwBtnHeight);
protected:
	virtual VOID	OnButtonClicked(CODLEx_Element_Button* IN pButton);
	virtual BOOL	OnDraw(HDC IN hDC,RECT* IN pPaintRect);

};
