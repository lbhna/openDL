#include "StdAfx.h"
#include ".\odl_view.h"
#include "../Painter/ODL_Painter.h"


CODL_View::CODL_View(void)
{
	m_ViewType		=VIEW_GENERAL;
}

CODL_View::~CODL_View(void)
{
}

VOID		CODL_View::OnUpdate()
{
	CODL_CanvasBase*	pCanvas			=GetActiveCanvas();
	BOOL				bNeedDrawAll	=TRUE;
	if(pCanvas != NULL)
	{
		if(pCanvas->IsMaximized())
		{
			pCanvas->OnUpdate();
			bNeedDrawAll=FALSE;
		}
	}

	if(bNeedDrawAll)
	{

		switch(m_ViewStyle)
		{
		case OVS_TILES:
			{
				DWORD	endIndex =min(GetCount(),m_dwCurFirstCanvasIndex+m_dwRow*m_dwCol);
				for(LONG i=m_dwCurFirstCanvasIndex;i<endIndex;i++)
				{
					pCanvas		=(CODL_CanvasBase*)GetObj(i);
					if(pCanvas != NULL)
					{
						pCanvas->OnUpdate();
					}
				}
			}
			break;
		case OVS_CASCADE:
			{
				for(LONG i=0;i<GetCount();i++)
				{
					pCanvas		=(CODL_CanvasBase*)GetObj(i);
					if(pCanvas != NULL)
						pCanvas->OnUpdate();
				}
			}
			break;
		}

	}





}

