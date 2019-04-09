#pragma once
/********************************************************************\
	filename: 	MemoryPool.h  
	author:		LB                               
	created:	2009-4-30
    purpose:    内存池管理类
	
	且不论不会产生碎片和内存泄漏，经测试，在对一个对象分配、删除100万次时
	用内存池比常规的new和delete快4~8倍
	
\********************************************************************/

#define ENABLE_USE_MEM_POOL			//如果定义，则允许使用内存池

//--------------------------------------------------------------------

#define	MEM_BLOCK_MIN_SIZE			256			//内存块最小大小

#ifdef ENABLE_USE_MEM_POOL
	#include <new.h>
	#define MEM_BLOCK_COUNT			10240		//内存池块数
#else
	#define MEM_BLOCK_COUNT			1			//内存池块数
#endif

class CMemoryPool
{
private:
	//内存分块头
	struct _BlockHeader
	{
		WORD	bUsed;			//是否被占用
		WORD	wBlockCount;	//包含多少块
		INT		iSize;			//请求分配的大小
	};
	BYTE*				m_pMemPool;			//内存池首地址
	BYTE*				m_pLastBlockAddr;	//内存池尾地址
	INT					m_iMemPoolSize;		//内存池大小
	_BlockHeader*		m_pBlockArray;		//内存块映射表
	INT					m_iBlockCount;		//内存块数量
	INT					m_iLastFindBlockIndex;
	INT					m_iLeftBlockCount;
	INT					m_iPerBlockSize;	//每个内存块的大小

public:
	CMemoryPool(INT iMemBlockCount = MEM_BLOCK_COUNT,INT iPerBlockSize = MEM_BLOCK_MIN_SIZE);	
	virtual ~CMemoryPool(void);
public:

	//请求分配iSize大小的内存，返回地址
	VOID*					Alloc(INT	IN iSize);		
	
	//请求释放内存
	BOOL					Free(VOID * IN pAddr);			

	//获取内存的大小
	INT						GetSize(VOID* IN pAddr)
	{
		if(!IsValidAddr(pAddr))
			return -1;
		
		INT	size=m_pBlockArray[AddrToBlockIndex(pAddr)].iSize;
		return size;
	}

	//获取实际分配的大小
	INT					GetRealSize(VOID* IN pAddr)
	{
		if(!IsValidAddr(pAddr))
			return -1;
		
		INT	size=m_pBlockArray[AddrToBlockIndex(pAddr)].wBlockCount*m_iPerBlockSize;
		return size;
	}

private:
	BOOL			IsValidAddr(VOID* IN 	pAddr);
	//查找连续的块，返回第一个块的索引
	INT				FindSequenceBlock(INT IN iCount);
	VOID*			BlockIndexToAddr(INT	IN iIndex);
	INT				AddrToBlockIndex(VOID*	IN pAddr);				
};
class CMemoryPoolManager
{
	struct _MEMP_NODE
	{
		CMemoryPool*	pPool;
		_MEMP_NODE*		pNext;
	};
protected:
	_MEMP_NODE*			m_pRoot;
	DWORD				m_dwPageCount;		//当前分页数量
	DWORD				m_dwMaxPageCount;	//最多允许的分页数量
	CRITICAL_SECTION	m_hSyncSection;

public:
	CMemoryPoolManager(DWORD IN dwMaxPageCount)
	{
		m_pRoot			=new _MEMP_NODE;
		m_pRoot->pPool	=new CMemoryPool();	
		m_pRoot->pNext	=NULL;
		m_dwPageCount	=1;
		m_dwMaxPageCount=dwMaxPageCount;
		InitializeCriticalSection(&m_hSyncSection);

	}
	~CMemoryPoolManager()
	{
		Clear();
		DeleteCriticalSection(&m_hSyncSection);
	}

public:
	//请求分配iSize大小的内存，返回地址
	VOID*					Alloc(INT	IN iSize);
	//请求释放内存
	VOID					Free(VOID * IN pAddr);
	//清除所有内存
	VOID					Clear();
	//获取内存的大小
	INT						GetSize(VOID* IN pAddr);
	//获取实际分配的大小
	INT						GetRealSize(VOID* IN pAddr);
protected:
	_MEMP_NODE*				AddNewPage();

};

//------------------------------------------------------------------------
extern			CMemoryPoolManager				gm_theMemPool;

