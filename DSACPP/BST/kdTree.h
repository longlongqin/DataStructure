#ifndef DSACPP_BST_KDTREE_H_
#define DSACPP_BST_KDTREE_H_

/*kd��������ɲο���https://my.oschina.net/u/4352976/blog/3628336 */

#include <cmath> //pow() sqrt()
#include <algorithm>

template<class T> class KdNode; //ǰ������
template<class T> using KdNodeposi = KdNode<T>*; //����ڵ��λ��
template<class T>
class KdNode //kd���Ľڵ�
{
public:
	KdNodeposi<T> parent_; //����
	KdNodeposi<T> lc_; //����
	KdNodeposi<T> rc_; //�Һ���
	int splitAttribute_; //����ά�ȣ�ĿǰӦ�û��ֵ��Ǹ�ά�ȣ�
	std::vector<T> vec_; //����Ԫ��

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
	KdNodeposi<T> root_; //����

public:
	KdTree()
	{
		root_ = nullptr;
	}
	KdTree(std::vector<std::vector<T>>& data) //����kd����������ɺ󣬷��ص���������
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

	//ת�þ���
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

	//����ÿ��ά���ϵķ���
	/*���ͳ���еķ�����������ÿ������ֵ��ȫ������ֵ��ƽ����֮���ƽ��ֵ��ƽ����*/
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

	//ȷ���ָ��ߣ�����󷽲�ȷ����
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

	//��ѯ��ֵ
	T getSplitValue(std::vector<T>& vec)
	{
		std::sort(vec.begin(), vec.end());
		return vec[vec.size() / 2];
	}

	//����2��Kά��ľ���
	static double getDistance(std::vector<T>& point1, std::vector<T>& point2)
	{
		int distance = 0;
		for (int i = 0; i < point1.size(); i++)
		{
			distance += pow(point1[i] - point2[i], 2);
		}
		return sqrt(distance);
	}

	//����kd��
	KdNodeposi<T> createKdTree(std::vector<std::vector<T>>& data)
	{
		if (data.empty())	return nullptr; 

		if (data.size() == 1)
			return (new KdNode(data[0], -1));

		//����������ֵ
		std::vector<std::vector<T>> data_T = transpose(data);
		int splitAttribute = getSpiltAttribute(data_T);
	}
};

#endif
