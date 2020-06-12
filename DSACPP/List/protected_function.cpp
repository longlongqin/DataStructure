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