#pragma once
/********************************************************************\
	filename: 	G:\LIBO\projects\OpenDL\OpenDL\ODL_Include.h
	created:	2012/02/21
	author:		LB
	purpose:	全局包含头文件
\*********************************************************************/

#include "./Base/GlobalDefine.h"
#include "./Base/ODL_Vector2f.h"
#include "./Base/ODL_ListT.h"
#include "./Base/ODL_Listener.h"
#include "./Base/ODL_DirtyRect.h"
#include "./Base/ODL_MemDC.h"
#include "./Base/ODL_Image.h"

#include "./Canvas/ODL_GDICanvas.h"

#include "./Tools/ODL_Tools.h"

#include "./Painter/ODL_Painter.h"
#include "./Elements/ODL_ElementBase.h"
#include "./Elements/ODL_OverlayElementBase.h"
#include "./Elements/ODL_LayerElementBase.h"
#include "./View/ODL_View.h"
#include "./Resource/ODL_ResourceManager.h"
#include "./Resource/ODL_ImageList.h"











#ifdef _DEBUG
	#pragma  comment(lib,"OpenDL_D.lib")
#else
	#pragma comment(lib,"OpenDL.lib")
#endif
