//STL���Դ��ġ�ջ��stack������ʾ��
#include <stack> //ʹ��ջ
#include <iostream>

int main()
{
	std::stack<double> dstack;

	dstack.push(1.1);
	dstack.push(2.2);
	dstack.push(3.3);

	
	std::cout << "ջ��Ԫ�أ�" << dstack.top() << '\n';

	dstack.pop();
	std::cout << "��ջ�󣬵�ǰջ��Ԫ�أ�" << dstack.top() << '\n';

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;

}