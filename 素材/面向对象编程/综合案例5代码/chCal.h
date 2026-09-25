#pragma once
#include "abstrCal.h"
#include <algorithm>
#include <iostream>

// 加法类
class AddCalculator : public AbstractCalculator
{
public:
	double getResult() 
	{
		return num1 + num2;
	}
};

// 减法类
class SubCalculator : public AbstractCalculator
{
public:
	double getResult() 
	{
		return num1 - num2;
	}
};

// 乘法类
class MulCalculator :public AbstractCalculator
{
public:
	double getResult() 
	{
		return num1 * num2;
	}
};

// 除法类
class DivCalculator : public AbstractCalculator
{
public:
	double getResult()
	{
		if (num2 == 0) {
			std::cout << "除数不能为0" << std::endl;
			return 0;
		}
		return num1 / num2;
	}
};

// 求余类
class SurCalculator : public AbstractCalculator
{
public:
	double getResult()
	{
		if (num2 == 0) {
			std::cout << "余数不能为0" << std::endl;
			return 0;
		}
		return (int)num1 % (int)num2;
	}
};

// 乘方类
class PowCalculator : public AbstractCalculator
{
public:
	double getResult()
	{
		return num1 * num1;
	}
};

// 开根类
class SqrtCalculator : public AbstractCalculator
{
public:
	double getResult()
	{
		return sqrt(num1);
	}
};

// 次幂类
class PowpCalculator : public AbstractCalculator
{
public:
	double getResult()
	{
		return pow(num1, num2);
	}
};
