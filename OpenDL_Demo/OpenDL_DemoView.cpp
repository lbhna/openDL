// OpenDL_DemoView.cpp : COpenDL_DemoView ���ʵ��
//

#include "stdafx.h"
#include "OpenDL_Demo.h"

#include "OpenDL_DemoDoc.h"
#include "OpenDL_DemoView.h"
#include ".\opendl_demoview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COpenDL_DemoView
IMPLEMENT_DYNCREATE(COpenDL_DemoView, CView)
BEGIN_MESSAGE_MAP(COpenDL_DemoView, CView)
	// ��׼��ӡ����
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_SHOW_CURVE, OnShowCurve)
	ON_COMMAND(IDM_SHOW_CURVE_MODAL, OnShowCurveModal)
	ON_COMMAND(IDM_SAVECANVAS_TO_FILE, OnSavecanvasToFile)
	ON_COMMAND(IDM_SAVECANVAS_TO_CLIPBOARD, OnSavecanvasToClipboard)
	ON_COMMAND(IDM_SAVEVIEW_TO_FILE, OnSaveviewToFile)
	ON_COMMAND(IDM_SAVEVIEW_TO_CLIPBOARD, OnSaveviewToClipboard)
	ON_COMMAND(IDM_ABS_LOCATE, OnAbsLocate)
	ON_COMMAND(ID_SHOW_HIDE_PREVIEW, OnShowHidePreview)
	ON_UPDATE_COMMAND_UI(ID_SHOW_HIDE_PREVIEW, OnUpdateShowHidePreview)
	ON_COMMAND(IDM_CURVE_CLEARDATA, OnCurveCleardata)
	ON_MESSAGE(USERMSG_CANVAS,OnCanvasCallbackMessage)
	ON_COMMAND(IDM_SPLIT_DATA, OnSplitData)
END_MESSAGE_MAP()

// COpenDL_DemoView ����/����
COpenDL_DemoView::COpenDL_DemoView()
{
	// TODO: �ڴ˴���ӹ������
	m_pODL_View		=NULL;
	m_pCurve1		=NULL;
	m_pCompass		=NULL;
	m_pCurve11		=NULL;
	m_pCurve12		=NULL;
	m_pCurve4		=NULL;
	m_pCurveDlg		=NULL;
	m_pText1		=NULL;
}
COpenDL_DemoView::~COpenDL_DemoView()
{
	ODL_SafeRelease(m_pCurve1);
	ODL_SafeRelease(m_pCompass);
	ODL_SafeRelease(m_pCurve11);
	ODL_SafeRelease(m_pCurve12);
	ODL_SafeRelease(m_pCurve4);
	ODL_SafeRelease(m_pText1);
	ODL_SafeRelease(m_pODL_View);
	if(m_pCurveDlg != NULL)
	{
		m_pCurveDlg->DestroyWindow();
		delete m_pCurveDlg;
		m_pCurveDlg=NULL;
	}
}
BOOL COpenDL_DemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ
	return CView::PreCreateWindow(cs);
}
// COpenDL_DemoView ����
void COpenDL_DemoView::OnDraw(CDC* /*pDC*/)
{
	COpenDL_DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

// COpenDL_DemoView ���

#ifdef _DEBUG
void COpenDL_DemoView::AssertValid() const
{
	CView::AssertValid();
}

void COpenDL_DemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
COpenDL_DemoDoc* COpenDL_DemoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenDL_DemoDoc)));
	return (COpenDL_DemoDoc*)m_pDocument;
}
#endif //_DEBUG
VOID CALLBACK OnButtonClickedCallback(DWORD IN dwID)
{
	CString str;
	str.Format("Button: %d  clicked!",dwID);
	AfxMessageBox(str);
}

