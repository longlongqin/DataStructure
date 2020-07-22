#ifndef DSACPP_DINTREE_RECONSITUTION_H
#define DSACPP_DINTREE_RECONSITUTION_H
/*���������ع�*/
#include "BinTree.h"
#include "IncludedImplementCpp.h"
#include <vector>
using namespace std;


//1.����+����
template<typename T>
BinNode<T> buildBinTree1(vector<T> preOrder, vector<T> inOrder)
{
	return buildBinTree1(preOrder, 0, preOrder.size() - 1, inOrder, 0, inOrder.size());
}

template<typename T>
BinNode<T> buildBinTree1(vector<T> preOrder, int startPre, int endPre,
						vector<T> inOrder, int startIn, int endIn)
{
	if (startPre > endPre) //���������������е�  ��ʼ���>�������
		return NULL; //�򷵻�NULL

	BinNode<T> root = new BinNode<T>(preOrder[startPre]); //�������ڵ㣨���������еĵ�һ��Ԫ�ص�ֵ���Ǹ��ڵ��ֵ��

	//�������������ҵ����ڵ��λ��
	for (int i = startIn; i < endIn; ++i)
	{
		if(inOrder[i] == preOrder[startPre]) //���������е�������������Ԫ�ص�ֵ���Ǹ��ڵ��ֵ
			break;
	}

	//������������ÿһ�������������������ҵ��������ĸ��ڵ�
	root.lc_ = buildBinTree1(preOrder, startPre + 1, startPre + (i - startIn), inOrder, startIn, i - 1); //�ݹ�������������ҵ������ĸ��ڵ�
	root.rc_ = buildBinTree1(preOrder, (startPre + (i - startIn) + 1), endPre, inOrder, i + 1, endIn);   //�ݹ�������������ҵ������ĸ��ڵ�
	return root; //��󷵻������������ĸ��ڵ㣨֪�����ڵ㣬����BinNode��ĸ��ס����Һ��ӣ������Ƴ���������
}


//2. ����+����
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
	
	BinNode<T> root = new BinNode<T>(postOrder[endPost]); //���������е�ĩβԪ�ؾ���ԭ�������ĸ��ڵ��Ԫ��ֵ

	for (int i = startIn; i < endIn; ++i)
	{//�������������ҵ����ڵ��λ��
		if(postOrder[endPost] == inOrder[i])
			break;
	}
	//���������������������ҵ������������ȼ������У����еݹ鹹��
	root.lc_ = buildBinTree2(postOrder, startPost, startPost+(i-startIn)-1, inOrder, startIn, i - 1); //�ݹ�������������ҵ������ĸ��ڵ�
	root.rc_ = buildBinTree2(postOrder, ((startPost + (i - startIn) -1)+ 1), endPost, inOrder, i + 1, endIn); //�ݹ�������������ҵ������ĸ��ڵ�
	return root;
}

#endif
