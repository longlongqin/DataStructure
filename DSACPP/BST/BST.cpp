#include "BST.h"

//����
template<class T>
BinNodePosi<T>& BST<T>::search(const T& e)  //��BST�в��ҹؼ���e
{
	return searchIn(root_, e, hot_ = nullptr); //����Ŀ��ڵ�λ�õ����ã��Ա�������롢ɾ������
}

template<class T>
static BinNodePosi<T>& searchIn(BinNodePosi<T>& v, const T& e, BinNodePosi<T>& hot)
{
	if ((e == v->data_) || !v) // �ݹ��
	{// ����e == v->data_��ʱ�����ҳɹ���
	 // ��v�ڵ�Ϊ��ʱ������ʧ��,Ҳ����һ��ֵ����ʱ��ֵΪnull��������ʹ�����ڱ����ԡ�
		return v->data_;
	}
	
	hot = v; //һ���������¼��ǰ�ڵ㣬Ȼ���������һ��ݹ�
	return searchIn((e > v.data_) ? v->rc_ : v->lc_, e, hot);
} //����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��


//����
template<class T>
BinNodePosi<T> BST<T>::insert(const T& e)
{
	BinNodePosi<T>& x = search(e); //���ң��ҳ�Ҫ�����λ��
	if (x) return x; //ȷ��Ŀ�겻���ڣ������hot_�����ã�[�������Ҫ�����ֵe����ԭ�����������б����ʹ��ڣ���ֱ�ӷ���]

	BinNode<T>* x1 = new BinNode<T>(e, hot_); //�����½ڵ㣬��eΪ�ؼ��룬��hot_Ϊ����

	//��ʼ�������ȵĸ߶ȣ��Լ��������Ĺ�ģ
	++size_;
	updateHeightAbove(x1); //�������ȵĸ߶�

	return x1; //�²���Ľڵ㣬��ΪҶ�ڵ�
} //����e�Ƿ������ԭ���У�����ʱ����x->data == e


// ɾ��
template<class T>
bool BST<T>::remove(const T& e)
{
	BinNodePosi<T>& x = search(e); if (!x) return false; //ȷ��Ҫɾ����Ŀ����ڣ�����hot_�����ã�
	removeAt(x, hot_);

	//���¶���������
	--size_;
	updateHeightAbove(hot_); //��Ϊx�ڵ㱻ɾ�������Դ��丸�ڵ㿪ʼ�����Ƚ��и߶ȸ���
	return true;

} //ɾ���ɹ�����ɷ���ֵָʾ

template<class T>
static BinNodePosi<T> removeAt(BinNodePosi<T>& x, BinNodePosi<T> hot)
{
	BinNodePosi<T> w = x; //ʵ�ʱ�ɾ���Ľڵ㣬��ֵͬx
	BinNodePosi<T> succ = nullptr; //ʵ�ʱ�ɾ���Ľڵ�ĺ�̽ڵ㣨����������еĺ�̽ڵ㣩

	//��������ۣ�1.��ɾ���Ľڵ�ֻ�� �Һ��ӡ����ӡ��޺��ӣ�2.���Һ��Ӿ�����
	if (!HasLChild(*x)) //1.1������������
		succ = x->rc_;  //��ֱ��*x�滻Ϊ��������x������Ҷ�ӽڵ㣬��ʱ��ֱ�Ӻ��Ϊ�գ�
	else if (!HasRChild(*x)) //1.2 ������������
		succ = x->lc_;       // ��ֱ�ӽ�*x�滻Ϊ��������x������Ҷ�ӽڵ㣬��ʱ��ֱ�Ӻ��Ϊ�գ�
	else // 2.��������������
	{
		w = w->succ(); //�ҵ�*x��ֱ�Ӻ��*w
		swap(x->data_, w->data_);

		BinNodePosi<T> u = w->parent_;
		((u == x) ? u->rc_ : u->lc_) = succ = w->rc_;
	}

	hot = w->parent_; //��¼��ɾ���ڵ�ĸ���
	if (succ) //�����ɾ���ڵ��ֱ�Ӻ�̴��ڣ���
	{//����ɾ���ڵ�w�ĸ��ڵ���w��ֱ�Ӻ������
		succ->parent_ = hot; //���ڵ�ȷ��
		succ = ((hot->lc_ == w) ? hot->lc_ : hot->rc_); //ȷ�������ӻ����Һ���
	}
		
	release(w); release(w->data_); //�ͷű�ժ���Ľڵ�
	return succ; //���ؽ�����
}