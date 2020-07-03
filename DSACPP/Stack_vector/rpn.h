#pragma once

#include "stack.h"
#include <cstdint>
#include "stack_apply.cpp"

double calcu(double a, char op, double b);

double calcu(char op, double b);
std::int_fast64_t Factorial(int n); //¼ÆËã½×³Ë

void readNumber(char*& s, Stack<float>& stack);

void append(char*&, double);
void append(char*&, char);

char orderBetween(char, char);
Operator optr2rank(char op);
