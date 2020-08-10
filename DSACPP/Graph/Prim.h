#ifndef DSACPP_GRAPH_PRIM_H_
#define DSACPP_GRAPH_PRIM_H_
//��С֧������prim�㷨

#include "Graph.h"
template <typename Tv, typename Te> //Prim�㷨��������ͨͼ�����߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
void Graph<Tv, Te>::prim(int s)
{ //assert: 0 <= s < n
	reset(); priority(s);
	for (int i = 0; i < n_; i++)
	{
		Status(s) = VISITED;
		if (parent(s) == -1)
			type(parent(s), s) = TREE;

		for (int j = firstNbr(s); j > -1; j = nextNbr(s, j))
		{
			if ((priority(j) > weight(s, j)) && (Status(j) == UNDISCOVERED))
			{
				priority(j) = weight(s, j);
				parent(j) = s;
			}
		}

		for (int shortest = INT_MAX, j = 0; j < n; j++)
		{
			if ((priority(j) < shortest) && (Status(j) == UNDISCOVERED))
			{
				shortest = priority(j);
				s = j;
			}
		}
	}
}

#endif
