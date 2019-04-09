#include "stdafx.h"
#include "ResourceLoader.h"


HINSTANCE		CResourceLoader::m_hSelfResourceHandle	=NULL;

CResourceLoader::CResourceLoader()
{
	m_hOldResourceHandel =NULL;
	HINSTANCE	hRes	=afxCurrentResourceHandle;
	if(hRes != CResourceLoader::m_hSelfResourceHandle)
	{
		m_hOldResourceHandel =hRes;
		AfxSetResourceHandle(CResourceLoader::m_hSelfResourceHandle);
	}
}

CResourceLoader::~CResourceLoader()
{
	if(m_hOldResourceHandel != NULL)
	{
		AfxSetResourceHandle(m_hOldResourceHandel);
	}
}
