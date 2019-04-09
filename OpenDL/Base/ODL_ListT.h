#pragma once

/********************************************************************\
	filename: 	g:\Libo\projects\OpenDL\OpenDL\Base\ListTemplate.h
	created:	2012/03/13
	author:		LB
	purpose:	˫������ģ����
\*********************************************************************/

template<class T>
class CODL_ListT
{
private:
	class CListNode
	{
	public:
		CListNode	*pPrev;
		CListNode	*pNext;
		T			Data;
		CListNode()
		{
			pPrev	=NULL;
			pNext	=NULL;
		}
	};
	CListNode*			pHead;		//ͷָ��
	CListNode*			pTail;		//βָ��
	CRITICAL_SECTION	m_Section;	//�̷߳��ʻ�����
	DWORD				m_dwCount;
private:
	CListNode*			m_pLookatListHead;
	DWORD				m_dwLookatListCount;
	DWORD				m_dwLookatListMaxCount;

public:
	CODL_ListT()
	{
		InitializeCriticalSection(&m_Section);
		pHead		=NULL;
		pTail		=NULL;
		m_dwCount	=0;

		m_dwLookatListMaxCount	=100;
		m_dwLookatListCount		=0;
		m_pLookatListHead		=NULL;
	}
	~CODL_ListT()
	{
		DestroyList();
		DeleteCriticalSection(&m_Section);
	}
	void LOCK()
	{
		EnterCriticalSection(&m_Section);
	}
	void UNLOCK()
	{
		LeaveCriticalSection(&m_Section);
	}
public://����
	
	T *				AddTail(T *pData)
	{
		CListNode *pNewNode=AllocNode(pData);
		if(pNewNode==NULL)return NULL;
		//----------------------------------

		if(pHead==NULL)
		{//��һ���ڵ�
			pTail=pNewNode;
			pHead=pNewNode;
		}
		else
		{//��ӵ�β��
			pNewNode->pPrev=pTail;
			pTail->pNext=pNewNode;
			pTail=pNewNode;
		}
		
		m_dwCount ++;

		return &pNewNode->Data;
	}
	T*			AddHead(T *pData)//��������ͷ��
	{
		CListNode *pNewNode=AllocNode(pData);
		if(pNewNode==NULL)return NULL;
		//----------------------------------
		if(pTail==NULL)
		{//��һ���ڵ�
			pTail=pNewNode;
			pHead=pNewNode;
		}
		else
		{//��ӵ�ͷ��
			pNewNode->pNext=pHead;
			pHead->pPrev=pNewNode;
			pHead=pNewNode;
		}
	
		m_dwCount ++;

		return &pNewNode->Data;
	}
	POSITION		GetPosByIndex(DWORD index)//���������Ż�ȡpos
	{
		CListNode	*pNode;
		DWORD		total =GetLength();
		if(index >= total)
			return NULL;

		if(index > (total+1)/2)
		{
			pNode		=pTail;
			LONG	i	=total-1;
			while(pNode!=NULL && i>=0)
			{	
				if(i==index)
					return (POSITION)pNode;
				pNode=pNode->pPrev;
				i--;
			}
		}
		else
		{
			pNode		=pHead;
			DWORD	i	=0;
			while(pNode!=NULL)
			{	
				if(i==index)
					return (POSITION)pNode;
				pNode=pNode->pNext;
				i++;
			}
		}


		
		return NULL;
	}
	LONG		PositionToIndex(POSITION pos)
	{
		if(pos == NULL)
			return -1;
		LONG		index	=0;
		CListNode	*pNode =pHead;
		while(pNode != NULL)
		{
			if(pNode == (CListNode	*)pos)
				return index;
			index ++;
			pNode =pNode->pNext;
		}
		return -1;
	}
	T*			InsertNodeInIndex(T *pData,DWORD index)//����ָ�������ĺ���
	{
		POSITION pos=GetPosByIndex(index);
		 return InsertNode(pData,pos);
	}
	T *			InsertNode(T *pData,POSITION pos=NULL)//����ָ��λ�õĺ���
	{
		if(pos==NULL)
		{//��ָ��λ�ã���ֱ�Ӳ���β��
			AddTail(pData);
			return NULL;
		}
		CListNode *pNewNode=AllocNode(pData);
		if(pNewNode==NULL)
			return NULL;
		//-----------------------------------
		CListNode	*pTmp=(CListNode*)pos;
		if(pTmp->pNext==NULL)//β�ڵ�
		{
			pNewNode->pPrev=pTmp;
			pTmp->pNext=pNewNode;

			pTail=pNewNode;//β�ڵ�ָ����
		}
		else
		{//�м�ڵ�
			pNewNode->pPrev		=pTmp;
			pNewNode->pNext		=pTmp->pNext;
			pTmp->pNext->pPrev	=pNewNode;

			pTmp->pNext		=pNewNode;


		}

		m_dwCount ++;

		return &pNewNode->Data;
	}

