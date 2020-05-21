/*
C++的 STL 中自带的"队列"(list)的示例

原文：https://www.cnblogs.com/skywang12345/p/3562279.html
*/

#include <queue> //使用模板库的队列
#include <iostream>

int main()
{
	std::queue<int> IntQueue;

	// 入队
	IntQueue.push(1);
	IntQueue.push(2);
	IntQueue.push(3);

	//出队
	IntQueue.pop();

	std::cout << "此时，队列的大小为：" << IntQueue.size() << '\n';
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