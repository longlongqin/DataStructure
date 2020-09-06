#ifndef DSACPP_BTREE_BTREE_H_
#define DSACPP_BTREE_BTREE_H_
/*B-�� ��ģ����*/

#include <cmath> //ceil()
#include "BTNode.h"

template<class T>
class BTree
{
protected:
	int size_; //��Źؼ�������
	int order_; //B-���Ľ״Σ�����Ϊ3 ���� ����ʱָ��
	BTNodePosi<T> root_; //����
	BTNodePosi<T> hot_; //�����ʵķǿգ����� �������ڵ��λ��
	
	void solveOverflow(BTNodePosi<T>); //����������ķ��Ѵ���
	void solveUnderflow(BTNodePosi<T>); //��ɾ��������֮��ĺϲ�����

public:
	BTree(int order = 3) //���캯����Ĭ��Ϊ��͵�3��
		: order_(order), size_(0)
	{
		root_ = new BTNode<T>;
	}
	~BTree() //�����������ͷ����нڵ�
	{
		if (root_)
			release(root_);
	}

	const int order() { return order_ }; //����
	const int size() { return size_ }; //��ģ
	BTNodePosi<T>& root() (return root_); //����
	bool empty() { return !root_ }; //�п�

	BTNodePosi<T> search1(const T& e); //����
	bool insert1(const T& e); //����
	bool remove1(const T& e); //ɾ��
};


/**************************************����********************************************/
template<class T>
BTNodePosi<T> BTree<T>::search1(const T& e)
{
	BTNodePosi<T> v = root(); 	hot_ = nullptr; //�Ӹ��ڵ����
	while (v)
	{
		Rank r = v->key_.search(e); //�ڵ�ǰ�ڵ��У��ҵ�������e�����ؼ���
									//ע���˴���search()������ͷ�ļ���vector.h���еģ�
									//�ú���������ľ���˳����Ҳ�����e��Ԫ�ء������뿴��dsacpp��ԭ����룩��
		if ((r >= 0) && (v->key_[r] == e)) //�ɹ��ҵ��ùؼ���
			return v; //���ظùؼ������ڵĽڵ�
					  //���ùؼ���������ڵ�ľ���λ���� �ϲ���ù��̽�һ������ �ҵ��ġ��������ǲ��ù����ڸýڵ�ľ���λ�ã�
		else // ����δ���У���������һ���������
		{
			hot_ = v;
			v = v->child_[r + 1]; //ת���Ӧ������hot_ָ�������ĸ��ף�������Ҫ��I/O
		}
	}
	return NULL; //ʧ�ܣ����յִ��ⲿ�ڵ�
}


