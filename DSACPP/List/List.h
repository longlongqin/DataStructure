#ifndef DSACPP_LIST_LIST_H_
#define DSACPP_LIST_LIST_H_
#include "ListNode.h"

template<class T>
class List
{
private:
	int size_;
	ListNodePosi<T> header_;
	ListNodePosi<T> trailer_;

protected:
	void init(); //列表创建时的初始化
	int clear();  //清除所有节点
	void copyNodes(ListNodePosi<T> p, int);

public:
//构造函数
	List(); //默认
	List(List<T> const& L); //整体复制构造
	List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNodePosi<T> p, int n); // 复制列表中自位置p起的n项

//析构函数
	~List();

//只读访问接口
	ListNodePosi<T> first(); //返回首节点
	ListNodePosi<T> last(); //返回最后一个节点
	T& operator[](Rank r);
	Rank size() const;
	bool empty() const;
	bool valid(ListNodePosi<T> p); //判断位置是否合法
	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const;
	ListNodePosi<T> find(T const& e) const;

//可写访问接口
	ListNodePosi<T> insertAsFirst(T const& e);
	ListNodePosi<T> insertAsLast(T const& e);
	ListNodePosi<T> insertA(ListNodePosi<T> p, T const& e);
	ListNodePosi<T> insertB(ListNodePosi<T> p, T congst& e);
	T remove(ListNodePosi<T> p); //删除节点
	int deduplicate(); // 无序去重
	int uniquify(); // 有序去重
};


#include "member_function_implement.h"

#endif 

