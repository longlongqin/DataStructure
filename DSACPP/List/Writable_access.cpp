#include "List.h"

template<class T>
ListNodePosi<T> List<T>::insertAsFirst(T const& e)
{
	++size_;
	return header_->insertAsucc(e);
}

template<class T>
ListNodePosi<T> List<T>::insertAsLast(T const& e)
{
	++size_;
	return trailer_->insertAspred(e);
}

template<class T>
ListNodePosi<T> List<T>::insertA(ListNodePosi<T> p, T const& e)
{
	++size_;
	return p->insertAspred(e);
}

template<class T>
ListNodePosi<T> List<T>::insertB(ListNodePosi<T> p, T congst& e)
{
	++size_;
	return p->insertAsucc(e);
}

template<class T>
T List<T>::remove(ListNodePosi<T> p)
{
	T data = p->data_;
	p->pred_->succ_ = p->succ_;
	p->succ_->pred_ = p->pred_;

	--size_;
	delete p; //不要忘记，手动收回内存
	return data;
}

template<class T>
int List<T>::deduplicate()
{

}