/**************************************����********************************************/
template<class T>
bool BTree<T>::insert1(const T& e)
{
	BTNodePosi<T> v = search1(e);
	if (v)  return false; //����Ѿ��鵽ԭ�����Ѿ����ڹؼ���e��
						  //���ա���ֹ�ؼ����ظ�ԭ�򡱣���ʱ�Ͳ����ٲ�����

	//(else)  ���search1(e)�Ľ��Ϊ�գ���˵��ԭ���в����ڹؼ���e�����Բ��롣
	//		  ��ʱ����Ȼ���ص����ⲿ�ڵ�v�������丸�ڵ�Ҳ�Ѿ�����¼�����˼�hot_
	Rank r = hot_->key_.search(e); //�ڽڵ�hot_������ؼ����в��Һ�ʱ�Ĳ���λ��
	hot_->key_.insert(r + 1, e); //���¹ؼ��������Ӧ��λ��
	hot_->child_.insert(r + 2, nullptr); //����һ��������ָ��

	size_++; //����ȫ����ģ
	solveOverflow(hot_); //������������������Ҫ����
	
	return true; //����ɹ�
}
template<typename T>
void BTree<T>::solveOverflow(BTNodePosi<T> v)
{
	if (order() >= v->key_.size()) return; //�ݹ������ǰ�ڵ㲢δ����

	Rank s = order_ / 2; //��㣨��ʱӦ�� order_ = v.size() = child_.size() -1��
	BTNodePosi<T> u = new BTNode<T>(); //ע�⣺�½ڵ�����һ���պ���

	//�������ý�����Ҳ�Ĺؼ���һ�����һ���½ڵ�u
	for (Rank i = 0; i < order_ - s - 1; i++) //v�Ҳ��order_-s-1�����Ӽ��ؼ��� ����Ϊ�Ҳ�ڵ�u
	{
		u->child_.insert(i, v->child_.remove(s + 1));
		u->key_.insert(i, v->key_.remove(s + 1));
	}
	u->child_.insert(order_ - s - 1, v->child_.remove(s + 1)); //�ƶ�v�����Һ���

	if (u->child_[0]) //���u�ĺ����Ƿǿգ���
		for (Rank j = 0; j < order_ - s; j++)
			u->child_[j].parent_ = u; //�����ǵĸ��׽ڵ�ͬһָ��u

	// �����ڽ�v�ڵ����㣨��������㣩��ʼ���Ҳ�ؼ��� ����½ڵ�u��ͬʱ��Ҳ����Щ�ؼ���ӽڵ�v��remove����
	// ���ԣ�����Ҫ���½��ڵ�����ʾv�е��ܵ����ؼ�������
	BTNodePosi<T> p = v->parent_; //pΪv�ڵ㵱ǰ�ĸ���
	if (!p) //���p�գ���ʱ��Ӧһֱ���紫������������Ϊ�����ĸ���Ϊ�գ����򴴽�֮
	{
		root_ = p = new BTNode<T>();
		p->child_[0] = v;
		v->parent_ = p;
	}
	Rank r = 1 + p->key_.search(v->key_[0]); // p��ָ��u��ָ�����(��Ϊpʵ���Ͼ������ؼ�������֮�����ڵĽڵ㣩
											 // ���ԣ���p->key_.search(v->key_[0])����ʾ��� ��ಿ�ֽڵ㣨��������remove������Ҳ�ؼ�����v����
											 // �ڽڵ�p�еĵڼ�����֧���� �����ȣ�
											 // Ȼ���� +1 �͵õ� ����Ҳಿ����ɵĽڵ㣨��������u����p�ڵ��еĵڼ�����֧���� �����ȣ�
	p->key_.insert(r, v->key_.remove(s)); //�����ؼ�������
	p->child_.insert(r + 1, u); //�½ڵ�u�븸�ڵ�p����

	
	solveOverflow(p); //����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)��
}


/**************************************ɾ��********************************************/
template<class T>
bool BTree<T>::remove1(const T& e)
{
	BTNodePosi<T> v = search1(e); if (!v) return false; //������ʧ��ʱ��˵��ԭ�����������ڸùؼ���
	
	Rank r = v->key_.search(e); //�ҵ��ؼ���e�ڽڵ�v�е���
	if (v->child_[0]) //��v��Ҷ�ӽڵ㣬��e�ĺ�̱�����ĳ��Ҷ�ڵ�
	{
		BTNodePosi<T> u = v->child_[r + 1]; //����������һֱ���󣬼���
		while (u->child_[0])
			u = u->child_[0]; //�ҳ�e�ĺ��
		v->key_[r] = u->key_[0]; v = u; r = 0; // ����֮����
	} //���ˣ�v��Ȼλ����ײ㣬�����е�r���ؼ�����Ǵ�ɾ����

	v->key_.remove(r); v->child_.remove(r + 1); --size_; //ɾ��e���Լ����������ⲿ�ڵ�֮һ

	solveUnderflow(v); //���б�Ҫ����Ҫ����ת��ϲ�
	return true;
}

