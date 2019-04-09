// OpenDL_DemoView.h : COpenDL_DemoView ��Ľӿ�
//


#pragma once

#define		USERMSG_CANVAS			(WM_USER+1)	//�����Ļص���Ϣ


#include "CurveDlg.h"
class COpenDL_DemoView : public CView
{
protected: // �������л�����
	COpenDL_DemoView();
	DECLARE_DYNCREATE(COpenDL_DemoView)
	CCurveDlg*			m_pCurveDlg;
	CODL_View*			m_pODL_View;
	CMenu				m_theRButtonMenu;


	CODLEx_Element_TextArea* m_pText1;
	CODLEx_Element_CurveBase* m_pCurve1;
	CODLEx_Element_CurveBase* m_pCurve11;
	CODLEx_Element_CurveBase* m_pCurve12;
	CODLEx_Element_CurveBase* m_pCurve4;
	CODLEx_Element_Compass*	m_pCompass;
// ����
public:
	COpenDL_DemoDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// ʵ��
public:
	virtual ~COpenDL_DemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowCurve();
	afx_msg void OnShowCurveModal();
	afx_msg void OnSavecanvasToFile();
	afx_msg void OnSavecanvasToClipboard();
	afx_msg void OnSaveviewToFile();
	afx_msg void OnSaveviewToClipboard();
	afx_msg void OnAbsLocate();
	afx_msg void OnShowHidePreview();
	afx_msg void OnUpdateShowHidePreview(CCmdUI *pCmdUI);
	afx_msg void OnCurveCleardata();
	afx_msg LRESULT OnCanvasCallbackMessage(WPARAM wp,LPARAM lp);
	afx_msg void OnSplitData();
};

#ifndef _DEBUG  // OpenDL_DemoView.cpp �ĵ��԰汾
inline COpenDL_DemoDoc* COpenDL_DemoView::GetDocument() const
   { return reinterpret_cast<COpenDL_DemoDoc*>(m_pDocument); }
#endif

