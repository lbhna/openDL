#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Base\ODL_ObjListBase.h
	created:	2012/02/22
	author:		LB
	purpose:	¡¥±Ì¿‡
\*********************************************************************/

#include "./ODL_ObjBase.h"


class ODL_EXPORT CODL_ObjListBase :
	public CODL_ObjBase
{
public:
	static LONG		m_lOverflowIncreaseStep;
protected:
	LONG			m_lMaxSize;
	LONG			m_lCount;
	CODL_ObjBase**	m_ppObj;

public:
	CODL_ObjListBase(void);
	virtual ~CODL_ObjListBase(void);

public:
	LONG			GetCount();
	VOID			Clear();

	CODL_ObjBase*	GetObj(LONG IN lIndex);
	CODL_ObjBase*	operator[](LONG IN lIndex){return GetObj(lIndex);}

	LONG			FindObj(CODL_ObjBase* IN pObj);
	BOOL			DelObj(LONG IN lIndex);
	BOOL			DelObj(CODL_ObjBase* IN pObj);
	VOID			AddObj(CODL_ObjBase* IN pObj);
	VOID			InsertObj(LONG IN lInsertBefore,CODL_ObjBase* IN pObj);

	BOOL			ChangeObject(LONG IN lIndex,CODL_ObjBase* IN pObj);

	BOOL			Swap(LONG IN lIndex1,LONG IN lIndex2);
	BOOL			Swap(CODL_ObjBase* IN pObj1,CODL_ObjBase* IN pObj2);

protected:
	VOID			OverflowCheck(LONG IN lStep=1);


};

