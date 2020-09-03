#ifndef DSACPP_BST_SPLAY_H_
#define DSACPP_BST_SPLAY_H_
/*伸展树模板类*/

#include "BST.h"

template<class T>
class Splay : public BST<T>
{
protected:
	BinNodePosi<T> splay(BinNodePosi<T> v); //将节点v伸展至根

public:
	BinNodePosi<T>& search(const T& e); //查找（重写）
	BinNodePosi<T> insert(const T& e); //插入（重写）
	bool remove(const T& e);	//删除（重写）
};

/*********************************伸展算法的实现***********************************/
template<typename NodePosi> //在节点*p与*lc（可能为空）建立 “父（左）子”关系
inline void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lc_ = lc;
	if (lc)
		lc->parent_ = p;
}

template<typename NodePosi> //在节点*p与*rc（可能为空）建立 “父（右）子”关系
inline void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->lc_ = rc;
	if (rc)
		rc->parent_ = p;
}

template<class T> //splay树伸展算法：从节点v出发逐层伸展
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v)
{
	//由于使用双层伸展，所以先找到v的父亲p、祖父g（此时需要v节点不空）
	if (v == nullptr)
		return nullptr;
	BinNodePosi<T> p = v->parent_;
	BinNodePosi<T> g = p->parent_;
	
	while (p && g) //在v的每一次双层伸展时，要确保v的每一次的父亲、祖父是存在的
	{
		BinNodePosi<T> gg = g->parent_; //每轮之后*v都以原曾祖父（great-grand parent）为父亲

		if (IsLChild(*p)) //zig
		{
			if (IsLChild(*v)) //zig-zig
			{
				attachAsLChild(g, p->rc_);	attachAsRChild(p, g);
				attachAsLChild(p, v->rc_);	attachAsRChild(v, p);
			}
			else //zig-zag
			{
				attachAsLChild(p, v->rc_);	attachAsRChild(v, p);
				attachAsRChild(g, v->lc_);	attachAsLChild(v, g);
			}
		}
		else if (IsRChild(*p)) //zag
		{
			if (IsRChild(*v)) //zag-zag
			{
				attachAsRChild(g, p->lc_);	attachAsLChild(p, g);
				attachAsRChild(p, v->lc_);	attachAsLChild(v, p);
			}
			else //zag-zig
			{
				attachAsRChild(p, v->lc_);	attachAsLChild(v, p);
				attachAsLChild(g, v->rc_);	attachAsRChild(v, g);
			}
		}

		//完成一次双层伸展之后，需要将*v与*gg建立联系
		if (!gg)	v->parent_ = nullptr; //*v的原先的曾祖父*gg不存在，则说明，此时*v应为树根
		else //否则，*gg此后应该以*v作为左or右孩子
		{
			(g == gg->lc_) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}

		updateHeight(g); updateHeight(p); updateHeight(v); //每轮都更新一下节点g、p、v的高度
	} /*到此为止，双层伸展结束，且此时的g节点彼等于null，p有可能存在原因是：
	  * 因为此时已经完成双层伸展，也就是说，v上面的节点不能再构成“v,p,g”这三个节点了，此时
	  * 可以肯定的是g节点肯定是空的，而p节点有可能存在：
	  * 1. 如果当初v最初的深度为奇数，那么此时p是存在的；
	  * 2. 如果为偶数，那么p不存在，此时v就在树根的位置
	  * 具体可看：https://www.yuque.com/longlongqin/xkqqbk/xzo2yd#VIlCh
	  */
	if (p = v->parent_) //当p非空是，还需要一次 zig/zag
	{
		if (p->lc_ = v) //v是p的左子树
		{
			attachAsLChild(p, v->rc_);
			attachAsLChild(v, p);
		}
		else //v是p的右子树
		{
			attachAsRChild(p, v->lc_);
			attachAsLChild(v, p);
		}	
		updateHeight(p); updateHeight(v);
	}

	v->parent_ = nullptr; //最后，v是树根，所以它的父亲为空
	return v;
} //调整之后心术跟应为被伸展的节点，故返回该节点的位置一边上层函数更新树根


/*********************************查找***********************************/
template<class T>
BinNodePosi<T>& Splay<T>::search(const T& e)
{
	BinNodePosi<T> p = searchIn(root_, e, hot_ = nullptr);
	
	root_ = splay(p ? p : hot_); //如果查找成功，则p非空；失败，则p为空
	/*
	* 1. 查找成功，则将查找到的节点，调用splay()算法，将其伸展到树根；
	* 2. 查找失败，则将查找失败的hot_节点，调用splay()算法，将其伸展到树根；
	*/

	return root_;
} //与其它BST不同，无论查找成功与否，_root都指向最后被访问的节点

/*********************************插入***********************************/
template<class T>
BinNodePosi<T> Splay<T>::insert(const T& e)
{
	if(root_ == nullptr) //原树为空时
	{
		size_++;
		return root_ = new BinNode<T>(e);
	}
	if (e == search(e)) //如果将要插入的关键码已经存在，则直接返回
		return root_; //因为查找之后，会进行伸展，所以被查找的节点会被伸展到根节点处

	BinNodePosi<T> t = search(e); ++size_; //创建新节点

	if (e > t->data_) //t作为v的左孩子
	{
		BinNodePosi<T> v = new BinNode<T>(e); //插入新的根节点，此根节点以e为关键码的新节点v作为树根
		t->parent_ = v;
		v->lc_ = t;
		v->rc_ = t->rc_;
		t->rc_ = nullptr;
	}
	else if (e < t->data_) //t作为v的右孩子。【这里存在 e = t->data_，因为包含在了if (e == search(e)) 中】
	{
		BinNodePosi<T> v = new BinNode<T>(e);
		t->parent_ = v;
		v->lc_ = t->lc_;
		v->rc_ = t;
		t->rc_ = nullptr;
	}

	updateHeightAbove(t); //更新t及其祖先（实际上只有t一个）的高度
	
	return root_; //新节点v（v就是根节点）必然位于根节点处
} //无论e是否存在原树中，返回时总有root_->data_ = e


/*********************************删除***********************************/
template<class T>
bool Splay<T>::remove(const T& e)
{
	if (!root_ || e != search(e)->data_) //当树为空 or 目标不存在，则返回false
		return false;

	BinNodePosi<T> v = root_; //经search() 后节点e已被伸展值树根

	if (!root_->lc_) //如果没有左子树，则可直接删除
	{
		root_ = root_->rc_;
		root_->parent_ = nullptr;
	}
	else if (!root_->rc_) //如果没有右子树，则也可直接删除
	{
		root_ = root_->lc_;
		root_->parent_ = nullptr;
	}
	else //左右子树均存在
	{
		//先暂时将左子树切掉（对称的，在本次查找中(第二次) 你也可以暂时将右子树切掉）
		BinNodePosi < T> LTree = root_->lc_; LTree->parent_ = nullptr; //先暂存一下左子树
		root_ = root_->rc_; //原树根节点记录在v中
		root_->parent_ = nullptr;

		search(e); //还是以e为关键码进行第二次查找（此次查找必然失败）
		//至此，右子树中最小节点必伸展至根，且（因无雷同节点）其左子树必空，于是
		root_->lc_ = LTree; LTree->parent_ = root_; //只需将原左子树接回原位置即可
	}

	release(v->data_); release(v); --size_; //释放节点、更新规模

	if (!root_) //此后，若树非空，则需更新树根的高度
		updateHeight(root_);

	return true; //返回成功标志
} //若目标节点存在且被删除，返回true；否则返回false


#endif
