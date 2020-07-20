#ifndef DSACPP_BINTREE_TRAVERSAL_H
#define DSACPP_BINTREE_TRAVERSAL_H
#include "BinTree.h"
#include <stack>
#include <queue>

/******************************遍历：递归版*********************************/

//1.先序遍历
template<typename T, typename VST> //元素类型、操作器
void travPre_R(BinNodePosi<T> x, VST& visit) //二叉树先序遍历（迭代版）
{
	if (!x) return; //递归基（当到达叶子节点时，递归结束）
	visit(x->data_);
	travPre_R(x->lc_, visit); //递归遍历左子树
	travPre_R(x->rc_, visit); //递归遍历右子树
}

//2.中序遍历
template<typename T, typename VST>//元素类型、操作器
void travIn_R(BinNodePosi<T> x, VST& visit)
{
	if (!x) return; //递归基（当到达叶子节点时，递归结束）
	travIn_R(x->lc_, visit);
	visit(x->data_);
	travIn_R(x->rc_, visit);
}

//3.后序遍历
template<typename T, typename VST>//元素类型、操作器
void travPost_R(BinNodePosi<T> x, VST& visit)
{
	if (!x)	return;
	travPost_R(x->lc_, visit);
	travPost_R(x->rc_, visit);
	visit(x->data_);
}

/******************************遍历：迭代版*********************************/

//1.先序遍历（版本1）
template<typename T, typename VST>
void travPre_I1(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S; //辅助栈
	if (x) S.push(x); //根节点入栈

	while (!S.empty()) //在栈空之前反复循环
	{
		x = S.pop(); visit(x->data_); //弹出并访问当前节点，其非空孩子的入栈次序为“先右后左”
		//入栈次序：先右孩子、后左孩子
		if(HasRChild(*x))
			S.push(x->rc_);
		if (HasLChild(*x))
			S.push(x->lc_);
	}
}

//1.先序遍历（版本2）
//自顶向下访问最左侧通路沿途的各个节点。
//使用辅助栈 逆序记录最左侧通路上的节点，以便确定其对应右子树自底而上的遍历次序
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi<T> x, VST& visit, std::stack<BinNodePosi<T>> S)
{
	while (x)
	{
		visit(x->data_); //访问当前节点
		if (!x->rc_)	S.push(x->rc_); //右孩子入栈暂存
		x = x->lc_; //沿做分支深入一层
	}
}


//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template<typename T, typename VST>
void travPre_I2(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S;
	while (true)
	{
		visitAlongLeftBranch(x, visit, S); //从当前节点出发，逐批访问
		if(S.empty())	break; //栈空则停止
		x = S.pop(); //弹出下一批的起点
	}
}

//2.中序遍历（版本1）
//当前节点入栈后随即向左侧分支深入，（注意这里还没有访问），迭代直到没有左孩子
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
		goAlongLeftBranch(x, visit, S); //从当前节点出发，逐批入栈
		if (S.empty()) break; //直至所有节点处理完毕

		x = S.pop(); visit(x->data_); //弹出栈顶元素并访问
		
		x = x->rc_; //转向右子树
	}
}

//2.中序遍历（版本2）
template<typename T, typename VST>
void travIn_I2(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S;
	while (true)
	{
		if (x)
		{
			S.push(x); //根节点入栈
			x = x->lc_; //深入遍历左子树
		}
		else if (!S.empty())
		{
			x = S.pop(); visit(x); //尚未访问的最低祖先节点退栈；访问该节点
			x = x->rc_; //遍历祖先的右子树
		}
		else
			break;  //栈空，表示遍历完成
	}
}

//2.中序遍历（版本3）
template<typename T, typename VST>
void travIn_I3(BinNodePosi<T> x, VST& visit) //无需辅助栈
{
	bool backtrack = false; //将原辅助栈 替换为 标志位backtrack：标志前一步是否刚从 左子树 回溯
	while (true)
	{
		if (backtrack == false && HasLChild(*x)) //如果有左子树 且 刚刚没有回溯
		{
			x = x->lc_; //深入遍历左子树
		}
		else //否则 —— 无左子树 或者 刚刚 回溯
		{
			visit(x->data_); //访问该节点
			if (HasRChild(*x)) //如果该节点有右子树，
			{
				x = x->rc_; //则 深入右子树遍历
				backtrack = false; //并 关闭回溯标志
			}
			else //如果没有右子树，则
			{
				x = x->succ(); //回溯
				if (!x) break; //如果其直接后继为空，表示其为 末节点
				backtrack = true; //并设置回溯标志
			}
		}
	}
}

//3.后序遍历
template<typename T>
static void gotoHLVFL(std::stack<BinNodePosi<T>> S)
{
	while (BinNodePosi<T> x = S.top())
	{
		if (HasLChild(*x)) //（首先，尽可能的向左）有左孩子时，
		{
			if (HasRChild(*x)) S.push(x->rc_); //同时又有右孩子时，则右孩子先入栈
			S.push(x->lc_); //然后，左孩子再入栈
		}
		else //如果没有左孩子，
		{
			if (x->rc_)
				S.push(x->rc_); //然后，应尽可能的向右
		}
	}
}

template<typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit)
{
	std::stack<BinNodePosi<T>> S; //辅助栈

	if (x)
		S.push(x); //首先，根节点入栈
	while (!S.empty()) //当栈不空时，
	{
		if (S.top() != x->parent_) //若栈顶元素不是 当前节点的父节点，（那必然是其右兄弟（或者是它自己，如根节点的时候））则
		{
			gotoHLVFL(S); // 转向其右兄弟所在子树（包含右兄弟），找到HLVFL
		}
		//当栈顶元素是当前节点的父节点 或者 找到HLVFL之后
		x = S.pop(); //弹出栈顶元素（该栈顶元素为前一节点的直接后继）
		visit(x); //并访问它
	}
}

//层次遍历：迭代版
template<typename T, typename VST> //元素类型、操作器
void travLevel(BinNodePosi<T> x, VST& visit)
{
	std::queue<BinNodePosi<T>> Q; //辅助队列
	Q.push(x); //根节点入队
	
	while (!Q.empty()) //队列不空时
	{
		x = Q.pop();  //取出队首节点
		visit(x->data_); //并访问

		if(HasLChild(*x)) //如果有左孩子，则左孩子入队
			Q.push(x->lc_);
		if(HasRChild(*x)) //如果有右孩子，则左孩子入队
			Q.push(x->rc_);	
	}
}
#endif
