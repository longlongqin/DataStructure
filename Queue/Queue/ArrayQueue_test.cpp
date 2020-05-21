#if 0

#include "ArrayQueue.h"

int main()
{
	ArrayQueue<int> IntArray;

	IntArray.add(1);
	IntArray.add(2);
	IntArray.add(3);

	//打印出队列中的元素（从队首~队尾）
	for (int i = 0; i < IntArray.size(); ++i)
	{
		std::cout << "IntQueue[" << i << "] = " << IntArray.traverse(i) << '\n';
	}


	std::cout << "出队完成后，队首元素为：" << IntArray.pop() << '\n';
	std::cout << "此时，队列的大小为：" << IntArray.size() << '\n';

	std::cout << "is_empty()=" << IntArray.isEmpty() << '\n';

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}

#endif
