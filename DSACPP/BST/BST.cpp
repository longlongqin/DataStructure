#include "BST.h"

//查找
template<class T>
BinNodePosi<T>& BST<T>::search(const T& e)  //在BST中查找关键码e
{
	return searchIn(root_, e, hot_ = nullptr); //返回目标节点位置的引用，以便后续插入、删除操作
}

template<class T>
static BinNodePosi<T>& searchIn(BinNodePosi<T>& v, const T& e, BinNodePosi<T>& hot)
{
	if ((e == v->data_) || !v) // 递归基
	{// 当（e == v->data_）时，查找成功；
	 // 当v节点为空时，查找失败,也返回一个值（此时该值为null）【这里使用了哨兵策略】
		return v->data_;
	}
	
	hot = v; //一般情况：记录当前节点，然后继续深入一层递归
	return searchIn((e > v.data_) ? v->rc_ : v->lc_, e, hot);
} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）


//插入
template<class T>
BinNodePosi<T> BST<T>::insert(const T& e)
{
	BinNodePosi<T>& x = search(e); //查找，找出要插入的位置
	if (x) return x; //确认目标不存在（留意对hot_的设置）[即，如果要插入的值e，在原二叉搜索树中本来就存在，则直接返回]

	BinNode<T>* x1 = new BinNode<T>(e, hot_); //创建新节点，以e为关键码，以hot_为父亲

	//开始更新祖先的高度，以及二叉树的规模
	++size_;
	updateHeightAbove(x1); //更新祖先的高度

	return x1; //新插入的节点，必为叶节点
} //无论e是否存在于原树中，返回时总有x->data == e


// 删除
template<class T>
bool BST<T>::remove(const T& e)
{
	BinNodePosi<T>& x = search(e); if (!x) return false; //确认要删除的目标存在（留意hot_的设置）
	removeAt(x, hot_);

	//更新二叉搜索树
	--size_;
	updateHeightAbove(hot_); //因为x节点被删除，所以从其父节点开始的祖先进行高度更新
	return true;

} //删除成功与否，由返回值指示

template<class T>
static BinNodePosi<T> removeAt(BinNodePosi<T>& x, BinNodePosi<T> hot)
{
	BinNodePosi<T> w = x; //实际被删除的节点，初值同x
	BinNodePosi<T> succ = nullptr; //实际被删除的节点的后继节点（是中序遍历中的后继节点）

	//分情况讨论：1.被删除的节点只有 右孩子、左孩子、无孩子；2.左右孩子均存在
	if (!HasLChild(*x)) //1.1不存在左子树
		succ = x->rc_;  //则，直接*x替换为右子树（x可能是叶子节点，此时其直接后继为空）
	else if (!HasRChild(*x)) //1.2 不存在右子树
		succ = x->lc_;       // 则，直接将*x替换为左子树（x可能是叶子节点，此时其直接后继为空）
	else // 2.左右子树均存在
	{
		w = w->succ(); //找到*x的直接后继*w
		swap(x->data_, w->data_);

		BinNodePosi<T> u = w->parent_;
		((u == x) ? u->rc_ : u->lc_) = succ = w->rc_;
	}

	hot = w->parent_; //记录被删除节点的父亲
	if (succ) //如果被删除节点的直接后继存在，则
	{//将被删除节点w的父节点与w的直接后继相连
		succ->parent_ = hot; //父节点确定
		succ = ((hot->lc_ == w) ? hot->lc_ : hot->rc_); //确定是左孩子还是右孩子
	}
		
	release(w); release(w->data_); //释放被摘除的节点
	return succ; //返回接替者
}