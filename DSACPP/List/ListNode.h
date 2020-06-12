#ifndef DSACPP_LIST_LISTNODE_H_
#define DSACPP_LIST_LISTNODE_H_

typedef int Rank;

template <typename T> class ListNode; //ǰ������
template <typename T> using ListNodePosi = ListNode<T>*;

template<class T>
class ListNode
{
private:
	T data_;
	ListNodePosi<T> pred_; ListNodePosi<T> succ_; //ǰ��������

public:
	//���캯��
	ListNode() {}; //���header��trailer�Ĺ���
	ListNode(T e, ListNodePosi<T> pred = nullptr, ListNodePosi<T> succ = nullptr) //Ĭ�Ϲ�����
		: data_{ e }, pred_{ pred }, succ_{ succ } {}

	//�����ӿ�
	ListNodePosi<T> insertAspred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi<T>insertAsucc(T const& e);  //������ǰ�ڵ�֮������½ڵ�

};
 
template<class T>
ListNodePosi<T> ListNode<T>::insertAspred(T const& e)
{
	ListNodePosi(T) node = new ListNode(e, pred_, this); //pred_�ǵ�ǰ�ڵ��ǰ����thisָ��ǰ�ڵ�
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
