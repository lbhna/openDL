// OpenDL_Demo.h : OpenDL_Demo Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// COpenDL_DemoApp:
// �йش����ʵ�֣������ OpenDL_Demo.cpp
//

class COpenDL_DemoApp : public CWinApp
{
public:
	COpenDL_DemoApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern COpenDL_DemoApp theApp;
