#pragma once

/*====================================================================\
		#创建日期:	2015/02/06
		#文件名  :	ODLEx_Element_PictureButton
		#作者    :	LBHNA   
		#说明    :	图片按钮类
\====================================================================*/


#include "./ODLEx_Element_Picture.h"

typedef ODLEX_EXPORT enum
{
	ODL_PBS_NORMAL			=0,	//正常状态
	ODL_PBS_ACTIVE			=1,	//鼠标按下状态
	ODL_PBS_FOCUS			=2,	//获取鼠标焦点
	ODL_PBS_GRAY			=3,	//禁用状态
	ODL_PBS_CHECKED			=4,	//选中状态

	ODL_PBS_FORCE_DWORD		=0x7FFFFFFF,
}ODL_PBSTATUS;
class ODLEX_EXPORT CODLEx_Element_PictureButton:
	public CODLEx_Element_Picture
{
protected:
	CODL_Image*					m_pActiveImage;	//鼠标按下状态
	CODL_Image*					m_pNormalImage;	//正常状态
	CODL_Image*					m_pFocusImage;	//获取焦点状态
	CODL_Image*					m_pGrayImage;		//禁用状态
	CODL_Image*					m_pCheckedImage;	//选中状态
protected:
	ODL_PBSTATUS				m_Status;
	BTN_CLICKED_CALLBACK		m_pClickedCallbackFunction;
	DWORD_PTR					m_CallbackUserData;

	BOOL						m_bMouseOver;
	BOOL						m_bPushed;
	BOOL						m_bChecked;
	BOOL						m_bEnableChecked;
	ODL_PBSTATUS				m_oldStatus;

public:
	CODLEx_Element_PictureButton(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_PictureButton();

public:
	ODL_PBSTATUS	GetStatus();
	VOID			SetStatus(ODL_PBSTATUS IN status);
	VOID			EnableChecked(BOOL IN bEnable);
	BOOL			IsEnableChecked();

	VOID			SetClickedCallback(BTN_CLICKED_CALLBACK IN callbackFunction,DWORD_PTR IN UserData=0);

	BOOL			SetNormalImage(LPCSTR IN pFileName);
	BOOL			SetNormalImage(LPVOID IN pImageData,DWORD IN dwDataSize);
	BOOL			SetActiveImage(LPCSTR IN pFileName);
	BOOL			SetActiveImage(LPVOID IN pImageData,DWORD IN dwDataSize);
	BOOL			SetFocusImage(LPCSTR IN pFileName);
	BOOL			SetFocusImage(LPVOID IN pImageData,DWORD IN dwDataSize);
	BOOL			SetGrayImage(LPCSTR IN pFileName);
	BOOL			SetGrayImage(LPVOID IN pImageData,DWORD IN dwDataSize);
	BOOL			SetCheckedImage(LPCSTR IN pFileName);
	BOOL			SetCheckedImage(LPVOID IN pImageData,DWORD IN dwDataSize);

public:
	virtual BOOL	OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint);
	virtual BOOL	OnClicked();
	virtual VOID	OnMouseOver();
	virtual VOID	OnMouseOut();
};