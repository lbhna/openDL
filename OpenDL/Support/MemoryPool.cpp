#include "StdAfx.h"
#include ".\memorypool.h"

CMemoryPoolManager		gm_theMemPool(10);

CMemoryPool::CMemoryPool(INT iMemBlockCount,INT iPerBlockSize)
{
	m_iBlockCount			=	iMemBlockCount;
	if(m_iBlockCount<=0)	
		m_iBlockCount		=	1;
	m_iPerBlockSize			=	iPerBlockSize;
	m_iMemPoolSize			=	m_iBlockCount*m_iPerBlockSize;					//内存池大小

	m_pMemPool				=	new BYTE[m_iMemPoolSize];							//内存池首地址
	m_pBlockArray			=	new _BlockHeader[m_iBlockCount];


	for(INT	i=0;i<m_iBlockCount;i++)
	{
		m_pBlockArray[i].bUsed			=FALSE;
		m_pBlockArray[i].wBlockCount	=0;
		m_pBlockArray[i].iSize			=0;
	}
	m_iLastFindBlockIndex	=0;
	m_pLastBlockAddr		=m_pMemPool+(m_iBlockCount-1)*m_iPerBlockSize;		//内存池尾地址
	m_iLeftBlockCount		=m_iBlockCount;				//内存池剩余块数
}

CMemoryPool::~CMemoryPool(void)
{
	if(m_pMemPool!=NULL)
	{
		delete []m_pMemPool;
		m_pMemPool=NULL;
	}

	if(m_pBlockArray!=NULL)
	{
		delete []m_pBlockArray;
		m_pBlockArray=NULL;
	}
	m_iLeftBlockCount=0;
}
//请求分配iSize大小的内存，返回地址
VOID*				CMemoryPool::Alloc(INT	IN iSize)
{
	INT		alloc_block_count=(iSize/m_iPerBlockSize);
	if(iSize % m_iPerBlockSize != 0)
		alloc_block_count +=1;

	VOID*			pAddr=NULL;
	INT				index=-1;
	if(m_iLeftBlockCount >= alloc_block_count)
		index=FindSequenceBlock(alloc_block_count);

	if(index < 0)
		return NULL;

	m_pBlockArray[index].bUsed			=TRUE;
	m_pBlockArray[index].wBlockCount	=alloc_block_count;
	m_pBlockArray[index].iSize			=iSize;

	for(INT i=1;i<alloc_block_count;i++)
	{
		m_pBlockArray[index+i].bUsed		=TRUE;
		m_pBlockArray[index+i].wBlockCount	=1;
		m_pBlockArray[index+i].iSize		=0;
	}

	pAddr=BlockIndexToAddr(index);
	m_iLeftBlockCount -=alloc_block_count;
	return pAddr;
}

//请求释放内存
BOOL				CMemoryPool::Free(VOID * IN pAddr)
{
	if(!IsValidAddr(pAddr))
		return FALSE;

	DWORD	index=AddrToBlockIndex(pAddr);
	m_iLeftBlockCount +=m_pBlockArray[index].wBlockCount;

	DWORD	count =m_pBlockArray[index].wBlockCount;
	for(DWORD i=0;i<count;i++)
	{
		m_pBlockArray[index+i].bUsed		=FALSE;
		m_pBlockArray[index+i].wBlockCount	=1;
		m_pBlockArray[index+i].iSize		=0;
	}
	return TRUE;
}

//查找连续的块，返回第一个块的索引
INT				CMemoryPool::FindSequenceBlock(INT IN iCount)
{
	INT		iStartIndex	=-1;
	INT		count		=0;
	INT		i			=0;
	for(i=m_iLastFindBlockIndex;i<m_iBlockCount;i++)
	{
		if(m_pBlockArray[i].bUsed)
		{
			iStartIndex=-1;
		}
		else
		{
			if(iStartIndex==-1)
			{
				iStartIndex=i;
				count=1;
			}
			else
			{
				count++;
			}
			if(count>=iCount)
			{
				m_iLastFindBlockIndex =iStartIndex+iCount;
				return iStartIndex;
			}
		}
	}

	iStartIndex	=-1;
	count		=0;
	for(i=0;i<m_iLastFindBlockIndex;i++)
	{
		if(m_pBlockArray[i].bUsed)
		{
			iStartIndex=-1;
		}
		else
		{
			if(iStartIndex==-1)
			{
				iStartIndex=i;
				count=1;
			}
			else
			{
				count++;
			}
			if(count>=iCount)
			{
				m_iLastFindBlockIndex =iStartIndex+iCount;
				return iStartIndex;
			}
		}
	}
	return -1;
}


inline BOOL			CMemoryPool::IsValidAddr(VOID*	pAddr)
{
	if(pAddr < m_pMemPool)
		return FALSE;
	if(pAddr > m_pLastBlockAddr)
		return FALSE;
	return TRUE;
}

