#ifndef DSACPP_LIST_LISTNODE_H_
#define DSACPP_LIST_LISTNODE_H_

typedef int Rank;

template <typename T> class ListNode; //前向声明
template <typename T> using ListNodePosi = ListNode<T>*;

template<class T>
class ListNode
{
private:
	T data_;
	ListNodePosi<T> pred_; ListNodePosi<T> succ_; //前驱、后驱

public:
	//构造函数
	ListNode() {}; //针对header、trailer的构造
	ListNode(T e, ListNodePosi<T> pred = nullptr, ListNodePosi<T> succ = nullptr) //默认构造器
		: data_{ e }, pred_{ pred }, succ_{ succ } {}

	//操作接口
	ListNodePosi<T> insertAspred(T const& e); //紧靠当前节点之前插入新节点
	ListNodePosi<T>insertAsucc(T const& e);  //紧靠当前节点之后插入新节点

};
 
template<class T>
ListNodePosi<T> ListNode<T>::insertAspred(T const& e)
{
	ListNodePosi(T) node = new ListNode(e, pred_, this); //pred_是当前节点的前驱，this指向当前节点
	pred_->succ_ = node;
	pred_ = node;

	return node;
}

template<class T>
ListNodePosi<T> ListNode<T>::insertAsucc(T const& e)
{
	ListNodePosi(T) node = new ListNode(e, this, succ_);
	succ_->pred_ = node;
	succ_ = node;

	return node;
}

#endif
