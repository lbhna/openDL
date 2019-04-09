#pragma once
/********************************************************************\
	filename: 	ODLEx_Element_AdjustLine.h
	created:	2014/10/28
	author:		LB
	purpose:	�ɵ�����������
\*********************************************************************/
#include "ODLEx_Element_CurveBase.h"

#define		AdjustPointAdd			0
#define		AdjustPointMove			1
#define		AdjustPointDelete		2
#define		AdjustPointSelect		3


#define		ADJUSTLINE_MSG		(CANVAS_CALLBACKMSG_USER+1)

struct		OLD_ADJUSTLINE_MSG
{
	DWORD			type;	//���涨��ļ�����Ϣ����
	DWORD			x;		//xֵ
	float			y;		//yֵ
	DWORD			ox;		//��xֵ,move��Ч
	DWORD			pLine;	//����ָ��
};

class ODLEX_EXPORT CODLEx_Element_AdjustLine:public CODL_ElementBase
{
protected:
	//��ͼ����
	CODL_Pen*					m_pLinePen;
	CODL_Brush*					m_pSelectBrush;
	DWORD						m_dwPointRadius;	//
	CODL_Font*					m_pTextFont;
	DWORD						m_TextBkColor;
	DWORD						m_TextColor;

	//���ò���
	BOOL						m_bFilterLBDBLCLK;//���˵�˫���¼�
		 
	BOOL						m_bMinX;
	BOOL						m_bMaxX;
	BOOL						m_bMinY;
	BOOL						m_bMaxY;
	float						m_fMinX;
	float						m_fMaxX;
	float						m_fMaxY;
	float						m_fMinY;

	BOOL						m_bEnableClickAdd;		//�Զ��ӵ�
	BOOL						m_bLockFirstXatZero;	//�׵�Xʼ������0
	BOOL						m_bTrueFalseStyle;
	BOOL						m_bXinteger;
	BOOL						m_bEnable;	

	//��ʱ����
	INT							m_dwLastSelect;		//
	BOOL						m_bPressed;
	POINT						m_ptOffset;
	DWORD						m_dwBK_X;			//

public:
	CODLEx_Element_AdjustLine(CODL_CanvasBase* IN pCanvas,BOOL bLockFirstXatZero);
	virtual ~CODLEx_Element_AdjustLine();

public:
	VOID				SetColor(COLORREF IN clr);

	VOID				SetPointRadius(DWORD IN dwRadius);
	DWORD				GetPointRadius(){return m_dwPointRadius;}
	CODLEx_CurveData*	AddData(FLOAT IN x,FLOAT IN y);
	VOID				MoveDataX(FLOAT IN x,FLOAT newX,BOOL bNotify =FALSE);//ע��Խ��
	VOID				DeleteDataByX(DWORD X,BOOL bNotify = FALSE);
	CODLEx_CurveData*	GetCurveDataData(INT index);
	VOID				DeleteDataByIndex(INT index,BOOL bNotify = FALSE);
	VOID				CancelSelect(BOOL bNofity);
	//
	BOOL				HitTest(CPoint& pt);
	int					GetSelectIndex();
	BOOL				CanDelectSelect();
	BOOL				IsMovingPoint();

	//
	VOID				Clear();
	VOID				ClearMinMaxLimit();
	VOID				SetMinX(float fMinX);
	VOID				SetMaxX(float fMaxX);
	VOID				SetMinY(float fMinY);
	VOID				SetMaxY(float fMaxY);


	//����ӵ�
	VOID				EnableClickAdd(BOOL bEnable);	
	//��һ��x����0
	VOID				EnableFirstZeroLock(BOOL bEnable);
	//����˫���¼�
	void				EnableLBDClickFliter(BOOL bEnable);
	//Yֵֻ��0��1
	VOID				EnableTrueFalseStyle(BOOL bEnable);
	//X��ȡ����
	VOID				EnableXinteger(BOOL bEnable);

	//�����ܿ���
	VOID				EnableOperator(BOOL bEnable);

	//
	VOID				SetLineParameter(UINT IN nLineStyle,UINT IN nLineWidth,COLORREF IN LineColor);




protected:
	OLD_ADJUSTLINE_MSG	m_Msg,m_Msg2;
	CODL_ListT<POINT>			m_theDrawDataList;
	CODL_ListT<CODLEx_CurveData>m_theDataList;

	void				Init();
	BOOL				InSelect(POINT pt,CODLEx_CurveData*  pData,POINT& offset);
	RECT				GetDropPointRect(CODLEx_CurveData* pData);

	INT					AddValueAtPoint(POINT pt);

	BOOL				FormatX(float& x,int index,DWORD style);
	FLOAT				FormatY(float& y);
	BOOL				IsXinLimitRange(float x);
	
	int					XValueToCoordSpacce(float x);
	int					YValueToCoordSpacce(float y);
	float				CoordSpaceToXValue(int x);
	float				CoordSpaceToYValue(int y);
	void				PostUnselectMsg();
	VOID				PostSelectMsg();
	

protected:
	BOOL				OnLButtonDown(POINT pt);
	BOOL				OnLButtonUp();
	BOOL				OnMouseMove(POINT pt);
	BOOL				OnLButtonDBDown(POINT pt);
	BOOL				OnKeyDown(UINT message, WPARAM wParam, LPARAM lParam);

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
	virtual BOOL		OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
};










