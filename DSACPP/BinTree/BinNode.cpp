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

template<class T>
BinNodePosi<T> BinNode<T>::succ() //中序遍历中的节点的直接后继
{
	BinNodePosi<T> s = this; //记录后继的临时变量
	if (rc_)
	{
		s = rc_; //如果有右孩子，则当前节点的直接后继必在其右子树中
		while (HasLChild(*s)) s = s->lc_; //且其直接后继为其右子树中 最靠左（最小）的节点
	}
	else //否则，其直接后继应当为“当前节点包含于其左子树中的最低祖先”，具体就是
	{
		while (IsRChild(*s))	s = s->parent_; //逆向的沿邮箱分支，不断朝左上方移动
		s = s->parent_; //最后在超右上方移动一步，即抵达直接后继（如果存在）
	}
		
	return s;
}

