#ifndef DSACPP_VECTOR_VECTOR_H_
#define DSACPP_VECTOR_VECTOR_H_

#include "Include_Header.h"

typedef int Rank; //秩
constexpr auto DEFAULT_CAPACITY = 3; //默认的初始容量（实际应用中可设置为更大）

template<class T>
class Vector
{
protected:
	Rank size_; int capacity_;  T* elem_; //规模、容量、数据区

	void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间[lo,hi)
	void expand(); //空间不足时扩容
	void shrink(); //缩容: 装填因子过小时，压缩
	static Rank binSearch(T* A, T const& e, Rank lo, Rank hi); //二分查找（三个版本）（有序向量中使用）
	bool bubble(Rank lo, Rank hi); //扫描交换
	void bubbleSort(Rank lo, Rank hi); //冒泡排序算法
	void selectSort(Rank lo, Rank hi); //选择排序算法
	void merge(Rank lo,Rank mi, Rank hi); //归并算法
	void mergeSort(Rank lo, Rank hi); //归并排序算法
	void heapSort(Rank lo, Rank hi); //堆排序算法
	void quickSort(Rank lo, Rank hi); //快速排序算法

public:
//构造函数
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T v = 0); //所有元素初始为v
	Vector(T const* A, Rank n); //数组整体复制
	Vector(T const* A, Rank lo, Rank hi); //区间
	Vector(Vector<T> const& v); //向量整体复制
	Vector(Vector<T> const& v, Rank lo, Rank hi); //区间

//析构函数
	~Vector();

//只读访问接口
	Rank size() const; //规模
	bool empty() const; //判空
	Rank find(T const& e) const; //无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi) const; //无序向量区间查找
	int disordered() const; //有序性甄别
	Rank search(T const& e) const; //有序向量整体查找
	Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找


//可写访问接口
	T& operator[](Rank r) const; //重载下表操作符，就可以类似于数组形式引用各元素
	Vector<T>& operator=(Vector<T> const& v); //重载赋值操作符，以便直接克隆向量
	void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
	Rank insert(Rank r, T const& e); //插入元素
	int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素
	T remove(Rank r); //删除秩为r的元素
	int deduplicate(); //无序状态下，删除重复元素
	int uniquify(); //有序状态下，删除重复元素
	void sort(Rank lo, Rank hi); //掉[lo,hi)进行排序
	void sort(); //整体排序

//遍历
	void traverse(void(*visit)(T&)); //遍历（使用函数指针，只读或局部性修改）
	template <typename VST> void traverse(VST& visit);  //遍历（使用函数对象，可全局性修改)
};

/***********************************************************************/
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	elem_ = new T[capacity_= 2 * (hi - lo)]; //分配空间，规模清零
	while (lo < hi)
		elem_[size_++] = A[lo++];
}


template<class T>
void Vector<T>::expand() //空间不足时扩容
{
	if (size_ < capacity_) return; //尚未满员时，不必扩容
	if (capacity_ < DEFAULT_CAPACITY) capacity_ = DEFAULT_CAPACITY; //不低于最小容量
	T* oldelem = elem_;
	elem_ = new T[capacity_ <<= 1]; //容量加倍
	for (int i = 0; i < size_; i++)
		elem_[i] = oldelem[i];
	delete[] oldelem; 
}

template<class T>
void Vector<T>::shrink() //缩容: 装填因子过小时，压缩
{
	if (capacity_ < DEFAULT_CAPACITY << 1) return; //不至收缩到DEFAULT_CAPACITY以下
	if (size_ << 2 > capacity_) return; //以25%为界限
	T* oldelem = elem_; 	elem_ = new T[capacity_ >>= 1]; //容量减半
	for (int i = 0; i < size_; i++)
		elem_[i] = oldelem[i];
	delete[] oldelem;
}

template<class T>
static Rank Vector<T>::binSearch(T* A, T const& e, Rank lo, Rank hi)
{
#if 0
	//版本1：三分支
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1; //寻找区间中点
		if (A[mi] < e)
			hi = mi;
		else if (A[mi] > e)
			lo = mi + 1;
		else
			return mi; //此时查找成功
	}
	return -1; //查找失败

		//版本2：二分支
	while (hi - lo > 1) //成功查找不能提前终止
	{
		Rank mi = (lo + hi) >> 1;
		(e > A[mi]) ? lo = mi : hi = mi; //经比较后确定深入[lo,mi) 还是[mi,hi)
	}//循环结束时，hi = lo+1
	return (e == A[lo]) ? lo : -1; //因为循环结束时，区间元素只有一个，所以此时lo与mi相等
