#pragma once

class Fib //Fibonacci������
{
private:
	int f, g; //f = fib(k - 1), g = fib(k)����Ϊint�ͣ��ܿ�ͻ���ֵ���
public:
	Fib(int n) //��ʼ��Ϊ��С��n����СFibonacci��
	{
		f = 0; g = 1; 
		while (g < n) next();
	}

	int get() { return g; } //��ȡ��ǰFibonacci�O(1)ʱ��
	int next() { g += f; f = g - f; return g; } //ת��Fibonacci���е���һ��
	int prev() { f = g - f; g -= f; return g; } //ת��Fibonacci���е�ǰһ��
};
