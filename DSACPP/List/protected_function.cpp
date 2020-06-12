#include "List.h"

template<class T>
void List<T>::init()
{
	header_ = new ListNode<T>;
	trailer_ = new ListNode<T>;

	header_->pred_ = nullptr;
	header_->succ_ = trailer_;

	trailer_->pred_ = header_;
	trailer_->succ_ = nullptr;

	size_ = 0;
}

template<class T>
int List<T>::clear()
{
	int oldsize = size_;
	while (size_ > 0)
	{
		remove(header_->succ_); //反复删除首节点，直至列表变空
		--size_;
	}
	return oldsize;
}

template<class T>
void List<T>::copyNodes(ListNodePosi<T> p, int n)
{
	init();
	while (n-- > 0)
	{
		insertAsLast(p->data_);
		p = p->succ_;
	}
}

template<class T>
void List<T>::insertionSort(ListNodePosi<T> p, int n)
{
	for (int r = 0; r < n; r++)
	{
		insertB(search(p->data_, r, p), p->data_);
		p = p->succ_;
		remove(p->pred_);
	}
}

template<class T>
void List<T>::selectionSort(ListNodePosi<T> p, int n)
{
	ListNodePosi<T> head = p->pred_;
	ListNodePosi<T> trail = p;
	for (int i = 0; i < n; i++)
		trail = trail->succ_;  //待排序区间为：(head,trail)
	while (n-- > 1)
	{
		ListNodePosi<T> max = selectMax(head, n);
		insertA(trail, remove(max));
		trail = trail->pred_;
	}
}

template<class T>
void List<T>::mergeSort(ListNodePosi<T>& p, int n)
{
	if (n < 2) return;
	int mi = n >> 1; //求中点的秩
	ListNodePosi<T> q = p;
	for (int i = 0; i < m; i++)
		q = q->succ_;  //求位于中点的节点
	mergeSort(p, mi); mergeSort(q, n - mi);
	merge(p, mi, *this, q, n - mi); //归并
}

template<class T>
void List<T>::merge(ListNodePosi<T>& p, int n, List<T>& L, ListNodePosi<T> q, int m)
{
	ListNodePosi<T> pp = p->pred_;
	while (m > 0)
	{
		if ((n > 0) && (p->data_ <= q->data_)) //前一子列中p仍在区间内，且v(p)<=v(q)
		{
			if(q == (p =p->succ_)) //如果p的直接后继与q相等
			{
				break; //则说明此时，前一子序列与后一子序列已经归并完成
			}
			--n; //否则，就是让p指向其直接后继，继续比较
		}
		else if ((n <= 0) || (p->data_ > q->data_)) //前一子序列的p超出右界,或者v(p)>v(q)
		{
			insertA(p, q->data_); //则，将 后一子序列中的q插入p之前(成为p的直接前驱)
			q = q->succ_;
			L.remove(q->pred_); //参数中的L(一般)指的是后一子序列的列表。（但也可以是前、后子序列来自同一列表）
			--m;
		}
	}
	p = pp->succ_; //归并后的(新)起点
}