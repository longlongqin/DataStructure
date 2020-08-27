#ifndef DSACPP_GRAPH_KRUSKAL_H_
#define DSACPP_GRAPH_KRUSKAL_H_
/*参考于：《大话数据结构》P251*/

#include "GraphMatrix.h" //邻接矩阵
//对边集数组Edge结构定义
typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;

template<class Tv, class Te>
void MiniSpanTree_Krusal(GraphMatrix<Tv,Te> G)
{
	int n, m;

	Edge edges[G.e_]; //定义边集数组（它的数组长度应不小于原图G的边数）
	int parent[G.n_]; //定义 数组用来判断边与边是否形成环路

	bubbleSort(G); //将邻接矩阵转化G为边集数组edges，并按权由小到大排序（在这里选择 冒泡排序）

	for (int i = 0; i<G.n_; i++)
	{
		parent[i] = 0; //将数组元素初始化为0
	}

	for (int j = 0; j < G.e_; j++)
	{
		n = Find(parent, edges[j].begin);
		m = Find(parent, edges[j].end);
		if (n != m) //假如n与m不等，说明此边没有与现有生成树形成环路
		{
			parent[n] = m; //将此边的结尾顶点放入下标为起点的parent中，表示此顶点已经在生成树集合中
		}
	}
}

template<class Tv, class Te>
void bubbleSort(GraphMatrix<Tv, Te> G) /*邓俊辉《数据结构》P5*/
{
	bool sorted = false; //整体排序壁纸，首先假定尚未排序

	int n1 = G.E.size();
	while (sorted)
	{
		sorted = true; //假定已经排序
		for (int i = G.E; i < n1; i++)
		{
			if (G.E[i] > G.E[i+1])
			{
				swap(G.E[i], G.E[i + 1]);
				sorted = false;
			}
		}

		n1--; //此时，末尾元素必然就位，所以可以缩短待排序序列的长度
	}
}

int Find(int* parent, int f) /*查找 连线顶点 的尾部下标*/
{
	while (parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}
#endif