	void			DelHead()//ɾ��ͷ�ڵ�
	{
		if(pHead==NULL)return;
		CListNode *pTmp=pHead;
		pHead=pHead->pNext;
		if(pHead!=NULL)
		{
			pHead->pPrev=NULL;
		}
		else
		{
			pTail=NULL;
		}
		FreeNode(pTmp);
		m_dwCount --;
	}
	void			DelTail()//ɾ��β�ڵ�
	{
		if(pTail==NULL)return;
		CListNode *pTmp=pTail;
		pTail=pTail->pPrev;
		if(pTail!=NULL)
		{
			pTail->pNext=NULL;
		}
		else
		{
			pHead=NULL;
		}
		FreeNode(pTmp);
		m_dwCount --;

	}
	void			DelNodeByIndex(DWORD index)
	{
		DelNode(GetPosByIndex(index));
	}
	void			DelNode(POSITION pos)//ɾ��һ���ڵ�
	{
		if(pos==NULL)
			return;
		CListNode	*pNode=(CListNode*)pos;
		if(pNode->pPrev==NULL&&pNode->pNext==NULL)
		{//���һ���ڵ�
			pHead=NULL;
			pTail=NULL;
		}
		else
		{
			if(pNode->pPrev==NULL)
			{//ͷ
				pHead=pHead->pNext;
				pHead->pPrev=NULL;
			}
			else if(pNode->pNext==NULL)
			{//β
				pTail=pNode->pPrev;
				pTail->pNext=NULL;
			}
			else
			{//�м�
				//�������жϿ��ýڵ�
				pNode->pPrev->pNext=pNode->pNext;//ǰһ�ڵ�ĺ�һ�ڵ�ָ���Լ��ĺ�һ�ڵ�
				pNode->pNext->pPrev=pNode->pPrev;//��һ�ڵ��ǰһ�ڵ�ָ���Լ���ǰһ�ڵ�
			}
		}
	//ɾ���ڴ�
		FreeNode(pNode);
		m_dwCount --;

	}

public://����
	POSITION		GetFirstPosition()
	{
		return (POSITION)pHead;
	}
	POSITION		GetLastPosition()
	{
		return (POSITION)pTail;
	}
	T				*GetAt(POSITION pos)
	{
		if(pos==NULL)
			return NULL;
		CListNode *pNode=(CListNode*)pos;
		return &pNode->Data;		
	}
	BOOL			GetAt(POSITION pos,T IN OUT *pData)
	{
		if(pos==NULL)
			return FALSE;
		CListNode *pNode=(CListNode*)pos;
		*pData = pNode->Data;		//=�ſ������أ������������֧�ֶ���Ķ���Ĵ洢��ֱ����memcpy�Ͳ���
		return TRUE;
	}
	void			MoveNext(POSITION &pos)
	{		
		if(pos==NULL)return;
		CListNode *pNode=(CListNode*)pos;
		if(pNode->pNext==NULL)
			pos=NULL;
		else
			pos=(POSITION)pNode->pNext;
	}
	void			MovePrev(POSITION &pos)
	{
		if(pos==NULL)return;
		CListNode *pNode=(CListNode*)pos;
		if(pNode->pPrev==NULL)
			pos=NULL;
		else
			pos=(POSITION)pNode->pPrev;
	}

public:
	BOOL			IsEmpty()	//���������Ƿ�Ϊ��
	{
		if(pHead==NULL)
			return TRUE;
		return FALSE;
	}
	DWORD			GetLength()//��ȡ�����ȣ����ؽڵ����
	{
		return m_dwCount;
	}
	void			ClearList()
	{
		CListNode *pTemp=pTail;
		while(pTemp!=NULL)
		{
			pTail=pTemp->pPrev;
			delete pTemp;
			pTemp=pTail;
		}		
		pHead		=NULL;
		pTail		=NULL;
		m_dwCount	=0;
	}
	void			DestroyList()//���������ͷ��ڴ�
	{
		ClearList();
		ClearLookatList();
	}

