#include "stdafx.h"
#include "ODL_MemDC.h"

CODL_MemDC::CODL_MemDC()
{
	m_hDstDC				=NULL;
	m_hBitmap				=NULL;
	m_hBitmapDC				=NULL;
	m_BitmapSize.cx			=0;
	m_BitmapSize.cy			=0;
}
CODL_MemDC::~CODL_MemDC()
{
	ODL_SafeDeleteGDIObj(m_hBitmap);
	if(m_hBitmapDC != NULL)
		DeleteDC(m_hBitmapDC);
}

BOOL		CODL_MemDC::IsValid()
{
	return (m_hBitmapDC!=NULL);
}
SIZE*		CODL_MemDC::GetSize()
{
	return &m_BitmapSize;
}
BOOL		CODL_MemDC::Update(HDC IN hDC,SIZE* IN pSize)
{
	m_hDstDC			=hDC;
	if(m_BitmapSize.cx != pSize->cx || m_BitmapSize.cy != pSize->cy)
	{
		ODL_SafeDeleteGDIObj(m_hBitmap);
		if(m_hBitmapDC != NULL)
			DeleteDC(m_hBitmapDC);
		m_hBitmapDC			=CreateCompatibleDC(hDC);
		m_BitmapSize.cx		=pSize->cx;
		m_BitmapSize.cy		=pSize->cy;
		m_hBitmap			=CreateCompatibleBitmap(hDC,m_BitmapSize.cx,m_BitmapSize.cy);
		SelectObject(m_hBitmapDC,m_hBitmap);
		return TRUE;
	}
	return FALSE;
}
BOOL		CODL_MemDC::BitPresent(LONG IN DstX,LONG IN DstY,LONG IN DstCX,LONG IN DstCY,LONG IN SrcX,LONG IN SrcY,UINT rop)
{
	return BitBlt(m_hDstDC,DstX,DstY,DstCX,DstCY,m_hBitmapDC,SrcX,SrcY,rop);
}
BOOL		CODL_MemDC::StretchPresent(LONG IN DstX,LONG IN DstY,LONG IN DstCX,LONG IN DstCY,LONG IN SrcX,LONG IN SrcY,LONG IN SrcCX,LONG IN SrcCY,UINT rop)
{
	return StretchBlt(m_hDstDC,DstX,DstY,DstCX,DstCY,m_hBitmapDC,SrcX,SrcY,SrcCX,SrcCY,rop);
}
