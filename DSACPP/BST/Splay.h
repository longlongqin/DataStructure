#ifndef DSACPP_BST_SPLAY_H_
#define DSACPP_BST_SPLAY_H_
/*��չ��ģ����*/

#include "BST.h"

template<class T>
class Splay : public BST<T>
{
protected:
	BinNodePosi<T> splay(BinNodePosi<T> v); //���ڵ�v��չ����

public:
	BinNodePosi<T>& search(const T& e); //���ң���д��
	BinNodePosi<T> insert(const T& e); //���루��д��
	bool remove(const T& e);	//ɾ������д��
};

/*********************************��չ�㷨��ʵ��***********************************/
template<typename NodePosi> //�ڽڵ�*p��*lc������Ϊ�գ����� ���������ӡ���ϵ
inline void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lc_ = lc;
	if (lc)
		lc->parent_ = p;
}

template<typename NodePosi> //�ڽڵ�*p��*rc������Ϊ�գ����� �������ң��ӡ���ϵ
inline void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->lc_ = rc;
	if (rc)
		rc->parent_ = p;
}

template<class T> //splay����չ�㷨���ӽڵ�v���������չ
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v)
{
	//����ʹ��˫����չ���������ҵ�v�ĸ���p���游g����ʱ��Ҫv�ڵ㲻�գ�
	if (v == nullptr)
		return nullptr;
	BinNodePosi<T> p = v->parent_;
	BinNodePosi<T> g = p->parent_;
	
	while (p && g) //��v��ÿһ��˫����չʱ��Ҫȷ��v��ÿһ�εĸ��ס��游�Ǵ��ڵ�
	{
		BinNodePosi<T> gg = g->parent_; //ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ����

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

		//���һ��˫����չ֮����Ҫ��*v��*gg������ϵ
		if (!gg)	v->parent_ = nullptr; //*v��ԭ�ȵ����游*gg�����ڣ���˵������ʱ*vӦΪ����
		else //����*gg�˺�Ӧ����*v��Ϊ��or�Һ���
		{
			(g == gg->lc_) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}

		updateHeight(g); updateHeight(p); updateHeight(v); //ÿ�ֶ�����һ�½ڵ�g��p��v�ĸ߶�
	} /*����Ϊֹ��˫����չ�������Ҵ�ʱ��g�ڵ�˵���null��p�п��ܴ���ԭ���ǣ�
	  * ��Ϊ��ʱ�Ѿ����˫����չ��Ҳ����˵��v����Ľڵ㲻���ٹ��ɡ�v,p,g���������ڵ��ˣ���ʱ
	  * ���Կ϶�����g�ڵ�϶��ǿյģ���p�ڵ��п��ܴ��ڣ�
	  * 1. �������v��������Ϊ��������ô��ʱp�Ǵ��ڵģ�
	  * 2. ���Ϊż������ôp�����ڣ���ʱv����������λ��
	  * ����ɿ���https://www.yuque.com/longlongqin/xkqqbk/xzo2yd#VIlCh
	  */
	if (p = v->parent_) //��p�ǿ��ǣ�����Ҫһ�� zig/zag
	{
		if (p->lc_ = v) //v��p��������
		{
			attachAsLChild(p, v->rc_);
			attachAsLChild(v, p);
		}
		else //v��p��������
		{
			attachAsRChild(p, v->lc_);
			attachAsLChild(v, p);
		}	
		updateHeight(p); updateHeight(v);
	}

	v->parent_ = nullptr; //���v���������������ĸ���Ϊ��
	return v;
} //����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ��һ���ϲ㺯����������


/*********************************����***********************************/
template<class T>
BinNodePosi<T>& Splay<T>::search(const T& e)
{
	BinNodePosi<T> p = searchIn(root_, e, hot_ = nullptr);
	
	root_ = splay(p ? p : hot_); //������ҳɹ�����p�ǿգ�ʧ�ܣ���pΪ��
	/*
	* 1. ���ҳɹ����򽫲��ҵ��Ľڵ㣬����splay()�㷨��������չ��������
	* 2. ����ʧ�ܣ��򽫲���ʧ�ܵ�hot_�ڵ㣬����splay()�㷨��������չ��������
	*/

	return root_;
} //������BST��ͬ�����۲��ҳɹ����_root��ָ����󱻷��ʵĽڵ�

/*********************************����***********************************/
template<class T>
BinNodePosi<T> Splay<T>::insert(const T& e)
{
	if(root_ == nullptr) //ԭ��Ϊ��ʱ
	{
		size_++;
		return root_ = new BinNode<T>(e);
	}
	if (e == search(e)) //�����Ҫ����Ĺؼ����Ѿ����ڣ���ֱ�ӷ���
		return root_; //��Ϊ����֮�󣬻������չ�����Ա����ҵĽڵ�ᱻ��չ�����ڵ㴦

	BinNodePosi<T> t = search(e); ++size_; //�����½ڵ�

	if (e > t->data_) //t��Ϊv������
	{
		BinNodePosi<T> v = new BinNode<T>(e); //�����µĸ��ڵ㣬�˸��ڵ���eΪ�ؼ�����½ڵ�v��Ϊ����
		t->parent_ = v;
		v->lc_ = t;
		v->rc_ = t->rc_;
		t->rc_ = nullptr;
	}
	else if (e < t->data_) //t��Ϊv���Һ��ӡ���������� e = t->data_����Ϊ��������if (e == search(e)) �С�
	{
		BinNodePosi<T> v = new BinNode<T>(e);
		t->parent_ = v;
		v->lc_ = t->lc_;
		v->rc_ = t;
		t->rc_ = nullptr;
	}

	updateHeightAbove(t); //����t�������ȣ�ʵ����ֻ��tһ�����ĸ߶�
	
	return root_; //�½ڵ�v��v���Ǹ��ڵ㣩��Ȼλ�ڸ��ڵ㴦
} //����e�Ƿ����ԭ���У�����ʱ����root_->data_ = e


/*********************************ɾ��***********************************/
template<class T>
bool Splay<T>::remove(const T& e)
{
	if (!root_ || e != search(e)->data_) //����Ϊ�� or Ŀ�겻���ڣ��򷵻�false
		return false;

	BinNodePosi<T> v = root_; //��search() ��ڵ�e�ѱ���չֵ����

	if (!root_->lc_) //���û�������������ֱ��ɾ��
	{
		root_ = root_->rc_;
		root_->parent_ = nullptr;
	}
	else if (!root_->rc_) //���û������������Ҳ��ֱ��ɾ��
	{
		root_ = root_->lc_;
		root_->parent_ = nullptr;
	}
	else //��������������
	{
		//����ʱ���������е����ԳƵģ��ڱ��β�����(�ڶ���) ��Ҳ������ʱ���������е���
		BinNodePosi < T> LTree = root_->lc_; LTree->parent_ = nullptr; //���ݴ�һ��������
		root_ = root_->rc_; //ԭ�����ڵ��¼��v��
		root_->parent_ = nullptr;

		search(e); //������eΪ�ؼ�����еڶ��β��ң��˴β��ұ�Ȼʧ�ܣ�
		//���ˣ�����������С�ڵ����չ�������ң�������ͬ�ڵ㣩���������ؿգ�����
		root_->lc_ = LTree; LTree->parent_ = root_; //ֻ�轫ԭ�������ӻ�ԭλ�ü���
	}

	release(v->data_); release(v); --size_; //�ͷŽڵ㡢���¹�ģ

	if (!root_) //�˺������ǿգ�������������ĸ߶�
		updateHeight(root_);

	return true; //���سɹ���־
} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false


#endif
