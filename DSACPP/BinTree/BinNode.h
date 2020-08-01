#ifndef DSACPP_BINTREE_BINNODE_H_
#define DSACPP_BINTREE_BINNODE_H_

template<class T>	class BinNode; //为了使用BinNode类，需要前置声明
template<typename T>	using BinNodePosi = BinNode<T>*; //节点位置

#define stature(p)	((p)?(p->height):-1);	//节点高度（与“空树高度为-1”的约定相统一）

typedef enum { RB_RED, RB_BLACK }	RBColor; //节点颜色


template<class T>
class BinNode
{
private:
	T data_; //元素值
	BinNodePosi parent_; BinNodePosi lc_; BinNodePosi rc_; //父亲节点、左孩子、右孩子节点
	int height_; //高度
	int npl_; //Null Path Length（左式堆，也可以直接用height代替）
	RBColor color_; //颜色（红黑树）

public:
//构造函数
	BinNode()
		: parent_(nullptr),lc_(nullptr),rc_(nullptr),height_(0),npl_(1),color_(RB_RED)
	{}

	BinNode(T e, BinNodePosi parent = nullptr, BinNodePosi lc = nullptr, BinNodePosi rc = nullptr,
		int height = 0, int npl = 1, RBColor color = RB_RED)
		: data_(e), parent_(parent), lc_(lc), rc_(rc), height_(height), npl_(npl), color_(color)
	{}

//操作接口
	int size(); //统计当前节点后代总数，即以当前节点为根的子树的规模

	//约定，在插入新节点之前，当前节点尚无左、或 右 孩子
	BinNodePosi insertAsLC(const T& e); // 作为当前节点的左孩子插入新节点
	BinNodePosi insertAsRC(const T& e); // 作为当前节点的右孩子插入新节点
	BinNodePosi succ(); //取当前节点的直接后继（中序遍历中）

	template<typename VST> void travLevel(VST&); // 子树的层次遍历
	template<typename VST> void travPre(VST&);   // 子树的先序遍历
	template<typename VST> void travIn(VST&);	 // 子树的中序遍历
	template<typename VST> void travPost(VST&);  // 子树的后序遍历

//比较器、判别器
	bool operate < (const BinNode& bn) { return data_ < bn.data_ }
	bool operate == (const BinNode & bn) { return data_ == bn.data_ }

};

#endif
