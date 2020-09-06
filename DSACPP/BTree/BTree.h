#ifndef DSACPP_BTREE_BTREE_H_
#define DSACPP_BTREE_BTREE_H_
/*B-树 的模板类*/

#include <cmath> //ceil()
#include "BTNode.h"

template<class T>
class BTree
{
protected:
	int size_; //存放关键码总数
	int order_; //B-树的阶次，至少为3 —— 创建时指定
	BTNodePosi<T> root_; //树根
	BTNodePosi<T> hot_; //最后访问的非空（除非 空树）节点的位置
	
	void solveOverflow(BTNodePosi<T>); //因插入而上溢的分裂处理
	void solveUnderflow(BTNodePosi<T>); //因删除而下溢之后的合并处理

public:
	BTree(int order = 3) //构造函数：默认为最低的3阶
		: order_(order), size_(0)
	{
		root_ = new BTNode<T>;
	}
	~BTree() //析构函数：释放所有节点
	{
		if (root_)
			release(root_);
	}

	const int order() { return order_ }; //阶数
	const int size() { return size_ }; //规模
	BTNodePosi<T>& root() (return root_); //树根
	bool empty() { return !root_ }; //判空

	BTNodePosi<T> search1(const T& e); //查找
	bool insert1(const T& e); //插入
	bool remove1(const T& e); //删除
};


/**************************************查找********************************************/
template<class T>
BTNodePosi<T> BTree<T>::search1(const T& e)
{
	BTNodePosi<T> v = root(); 	hot_ = nullptr; //从根节点出发
	while (v)
	{
		Rank r = v->key_.search(e); //在当前节点中，找到不大于e的最大关键码
									//注：此处的search()函数是头文件“vector.h”中的，
									//该函数本身定义的就是顺序查找不超过e的元素【详情请看：dsacpp（原版代码）】
		if ((r >= 0) && (v->key_[r] == e)) //成功找到该关键码
			return v; //返回该关键码所在的节点
					  //（该关键码在这个节点的具体位置是 上层调用过程进一步查找 找到的。这里我们不用管它在该节点的具体位置）
		else // 否则（未命中），进入下一层继续查找
		{
			hot_ = v;
			v = v->child_[r + 1]; //转入对应子树（hot_指向子树的父亲）——需要做I/O
		}
	}
	return NULL; //失败：最终抵达外部节点
}


/**************************************插入********************************************/
template<class T>
bool BTree<T>::insert1(const T& e)
{
	BTNodePosi<T> v = search1(e);
	if (v)  return false; //如果已经查到原树中已经存在关键码e。
						  //按照“禁止关键码重复原则”，此时就不能再插入了

	//(else)  如果search1(e)的结果为空，则说明原树中不存在关键码e，可以插入。
	//		  此时，虽然返回的是外部节点v，但是其父节点也已经被记录下来了即hot_
	Rank r = hot_->key_.search(e); //在节点hot_的有序关键码中查找何时的插入位置
	hot_->key_.insert(r + 1, e); //将新关键码插入相应的位置
	hot_->child_.insert(r + 2, nullptr); //创建一个空子树指针

	size_++; //更新全树规模
	solveOverflow(hot_); //如果有上溢情况，则需要处理
	
	return true; //插入成功
}
template<typename T>
void BTree<T>::solveOverflow(BTNodePosi<T> v)
{
	if (order() >= v->key_.size()) return; //递归基：当前节点并未上溢

	Rank s = order_ / 2; //轴点（此时应有 order_ = v.size() = child_.size() -1）
	BTNodePosi<T> u = new BTNode<T>(); //注意：新节点已有一个空孩子

	//接下来该将轴点右侧的关键码一起组成一个新节点u
	for (Rank i = 0; i < order_ - s - 1; i++) //v右侧的order_-s-1个孩子及关键码 分裂为右侧节点u
	{
		u->child_.insert(i, v->child_.remove(s + 1));
		u->key_.insert(i, v->key_.remove(s + 1));
	}
	u->child_.insert(order_ - s - 1, v->child_.remove(s + 1)); //移动v最靠左的右孩子

	if (u->child_[0]) //如果u的孩子们非空，则
		for (Rank j = 0; j < order_ - s; j++)
			u->child_[j].parent_ = u; //令他们的父亲节点同一指向u

	// 由于在将v节点从轴点（不包含轴点）开始的右侧关键码 组成新节点u的同时，也将这些关键码从节点v中remove掉了
	// 所以，不需要再新建节点来表示v中的周丹左侧关键码组了
	BTNodePosi<T> p = v->parent_; //p为v节点当前的父亲
	if (!p) //如果p空（此时对应一直上溢传播至树根，因为树根的父亲为空），则创建之
	{
		root_ = p = new BTNode<T>();
		p->child_[0] = v;
		v->parent_ = p;
	}
	Rank r = 1 + p->key_.search(v->key_[0]); // p中指向u的指针的秩(因为p实际上就是轴点关键码上升之后所在的节点）
											 // 所以，“p->key_.search(v->key_[0])”表示轴点 左侧部分节点（代码中是remove掉轴点右侧关键码后的v），
											 // 在节点p中的第几个分支（即 它的秩）
											 // 然后，再 +1 就得到 轴点右侧部分组成的节点（代码中是u）在p节点中的第几个分支（即 它的秩）
	p->key_.insert(r, v->key_.remove(s)); //将轴点关键码上溢
	p->child_.insert(r + 1, u); //新节点u与父节点p互联

	
	solveOverflow(p); //上升一层，如有必要则继续分裂——至多递归O(logn)次
}


