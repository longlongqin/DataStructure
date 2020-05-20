#ifndef ARRAY_STACK_H_
#define ARRAY_STACK_H_
//�̴̳��룺https://www.cnblogs.com/skywang12345/p/3562239.html
#include <iostream>

template<class T>
class ArrayStack
{
private:
	T* m_arr;
	int m_count; // ջ���е�Ԫ����Ŀ

public:
	ArrayStack();
	~ArrayStack();

	// ��ջ
	void push(T node_value);
	
	// ��ջ
	T pop();

	// ����ջ��Ԫ��
	T top_node();

	// ����ջ���е�Ԫ����Ŀ
	int size();

	// ջ�Ƿ�Ϊ��
	int isEmpty();
};

template<class T>
ArrayStack<T>::ArrayStack()
{
	m_arr = new T[12]; //Ĭ��ջ�Ĵ�СΪ12
	if (!m_arr) //�����䲻�ɹ������ش�����ʾ
		std::cout << "arr malloc error!" << '\n';
}

template<class T>
ArrayStack<T>::~ArrayStack()
{
	delete[] m_arr;
	m_arr = NULL; //����ָ��գ���ֹ����Ȼָ���ͷŵ��ڴ�ռ�
}

template<class T>
void ArrayStack<T>::push(T node_value)
{
	m_arr[m_count + 1] = node_value;
	++m_count;
}

template<class T>
T ArrayStack<T>::pop()
{
	return m_arr[m_count--];
}

template<class T>
T ArrayStack<T>::top_node()
{
	return m_arr[m_count];
}

template<class T>
int ArrayStack<T>::size()
{
	return m_count;
}

template<class T>
int ArrayStack<T>::isEmpty()
{
	return m_count == 0;
}


#endif
