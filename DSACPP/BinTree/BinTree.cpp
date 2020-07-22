#include "BinTree.h"
#include "IncludedImplementCpp.h"
#include "release.h"

//高度更新
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x)
{
	return x->height_ = 1 + max(stature(x->lc_), stature(x->rc_));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent_;
	}
}

//节点插入
template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRoot(const T& e)
{
	size_ += 1;
	return root_ = new BinNode<T>(e);
}

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsLC(BinNodePosi<T> x, const T& e)
{
	size_ += 1;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lc_;
}

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRC(BinNodePosi<T> x, const T& e)
{
	size_++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc_;
}

//子树接入
template<typename T>
BinNodePosi<T> BinTree<T>::attachAsLC(BinNodePosi<T> x, BinTree<T>*& t)
{
	
	if (t->root_) //检测该子树是否为空
	{
		x->lc_ = t->root_;
		x->lc_->parent_ = x; //接入
	}
	updateHeightAbove(x);

	//释放原树
	t->root_ = nullptr; t->size_ = 0; release(t); t = nullptr;

	return x; //返回接入位置
}

template<typename T>
BinNodePosi<T> BinTree<T>::attachAsRC(BinNodePosi<T> x, BinTree<T>*& t)
{
	if (t->root_)
	{
		x->rc_ = t->root_;
		x->rc_->parent_ = x;
	}
	updateHeightAbove(x);
	t->root_ = nullptr; t->size_ = 0; release(t); t = nullptr;
	return x;
}

//子树删除
template<typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt(BinNodePosi<T> x)
{
	if (!x)
		return 0; //递归基：空树
	int n = 1 + removeAt(x->lc_) + removeAt(x->rc_); //递归释放左、右子树

	release(x->data_); release(x);  //释放被摘除节点，
	return n;	//并返回删除节点总数
}

template<typename T> //删除二叉树中 位置x处 及其后代， 返回被删除节点的数目
int BinTree<T>::remove(BinNodePosi<T> x) //assert：x为二叉树中合法的位置
{
	FromParentTo(*x) = nullptr; //切断来自父节点的指针
	updateHeightAbove(x); //更新祖先节点的高度
	
	int n = removeAt(x); size_ -= n; //删除子树x。更新规模。
	return n; //返回被删除子树的规模
}


//子树分离
template<class T>
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x)
{
	FromParentTo(*x) = nullptr; //切断来自父节点的指针
	updateHeightAbove(x->parent_); //更新原树中所有祖先的高度

	BinTree<T>* s = new BinTree<T>(x->data_); //创建新树
	s->root_ = x;	x->parent_ = nullptr; //新树根节点为x，x的父亲为nullptr
	s->size_ = x->size_; //新树的规模
	this->size_ -= s->size_; //更新原树的规模
	return s; //返回新树（分离下来的子树）
}
