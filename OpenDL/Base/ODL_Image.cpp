#include "stdafx.h"
#include "./ODL_Image.h"
#include "../Tools/ODL_Tools.h"


CODL_Image::CODL_Image()
{
	m_pImage		=NULL;
	m_ImageSize.cx	=0;
	m_ImageSize.cy	=0;
}
CODL_Image::~CODL_Image()
{
	ODL_SafeDelete(m_pImage);
}
BOOL		CODL_Image::Load(LPCSTR IN pImageFileName)
{
	if(pImageFileName == NULL)
		return FALSE;

	ODL_SafeDelete(m_pImage);
	m_ImageSize.cx	=0;
	m_ImageSize.cy	=0;

	LPWSTR	name	=CODL_Tools::WideChar(pImageFileName);
	m_pImage	=new Image(name);
	ODL_SafeDeleteArray(name);
	if(m_pImage == NULL)
		return FALSE;
	if(m_pImage->GetLastStatus()!=Ok)
		return FALSE;
	m_ImageSize.cx	=m_pImage->GetWidth();
	m_ImageSize.cy	=m_pImage->GetHeight();
	return TRUE;
}
BOOL		CODL_Image::Load(LPVOID IN pImageData,DWORD IN dwDataSize)
{
	if(pImageData == NULL)
		return FALSE;
	ODL_SafeDelete(m_pImage);
	m_ImageSize.cx	=0;
	m_ImageSize.cy	=0;
	LPSTREAM	pStream;
	CreateStreamOnHGlobal(NULL,TRUE,&pStream);	
	if(pStream==NULL)
		return FALSE;
	LARGE_INTEGER offset;
	offset.HighPart		=0;
	offset.LowPart		=0;
	pStream->Seek(offset,STREAM_SEEK_SET,NULL);
	pStream->Write(pImageData,dwDataSize,NULL);
	m_pImage	=new Image(pStream);
	pStream->Release();
	if(m_pImage->GetLastStatus()!=Ok)
		return FALSE;
	m_ImageSize.cx	=m_pImage->GetWidth();
	m_ImageSize.cy	=m_pImage->GetHeight();
	return TRUE;
}
LONG	CODL_Image::GetWidth()
{
	return m_ImageSize.cx;
}
LONG	CODL_Image::GetHeight()
{
	return m_ImageSize.cy;
}





