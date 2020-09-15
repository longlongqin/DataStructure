#ifndef DSACPP_BST_REDBLACK_H_
#define DSACPP_BST_REDBLACK_H_
/*�����*/

#include <algorithm> //std::max
#include "BST.h" //���ڶ���������ʵ�ֵĺ����

template<class T>
class RedBlack : public BST<T>
{
protected:
	void solveDoubleRed(BinNodePosi<T> x); //˫������
	void solveDoubleBlack(BinNodePosi<T> r); //˫������
	int updateHeight(BinNodePosi<T> x); //���½ڵ�x�ĸ߶ȣ�����ָ �ڸ߶ȣ�

public:
	BinNodePosi<T> insert(const T& e); //����
	bool remove(const T& e); //ɾ��
	//BST::search()������ӿ�ֱ������
};

#define IsBlack(p)  (p->color == RB_BLACK || !p) //�ж��Ƿ�Ϊ�ڽڵ㣨�ⲿ�ڵ�Ҳ�����ڽڵ㣩
#define IsRed(p)	(p->color == RB_RED)  //�ж��Ƿ�Ϊ��ڵ�

//������ĸ߶ȸ��µ����������ýڵ�� �����ӽڵ�߶���ͬ ���� �ýڵ�ĸ߶ȵ����󣨻��ң����ӵĸ߶ȣ����ýڵ�Ϊ�ڽڵ�ʱ����Ҫ+1�� ��ʱ�򣬲���Ҫ����
/*
* Ҳ����˵����������Ϊ��
* 1. �������Һ��ӵĺڸ߶Ȳ���;
* 2. ������Ϊ��ڵ㣬�ڸ߶����亢�Ӳ����;
* 3. ������Ϊ�ڽڵ㣬�ڸ߶Ȳ����ں��ӵĺڸ߶ȼ�һ��
* ע�⣺������ж��Ƿ�Ҫ���£� BlackHeightUpdated(x)Ϊ��˵��������Ҫ���¡�
*/
#define BlackHeightUpdated(x)	( (stature((x).rc_ == stature((x).lc_))) &&\
								 ((x).height_ == (IsRed(&x) ? stature(x).lc_ : stature(x).lc_) + 1))

//���½ڵ�߶ȣ��ڸ߶ȣ�
template<class T>
int RedBlack<T>::updateHeight(BinNodePosi<T> x)
{
	x->height_ = std::max(stature(x->lc_), stature(x->rc_)); //���ӽڵ�һ�� �ڸ߶� ��ȣ����ǳ��� �����Ӿ�Ϊ�ڽڵ�
	/*DSA*/// ������и��ڵ����Һ��ӵĺڸ߶�ͨ�����
    /*DSA*/// ����֮����ȡ����ֵ���Ǳ�����ɾ���ڵ���ƽ����������У���ȷ���±�ɾ���ڵ㸸�׵ĺڸ߶�
    /*DSA*/// ����rotateAt()����ݱ�ɾ���ڵ������ߣ��߶�Сһ�����ø��ڵ�ĺڸ߶�
	return IsBlack(x) ? x->height_++ : x->height_; //���ýڵ��Ǻڽڵ㣬��������ȣ�������Ҫ+1��
} // ��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�

/******************************����********************************/
template<typename T>
BinNodePosi<T> RedBlack<T>::insert(const T& e)
{
	BinNodePosi<T>& x = search(e); 
	if (x)	return x; //�������ԭ�ں������ҵ��˹ؼ���e�Ľڵ㣬����������
	x = new BinNode<T>(e, hot_, nullptr, nullptr, -1); //����ԭ���в����ڹؼ���e����������ڵ�x����hot_Ϊ�����ڸ߶�Ϊ-1
	solveDoubleRed(x); //��˫�������󣬼��ɷ���
	return x ? x : hot_->parent_;
} //����e�Ƿ����ԭ���У�����ʱ���� x->data_ == e

 /*
 * RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
 *    RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
 *    RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
 */
