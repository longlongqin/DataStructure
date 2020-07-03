#pragma once
#include "../DSACPP/vector.h"

template<class T>
class Stack : public Vector<T>
{
public:
	void push(const T& e)
	{
		insert(size(), e);  //入栈，等效于：将新元素作为向量的末尾元素插入
	}

	T pop()
	{
		return remove(size() - 1); //出栈，等效于：将向量中的末尾元素删除
	}

	T& top()
	{
		return (*this)[size() - 1];
	}
};

#if 0
//使用List为父类，实现栈（只是当做练习）
namespace use_List
{
#include "../List/List.h"

	template<class T>
	class Stack : public List<T>
	{
		void push(const T& e)
		{
			insertAsLast(e);
		}

		T pop()
		{
			remove(last());
		}

		T& top()
		{
			return last()->data_;
		}
	};

}
#endif
