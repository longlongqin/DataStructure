#ifndef DSACPP_BINTREE_BINTREE_H
#define DSACPP_BINTREE_BINTREE_H

#include "BinNode.h"
#include "StateJudge.h"

template<class T>
class BinTree
{
protected:
	int size_; BinNodePosi<T> root_; //规模、根节点
	virtual int updateHeight(BinNodePosi<T> x); //更新节点x 的高度
	void updateHeightAbove(BinNodePosi<T> x); //更新节点x及其祖先的高度

public:
	BinTree()
		: size_(0), root_(nullptr)
	{}
	~BinTree()
	{
		if (size_ > 0) remove(root_);
	}

	int size() const; //规模
	bool empty() const;	//判空
	BinNodePosi<T> root() const; //树根
	BinNodePosi<T> insertAsRoot(const T& e); //插入根节点
	BinNodePosi<T> insertAsLC(BinNodePosi<T> x, const T& e); //作为x的左孩子插入（假设原本无左孩子）
	BinNodePosi<T> insertAsRC(BinNodePosi<T> x, const T& e); //作为x的右孩子插入（假设原本右左孩子）
	BinNodePosi<T> attachAsLC(BinNodePosi<T> x, BinTree<T>*& t); //t作为x的左子树接入
	BinNodePosi<T> attachAsRC(BinNodePosi<T> x, BinTree<T>*& t); //t作为x的右子树接入
	int remove(BinNodePosi<T> x); //删除以 位置x处 为根的子树，返回被删除的子树的规模
	BinTree* secede(BinNodePosi<T> x); //将子树x从当前数中摘除，并将其转换为独立的子树

	template<typename VST>
	void travLevel(VST& visit); //层次遍历

	template<typename VST>
	void travPre(VST& visit);  //先序遍历

	template<typename VST>
	void travIn(VST& visit);	//中序遍历

	template<typename VST>
	void travPost(VST& visit);	//后序遍历

	void operator<(const BinTree<T>& t); //比较器
	bool operator== (const BinTree<T>& t); //判等器
};

#endif
