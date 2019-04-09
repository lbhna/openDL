#include "StdAfx.h"
#include ".\memorypool.h"

CMemoryPoolManager		gm_theMemPool(10);

CMemoryPool::CMemoryPool(INT iMemBlockCount,INT iPerBlockSize)
{
	m_iBlockCount			=	iMemBlockCount;
	if(m_iBlockCount<=0)	
		m_iBlockCount		=	1;
	m_iPerBlockSize			=	iPerBlockSize;
	m_iMemPoolSize			=	m_iBlockCount*m_iPerBlockSize;					//�ڴ�ش�С

	m_pMemPool				=	new BYTE[m_iMemPoolSize];							//�ڴ���׵�ַ
	m_pBlockArray			=	new _BlockHeader[m_iBlockCount];


	for(INT	i=0;i<m_iBlockCount;i++)
	{
		m_pBlockArray[i].bUsed			=FALSE;
		m_pBlockArray[i].wBlockCount	=0;
		m_pBlockArray[i].iSize			=0;
	}
	m_iLastFindBlockIndex	=0;
	m_pLastBlockAddr		=m_pMemPool+(m_iBlockCount-1)*m_iPerBlockSize;		//�ڴ��β��ַ
	m_iLeftBlockCount		=m_iBlockCount;				//�ڴ��ʣ�����
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
//�������iSize��С���ڴ棬���ص�ַ
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

//�����ͷ��ڴ�
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

//���������Ŀ飬���ص�һ���������
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
//�������iSize��С���ڴ棬���ص�ַ
VOID*	CMemoryPoolManager::Alloc(INT	IN iSize)
{
	if(iSize >= MEM_BLOCK_MIN_SIZE*MEM_BLOCK_COUNT)
	{//Ҫ������ڴ���ڷ�ҳ��С��ֱ����new����
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
	{//��ҳ���㣬
		if(m_dwPageCount < m_dwMaxPageCount)
		{//��������Է����µķ�ҳ��������µķ�ҳ�����ڷ�ҳ�з����ڴ�
			pNode =AddNewPage();
			if(pNode != NULL)
			{
				TRACE("#��ǰ[%d]����ҳ����������Ҫ�������µķ�ҳ!\r\n",m_dwPageCount-1);

				pMem =pNode->pPool->Alloc(iSize);
			}
		}
	}
	LeaveCriticalSection(&m_hSyncSection);

	if(pMem == NULL)
	{//�޷����� ��ֱ����new�����ڴ�
		pMem =new BYTE[iSize];

		TRACE("#�ڴ��[��ǰ %d ����ҳ]���㣬ֱ����new����!\r\n",m_dwPageCount);
	}
	return pMem;
}

//�����ͷ��ڴ�
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

	//����������κη�ҳ������new�����ڴ棬ֱ��delete��
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
//��ȡ�ڴ�Ĵ�С
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

//��ȡʵ�ʷ���Ĵ�С
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
{//���һ���µķ�ҳ

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


