// OpenDL_Demo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "OpenDL_Demo.h"
#include "MainFrm.h"

#include "OpenDL_DemoDoc.h"
#include "OpenDL_DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenDL_DemoApp

BEGIN_MESSAGE_MAP(COpenDL_DemoApp, CWinApp)
END_MESSAGE_MAP()


// COpenDL_DemoApp ����

COpenDL_DemoApp::COpenDL_DemoApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� COpenDL_DemoApp ����

COpenDL_DemoApp theApp;

// COpenDL_DemoApp ��ʼ��

BOOL COpenDL_DemoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();


	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COpenDL_DemoDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(COpenDL_DemoView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->SetWindowPos(NULL,30,30,1920*0.8+15,1050*0.8+50,SWP_SHOWWINDOW);
	//m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// �������ں�׺ʱ�ŵ��� DragAcceptFiles��
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	return TRUE;
}
