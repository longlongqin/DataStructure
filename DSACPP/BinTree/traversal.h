#ifndef DSACPP_BINTREE_TRAVERSAL_H
#define DSACPP_BINTREE_TRAVERSAL_H
#include "BinTree.h"
#include <stack>
#include <queue>

/******************************�������ݹ��*********************************/

//1.�������
template<typename T, typename VST> //Ԫ�����͡�������
void travPre_R(BinNodePosi<T> x, VST& visit) //��������������������棩
{
	if (!x) return; //�ݹ����������Ҷ�ӽڵ�ʱ���ݹ������
	visit(x->data_);
	travPre_R(x->lc_, visit); //�ݹ����������
	travPre_R(x->rc_, visit); //�ݹ����������
}

//2.�������
template<typename T, typename VST>//Ԫ�����͡�������
void travIn_R(BinNodePosi<T> x, VST& visit)
{
	if (!x) return; //�ݹ����������Ҷ�ӽڵ�ʱ���ݹ������
	travIn_R(x->lc_, visit);
	visit(x->data_);
	travIn_R(x->rc_, visit);
}

//3.�������
template<typename T, typename VST>//Ԫ�����͡�������
void travPost_R(BinNodePosi<T> x, VST& visit)
{
	if (!x)	return;
	travPost_R(x->lc_, visit);
	travPost_R(x->rc_, visit);
	visit(x->data_);
}

/******************************������������*********************************/

//1.����������汾1��
template<typename T, typename VST>
void travPre_I1(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S; //����ջ
	if (x) S.push(x); //���ڵ���ջ

	while (!S.empty()) //��ջ��֮ǰ����ѭ��
	{
		x = S.pop(); visit(x->data_); //���������ʵ�ǰ�ڵ㣬��ǿպ��ӵ���ջ����Ϊ�����Һ���
		//��ջ�������Һ��ӡ�������
		if(HasRChild(*x))
			S.push(x->rc_);
		if (HasLChild(*x))
			S.push(x->lc_);
	}
}

//1.����������汾2��
//�Զ����·��������ͨ·��;�ĸ����ڵ㡣
//ʹ�ø���ջ �����¼�����ͨ·�ϵĽڵ㣬�Ա�ȷ�����Ӧ�������Ե׶��ϵı�������
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi<T> x, VST& visit, std::stack<BinNodePosi<T>> S)
{
	while (x)
	{
		visit(x->data_); //���ʵ�ǰ�ڵ�
		if (!x->rc_)	S.push(x->rc_); //�Һ�����ջ�ݴ�
		x = x->lc_; //������֧����һ��
	}
}


//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template<typename T, typename VST>
void travPre_I2(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S;
	while (true)
	{
		visitAlongLeftBranch(x, visit, S); //�ӵ�ǰ�ڵ��������������
		if(S.empty())	break; //ջ����ֹͣ
		x = S.pop(); //������һ�������
	}
}

//2.����������汾1��
//��ǰ�ڵ���ջ���漴������֧���룬��ע�����ﻹû�з��ʣ�������ֱ��û������
template<typename T, typename VST>
static void goAlongLeftBranch(BinNodePosi<T> x, VST& visit, std::stack<BinNodePosi<T>> S)
{
	while (x)
	{
		S.push(x);
		if (x->lc_)
			x = x->lc_;
	}
}

template<typename T, typename VST>
void travIn_I1(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S;
	while (true)
	{
		goAlongLeftBranch(x, visit, S); //�ӵ�ǰ�ڵ������������ջ
		if (S.empty()) break; //ֱ�����нڵ㴦�����

		x = S.pop(); visit(x->data_); //����ջ��Ԫ�ز�����
		
		x = x->rc_; //ת��������
	}
}

//2.����������汾2��
template<typename T, typename VST>
void travIn_I2(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S;
	while (true)
	{
		if (x)
		{
			S.push(x); //���ڵ���ջ
			x = x->lc_; //�������������
		}
		else if (!S.empty())
		{
			x = S.pop(); visit(x); //��δ���ʵ�������Ƚڵ���ջ�����ʸýڵ�
			x = x->rc_; //�������ȵ�������
		}
		else
			break;  //ջ�գ���ʾ�������
	}
}

//2.����������汾3��
template<typename T, typename VST>
void travIn_I3(BinNodePosi<T> x, VST& visit) //���踨��ջ
{
	bool backtrack = false; //��ԭ����ջ �滻Ϊ ��־λbacktrack����־ǰһ���Ƿ�մ� ������ ����
	while (true)
	{
		if (backtrack == false && HasLChild(*x)) //����������� �� �ո�û�л���
		{
			x = x->lc_; //�������������
		}
		else //���� ���� �������� ���� �ո� ����
		{
			visit(x->data_); //���ʸýڵ�
			if (HasRChild(*x)) //����ýڵ�����������
			{
				x = x->rc_; //�� ��������������
				backtrack = false; //�� �رջ��ݱ�־
			}
			else //���û������������
			{
				x = x->succ(); //����
				if (!x) break; //�����ֱ�Ӻ��Ϊ�գ���ʾ��Ϊ ĩ�ڵ�
				backtrack = true; //�����û��ݱ�־
			}
		}
	}
}

//3.�������
template<typename T>
static void gotoHLVFL(std::stack<BinNodePosi<T>> S)
{
	while (BinNodePosi<T> x = S.top())
	{
		if (HasLChild(*x)) //�����ȣ������ܵ�����������ʱ��
		{
			if (HasRChild(*x)) S.push(x->rc_); //ͬʱ�����Һ���ʱ�����Һ�������ջ
			S.push(x->lc_); //Ȼ����������ջ
		}
		else //���û�����ӣ�
		{
			if (x->rc_)
				S.push(x->rc_); //Ȼ��Ӧ�����ܵ�����
		}
	}
}

template<typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S; //����ջ

	if (x)
		S.push(x); //���ȣ����ڵ���ջ
	while (!S.empty()) //��ջ����ʱ��
	{
		if (S.top() != x->parent_) //��ջ��Ԫ�ز��� ��ǰ�ڵ�ĸ��ڵ㣬���Ǳ�Ȼ�������ֵܣ����������Լ�������ڵ��ʱ�򣩣���
		{
			gotoHLVFL(S); // ת�������ֵ������������������ֵܣ����ҵ�HLVFL
		}
		//��ջ��Ԫ���ǵ�ǰ�ڵ�ĸ��ڵ� ���� �ҵ�HLVFL֮��
		x = S.pop(); //����ջ��Ԫ�أ���ջ��Ԫ��Ϊǰһ�ڵ��ֱ�Ӻ�̣�
		visit(x); //��������
	}
}

//��α�����������
template<typename T, typename VST> //Ԫ�����͡�������
void travLevel(BinNodePosi<T> x, VST& visit)
{
	std::queue<BinNodePosi<T>> Q; //��������
	Q.push(x); //���ڵ����
	
	while (!Q.empty()) //���в���ʱ
	{
		x = Q.pop();  //ȡ�����׽ڵ�
		visit(x->data_); //������

		if(HasLChild(*x)) //��������ӣ����������
			Q.push(x->lc_);
		if(HasRChild(*x)) //������Һ��ӣ����������
			Q.push(x->rc_);	
	}
}
#endif
