#include <iostream>
#include "DoubleLink.h"
#include <string>

// 双向链表操作 int型数据
void int_test()
{
	int arr[4]{ 10,20,30,40 };

	std::cout << "\n----int_test----" << '\n';

	//创建双向链表
	DoubleLink<int>* pdlink = new DoubleLink<int>();

	//将数组中的元素依次插入链表中
	for (int element : arr)
	{
		int i = 0;
		pdlink->insert(i, element);
	}

	std::cout << "IsEmpty() = " << pdlink->IsEmpty() << '\n'; //链表是否为空
	std::cout << "node_size() = " << pdlink->node_size() << '\n';

	//打印双链表的全部数据
	for (int i{ 0 }; i < pdlink->node_size(); ++i)
	{
		std::cout << "pdlink(" << i << ")=" << pdlink->get(i) << '\n';
	}
}

void string_test()
{
	std::cout << "\n----string_test----" << '\n';

	std::string arr[4] = { "ten", "twenty", "thirty", "forty" };

	//创建双向链表
	DoubleLink<std::string>* pdlink = new DoubleLink<std::string>();

	//将数组中的元素依次插入链表中
	for (std::string element : arr)
	{
		int i = 0;
		pdlink->insert(i, element);
	}

	std::cout << "IsEmpty() = " << pdlink->IsEmpty() << '\n'; //链表是否为空
	std::cout << "node_size() = " << pdlink->node_size() << '\n';

	// 打印双链表的全部数据
	for (int i{ 0 }; i < pdlink->node_size(); ++i)
	{
		std::cout << "pdlink(" << i << ")=" << pdlink->get(i) << '\n';
	}
}

//实例化一个结构体类型的双向链表
struct Student
{
	int id;
	char name[20];
};

static Student arr[] =
{
	{001,"金吒"},
	{002,"木吒"},
	{003,"哪吒"}
};

void object_test()
{
	std::cout<< "\n----object_test----" << '\n';

	//创建双向链表
	DoubleLink<Student>* pdlink = new DoubleLink<Student>();

	//将数组中的元素依次插入链表中
	for (Student element : arr)
	{
		int i = 0;
		pdlink->insert(i, element);
	}

	std::cout << "IsEmpty() = " << pdlink->IsEmpty() << '\n'; //链表是否为空
	std::cout << "node_size() = " << pdlink->node_size() << '\n';

	// 打印双链表的全部数据
	for (int i(0);i<pdlink->node_size();++i)
	{
		std::cout << "pdlink(" << i << ") = [" << pdlink->get(i).id
			<< ',' << pdlink->get(i).name << ']' << '\n';
	}
}

int main()
{
	int_test();
	string_test();
	object_test();

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
	return 0;

}