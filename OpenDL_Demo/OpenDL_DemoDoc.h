// OpenDL_DemoDoc.h :  COpenDL_DemoDoc ��Ľӿ�
//


#pragma once

class COpenDL_DemoDoc : public CDocument
{
protected: // �������л�����
	COpenDL_DemoDoc();
	DECLARE_DYNCREATE(COpenDL_DemoDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~COpenDL_DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


