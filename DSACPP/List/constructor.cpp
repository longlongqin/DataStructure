#include "List.h"

template<class T>
List<T>::List()
{
	init();
}

template<class T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L.size_);
}

template<class T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	ListNodePosi<T> p = L.first();
	while (r-- > 0)
		p = p->succ_;
	copyNodes(p, n);
}

template<class T>
List<T>::List(ListNodePosi<T> p, int n)
{
	copyNodes(p, n);
}