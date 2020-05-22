#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_
/*
ԭ�Ľ̳̣�https://www.cnblogs.com/skywang12345/p/3576373.html
*/

#include <iostream>
#include <cassert>
#include <iomanip>

//�������ڵ�Ķ���
template<class T>
class BSTNode
{
private:
	T m_nodeValue; // �ؼ���(��ֵ)
	BSTNode* m_left; //����
	BSTNode* m_right;//�Һ���
	BSTNode* m_parent; //˫�׽��

public:
	BSTNode(T nodeValue, BSTNode* left, BSTNode* right, BSTNode* parent)
		: m_nodeValue{nodeValue}, m_left{left}, m_right{right}, m_parent{parent}
	{
	}
};

//����������Ĳ���
template<class T>
class BSTree
{
private:
	BSTNode<T>* m_root; //���ڵ�

private:
	//ǰ���С��������
	void preOrderTravel(BSTNode<T>* tree) const;
	void inOrderTravel(BSTNode<T>* tree) const;
	void postOrderTravel(BSTNode<T>* tree) const;

	//�������֣�ֵΪkey�Ľڵ�
	BSTNode<T>* recursionSearch(BSTNode<T>* root, T key); //�ݹ鷽ʽ����
	BSTNode<T>* search(BSTNode<T>* root, T key);			//�ǵݹ鷽ʽ����

	//���ҽڵ��е�ֵ���С �ļ�ֵ
	T minimum(BSTNode<T>* tree);
	T maximum(BSTNode<T>* tree);

	//��������������½ڵ�
	void insert(BSTNode<T>*& tree, BSTNode<T>* z);

	//ɾ��ָ���ڵ�
	BSTNode<T>* remove(BSTNode<T>*& tree, BSTNode<T>* z);

	//���ٽڵ�
	void destroy(BSTNode<T>*& tree);

	//��ӡ���������(0��ǰ��1������2������)
	void print(BSTNode<T>* tree, T key, int direction);

public:
	BSTree();
	~BSTree();

	//ǰ���С��������
	void preOrderTravel();
	void inOrderTravel();
	void postOrderTravel();

	//�������֣�ֵΪkey�Ľڵ�
	BSTNode<T>* recursionSearch(T key); //�ݹ鷽ʽ����
	BSTNode<T>* search(T key);			//�ǵݹ鷽ʽ����

	//���ҽڵ��������� �ļ�ֵ
	T minimum();
	T maximum();

	//���ҽڵ�x�ĺ�̽ڵ㣨����ֵ���ڸý���"��С���"��
	BSTNode<T>* successorNode(BSTNode<T>* x);
	//���ҽڵ�x��ǰ���ڵ㣨����ֵС�ڸý���"�����"��
	BSTNode<T>* predecessorNode(BSTNode<T>* x);

	//��������������½ڵ�
	void insert(T key);

	//ɾ��ָ���ڵ�
	void remove(T key);

	//���ٽڵ�
	void destroy();

	//��ӡ���������(0��ǰ��1������2������)
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
	assert(root != NULL && "��Ϊ�գ��޷�����");

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
	assert(root != NULL && "��Ϊ�գ��޷�����");
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
	assert(tree != NULL && "��Ϊ�գ��޷���������ߵĽڵ�");
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
	assert(tree != NULL && "��Ϊ�գ��޷���������ߵĽڵ�");
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
	//��������Һ��Ӵ��ڣ������Һ��Ӿ������ĺ��
	if (x->m_right != NULL)
		return minimum(x->m_right);
	
	// �����Һ��Ӳ�����ʱ���������
	// 1.��x�� һ������ʱ�����ĺ�̽ڵ�Ϊ���丸�ڵ�
	// 2.x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
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
	//���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ����������������"��
	if (x->m_left != NULL)
		return maximum(x->m_left);

	// ���xû�����ӡ���x���������ֿ��ܣ�
	// 1.x�� "һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
	// 2.x�� "һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
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

	// ����z�Ĳ���λ��
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

	// ����½����ʧ�ܣ��򷵻ء�
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
		if (direction == 0)    // tree�Ǹ��ڵ�
			cout << setw(2) << tree->key << " is root" << endl;
		else                // tree�Ƿ�֧�ڵ�
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