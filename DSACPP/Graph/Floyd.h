#ifndef DSACPP_GRAPH_FLOYD_H_
#define DSACPP_GRAPH_FLOYD_H_
/*参考：https://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html#:~:text=Dijkstra(%E8%BF%AA%E6%9D%B0%E6%96%AF%E7%89%B9,%E8%AE%BA%EF%BC%8C%E8%BF%90%E7%AD%B9%E5%AD%A6%E7%AD%89%E7%AD%89%E3%80%82*/

typedef struct  
{
	char vertex[n]; //顶点表
	int edges[n][n]; // 邻接矩阵，可看做边表
	int n, e; //图中当前顶点数、变数
}MGraph;

void Floyd(MGraph G)
{
	int A[G.n][G.n];
	int path[G.n][G.n];

	for (int i = 0; i < G.n; i++) //初始化数组
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = G.edges[i][j];
			path[i][j] = -1;
		}
	}
	for (int k = 0; k < G.n; k++)
	{
		for (int i = 0; i < G.n; i++)
			for (int j = 0; j < G.n; j++)
			{//如果经过下标为k 顶点路径比原两点间路径更短，则将当前两点间权值设为更小者
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
			}
	}
}

#endif
