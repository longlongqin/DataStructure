#ifndef DSACPP_BTREE_BTREE_H_
#define DSACPP_BTREE_BTREE_H_
/*��·��������B-����B����*/
/* B���Ľڵ� */


#include "../DSACPP/Vector.h"

template<class T> class BTNode; //Ϊ��ʹ��BTNode����Ҫǰ������
template<class T> using BTNodePosi = BTNode<T>*; //�ڵ�λ��

//B-���ڵ��ģ����
template<class T>
class BTNode
{
	//Ϊ�˼򻯣�����ĳ�Ա��������Ϊpublic
public:
	BTNodePosi<T> parent_; //���ڵ�
	vector<T> key_; //�ؼ�������
	vector<BTNodePosi<T>> child_; //�����������䳤���ܱ�key������һ��

	//���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ�룩
	BTNode()
	{
		parent_ = nullptr;
		child_.insert(0, nullptr);
	}
	BTNode(T e, BTNodePosi<T> lc = nullptr, BTNodePosi<T> rc = nullptr)
	{
		parent_ = nullptr; //��Ϊ���ڵ����
		key_.insert(0, e); //ֻ��һ���ؼ���
		child_.insert(0, lc); child_.insert(1, rc); //��������

		if (lc) lc->parent_ = this;
		if (rc)	rc->parent_ = this;
	}
};


#endif
