#pragma once

class CResourceLoader  
{
public:
	static	HINSTANCE		m_hSelfResourceHandle;
protected:
	HINSTANCE				m_hOldResourceHandel;
public:
	CResourceLoader();
	virtual ~CResourceLoader();

};

