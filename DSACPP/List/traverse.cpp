#include "List.h"

template<class T>
void List<T>::traverse(void (*visit) (T&)) //��������ָ�����
{
	for (ListNodePosi<T> p =header_->succ_; p!=trailer_;p=p->succ_)
	{
		visit(p->data_);
	}
}

template<class T>
template<class VST>
void List<T>::traverse(VST& visit) //���������������
{
	for (ListNodePosi<T> p = header_->succ_; p != trailer_; p = p->succ_)
	{
		visit(p->data_);
	}
}