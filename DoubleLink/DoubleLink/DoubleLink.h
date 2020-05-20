#ifndef DOUBLE_LINK_H
#define DOUBLE_LINK_H

/*双向链表*/
#include <iostream>
#include <cassert>

template <class T>
class DNode  //节点的结构
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
	int m_count; //节点数目
	DNode<T>* m_phead; //头指针

public:
	DoubleLink();
	~DoubleLink();

	int node_size(); //获得链表节点数目
	int IsEmpty(); //链表是否为空

	/*增加节点，（T node  实际是指要插入的节点的value）*/
	int insert(int index, T node_value);
	int insert_first(T node_value);
	int insert_last(T node_value);

	/*删除节点*/
	int del(int index);
	int del_first();
	int del_last();

	/*获得节点的值*/
	T get(int index);
	T get_first();
	T get_last();

private:
	//访问节点
	DNode<T>* get_node(int index);
};

template <class	T>
DoubleLink<T>::DoubleLink()
{
	//创建表头，注意，表头不存储数据
	m_phead = new DNode<T>();
	m_phead->m_prev = m_phead->m_next = m_phead;

	//设置链表节点数为0
	m_count = 0;
}

template<class T>
DoubleLink<T>::~DoubleLink()
{
	//删除所有节点
	DNode<T>* ptmp;
	DNode<T>* pnode = m_phead->m_next;

	while (pnode != m_phead)
	{
		ptmp = pnode;
		pnode = pnode->m_next;
		delete ptmp;
	}

	//删除表头
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
	//判断下标输入是否正确
	assert((index >= 0 && index < m_count) && "the index in out of bound in get_node()!");

	//正向查找
	if (index <= (m_count / 2))
	{
		int count = 0;
		DNode<T>* pindex = m_phead->m_next;
		while (count++ < index)
			pindex = pindex->m_next;

		return pindex;
	}
	//反向查找
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
		DNode<T>* pindex = get_node(index); //找出要插入的位置的原始节点
		DNode<T>* pnode = new DNode<T>(node_value, pindex->m_prev, pindex); //创建出要插入的节点

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
	delete pindex; //不要忘记
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
