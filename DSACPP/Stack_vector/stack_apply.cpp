#include "stack_apply.h"
#include "rpn.h"
#include <cassert>  // assert
#include <cctype>  // isdigit
#include <cstdlib> // exit

/*1�����������������ת��*/
//�ݹ��
void convert(Stack<char>& s, std::int_fast32_t n, int base)
{
	//assert((base > 1 && base <= 16) && "ת��Ϊ�Ľ�����Ӧ����(1,16]���䡣");
	static char digit[] ={ '0', '1', '2', '3', '4', '5', '6','7','8','9',
							'A', 'B','C', 'D','E','F', };
	if (n > 0) //����������ʱ�������Ľ���
	{
		s.push(digit[n % base]); //��ÿ�γ��Ԧ�֮������� ��ջ
		convert(s, n / base, base);
	}
}

//������
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

/*2������ƥ��*/
template<typename T>
bool paren(const char exp[], int lo, int hi)
{
	Stack<T> S; //ʹ��ջ ��¼�Ѿ����ֵ���δƥ�������
	for (int i = lo, i <= hi; ++i)
	{
		switch (exp[i])
		{ //������ֱ�ӽ�վ������������ջ��ʧ�䣬��ƥ��ʧ��
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
	return S.empty();	//�������ʽɨ��֮��ռ���������У������ţ���ƥ��
}



/*3��ջ��ϴ�����ϰ�⼯[4.3]��*/
template<typename T>
void check(Stack<T> A, Stack<T> B) //AΪԭ���У�BΪ������һ��ջ��ϴ
{
	Stack<T> rb, S; //ջBת�ƣ�����һ�ݣ���ջrb��SΪ��תջ

	while (!B.empty()) //�Ƚ�Ҫ��֤��ջBת�Ƶ�ջrb
	{
		rb.push(B.pop());
	}

	while (!A.empty())
	{
		S.push(A.pop());

		if (rb.top() == S.top()) //ģ���ϴ�Ĺ��̣����rbջ����s��һ������ô�ͽ�rb��s��pop��
		{
			rb.pop();
			S.pop();
		}

		while (!S.empty()) //��Sջ�л���Ԫ��ʱ����Ҫ������rbջ�е�ջ��Ԫ�رȽ��Ƿ����
		{
			if (S.top() == rb.top())
			{
				rb.pop();
				S.pop();
			}
		}
	}

	return S.empty();  //��������תջ(S��Ϊ�գ�˵����һ��ջ��ϴ
}


/*4����׺���ʽ*/
//���ȣ���������������ȼ��Ķ�ά��
constexpr auto N_OPTR = 9;

enum Operator
{
	ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
}; //�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char pri[N_OPTR][N_OPTR] = {
	/*              |-------------------- �� ǰ �� �� �� --------------------| */
	/*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

float evalute(char* S, char*& RPN)
{
	Stack<float> opnd; //������ջ
	Stack<char>	 optr; //�����ջ 

	optr.push('\0');
	while (!optr.empty()) //�������ջ�ǿ�֮ǰ�����������ʽ�����ַ�
	{
		if (std::isdigit(*S)) //��������֣������ȡ��Sջ�У����ҽ��������RPNβ��
		{
			readNumber(S, opnd);
			append(RPN, opnd.top());
		}
		else                 //������ǰ�ַ�Ϊ���������
		{
			switch (orderBetween(optr.top(), *S))  //�����������ջ��ջ�������֮������ȼ��ߵͷֱ���
			{
			case '<':	//ջ����������ȼ�����ʱ
				optr.push(*S); S++;	break; //�����Ƴ٣���ǰ�������ջ
			case '>': { //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
				char op = optr.pop();	append(RPN, op); //ջ���������ջ��������RPNĩβ
				if (op == '!') //������һԪ�����
				{
					float pOpnd = opnd.pop(); //ֻ��ȡ��һ������������
					opnd.push(calcu(op, pOpnd)); //ʵʩһԪ���㣬�����ջ
				}
				else //����������Ԫ�����
				{
					float pOpnd1 = opnd.pop(); float pOpnd2 = opnd.pop(); //ȡ�� ��ǰ������
					opnd.push(calcu(pOpnd1, op, pOpnd2)); //ʵʩ��Ԫ���㣬�����ջ
				}
				break;
			}
			default: std::exit(-1); //���﷨����ʱ����������ֱ���˳�
			}
		}		
	}
	return opnd.pop(); //�������������ļ�����
}