template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi<T> x)
{
	if (IsRoot(*x)) // ����Ѿ����ݹ飩������������ת��ɫ����������
	{
		root_->color_ = RB_BLACK;
		root_->height_++;
		return;
	}
	// ����x�ĸ��ױ�Ȼ����
	BinNodePosi<T> p = x->parent_; if (IsBlack(p))	return; //��pΪ��ɫʱ���������ڵ�������Ϊû�г��֡�˫��ȱ�ݡ�
	
	BinNodePosi<T> g = p->parent_; //��pΪ�죬����֡�˫��ȱ�ݡ�����ʱx���游g��Ȼ���ڣ���g��Ϊ��ɫ
	BinNodePosi<T> u = uncle(x); //���£�����x���常u����ɫ��������ۣ�

	if (IsBlack(u)) //1. uΪ��ɫ(��null)ʱ
	{
		if (IsLChild(*x) && IsLChild(*p)) //��x��pͬһ��ʱ��zig-zig����zag-zag������
			p->color_ = RB_BLACK; //p�ɺ��ڣ�x���ֺ�ɫ����
		else //��x��p��ࣨzig-zag����zag-zig��ʱ����
			x->color_ = RB_BLACK; //x�ɺ��ڣ�p���ֺ�ɫ����
		g->color_ = RB_RED; //gһ���ɺڱ�죬��Ϊ����x��p��λ����Σ��������Ķ�����g������ɫ
		
		BinNodePosi<T> gg = g->parent_; //���游
		BinNodePosi<T> r = FromParentTo(*g) = rotateAt(x); //��3+4����������������ڵ�
		r->parent_ = gg; //��ԭ���游����
	}
	else //2. uΪ��ɫʱ
	{
		p->color_ = RB_BLACK; p->height_++; //p�ɺ��ڣ����ԣ��߶�+1��
		u->color_ = RB_BLACK; u->height_++; //u�ɺ��ڣ����ԣ��߶�+1��
		if (!IsRoot(*g)) g->color_ = RB_RED; //g�Ǹ��ڵ㣬�ſ��Խ���תΪ��ɫ
		solveDoubleRed(g); //��Ч�ؽ�g��Ϊ�ղ���Ľڵ㣨������β�ݹ飬���Ż�Ϊ������ʽ��
	}
}

/******************************ɾ��********************************/
template<typename T>
bool RedBlack<T>::remove(const T& e)
{
	BinNodePosi<T>& x = search(e); if (!x) return false; //ȷ��Ŀ����ڣ�����hot_��λ�ã�
	BinNodePosi<T> r = removeAt(x, hot_);	if (!(--size_)) return true; //ʵʩɾ����rΪɾ��x�ڵ������������������

	//assert�� hot_��ĳһ���ӱ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����档���¼���Ƿ�ʧ�⣬������Ҫ���
	if (!hot_) // ��ɾ���ڵ�λ��������������r��ɫ��Σ�ֻ�轫����Ϊ��ɫ�����ºڸ߶ȼ��ɡ�
	{
		root_->color_ = RB_BLACK; 
		updateHeight(root_); 
		return true;
	}
	else // ��ɾ���Ľڵ㲻����������xͳһ����˫��֧�ڵ㣬��ʱx�ĸ���p(hot_)����
	{
		// 2.1 ��xΪ��ɫʱ������ժ������w������x�滻Ϊr֮�󣬼��ɡ�
		/* ����Ӧ��ʹ�á�if(IsRed(x))�����жϵģ�����ʹ�������if��䣬��ʵ�ǵȼ۵ģ�
		 * ��Ϊ�����x�Ǻ�ɫ���ǾͿ϶����ø��ºڸ߶ȡ������������ø��ºڸ߶ȵģ�˵��xһ���Ǻ�ɫ����Ϊ2.2��2.3��һ������µģ�
		 */
		if (BlackHeightUpdated(*hot_)) 
			return true;

		//2.2 ��xΪ��ɫ��ֻҪ��ͼ(b)��ʾrΪ��ɫ������ͼ(b')��ʾ��
		//ֻ����ɾ������֮��r��תΪ��ɫ�����ʹ�þֲ������ĺڸ߶ȸ�ԭ��
		if (IsRed(r)) //����֮���Բ����ж�x�Ǻ�ɫ������Ϊ�����if��䣬������xΪ��ɫʱ����ִ�еġ�
		{
			r->color_ = RB_BLACK;
			r->height_++;
			return true;
		}

		// 2.3 xΪ��ɫ��rΪ��ɫ����ʱ���֣���˫�ڡ�����
		// ��ʱ�����ú���solveDoubleBlack()�����˫�����⡣
		solveDoubleBlack(r);
		return true;
	}
} //��Ŀ��ڵ���� �ұ�ɾ��������true�����򷵻�false

