#include <iostream>
#include "DoubleLink.h"
#include <string>

// ˫��������� int������
void int_test()
{
	int arr[4]{ 10,20,30,40 };

	std::cout << "\n----int_test----" << '\n';

	//����˫������
	DoubleLink<int>* pdlink = new DoubleLink<int>();

	//�������е�Ԫ�����β���������
	for (int element : arr)
	{
		int i = 0;
		pdlink->insert(i, element);
	}

	std::cout << "IsEmpty() = " << pdlink->IsEmpty() << '\n'; //�����Ƿ�Ϊ��
	std::cout << "node_size() = " << pdlink->node_size() << '\n';

	//��ӡ˫�����ȫ������
	for (int i{ 0 }; i < pdlink->node_size(); ++i)
	{
		std::cout << "pdlink(" << i << ")=" << pdlink->get(i) << '\n';
	}
}

void string_test()
{
	std::cout << "\n----string_test----" << '\n';

	std::string arr[4] = { "ten", "twenty", "thirty", "forty" };

	//����˫������
	DoubleLink<std::string>* pdlink = new DoubleLink<std::string>();

	//�������е�Ԫ�����β���������
	for (std::string element : arr)
	{
		int i = 0;
		pdlink->insert(i, element);
	}

	std::cout << "IsEmpty() = " << pdlink->IsEmpty() << '\n'; //�����Ƿ�Ϊ��
	std::cout << "node_size() = " << pdlink->node_size() << '\n';

	// ��ӡ˫�����ȫ������
	for (int i{ 0 }; i < pdlink->node_size(); ++i)
	{
		std::cout << "pdlink(" << i << ")=" << pdlink->get(i) << '\n';
	}
}

//ʵ����һ���ṹ�����͵�˫������
struct Student
{
	int id;
	char name[20];
};

static Student arr[] =
{
	{001,"��߸"},
	{002,"ľ߸"},
	{003,"��߸"}
};

void object_test()
{
	std::cout<< "\n----object_test----" << '\n';

	//����˫������
	DoubleLink<Student>* pdlink = new DoubleLink<Student>();

	//�������е�Ԫ�����β���������
	for (Student element : arr)
	{
		int i = 0;
		pdlink->insert(i, element);
	}

	std::cout << "IsEmpty() = " << pdlink->IsEmpty() << '\n'; //�����Ƿ�Ϊ��
	std::cout << "node_size() = " << pdlink->node_size() << '\n';

	// ��ӡ˫�����ȫ������
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