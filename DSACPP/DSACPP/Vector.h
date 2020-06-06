#ifndef DSACPP_VECTOR_VECTOR_H_
#define DSACPP_VECTOR_VECTOR_H_

#include "Include_Header.h"

typedef int Rank; //��
constexpr auto DEFAULT_CAPACITY = 3; //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template<class T>
class Vector
{
protected:
	Rank size_; int capacity_;  T* elem_; //��ģ��������������

	void copyFrom(T const* A, Rank lo, Rank hi); //������������[lo,hi)
	void expand(); //�ռ䲻��ʱ����
	void shrink(); //����: װ�����ӹ�Сʱ��ѹ��
	static Rank binSearch(T* A, T const& e, Rank lo, Rank hi); //���ֲ��ң������汾��������������ʹ�ã�
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	void bubbleSort(Rank lo, Rank hi); //ð�������㷨
	void selectSort(Rank lo, Rank hi); //ѡ�������㷨
	void merge(Rank lo,Rank mi, Rank hi); //�鲢�㷨
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
	void heapSort(Rank lo, Rank hi); //�������㷨
	void quickSort(Rank lo, Rank hi); //���������㷨

public:
//���캯��
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T v = 0); //����Ԫ�س�ʼΪv
	Vector(T const* A, Rank n); //�������帴��
	Vector(T const* A, Rank lo, Rank hi); //����
	Vector(Vector<T> const& v); //�������帴��
	Vector(Vector<T> const& v, Rank lo, Rank hi); //����

//��������
	~Vector();

//ֻ�����ʽӿ�
	Rank size() const; //��ģ
	bool empty() const; //�п�
	Rank find(T const& e) const; //���������������
	Rank find(T const& e, Rank lo, Rank hi) const; //���������������
	int disordered() const; //���������
	Rank search(T const& e) const; //���������������
	Rank search(T const& e, Rank lo, Rank hi) const; //���������������


//��д���ʽӿ�
	T& operator[](Rank r) const; //�����±���������Ϳ���������������ʽ���ø�Ԫ��
	Vector<T>& operator=(Vector<T> const& v); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	Rank insert(Rank r, T const& e); //����Ԫ��
	int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
	T remove(Rank r); //ɾ����Ϊr��Ԫ��
	int deduplicate(); //����״̬�£�ɾ���ظ�Ԫ��
	int uniquify(); //����״̬�£�ɾ���ظ�Ԫ��
	void sort(Rank lo, Rank hi); //��[lo,hi)��������
	void sort(); //��������

//����
	void traverse(void(*visit)(T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	template <typename VST> void traverse(VST& visit);  //������ʹ�ú������󣬿�ȫ�����޸�)
};

/***********************************************************************/
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	elem_ = new T[capacity_= 2 * (hi - lo)]; //����ռ䣬��ģ����
	while (lo < hi)
		elem_[size_++] = A[lo++];
}


template<class T>
void Vector<T>::expand() //�ռ䲻��ʱ����
{
	if (size_ < capacity_) return; //��δ��Աʱ����������
	if (capacity_ < DEFAULT_CAPACITY) capacity_ = DEFAULT_CAPACITY; //��������С����
	T* oldelem = elem_;
	elem_ = new T[capacity_ <<= 1]; //�����ӱ�
	for (int i = 0; i < size_; i++)
		elem_[i] = oldelem[i];
	delete[] oldelem; 
}

template<class T>
void Vector<T>::shrink() //����: װ�����ӹ�Сʱ��ѹ��
{
	if (capacity_ < DEFAULT_CAPACITY << 1) return; //����������DEFAULT_CAPACITY����
	if (size_ << 2 > capacity_) return; //��25%Ϊ����
	T* oldelem = elem_; 	elem_ = new T[capacity_ >>= 1]; //��������
	for (int i = 0; i < size_; i++)
		elem_[i] = oldelem[i];
	delete[] oldelem;
}

template<class T>
static Rank Vector<T>::binSearch(T* A, T const& e, Rank lo, Rank hi)
{
#if 0
	//�汾1������֧
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1; //Ѱ�������е�
		if (A[mi] < e)
			hi = mi;
		else if (A[mi] > e)
			lo = mi + 1;
		else
			return mi; //��ʱ���ҳɹ�
	}
	return -1; //����ʧ��

		//�汾2������֧
	while (hi - lo > 1) //�ɹ����Ҳ�����ǰ��ֹ
	{
		Rank mi = (lo + hi) >> 1;
		(e > A[mi]) ? lo = mi : hi = mi; //���ȽϺ�ȷ������[lo,mi) ����[mi,hi)
	}//ѭ������ʱ��hi = lo+1
	return (e == A[lo]) ? lo : -1; //��Ϊѭ������ʱ������Ԫ��ֻ��һ�������Դ�ʱlo��mi���
