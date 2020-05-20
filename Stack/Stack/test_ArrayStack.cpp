#if 0

#include "ArrayStack.h"
#include <iostream>

int main()
{
	ArrayStack<int> astack{};

	//入栈
	astack.push(1);
	std::cout << "stack[" << astack.size() << "] = " << astack.top_node() << '\n';
	astack.push(2);
	std::cout << "stack[" << astack.size() << "] = " << astack.top_node() << '\n';
	astack.push(3);
	std::cout << "stack[" << astack.size() << "] = " << astack.top_node() << '\n';
	

	//栈顶元素
	std::cout << "当前栈顶元素为：" << astack.top_node() << '\n';

	//出栈
	astack.pop();
	std::cout << "出栈之后，当前栈顶元素为：" << astack.top_node() << '\n';

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;

}

#endif