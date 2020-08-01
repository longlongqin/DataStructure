#ifndef DSACPP_GRAPH_GRAPHMATRIX_H_
#define DSACPP_GRAPH_GRAPHMATRIX_H_
/*邻接矩阵*/

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态

template<class Tv>
class Vertex	//顶点
{
public:
	Vertex(const Tv& d) //构造新顶点
		: data_(d), inDegree_(0), outDegree_(0), status_(UNDISCOVERED),
		dTime_(-1), fTime_(-1), parent_(-1), 
		priority_(INT_MAX) 
	{}

public:
	Tv data_; //数据

	int inDegree_; //出度
	int outDegree_; //入度
	VStatus status_; //状态
	int dTime_, fTime_; //时间标签（被发现时刻，访问完毕时刻）
	int parent_; //在遍历树中的父节点
	int priority_; //在遍历树中的优先级（最短路径(通路)、极短跨边等）
};


typedef enum { UNDETERMINED, TREE, CROSS, FORWORD, BACKWARD } EStatus; //边在遍历树中所属的类型

template<class Te>
class Edge //边
{
public:
	Edge(const Te& d, int w) // 构造新边
		:data_(d), weight_(w), status_(UNDETERMINED)
	{}

public:
	Te data_; // 数据
	int weight_; // 权重
	EStatus status_; //类型
};

#endif