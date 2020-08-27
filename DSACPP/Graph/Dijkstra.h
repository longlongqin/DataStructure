#ifndef DSACPP_GRAPH_DIJKSTRA_H_
#define DSACPP_GRAPH_DIJKSTRA_H_
/*�ο���https://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html#:~:text=Dijkstra(%E8%BF%AA%E6%9D%B0%E6%96%AF%E7%89%B9,%E8%AE%BA%EF%BC%8C%E8%BF%90%E7%AD%B9%E5%AD%A6%E7%AD%89%E7%AD%89%E3%80%82*/

#include "Graph.h"

template <typename Tv, typename Te> //���·��Dijkstra�㷨��������һ�������ͼ
void Graph<Tv, Te>::dijkstra(int s)
{ //assert: 0 <= s < n
	reset(); priority(s) = 0;

	for (int i =0; i<n_; i++) //��������n�����㡢n-1����
	{
		Status(s) = VISITED;
		if (parent(s) != -1)
			type(parent(s), s); ////���뵱ǰ��s
		for(int j = firstNbr(s); j>-1; j = nextNbr(s,j)) //ö��s�������ھ�j
			if (Status(j) == UNDISCOVERED && priority(j) > (priority(s) + weight(s, j))) //���ڽӶ���j���ɳڣ����¾��루Ȩֵ����
			{////��Prim�㷨Ψһ�Ĳ�֮ͬ��
				priority(j) = priority(s) + weight(s, j);
				parent(j) = s;
			}
		for (int shortest = INT_MAX, j = 0; j < n_; j++) //ѡ����һ�������
		{
			if (Status(j) == UNDISCOVERED && shortest > priority(j))
			{
				shortest = priority(j);
				s = j;
			}
		}
	}
} // ����������ͨͼ������ÿһ���߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�

template <typename Tv, typename Te>
struct DijkstraPU ////���Dijkstra�㷨�Ķ������ȼ�������
{
	virtual void operator() (Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v)) //����ukÿһ��δ�����ֵ��ڽӶ���v����Dijkstra����
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v))  //���ɳ�
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v); //�������ȼ�������
				g->parent(v) = uk; //��ͬʱ���¸��ڵ�
			}
	}
};

#endif // !DSACPP_GRAPH_DIJKSTRA_H_