inline VOID*		CMemoryPool::BlockIndexToAddr(INT	IN iIndex)
{
	if(iIndex>=m_iBlockCount)
		return NULL;
	return (m_pMemPool+(m_iPerBlockSize*iIndex));
}
inline INT		CMemoryPool::AddrToBlockIndex(VOID*	IN pAddr)
{
	return (INT)((DWORD)((BYTE*)pAddr-(BYTE*)m_pMemPool)/(DWORD)m_iPerBlockSize);
}
////////////////////////////////////////////////////////////////////////////////////
//请求分配iSize大小的内存，返回地址
VOID*	CMemoryPoolManager::Alloc(INT	IN iSize)
{
	if(iSize >= MEM_BLOCK_MIN_SIZE*MEM_BLOCK_COUNT)
	{//要分配的内存大于分页大小，直接用new分配
		return new BYTE[iSize];
	}
	EnterCriticalSection(&m_hSyncSection);

	VOID*			pMem	=NULL;
	_MEMP_NODE*		pNode	=m_pRoot;
	while(pNode != NULL)
	{
		pMem	=pNode->pPool->Alloc(iSize);
		if(pMem != NULL)
			break;
		pNode	=pNode->pNext;
	}

	if(pMem == NULL)
	{//分页不足，
		if(m_dwPageCount < m_dwMaxPageCount)
		{//如果还可以分配新的分页，则分配新的分页，并在分页中分配内存
			pNode =AddNewPage();
			if(pNode != NULL)
			{
				TRACE("#当前[%d]个分页不能满足需要，分配新的分页!\r\n",m_dwPageCount-1);

				pMem =pNode->pPool->Alloc(iSize);
			}
		}
	}
	LeaveCriticalSection(&m_hSyncSection);

	if(pMem == NULL)
	{//无法分配 ，直接用new分配内存
		pMem =new BYTE[iSize];

		TRACE("#内存池[当前 %d 个分页]不足，直接用new分配!\r\n",m_dwPageCount);
	}
	return pMem;
}

//请求释放内存
VOID	CMemoryPoolManager::Free(VOID * IN pAddr)
{
	if(pAddr == NULL)
		return;

	EnterCriticalSection(&m_hSyncSection);

	_MEMP_NODE*		pNode	=m_pRoot;
	while(pNode != NULL)
	{
		if(pNode->pPool->Free(pAddr))
		{
			pAddr =NULL;
			break;
		}
		pNode =pNode->pNext;
	}
	LeaveCriticalSection(&m_hSyncSection);

	//如果不属于任何分页，则是new出的内存，直接delete掉
	if(pAddr != NULL)
		delete []pAddr;
}

VOID	CMemoryPoolManager::Clear()
{
	EnterCriticalSection(&m_hSyncSection);
	if(m_pRoot != NULL)
	{
		_MEMP_NODE*		pNode =m_pRoot;
		while( pNode != NULL )
		{
			m_pRoot		=pNode->pNext;

			delete pNode->pPool;
			delete pNode;

			pNode =m_pRoot;
		}
	}
	m_dwPageCount =0;
	LeaveCriticalSection(&m_hSyncSection);
}
//获取内存的大小
INT	CMemoryPoolManager::GetSize(VOID* IN pAddr)
{
	INT		size =0;
	EnterCriticalSection(&m_hSyncSection);

	_MEMP_NODE*		pNode	=m_pRoot;
	while(pNode != NULL)
	{
		size =pNode->pPool->GetSize(pAddr);
		if(size >= 0)
			break;
		pNode =pNode->pNext;
	}
	LeaveCriticalSection(&m_hSyncSection);
	return size;
}

//获取实际分配的大小
INT	CMemoryPoolManager::GetRealSize(VOID* IN pAddr)
{
	INT		size =0;
	EnterCriticalSection(&m_hSyncSection);

	_MEMP_NODE*		pNode	=m_pRoot;
	while(pNode != NULL)
	{
		size =pNode->pPool->GetRealSize(pAddr);
		if(size >= 0)
			break;
		pNode =pNode->pNext;
	}
	LeaveCriticalSection(&m_hSyncSection);
	return size;
}


CMemoryPoolManager::_MEMP_NODE*		CMemoryPoolManager::AddNewPage()
{//添加一个新的分页

	_MEMP_NODE* pNewNode =new _MEMP_NODE;
	if(pNewNode == NULL)
		return NULL;
	pNewNode->pPool		 =new CMemoryPool();
	if(pNewNode->pPool == NULL)
	{
		delete pNewNode;
		return NULL;
	}

	if(m_pRoot != NULL)
		pNewNode->pNext =m_pRoot;
	else
		pNewNode->pNext =NULL;
	m_pRoot	=pNewNode;
	m_dwPageCount++;

	return m_pRoot;
}