#ifdef ENABLE_USE_MEM_POOL//允许使用内存池

	#define			LB_ALLOC(size)			gm_theMemPool.Alloc(size);
	#define			LB_FREE(addr)			{gm_theMemPool.Free(addr);addr=NULL;}
	#define			LB_SIZE(addr)			gm_theMemPool.GetSize(addr);
	#define			LB_REALSIZE(addr)		gm_theMemPool.GetRealSize(addr);


	//使用下列宏时，请注释掉VC对new的宏重定义.如下：
	/***********************************************\
	
			//#ifdef _DEBUG
			//#define new DEBUG_NEW
			//#endif

	\************************************************/
	#define			LB_NEW0(object_pointer,class_name)								{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name();}
	#define			LB_NEW1(object_pointer,class_name,v1)							{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1);}
	#define			LB_NEW2(object_pointer,class_name,v1,v2)						{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2);}
	#define			LB_NEW3(object_pointer,class_name,v1,v2,v3)						{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3);}
	#define			LB_NEW4(object_pointer,class_name,v1,v2,v3,v4)					{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3,v4);}
	#define			LB_NEW5(object_pointer,class_name,v1,v2,v3,v4,v5)				{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3,v4,v5);}
	#define			LB_NEW6(object_pointer,class_name,v1,v2,v3,v4,v5,v6)			{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3,v4,v6);}
	#define			LB_NEW7(object_pointer,class_name,v1,v2,v3,v4,v5,v6,v7)			{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3,v4,v6,v7);}
	#define			LB_NEW8(object_pointer,class_name,v1,v2,v3,v4,v5,v6,v7,v8)		{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3,v4,v6,v7,v8);}
	#define			LB_NEW9(object_pointer,class_name,v1,v2,v3,v4,v5,v6,v7,v8,v9)	{void* pBuf=LB_ALLOC(sizeof(##class_name));object_pointer=new(pBuf)##class_name(v1,v2,v3,v4,v6,v7,v8,v9);}
	#define			LB_DELETE(object_pointer,class_name)							{if(gm_theMemPool.GetSize(object_pointer)==0){if(object_pointer!=NULL)delete object_pointer;}else{object_pointer->~##class_name();LB_FREE(object_pointer);}object_pointer=NULL;}

#else/////////////////////////////////////////////////////////////////
	//禁止使用内存池
	#define			LB_ALLOC(size)			new BYTE[size];
	#define			LB_FREE(addr)			{if(addr!=NULL){delete addr;addr=NULL;}}
	#define			LB_SIZE(addr)			sizeof(addr);
	#define			LB_REALSIZE(addr)		sizeof(addr);

	#define			LB_NEW0(object_pointer,class_name)								{object_pointer=new(##class_name)();}
	#define			LB_NEW1(object_pointer,class_name,v1)							{object_pointer=new(##class_name)(v1);}
	#define			LB_NEW2(object_pointer,class_name,v1,v2)						{object_pointer=new(##class_name)(v1,v2);}
	#define			LB_NEW3(object_pointer,class_name,v1,v2,v3)						{object_pointer=new(##class_name)(v1,v2,v3);}
	#define			LB_NEW4(object_pointer,class_name,v1,v2,v3,v4)					{object_pointer=new(##class_name)(v1,v2,v3,v4);}
	#define			LB_NEW5(object_pointer,class_name,v1,v2,v3,v4,v5)				{object_pointer=new(##class_name)(v1,v2,v3,v4,v5);}
	#define			LB_NEW6(object_pointer,class_name,v1,v2,v3,v4,v5,v6)			{object_pointer=new(##class_name)(v1,v2,v3,v4,v6);}
	#define			LB_NEW7(object_pointer,class_name,v1,v2,v3,v4,v5,v6,v7)			{object_pointer=new(##class_name)(v1,v2,v3,v4,v6,v7);}
	#define			LB_NEW8(object_pointer,class_name,v1,v2,v3,v4,v5,v6,v7,v8)		{object_pointer=new(##class_name)(v1,v2,v3,v4,v6,v7,v8);}
	#define			LB_NEW9(object_pointer,class_name,v1,v2,v3,v4,v5,v6,v7,v8,v9)	{object_pointer=new(##class_name)(v1,v2,v3,v4,v6,v7,v8,v9);}
	#define			LB_DELETE(object_pointer,class_name)							{if(object_pointer!=NULL)delete object_pointer;object_pointer=NULL;}

#endif
//------------------------------------------------------------------------
