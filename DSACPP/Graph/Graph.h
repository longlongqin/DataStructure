#ifndef DSACPP_GRAPH_GRAPH_H_
#define DSACPP_GRAPH_GRAPH_H_

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus; //顶点状态
typedef enum{UNDETERMINED, TREE, CROSS, FORWORD, BACKWARD} EType; //边在遍历树中所属的类型

template<class Tv, class Te>
class Graph
{
public:
	int n_, e_; //顶点总数、边总数
private:
	void reset() //所有顶点、边的辅助信息复位
	{
		for (int i = 0; i < n_; i++)
		{
			
		}
	}
};

#endif
