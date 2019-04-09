#include "StdAfx.h"
#include ".\odl_objlistbase.h"



LONG	CODL_ObjListBase::m_lOverflowIncreaseStep		=16;
CODL_ObjListBase::CODL_ObjListBase(void)
{
	m_lMaxSize			=0;
	m_ppObj				=NULL;
	m_lCount			=0;
}

CODL_ObjListBase::~CODL_ObjListBase(void)
{
	Clear();
}
inline LONG			CODL_ObjListBase::GetCount()
{
	return m_lCount;
}
VOID			CODL_ObjListBase::Clear()
{
	for(LONG i=0;i<m_lCount;i++)
	{
		m_ppObj[i]->SetObjListIndex(-1);
		m_ppObj[i]->Release();
	}
	LB_FREE(m_ppObj);
	m_lCount	=0;
}
inline CODL_ObjBase*	CODL_ObjListBase::GetObj(LONG IN lIndex)
{
	if(lIndex < 0 || lIndex >= m_lCount || m_ppObj == NULL)
		return NULL;

	return m_ppObj[lIndex];
}
inline LONG			CODL_ObjListBase::FindObj(CODL_ObjBase* IN pObj)
{
	if(pObj == NULL)
		return -1;
	LONG lIndex =pObj->GetObjListIndex();
	if(lIndex < 0 || lIndex >= m_lCount)
		return -1;
	return lIndex;
}

inline BOOL			CODL_ObjListBase::DelObj(LONG IN lIndex)
{
	if(lIndex < 0 || lIndex >= m_lCount || m_ppObj == NULL)
		return FALSE;

	m_ppObj[lIndex]->SetObjListIndex(-1);
	m_ppObj[lIndex]->Release();

	--m_lCount;

	LONG i=0;
	for(i=lIndex;i<m_lCount;i++)
	{
		m_ppObj[i]=m_ppObj[i+1];
		m_ppObj[i]->SetObjListIndex(i);
	}
	m_ppObj[i]=0;

	return TRUE;
}

inline BOOL			CODL_ObjListBase::DelObj(CODL_ObjBase* IN pObj)
{
	return DelObj(FindObj(pObj));
}

inline VOID			CODL_ObjListBase::AddObj(CODL_ObjBase* IN pObj)
{
	if(pObj == NULL)
		return;
	OverflowCheck();
	m_ppObj[m_lCount]=pObj;
	pObj->SetObjListIndex(m_lCount);
	pObj->AddRef();
	m_lCount++;
}
VOID			CODL_ObjListBase::InsertObj(LONG IN lInsertBefore,CODL_ObjBase* IN pObj)
{
	if(pObj == NULL)
		return;
	OverflowCheck();
	LONG index =lInsertBefore;
	if(index<0)
		index=0;
	if(index>m_lCount)
		index=m_lCount;

	for(LONG i=m_lCount;i>index;i--)
	{
		m_ppObj[i] = m_ppObj[i-1];
	}

	m_ppObj[index]=pObj;
	pObj->SetObjListIndex(index);
	pObj->AddRef();
	m_lCount++;

}


BOOL			CODL_ObjListBase::ChangeObject(LONG IN lIndex,CODL_ObjBase* IN pObj)
{
	if(lIndex >= m_lCount || pObj == NULL)
		return FALSE;
	if(m_ppObj[lIndex] == pObj)
		return TRUE;
	m_ppObj[lIndex]->Release();
	m_ppObj[lIndex] =pObj;
	m_ppObj[lIndex]->AddRef();
	return TRUE;
}


BOOL			CODL_ObjListBase::Swap(LONG IN lIndex1,LONG IN lIndex2)
{
	if(lIndex1 <0 || lIndex1 >= m_lCount||
		lIndex2 <0 || lIndex2 >= m_lCount)
		return FALSE;

	CODL_ObjBase*	pTmp	=m_ppObj[lIndex1];

	m_ppObj[lIndex1]		=m_ppObj[lIndex2];
	m_ppObj[lIndex1]->SetObjListIndex(lIndex1);

	m_ppObj[lIndex2]		=pTmp;
	m_ppObj[lIndex2]->SetObjListIndex(lIndex2);

	return TRUE;
}

BOOL			CODL_ObjListBase::Swap(CODL_ObjBase* IN pObj1,CODL_ObjBase* IN pObj2)
{
	return Swap(FindObj(pObj1),FindObj(pObj2));
}

inline VOID			CODL_ObjListBase::OverflowCheck(LONG IN lStep)
{
	if( (m_lCount+lStep) >= m_lMaxSize || m_ppObj == NULL)
	{
		m_lMaxSize += max(lStep,CODL_ObjListBase::m_lOverflowIncreaseStep);

		CODL_ObjBase**	ppObj	= (CODL_ObjBase**)LB_ALLOC( sizeof(CODL_ObjBase*) * m_lMaxSize );

		LONG i=0;
		for( i=0;i<m_lCount;i++)
			ppObj[i] = m_ppObj[i];
		for(i=m_lCount;i<m_lMaxSize;i++)
			ppObj[i] = 0;

		LB_FREE(m_ppObj);
		m_ppObj		= ppObj;
	}

}


