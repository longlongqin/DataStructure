#pragma once
/*栈的应用*/
#include "stack.h"
#include <cstdint> //int_fast32_t



/*1、逆序输出——进制转换*/
void convert(Stack<char>& s, std::int_fast32_t n, int base); //递归版
void convert1(Stack<char>& s, std::int_fast32_t n, int base); //迭代版

/*2、括号匹配*/
bool paren(const char exp[], int lo, int hi); //迭代实现

// “递归实现”
// 的时候，是基于括号的计数实现的，它只能进行匹配某一特定
// 的括号。但如果表达式中有不同的括号，那么递归实现使用的计数策略
// 就不行了。

/*3、栈混洗的甄别（习题集[4.3]）*/
//参考：https://www.twblogs.net/a/5c0a2509bd9eee6fb37b6f4e?lang=zh-cn
template<typename T>
void check(Stack<T> A, Stack<T> B);

/*4、中缀表达式*/
float evalute(char* S, char*& RPN);






/*5、逆波兰表达式*/
