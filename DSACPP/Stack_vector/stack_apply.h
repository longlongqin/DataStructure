#pragma once
/*ջ��Ӧ��*/
#include "stack.h"
#include <cstdint> //int_fast32_t



/*1�����������������ת��*/
void convert(Stack<char>& s, std::int_fast32_t n, int base); //�ݹ��
void convert1(Stack<char>& s, std::int_fast32_t n, int base); //������

/*2������ƥ��*/
bool paren(const char exp[], int lo, int hi); //����ʵ��

// ���ݹ�ʵ�֡�
// ��ʱ���ǻ������ŵļ���ʵ�ֵģ���ֻ�ܽ���ƥ��ĳһ�ض�
// �����š���������ʽ���в�ͬ�����ţ���ô�ݹ�ʵ��ʹ�õļ�������
// �Ͳ����ˡ�

/*3��ջ��ϴ�����ϰ�⼯[4.3]��*/
//�ο���https://www.twblogs.net/a/5c0a2509bd9eee6fb37b6f4e?lang=zh-cn
template<typename T>
void check(Stack<T> A, Stack<T> B);

/*4����׺���ʽ*/
float evalute(char* S, char*& RPN);






/*5���沨�����ʽ*/
