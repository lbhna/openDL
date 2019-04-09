#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\View\ODL_View.h
	created:	2012/02/21
	author:		LB
	purpose:	ODL  ”¿‡
\*********************************************************************/

#include "./ODL_Viewbase.h"

class ODL_EXPORT CODL_ViewBase;


class ODL_EXPORT CODL_View :
	public CODL_ViewBase
{
public:
	CODL_View(void);
	virtual ~CODL_View(void);
public:
	virtual VOID			OnUpdate();
};

