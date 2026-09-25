#pragma once
// 抽象计算基类
class AbstractCalculator
{
public:
	//写上virtual关键字，方便下面的类继承时的同名函数进行重写,纯虚函数，用来得到计算结果
	virtual double getResult() = 0;
	double num1, num2;
};
