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
		remove(header_->succ_); //����ɾ���׽ڵ㣬ֱ���б���
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
		trail = trail->succ_;  //����������Ϊ��(head,trail)
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
	int mi = n >> 1; //���е����
	ListNodePosi<T> q = p;
	for (int i = 0; i < m; i++)
		q = q->succ_;  //��λ���е�Ľڵ�
	mergeSort(p, mi); mergeSort(q, n - mi);
	merge(p, mi, *this, q, n - mi); //�鲢
}

template<class T>
void List<T>::merge(ListNodePosi<T>& p, int n, List<T>& L, ListNodePosi<T> q, int m)
{
	ListNodePosi<T> pp = p->pred_;
	while (m > 0)
	{
		if ((n > 0) && (p->data_ <= q->data_)) //ǰһ������p���������ڣ���v(p)<=v(q)
		{
			if(q == (p =p->succ_)) //���p��ֱ�Ӻ����q���
			{
				break; //��˵����ʱ��ǰһ���������һ�������Ѿ��鲢���
			}
			--n; //���򣬾�����pָ����ֱ�Ӻ�̣������Ƚ�
		}
		else if ((n <= 0) || (p->data_ > q->data_)) //ǰһ�����е�p�����ҽ�,����v(p)>v(q)
		{
			insertA(p, q->data_); //�򣬽� ��һ�������е�q����p֮ǰ(��Ϊp��ֱ��ǰ��)
			q = q->succ_;
			L.remove(q->pred_); //�����е�L(һ��)ָ���Ǻ�һ�����е��б�����Ҳ������ǰ��������������ͬһ�б�
			--m;
		}
	}
	p = pp->succ_; //�鲢���(��)���
}