template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi<T> v)
{
	if (ceil(order_ / 2) - 1 <= v->key_.size()) //�ݹ������ǰ�ڵ㲢δ����
		return;		//���е�ceil(float arg)���������㲻С��arg����С����ֵ

	BTNodePosi<T> p = v->parent_;
	if (!p) //�ݹ����v�ѵ����ڵ㣬û�к������ޣ�ֻ�豣֤���ڵ�ؼ���������һ�����ɣ���p�Ǹ��ڵ�v�ĸ��ף�������Ϊ��	
	{
		if (!v->key_.size() && v->child_[0]) //���ԣ�Ҫʹ���ڵ����磬��ֻ���Ǹ��ڵ���һ���ؼ��붼û�У��������У�Ψһ�أ��ǿպ���
		{
			root_ = v->child_[0]; root_->parent_ = nullptr; //��ʱ��ֻ�轫���²�ǿպ�������Ϊ������
			v->child_[0] = nullptr; release(v); //����ԭ���ĸ��ڵ�ɾ�������٣�
		}
		return;
	}//�����߶Ƚ���һ��


	Rank r = 0; while (p->child_[r] != v) ++r; //ȷ��v��p�ĵ�r������ ���� ��ʱv���ܲ����ؼ��룬���Բ���ͨ���ؼ������

	//���1�������ֵܽӹؼ��루������
	if(r>0) //��v����p�ĵ�һ�����ӣ���ʱ�������ֵܣ�����
	{
		BTNodePosi<T> ls = p->child_[r - 1]; //v�����ֵܱش���
		if (ceil(order_ / 2) =< ls->key_.size())//�����ֵ��㹻���֡�������ؼ����Ǵ�����͹ؼ������ģ�
		{
			v->key_.insert(0, p->key_[r - 1]); //��p���һ���ؼ����v
			p->key_[r - 1] = ls->key_.remove(ls->key_.size() - 1); //����ls�����ؼ���ת��p
			//ͬʱ��ls���ķ�֧һ��ת��ȥ
			v->child_.insert(0, ls->child_.remove(ls->child_.size() - 1)); 
			if (v->child_[0]) v->child_[0].parent_ = v;

			return; //���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
		}
	} //���ˣ����ֵ�ҪôΪ�գ�Ҫô̫��

	//���2�������ֵܽӹؼ��루������
	if (r < p->(child_.size() + 1)) //��v����p�����һ�����ӣ���ʱ�������ֵܣ�,
	{
		BTNodePosi<T> rs = p->child_[r + 1]; //�ҵ���v���ڵ����ֵ�
		if (ceil(order_ / 2) =< rs->child_.size()) //�����ֵ��㹻���֡�������ؼ����Ǵ�����͹ؼ������ģ�
		{
			v->key_.insert(v->key_.size(), p->key_[r]); //��p���һ���ؼ����v
			p->key_[r] = rc.key_.remove(0); //����rs����С�ؼ���ת��p
			//ͬʱ��rs��һ���ķ�֧һ��ת��ȥ
			v->child_.insert(v->child_.size(), rc.child_.remove(0));
			if (v->child_[v->child_.size() - 1]) v->child_[v->child_.size() - 1] = v;

			return; //���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
		}
	}//���ˣ����ֵ�ҪôΪ�գ�Ҫô̫��

	//���3�������ֵ�ҪôΪ�գ���������ͬʱ����Ҫô��̫���ݡ� ������������Ҫ���� �ϲ�
	if (r > 0) //�����ֵܺϲ�
	{
		BTNodePosi<T> ls = p->child_[r + 1]; //���ֵܣ���Ȼ���ڣ�
		ls->key_.insert(ls->key_.size(), p->key_.remove(r - 1)); p->child_.remove(r); //p�ĵ�r-1���ؼ���ת��ls,v������p�ĵ�r������
		
		ls->child_.insert(ls->child_.size(), v->child_.remove(0)); //��v�������ķ�֧���̸�ls
		if (ls->child_.[ls->child_.size() - 1]) //v������ຢ�ӹ��̸�ls�����Ҳຢ��
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
		release(v); //�ͷ�v
	}
	else //�����ֵܺϲ�
	{
		BTNodePosi<T> rs = p->child_[r + 1]; //���ֵ�
		rs.key_.insert(0, p->key_.remove(r));	p->child_.remove(r);

		rs->child_.insert(0, v->child_.remove(v->child_.size() - 1));//��v�����Ҳ�ķ�֧���̸�rs
		if (rs->child_[0])	rs->child_[0].parent_ = rs;
		while (!v->key_.empty()) //Ȼ����ѭ���Ľ�vʣ��Ĺؼ���ͺ��ӣ�����ת��rs
		{
			rs->key_.insert(0, v->key_.remove(v->key_.size() - 1));
			rs->child_.insert(0, v->child_.remove(v->child_.size() - 1));
			if (rs->child_[0])
			{
				rs->child_[0] = rs;
			}
		}
		release(v); //�ͷ�v
	}

	solveUnderflow(p); //����һ�㣬���б�Ҫ��������ѡ�����������ݹ� O(logn)��

	return;
}
#endif
