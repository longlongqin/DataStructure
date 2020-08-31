#ifndef DSACPP_BST_AVL_H_
#define DSACPP_BST_AVL_H_
#include "BST.h"

template<class T>
class AVL : public BST<T>
{
public:
	BinNodePosi<T> insert(const T& e); //插入（重写）
	bool remove(const T& e); //删除（重写）
	// BST::search() 等其余接口可直接沿用
};

//对节点的平衡性的判断
#define Balanced(x)		(stature((x).lc_) == stature((x).rc_)) //理想平衡条件
#define BalFac(x)		(stature(x).lc_ - stature(x).rc_)	//平衡因子
#define AvlBalanced(x)	(BalFac(x) <=1 && BalFac(x) >=- 1)	//AVL平衡条件

//通过g(x)节点，找到p、v节点
/***************************************************************************
* g(x)：新引入节点后，引起失衡的最深者的节点；
* p：为g(x) 的孩子；
* v：为p的孩子；【v有可能与x是同一个节点】
****/
template<typename T>
BinNodePosi<T> tallerChild(BinNodePosi<T> g)
{
	if (stature(x->lc_) > stature(x->rc_)) //左高
		return x->lc_;
	else if (stature(x->lc_) < stature(x->rc_)) //右高
		return x->rc_;
	else if (stature(x->lc_) = stature(x->rc_)) //等高：与父亲x 同侧者（zig-zig或者 zag-zag）优先【同侧时，只需要单旋即可恢复平衡】
		return IsLChild(*x) ? x->lc_ : x->rc_;
}

//插入
template<class T>
BinNodePosi<T> AVL<T>::insert(const T& e) 
{
	BinNodePosi<T>& x = search(e); if (x) return x; //如果寻找到e（即x节点存在），那么就不用插入了（因为已经存在），则直接返回
	BinNodePosi<T> xx = x = new BinNode<T>(e, hot_);  size_++;//创建新节点x

	//此时，x的父亲hot_若增高，则其祖父有可能失衡
	for (BinNodePosi<T> g = hot_; g; g = g->parent_)
		if (!AvlBalanced(*g)) //找到最深的失衡节点g，则采用“3+4”算法，进行复衡，并将子树重新并入原树中
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //使用“FromParentTo(g*)”表示：g的父亲节点的孩子指针 来 指向这个复衡的子树的根节点（从而将子树重新并入原树中）
			break;
		}
		else //否则（g依然平衡），则只需简单的
		{
			updateHeight(g); //只更新g的高度（因为在for循环中，所以每次循环只更新它自己，循环结束其他节点高度也更新了）【虽然g未失衡，但是其高度还是有可能增加的】
		}
		
	return xx; //最后返回新节点的位置
}

//删除
template<class T>
bool AVL<T>::remove(const T& e)
{
	BinNodePosi<T>& x = search(e); if (!x) return false; //如果没找到要删除的节点，则返回false
	removeAt(x, hot_); --size_; //先按照BST规则删除，（此后被删除节点的父亲、祖先均有可能失衡）

	for (BinNodePosi<T> g = hot_; g; g = g->parent_)
	{
		if (!AvlBalanced(*g)) //一旦发现失衡，使用“3+4”算法使之复衡
		{
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //并将该子树连接至原树中
			//注意，这里不要“break;”。因为局部复衡之后，祖先节点有可能还是失衡的，所以要循环着对每一个祖先判断，如果失衡就将其复衡
			updateHeight(g);
		}
	}
	return true; //删除成功
}

//“3+4”算法
template<typename T>
BinNodePosi<T> BST<T>::connect34(BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c, BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3)
{
	//判断Tx是否存在，是因为子树Tx有可能为空树
	a->lc_ = T0; if (T0) T0->parent_ = a; 
	a->rc_ = T1; if (T1) T1->parent_ = a; updateHeight(a); //更新节点a的高度
	c->lc_ = T2; if (T2) T2->parent_ = c;
	c->rc_ = T3; if (T3) T3->parent_ = c; updateHeight(c); //更新节点c的高度
	b->lc_ = a; a->parent_ = b;
	b->rc_ = b; c->parent_ = b; updateHeight(b); //更新节点b的高度

	return b; //返回该子树的新的根节点
}

template<typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> v) //v为非空 孙辈的节点
{
	BinNodePosi<T> p = v->parent_; BinNodePosi<T> g = p->parent_;  //视v,p和g相对位置分四种情况

	if (IsLChild(*p)) //zig
	{
		if (IsLChild(*v)) //zig-zig
		{
			p->parent_ = g->parent_;
			return connect34(v, p, g, v->lc_, v->rc_, p->rc_, g->rc_);
		}
		else //zig-zag
		{
			v->parent_ = g->parent_;
			return connect34(p, v, g, p->lc_, v->lc_, v->rc_, g->rc_);
		}
	}
	else //zag
	{
		if (IsLChild(*v)) //zag-zig
		{
			v->parent_ = g->parent_;
			return connect34(g, v, p, g->lc_, v->lc_, v->rc_, p->rc_);
		}
		else //zag-zag
		{
			p->parent_ = g->parent_;
			return connect34(g, p, v, g->lc_, p->lc_, v->lc_, v->rc_);
		}
	}
}
#endif
