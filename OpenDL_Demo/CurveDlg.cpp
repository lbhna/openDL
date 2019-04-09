// CurveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenDL_Demo.h"
#include "CurveDlg.h"
#include ".\curvedlg.h"


// CCurveDlg dialog

IMPLEMENT_DYNAMIC(CCurveDlg, CDialog)
CCurveDlg::CCurveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCurveDlg::IDD, pParent)
{
	m_pView		=NULL;
	m_pCurve	=NULL;
}

CCurveDlg::~CCurveDlg()
{
	ODL_SafeRelease(m_pCurve);
	ODL_SafeRelease(m_pView);
}

void CCurveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCurveDlg, CDialog)
	ON_COMMAND(IDM_SAVECANVAS_TO_FILE, OnSavecanvasToFile)
	ON_WM_PAINT()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CCurveDlg message handlers

BOOL CCurveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_pView == NULL)
	{
		m_pView		=new CODL_View();
		CRect rect;
		GetClientRect(&rect);
		rect.DeflateRect(20,20,20,20);

        HWND hwnd =GetDlgItem(IDC_BUTTON1)->m_hWnd;
		INT ret =m_pView->Create(hwnd,RGB(20,50,20));
		if( ret != 0)
			return FALSE;
		//载入应用层菜单资源
		m_theRButtonMenu.LoadMenu(IDR_RBUTTON_MENU);



		CODLEx_Element_ZoomFrame* pFrame;
		CODLEx_Element_Coordinate* pCoord;
		CODL_CanvasBase*		pCanvas =m_pView->AddNewCanvas("test");

		//为画布创建一个标题对象
		CODLEx_Element_CanvasTitle*		pTitle =new CODLEx_Element_CanvasTitle(pCanvas);
		pCanvas->AddObj(pTitle);
		pTitle->Release();

		//为新画布设置右键菜单
		pCanvas->SetRButtonMenu(m_theRButtonMenu.GetSubMenu(1)->GetSafeHmenu());



		pFrame =new CODLEx_Element_ZoomFrame(pCanvas);
		pCanvas->AddObj(pFrame);
		pCanvas->SetZoomFrame(pFrame);
		pFrame->Release();

		CODLEx_Element_DefaultToolbar*	pDefaultToolBar =new CODLEx_Element_DefaultToolbar(pCanvas);
		pDefaultToolBar->Init(32,32);
		pCanvas->AddObj(pDefaultToolBar);
		pDefaultToolBar->SetPos(0,0);
		pDefaultToolBar->Release();

		pCoord =new CODLEx_Element_Coordinate(pCanvas);
		pCanvas->AddObj(pCoord);
		pCanvas->SetCoordinate(pCoord);
		pCoord->SetCenterOffset(50,50);
		pCoord->SetXPerUnitPixels(30.0f);
		pCoord->SetYPerUnitPixels(20.0f);
		pCoord->Release();

		//添加一个标牌
		CODLEx_Element_Label*	pLabel =new CODLEx_Element_Label(pCanvas);
		pLabel->Init(5,3);
		pLabel->SetTitle("测试标牌 title");
		pLabel->ShowTitle(TRUE);
		pLabel->ShowBorder(TRUE);
		pLabel->SetBorderStyle(PS_SOLID,1,RGB(0,255,0));
		pLabel->SetMargin(10);

		srand(time(NULL));
		CString txt;
		for(int x=0;x<5;x++)
			for(int y=0;y<3;y++)
			{
				txt.Format(" %d行%d列 ",x,y);
				pLabel->SetText(x,y,txt);
				pLabel->SetTextColor(x,y,RGB(rand()%255,rand()%255,rand()%255));
				pLabel->SetTextBkColor(x,y,RGB(rand()%255,rand()%255,rand()%255));
			}
			pLabel->SetAnchorPos(100,100);
			pLabel->SetPos(250,250);
			pLabel->SetZIndex(100);
			pCanvas->AddObj(pLabel);
			pLabel->Release();



		CODLEx_Element_CrossLine* pCrossLine =new CODLEx_Element_CrossLine(pCanvas);
		pCanvas->AddObj(pCrossLine);
		pCanvas->SetCrossLine(pCrossLine);
		pCrossLine->SetLineParameter(PS_SOLID,1,RGB(0,255,0));
		pCrossLine->Invalidate();
		pCrossLine->Release();

		m_pCurve =new CODLEx_Element_CurveBase(pCanvas,"line");
		pCanvas->AddObj(m_pCurve);
		
		//设置右键菜单
		m_pCurve->SetRButtonMenu((HMENU)m_theRButtonMenu.GetSubMenu(0)->GetSafeHmenu());

		m_pCurve->Init(PS_DOT,1,RGB(255,0,0));
		for(DWORD i=0;i<100;i++)
		{
			if(i==50)
				m_pCurve->AddData(i,2+rand()%9,1);
			else
				m_pCurve->AddData(i,2+rand()%9);
		}
		m_pCurve->Invalidate();



		CODLEx_Element_CheckBox* pBox =new CODLEx_Element_CheckBox(pCanvas);
		pCanvas->AddObj(pBox);
		pBox->SetText("test checkbox");
		pBox->SetPos(50,50);
		pBox->Release();

		CODLEx_Element_TextArea* pText =new CODLEx_Element_TextArea(pCanvas);
		pText->SetText("text");
		pText->SetPos(100,100);
		pText->SetSize(60,20);
		pText->EnableAdjustSize(TRUE);
		pText->EnableDrag(TRUE);
		pText->EnableFixedSize(TRUE);
		pText->EnableShowBkColor(TRUE);
		pText->EnableShowBorder(TRUE);
		pCanvas->AddObj(pText);
		pText->Release();

		pCanvas->Release();
	}




	return TRUE;  
}



//#######对话框程序和文档视图程序唯一的调用区别：###########
BOOL CCurveDlg::PreTranslateMessage(MSG* pMsg)
{
	//注意这一行的不同
	//目的在于将对话框的消息传递向普通窗口一样处理
	return CWnd::PreTranslateMessage(pMsg);
}

void CCurveDlg::OnSavecanvasToFile()
{
	if(m_pView == NULL)
		return;
	CFileDialog dlg(FALSE,"bmp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"bmp Files (*.bmp)|*.bmp||");
	if(dlg.DoModal()!=IDOK)
		return;

	if(m_pView->SaveToBmpFile(dlg.GetPathName()))
	{
		ShellExecute(NULL,"open",dlg.GetPathName(),NULL,NULL,SW_SHOW);
	}	
}


void CCurveDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}


void CCurveDlg::OnTimer(UINT_PTR nIDEvent)
{

    CDialog::OnTimer(nIDEvent);
}
