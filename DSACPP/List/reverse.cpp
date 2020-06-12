#include "List.h"

//�汾1
template<class T>
void List<T>::reverse()
{
	ListNodePosi<T> former = header_->succ_ ; //ǰ
	ListNodePosi<T> later = trailer_->pred_; //��

	Rank start = 0, end = size_;
	while (start < end)
	{
		swap(former->data_, later->data_);
		former = former->succ_; later = later->pred_;
		++start; --end;
	}
}