#ifndef DSACPP_GRAPH_GRAPH_H_
#define DSACPP_GRAPH_GRAPH_H_

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus; //����״̬
typedef enum{UNDETERMINED, TREE, CROSS, FORWORD, BACKWARD} EType; //���ڱ�����������������

template<class Tv, class Te>
class Graph
{
public:
	int n_, e_; //����������������
private:
	void reset() //���ж��㡢�ߵĸ�����Ϣ��λ
	{
		for (int i = 0; i < n_; i++)
		{
			
		}
	}
};

#endif
