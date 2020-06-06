#pragma once

class Fib //Fibonacci数列类
{
private:
	int f, g; //f = fib(k - 1), g = fib(k)。均为int型，很快就会数值溢出
public:
	Fib(int n) //初始化为不小于n的最小Fibonacci项
	{
		f = 0; g = 1; 
		while (g < n) next();
	}

	int get() { return g; } //获取当前Fibonacci项，O(1)时间
	int next() { g += f; f = g - f; return g; } //转至Fibonacci数列的下一项
	int prev() { f = g - f; g -= f; return g; } //转至Fibonacci数列的前一项
};
