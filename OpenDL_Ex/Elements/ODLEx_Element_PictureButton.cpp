#include "stdafx.h"
#include "./ODLEx_Element_PictureButton.h"



CODLEx_Element_PictureButton::CODLEx_Element_PictureButton(CODL_CanvasBase* IN pCanvas):
CODLEx_Element_Picture(pCanvas)
{
	m_Type						=ODL_ELEMENT_PICTURE_BUTTON;
	m_pClickedCallbackFunction	=NULL;
	m_CallbackUserData			=0;

	m_pActiveImage				=NULL;	
	m_pNormalImage				=NULL;	
	m_pFocusImage				=NULL;	
	m_pGrayImage				=NULL;		
	m_pGrayImage				=NULL;		
	m_pCheckedImage				=NULL;	
	m_bMouseOver				=FALSE;
	m_Status					=ODL_PBS_NORMAL;
	m_bPushed					=FALSE;
	m_bChecked					=FALSE;
	m_bEnableChecked			=FALSE;
	m_oldStatus					=ODL_PBS_NORMAL;

}
CODLEx_Element_PictureButton::~CODLEx_Element_PictureButton()
{
	ODL_SafeRelease(m_pActiveImage	);
	ODL_SafeRelease(m_pNormalImage	);
	ODL_SafeRelease(m_pFocusImage	);
	ODL_SafeRelease(m_pGrayImage	);
	ODL_SafeRelease(m_pGrayImage	);
	ODL_SafeRelease(m_pCheckedImage );
}
ODL_PBSTATUS	CODLEx_Element_PictureButton::GetStatus()
{
	return m_Status;
}
BOOL			CODLEx_Element_PictureButton::SetNormalImage(LPCSTR IN pFileName)
{
	ODL_SafeRelease(m_pNormalImage	);
	m_pNormalImage	=new CODL_Image();
	if(!m_pNormalImage->Load(pFileName))
	{
		ODL_SafeRelease(m_pNormalImage);
		return FALSE;
	}
	SetImage(m_pNormalImage);
	return TRUE;
}
BOOL			CODLEx_Element_PictureButton::SetNormalImage(LPVOID IN pImageData,DWORD IN dwDataSize)
{
	ODL_SafeRelease(m_pNormalImage	);
	m_pNormalImage	=new CODL_Image();
	if(!m_pNormalImage->Load(pImageData,dwDataSize))
	{
		ODL_SafeRelease(m_pNormalImage);
		return FALSE;
	}
	SetImage(m_pNormalImage);
	return TRUE;
}
BOOL			CODLEx_Element_PictureButton::SetActiveImage(LPCSTR IN pFileName)
{
	ODL_SafeRelease(m_pActiveImage	);
	m_pActiveImage	=new CODL_Image();
	if(!m_pActiveImage->Load(pFileName))
	{
		ODL_SafeRelease(m_pActiveImage);
		return FALSE;
	}
	return TRUE;
}
BOOL			CODLEx_Element_PictureButton::SetActiveImage(LPVOID IN pImageData,DWORD IN dwDataSize)
{
	ODL_SafeRelease(m_pActiveImage	);
	m_pActiveImage	=new CODL_Image();
	if(!m_pActiveImage->Load(pImageData,dwDataSize))
	{
		ODL_SafeRelease(m_pActiveImage);
		return FALSE;
	}
	return TRUE;

}
BOOL			CODLEx_Element_PictureButton::SetFocusImage(LPCSTR IN pFileName)
{
	ODL_SafeRelease(m_pFocusImage	);
	m_pFocusImage	=new CODL_Image();
	if(!m_pFocusImage->Load(pFileName))
	{
		ODL_SafeRelease(m_pFocusImage);
		return FALSE;
	}
	return TRUE;
}
BOOL			CODLEx_Element_PictureButton::SetFocusImage(LPVOID IN pImageData,DWORD IN dwDataSize)
{
	ODL_SafeRelease(m_pFocusImage	);
	m_pFocusImage	=new CODL_Image();
	if(!m_pFocusImage->Load(pImageData,dwDataSize))
	{
		ODL_SafeRelease(m_pFocusImage);
		return FALSE;
	}
	return TRUE;

}
BOOL			CODLEx_Element_PictureButton::SetGrayImage(LPCSTR IN pFileName)
{
	ODL_SafeRelease(m_pGrayImage	);
	m_pGrayImage	=new CODL_Image();
	if(!m_pGrayImage->Load(pFileName))
	{
		ODL_SafeRelease(m_pGrayImage);
		return FALSE;
	}
	return TRUE;
}
BOOL			CODLEx_Element_PictureButton::SetGrayImage(LPVOID IN pImageData,DWORD IN dwDataSize)
{
	ODL_SafeRelease(m_pGrayImage	);
	m_pGrayImage	=new CODL_Image();
	if(!m_pGrayImage->Load(pImageData,dwDataSize))
	{
		ODL_SafeRelease(m_pGrayImage);
		return FALSE;
	}
	return TRUE;

}
BOOL			CODLEx_Element_PictureButton::SetCheckedImage(LPCSTR IN pFileName)
{
	ODL_SafeRelease(m_pCheckedImage	);
	m_pCheckedImage	=new CODL_Image();
	if(!m_pCheckedImage->Load(pFileName))
	{
		ODL_SafeRelease(m_pCheckedImage);
		return FALSE;
	}
	return TRUE;
}
BOOL			CODLEx_Element_PictureButton::SetCheckedImage(LPVOID IN pImageData,DWORD IN dwDataSize)
{
	ODL_SafeRelease(m_pCheckedImage	);
	m_pCheckedImage	=new CODL_Image();
	if(!m_pCheckedImage->Load(pImageData,dwDataSize))
	{
		ODL_SafeRelease(m_pCheckedImage);
		return FALSE;
	}
	return TRUE;

}

