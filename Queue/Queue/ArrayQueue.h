#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_
//ʹ������ʵ��
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

	// ����
	T pop();

	//����
	void add(T node_value);

	//���ʶ���Ԫ��
	T traverse(int index);

	int size();
	int isEmpty();
};

template<class T>
ArrayQueue<T>::ArrayQueue()
{
	m_count = 0;
	//Ĭ�϶��д�СΪ12
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
		std::cout << "�����ѿգ�����ʱ���ܽ��г��Ӳ�����\n";
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
