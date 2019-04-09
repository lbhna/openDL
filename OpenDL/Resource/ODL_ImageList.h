#pragma once
#include "..\Base\ODL_ObjBase.h"
/*====================================================================\
		#��������:	2015/05/25
		#�ļ���  :	ODL_ImageList
		#����    :	LBHNA   
		#˵��    :	Imagelist��Դ��
\====================================================================*/

class ODL_EXPORT CODL_ImageList:
	public CODL_ObjBase
{
protected:
	CImageList*					m_pImageList;
public:
	CODL_ImageList();
	CODL_ImageList(CImageList* IN pImageList);
	virtual ~CODL_ImageList();

public:
	CImageList*		GetImageList(){return m_pImageList;}
public:
	virtual BOOL	Create(int cx, int cy, UINT nFlags, int nInitial, int nGrow);
	virtual BOOL	Create(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	virtual BOOL	Create(LPCSTR lpszBitmapID, int cx, int nGrow, COLORREF crMask);
	virtual VOID	GetImageSize(LONG IN lImageIndex,LONG& OUT cx,LONG& OUT cy);
	virtual BOOL	Draw(HDC IN hDC, int nImage, POINT pt, UINT nStyle);
	virtual BOOL	DrawEx(HDC IN hDC, int nImage, POINT pt, SIZE sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle);

};