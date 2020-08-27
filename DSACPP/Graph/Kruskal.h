#ifndef DSACPP_GRAPH_KRUSKAL_H_
#define DSACPP_GRAPH_KRUSKAL_H_
/*�ο��ڣ��������ݽṹ��P251*/

#include "GraphMatrix.h" //�ڽӾ���
//�Ա߼�����Edge�ṹ����
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

	Edge edges[G.e_]; //����߼����飨�������鳤��Ӧ��С��ԭͼG�ı�����
	int parent[G.n_]; //���� ���������жϱ�����Ƿ��γɻ�·

	bubbleSort(G); //���ڽӾ���ת��GΪ�߼�����edges������Ȩ��С��������������ѡ�� ð������

	for (int i = 0; i<G.n_; i++)
	{
		parent[i] = 0; //������Ԫ�س�ʼ��Ϊ0
	}

	for (int j = 0; j < G.e_; j++)
	{
		n = Find(parent, edges[j].begin);
		m = Find(parent, edges[j].end);
		if (n != m) //����n��m���ȣ�˵���˱�û���������������γɻ�·
		{
			parent[n] = m; //���˱ߵĽ�β��������±�Ϊ����parent�У���ʾ�˶����Ѿ���������������
		}
	}
}

template<class Tv, class Te>
void bubbleSort(GraphMatrix<Tv, Te> G) /*�˿��ԡ����ݽṹ��P5*/
{
	bool sorted = false; //���������ֽ�����ȼٶ���δ����

	int n1 = G.E.size();
	while (sorted)
	{
		sorted = true; //�ٶ��Ѿ�����
		for (int i = G.E; i < n1; i++)
		{
			if (G.E[i] > G.E[i+1])
			{
				swap(G.E[i], G.E[i + 1]);
				sorted = false;
			}
		}

		n1--; //��ʱ��ĩβԪ�ر�Ȼ��λ�����Կ������̴��������еĳ���
	}
}

int Find(int* parent, int f) /*���� ���߶��� ��β���±�*/
{
	while (parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}
#endif
