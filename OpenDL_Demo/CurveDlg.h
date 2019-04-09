#pragma once


// CCurveDlg dialog

class CCurveDlg : public CDialog
{
	DECLARE_DYNAMIC(CCurveDlg)
protected:
	CODL_View*					m_pView;
	CODLEx_Element_CurveBase*	m_pCurve;
	CMenu						m_theRButtonMenu;
public:
	CCurveDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCurveDlg();

// Dialog Data
	enum { IDD = IDD_CURVE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSavecanvasToFile();
	afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
