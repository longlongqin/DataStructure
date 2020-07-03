#include "rpn.h"
#include <cstdlib> //exit
#include <cctype>
#include <cstring> //strlen
#include <cstdio>  //sprintf

double calcu(double a, char op, double b)
{
	switch (op)
	{
	case '+':	return a + b;
	case '-':	return a - b;
	case '*':	return a * b;
	case '/':	
		if (b == 0)
			std::exit(-1);
		return a / b;
	case '^':	return pow(a, b);
	default:	std::exit(-1);
	}
}



double calcu(char op, double b)
{
	switch (op)
	{
	case '!':	return	Factorial(b);
	default:	std::exit(-1);
	}
}
std::int_fast64_t Factorial(int n)
{
	std::int_fast64_t result = 1;
	while (n > 1)
	{
		result *= n;
	}
	return result;
}


void readNumber(char*& s, Stack<float>& stack)
{
	stack.push((double)(*s - '0'));
	while (isdigit(*(++s)))
	{
		stack.push(stack.pop() * 10 + (*s - '0'));
	}

	if (*s == '.')
	{
		float fraction = 1;
		while (isdigit(*(++s)))
			stack.push(stack.pop() + (*s - '0') * (fraction /= 10));
	}
	else
		return;
}


void append(char*& rpn, char optr)
{
	int n = strlen(rpn);  //RPN当前长度（以‘\0’结尾，长度为n+1）
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3)); //扩展空间
	sprintf(rpn + n, "%c", optr); //将当前操作符追加到rpn中
	rpn[n + 2] = '\0';
}

void append(char*& rpn, double opnd)
{
	char buf[64];
	if ((opnd - (int)opnd) > 0.0) //浮点格式
		sprintf(buf, "%f \0", opnd);
	else //或者是 整数格式
		sprintf(buf, "%d \0", opnd);

	rpn = (char*)realloc(rpn, sizeof(char) * (strlen(rpn) + strlen(buf) + 1)); //扩展空间
	strcat(rpn, buf); //RPN加长
}

char orderBetween(char op1, char op2) //比较两个运算符之间的优先级
{
	return	pri[optr2rank(op1)][optr2rank(op2)];
}
Operator optr2rank(char op) //由运算符转译出编号
{
	switch (op)
	{
	case '+':	return ADD;
	case '-':	return SUB;
	case '*':	return MUL;
	case '/':	return DIV;
	case '^':	return POW;
	case '!':	return FAC;
	case '(':	return L_P;
	case ')':	return R_P;
	case '\0':	return EOE;
	default:	exit(-1);
	}
}