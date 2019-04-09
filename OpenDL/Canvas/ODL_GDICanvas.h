#pragma once
#include "ODL_Canvasbase.h"

class ODL_EXPORT CODL_GDICanvas :
	public CODL_CanvasBase
{
protected:
	HDC						m_hDrawDC;
	HBITMAP					m_hBitmap;

public:
	CODL_GDICanvas(CODL_ViewBase* IN pView);
	virtual ~CODL_GDICanvas(void);
public:
	virtual INT				SetSize(PSIZE IN pSize);
	virtual INT				SetSize(DWORD IN cx,DWORD IN cy);
	virtual INT				Draw();
	virtual INT				Present();
	virtual BOOL			ResetCanvas();
	virtual HDC				GetDC(){return m_hDrawDC;}
	virtual VOID			ReleaseDC(HDC IN hDC){}
	virtual BOOL			SaveToBmpFile(LPCSTR IN pFileName);
	virtual BOOL			SaveToClipboard();

};

