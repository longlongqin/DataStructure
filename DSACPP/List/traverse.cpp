#include "List.h"

template<class T>
void List<T>::traverse(void (*visit) (T&)) //借助函数指针机制
{
	for (ListNodePosi<T> p =header_->succ_; p!=trailer_;p=p->succ_)
	{
		visit(p->data_);
	}
}

template<class T>
template<class VST>
void List<T>::traverse(VST& visit) //借助函数对象机制
{
	for (ListNodePosi<T> p = header_->succ_; p != trailer_; p = p->succ_)
	{
		visit(p->data_);
	}
}