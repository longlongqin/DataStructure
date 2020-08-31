#ifndef DSACPP_BST_AVL_H_
#define DSACPP_BST_AVL_H_
#include "BST.h"

template<class T>
class AVL : public BST<T>
{
public:
	BinNodePosi<T> insert(const T& e); //���루��д��
	bool remove(const T& e); //ɾ������д��
	// BST::search() ������ӿڿ�ֱ������
};

//�Խڵ��ƽ���Ե��ж�
#define Balanced(x)		(stature((x).lc_) == stature((x).rc_)) //����ƽ������
#define BalFac(x)		(stature(x).lc_ - stature(x).rc_)	//ƽ������
#define AvlBalanced(x)	(BalFac(x) <=1 && BalFac(x) >=- 1)	//AVLƽ������

//ͨ��g(x)�ڵ㣬�ҵ�p��v�ڵ�
/***************************************************************************
* g(x)��������ڵ������ʧ��������ߵĽڵ㣻
* p��Ϊg(x) �ĺ��ӣ�
* v��Ϊp�ĺ��ӣ���v�п�����x��ͬһ���ڵ㡿
****/
template<typename T>
BinNodePosi<T> tallerChild(BinNodePosi<T> g)
{
	if (stature(x->lc_) > stature(x->rc_)) //���
		return x->lc_;
	else if (stature(x->lc_) < stature(x->rc_)) //�Ҹ�
		return x->rc_;
	else if (stature(x->lc_) = stature(x->rc_)) //�ȸߣ��븸��x ͬ���ߣ�zig-zig���� zag-zag�����ȡ�ͬ��ʱ��ֻ��Ҫ�������ɻָ�ƽ�⡿
		return IsLChild(*x) ? x->lc_ : x->rc_;
}

//����
template<class T>
BinNodePosi<T> AVL<T>::insert(const T& e) 
{
	BinNodePosi<T>& x = search(e); if (x) return x; //���Ѱ�ҵ�e����x�ڵ���ڣ�����ô�Ͳ��ò����ˣ���Ϊ�Ѿ����ڣ�����ֱ�ӷ���
	BinNodePosi<T> xx = x = new BinNode<T>(e, hot_);  size_++;//�����½ڵ�x

	//��ʱ��x�ĸ���hot_�����ߣ������游�п���ʧ��
	for (BinNodePosi<T> g = hot_; g; g = g->parent_)
		if (!AvlBalanced(*g)) //�ҵ������ʧ��ڵ�g������á�3+4���㷨�����и��⣬�����������²���ԭ����
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //ʹ�á�FromParentTo(g*)����ʾ��g�ĸ��׽ڵ�ĺ���ָ�� �� ָ���������������ĸ��ڵ㣨�Ӷ����������²���ԭ���У�
			break;
		}
		else //����g��Ȼƽ�⣩����ֻ��򵥵�
		{
			updateHeight(g); //ֻ����g�ĸ߶ȣ���Ϊ��forѭ���У�����ÿ��ѭ��ֻ�������Լ���ѭ�����������ڵ�߶�Ҳ�����ˣ�����Ȼgδʧ�⣬������߶Ȼ����п������ӵġ�
		}
		
	return xx; //��󷵻��½ڵ��λ��
}

//ɾ��
template<class T>
bool AVL<T>::remove(const T& e)
{
	BinNodePosi<T>& x = search(e); if (!x) return false; //���û�ҵ�Ҫɾ���Ľڵ㣬�򷵻�false
	removeAt(x, hot_); --size_; //�Ȱ���BST����ɾ�������˺�ɾ���ڵ�ĸ��ס����Ⱦ��п���ʧ�⣩

	for (BinNodePosi<T> g = hot_; g; g = g->parent_)
	{
		if (!AvlBalanced(*g)) //һ������ʧ�⣬ʹ�á�3+4���㷨ʹ֮����
		{
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //����������������ԭ����
			//ע�⣬���ﲻҪ��break;������Ϊ�ֲ�����֮�����Ƚڵ��п��ܻ���ʧ��ģ�����Ҫѭ���Ŷ�ÿһ�������жϣ����ʧ��ͽ��临��
			updateHeight(g);
		}
	}
	return true; //ɾ���ɹ�
}

//��3+4���㷨
template<typename T>
BinNodePosi<T> BST<T>::connect34(BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c, BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3)
{
	//�ж�Tx�Ƿ���ڣ�����Ϊ����Tx�п���Ϊ����
	a->lc_ = T0; if (T0) T0->parent_ = a; 
	a->rc_ = T1; if (T1) T1->parent_ = a; updateHeight(a); //���½ڵ�a�ĸ߶�
	c->lc_ = T2; if (T2) T2->parent_ = c;
	c->rc_ = T3; if (T3) T3->parent_ = c; updateHeight(c); //���½ڵ�c�ĸ߶�
	b->lc_ = a; a->parent_ = b;
	b->rc_ = b; c->parent_ = b; updateHeight(b); //���½ڵ�b�ĸ߶�

	return b; //���ظ��������µĸ��ڵ�
}

template<typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> v) //vΪ�ǿ� �ﱲ�Ľڵ�
{
	BinNodePosi<T> p = v->parent_; BinNodePosi<T> g = p->parent_;  //��v,p��g���λ�÷��������

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
