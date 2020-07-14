#ifndef DSACPP_QUEUE_QUEUE_H_
#define DSACPP_QUEUE_QUEUE_H_

#include "../List/List.h" //������Ϊ����

template<class T>
class Queue : public List<T>
{
public: //size() empty() ���������
	void enqueue(const T& e) //���
	{
		insertAsLast(e);
	}


	T dequeue() //����
	{
		return remove(first());
	}


	T& front()  //����
	{
		return first()->data_;
	}

};

struct Customer
{
	int window; //���ڱ��
	unsigned int time; //����ʱ��
};

void simulate(int nWin, int servTime) //����ָ����������������ʱ��ģ������ҵ��
{
	Queue<Customer>* windows = new Queue<Customer>[nWin]; //Ϊÿһ�����ڴ���һ������
	for (int now = 0; now < servTime; ++now) //���°�֮ǰ��ÿ��һ����λʱ��
	{
		if (rand() % (1 + nWin)) //�¹˿���nWin/(nWin + 1)�ĸ��ʵ���
		{
			Customer c; c.time = 1 + rand() % 98; //�¹˿͵������ʱ�����
			c.window = bestWindow(windows, nWin); //�ҳ���ѣ���̣����񴰿�
			windows[c.window].enqueue(c); //�¹˿ͼ�����Ӧ�Ķ���
		}

		for (int i = 0; i < nWin; ++i) //�ֱ���
		{
			if (!windows[i].empty()) //ÿ���ǿն���
			{
				if (--windows[i].front().time <= 0) //���׹˿͵ķ���ʱ�����һ����λ
					windows[i].dequeue();  //��ʱ�����׹˿͵�ҵ�������ɣ�����
			}
		}
	} //for
	delete[] windows; //�ͷ����ж��У���ǰ��~List���Զ���ն��У�
}
void bestWindow(Queue<Customer> windows[], int nWin) //������Լ�������������Ϊ���Ŷ���
{
	int minsize = windows[0].size();
	int optiWin = 0; //���Ŷ��У���ʼΪ��0�����������ţ�

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