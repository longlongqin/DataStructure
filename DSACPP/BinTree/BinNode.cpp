#include "BinNode.h"

template<class T>
int BinNode<T>::size()
{
	int s = 1; //ͳ�Ʊ���
	if (lc_)
	{
		s += lc_->size();	//�ݹ������������ģ
	}
	
	if (rc_)
	{
		s += rc_->size();	//�ݹ������������ģ
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

