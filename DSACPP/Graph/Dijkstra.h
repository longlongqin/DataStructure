#ifndef DSACPP_GRAPH_DIJKSTRA_H_
#define DSACPP_GRAPH_DIJKSTRA_H_
/*参考：https://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html#:~:text=Dijkstra(%E8%BF%AA%E6%9D%B0%E6%96%AF%E7%89%B9,%E8%AE%BA%EF%BC%8C%E8%BF%90%E7%AD%B9%E5%AD%A6%E7%AD%89%E7%AD%89%E3%80%82*/

#include "Graph.h"

template <typename Tv, typename Te> //最短路径Dijkstra算法：适用于一般的有向图
void Graph<Tv, Te>::dijkstra(int s)
{ //assert: 0 <= s < n
	reset(); priority(s) = 0;

	for (int i =0; i<n_; i++) //共需引入n个顶点、n-1条边
	{
		Status(s) = VISITED;
		if (parent(s) != -1)
			type(parent(s), s); ////引入当前的s
		for(int j = firstNbr(s); j>-1; j = nextNbr(s,j)) //枚举s的所有邻居j
			if (Status(j) == UNDISCOVERED && priority(j) > (priority(s) + weight(s, j))) //对邻接顶点j做松弛（更新距离（权值））
			{////与Prim算法唯一的不同之处
				priority(j) = priority(s) + weight(s, j);
				parent(j) = s;
			}
		for (int shortest = INT_MAX, j = 0; j < n_; j++) //选出下一最近顶点
		{
			if (Status(j) == UNDISCOVERED && shortest > priority(j))
			{
				shortest = priority(j);
				s = j;
			}
		}
	}
} // 对于无向连通图，假设每一条边表示为方向互逆、权重相等的一对边

template <typename Tv, typename Te>
struct DijkstraPU ////针对Dijkstra算法的顶点优先级更新器
{
	virtual void operator() (Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v)) //对于uk每一尚未被发现的邻接顶点v，按Dijkstra策略
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v))  //做松弛
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v); //更新优先级（数）
				g->parent(v) = uk; //并同时更新父节点
			}
	}
};

#endif // !DSACPP_GRAPH_DIJKSTRA_H_
