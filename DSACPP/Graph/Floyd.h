#ifndef DSACPP_GRAPH_FLOYD_H_
#define DSACPP_GRAPH_FLOYD_H_
/*�ο���https://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html#:~:text=Dijkstra(%E8%BF%AA%E6%9D%B0%E6%96%AF%E7%89%B9,%E8%AE%BA%EF%BC%8C%E8%BF%90%E7%AD%B9%E5%AD%A6%E7%AD%89%E7%AD%89%E3%80%82*/

typedef struct  
{
	char vertex[n]; //�����
	int edges[n][n]; // �ڽӾ��󣬿ɿ����߱�
	int n, e; //ͼ�е�ǰ������������
}MGraph;

void Floyd(MGraph G)
{
	int A[G.n][G.n];
	int path[G.n][G.n];

	for (int i = 0; i < G.n; i++) //��ʼ������
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
			{//��������±�Ϊk ����·����ԭ�����·�����̣��򽫵�ǰ�����Ȩֵ��Ϊ��С��
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
			}
	}
}

#endif