#endif
	//�汾3��������������0ʱ�Ž���ѭ��
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	} //�ɹ����Ҳ�����ǰ��ֹ
	return --lo; //ѭ������ʱ��lo�Ǵ���e��Ԫ�ص���С�ȣ����ԣ�lo-1���ǲ�����e�������
}

template<class T>
bool Vector<T>::bubble(Rank lo, Rank hi) //ɨ�轻����ֻ����һ�ˣ�
{
	//ÿһ�˵�ɨ�轻��������ʹĩԪ�ؾ�λ
	bool sorted = true; //���������־
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
	while (bubble(lo, hi) = false) //�����������־λfalseʱ����ζ�Ż���Ҫ�ٴν���ɨ�轻��
		--hi;
}

template<class T>
inline void Vector<T>::selectSort(Rank lo, Rank hi)
{
}

template<class T>
void Vector<T>::merge(Rank lo,Rank mi, Rank hi) //���������Ĺ鲢����·�鲢�Ľӿ�ʵ�֣�
{
	T* A = elem_ + lo; //�ϲ��������A[0,hi-lo) = elem_[lo,hi)
	int lb = mi - lo; T* B = new T[lb]; //ǰ������B[0,lb) = elem_[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i], ++i); //����ǰ������
	int lc = hi - mi; T* C = elem_ + mi; //��������C[0,lc) = elem_[mi,hi)
	for (Rank i = 0, j = 0, k = 0; ((j < lb) || (k < lc));) //��ʼ�ϲ���B[j]��C[k]��С������Aĩβ��
	{
		//��������Bû�������ȵķ�Χ������ B��Ԫ��С��C�е�Ԫ�� ���� C��Ԫ���Ѿ��ϲ��꣬ ��Ͱ����B[j]Ԫ������A��ĩβ
		if ((j < lb) && ((B[j] < C[k]) || (k >= lc))) A[i++] = B[j++];
		//ͬ�����棬�����������Cû�������ȵķ�Χ
		if ((k < lc) && ((C[k] < B[j]) || (j >= lb))) A[i++] = C[k++];
	}
}

template<class T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return; //hi-lo<2 ������ʱ����ֻ��һ��Ԫ�أ�������Ȼ�������
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi); mergeSort(mi, hi);
	merge(lo, mi, hi);
}

/****************************���캯��**********************************/
template<class T>
Vector<T>::Vector(int capacity /* = DEFAULT_CAPACITY */, int size /* = 0 */, T v /* = 0 */)
{
	//ΪʲôҪע�͵�Ĭ�ϲ�����ֵ����Ϊ��ע�ͣ����൱���ض���Ĭ�ϲ���
	//������ͣ�https://www.yuque.com/longlongqin/gs7wey/minyp9
	elem_ = new T[capacity_ = capacity];
	for (size_ = 0; size_ < size; ++size_)
		elem_[size_] = v; 
}
template<class T>
Vector<T>::Vector(T const* A, Rank n) //�������帴��
{
	copyFrom(A, 0, n);
}
template<class T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi)//����
{
	copyFrom(A, lo, hi);
}
template<class T>
Vector<T>::Vector(Vector<T> const& v) //�������帳ֵ
{
	copyFrom(v.elem_, 0, v.size_);
}
template<class T>
Vector<T>::Vector(Vector<T> const& v, Rank lo, Rank hi) //����
{
	copyFrom(v.elem_, lo, hi);
}

/****************************��������**********************************/
template<class T>
Vector<T>::~Vector()
{
	delete[] elem_;
}

/****************************ֻ�����ʽӿ�**********************************/
template<class T>
Rank Vector<T>::size() const {return size_;} //��ģ

template<class T>
bool Vector<T>::empty() const { return !size_; } //�п�

template<class T>
Rank Vector<T>::find(T const& e) const
{
	find(e, 0, size_);
}

template<class T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while( (lo<hi--) && (e != elem_[hi]))
		return hi;  //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}

template<class T>
int Vector<T>::disordered() const //��������Ƿ�����
{
	int n = 0; //������
	for (int i = 1; i < size_; ++i)
		if (elem_[i - 1] > elem_[i])
			++n;
	return n;  //���ҽ���n=0ʱ����������
}

template<class T>
inline Rank Vector<T>::search(T const& e) const
{
	return (0 >= size_) ? -1 : search(e, 0, size_); //���������в�����ʱ������-1
}

