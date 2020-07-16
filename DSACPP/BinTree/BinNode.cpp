#include "BinNode.h"

template<class T>
int BinNode<T>::size()
{
	int s = 1; //统计本身
	if (lc_)
	{
		s += lc_->size();	//递归计入左子树规模
	}
	
	if (rc_)
	{
		s += rc_->size();	//递归计入右子树规模
	}
}

template<class T>
BinNodePosi<T> BinNode<T>::insertAsLC(const T& e)
{
	return lc_ = new BinNode(e, this);
}

template<class T>
BinNodePosi<T> BinNode<T>::insertAsRC(const T& e)
{
	return rc_ = new BinNode(e, this);
}

