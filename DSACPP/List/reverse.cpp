#include "List.h"

//°æ±¾1
template<class T>
void List<T>::reverse()
{
	ListNodePosi<T> former = header_->succ_ ; //Ç°
	ListNodePosi<T> later = trailer_->pred_; //ºó

	Rank start = 0, end = size_;
	while (start < end)
	{
		swap(former->data_, later->data_);
		former = former->succ_; later = later->pred_;
		++start; --end;
	}
}