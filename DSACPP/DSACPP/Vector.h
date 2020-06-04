#ifndef DSACPP_VECTOR_VECTOR_H_
#define DSACPP_VECTOR_VECTOR_H_


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


//可写访问接口
	T& operator[](Rank r) const; //重载下表操作符，就可以类似于数组形式引用各元素
	Vector<T>& operator=(Vector<T> const& v); //重载赋值操作符，以便直接克隆向量
	void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
	Rank insert(Rank r, T const& e); //插入元素
	int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素
	T remove(Rank r); //删除秩为r的元素
	int deduplicate(); //无序状态下，删除重复元素
	int uniquify(); //有序状态下，删除重复元素

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
int Vector<T>::uniquify() //有序去重
{
	return 0;
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
//2.5.2 置乱器
template<typename T>
void permute(Vector<T>& v)  //随机置乱向量，使各元素等概率出现于各位置
{
	for (int i = v.size(); i > 0; --i) //自后向前
		swap(v[i - 1], v[rand() % i]);  //V[i - 1]与V[0, i)中某一随机元素交换
}

//2.5.3 判断器与比较器
template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } //less than
template<typename T> static bool lt(T& a, T& b) { return a < b; }  //less than
template<typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template<typename T> static bool eq(T& a, T& b) { return a == b; }  //equal


#endif


