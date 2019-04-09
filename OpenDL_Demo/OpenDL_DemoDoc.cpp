// OpenDL_DemoDoc.cpp :  COpenDL_DemoDoc 类的实现
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


// COpenDL_DemoDoc 构造/析构

COpenDL_DemoDoc::COpenDL_DemoDoc()
{
	// TODO: 在此添加一次性构造代码

}

COpenDL_DemoDoc::~COpenDL_DemoDoc()
{
}

BOOL COpenDL_DemoDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COpenDL_DemoDoc 序列化

void COpenDL_DemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// COpenDL_DemoDoc 诊断

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


// COpenDL_DemoDoc 命令
