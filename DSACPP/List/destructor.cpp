#include "List.h"

template<class T>
List<T>::~List()
{
	clear(); //������б�
	delete header_; delete trailer_; //Ȼ���ͷ�ǰ��������ڱ��ڵ�
}