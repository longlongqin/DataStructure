#ifndef DSACPP_BINTREE_BINTREE_H
#define DSACPP_BINTREE_BINTREE_H

#include "BinNode.h"
#include "StateJudge.h"

template<class T>
class BinTree
{
protected:
	int size_; BinNodePosi<T> root_; //��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi<T> x); //���½ڵ�x �ĸ߶�
	void updateHeightAbove(BinNodePosi<T> x); //���½ڵ�x�������ȵĸ߶�

public:
	BinTree()
		: size_(0), root_(nullptr)
	{}
	~BinTree()
	{
		if (size_ > 0) remove(root_);
	}

	int size() const; //��ģ
	bool empty() const;	//�п�
	BinNodePosi<T> root() const; //����
	BinNodePosi<T> insertAsRoot(const T& e); //������ڵ�
	BinNodePosi<T> insertAsLC(BinNodePosi<T> x, const T& e); //��Ϊx�����Ӳ��루����ԭ�������ӣ�
	BinNodePosi<T> insertAsRC(BinNodePosi<T> x, const T& e); //��Ϊx���Һ��Ӳ��루����ԭ�������ӣ�
	BinNodePosi<T> attachAsLC(BinNodePosi<T> x, BinTree<T>*& t); //t��Ϊx������������
	BinNodePosi<T> attachAsRC(BinNodePosi<T> x, BinTree<T>*& t); //t��Ϊx������������
	int remove(BinNodePosi<T> x); //ɾ���� λ��x�� Ϊ�������������ر�ɾ���������Ĺ�ģ
	BinTree* secede(BinNodePosi<T> x); //������x�ӵ�ǰ����ժ����������ת��Ϊ����������

	template<typename VST>
	void travLevel(VST& visit); //��α���

	template<typename VST>
	void travPre(VST& visit);  //�������

	template<typename VST>
	void travIn(VST& visit);	//�������

	template<typename VST>
	void travPost(VST& visit);	//�������

	void operator<(const BinTree<T>& t); //�Ƚ���
	bool operator== (const BinTree<T>& t); //�е���
};

#endif
