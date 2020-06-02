#pragma once

typedef int Rank; //��
constexpr auto DEFAULT_CAPACITY = 3; //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template<class T>
class Vector
{
protected:
	Rank size_; int capacity_;  T* elem_; //��ģ��������������

	void copyFrom(T const* A, Rank lo, Rank hi);

public:
//���캯��
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T v = 0); //����Ԫ�س�ʼΪv
	Vector(T const* A, Rank n); //�������帴��
	Vector(T const* A, Rank lo, Rank hi); //����
	Vector(Vector<T> const& v); //�������帴��
	Vector(Vector<T> const& v, Rank lo, Rank hi); //����

//��������
	~Vector();

//��д���ʽӿ�
	Vector<T>& operator=(Vector<T> const& v); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
};

/***********************************************************************/
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	elem_ = new T[capacity_= 2 * (hi - lo)]; //����ռ䣬��ģ����
	while (lo < hi)
		elem_[size_++] = A[lo++];
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

/*******************************��д���ʽӿ�*********************************/
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v)
{
	if (elem_)  //�ͷ�ԭ������
		delete[] elem_;
	copyFrom(v.elem_, 0, v.size_);
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}
