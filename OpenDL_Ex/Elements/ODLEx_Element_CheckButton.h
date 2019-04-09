#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL_Ex\Elements\ODLEx_Element_CheckButton.h
	created:	2012/03/26
	author:		LB
	purpose:	´øCHECK×´Ì¬µÄ°´Å¥
\*********************************************************************/

#include "ODLEx_Element_Button.h"

class ODLEX_EXPORT CODLEx_Element_CheckButton :
	public CODLEx_Element_Button
{
protected:
	BOOL				m_bChecked;
	BOOL				m_bGroupControl;
public:
	CODLEx_Element_CheckButton(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_CheckButton(void);
public:
	VOID				SetChecked(BOOL IN bChecked);
	BOOL				IsChecked(){return m_bChecked;}
	BOOL				IsGroupControl(){return m_bGroupControl;}
	VOID				SetGroupControl(BOOL IN bEnable){m_bGroupControl=bEnable;}

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);

};
