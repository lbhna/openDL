#pragma once
/********************************************************************\
	filename: 	MemoryPool.h  
	author:		LB                               
	created:	2009-4-30
    purpose:    �ڴ�ع�����
	
	�Ҳ��۲��������Ƭ���ڴ�й©�������ԣ��ڶ�һ��������䡢ɾ��100���ʱ
	���ڴ�رȳ����new��delete��4~8��
	
\********************************************************************/

#define ENABLE_USE_MEM_POOL			//������壬������ʹ���ڴ��

//--------------------------------------------------------------------

#define	MEM_BLOCK_MIN_SIZE			256			//�ڴ����С��С

#ifdef ENABLE_USE_MEM_POOL
	#include <new.h>
	#define MEM_BLOCK_COUNT			10240		//�ڴ�ؿ���
#else
	#define MEM_BLOCK_COUNT			1			//�ڴ�ؿ���
#endif

class CMemoryPool
{
private:
	//�ڴ�ֿ�ͷ
	struct _BlockHeader
	{
		WORD	bUsed;			//�Ƿ�ռ��
		WORD	wBlockCount;	//�������ٿ�
		INT		iSize;			//�������Ĵ�С
	};
	BYTE*				m_pMemPool;			//�ڴ���׵�ַ
	BYTE*				m_pLastBlockAddr;	//�ڴ��β��ַ
	INT					m_iMemPoolSize;		//�ڴ�ش�С
	_BlockHeader*		m_pBlockArray;		//�ڴ��ӳ���
	INT					m_iBlockCount;		//�ڴ������
	INT					m_iLastFindBlockIndex;
	INT					m_iLeftBlockCount;
	INT					m_iPerBlockSize;	//ÿ���ڴ��Ĵ�С

public:
	CMemoryPool(INT iMemBlockCount = MEM_BLOCK_COUNT,INT iPerBlockSize = MEM_BLOCK_MIN_SIZE);	
	virtual ~CMemoryPool(void);
public:

	//�������iSize��С���ڴ棬���ص�ַ
	VOID*					Alloc(INT	IN iSize);		
	
	//�����ͷ��ڴ�
	BOOL					Free(VOID * IN pAddr);			

	//��ȡ�ڴ�Ĵ�С
	INT						GetSize(VOID* IN pAddr)
	{
		if(!IsValidAddr(pAddr))
			return -1;
		
		INT	size=m_pBlockArray[AddrToBlockIndex(pAddr)].iSize;
		return size;
	}

	//��ȡʵ�ʷ���Ĵ�С
	INT					GetRealSize(VOID* IN pAddr)
	{
		if(!IsValidAddr(pAddr))
			return -1;
		
		INT	size=m_pBlockArray[AddrToBlockIndex(pAddr)].wBlockCount*m_iPerBlockSize;
		return size;
	}

private:
	BOOL			IsValidAddr(VOID* IN 	pAddr);
	//���������Ŀ飬���ص�һ���������
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
	DWORD				m_dwPageCount;		//��ǰ��ҳ����
	DWORD				m_dwMaxPageCount;	//�������ķ�ҳ����
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
	//�������iSize��С���ڴ棬���ص�ַ
	VOID*					Alloc(INT	IN iSize);
	//�����ͷ��ڴ�
	VOID					Free(VOID * IN pAddr);
	//��������ڴ�
	VOID					Clear();
	//��ȡ�ڴ�Ĵ�С
	INT						GetSize(VOID* IN pAddr);
	//��ȡʵ�ʷ���Ĵ�С
	INT						GetRealSize(VOID* IN pAddr);
protected:
	_MEMP_NODE*				AddNewPage();

};

//------------------------------------------------------------------------
extern			CMemoryPoolManager				gm_theMemPool;

#ifdef ENABLE_USE_MEM_POOL//����ʹ���ڴ��

	#define			LB_ALLOC(size)			gm_theMemPool.Alloc(size);
	#define			LB_FREE(addr)			{gm_theMemPool.Free(addr);addr=NULL;}
	#define			LB_SIZE(addr)			gm_theMemPool.GetSize(addr);
	#define			LB_REALSIZE(addr)		gm_theMemPool.GetRealSize(addr);


	//ʹ�����к�ʱ����ע�͵�VC��new�ĺ��ض���.���£�
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
	//��ֹʹ���ڴ��
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
