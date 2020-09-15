#ifndef DSACPP_BST_REDBLACK_H_
#define DSACPP_BST_REDBLACK_H_
/*红黑树*/

#include <algorithm> //std::max
#include "BST.h" //基于二叉搜索树实现的红黑树

template<class T>
class RedBlack : public BST<T>
{
protected:
	void solveDoubleRed(BinNodePosi<T> x); //双红修正
	void solveDoubleBlack(BinNodePosi<T> r); //双黑修正
	int updateHeight(BinNodePosi<T> x); //更新节点x的高度（这里指 黑高度）

public:
	BinNodePosi<T> insert(const T& e); //插入
	bool remove(const T& e); //删除
	//BST::search()等其余接口直接沿用
};

#define IsBlack(p)  (p->color == RB_BLACK || !p) //判断是否为黑节点（外部节点也视作黑节点）
#define IsRed(p)	(p->color == RB_RED)  //判断是否为红节点

//红黑树的高度更新的条件：当该节点的 左右子节点高度相同 并且 该节点的高度等于左（或右）孩子的高度（当该节点为黑节点时还需要+1） 的时候，不需要更新
/*
* 也就是说，更新条件为：
* 1. 或者左、右孩子的黑高度不等;
* 2. 或者作为红节点，黑高度与其孩子不相等;
* 3. 或者作为黑节点，黑高度不等于孩子的黑高度加一。
* 注意：下面的判断是否要更新， BlackHeightUpdated(x)为真说明，不需要更新。
*/
#define BlackHeightUpdated(x)	( (stature((x).rc_ == stature((x).lc_))) &&\
								 ((x).height_ == (IsRed(&x) ? stature(x).lc_ : stature(x).lc_) + 1))

//更新节点高度（黑高度）
template<class T>
int RedBlack<T>::updateHeight(BinNodePosi<T> x)
{
	x->height_ = std::max(stature(x->lc_), stature(x->rc_)); //孩子节点一般 黑高度 相等，除非出现 两孩子均为黑节点
	/*DSA*/// 红黑树中各节点左、右孩子的黑高度通常相等
    /*DSA*/// 这里之所以取更大值，是便于在删除节点后的平衡调整过程中，正确更新被删除节点父亲的黑高度
    /*DSA*/// 否则，rotateAt()会根据被删除节点的替代者（高度小一）设置父节点的黑高度
	return IsBlack(x) ? x->height_++ : x->height_; //若该节点是黑节点，则计入黑深度（即还需要+1）
} // 因统一定义stature(NULL) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较判断

/******************************插入********************************/
template<typename T>
BinNodePosi<T> RedBlack<T>::insert(const T& e)
{
	BinNodePosi<T>& x = search(e); 
	if (x)	return x; //如果，在原黑红树中找到了关键码e的节点，则立即返回
	x = new BinNode<T>(e, hot_, nullptr, nullptr, -1); //否则（原树中不存在关键码e），创建红节点x，以hot_为父，黑高度为-1
	solveDoubleRed(x); //经双红修正后，即可返回
	return x ? x : hot_->parent_;
} //无论e是否存在原树中，返回时总有 x->data_ == e

 /*
 * RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
 *    RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
 */
template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi<T> x)
{
	if (IsRoot(*x)) // 如果已经（递归）至树根，则将其转黑色，更新树高
	{
		root_->color_ = RB_BLACK;
		root_->height_++;
		return;
	}
	// 否则，x的父亲必然存在
	BinNodePosi<T> p = x->parent_; if (IsBlack(p))	return; //当p为黑色时，就无需在调整，因为没有出现“双红缺陷”
	
	BinNodePosi<T> g = p->parent_; //当p为红，则出现“双红缺陷”，此时x的祖父g必然存在，且g必为黑色
	BinNodePosi<T> u = uncle(x); //以下，根据x的叔父u的颜色分情况讨论：

	if (IsBlack(u)) //1. u为黑色(含null)时
	{
		if (IsLChild(*x) && IsLChild(*p)) //当x与p同一侧时（zig-zig或者zag-zag），则
			p->color_ = RB_BLACK; //p由红变黑，x保持红色不变
		else //当x与p异侧（zig-zag或者zag-zig）时，则
			x->color_ = RB_BLACK; //x由红变黑，p保持红色不变
		g->color_ = RB_RED; //g一定由黑变红，因为无论x与p的位置如何，他们做的都是与g交换颜色
		
		BinNodePosi<T> gg = g->parent_; //曾祖父
		BinNodePosi<T> r = FromParentTo(*g) = rotateAt(x); //“3+4”调整后的子树根节点
		r->parent_ = gg; //与原曾祖父连接
	}
	else //2. u为红色时
	{
		p->color_ = RB_BLACK; p->height_++; //p由红变黑（所以，高度+1）
		u->color_ = RB_BLACK; u->height_++; //u由红变黑（所以，高度+1）
		if (!IsRoot(*g)) g->color_ = RB_RED; //g非根节点，才可以将其转为红色
		solveDoubleRed(g); //等效地将g视为刚插入的节点（类似于尾递归，可优化为迭代形式）
	}
}