BOOL gm_bCanvasCoordInitOk =FALSE;
LRESULT COpenDL_DemoView::OnCanvasCallbackMessage(WPARAM wp,LPARAM lp)
{
	switch(wp)
	{
	case CANVAS_CALLBACKMSG_OnSizeChanged:
		{
			CODL_CanvasBase*	pCanvas =(CODL_CanvasBase*)lp;
			
			TRACE("������С�ı�...[ %s ]( %d , %d ).\r\n",
				pCanvas->GetName(),
				pCanvas->GetSize()->cx,
				pCanvas->GetSize()->cy);

			if(!gm_bCanvasCoordInitOk)
			{//ΪʲôҪ��ô����
				//�ڳ�ʼ��ʱ��������û�зŵ������ӵĻ����У���С�ǲ���ȷ�ģ�����Ҫ������������
				//��һ��ִ�е�����ʱӦ�����������²��ֻ�����

				gm_bCanvasCoordInitOk =TRUE;
				//��ʼ������������ʾ��Χ
				CODLEx_Element_Coordinate* pCoord =(CODLEx_Element_Coordinate*)pCanvas->GetCoordinate();//�õ�������
				//���������᷶Χ�������ڻ������Ԫ�ض���ʼ�����ʹ��
				pCoord->SetGraduationRange(	-10.0f,0.0f,500.0f,	-10.0f,0.0f,10.0f);
			}
			

		}
		break;
	}
	return 0;
}
// COpenDL_DemoView ��Ϣ�������
void COpenDL_DemoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	if(m_pODL_View == NULL)
	{
		DWORD	i=0;

		m_pODL_View		=new CODL_View();

		CRect clientrect;
		GetClientRect(&clientrect);
		clientrect.DeflateRect(50,50,20,20);

		//����һ���Ӷ��󣬰󶨵����ھ������ָ���ӵı���ɫ
		INT ret =m_pODL_View->Create(m_hWnd,&clientrect,FALSE,RGB(20,50,20));
		if( ret != 0)
			return ;
        //����Ӧ�ò�˵���Դ
		m_theRButtonMenu.LoadMenu(IDR_RBUTTON_MENU);

		CODLEx_Element_ZoomFrame* pFrame;
		CODLEx_Element_Coordinate* pCoord;
		
		//��������Ϊ��ǰ�������һ����������Ϊ��test������������
		CODL_CanvasBase*		pCanvas =m_pODL_View->AddNewCanvas("test���Ի���");
		
		//Ϊ�������� �ص���ϢID,�����ڻ�����С�ı�ʱ����Ϣ����
		pCanvas->SetCallbackMessageID(m_hWnd,USERMSG_CANVAS);//�˴�����������������ʾ��Χ


		//Ϊ�»��������Ҽ��˵�
		pCanvas->SetRButtonMenu(m_theRButtonMenu.GetSubMenu(1)->GetSafeHmenu());
		//Ϊ��������һ���������
		CODLEx_Element_CanvasTitle*		pTitle =new CODLEx_Element_CanvasTitle(pCanvas);
		pCanvas->AddObj(pTitle);
		
		CODLEx_Element_PictureButton*	pPictureBtn=NULL;
		
		

		CODLEx_Element_ShapeEllipse*	pEllipse =new CODLEx_Element_ShapeEllipse(pCanvas);
		pCanvas->AddObj(pEllipse);
		pEllipse->Release();
		pEllipse->SetShapeCoordinate(ODLSC_COORDINATE);
		pEllipse->SetPos(2,1);
		pEllipse->SetSize(5,3);
		pEllipse->EnableFill(TRUE);
		pEllipse->EnableStroke(TRUE);
		pEllipse->EnableSelect(TRUE);
		pEllipse->EnableAdjustSize(TRUE);
		pEllipse->EnableDrag(TRUE);
		pEllipse->SetAlpha(125);

		CODLEx_Element_ShapeRectangle*	pRectangle =new CODLEx_Element_ShapeRectangle(pCanvas);
		pCanvas->AddObj(pRectangle);
		pRectangle->Release();
		pRectangle->SetShapeCoordinate(ODLSC_COORDINATE);
		pRectangle->SetPos(0,0);
		pRectangle->SetSize(5,3);
		pRectangle->EnableRoundRect(TRUE);
		pRectangle->SetRoundSize(1,1);
		pRectangle->EnableFill(TRUE);
		pRectangle->EnableStroke(TRUE);
		pRectangle->EnableSelect(TRUE);
		pRectangle->EnableAdjustSize(TRUE);
		pRectangle->EnableDrag(TRUE);
		pRectangle->SetAlpha(125);

		CODLEx_Element_ShapeLine*	pShapeLine =new CODLEx_Element_ShapeLine(pCanvas);
		pCanvas->AddObj(pShapeLine);
		pShapeLine->Release();
		pShapeLine->SetStartPoint(200,110);
		pShapeLine->SetEndPoint(200,500);
		pShapeLine->EnableSelect(TRUE);
		pShapeLine->EnableAdjustSize(TRUE);
		pShapeLine->EnableDrag(TRUE);
		pShapeLine->SetShapeCoordinate(ODLSC_SCREEN);
		LOGPEN lp;
		lp.lopnColor	=RGB(255,255,0);
		lp.lopnStyle	=PS_SOLID;
		lp.lopnWidth.x	=5;
		lp.lopnWidth.y	=5;
		pShapeLine->SetStokePen(&lp);


		//###ָ�������ı�����
		pCanvas->SetCanvasTitle(pTitle);

		pTitle->SetBorderStyle(PS_SOLID,2,RGB(50,50,100));
		pTitle->Release();


		//��ӻ���Ĭ�Ϲ�����
		CODLEx_Element_DefaultToolbar*	pDefaultToolBar =new CODLEx_Element_DefaultToolbar(pCanvas);
		pDefaultToolBar->Init(24,24 );
		pCanvas->AddObj(pDefaultToolBar);
		pDefaultToolBar->SetPos(0,0);
		pDefaultToolBar->Release();

		//���һ��ͼ������
		CODLEx_Element_DiagramPreview* pPreview =new CODLEx_Element_DiagramPreview(pCanvas);
		pCanvas->AddObj(pPreview);
		//����ͼ����z-indexֵ��
		pPreview->SetZIndex(12);
		//����ͼ����ʼλ��
		pPreview->SetPos(50,50);
		//����͸����
		pPreview->SetAlpha(200);
		//������ǰͼ��ָ��ö���
		pCanvas->SetDiagramPreview(pPreview);
		pPreview->Release();


		//���һ������
		CODLEx_Element_Label*	pLabel =new CODLEx_Element_Label(pCanvas);
		pLabel->Init(5,3);
		pLabel->SetTitle("���Ա��� title");
		pLabel->ShowTitle(TRUE);
		pLabel->ShowBorder(TRUE);
		pLabel->SetBorderStyle(PS_SOLID,1,RGB(0,255,0));
		pLabel->SetMargin(10);
	
		pLabel->GetTitleTextObject()->SetTextFont("����",16);
		pLabel->GetTitleTextObject()->SetTextColor(RGB(255,0,255));
		 

		srand(time(NULL));
		CString txt;
		for(int x=0;x<5;x++)
			for(int y=0;y<3;y++)
			{
				txt.Format(" %d��%d�� ",x,y);
				pLabel->SetText(x,y,txt);
				pLabel->SetTextColor(x,y,RGB(rand()%255,rand()%255,rand()%255));
				pLabel->SetTextBkColor(x,y,RGB(rand()%255,rand()%255,rand()%255));
			}
		pLabel->SetAnchorPos(100,100);
		pLabel->SetPos(250,250);
		pLabel->SetZIndex(100);
		pLabel->SetAlpha(205);
		pCanvas->AddObj(pLabel);
		pLabel->Release();


		//���һ����������
		CODLEx_Element_SafeArea*	pArea =new CODLEx_Element_SafeArea(pCanvas);
		pArea->SetYMaxValue(30.0f);
		pArea->SetYMinValue(-30.0f);
		pArea->ShowYDownlimitLine(TRUE);
		pArea->ShowYUplimitLine(TRUE);

		pArea->SetXMaxValue(130.0f);
		pArea->SetXMinValue(-130.0f);
		pArea->ShowXDownlimitLine(TRUE);
		pArea->ShowXUplimitLine(TRUE);

		pArea->ShowText(TRUE);
		pCanvas->AddObj(pArea);
		pArea->Release();


		
		////���һ����ť
		//CODLEx_Element_Button*	pButton=new CODLEx_Element_Button(pCanvas);
		////�趨�ص�����
		//pButton->SetClickedCallback((BTN_CLICKED_CALLBACK)OnButtonClickedCallback);
		//pButton->SetID(2000);
		//pButton->SetTitle("���԰�ť z-index=11","����",20,RGB(255,0,255));
		//pButton->SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
		//pButton->SetPos(100,40);
		//pButton->SetSize(250,32);
		////��ӵ�����
		//pCanvas->AddObj(pButton);
		////����z-index 
		//pButton->SetZIndex(11);
		//pButton->Release();


		//����һ������ѡ�����󣬲���ӵ�����
		pFrame =new CODLEx_Element_ZoomFrame(pCanvas);
		pCanvas->AddObj(pFrame);
		pCanvas->SetZoomFrame(pFrame);
		
		//���Ӧ�ò���Ҫʹ�øö����򱣴�ָ�룬�����˳�ʱRelease��
		pFrame->Release();
		
		//���û����ı���ɫ
		pCanvas->SetBkColor(RGB(0,0,0));
		


		//���һ���ı�����
		m_pText1 =new CODLEx_Element_TextArea(pCanvas);
		pCanvas->AddObj(m_pText1);
		m_pText1->SetText("�ı�������� z-index=10");
		m_pText1->SetTextFont("����",12,600);
		m_pText1->SetZIndex(10);//���ڶ���
		m_pText1->SetMargin(10);
		m_pText1->SetTextColor(RGB(255,255,255));
		m_pText1->SetBkColor(RGB(50,150,50));
		m_pText1->SetBorder(RGB(255,255,255),1,PS_DOT);
		m_pText1->SetTextAlign(DT_LEFT|DT_TOP);
		m_pText1->SetAlpha(205);
		//m_pText1->EnableDrag(TRUE);



		//����һ�������������ӵ�����
		pCoord =new CODLEx_Element_Coordinate(pCanvas);
		pCanvas->AddObj(pCoord);
		pCanvas->SetCoordinate(pCoord);
		pCoord->SetCenterOffset(50,50);	//������ԭ���ʼλ������ڻ��������·���		
		//����X��������ÿ���̶ȶ�������
		pCoord->SetXPerUnitPixels(50.0f);
		pCoord->SetXUnitValue(1.0f);
		//����Y��ÿ���̶ȶ�������
		pCoord->SetYPerUnitPixels(50.0f);
		pCoord->SetYUnitValue(1.0f); 
		//�������������ƺ����塢��ɫ
		pCoord->SetXAxisName("x��",RGB(255,0,0),"����",12);
		pCoord->SetYAxisName("y��",RGB(0,255,0),"����",12);
		//������������ʽ���߿���ɫ
		pCoord->SetXAxisPara(2,RGB(250,0,0));
		pCoord->SetYAxisPara(2,RGB(0,250,0));
		//�̶������᷶Χ���ڻ�����С�ı�ʱ
		pCoord->EnableBindStatus(TRUE);	
		pCoord->EnableShowYAxisAssistText(TRUE);
		pCoord->SetYAxisAssistTextScale(0.5f);
		pCoord->SetYAxisAssistTextColor(RGB(255,50,0));

		//��Demo����û���õ������ᣬ�˴�ֱ��Release
		pCoord->Release();



		//Ϊ�������һ��ʮ���߶���
		CODLEx_Element_CrossLine* pCrossLine =new CODLEx_Element_CrossLine(pCanvas);
		pCanvas->AddObj(pCrossLine);
		//����ʮ���ߵ���ʽ����
		pCanvas->SetCrossLine(pCrossLine);
		pCrossLine->SetLineParameter(PS_SOLID,1,RGB(0,255,0));
		pCrossLine->Invalidate();
		pCrossLine->Release();


		//���һ�����ߣ����ں���Ҫ������������ݣ����Ա����˸ö����ָ��
		m_pCurve1 =new CODLEx_Element_CurveBase(pCanvas,"Yֵ�Ŵ���3.75��������");
		pCanvas->AddObj(m_pCurve1);
		//��ʼ������
		m_pCurve1->Init(PS_DOT,1,RGB(255,0,0));
		

		m_pCurve1->Invalidate();

		//�����Ҽ��˵�
		m_pCurve1->SetRButtonMenu((HMENU)m_theRButtonMenu.GetSubMenu(0)->GetSafeHmenu());
		//������������
		m_pCurve1->SetScale(1.0f,3.75f);

		//������ߵ㳬��Ҳ���
		m_pCurve1->EnableLinkOverflow(TRUE);



		//�����һ������
		m_pCurve11 =new CODLEx_Element_CurveBase(pCanvas,"���ۺ���");
		pCanvas->AddObj(m_pCurve11);
		m_pCurve11->Init(PS_SOLID,1,RGB(255,255,255));
		m_pCurve11->EnableAutoScroll(FALSE);
		//������ߵ㳬��Ҳ���
		m_pCurve11->EnableLinkOverflow(TRUE);

		m_pCurve11->Invalidate();
		m_pCurve11->SetRButtonMenu((HMENU)m_theRButtonMenu.GetSubMenu(0)->GetSafeHmenu());

		m_pCurve12 =new CODLEx_Element_CurveBase(pCanvas,"line12");
		pCanvas->AddObj(m_pCurve12);
		m_pCurve12->Init(PS_SOLID,2,RGB(0,255,255));

		m_pCurve12->Invalidate();
		m_pCurve12->SetRButtonMenu((HMENU)m_theRButtonMenu.GetSubMenu(0)->GetSafeHmenu());
		//������ߵ㳬��Ҳ���
		m_pCurve12->EnableLinkOverflow(TRUE);

	
		pCanvas->Release();
		////////////////////////////////////////////

		//����һ������
		pCanvas =m_pODL_View->AddNewCanvas("����2��");
		pCanvas->SetRButtonMenu(m_theRButtonMenu.GetSubMenu(1)->GetSafeHmenu());
		//Ϊ��������һ���������
		pTitle =new CODLEx_Element_CanvasTitle(pCanvas);
		pCanvas->AddObj(pTitle);
		
		//###ָ�������ı�����
		pCanvas->SetCanvasTitle(pTitle);

		pTitle->SetBackgroundStyle(BS_SOLID,HS_HORIZONTAL,RGB(150,150,150));
		pTitle->SetFont("����",24,500);
		pTitle->SetTitleColor(RGB(255,200,50));
		pTitle->SetBorderStyle(PS_DOT,1,RGB(255,255,255));
		pTitle->Release();


		pFrame =new CODLEx_Element_ZoomFrame(pCanvas);
		pCanvas->AddObj(pFrame);
		pCanvas->SetZoomFrame(pFrame);
		pFrame->Release();


		pCoord =new CODLEx_Element_Coordinate(pCanvas);
		pCanvas->AddObj(pCoord);
		pCanvas->SetCoordinate(pCoord);
		pCoord->SetCenterOffset(50,50);
		pCoord->SetXPerUnitPixels(20.0f);
		pCoord->SetYPerUnitPixels(20.0f);
		pCoord->SetYUnitValue(1.0f);

		pCoord->EnableShowYAxisAssistText(TRUE);
		pCoord->SetYAxisAssistTextScale(0.5f);
		pCoord->SetYAxisAssistTextColor(RGB(255,50,0));
		pCoord->MinusYAxis(TRUE);
		pCoord->Release();



		//���һ��ָ����
		m_pCompass =new CODLEx_Element_Compass(pCanvas,40,60,100);
		pCanvas->AddObj(m_pCompass);

		m_pCompass->SetSize(40,80);

		CODLEx_Element_Ship*	pShip	=new CODLEx_Element_Ship(pCanvas);
		pCanvas->AddObj(pShip);
		pShip->Release();


		CODLEx_Element_DropPoint*	pPoint =new CODLEx_Element_DropPoint(pCanvas);

		pPoint->SetDropPointName("GPS�������");
		pPoint->SetDropPointRadius(6);
		pPoint->SetPointColor(RGB(255,255,0));
		pPoint->ShowLabel(TRUE);
		pPoint->SetOffset(7,5);
		pCanvas->AddObj(pPoint);
		pPoint->Release();


		pPoint =new CODLEx_Element_DropPoint(pCanvas);
		pPoint->SetDropPointName("ˮ���������");
		pPoint->SetDropPointRadius(6);
		pPoint->SetPointColor(RGB(255,0,255));
		pPoint->ShowLabel(TRUE);
		pPoint->SetOffset(5,-10);
		pCanvas->AddObj(pPoint);
		pPoint->Release();



		pCanvas->Release();
		////////////////////////////////////////////

		//����һ������
		pCanvas =m_pODL_View->AddNewCanvas("test3");
		pCanvas->SetRButtonMenu(m_theRButtonMenu.GetSubMenu(1)->GetSafeHmenu());
		//Ϊ��������һ���������		
		pTitle =new CODLEx_Element_CanvasTitle(pCanvas);
		pCanvas->AddObj(pTitle);
		pTitle->Release();

		pFrame =new CODLEx_Element_ZoomFrame(pCanvas);
		pCanvas->AddObj(pFrame);
		pCanvas->SetZoomFrame(pFrame);
		pFrame->Release();





		CODLEx_Element_Report*	pReport  =new CODLEx_Element_Report(pCanvas);
		pCanvas->AddObj(pReport);
		pReport->SetPos(50,50);
		pReport->SetSize(300,300);
		pReport->SetRows(24);
		pReport->SetCols(14);
		CODLEx_Element_ReportRow* pRow;
		LOGBRUSH lb;
		lb.lbColor	=RGB(200,250,250);
		lb.lbHatch	=0;
		lb.lbStyle	=BS_SOLID;
		for(LONG j=0;j<pReport->GetRows();j++)
		{
			pRow =pReport->GetRow(j);
			if(j%2==0)
				pRow->SetDefaultBkBrush(&lb);
		}
		pReport->ShowHeader(TRUE);
		lb.lbColor=RGB(155,155,155);
		pReport->GetHeader()->SetDefaultBkBrush(&lb);
		LOGFONT lf;
		ZeroMemory(&lf,sizeof(lf));
		lf.lfCharSet	=GB2312_CHARSET;
		strcpy(lf.lfFaceName,"����");
		lf.lfHeight		=16;
		lf.lfWeight		=1000;
		pReport->GetHeader()->SetDefaultFont(&lf);
		pReport->GetHeader()->SetDefaultTextColor(RGB(0,0,0));

		pReport->EnableSelect(TRUE);
		pReport->EnableAdjustSize(TRUE);
		pReport->EnableDrag(TRUE);
		pReport->EnsureVisible(14,5);
		
		pReport->SetRowTextColor(5,RGB(255,0,0));
		pReport->SetColBkBrush(0,&lb);

		lb.lbColor=RGB(255,200,255);
		pReport->SetColBkBrush(3,&lb);

		lb.lbColor=RGB(255,255,200);
		pReport->SetColBkBrush(5,&lb);

		char text[64];
		for(i=0;i<24;i++)
		{
			pReport->SetRowHeight(i,32+rand()%50);
			for(int j=0;j<pReport->GetRow(i)->GetItemCount();j++)
			{
				sprintf(text,"����[%d:%d]",i,j);
				pReport->GetRow(i)->GetItem(j)->SetText(text);
			}
		}
		pReport->SetColWidth(0,80);

		CODLEx_Element_ReportRow* pHeader =pReport->GetHeader();
		for(i=0;i<pHeader->GetItemCount();i++)
		{
			sprintf(text,"��ͷ%02d",i+1);
			pHeader->GetItem(i)->SetText(text);
			pHeader->GetItem(i)->EnableClicked(TRUE);
			pHeader->GetItem(i)->ShowBorder(TRUE);
			pHeader->GetItem(i)->SetBorderSize(1);
		}
		CImageList theImageList;
		theImageList.Create(32,32,ILC_COLOR8,0,4);		
		theImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
		CODL_ImageList* pImageList =new CODL_ImageList(&theImageList);

		for(i=0;i<pReport->GetRows();i++)
		{
			pReport->GetItem(i,0)->
				EnableClicked(TRUE)->
				ShowBorder(TRUE)->
				SetBorderSize(1)->
				SetImage(pImageList,0)->
				EnableSelect(FALSE);
		}
		for(i=0;i<pReport->GetRows();i++)
		{
			pReport->GetItem(i,4)->
				EnableClicked(TRUE)->
				ShowBorder(TRUE)->
				SetBorderSize(1)->
				SetImage(pImageList,0)->
				EnableSelect(FALSE);
		}


		pImageList->Release();

		pReport->Release();
		pCanvas->Release();




		////////////////////////////////////////////

		//������������������һ��������������������
		pCanvas =m_pODL_View->AddNewCanvas("test4");
		pCanvas->SetRButtonMenu(m_theRButtonMenu.GetSubMenu(1)->GetSafeHmenu());


		pFrame =new CODLEx_Element_ZoomFrame(pCanvas);
		pCanvas->AddObj(pFrame);
		pCanvas->SetZoomFrame(pFrame);
		pFrame->Release();


		pCoord =new CODLEx_Element_Coordinate(pCanvas);
		pCanvas->AddObj(pCoord);
		pCanvas->SetCoordinate(pCoord);
		pCoord->SetCenterOffset(50,50);
		pCoord->SetYPerUnitPixels(20.0f);
		pCoord->Release();

		m_pCurve4 =new CODLEx_Element_CurveBase(pCanvas,"test_line1");
		pCanvas->AddObj(m_pCurve4);
		m_pCurve4->Init(PS_SOLID,1,RGB(255,250,0));
		m_pCurve4->Invalidate();
		m_pCurve4->SetRButtonMenu((HMENU)m_theRButtonMenu.GetSubMenu(0)->GetSafeHmenu());


		CODLEx_Element_Histogram*	pHistogram =new CODLEx_Element_Histogram(pCanvas);
		pCanvas->AddObj(pHistogram);
		for( i=0;i<100;i++)
		{
			pHistogram->AddData(i,2+rand()%9);
		}
		pHistogram->SetZIndex(-1);
		pHistogram->Release();
		pCanvas->Release();


		////////////////////////////////////////////

		//����һ������
		pCanvas =m_pODL_View->AddNewCanvas("ScrollBar");
		CODLEx_Element_ScrollBar*	pScrollBar =new CODLEx_Element_ScrollBar(pCanvas);

		pScrollBar->SetPos(250,150);
		pScrollBar->SetSize(20,200);
		pScrollBar->SetPageSize(50);
		pScrollBar->SetPosition(50);

		CODL_Brush* pbrush =m_pODL_View->GetResourceManager()->CreateBrush(PS_SOLID,RGB(125,125,125),0);
		pScrollBar->SetBackBrush(pbrush);
		pbrush->Release();

		pCanvas->AddObj(pScrollBar);
		pScrollBar->Release();


		pScrollBar =new CODLEx_Element_ScrollBar(pCanvas);
		pScrollBar->SetPos(50,350);
		pScrollBar->SetSize(200,20);
		pScrollBar->SetPageSize(50);
		pScrollBar->SetPosition(50);
		pScrollBar->SetHorizontal(TRUE);
		pCanvas->AddObj(pScrollBar);
		pScrollBar->Release();


		CODLEx_Element_LedDigital*		pDigital =new CODLEx_Element_LedDigital(pCanvas);
		pCanvas->AddObj(pDigital);
		pDigital->SetPos(100,100);
		pDigital->SetSize(400,40);
		pDigital->SetValue("-12:34:56.7890");
		pDigital->EnableAdjustSize(TRUE);
		pDigital->EnableSelect(TRUE);
		pDigital->EnableDrag(TRUE);
		
		pDigital->Release();



		pCanvas->Release();



		//����һ������
		pCanvas =m_pODL_View->AddNewCanvas("GUI Test");
		pCanvas->SetBkColor(RGB(20,50,20));
		CHAR Dir[1024];
		ZeroMemory(Dir,sizeof(Dir));
		GetModuleFileName(NULL,Dir,1024);
		for(int i=strlen(Dir)-1;i>0;i--)
		{
			if(Dir[i]=='\\')
			{
				Dir[i]=0;
				break;
			}
		}


		CString normal,active,checked,focus;

		
		normal.Format("%s\\Resource\\main.png",Dir);
		CODLEx_Element_Picture* pMainFrame=new CODLEx_Element_Picture(pCanvas);
		if(pMainFrame->SetImage(normal))
		{
			pCanvas->AddObj(pMainFrame);
			pMainFrame->SetSize(1920*0.8,84*0.8);
		}
		ODL_SafeRelease(pMainFrame);

		normal.Format("%s\\Resource\\status.png",Dir);
		pMainFrame=new CODLEx_Element_Picture(pCanvas);
		if(pMainFrame->SetImage(normal))
		{
			pCanvas->AddObj(pMainFrame);
			pMainFrame->SetPos(770,793);
			pMainFrame->SetSize(766*0.8,49*0.8);

		}
		ODL_SafeRelease(pMainFrame);
		
		normal.Format("%s\\Resource\\btn1_normal.png",Dir);
		CODLEx_Element_Picture* pImage=new CODLEx_Element_Picture(pCanvas);
		pImage->SetImage(normal);
		pImage->EnableAdjustSize(TRUE);
		pImage->EnableSelect(TRUE);
		pImage->EnableDrag(TRUE);
		pCanvas->AddObj(pImage);
		pImage->SetPos(10,90);
		pImage->Release();


		CODLEx_Element_PictureButton*	pButton =NULL;
		POINT	pos;
		SIZE	size;

		pos.x=1370;
		pos.y=72;
		size.cx =166;
		size.cy	=82;
		
		for(int i=1;i<10;i++)
		{
			pButton	=new CODLEx_Element_PictureButton(pCanvas);
			pCanvas->AddObj(pButton);
			normal.Format(		"%s\\Resource\\btn%d_normal.png",Dir,i);
			active.Format(		"%s\\Resource\\btn%d_active.png",Dir,i);
			checked.Format(		"%s\\Resource\\btn%d_checked.png",Dir,i);
			focus.Format(		"%s\\Resource\\btn%d_focus.png",Dir,i);

			pButton->SetNormalImage(normal);
			pButton->SetActiveImage(active);
			pButton->SetCheckedImage(checked);
			pButton->SetFocusImage(focus);
			pButton->SetPos(pos.x,pos.y+(i-1)*(size.cy+3));
			pButton->SetSize(size);
			//pButton->SetCourse(-10.0f);
			pButton->EnableSelect(TRUE);
			pButton->EnableAdjustSize(TRUE);
			pButton->EnableDrag(TRUE);
			
			ODL_SafeRelease(pButton);
		}



		pos.x	=4;
		pos.y	=793;
		size.cx =144;
		size.cy	=42;

		for(int i=1;i<6;i++)
		{
			pButton	=new CODLEx_Element_PictureButton(pCanvas);
			normal.Format(		"%s\\Resource\\label%d_normal.png",Dir,i);
			checked.Format(		"%s\\Resource\\label%d_checked.png",Dir,i);
			
			pCanvas->AddObj(pButton);
			pButton->SetNormalImage(normal);
			pButton->SetCheckedImage(checked);
			pButton->SetPos(pos.x+(i-1)*(size.cx+3),pos.y);
			pButton->SetSize(size);
			pButton->EnableChecked(TRUE);
			
			ODL_SafeRelease(pButton);
		}

		pCanvas->Release();
		
		


		//�����Ӷ���Ļ������ֲ�����
		m_pODL_View->SetCanvasLayout(2,3);








	}	    
	SetTimer(1,200,NULL);

}
void COpenDL_DemoView::OnDestroy()
{
	ODL_SafeRelease(m_pODL_View);
	CView::OnDestroy();
}

