#ifndef DSACPP_BTREE_BTREE_H_
#define DSACPP_BTREE_BTREE_H_
/*多路搜索树：B-树（B树）*/
/* B树的节点 */


#include "../DSACPP/Vector.h"

template<class T> class BTNode; //为了使用BTNode，需要前置声明
template<class T> using BTNodePosi = BTNode<T>*; //节点位置

//B-树节点的模板类
template<class T>
class BTNode
{
	//为了简化，将类的成员变量设置为public
public:
	BTNodePosi<T> parent_; //父节点
	vector<T> key_; //关键码向量
	vector<BTNodePosi<T>> child_; //孩子向量（其长度总比key向量多一）

	//构造函数（注意：BTNode只能作为根节点创建，而且初始时有0个关键码和1个空孩子指针）
	BTNode()
	{
		parent_ = nullptr;
		child_.insert(0, nullptr);
	}
	BTNode(T e, BTNodePosi<T> lc = nullptr, BTNodePosi<T> rc = nullptr)
	{
		parent_ = nullptr; //作为根节点插入
		key_.insert(0, e); //只有一个关键码
		child_.insert(0, lc); child_.insert(1, rc); //两个孩子

		if (lc) lc->parent_ = this;
		if (rc)	rc->parent_ = this;
	}
};


#endif