	POSITION		Find(T& Data)
	{
		CListNode	*pNode=NULL;
		POSITION	pos=GetFirstPosition();
		for(;pos!=NULL;)
		{
			pNode=(CListNode*)pos;
			if(pNode==NULL)
				break;
				
			if(pNode->Data==Data)//֧��==������
					return pos;
			MoveNext(pos);
		}
		return NULL;
	}
	BOOL			Swap(T* pData1,T* pData2)
	{
		if(pData1==NULL||pData2==NULL)
			return FALSE;
		return Swap(Find(*pData1),Find(*pData2));

	}
	BOOL			Swap(POSITION pos1,POSITION pos2)
	{
		if(pos1==NULL||pos2==NULL||pos1==pos2)
			return FALSE;
		
		CListNode *pNode1=(CListNode*)pos1;
		CListNode *pNode2=(CListNode*)pos2;
		CListNode *pPrev1,*pNext1;
		CListNode *pPrev2,*pNext2;
		pPrev1=pNode1->pPrev;
		pNext1=pNode1->pNext;
		pPrev2=pNode2->pPrev;
		pNext2=pNode2->pNext;

		DWORD	flag1=0,flag2=0;
		if(pNode1==pHead)
			flag1=1;
		else if(pNode1==pTail)
			flag1=2;

		if(pNode2==pHead)
			flag2=1;
		else if(pNode2==pTail)
			flag2=2;

		if(pNode1->pNext==pNode2)
		{//���ٽڵ�
			if(pPrev1!=NULL)
				pPrev1->pNext=pNode2;
			pNode2->pPrev=pPrev1;

			pNode2->pNext=pNode1;
			pNode1->pPrev=pNode2;

			pNode1->pNext=pNext2;
			if(pNext2!=NULL)
				pNext2->pPrev=pNode1;


		}
		else if(pNode2->pNext==pNode1)
		{//
			if(pPrev2!=NULL)
				pPrev2->pNext=pNode1;
			pNode1->pPrev=pPrev2;

			pNode1->pNext=pNode2;
			pNode2->pPrev=pNode1;

			pNode2->pNext=pNext1;
			if(pNext1!=NULL)
				pNext1->pPrev=pNode2;
		}else
		{
			pNode1->pNext=pNext2;
			pNode1->pPrev=pPrev2;
			if(pNext2!=NULL)pNext2->pPrev=pNode1;
			if(pPrev2!=NULL)pPrev2->pNext=pNode1;

			pNode2->pNext=pNext1;
			pNode2->pPrev=pPrev1;
			if(pNext1!=NULL)pNext1->pPrev=pNode2;
			if(pPrev1!=NULL)pPrev1->pNext=pNode2;
		}

		switch(flag1)
		{
		case 1:
			{
				pHead=pNode2;
			}
			break;
		case 2:
			{
				pTail=pNode2;
			}
			break;
		}
		switch(flag2)
		{
		case 1:
			{
				pHead=pNode1;
			}
			break;
		case 2:
			{
				pTail=pNode1;
			}
			break;
		}
		return TRUE;
	}
public:
	T*	operator[](int index)
	{
		POSITION pos=GetPosByIndex(index);
		return GetAt(pos);
	}
	void	ClearLookatList()
	{
		CListNode*	pNode;
		while(m_pLookatListHead!=NULL)
		{
			pNode				=m_pLookatListHead;
			m_pLookatListHead	=m_pLookatListHead->pNext;
			delete pNode;
		}

		m_dwLookatListCount		=0;
		m_pLookatListHead		=NULL;
	}
private:
	CListNode	*AllocNode(T *pData)
	{
		if(pData==NULL)
			return NULL;
		CListNode *pNewNode=NULL;
		try
		{
			pNewNode		=GetNodeFromLookatList();
			if(pNewNode ==NULL)
				pNewNode	=new CListNode;
		}
		catch(...)
		{
			pNewNode=NULL;
		}

		if(pNewNode==NULL)
			return NULL;

		pNewNode->pNext=NULL;
		pNewNode->pPrev=NULL;

		pNewNode->Data = *pData;	//֧����Ķ������� = �������,
		return pNewNode;

	}
	void	FreeNode(CListNode* pNode)
	{
		if(m_dwLookatListCount <m_dwLookatListMaxCount)
		{
			pNode->pNext		=m_pLookatListHead;
			pNode->pPrev		=NULL;
			m_pLookatListHead	=pNode;
			m_dwLookatListCount ++;
			return;
		}
		delete pNode;
	}
	CListNode*	GetNodeFromLookatList()
	{
		if(m_pLookatListHead ==NULL)
			return NULL;

		CListNode*	pNode;
		pNode				=m_pLookatListHead;
		m_pLookatListHead	=m_pLookatListHead->pNext;

		pNode->pNext =pNode->pPrev =NULL;
		return pNode;		
	}

	void	SetLookatListMaxSize(DWORD dwSize)
	{
		m_dwLookatListMaxCount	=m_dwLookatListMaxCount;
		if(m_dwLookatListCount > dwSize && m_pLookatListHead!=NULL)
		{
			CListNode*	pNode;
			for(DWORD i=0;i<m_dwLookatListCount-m_dwLookatListMaxCount;i++)
			{
				pNode				=m_pLookatListHead;
				m_pLookatListHead	=m_pLookatListHead->pNext;
				delete pNode;
				
				if(m_pLookatListHead ==NULL)
					break;
			}
		}
	}
};