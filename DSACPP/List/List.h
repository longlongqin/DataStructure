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
	void insertionSort(ListNodePosi<T> p, int n); //对从p开始连续的n个节点插入排序
	void selectionSort(ListNodePosi<T>, int); //对从p开始连续的n个节点选择排序
	void mergeSort(ListNodePosi<T>&, int); //对从p开始连续的n个节点归并排序
	void merge(ListNodePosi<T>&, int, List<T>&, ListNodePosi<T>, int); //归并

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
	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const;
	ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //在p及其n-1个后继中选出最大者
	ListNodePosi<T> selectMax(); //整体最大者

//可写访问接口
	ListNodePosi<T> insertAsFirst(T const& e);
	ListNodePosi<T> insertAsLast(T const& e);
	ListNodePosi<T> insertA(ListNodePosi<T> p, T const& e);
	ListNodePosi<T> insertB(ListNodePosi<T> p, T const& e);
	T remove(ListNodePosi<T> p); //删除节点
	int deduplicate(); // 无序去重
	int uniquify(); // 有序去重
	void sort(ListNodePosi<T> p, int n); // 列表区间排序
	void sort(); //列表整体排序
	void reverse(); //前后倒置（习题）


//遍历
	void traverse(void (*visit) (T&)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template<class VST> //操作器
	void traverse(VST&);  //遍历，依次实施visit操作（函数对象，可全局性修改）

};



#include "member_function_implement.h"

#endif 

