#pragma once
/*====================================================================\
		#创建日期:	2015/05/14
		#文件名  :	ODL_MemDC
		#作者    :	LBHNA   
		#说明    :	内存DC
\====================================================================*/


#include "./ODL_ObjBase.h"

class ODL_EXPORT CODL_MemDC:
	public CODL_ObjBase
{
protected:
	HDC								m_hDstDC;
	HBITMAP							m_hBitmap;
	HDC								m_hBitmapDC;
	SIZE							m_BitmapSize;
public:
	CODL_MemDC();
	virtual ~CODL_MemDC();
public:
	BOOL					IsValid();
	SIZE*					GetSize();
	BOOL					Update(HDC IN hDC,SIZE* IN pSize);
	operator				HDC(){return m_hBitmapDC;}
public:
	BOOL					BitPresent(LONG IN DstX,LONG IN DstY,LONG IN DstCX,LONG IN DstCY,LONG IN SrcX,LONG IN SrcY,UINT rop=SRCCOPY);
	BOOL					StretchPresent(LONG IN DstX,LONG IN DstY,LONG IN DstCX,LONG IN DstCY,LONG IN SrcX,LONG IN SrcY,LONG IN SrcCX,LONG IN SrcCY,UINT rop=SRCCOPY);
};