VOID		CODLEx_Element_PictureButton::SetStatus(ODL_PBSTATUS IN status)
{
	if(m_Status	==status)
		return;
	m_Status	=status;
	switch(m_Status)
	{
	case ODL_PBS_NORMAL:
		{
			SetImage(m_pNormalImage);
		}
		break;
	case ODL_PBS_ACTIVE:
		{
			if(m_pActiveImage != NULL)
				SetImage(m_pActiveImage);
		}
		break;
	case ODL_PBS_FOCUS:
		{
			if(m_pFocusImage != NULL)
				SetImage(m_pFocusImage);
		}
		break;
	case ODL_PBS_GRAY:
		{
			if(m_pGrayImage != NULL)
				SetImage(m_pGrayImage);
		}
		break;
	case ODL_PBS_CHECKED:
		{
			if(m_pCheckedImage != NULL)
				SetImage(m_pCheckedImage);
		}
		break;
	default:
		{
			SetImage(m_pNormalImage);
		}
		break;
	}
	Invalidate(TRUE);
}
VOID		CODLEx_Element_PictureButton::EnableChecked(BOOL IN bEnable)
{
	m_bEnableChecked	=bEnable;
}
BOOL		CODLEx_Element_PictureButton::IsEnableChecked()
{
	return m_bEnableChecked;
}

BOOL		CODLEx_Element_PictureButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult,POINT* pPoint)
{
	if(m_Status == ODL_PBS_GRAY)
		return FALSE;
	if(!IsControlSwitchKeyPressed())
	{
		switch(message)
		{
		case WM_LBUTTONDOWN:
			{
				if(PtInElement(*pPoint))
				{
					m_bPushed =TRUE;
					m_oldStatus	=m_Status;
					SetStatus(ODL_PBS_ACTIVE);
					Invalidate(TRUE);
					return TRUE;
				}
			}
			break;
		case WM_LBUTTONUP:
			{
				if(PtInElement(*pPoint) && m_bPushed)
				{
					m_bPushed =FALSE;
					SetStatus(m_oldStatus);
					Invalidate(TRUE);
					return OnClicked();
				}
			}
			break;
		case WM_MOUSEMOVE:
			{
				if(!PtInElement(*pPoint))
				{
					if(m_bMouseOver)
					{
						m_bMouseOver =FALSE;
						OnMouseOut();
					}
					if(m_bPushed)
					{
						m_bPushed =FALSE;
						Invalidate(TRUE);
					}
				}
				else
				{
					if(!m_bMouseOver)
					{
						m_bMouseOver =TRUE;
						OnMouseOver();
					}
				}
			}
			break;
		}
	}
	return CODLEx_Element_Picture::OnWndMsg(message,wParam,lParam,pResult,pPoint);
}
VOID		CODLEx_Element_PictureButton::SetClickedCallback(BTN_CLICKED_CALLBACK IN callbackFunction,DWORD_PTR IN UserData)
{
	m_pClickedCallbackFunction	=callbackFunction;
	m_CallbackUserData			=UserData;
}
BOOL	CODLEx_Element_PictureButton::OnClicked()
{
	if(m_bEnableChecked)
	{
		m_bChecked =!m_bChecked;
		if(m_pCheckedImage != NULL)
		{
			if(m_bChecked)
				SetImage(m_pCheckedImage);
		}
	}

	if(m_pClickedCallbackFunction != NULL)
	{
		m_pClickedCallbackFunction(GetID(),m_CallbackUserData);
	}
	if(m_pListener != NULL)
	{
		m_pListener->OnElement_Clicked(this);
	}
	return TRUE;
}
VOID	CODLEx_Element_PictureButton::OnMouseOver()
{
	CODLEx_Element_Picture::OnMouseOver();
	if(m_bChecked && m_pCheckedImage != NULL)
		return;
	SetStatus(ODL_PBS_FOCUS);
}
VOID	CODLEx_Element_PictureButton::OnMouseOut()
{
	CODLEx_Element_Picture::OnMouseOut();
	if(m_bChecked && m_pCheckedImage != NULL)
		return;
	SetStatus(ODL_PBS_NORMAL);
}

