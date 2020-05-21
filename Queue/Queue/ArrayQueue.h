#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_
//使用数组实现
#include <iostream>

template<class T>
class ArrayQueue
{
private:
	T* m_arr;
	int m_count;

public:
	ArrayQueue();
	~ArrayQueue();

	// 出队
	T pop();

	//进队
	void add(T node_value);

	//访问队列元素
	T traverse(int index);

	int size();
	int isEmpty();
};

template<class T>
ArrayQueue<T>::ArrayQueue()
{
	m_count = 0;
	//默认队列大小为12
	m_arr = new T[12];
	if (!m_arr)
	{
		std::cout << "arr malloc error!" << std::endl;
	}
}

template<class T>
ArrayQueue<T>::~ArrayQueue()
{
	delete[] m_arr;

	m_arr = NULL;
}

template<class T>
T ArrayQueue<T>::pop()
{
	if (m_count == 0)
	{
		std::cout << "队列已空，即此时不能进行出队操作！\n";
		return -1;
	}

	T tmp = m_arr[0];
	--m_count;
	for (int i = 0; i < m_count; ++i)
		m_arr[i] = m_arr[i + 1];
	return tmp;
}

template<class T>
void ArrayQueue<T>::add(T node_value)
{
	m_arr[m_count] = node_value;
	++m_count;
}

template<class T>
T ArrayQueue<T>::traverse(int index)
{
	return m_arr[index];
}

template<class T>
int ArrayQueue<T>::size()
{
	return m_count;
}

template<class T>
int ArrayQueue<T>::isEmpty()
{
	return (m_count == 0);
}

#endif