void COpenDL_DemoView::OnClose()
{
	ODL_SafeRelease(m_pODL_View);
	CView::OnClose();
}


DWORD	gm_dwSplitData=0;

void COpenDL_DemoView::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1:
		{
			break;
			static DWORD counter =0;
			m_pCurve1->AddData(counter,1+rand()%9,gm_dwSplitData);
			m_pCurve11->AddData(counter,3+rand()%9,gm_dwSplitData);
			m_pCurve12->AddData(counter,1+rand()%15,gm_dwSplitData);
			
			counter++;

			m_pCompass->SetPose(m_pCompass->GetPose()+2.0f);

			
			static float angle=0.0f,radius=1.0f;
			float x,y;
			
			radius+=0.05f;
			angle+=5.0f;
			x =radius*sin(angle/180.0f*3.141592654f);
			y =radius*cos(angle/180.0f*3.141592654f);
			

			m_pText1->SetPos(100+x,100+y);



			m_pCurve11->Invalidate(FALSE);//ʹ���ߺͻ�����Ч
			m_pCurve12->Invalidate(FALSE);
			m_pCurve1->Invalidate(FALSE);
			m_pCurve4->Invalidate(TRUE);//ʹ���ߡ��������Ӷ���Ч
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}
void COpenDL_DemoView::OnShowCurve()
{
	CCurveDlg dlg;
	dlg.DoModal();

}

