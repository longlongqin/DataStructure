#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_
/*
原文教程：https://www.cnblogs.com/skywang12345/p/3576373.html
*/

#include <iostream>
#include <cassert>
#include <iomanip>

//二叉树节点的定义
template<class T>
class BSTNode
{
private:
	T m_nodeValue; // 关键字(键值)
	BSTNode* m_left; //左孩子
	BSTNode* m_right;//右孩子
	BSTNode* m_parent; //双亲结点

public:
	BSTNode(T nodeValue, BSTNode* left, BSTNode* right, BSTNode* parent)
		: m_nodeValue{nodeValue}, m_left{left}, m_right{right}, m_parent{parent}
	{
	}
};

//二叉查找树的操作
template<class T>
class BSTree
{
private:
	BSTNode<T>* m_root; //根节点

private:
	//前、中、后序遍历
	void preOrderTravel(BSTNode<T>* tree) const;
	void inOrderTravel(BSTNode<T>* tree) const;
	void postOrderTravel(BSTNode<T>* tree) const;

	//查找树种，值为key的节点
	BSTNode<T>* recursionSearch(BSTNode<T>* root, T key); //递归方式查找
	BSTNode<T>* search(BSTNode<T>* root, T key);			//非递归方式查找

	//查找节点中的值最大、小 的键值
	T minimum(BSTNode<T>* tree);
	T maximum(BSTNode<T>* tree);

	//二叉查找树增加新节点
	void insert(BSTNode<T>*& tree, BSTNode<T>* z);

	//删除指定节点
	BSTNode<T>* remove(BSTNode<T>*& tree, BSTNode<T>* z);

	//销毁节点
	void destroy(BSTNode<T>*& tree);

	//打印二叉查找树(0：前序；1：中序；2：后序)
	void print(BSTNode<T>* tree, T key, int direction);

public:
	BSTree();
	~BSTree();

	//前、中、后序遍历
	void preOrderTravel();
	void inOrderTravel();
	void postOrderTravel();

	//查找树种，值为key的节点
	BSTNode<T>* recursionSearch(T key); //递归方式查找
	BSTNode<T>* search(T key);			//非递归方式查找

	//查找节点中最左、右 的键值
	T minimum();
	T maximum();

	//查找节点x的后继节点（数据值大于该结点的"最小结点"）
	BSTNode<T>* successorNode(BSTNode<T>* x);
	//查找节点x的前驱节点（数据值小于该结点的"最大结点"）
	BSTNode<T>* predecessorNode(BSTNode<T>* x);

	//二叉查找树增加新节点
	void insert(T key);

	//删除指定节点
	void remove(T key);

	//销毁节点
	void destroy();

	//打印二叉查找树(0：前序；1：中序；2：后序)
	void print();
};

//1
//2

template<class T>
void BSTree<T>::preOrderTravel(BSTNode<T>* tree) const
{
	if (tree != NULL)
	{
		std::cout << tree->m_nodeValue << ' ';
		preOrderTravel(tree->m_left);
		preOrderTravel(tree->m_right);
	}
}
template<class T>
void BSTree<T>::preOrderTravel()
{
	preOrderTravel(m_root);
}

template<class T>
void BSTree<T>::inOrderTravel(BSTNode<T>* tree) const
{
	if (tree != NULL)
	{
		inOrderTravel(tree->m_left);
		std::cout << tree->m_nodeValue << ' ';
		inOrderTravel(tree->m_right);
	}
}
template<class T>
void BSTree<T>::inOrderTravel()
{
	inOrderTravel(m_root);
}

template<class T>
void BSTree<T>::postOrderTravel(BSTNode<T>* tree) const
{
	if (tree!=NULL)
	{
		postOrderTravel(tree->m_left);
		postOrderTravel(tree->m_right);
		std::cout << tree->m_nodeValue << ' ';
	}
}
template<class T>
void BSTree<T>::postOrderTravel()
{
	postOrderTravel(m_root);
}


template<class T>
BSTNode<T>* BSTree<T>::recursionSearch(BSTNode<T>* root, T key)
{
	assert(root != NULL && "树为空，无法查找");

	if (key < root->m_nodeValue)
	{
		root = root->m_left;
		return recursionSearch(root, key);
	}
	else if (key > root->m_nodeValue)
	{
		root = root->m_right;
		return recursionSearch(root, key);
	}
	else if (key == root->m_nodeValue)
	{
		return root;
	}
}
template<class T>
BSTNode<T>* BSTree<T>::recursionSearch(T key)
{
	recursionSearch(m_root, key);
}

