#include "List.h"

template<class T>
ListNodePosi<T> List<T>::first()
{
	return header_->succ_;
}

template<class T>
ListNodePosi<T> List<T>::last()
{
	return trailer_->pred_;
}

template<class T>
T& List<T>::operator[](Rank r)
{
	ListNodePosi<T> p = first(); //从首节点开始
	while (r-- > 0)
		p = p->succ_;
	return p->data_;
}

template<class T>
Rank List<T>::size() const
{
	return size_;
}

template<class T>
bool List<T>::empty() const
{
	return size_ <= 0;
}

template<class T>
bool List<T>::valid(ListNodePosi<T> p)
{
	return p && (p != header_ && p != trailer_);
}

template<class T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const
{
	ListNodePosi<T> position = p;
	while (n-- > 0)
	{
		if (e == p->data_)
			return p;
		else
			p = p->pred_;
	}
	return nullptr; //此时找不到
}
template<class T>
ListNodePosi<T> List<T>::find(T const& e) const
{
	return find(e, size_, last());
}

template<class T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const
{
	ListNodePosi<T> position = p;
	while (n-- >= 0)
	{
		if (p->data_ > e)
			p = p->pred_;
		else if(p->data_ <= e)
			break;
	}
	return p;
}

template<class T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n)
{
	ListNodePosi<T> max = p;
	for (int i = 1; i < n; ++i)
	{
		if (p->succ_->data_ >= max)
			max = p->succ_;
		p = p->succ_;
	}
	return max;
}

template<class T>
ListNodePosi<T> List<T>::selectMax()
{
	return selectMax(header_->succ_, size_);
}