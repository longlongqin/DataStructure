#ifndef DSACPP_DINTREE_RECONSITUTION_H
#define DSACPP_DINTREE_RECONSITUTION_H
/*二叉树的重构*/
#include "BinTree.h"
#include "IncludedImplementCpp.h"
#include <vector>
using namespace std;


//1.先序+中序
template<typename T>
BinNode<T> buildBinTree1(vector<T> preOrder, vector<T> inOrder)
{
	return buildBinTree1(preOrder, 0, preOrder.size() - 1, inOrder, 0, inOrder.size());
}

template<typename T>
BinNode<T> buildBinTree1(vector<T> preOrder, int startPre, int endPre,
						vector<T> inOrder, int startIn, int endIn)
{
	if (startPre > endPre) //如果先序遍历序列中的  开始序号>结束序号
		return NULL; //则返回NULL

	BinNode<T> root = new BinNode<T>(preOrder[startPre]); //创建根节点（先序序列中的第一个元素的值即是根节点的值）

	//在中序序列中找到根节点的位置
	for (int i = startIn; i < endIn; ++i)
	{
		if(inOrder[i] == preOrder[startPre]) //中序序列中等于先序序列首元素的值就是根节点的值
			break;
	}

	//接下来就是在每一个左子树、右子树中找到该子树的根节点
	root.lc_ = buildBinTree1(preOrder, startPre + 1, startPre + (i - startIn), inOrder, startIn, i - 1); //递归遍历左子树，找到子树的根节点
	root.rc_ = buildBinTree1(preOrder, (startPre + (i - startIn) + 1), endPre, inOrder, i + 1, endIn);   //递归遍历右子树，找到子树的根节点
	return root; //最后返回整个二叉树的根节点（知道根节点，根据BinNode类的父亲、左右孩子，就能推出整棵树）
}


//2. 后序+中序
template<typename T>
BinNode<T> buildBinTree2(vector<T> postOrder, vector<T> inOrder)
{
	if (postOrder.size() == 0 || inOrder.size() == 0)	return NULL;

}

template<typename T>
BinNode<T> buildBinTree2(vector<T> postOrder, int startPost, int endPost,
	vector<T> inOrder, int startIn, int endIn)
{
	if (startPost > endPost || startIn > endIn)		return NULL;
	
	BinNode<T> root = new BinNode<T>(postOrder[endPost]); //后序序列中的末尾元素就是原二叉树的根节点的元素值

	for (int i = startIn; i < endIn; ++i)
	{//在中序序列中找到根节点的位置
		if(postOrder[endPost] == inOrder[i])
			break;
	}
	//接下来，从中序序列中找到左右子树长度及其序列，进行递归构造
	root.lc_ = buildBinTree2(postOrder, startPost, startPost+(i-startIn)-1, inOrder, startIn, i - 1); //递归遍历左子树，找到子树的根节点
	root.rc_ = buildBinTree2(postOrder, ((startPost + (i - startIn) -1)+ 1), endPost, inOrder, i + 1, endIn); //递归遍历右子树，找到子树的根节点
	return root;
}

#endif
