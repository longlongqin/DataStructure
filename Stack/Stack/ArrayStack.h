#ifndef ARRAY_STACK_H_
#define ARRAY_STACK_H_
//教程代码：https://www.cnblogs.com/skywang12345/p/3562239.html
#include <iostream>

template<class T>
class ArrayStack
{
private:
	T* m_arr;
	int m_count; // 栈现有的元素数目

public:
	ArrayStack();
	~ArrayStack();

	// 入栈
	void push(T node_value);
	
	// 出栈
	T pop();

	// 返回栈顶元素
	T top_node();

	// 返回栈现有的元素数目
	int size();

	// 栈是否为空
	int isEmpty();
};

template<class T>
ArrayStack<T>::ArrayStack()
{
	m_arr = new T[12]; //默认栈的大小为12
	if (!m_arr) //若分配不成功，返回错误提示
		std::cout << "arr malloc error!" << '\n';
}

template<class T>
ArrayStack<T>::~ArrayStack()
{
	delete[] m_arr;
	m_arr = NULL; //让它指向空，防止它依然指向被释放的内存空间
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