template<class T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* root, T key)
{
	assert(root != NULL && "树为空，无法查找");
	while (root!=NULL)
	{
		if (root->m_nodeValue == key)
			return root;
		else if (root->m_nodeValue > key)
			root = root->m_left;
		else if (root->m_nodeValue < key)
			root = root->m_right;
	}
}
template<class T>
BSTNode<T>* BSTree<T>::search(T key)
{
	search(m_root, key);
}

template<class T>
T BSTree<T>::minimum(BSTNode<T>* tree)
{
	assert(tree != NULL && "树为空，无法查找最左边的节点");
	while (tree->m_left !=NULL)
	{
		tree = tree->m_left;
	}
	return tree->m_nodeValue;
}
template<class T>
T BSTree<T>::minimum()
{
	minimum(m_root);
}

template<class T>
T BSTree<T>::maximum(BSTNode<T>* tree)
{
	assert(tree != NULL && "树为空，无法查找最左边的节点");
	while (tree!=NULL)
	{
		tree = tree->m_right;
	}
	return tree->m_nodeValue;
}
template<class T>
T BSTree<T>::maximum()
{
	maximum(m_root);
}

template<class T>
BSTNode<T>* BSTree<T>::successorNode(BSTNode<T>* x)
{
	//如果它的右孩子存在，则其右孩子就是它的后继
	if (x->m_right != NULL)
		return minimum(x->m_right);
	
	// 当其右孩子不存在时，分情况：
	// 1.当x是 一个左孩子时，它的后继节点为：其父节点
	// 2.x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
	BSTNode<T>* y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<class T>
BSTNode<T>* BSTree<T>::predecessorNode(BSTNode<T>* x)
{
	//如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最左结点"。
	if (x->m_left != NULL)
		return maximum(x->m_left);

	// 如果x没有左孩子。则x有以下两种可能：
	// 1.x是 "一个右孩子"，则"x的前驱结点"为 "它的父结点"。
	// 2.x是 "一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
	BSTNode<T>* y = x->m_parent;
	BSTNode<T>* y = x->parent;
	while ((y != NULL) && (x == y->left))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

template <class T>
void BSTree<T>::insert(BSTNode<T>*& tree, BSTNode<T>* z)
{
	BSTNode<T>* y = NULL;
	BSTNode<T>* x = tree;

	// 查找z的插入位置
	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->m_left;
		else
			x = x->m_right;
	}

	z->parent = y;
	if (y == NULL)
		tree = z;
	else if (z->key < y->key)
		y->m_left = z;
	else
		y->m_right = z;
}
template <class T>
void BSTree<T>::insert(T key)
{
	BSTNode<T>* z = NULL;

	// 如果新建结点失败，则返回。
	if ((z = new BSTNode<T>(key, NULL, NULL, NULL)) == NULL)
		return;

	insert(m_root, z);
}

template <class T>
BSTNode<T>* BSTree<T>::remove(BSTNode<T>*& tree, BSTNode<T>* z)
{
	BSTNode<T>* x = NULL;
	BSTNode<T>* y = NULL;

	if ((z->m_left == NULL) || (z->m_right == NULL))
		y = z;
	else
		y = successor(z);

	if (y->m_left != NULL)
		x = y->m_left;
	else
		x = y->m_right;

	if (x != NULL)
		x->parent = y->parent;

	if (y->parent == NULL)
		tree = x;
	else if (y == y->parent->m_left)
		y->parent->m_left = x;
	else
		y->parent->m_right = x;

	if (y != z)
		z->key = y->key;

	return y;
}
template <class T>
void BSTree<T>::remove(T key)
{
	BSTNode<T>* z, * node;

	if ((z = search(m_root, key)) != NULL)
		if ((node = remove(m_root, z)) != NULL)
			delete node;
}

template <class T>
void BSTree<T>::print(BSTNode<T>* tree, T key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			cout << setw(2) << tree->key << " is root" << endl;
		else                // tree是分支节点
			cout << setw(2) << tree->key << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->m_left, tree->key, -1);
		print(tree->m_right, tree->key, 1);
	}
}
template <class T>
void BSTree<T>::print()
{
	if (m_root != NULL)
		print(m_root, m_root->key, 0);
}

template <class T>
void BSTree<T>::destroy(BSTNode<T>*& tree)
{
	if (tree == NULL)
		return;

	if (tree->m_left != NULL)
		return destroy(tree->m_left);
	if (tree->right != NULL)
		return destroy(tree->m_right);

	delete tree;
	tree = NULL;
}

template <class T>
void BSTree<T>::destroy()
{
	destroy(m_root);
}


#endif