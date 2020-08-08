#ifndef DSACPP_GRAPH_BFS_H_
#define DSACPP_GRAPH_BFS_H_

//������ȱ����㷨
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
	{ //��һ������ж��㣬
		if (UNDISCOVERED == Status(v)); //һ��������δ���ֵĶ���
		BFS(v, clock); //���Ӹõ��������һ��BFS
	} while (s != (v = (++v % n_)));
}

template<class Tv, class Te>
void Graph<Tv,Te>::BFS(int v, int& clock)
{
	std::queue<int> Q; //���븨������

	Status(v) = DISCOVERED; Q.push(v);  //��ʼ�����

	while (!Q.empty()) //��Q���֮ǰ������
	{
		int v = Q.pop(); dTime(v) = ++clock; //ȡ������Ԫ��
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