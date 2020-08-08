#ifndef DSACPP_GRAPH_BFS_H_
#define DSACPP_GRAPH_BFS_H_

//广度优先遍历算法
#include "Graph.h"
#include <queue>
#include <stack>

template<class Tv,class Te>
void Graph<Tv, Te>::bfs(int s)
{
	reset();
	int clock = 0;
	int v = s;

	do 
	{ //逐一检查所有顶点，
		if (UNDISCOVERED == Status(v)); //一旦遇到尚未发现的顶点
		BFS(v, clock); //即从该店出发启动一次BFS
	} while (s != (v = (++v % n_)));
}

template<class Tv, class Te>
void Graph<Tv,Te>::BFS(int v, int& clock)
{
	std::queue<int> Q; //引入辅助队列

	Status(v) = DISCOVERED; Q.push(v);  //初始化起点

	while (!Q.empty()) //在Q变空之前，不断
	{
		int v = Q.pop(); dTime(v) = ++clock; //取出队首元素
		for(int u = first)
	}
	
}


template<class Tv, class Te>
void Graph<Tv, Te>::bcc(int s)
{
	reset(); int clock = 0; int v = s; std::stack<int> S;
	do 
	{
		if (UNDISCOVERED == Status(v))
			BBC(v, clock, S);

	} while (s != (v = (++v % n_)));
	
}

#define hac(x) (fTime(x))
template<class Tv, class Te>
void Graph<Tv, Te>::BCC(int v, int& clock, std::stack<int>& S)
{
	hac(v) = dTime(v) = ++clock; Status(v) = DISCOVERED; S.push(v);

	for (int u = firstNbr(v); u > -1; u = nextNbr(v))
	{
		switch (Status(u))
		{
		case UNDISCOVERED:
			parent(u) = v; type(v, u) = TREE; BCC(u, clock, S);
			if (hac(u) < dTime(v))
				hac(v) = min(hac(v), hac(u));
			else (hac(u) >= dTime(v))
			{
				while (v != S.pop());
				S.push(v);
			}
			break;

		case DISCOVERED:
			type(v, u) = BACKWARD;
			if (u != parent(v))
				hac(v) = min(hac(v), dTime(u));
			break;

		default: //VISITED
			type(v, u) = (dTime(v) < dTime(u)) ? FORWORD : CROSS;
			break;
		}

		Status(v) = VISITED;
	}
}