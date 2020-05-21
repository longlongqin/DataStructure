/*
C++�� STL ���Դ���"����"(list)��ʾ��

ԭ�ģ�https://www.cnblogs.com/skywang12345/p/3562279.html
*/

#include <queue> //ʹ��ģ���Ķ���
#include <iostream>

int main()
{
	std::queue<int> IntQueue;

	// ���
	IntQueue.push(1);
	IntQueue.push(2);
	IntQueue.push(3);

	//����
	IntQueue.pop();

	std::cout << "��ʱ�����еĴ�СΪ��" << IntQueue.size() << '\n';
	std::cout << "empty()=" << IntQueue.empty() << '\n';

	while (!IntQueue.empty())
	{
		std::cout << IntQueue.front() << ' ';
		IntQueue.pop();
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}