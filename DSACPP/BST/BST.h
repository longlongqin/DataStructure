#ifndef DSACPP_BST_BST_H_
#define DSACPP_BST_BST_H_
/*二叉搜索树模板类*/
#include "../BinTree/BinTree.h" //BinTree

template<class T>
class BST : public BinTree
{
public: //基本接口，以virtual修饰，强制要求所偶派生类（BST变种）根据各自的规则对其重写
	virtual BinNodePosi<T>& search(const T& e); //查找
	virtual BinNodePosi<T> insert(const T& e); //插入
	virtual bool remove(const T& e); //删除

protected:
	BinNodePosi<T> hot_; // “命中”的节点 的父节点

	// 在后续课程会用到，这里暂且只声明，先不定义。
	BinNodePosi<T> connect34(BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>
		BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>); //按照“3+4”结构，连接3个节点及四棵子树
	BinNodePosi<T> rotateAt(BinNodePosi<T> x); //对x 及其父亲，做统一的旋转调整
};

#endif
