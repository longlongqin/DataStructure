#include "List.h"

template<class T>
List<T>::~List()
{
	clear(); //先清空列表
	delete header_; delete trailer_; //然后，释放前后的两个哨兵节点
}