template<class T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
	// ���ʹ�ã����ֲ��ҡ��� Fibonacci����
	return (rand() % 2) ? binSearch(elem_, e, lo, hi) : fibSearch(elem_, e, lo, hi);
}

/****************************��д���ʽӿ�*********************************/
template<class T>
T& Vector<T>::operator[](Rank r) const //�����±������
{
	return elem_[r];
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
{
	if (elem_)  //�ͷ�ԭ������
		delete[] elem_;
	copyFrom(v.elem_, 0, v.size_);
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template<class T>
void Vector<T>::unsort(Rank lo, Rank hi)  //�ȸ��������������[lo, hi)
{
	T* V = elem_ + lo; //��������elem_[lo,hi) ������һ������v[0,hi-lo)
	for (int i = hi - lo; i > 0; --i) //�Ժ���ǰ
		swap(v[i-1], V[rand() % i]); //��v[i-1]��v[0,i)��ĳһԪ���������
}

template<class T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand(); //���б�Ҫ��������
	for (int i = size_; i > r; ++i)
		elem_[i] = elem_[i - 1];
	size_ += 1;
	elem_[r] = e;
	return r; //������
}

template<class T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0,0)
	while (hi < size_) elem_[lo++] = elem_[hi++];
	size_ = lo;
	shrink(); //���б�Ҫ�����������
	return hi - lo; //����ɾ��Ԫ�ص���Ŀ
}

template<class T>
T Vector<T>::remove(Rank r)
{
	T e = elem_[r];
	remove(r, r + 1);
	return e; //����ɾ����Ԫ��
}

template<class T>
int Vector<T>::deduplicate() //����ȥ��
{
	int oldsize = size_;
	Rank i = 1;
	while (i < size_) //��ǰ�����һ�����Ԫ��_elem[i]
		find(elem_[i], 0, i) < 0 ? i++ : remove(i);
	return oldsize - size_; //������ģ�仯������ɾ����Ԫ������
}

template<class T>
int Vector<T>::uniquify() //����ȥ�أ���Ч�棩
{
	Rank i= 0, j = 0; //���ԡ����족Ԫ�ص���
	while (++j < size_)
		if (elem_[i] != elem_[j])
			elem_[++i] = elem_[j]; //�ҵ���ǰһ��Ԫ�ز�ͬ���Ǹ�Ԫ�أ���ǰ����������ǰ�ߵ��Ҳ�
	size_ = ++i; //���¹�ģ����Ϊ�±���㿪ʼ�����Թ�ģ���±��1��
	shrink(); //���б�Ҫ��������
	return j-i; //����ɾ��Ԫ�ص��ܸ��� ����Ϊ��whileѭ��ʱ��++j�Ƕ���˸�1�ģ�
}

template<class T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%5)
	{
	case 1: bubbleSort(lo, hi); break; //ð������
	case 2: selectSort(lo, hi); break; //ѡ������
	case 3: mergeSort(lo, hi); break;  //�鲢����
	case 4: heapSort(lo, hi); break;   //������
	default: quickSort(lo, hi); break; //��������
	}
}

template<class T>
void Vector<T>::sort()
{
	sort(0, size_);
}

/****************************����*********************************/
template<class T>
void Vector<T>::traverse(void(*visit)(T&)) //��������ָ�����
{
	for (int i = 0; i < size_; ++i) visit(elem_[i]); //��������
}

template<class T> //Ԫ������
template<typename VST> //������
void Vector<T>::traverse(VST& visit) //���������������
{
	for (int i = 0; i < size_; ++i)  visit(elem_[i]);
}

/****************************�ǳ�Ա������ʵ��*********************************/

//2.5.3 �ж�����Ƚ���
template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } //less than
template<typename T> static bool lt(T& a, T& b) { return a < b; }  //less than
template<typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template<typename T> static bool eq(T& a, T& b) { return a == b; }  //equal

//2.6.6 Fibnacci����
template<typename T>
static Rank fibsearch(T* A, T const& e, Rank lo, Rank hi)
{
	Fib fib(hi - lo); //����һ��Fib����
	while (lo < hi)
	{
		while ((hi - lo) < fib.get()) fib.prev(); //�ҵ��ƽ�ָ�㣨����С�ڸù�ģ(hi-lo)�� ����fib�� �ټ�1  ��
		Rank mi = lo + fib.get() + 1;
		if (e < A[mi])
			hi = mi;
		else if (A[mi] < e)
			lo = mi + 1;
		else
			return mi;
	}
	return -1; //����ʧ��ʱ������-1
}

#endif