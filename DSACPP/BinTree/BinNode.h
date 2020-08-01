#ifndef DSACPP_BINTREE_BINNODE_H_
#define DSACPP_BINTREE_BINNODE_H_

template<class T>	class BinNode; //Ϊ��ʹ��BinNode�࣬��Ҫǰ������
template<typename T>	using BinNodePosi = BinNode<T>*; //�ڵ�λ��

#define stature(p)	((p)?(p->height):-1);	//�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��

typedef enum { RB_RED, RB_BLACK }	RBColor; //�ڵ���ɫ


template<class T>
class BinNode
{
private:
	T data_; //Ԫ��ֵ
	BinNodePosi parent_; BinNodePosi lc_; BinNodePosi rc_; //���׽ڵ㡢���ӡ��Һ��ӽڵ�
	int height_; //�߶�
	int npl_; //Null Path Length����ʽ�ѣ�Ҳ����ֱ����height���棩
	RBColor color_; //��ɫ���������

public:
//���캯��
	BinNode()
		: parent_(nullptr),lc_(nullptr),rc_(nullptr),height_(0),npl_(1),color_(RB_RED)
	{}

	BinNode(T e, BinNodePosi parent = nullptr, BinNodePosi lc = nullptr, BinNodePosi rc = nullptr,
		int height = 0, int npl = 1, RBColor color = RB_RED)
		: data_(e), parent_(parent), lc_(lc), rc_(rc), height_(height), npl_(npl), color_(color)
	{}

//�����ӿ�
	int size(); //ͳ�Ƶ�ǰ�ڵ������������Ե�ǰ�ڵ�Ϊ���������Ĺ�ģ

	//Լ�����ڲ����½ڵ�֮ǰ����ǰ�ڵ������󡢻� �� ����
	BinNodePosi insertAsLC(const T& e); // ��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi insertAsRC(const T& e); // ��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ�̣���������У�

	template<typename VST> void travLevel(VST&); // �����Ĳ�α���
	template<typename VST> void travPre(VST&);   // �������������
	template<typename VST> void travIn(VST&);	 // �������������
	template<typename VST> void travPost(VST&);  // �����ĺ������

//�Ƚ������б���
	bool operate < (const BinNode& bn) { return data_ < bn.data_ }
	bool operate == (const BinNode & bn) { return data_ == bn.data_ }

};

#endif
