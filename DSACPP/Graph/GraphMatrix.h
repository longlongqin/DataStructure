#ifndef DSACPP_GRAPH_GRAPHMATRIX_H_
#define DSACPP_GRAPH_GRAPHMATRIX_H_
/*�ڽӾ���*/

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬

template<class Tv>
class Vertex	//����
{
public:
	Vertex(const Tv& d) //�����¶���
		: data_(d), inDegree_(0), outDegree_(0), status_(UNDISCOVERED),
		dTime_(-1), fTime_(-1), parent_(-1), 
		priority_(INT_MAX) 
	{}

public:
	Tv data_; //����

	int inDegree_; //����
	int outDegree_; //���
	VStatus status_; //״̬
	int dTime_, fTime_; //ʱ���ǩ��������ʱ�̣��������ʱ�̣�
	int parent_; //�ڱ������еĸ��ڵ�
	int priority_; //�ڱ������е����ȼ������·��(ͨ·)�����̿�ߵȣ�
};


typedef enum { UNDETERMINED, TREE, CROSS, FORWORD, BACKWARD } EStatus; //���ڱ�����������������

template<class Te>
class Edge //��
{
public:
	Edge(const Te& d, int w) // �����±�
		:data_(d), weight_(w), status_(UNDETERMINED)
	{}

public:
	Te data_; // ����
	int weight_; // Ȩ��
	EStatus status_; //����
};

#endif