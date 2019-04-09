#pragma once
/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Base\ODL_ObjBase.h
	created:	2012/02/21
	author:		LB
	purpose:	ODL 对象基类
\*********************************************************************/
#include "GlobalDefine.h"

//----------------------------------------------------

class ODL_EXPORT CODL_ObjBase
{
protected:
	LONG				m_lRefCount;
	LONG				m_lObjListIndex;

	UINT_PTR			m_UserData;
public:
	CODL_ObjBase(void);
	virtual ~CODL_ObjBase(void);
public:
	VOID				SetUserData(UINT_PTR IN userData){m_UserData=userData;}
	UINT_PTR			GetUserData(){return m_UserData;}
	LONG				AddRef();
	LONG				Release();
	LONG				GetRefCount();
public:
	LONG				GetObjListIndex(){return m_lObjListIndex;}
	VOID				SetObjListIndex(LONG lIndex){m_lObjListIndex =lIndex;}
public:
	void*				operator new(size_t sz, const char* file, int line);
	void*				operator new(size_t sz, const char* file, int line, const char* func);
	void*				operator new(size_t sz);
	void*				operator new(size_t sz, void* ptr);
	void*				operator new[] ( size_t sz, const char* file, int line);
	void*				operator new[] ( size_t sz, const char* file, int line, const char* func );
	void*				operator new[] ( size_t sz );
	void				operator delete( void* ptr );
	void				operator delete( void* ptr, void* );
	void				operator delete( void* ptr, const char* , int);
	void				operator delete( void* ptr, const char* , int , const char*  );
	void				operator delete[] ( void* ptr );
	void				operator delete[] ( void* ptr, const char* , int);
	void				operator delete[] ( void* ptr, const char* , int , const char*  );

public:
	BOOL				IsKeyHoldPress(INT IN nKeyCode);




};

