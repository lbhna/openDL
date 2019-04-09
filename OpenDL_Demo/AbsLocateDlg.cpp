// AbsLocateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "opendl_demo.h"
#include "AbsLocateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbsLocateDlg dialog


CAbsLocateDlg::CAbsLocateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAbsLocateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbsLocateDlg)
	m_fXValue = 0.0f;
	//}}AFX_DATA_INIT
}


void CAbsLocateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbsLocateDlg)
	DDX_Text(pDX, IDC_X_VALUE, m_fXValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbsLocateDlg, CDialog)
	//{{AFX_MSG_MAP(CAbsLocateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbsLocateDlg message handlers

void CAbsLocateDlg::OnOK() 
{
	if(!UpdateData(TRUE))
		return;
	
	CDialog::OnOK();
}