void COpenDL_DemoView::OnShowCurveModal()
{
	if(m_pCurveDlg == NULL)
	{
		m_pCurveDlg =new CCurveDlg(this);
		m_pCurveDlg->Create(IDD_CURVE_DLG,this);
	}
	m_pCurveDlg->ShowWindow(SW_SHOW);
}

void COpenDL_DemoView::OnSavecanvasToFile()
{
	if(m_pODL_View == NULL)
		return;
	CFileDialog dlg(FALSE,"bmp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"bmp Files (*.bmp)|*.bmp||");
	if(dlg.DoModal()!=IDOK)
		return;

	if(m_pODL_View->GetActiveCanvas()->SaveToBmpFile(dlg.GetPathName()))
	{
		ShellExecute(NULL,"open",dlg.GetPathName(),NULL,NULL,SW_SHOW);
	}

}

void COpenDL_DemoView::OnSavecanvasToClipboard()
{
	if(m_pODL_View == NULL)
		return;
	m_pODL_View->GetActiveCanvas()->SaveToClipboard();
}

void COpenDL_DemoView::OnSaveviewToFile()
{
	if(m_pODL_View == NULL)
		return;
	CFileDialog dlg(FALSE,"bmp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"bmp Files (*.bmp)|*.bmp||");
	if(dlg.DoModal()!=IDOK)
		return;

	if(m_pODL_View->SaveToBmpFile(dlg.GetPathName()))
	{
		ShellExecute(NULL,"open",dlg.GetPathName(),NULL,NULL,SW_SHOW);
	}	

}

void COpenDL_DemoView::OnSaveviewToClipboard()
{
	if(m_pODL_View == NULL)
		return;
	m_pODL_View->SaveToClipboard();
}
#include "AbsLocateDlg.h"
void COpenDL_DemoView::OnAbsLocate()
{
	CAbsLocateDlg dlg(this);
	if(dlg.DoModal()!=IDOK)
		return;
	CODLEx_Element_Coordinate* pCoord =(CODLEx_Element_Coordinate*)m_pODL_View->GetActiveCanvas()->GetCoordinate();
	if(pCoord!=NULL)
	{
		pCoord->AbsLocate(dlg.m_fXValue);
		m_pODL_View->GetActiveCanvas()->EnableAutoScroll(FALSE);
	}
	
}
void COpenDL_DemoView::OnShowHidePreview()
{
	CODLEx_Element_DiagramPreview* pPreview =(CODLEx_Element_DiagramPreview*)m_pODL_View->GetActiveCanvas()->GetDiagramPreview();
	if(pPreview!=NULL)	
		pPreview->Show(!pPreview->IsShow());

}

void COpenDL_DemoView::OnUpdateShowHidePreview(CCmdUI *pCmdUI)
{

}

void COpenDL_DemoView::OnCurveCleardata()
{
	CODL_CanvasBase* pCanvas =m_pODL_View->GetActiveCanvas();
	if(pCanvas==NULL)
		return;
	CODL_ElementBase* pElement =pCanvas->GetSelected();
	if(pElement == NULL)
		return;
	switch(pElement->GetType())
	{
	case ODL_ELEMENT_CURVE:
		{
			((CODLEx_Element_CurveBase*)pElement)->ClearData();
		}
		break;
	}

}

void COpenDL_DemoView::OnSplitData()
{
	gm_dwSplitData=!gm_dwSplitData;
}
