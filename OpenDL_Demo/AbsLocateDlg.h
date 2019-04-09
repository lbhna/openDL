#if !defined(AFX_ABSLOCATEDLG_H__05D1675F_909B_436A_82C8_651D8E2DC35B__INCLUDED_)
#define AFX_ABSLOCATEDLG_H__05D1675F_909B_436A_82C8_651D8E2DC35B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AbsLocateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbsLocateDlg dialog

class CAbsLocateDlg : public CDialog
{
// Construction
public:
	float	m_fXValue;
	CAbsLocateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAbsLocateDlg)
	enum { IDD = IDD_ABS_LOCATE_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbsLocateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAbsLocateDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABSLOCATEDLG_H__05D1675F_909B_436A_82C8_651D8E2DC35B__INCLUDED_)
