#if 0

#include "ArrayStack.h"
#include <iostream>

int main()
{
	ArrayStack<int> astack{};

	//��ջ
	astack.push(1);
	std::cout << "stack[" << astack.size() << "] = " << astack.top_node() << '\n';
	astack.push(2);
	std::cout << "stack[" << astack.size() << "] = " << astack.top_node() << '\n';
	astack.push(3);
	std::cout << "stack[" << astack.size() << "] = " << astack.top_node() << '\n';
	

	//ջ��Ԫ��
	std::cout << "��ǰջ��Ԫ��Ϊ��" << astack.top_node() << '\n';

	//��ջ
	astack.pop();
	std::cout << "��ջ֮�󣬵�ǰջ��Ԫ��Ϊ��" << astack.top_node() << '\n';

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;

}

#endif