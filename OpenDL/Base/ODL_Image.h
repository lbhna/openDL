#pragma once
#include ".\ODL_ObjBase.h"
/*====================================================================\
		#创建日期:	2015/05/29
		#文件名  :	ODL_Image
		#作者    :	LBHNA   
		#说明    :	图像加载类
\====================================================================*/

#include "gdiplus.h"
using namespace Gdiplus;


class ODL_EXPORT CODL_Image:
	public CODL_ObjBase
{
protected:
	Image*				m_pImage;
	SIZE				m_ImageSize;
	
public:
	CODL_Image();
	virtual ~CODL_Image();
public:
	BOOL				Load(LPCSTR IN pImageFileName);
	BOOL				Load(LPVOID IN pImageData,DWORD IN dwDataSize);
	LONG				GetWidth();
	LONG				GetHeight();
	Image*				GetImageObject(){return m_pImage;}
};