/**************************************删除********************************************/
template<class T>
bool BTree<T>::remove1(const T& e)
{
	BTNodePosi<T> v = search1(e); if (!v) return false; //当查找失败时，说明原树根本不存在该关键码
	
	Rank r = v->key_.search(e); //找到关键码e在节点v中的秩
	if (v->child_[0]) //若v非叶子节点，则e的后继必属于某个叶节点
	{
		BTNodePosi<T> u = v->child_[r + 1]; //在右子树中一直向左，即可
		while (u->child_[0])
			u = u->child_[0]; //找出e的后继
		v->key_[r] = u->key_[0]; v = u; r = 0; // 并与之交换
	} //至此，v必然位于最底层，且其中第r个关键码就是待删除者

	v->key_.remove(r); v->child_.remove(r + 1); --size_; //删除e，以及其下两个外部节点之一

	solveUnderflow(v); //如有必要，需要做旋转或合并
	return true;
}

template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi<T> v)
{
	if (ceil(order_ / 2) - 1 <= v->key_.size()) //递归基：当前节点并未下溢
		return;		//其中的ceil(float arg)函数：计算不小于arg的最小整数值

	BTNodePosi<T> p = v->parent_;
	if (!p) //递归基：v已到根节点，没有孩子下限（只需保证根节点关键码最少有一个即可）。p是根节点v的父亲，所以它为空	
	{
		if (!v->key_.size() && v->child_[0]) //所以，要使根节点下溢，就只能是根节点中一个关键码都没有，但是它有（唯一地）非空孩子
		{
			root_ = v->child_[0]; root_->parent_ = nullptr; //此时，只需将其下层非空孩子设置为树根，
			v->child_[0] = nullptr; release(v); //并将原来的根节点删除（销毁）
		}
		return;
	}//整树高度降低一层


	Rank r = 0; while (p->child_[r] != v) ++r; //确定v是p的第r个孩子 —— 此时v可能不含关键码，所以不能通过关键码查找

	//情况1：向左兄弟接关键码（右旋）
	if(r>0) //当v不是p的第一个孩子（此时才有左兄弟），则
	{
		BTNodePosi<T> ls = p->child_[r - 1]; //v的左兄弟必存在
		if (ceil(order_ / 2) =< ls->key_.size())//若该兄弟足够“胖”（即其关键码是大于最低关键码数的）
		{
			v->key_.insert(0, p->key_[r - 1]); //则p借出一个关键码给v
			p->key_[r - 1] = ls->key_.remove(ls->key_.size() - 1); //并将ls的最大关键点转入p
			//同时将ls最后的分支一并转过去
			v->child_.insert(0, ls->child_.remove(ls->child_.size() - 1)); 
			if (v->child_[0]) v->child_[0].parent_ = v;

			return; //至此，通过右旋已完成当前层（以及所有层）的下溢处理
		}
	} //至此，左兄弟要么为空，要么太瘦

	//情况2：向右兄弟接关键码（左旋）
	if (r < p->(child_.size() + 1)) //当v不是p的最后一个孩子（此时才有右兄弟）,
	{
		BTNodePosi<T> rs = p->child_[r + 1]; //找到与v相邻的右兄弟
		if (ceil(order_ / 2) =< rs->child_.size()) //若该兄弟足够“胖”（即其关键码是大于最低关键码数的）
		{
			v->key_.insert(v->key_.size(), p->key_[r]); //则p借出一个关键码给v
			p->key_[r] = rc.key_.remove(0); //并将rs的最小关键点转入p
			//同时将rs第一个的分支一并转过去
			v->child_.insert(v->child_.size(), rc.child_.remove(0));
			if (v->child_[v->child_.size() - 1]) v->child_[v->child_.size() - 1] = v;

			return; //至此，通过左旋已完成当前层（以及所有层）的下溢处理
		}
	}//至此，右兄弟要么为空，要么太瘦

	//情况3：左、右兄弟要么为空（但不可能同时）；要么都太“瘦” ————则需要进行 合并
	if (r > 0) //与左兄弟合并
	{
		BTNodePosi<T> ls = p->child_[r + 1]; //左兄弟（必然存在）
		ls->key_.insert(ls->key_.size(), p->key_.remove(r - 1)); p->child_.remove(r); //p的第r-1个关键码转入ls,v不在是p的第r个孩子
		
		ls->child_.insert(ls->child_.size(), v->child_.remove(0)); //将v的最左侧的分支过继给ls
		if (ls->child_.[ls->child_.size() - 1]) //v的最左侧孩子过继给ls做最右侧孩子
			ls->child_[ls->child_.size() - 1] = ls;

		while (!v->key_.empty())
		{
			ls->key_.insert(ls->key_.size(), v->key_.remove(0)); 
			ls->child_.insert(ls->child_.size(), v->child_.remove(0));
			if (ls->child_[ls->child_.size() - 1])
			{
				ls->child_[ls->child_.size() - 1] = ls;
			}
		}
		release(v); //释放v
	}
	else //与右兄弟合并
	{
		BTNodePosi<T> rs = p->child_[r + 1]; //右兄弟
		rs.key_.insert(0, p->key_.remove(r));	p->child_.remove(r);

		rs->child_.insert(0, v->child_.remove(v->child_.size() - 1));//将v的最右侧的分支过继给rs
		if (rs->child_[0])	rs->child_[0].parent_ = rs;
		while (!v->key_.empty()) //然后在循环的将v剩余的关键码和孩子，依次转入rs
		{
			rs->key_.insert(0, v->key_.remove(v->key_.size() - 1));
			rs->child_.insert(0, v->child_.remove(v->child_.size() - 1));
			if (rs->child_[0])
			{
				rs->child_[0] = rs;
			}
		}
		release(v); //释放v
	}

	solveUnderflow(p); //上升一层，如有必要则继续分裂————至多递归 O(logn)层

	return;
}
#endif
