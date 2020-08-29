#ifndef DSACPP_BST_BST_H_
#define DSACPP_BST_BST_H_
/*����������ģ����*/
#include "../BinTree/BinTree.h" //BinTree

template<class T>
class BST : public BinTree
{
public: //�����ӿڣ���virtual���Σ�ǿ��Ҫ����ż�����ࣨBST���֣����ݸ��ԵĹ��������д
	virtual BinNodePosi<T>& search(const T& e); //����
	virtual BinNodePosi<T> insert(const T& e); //����
	virtual bool remove(const T& e); //ɾ��

protected:
	BinNodePosi<T> hot_; // �����С��Ľڵ� �ĸ��ڵ�

	// �ں����γ̻��õ�����������ֻ�������Ȳ����塣
	BinNodePosi<T> connect34(BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>
		BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>); //���ա�3+4���ṹ������3���ڵ㼰�Ŀ�����
	BinNodePosi<T> rotateAt(BinNodePosi<T> x); //��x ���丸�ף���ͳһ����ת����
};

#endif