#endif
	//版本3：当区间宽度缩至0时才结束循环
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	} //成功查找不可提前终止
	return --lo; //循环结束时，lo是大于e的元素的最小秩，所以（lo-1）是不大于e的最大秩
}

template<class T>
bool Vector<T>::bubble(Rank lo, Rank hi) //扫描交换（只进行一趟）
{
	//每一趟的扫描交换，都会使末元素就位
	bool sorted = true; //整体有序标志
	while (++lo < hi)
		if (elem_[lo - 1] > elem_[lo])
		{
			sorted = false;
			swap(elem_[lo - 1], elem_[lo]);
		}
	return sorted;
}

template<class T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (bubble(lo, hi) = false) //当整体有序标志位false时，意味着还需要再次进行扫描交换
		--hi;
}

template<class T>
inline void Vector<T>::selectSort(Rank lo, Rank hi)
{
}

template<class T>
void Vector<T>::merge(Rank lo,Rank mi, Rank hi) //有序向量的归并（二路归并的接口实现）
{
	T* A = elem_ + lo; //合并后的向量A[0,hi-lo) = elem_[lo,hi)
	int lb = mi - lo; T* B = new T[lb]; //前子向量B[0,lb) = elem_[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i], ++i); //复制前子向量
	int lc = hi - mi; T* C = elem_ + mi; //后子向量C[0,lc) = elem_[mi,hi)
	for (Rank i = 0, j = 0, k = 0; ((j < lb) || (k < lc));) //开始合并（B[j]和C[k]中小者续至A末尾）
	{
		//当子向量B没超过其秩的范围，而且 B的元素小于C中的元素 或者 C的元素已经合并完， 则就把这个B[j]元素续至A的末尾
		if ((j < lb) && ((B[j] < C[k]) || (k >= lc))) A[i++] = B[j++];
		//同理上面，这次是子向量C没超过其秩的范围
		if ((k < lc) && ((C[k] < B[j]) || (j >= lb))) A[i++] = C[k++];
	}
}

template<class T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return; //hi-lo<2 ，即此时区间只有一个元素，那它自然是有序的
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi); mergeSort(mi, hi);
	merge(lo, mi, hi);
}

/****************************构造函数**********************************/
template<class T>
Vector<T>::Vector(int capacity /* = DEFAULT_CAPACITY */, int size /* = 0 */, T v /* = 0 */)
{
	//为什么要注释掉默认参数的值，因为不注释，就相当于重定义默认参数
	//具体解释：https://www.yuque.com/longlongqin/gs7wey/minyp9
	elem_ = new T[capacity_ = capacity];
	for (size_ = 0; size_ < size; ++size_)
		elem_[size_] = v; 
}
template<class T>
Vector<T>::Vector(T const* A, Rank n) //数组整体复制
{
	copyFrom(A, 0, n);
}
template<class T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi)//区间
{
	copyFrom(A, lo, hi);
}
template<class T>
Vector<T>::Vector(Vector<T> const& v) //向量整体赋值
{
	copyFrom(v.elem_, 0, v.size_);
}
template<class T>
Vector<T>::Vector(Vector<T> const& v, Rank lo, Rank hi) //区间
{
	copyFrom(v.elem_, lo, hi);
}

/****************************析构函数**********************************/
template<class T>
Vector<T>::~Vector()
{
	delete[] elem_;
}

/****************************只读访问接口**********************************/
template<class T>
Rank Vector<T>::size() const {return size_;} //规模

template<class T>
bool Vector<T>::empty() const { return !size_; } //判空

template<class T>
Rank Vector<T>::find(T const& e) const
{
	find(e, 0, size_);
}

template<class T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while( (lo<hi--) && (e != elem_[hi]))
		return hi;  //若hi < lo，则意味着失败；否则hi即命中元素的秩
}

template<class T>
int Vector<T>::disordered() const //检查向量是否有序
{
	int n = 0; //计数器
	for (int i = 1; i < size_; ++i)
		if (elem_[i - 1] > elem_[i])
			++n;
	return n;  //当且仅当n=0时，向量有序
}

template<class T>
inline Rank Vector<T>::search(T const& e) const
{
	return (0 >= size_) ? -1 : search(e, 0, size_); //当向量序列不存在时，返回-1
}

template<class T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
	// 随机使用：二分查找、或 Fibonacci查找
	return (rand() % 2) ? binSearch(elem_, e, lo, hi) : fibSearch(elem_, e, lo, hi);
}

/****************************可写访问接口*********************************/
template<class T>
T& Vector<T>::operator[](Rank r) const //重载下表操作符
{
	return elem_[r];
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) //重载赋值操作符，以便直接克隆向量
{
	if (elem_)  //释放原有内容
		delete[] elem_;
	copyFrom(v.elem_, 0, v.size_);
	return *this; //返回当前对象的引用，以便链式赋值
}

template<class T>
void Vector<T>::unsort(Rank lo, Rank hi)  //等概率随机置乱区间[lo, hi)
{
	T* V = elem_ + lo; //将子向量elem_[lo,hi) 看成另一个向量v[0,hi-lo)
	for (int i = hi - lo; i > 0; --i) //自后向前
		swap(v[i-1], V[rand() % i]); //将v[i-1]与v[0,i)中某一元素随机交换
}

template<class T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand(); //若有必要，则扩容
	for (int i = size_; i > r; ++i)
		elem_[i] = elem_[i - 1];
	size_ += 1;
	elem_[r] = e;
	return r; //返回秩
}

template<class T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0; //出于效率考虑，单独处理退化的情况，如remove(0,0)
	while (hi < size_) elem_[lo++] = elem_[hi++];
	size_ = lo;
	shrink(); //若有必要，则进行缩容
	return hi - lo; //返回删除元素的数目
}

template<class T>
T Vector<T>::remove(Rank r)
{
	T e = elem_[r];
	remove(r, r + 1);
	return e; //返回删除的元素
}

template<class T>
int Vector<T>::deduplicate() //无序去重
{
	int oldsize = size_;
	Rank i = 1;
	while (i < size_) //自前向后逐一考查各元素_elem[i]
		find(elem_[i], 0, i) < 0 ? i++ : remove(i);
	return oldsize - size_; //向量规模变化，即被删除的元素总数
}

template<class T>
int Vector<T>::uniquify() //有序去重（高效版）
{
	Rank i= 0, j = 0; //各对“互异”元素的秩
	while (++j < size_)
		if (elem_[i] != elem_[j])
			elem_[++i] = elem_[j]; //找到与前一个元素不同的那个元素，向前移至紧邻于前者的右侧
	size_ = ++i; //更新规模（因为下标从零开始，所以规模比下标大1）
	shrink(); //若有必要进行缩容
	return j-i; //返回删除元素的总个数 （因为出while循环时，++j是多加了个1的）
}

template<class T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%5)
	{
	case 1: bubbleSort(lo, hi); break; //冒泡排序
	case 2: selectSort(lo, hi); break; //选择排序
	case 3: mergeSort(lo, hi); break;  //归并排序
	case 4: heapSort(lo, hi); break;   //堆排序
	default: quickSort(lo, hi); break; //快速排序
	}
}

template<class T>
void Vector<T>::sort()
{
	sort(0, size_);
}

/****************************遍历*********************************/
template<class T>
void Vector<T>::traverse(void(*visit)(T&)) //借助函数指针机制
{
	for (int i = 0; i < size_; ++i) visit(elem_[i]); //遍历向量
}

template<class T> //元素类型
template<typename VST> //操作器
void Vector<T>::traverse(VST& visit) //借助函数对象机制
{
	for (int i = 0; i < size_; ++i)  visit(elem_[i]);
}

/****************************非成员函数的实现*********************************/

//2.5.3 判断器与比较器
template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } //less than
template<typename T> static bool lt(T& a, T& b) { return a < b; }  //less than
template<typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template<typename T> static bool eq(T& a, T& b) { return a == b; }  //equal

//2.6.6 Fibnacci查找
template<typename T>
static Rank fibsearch(T* A, T const& e, Rank lo, Rank hi)
{
	Fib fib(hi - lo); //创建一个Fib数列
	while (lo < hi)
	{
		while ((hi - lo) < fib.get()) fib.prev(); //找到黄金分割点（即，小于该规模(hi-lo)的 最大的fib项 再加1  ）
		Rank mi = lo + fib.get() + 1;
		if (e < A[mi])
			hi = mi;
		else if (A[mi] < e)
			lo = mi + 1;
		else
			return mi;
	}
	return -1; //查找失败时，返回-1
}

#endif