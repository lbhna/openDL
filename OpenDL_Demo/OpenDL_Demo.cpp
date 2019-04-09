// OpenDL_Demo.cpp : 定义应用程序的类行为。
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


// COpenDL_DemoApp 构造

COpenDL_DemoApp::COpenDL_DemoApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 COpenDL_DemoApp 对象

COpenDL_DemoApp theApp;

// COpenDL_DemoApp 初始化

BOOL COpenDL_DemoApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COpenDL_DemoDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(COpenDL_DemoView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->SetWindowPos(NULL,30,30,1920*0.8+15,1050*0.8+50,SWP_SHOWWINDOW);
	//m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// 仅当存在后缀时才调用 DragAcceptFiles，
	//  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生
	return TRUE;
}
