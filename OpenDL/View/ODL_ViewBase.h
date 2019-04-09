#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\View\ODL_ViewBase.h
	created:	2012/02/21
	author:		LB
	purpose:	ODL �ӻ��� һ��������N�黭��
\*********************************************************************/
#include "../Base/ODL_ObjListBase.h"
#include "../Base/ODL_Listener.h"
#include "../Resource/ODL_ResourceManager.h"
#include "../Canvas/ODL_CanvasBase.h"


class ODL_EXPORT CODL_CanvasBase;
class ODL_EXPORT CODL_Painter;


typedef ODL_EXPORT enum
{
	OVS_TILES			=0,		//ƽ��
	OVS_CASCADE			=1,		//���


	OVS_FORCE_DWORD		=0x7fffffff,
}ODL_VIEW_STYLE;


class ODL_EXPORT CODL_ViewBase :
	public CODL_ObjListBase
{
protected:
	HWND					m_hDeviceWnd;				//�豸������
	VIEW_TYPE				m_ViewType;					//������
	CODL_Painter*			m_pPainter;					//����
	CODL_Listener*			m_pListener;
	COLORREF				m_BkColor;					//����ɫ
	RECT					m_PaintRect;

	DWORD					m_dwRow;
	DWORD					m_dwCol;
	DWORD					m_dwCurFirstCanvasIndex;
	CODL_CanvasBase*		m_pCurActiveCanvas;			//��ǰ����Ļ���

	DWORD					m_dwCanvasMarginSpace;


	ODL_VIEW_STYLE			m_ViewStyle;
protected:
	CODL_ResourceManager*	m_pResourceManager;			//��Դ����������

protected:
	BOOL					m_bDraging;				
	POINT					m_DragOffset;
	BOOL					m_bDragingChangeSize;		//�϶��ı��С
protected:
	WNDPROC 				m_OldWndProc;

public:
	CODL_ViewBase(void);
	virtual ~CODL_ViewBase(void);
public:

	virtual INT				Create(	HWND		IN hDeviceWnd,
									COLORREF	IN BkColor);
	virtual INT				Create(	HWND		IN hDeviceWnd,
									RECT*		IN pPaintRect,
									BOOL		IN bFixedSize,
									COLORREF	IN BkColor);
	virtual INT				Create(	HDC			IN hDC,
									HWND		IN hEventWnd,
									COLORREF	IN BkColor);
	virtual INT				Create(	HDC			IN hDC,
									HWND		IN hEventWnd,
									RECT*		IN pPaintRect,
									BOOL		IN bFixedSize,
									COLORREF	IN BkColor);

	virtual VOID			SetPaintRect(RECT* IN pPaintRect);

	virtual VOID			Update();
	virtual BOOL			OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL			SetCanvasLayout(DWORD IN dwRow,DWORD IN dwCol);
	virtual BOOL			LayoutCanvas(BOOL IN bViewStyleChanged=FALSE);//���·ֲ�����
	virtual VOID			Invalidate();
	virtual BOOL			SaveToBmpFile(LPCSTR IN pFileName);
	virtual BOOL			SaveToClipboard();
public:
	CODL_Painter*			GetPainter(){return m_pPainter;}
	CODL_ResourceManager*	GetResourceManager(){return m_pResourceManager;}
	VIEW_TYPE				GetViewType(){return m_ViewType;}
	COLORREF				GetBackColor(){return m_BkColor;}
	VOID					SetBackColor(COLORREF IN bkClr){m_BkColor=bkClr;}
	RECT*					GetPaintRect(){return &m_PaintRect;}
	HWND					GetDeviceWnd(){return m_hDeviceWnd;}
	ODL_VIEW_STYLE			GetViewStyle(){return m_ViewStyle;}
	VOID					SetViewStyle(ODL_VIEW_STYLE IN style);
	VOID					GetCanvasLayout(DWORD& OUT dwRow,DWORD& OUT dwCol);
	BOOL					PageDown();
	BOOL					PageUp();

	CODL_CanvasBase*		GetActiveCanvas();
	VOID					SetActiveCanvas(CODL_CanvasBase* IN pCanvas);
	CODL_CanvasBase*		PointSelectCanvas(POINT IN pt);


	CODL_CanvasBase*		AddNewCanvas(LPCSTR IN pName);

	CODL_CanvasBase*		GetCanvasByName(LPCSTR IN pName);
	BOOL					AddCanvas(CODL_CanvasBase* IN pCanvas);

	DWORD					GetCanvasMargin(){return m_dwCanvasMarginSpace;}
	VOID					SetCanvasMargin(DWORD IN dwMargin){m_dwCanvasMarginSpace=dwMargin;LayoutCanvas();}

	VOID					SetCanvasTopLayer(CODL_CanvasBase* IN pCanvas);
	VOID					SetListener(CODL_Listener* IN pListener);
protected:
	virtual VOID			OnUpdate()=0;

protected:
	virtual VOID			OnKeyDown(WPARAM IN wp,LPARAM IN lp);
	virtual VOID			OnLButtonDown(WPARAM IN wp,LPARAM IN lp);
	virtual VOID			OnLButtonUp(WPARAM IN wp,LPARAM IN lp);
	virtual VOID			OnMouseMove(WPARAM IN wp,LPARAM IN lp);
	virtual VOID			OnEndDrag(POINT IN pt);
	virtual VOID			DrawDragFrame(POINT IN pt);

protected:
	BOOL					HookWndProc();
	VOID					UnhookWndProc();
	LRESULT					CallOldWndProc(
							HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam
							);
	static LRESULT CALLBACK dumpWndProc(
							HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam
							);
};
