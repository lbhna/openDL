#pragma once
/*====================================================================\
		#创建日期:	2015/04/21
		#文件名  :	ODL_Listener
		#作者    :	LBHNA   
		#说明    :	回调类
\====================================================================*/



#include "./ODL_ObjBase.h"

class CODL_ElementBase;
class ODL_EXPORT CODL_Listener 
{
public:
	CODL_Listener();
	virtual ~CODL_Listener(void);
public:
	virtual VOID			OnView_StyleChanged(CODL_ObjBase* IN pView){}
public:
	virtual VOID			OnCanvas_ToTopLayer(CODL_ObjBase* IN pCanvas){}
	virtual VOID			OnCanvas_PosChanged(CODL_ObjBase* IN pCanvas){}
	virtual VOID			OnCanvas_SizeChanged(CODL_ObjBase* IN pCanvas){}
	virtual VOID			OnCanvas_Actived(CODL_ObjBase* IN pCanvas)	{}
	virtual VOID			OnCanvas_Deactived(CODL_ObjBase* IN pCanvas){}
	virtual VOID			OnCanvas_Swaped(CODL_ObjBase* IN pCanvas1,CODL_ObjBase* IN pCanvas2){}

public:
	virtual VOID			OnElement_Selected(CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_Unselected(CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_PosChanged(CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_SizeChanged(CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_Clicked(CODL_ElementBase* IN pElement){}

	virtual VOID			OnElement_ItemClicked(CODL_ElementBase* IN pContainer,CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_ItemSelected(CODL_ElementBase* IN pContainer,CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_ItemUnselected(CODL_ElementBase* IN pContainer,CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_ItemSizeChanged(CODL_ElementBase* IN pContainer,CODL_ElementBase* IN pElement){}
	virtual VOID			OnElement_ItemDeleted(CODL_ElementBase* IN pContainer,CODL_ElementBase* IN pElement){}

	virtual VOID			OnCoordinate_ZoomChanged(CODL_ElementBase* IN pElement){}
	virtual VOID			OnCoordinate_DragEnd(CODL_ElementBase* IN pElement){}
	virtual VOID			OnCoordinate_DiagramDragEnd(CODL_ElementBase* IN pElement){}
	virtual VOID			OnCoordinate_StatusChanged(CODL_ElementBase* IN pElement){}


};