template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi<T> r)
{
	BinNodePosi<T> p = r ? r->parent_ : hot_;  if (!p)	return; //r�ĸ��ף����p�����ڣ���rΪ��������
	/*�ʣ�ΪʲôҪ�ж�r�ĸ����Ƿ�Ϊ�գ�pΪ�գ���ʾrΪ���ڵ㣩��
	* ��Ϊ������еݹ���ã��п�����������������������Ҫ�ж��Ƿ�Ϊ����*/

	BinNodePosi<T> s = (r == p->lc_) ? p->rc_ : p->lc_; //s�ڵ㣨r���ֵܣ�

	if (IsBlack(s)) //sΪ��
	{
		BinNodePosi<T> t = nullptr; //s�ĺ캢�ӣ������Һ��ӣ��������ȣ��Ժ�ʱ��Ϊnullptr��
		if (IsRed(s->rc_))	t = s->rc_; //t���Һ���
		if (IsRed(s->lc_))	t = s->lc_; //t������

		if (t) //��s �� �캢��	BB-1
		{
			RBColor oldcolor = p->color_; //����ԭ�������ڵ�p����ɫ������t���丸�ס�����
			//���£�ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��ɫ
			BinNodePosi<T> b = FromParentTo(*p) = rotateAt(t); //��ת
			if (HasLChild(*b))
			{
				b->lc_->color_ = RB_BLACK;
				updateHeight(b->lc_); 
			}
			if (HasRChild(*b))
			{
				b->rc_->color_ = RB_BLACK;
				updateHeight(b->rc_);
			}

			b->color_ = oldcolor; // b�̳�p����ɫ���������������ڵ� �̳� ԭ�������ڵ����ɫ��
		}
		else //��s �� �캢��
		{
			s->color_ = RB_RED; s->height_--; //s��Ϊ��ɫ
			if (IsRed(p)) //BB-2R
			{
				p->color_ = RB_BLACK; //pת�ڣ�����ɫ�߶Ȳ��䣨��Ϊs�ɺڱ�죬p�ɺ��ڣ�
			}
			else //BB-2B
			{
				p->height_--; //p���Ǻ�ɫ��������ڸ߶ȼ�һ����Ϊs�ɺڱ�죩
				solveDoubleBlack(p); //�ݹ�����
			}
		}	
	}
	else //sΪ��ɫ��BB-3
	{
		s->color_ = RB_BLACK; p->color_ = RB_RED; //s��p��ɫ����������s�ɺ�ת�ڣ�p�ɺ�ת�죩
		BinNodePosi<T> t = IsLChild(*s) ? s->lc_ : s->rc_; //ȡt ���丸��sͬ��

		hot_ = p; FromParentTo(*p) = rotateAt(t); //��zig��zag��ת

		solveDoubleBlack(r); //��������r��˫��---��ʱ��p�Ѿ�ת�죬�ʺ���ֻ����BB-1��BB-2R
	}

}

#endif

