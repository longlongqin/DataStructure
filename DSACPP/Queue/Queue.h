#ifndef DSACPP_QUEUE_QUEUE_H_
#define DSACPP_QUEUE_QUEUE_H_

#include "../List/List.h" //以链表为父类

template<class T>
class Queue : public List<T>
{
public: //size() empty() 沿用链表的
	void enqueue(const T& e) //入队
	{
		insertAsLast(e);
	}


	T dequeue() //出队
	{
		return remove(first());
	}


	T& front()  //队首
	{
		return first()->data_;
	}

};

struct Customer
{
	int window; //窗口编号
	unsigned int time; //服务时长
};

void simulate(int nWin, int servTime) //按照指定窗口数，服务总时间模拟银行业务
{
	Queue<Customer>* windows = new Queue<Customer>[nWin]; //为每一个窗口创建一个队列
	for (int now = 0; now < servTime; ++now) //在下班之前，每个一个单位时间
	{
		if (rand() % (1 + nWin)) //新顾客以nWin/(nWin + 1)的概率到达
		{
			Customer c; c.time = 1 + rand() % 98; //新顾客到达，服务时长随机
			c.window = bestWindow(windows, nWin); //找出最佳（最短）服务窗口
			windows[c.window].enqueue(c); //新顾客加入相应的队列
		}

		for (int i = 0; i < nWin; ++i) //分别检查
		{
			if (!windows[i].empty()) //每个非空队列
			{
				if (--windows[i].front().time <= 0) //队首顾客的服务时间减少一个单位
					windows[i].dequeue();  //此时，队首顾客的业务办理完成，出列
			}
		}
	} //for
	delete[] windows; //释放所有队列（此前，~List会自动清空队列）
}
void bestWindow(Queue<Customer> windows[], int nWin) //在这里约定：队列最短则为最优队列
{
	int minsize = windows[0].size();
	int optiWin = 0; //最优队列（初始为第0个队列是最优）

	for (int i = 1; i < nWin; ++i)
	{
		if (minsize > windows[i].size())
		{
			minsize = windows[i].size();
			optiWin = i;
		}	
	}

	return optiWin;
}

#endif