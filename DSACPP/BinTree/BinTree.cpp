#include "BinTree.h"
#include "IncludedImplementCpp.h"
#include "release.h"

//�߶ȸ���
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

//�ڵ����
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

//��������
template<typename T>
BinNodePosi<T> BinTree<T>::attachAsLC(BinNodePosi<T> x, BinTree<T>*& t)
{
	
	if (t->root_) //���������Ƿ�Ϊ��
	{
		x->lc_ = t->root_;
		x->lc_->parent_ = x; //����
	}
	updateHeightAbove(x);

	//�ͷ�ԭ��
	t->root_ = nullptr; t->size_ = 0; release(t); t = nullptr;

	return x; //���ؽ���λ��
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

//����ɾ��
template<typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi<T> x)
{
	if (!x)
		return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc_) + removeAt(x->rc_); //�ݹ��ͷ���������

	release(x->data_); release(x);  //�ͷű�ժ���ڵ㣬
	return n;	//������ɾ���ڵ�����
}

template<typename T> //ɾ���������� λ��x�� �������� ���ر�ɾ���ڵ����Ŀ
int BinTree<T>::remove(BinNodePosi<T> x) //assert��xΪ�������кϷ���λ��
{
	FromParentTo(*x) = nullptr; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x); //�������Ƚڵ�ĸ߶�
	
	int n = removeAt(x); size_ -= n; //ɾ������x�����¹�ģ��
	return n; //���ر�ɾ�������Ĺ�ģ
}


//��������
template<class T>
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x)
{
	FromParentTo(*x) = nullptr; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent_); //����ԭ�����������ȵĸ߶�

	BinTree<T>* s = new BinTree<T>(x->data_); //��������
	s->root_ = x;	x->parent_ = nullptr; //�������ڵ�Ϊx��x�ĸ���Ϊnullptr
	s->size_ = x->size_; //�����Ĺ�ģ
	this->size_ -= s->size_; //����ԭ���Ĺ�ģ
	return s; //��������������������������
}
