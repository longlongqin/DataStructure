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
	void init(); //�б���ʱ�ĳ�ʼ��
	int clear();  //������нڵ�
	void copyNodes(ListNodePosi<T> p, int);

public:
//���캯��
	List(); //Ĭ��
	List(List<T> const& L); //���帴�ƹ���
	List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
	List(ListNodePosi<T> p, int n); // �����б�����λ��p���n��

//��������
	~List();

//ֻ�����ʽӿ�
	ListNodePosi<T> first(); //�����׽ڵ�
	ListNodePosi<T> last(); //�������һ���ڵ�
	T& operator[](Rank r);
	Rank size() const;
	bool empty() const;
	bool valid(ListNodePosi<T> p); //�ж�λ���Ƿ�Ϸ�
	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const;
	ListNodePosi<T> find(T const& e) const;

//��д���ʽӿ�
	ListNodePosi<T> insertAsFirst(T const& e);
	ListNodePosi<T> insertAsLast(T const& e);
	ListNodePosi<T> insertA(ListNodePosi<T> p, T const& e);
	ListNodePosi<T> insertB(ListNodePosi<T> p, T congst& e);
	T remove(ListNodePosi<T> p); //ɾ���ڵ�
	int deduplicate(); // ����ȥ��
	int uniquify(); // ����ȥ��
};


#include "member_function_implement.h"

#endif 

