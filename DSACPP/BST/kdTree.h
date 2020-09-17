#ifndef DSACPP_BST_KDTREE_H_
#define DSACPP_BST_KDTREE_H_

/*kd树，代码可参考：https://my.oschina.net/u/4352976/blog/3628336 */

#include <cmath> //pow() sqrt()
#include <algorithm>

template<class T> class KdNode; //前置声明
template<class T> using KdNodeposi = KdNode<T>*; //定义节点的位置
template<class T>
class KdNode //kd树的节点
{
public:
	KdNodeposi<T> parent_; //父亲
	KdNodeposi<T> lc_; //左孩子
	KdNodeposi<T> rc_; //右孩子
	int splitAttribute_; //划分维度（目前应该划分的那个维度）
	std::vector<T> vec_; //数据元素

public:
	KdNode(std::vector<T> v = {}, int split = 0, KdNodeposi<T> parent = nullptr,
		KdNodeposi<T> lc = nullptr, KdNodeposi<T> rc = nullptr)
		:vec_(v), splitAttribute_(split), parent_(parent), lc_(lc), rc_(rc)
	{}
};

template<class T>
class KdTree
{
private:
	KdNodeposi<T> root_; //树根

public:
	KdTree()
	{
		root_ = nullptr;
	}
	KdTree(std::vector<std::vector<T>>& data) //创建kd树（创建完成后，返回的是树根）
	{
		root_ = createKdTree(data);
	}

	KdNodeposi<T> getRoot() 
	{
		return root_;
	}

	std::vector<T> getRootData()
	{
		return root_->vec_;
	}

	//转置矩阵
	std::vector<std::vector<T>> transpose(std::vector<std::vector<T>>& data)
	{
		std::vector<std::vector<T>> trans(n, std::vector<T>(m, 0));
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[0].size(); j++)
				trans[i][j] = data[j][i];
		}
		return trans;
	}

	//计算每个维度上的方差
	/*方差：统计中的方差（样本方差）是每个样本值与全体样本值的平均数之差的平方值的平均数*/
	double getVariance(std::vector<T>& vec)
	{
		double sum = 0;
		double x = 0;
		for (int i = 0; i < vec.size(); i++)
			sum += vec[i];
		double avg = sum / vec.size();
		for (int j = 0; j < vec.size(); j++)
			x += pow(vec[j] - avg, 2);
		return x / vec.size();		
	}

	//确定分割线（由最大方差确定）
	int getSpiltAttribute(std::vector<std::vector<T>>& data)
	{
		int splitAttribute = 0;
		double maxVar = getVariance(data[0]);
		
		for (int i = 0; i < data.size(); i++)
		{
			double temp = getVariance(data[i]);
			if (temp > maxVar)
			{
				splitAttribute = i;
				maxVar = temp;
			}
		}
		return splitAttribute;
	}

	//查询中值
	T getSplitValue(std::vector<T>& vec)
	{
		std::sort(vec.begin(), vec.end());
		return vec[vec.size() / 2];
	}

	//计算2个K维点的距离
	static double getDistance(std::vector<T>& point1, std::vector<T>& point2)
	{
		int distance = 0;
		for (int i = 0; i < point1.size(); i++)
		{
			distance += pow(point1[i] - point2[i], 2);
		}
		return sqrt(distance);
	}

	//创建kd树
	KdNodeposi<T> createKdTree(std::vector<std::vector<T>>& data)
	{
		if (data.empty())	return nullptr; 

		if (data.size() == 1)
			return (new KdNode(data[0], -1));

		//获得轴序号与值
		std::vector<std::vector<T>> data_T = transpose(data);
		int splitAttribute = getSpiltAttribute(data_T);
	}
};

#endif
