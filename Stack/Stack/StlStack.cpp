//STL中自带的“栈（stack）”的示例
#include <stack> //使用栈
#include <iostream>

int main()
{
	std::stack<double> dstack;

	dstack.push(1.1);
	dstack.push(2.2);
	dstack.push(3.3);

	
	std::cout << "栈顶元素：" << dstack.top() << '\n';

	dstack.pop();
	std::cout << "出栈后，当前栈顶元素：" << dstack.top() << '\n';

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;

}