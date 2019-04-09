#include "StdAfx.h"
#include ".\odl_objbase.h"


CODL_ObjBase::CODL_ObjBase(void)
{
	m_lRefCount			=1;
	m_lObjListIndex		=-1;
	m_UserData			=0;
}

CODL_ObjBase::~CODL_ObjBase(void)
{
}
inline LONG				CODL_ObjBase::AddRef()
{
	return (++m_lRefCount);
}
inline LONG				CODL_ObjBase::Release()
{
	--m_lRefCount;

	if(m_lRefCount <=0 )
		delete this;

	return m_lRefCount;
}
inline LONG				CODL_ObjBase::GetRefCount()
{
	return m_lRefCount;
}
void* CODL_ObjBase::operator new(size_t sz, const char* file, int line)
{
	return LB_ALLOC((INT)sz);
}
void* CODL_ObjBase::operator new(size_t sz, const char* file, int line, const char* func)
{
	return LB_ALLOC((INT)sz);
}
void* CODL_ObjBase::operator new(size_t sz)
{
	return LB_ALLOC((INT)sz);
}
void* CODL_ObjBase::operator new(size_t sz, void* ptr)
{
	(void) sz;
	return ptr;
}
void* CODL_ObjBase::operator new[] ( size_t sz, const char* file, int line)
{
	return LB_ALLOC((INT)sz);
}
void* CODL_ObjBase::operator new[] ( size_t sz, const char* file, int line, const char* func )
{
	return LB_ALLOC((INT)sz);
}
void* CODL_ObjBase::operator new[] ( size_t sz )
{
	return LB_ALLOC((INT)sz);
}
void CODL_ObjBase::operator delete( void* ptr )
{
	LB_FREE(ptr);
}
void CODL_ObjBase::operator delete( void* ptr, void* )
{
	LB_FREE(ptr);
}
void CODL_ObjBase::operator delete( void* ptr, const char* , int )
{
	LB_FREE(ptr);
}
void CODL_ObjBase::operator delete( void* ptr, const char* , int , const char*  )
{
	LB_FREE(ptr);
}
void CODL_ObjBase::operator delete[] ( void* ptr )
{
	LB_FREE(ptr);
}
void CODL_ObjBase::operator delete[] ( void* ptr, const char* , int)
{
	LB_FREE(ptr);
}
void CODL_ObjBase::operator delete[] ( void* ptr, const char* , int , const char*  )
{
	LB_FREE(ptr);
}
BOOL CODL_ObjBase::IsKeyHoldPress(INT IN nKeyCode)
{
	return ( ( GetKeyState(nKeyCode) & 0xff00 ) != 0);
}


