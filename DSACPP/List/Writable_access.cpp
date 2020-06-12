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
ListNodePosi<T> List<T>::insertB(ListNodePosi<T> p, T const& e)
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
	if (size_ < 2)
		return 0;
	int oldsize = size_;
	
	ListNodePosi<T> p = header_->succ_;
	Rank r = 0;
	while (p != trailer_)
	{
		ListNodePosi q = find(p->data_, r, size_ - 1);
		size_--;
		q ? remove(q) : r++;
	}
	return oldsize - size_;
}

template<class T>
int List<T>::uniquify()
{
	int oldsize = size_;
	ListNodePosi<T> p = header_->succ_;
	while (p != trailer_)
	{
		if (p->data_ == p->succ_->data_)
			remove(p->succ_);
		else
			p = p->succ_;
	}
	return oldsize - size_;
}

template<class T>
void List<T>::sort(ListNodePosi<T> p, int n)
{
	switch (rand()%3)
	{
	case 1: insertionSort(p, n); break; //插入
	case 2: selectionSort(p, n); break; //选择
	default: mergeSort(p, n); break;  //归并
	}
}
template<class T>
void List<T>::sort()
{
	sort(first(), size_);
}