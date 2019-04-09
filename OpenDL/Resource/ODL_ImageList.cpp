#include "stdafx.h"
#include "ODL_ImageList.h"


CODL_ImageList::CODL_ImageList()
{
	m_pImageList	=new CImageList();
}

CODL_ImageList::CODL_ImageList(CImageList* IN pImageList)
{
	m_pImageList	=new CImageList();
	m_pImageList->Create(pImageList);
}
CODL_ImageList::~CODL_ImageList()
{
	ODL_SafeDelete(m_pImageList);
}
BOOL CODL_ImageList::Create(int cx, int cy, UINT nFlags, int nInitial, int nGrow)
{
	ODL_SafeDelete(m_pImageList);
	m_pImageList	=new CImageList();
	return m_pImageList->Create(cx, cy, nFlags, nInitial, nGrow);
}
BOOL CODL_ImageList::Create(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	ODL_SafeDelete(m_pImageList);
	m_pImageList	=new CImageList();
	return m_pImageList->Create(nBitmapID,  cx,  nGrow,  crMask);
}
BOOL CODL_ImageList::Create(LPCSTR lpszBitmapID, int cx, int nGrow, COLORREF crMask)
{
	ODL_SafeDelete(m_pImageList);
	m_pImageList	=new CImageList();
	return m_pImageList->Create(lpszBitmapID,  cx,  nGrow, crMask);
}
VOID CODL_ImageList::GetImageSize(LONG IN lImageIndex,LONG& OUT cx,LONG& OUT cy)
{
	cx	=0;
	cy	=0;
	IMAGEINFO info;
	ZeroMemory(&info,sizeof(info));
	m_pImageList->GetImageInfo(lImageIndex,&info);
	cx =info.rcImage.right-info.rcImage.left;
	cy =info.rcImage.bottom-info.rcImage.top;
}
BOOL	CODL_ImageList::Draw(HDC IN hDC, int nImage, POINT pt, UINT nStyle)
{
  return m_pImageList->Draw(CDC::FromHandle(hDC), nImage, pt, nStyle);
}
BOOL	CODL_ImageList::DrawEx(HDC IN hDC, int nImage, POINT pt, SIZE sz, COLORREF clrBk, COLORREF clrFg, UINT nStyle)
{ 
  return m_pImageList->DrawEx(CDC::FromHandle(hDC), nImage, pt, sz, clrBk, clrFg, nStyle);
}




