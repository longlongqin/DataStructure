#ifndef DSACPP_VECTOR_VECTOR_H_
#define DSACPP_VECTOR_VECTOR_H_


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


//��д���ʽӿ�
	T& operator[](Rank r) const; //�����±���������Ϳ���������������ʽ���ø�Ԫ��
	Vector<T>& operator=(Vector<T> const& v); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	Rank insert(Rank r, T const& e); //����Ԫ��
	int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
	T remove(Rank r); //ɾ����Ϊr��Ԫ��
	int deduplicate(); //����״̬�£�ɾ���ظ�Ԫ��
	int uniquify(); //����״̬�£�ɾ���ظ�Ԫ��

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
int Vector<T>::uniquify() //����ȥ��
{
	return 0;
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
//2.5.2 ������
template<typename T>
void permute(Vector<T>& v)  //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
{
	for (int i = v.size(); i > 0; --i) //�Ժ���ǰ
		swap(v[i - 1], v[rand() % i]);  //V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
}

//2.5.3 �ж�����Ƚ���
template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } //less than
template<typename T> static bool lt(T& a, T& b) { return a < b; }  //less than
template<typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template<typename T> static bool eq(T& a, T& b) { return a == b; }  //equal


#endif


