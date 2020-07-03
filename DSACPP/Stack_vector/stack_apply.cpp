#include "stack_apply.h"
#include "rpn.h"
#include <cassert>  // assert
#include <cctype>  // isdigit
#include <cstdlib> // exit

/*1、逆序输出——进制转换*/
//递归版
void convert(Stack<char>& s, std::int_fast32_t n, int base)
{
	//assert((base > 1 && base <= 16) && "转换为的进制数应该在(1,16]区间。");
	static char digit[] ={ '0', '1', '2', '3', '4', '5', '6','7','8','9',
							'A', 'B','C', 'D','E','F', };
	if (n > 0) //当还有余数时，反复的进行
	{
		s.push(digit[n % base]); //将每次除以λ之后的余数 入栈
		convert(s, n / base, base);
	}
}

//迭代版
void convert1(Stack<char>& s, std::int_fast32_t n, int base)
{
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6','7','8','9',
						'A', 'B','C', 'D','E','F', };
	while (n>0)
	{
		s.push(digit[n % base]);
		n /= base;
	}
}

/*2、括号匹配*/
template<typename T>
bool paren(const char exp[], int lo, int hi)
{
	Stack<T> S; //使用栈 记录已经发现但尚未匹配的括号
	for (int i = lo, i <= hi; ++i)
	{
		switch (exp[i])
		{ //左括号直接进站，若右括号与栈顶失配，则匹配失败
		case '(':
		case '[':
		case '{':
			S.push(exp[i]); break;
		case ')':	if ((S.pop() != '(') || (S.empty()))	return false;	break;
		case ']':	if ((S.pop() != ']') || (S.empty()))	return false;	break;
		case '}':	if ((S.pop() != '}') || (S.empty()))	return false;	break;
		default: break;
		}
	}
	return S.empty();	//整个表达式扫描之后，占中若仍留有（左）括号，则不匹配
}



/*3、栈混洗的甄别（习题集[4.3]）*/
template<typename T>
void check(Stack<T> A, Stack<T> B) //A为原序列，B为待检测的一个栈混洗
{
	Stack<T> rb, S; //栈B转移（复制一份）到栈rb；S为中转栈

	while (!B.empty()) //先将要验证的栈B转移到栈rb
	{
		rb.push(B.pop());
	}

	while (!A.empty())
	{
		S.push(A.pop());

		if (rb.top() == S.top()) //模拟混洗的过程，如果rb栈顶与s中一样，那么就将rb和s都pop。
		{
			rb.pop();
			S.pop();
		}

		while (!S.empty()) //当S栈中还有元素时，需要继续与rb栈中的栈顶元素比较是否相等
		{
			if (S.top() == rb.top())
			{
				rb.pop();
				S.pop();
			}
		}
	}

	return S.empty();  //最后，如果中转栈(S）为空，说明是一个栈混洗
}


/*4、中缀表达式*/
//首先，穿件运算符的优先级的二维表：
constexpr auto N_OPTR = 9;

enum Operator
{
	ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
}; //加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = {
	/*              |-------------------- 当 前 运 算 符 --------------------| */
	/*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

float evalute(char* S, char*& RPN)
{
	Stack<float> opnd; //运算数栈
	Stack<char>	 optr; //运算符栈 

	optr.push('\0');
	while (!optr.empty()) //在运算符栈非空之前，逐个处理表达式各个字符
	{
		if (std::isdigit(*S)) //如果是数字，则将其读取至S栈中，并且将其添加至RPN尾部
		{
			readNumber(S, opnd);
			append(RPN, opnd.top());
		}
		else                 //若果当前字符为运算符，则
		{
			switch (orderBetween(optr.top(), *S))  //视其与运算符栈的栈顶运算符之间的优先级高低分别处理
			{
			case '<':	//栈顶运算符优先级更低时
				optr.push(*S); S++;	break; //计算推迟，当前运算符入栈
			case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
				char op = optr.pop();	append(RPN, op); //栈顶运算符出栈并续接至RPN末尾
				if (op == '!') //若属于一元运算符
				{
					float pOpnd = opnd.pop(); //只需取出一个操作数，并
					opnd.push(calcu(op, pOpnd)); //实施一元计算，结果入栈
				}
				else //对于其他二元运算符
				{
					float pOpnd1 = opnd.pop(); float pOpnd2 = opnd.pop(); //取出 后、前操作数
					opnd.push(calcu(pOpnd1, op, pOpnd2)); //实施二元计算，结果入栈
				}
				break;
			}
			default: std::exit(-1); //当语法错误时，不作处理，直接退出
			}
		}		
	}
	return opnd.pop(); //弹出并返回最后的计算结果
}