// OpenDL_DemoDoc.cpp :  COpenDL_DemoDoc ���ʵ��
//

#include "stdafx.h"
#include "OpenDL_Demo.h"

#include "OpenDL_DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenDL_DemoDoc

IMPLEMENT_DYNCREATE(COpenDL_DemoDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenDL_DemoDoc, CDocument)
END_MESSAGE_MAP()


// COpenDL_DemoDoc ����/����

COpenDL_DemoDoc::COpenDL_DemoDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COpenDL_DemoDoc::~COpenDL_DemoDoc()
{
}

BOOL COpenDL_DemoDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COpenDL_DemoDoc ���л�

void COpenDL_DemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// COpenDL_DemoDoc ���

#ifdef _DEBUG
void COpenDL_DemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenDL_DemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COpenDL_DemoDoc ����
