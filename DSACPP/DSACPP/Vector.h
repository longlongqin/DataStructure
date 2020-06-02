#pragma once

typedef int Rank; //秩
constexpr auto DEFAULT_CAPACITY = 3; //默认的初始容量（实际应用中可设置为更大）

template<class T>
class Vector
{
protected:
	Rank size_; int capacity_;  T* elem_; //规模、容量、数据区

	void copyFrom(T const* A, Rank lo, Rank hi);

public:
//构造函数
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T v = 0); //所有元素初始为v
	Vector(T const* A, Rank n); //数组整体复制
	Vector(T const* A, Rank lo, Rank hi); //区间
	Vector(Vector<T> const& v); //向量整体复制
	Vector(Vector<T> const& v, Rank lo, Rank hi); //区间

//析构函数
	~Vector();

//可写访问接口
	Vector<T>& operator=(Vector<T> const& v); //重载赋值操作符，以便直接克隆向量
};

/***********************************************************************/
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	elem_ = new T[capacity_= 2 * (hi - lo)]; //分配空间，规模清零
	while (lo < hi)
		elem_[size_++] = A[lo++];
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

/*******************************可写访问接口*********************************/
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v)
{
	if (elem_)  //释放原有内容
		delete[] elem_;
	copyFrom(v.elem_, 0, v.size_);
	return *this; //返回当前对象的引用，以便链式赋值
}
