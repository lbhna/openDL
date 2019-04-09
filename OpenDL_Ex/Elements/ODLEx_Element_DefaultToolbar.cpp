#include "StdAfx.h"
#include ".\odlex_element_defaulttoolbar.h"

CODLEx_Element_DefaultToolbar::CODLEx_Element_DefaultToolbar(CODL_CanvasBase* IN pCanvas)
:CODLEx_Element_Toolbar(pCanvas)
{
	m_Type		= ODL_ELEMENT_DEFAULT_TOOLBAR;

}

CODLEx_Element_DefaultToolbar::~CODLEx_Element_DefaultToolbar(void)
{
}
INT				CODLEx_Element_DefaultToolbar::Init(DWORD IN dwBtnWidth,DWORD IN dwBtnHeight)
{
	CResourceLoader		autoResource;
	
	SetButtonSize(dwBtnWidth,dwBtnHeight);

	CODLEx_Element_CheckButton*		pCheckBtn	=NULL;

	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DRAG_AXIS));
	pCheckBtn->SetID(ODL_OPER_DRAG_AXIS);
	pCheckBtn->SetTips("�ƶ������� ( A + LButton )");
	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DRAG_AXIS_X));
	pCheckBtn->SetID(ODL_OPER_DRAG_AXIS_X);
	pCheckBtn->SetTips("�ƶ�������X ( X + LButton )");
	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DRAG_AXIS_Y));
	pCheckBtn->SetID(ODL_OPER_DRAG_AXIS_Y);
	pCheckBtn->SetTips("�ƶ�������Y ( Y + LButton )");

	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DRAG_DIAGRAM));
	pCheckBtn->SetID(ODL_OPER_DRAG_DIAGRAM);
	pCheckBtn->SetTips("ƽ��ͼ��  ( D + LButton )");
	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_SCALE_AXIS));
	pCheckBtn->SetID(ODL_OPER_SCALE_AXIS);
	pCheckBtn->SetTips("���������� ( A + MButton )");

	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_SCALE_AXIS_X));
	pCheckBtn->SetID(ODL_OPER_SCALE_AXIS_X);
	pCheckBtn->SetTips("����������X ( X + MButton )");
	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_SCALE_AXIS_Y));
	pCheckBtn->SetID(ODL_OPER_SCALE_AXIS_Y);
	pCheckBtn->SetTips("����������Y ( Y + MButton )");
	AddButton(pCheckBtn);
	pCheckBtn->Release();
	//-----------------------------------------------------------------


	//-----------------------------------------------------------------
	CODLEx_Element_Button* pBtn	= new CODLEx_Element_Button(GetCanvas());
	pBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DIAGRAM_MOVELEFT));
	pBtn->SetID(ODL_OPER_DIAGRAM_MOVELEFT);
	pBtn->SetTips("ͼ������ ( LEFT / J )");
	AddButton(pBtn);
	pBtn->Release();
	//-----------------------------------------------------------------
	
	//-----------------------------------------------------------------
	pBtn	= new CODLEx_Element_Button(GetCanvas());
	pBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DIAGRAM_MOVERIGHT));
	pBtn->SetID(ODL_OPER_DIAGRAM_MOVERIGHT);
	pBtn->SetTips("ͼ������ ( RIGHT / L )");
	AddButton(pBtn);
	pBtn->Release();
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	pBtn	= new CODLEx_Element_Button(GetCanvas());
	pBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DIAGRAM_MOVEUP));
	pBtn->SetID(ODL_OPER_DIAGRAM_MOVEUP);
	pBtn->SetTips("ͼ������ ( UP / I )");
	AddButton(pBtn);
	pBtn->Release();
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	pBtn	= new CODLEx_Element_Button(GetCanvas());
	pBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DIAGRAM_MOVEDOWN));
	pBtn->SetID(ODL_OPER_DIAGRAM_MOVEDOWN);
	pBtn->SetTips("ͼ������ ( DOWN / K )");
	AddButton(pBtn);
	pBtn->Release();
	//-----------------------------------------------------------------
	
	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_AUTO_SCROLL));
	pCheckBtn->SetID(ODL_OPER_ENABLE_AUTOSCROLL);
	pCheckBtn->SetTips("����/��ֹ ͼ���Զ�����");
	pCheckBtn->SetChecked(TRUE); 
	AddButton(pCheckBtn);
	pCheckBtn->SetGroupControl(FALSE);
	pCheckBtn->Release();


	//-----------------------------------------------------------------
	pCheckBtn	= new CODLEx_Element_CheckButton(GetCanvas());
	pCheckBtn->SetIcon(AfxGetApp()->LoadIcon(IDI_VIEW_STYLE));
	pCheckBtn->SetID(ODL_OPER_VIEWSTYLE_CASCADE);
	pCheckBtn->SetTips("ƽ��/��� ��ͼ");
	pCheckBtn->SetChecked(FALSE); 
	AddButton(pCheckBtn);
	pCheckBtn->SetGroupControl(FALSE);
	pCheckBtn->Release();






	return 0;
}
VOID				CODLEx_Element_DefaultToolbar::OnButtonClicked(CODLEx_Element_Button* IN pButton)
{
	CODLEx_Element_Toolbar::OnButtonClicked(pButton);

	if(pButton->GetType() == ODL_ELEMENT_CHECK_BUTTON)
	{
		if( ((CODLEx_Element_CheckButton*)pButton)->IsChecked() )
			GetCanvas()->SetCurrentOperation((ODL_OPERATION_TYPE)pButton->GetID());
		else
			GetCanvas()->SetCurrentOperation(ODL_OPER_NONE);
	}
	
	switch(pButton->GetID())
	{
	case ODL_OPER_DIAGRAM_MOVELEFT:
		{
			if(GetCanvas()->GetSelected() != NULL)
				return;
			GetCanvas()->MoveLeft(-1);
			
		}
		break;
	case ODL_OPER_DIAGRAM_MOVERIGHT:
		{
			if(GetCanvas()->GetSelected() != NULL)
				return;
			GetCanvas()->MoveLeft(1);
		}
		break;
	case ODL_OPER_DIAGRAM_MOVEUP:
		{
			if(GetCanvas()->GetSelected() != NULL)
				return;
			GetCanvas()->MoveUp(1);
		}
		break;
	case ODL_OPER_DIAGRAM_MOVEDOWN:
		{
			if(GetCanvas()->GetSelected() != NULL)
				return;
			GetCanvas()->MoveUp(-1);
		}
		break;
	case ODL_OPER_ENABLE_AUTOSCROLL:
		{
			GetCanvas()->EnableAutoScroll(!GetCanvas()->IsEnableAutoScroll());
		}
		break;
	case ODL_OPER_VIEWSTYLE_CASCADE:
		{
			BOOL bChecked	=((CODLEx_Element_CheckButton*)pButton)->IsChecked();
			if(bChecked)
				GetCanvas()->GetView()->SetViewStyle(OVS_CASCADE);
			else
				GetCanvas()->GetView()->SetViewStyle(OVS_TILES);			

		}
		break;
	}


}
BOOL		CODLEx_Element_DefaultToolbar::OnDraw(HDC IN hDC,RECT* IN pPaintRect)
{
	DrawBkground(hDC,pPaintRect);

	/////////////////////////////////////////////////////////////
	POSITION	pos;
	CODLEx_Element_Button*		pButton =GetFirstButton(pos);
	while(pButton != NULL)
	{
		if(pButton->GetID()==ODL_OPER_ENABLE_AUTOSCROLL)
		{
			((CODLEx_Element_CheckButton*)pButton)->SetChecked(GetCanvas()->IsEnableAutoScroll());
		}
		pButton->Draw(hDC,pPaintRect);
		pButton =GetNextButton(pos);
	}



	return TRUE;
}