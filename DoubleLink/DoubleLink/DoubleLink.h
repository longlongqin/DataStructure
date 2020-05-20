#ifndef DOUBLE_LINK_H
#define DOUBLE_LINK_H

/*˫������*/
#include <iostream>
#include <cassert>

template <class T>
class DNode  //�ڵ�Ľṹ
{
public:
	T m_value;
	DNode* m_prev;
	DNode* m_next;

public:
	DNode() : m_next{ NULL }, m_prev{ NULL }
	{
	}

	DNode(T value, DNode* prev, DNode* next)
		: m_value{ value }, m_prev{ prev }, m_next{ next }
	{
	}
};

template<class T>
class DoubleLink
{
private:
	int m_count; //�ڵ���Ŀ
	DNode<T>* m_phead; //ͷָ��

public:
	DoubleLink();
	~DoubleLink();

	int node_size(); //�������ڵ���Ŀ
	int IsEmpty(); //�����Ƿ�Ϊ��

	/*���ӽڵ㣬��T node  ʵ����ָҪ����Ľڵ��value��*/
	int insert(int index, T node_value);
	int insert_first(T node_value);
	int insert_last(T node_value);

	/*ɾ���ڵ�*/
	int del(int index);
	int del_first();
	int del_last();

	/*��ýڵ��ֵ*/
	T get(int index);
	T get_first();
	T get_last();

private:
	//���ʽڵ�
	DNode<T>* get_node(int index);
};

template <class	T>
DoubleLink<T>::DoubleLink()
{
	//������ͷ��ע�⣬��ͷ���洢����
	m_phead = new DNode<T>();
	m_phead->m_prev = m_phead->m_next = m_phead;

	//��������ڵ���Ϊ0
	m_count = 0;
}

template<class T>
DoubleLink<T>::~DoubleLink()
{
	//ɾ�����нڵ�
	DNode<T>* ptmp;
	DNode<T>* pnode = m_phead->m_next;

	while (pnode != m_phead)
	{
		ptmp = pnode;
		pnode = pnode->m_next;
		delete ptmp;
	}

	//ɾ����ͷ
	delete m_phead;
	m_phead = NULL;
}


template<class T>
int DoubleLink<T>::node_size()
{
	return m_count;
}

template<class T>
int DoubleLink<T>::IsEmpty()
{
	return m_count == 0;
}


template<class T>
DNode<T>* DoubleLink<T>::get_node(int index)
{
	//�ж��±������Ƿ���ȷ
	assert((index >= 0 && index < m_count) && "the index in out of bound in get_node()!");

	//�������
	if (index <= (m_count / 2))
	{
		int count = 0;
		DNode<T>* pindex = m_phead->m_next;
		while (count++ < index)
			pindex = pindex->m_next;

		return pindex;
	}
	//�������
	if ((index > m_count / 2) && (index < m_count))
	{
		int count = m_count - 1;
		DNode<T>* pindex = m_phead->m_prev;
		while (count-- > index)
			pindex = pindex->m_prev;

		return pindex;
	}
}

template<class T>
T DoubleLink<T>::get(int index)
{
	return get_node(index)->m_value;
}

template<class T>
T DoubleLink<T>::get_first()
{
	return get_node(0)->m_value;
}

template<class T>
T DoubleLink<T>::get_last()
{
	return get_node(m_count - 1)->m_value;
}


template<class T>
int DoubleLink<T>::insert(int index, T node_value)
{
	if (index == 0)
		return insert_first(node_value);
	else if (index == (m_count))
	{
		return insert_last(node_value);
	}
	else
	{
		assert((index >= 0 && index < m_count) && "the index in out of bound in insert()!");
		DNode<T>* pindex = get_node(index); //�ҳ�Ҫ�����λ�õ�ԭʼ�ڵ�
		DNode<T>* pnode = new DNode<T>(node_value, pindex->m_prev, pindex); //������Ҫ����Ľڵ�

		pindex->m_prev->m_next = pnode;
		pindex->m_prev = pnode;

		++m_count;
	}
	return 0;
}

template<class T>
int DoubleLink<T>::insert_first(T node_value)
{
	DNode<T>* pnode = new DNode<T>(node_value, m_phead, m_phead->m_next);
	m_phead->m_next->m_prev = pnode;
	m_phead->m_next = pnode;

	++m_count;

	return 0;
}

template<class T>
int DoubleLink<T>::insert_last(T node_value)
{
	DNode<T>* pnode = new DNode<T>(node_value, m_phead->m_prev, m_phead);
	m_phead->m_prev->m_next = pnode;
	m_phead->m_prev = pnode;

	++m_count;

	return 0;
}


template <class T>
int DoubleLink<T>::del(int index)
{
	DNode<T>* pindex = get_node(index);
	pindex->m_prev->m_next = pindex->m_next;
	pindex->m_next->m_prev = pindex->m_prev;
	delete pindex; //��Ҫ����
	--m_count;

	return 0;
}

template<class T>
int DoubleLink<T>::del_first()
{
	return del(0);
}

template<class T>
int DoubleLink<T>::del_last()
{
	return del(m_count - 1);
}


#endif