/******************************删除********************************/
template<typename T>
bool RedBlack<T>::remove(const T& e)
{
	BinNodePosi<T>& x = search(e); if (!x) return false; //确认目标存在（留意hot_的位置）
	BinNodePosi<T> r = removeAt(x, hot_);	if (!(--size_)) return true; //实施删除（r为删除x节点调整后，子树的树根）

	//assert： hot_的某一孩子被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要检查
	if (!hot_) // 当删除节点位于树根：则无论r颜色如何，只需将其置为黑色并更新黑高度即可。
	{
		root_->color_ = RB_BLACK; 
		updateHeight(root_); 
		return true;
	}
	else // 当删除的节点不在树根，则将x统一视作双分支节点，此时x的父亲p(hot_)存在
	{
		// 2.1 当x为红色时，则在摘除子树w，并将x替换为r之后，即可。
		/* 本来应该使用“if(IsRed(x))”来判断的，这里使用下面的if语句，其实是等价的：
		 * 因为，如果x是红色，那就肯定不用更新黑高度。反过来，不用更新黑高度的，说明x一定是红色（因为2.2、2.3是一定会更新的）
		 */
		if (BlackHeightUpdated(*hot_)) 
			return true;

		//2.2 当x为黑色，只要如图(b)所示r为红色，则如图(b')所示，
		//只需在删除操作之后将r翻转为黑色，亦可使得局部子树的黑高度复原。
		if (IsRed(r)) //这里之所以不用判断x是黑色，是因为上面的if语句，就是在x为红色时，才执行的。
		{
			r->color_ = RB_BLACK;
			r->height_++;
			return true;
		}

		// 2.3 x为黑色，r为黑色（此时出现，“双黑”）。
		// 此时，需用函数solveDoubleBlack()来解决双黑问题。
		solveDoubleBlack(r);
		return true;
	}
} //若目标节点存在 且被删除，返回true，否则返回false

template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi<T> r)
{
	BinNodePosi<T> p = r ? r->parent_ : hot_;  if (!p)	return; //r的父亲（如果p不存在，即r为树根。）
	/*问：为什么要判断r的父亲是否为空（p为空，表示r为根节点）？
	* 因为后面会有递归调用，有可能上升至树根处，所以需要判断是否为树根*/

	BinNodePosi<T> s = (r == p->lc_) ? p->rc_ : p->lc_; //s节点（r的兄弟）

	if (IsBlack(s)) //s为黑
	{
		BinNodePosi<T> t = nullptr; //s的红孩子（若左、右孩子，左者优先；皆黑时，为nullptr）
		if (IsRed(s->rc_))	t = s->rc_; //t是右孩子
		if (IsRed(s->lc_))	t = s->lc_; //t是左孩子

		if (t) //黑s 有 红孩子	BB-1
		{
			RBColor oldcolor = p->color_; //备份原子树根节点p的颜色，并对t及其父亲、祖先
			//以下，通过旋转重平衡，并将新子树的左右孩子染黑色
			BinNodePosi<T> b = FromParentTo(*p) = rotateAt(t); //旋转
			if (HasLChild(*b))
			{
				b->lc_->color_ = RB_BLACK;
				updateHeight(b->lc_); 
			}
			if (HasRChild(*b))
			{
				b->rc_->color_ = RB_BLACK;
				updateHeight(b->rc_);
			}

			b->color_ = oldcolor; // b继承p的颜色（即，新子树根节点 继承 原子树根节点的颜色）
		}
		else //黑s 无 红孩子
		{
			s->color_ = RB_RED; s->height_--; //s变为红色
			if (IsRed(p)) //BB-2R
			{
				p->color_ = RB_BLACK; //p转黑，但黑色高度不变（因为s由黑变红，p由红变黑）
			}
			else //BB-2B
			{
				p->height_--; //p还是黑色，但是其黑高度减一（因为s由黑变红）
				solveDoubleBlack(p); //递归上溯
			}
		}	
	}
	else //s为红色：BB-3
	{
		s->color_ = RB_BLACK; p->color_ = RB_RED; //s与p颜色互换（即：s由红转黑；p由黑转红）
		BinNodePosi<T> t = IsLChild(*s) ? s->lc_ : s->rc_; //取t 与其父亲s同侧

		hot_ = p; FromParentTo(*p) = rotateAt(t); //做zig或zag旋转

		solveDoubleBlack(r); //继续修正r处双黑---此时的p已经转红，故后续只能是BB-1或BB-2R
	}

}

#endif

