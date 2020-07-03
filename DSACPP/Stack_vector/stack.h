#pragma once
#include "../DSACPP/vector.h"

template<class T>
class Stack : public Vector<T>
{
public:
	void push(const T& e)
	{
		insert(size(), e);  //��ջ����Ч�ڣ�����Ԫ����Ϊ������ĩβԪ�ز���
	}

	T pop()
	{
		return remove(size() - 1); //��ջ����Ч�ڣ��������е�ĩβԪ��ɾ��
	}

	T& top()
	{
		return (*this)[size() - 1];
	}
};

#if 0
//ʹ��ListΪ���࣬ʵ��ջ��ֻ�ǵ�����ϰ��
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
