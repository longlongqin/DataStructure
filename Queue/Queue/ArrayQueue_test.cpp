#if 0

#include "ArrayQueue.h"

int main()
{
	ArrayQueue<int> IntArray;

	IntArray.add(1);
	IntArray.add(2);
	IntArray.add(3);

	//��ӡ�������е�Ԫ�أ��Ӷ���~��β��
	for (int i = 0; i < IntArray.size(); ++i)
	{
		std::cout << "IntQueue[" << i << "] = " << IntArray.traverse(i) << '\n';
	}


	std::cout << "������ɺ󣬶���Ԫ��Ϊ��" << IntArray.pop() << '\n';
	std::cout << "��ʱ�����еĴ�СΪ��" << IntArray.size() << '\n';

	std::cout << "is_empty()=" << IntArray.isEmpty() << '\n';

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}

#endif
