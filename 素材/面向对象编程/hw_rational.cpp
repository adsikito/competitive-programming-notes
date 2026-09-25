#include<iostream>
#include<string>
#include<stdlib.h>
class Rational
{
public:
	Rational(int num, int denom);//num=分子 ，denom=分母
 
	Rational operator+(Rational rhs);
	Rational operator-(Rational rhs);
	Rational operator*(Rational rhs);
	Rational operator/(Rational rhs);
 
	void printf();
	
private:
	void normalize();//负责对分数的简化处理
 
	int numerator;	//分子
	int denominator;//分母
};
 
Rational::Rational(int num, int denom)
{
	numerator = num;
	denominator = denom;
 
	normalize();
}
 
//normalize()对分数进行简化操作包括：
//1、只允许分子为负数，如果分母为负数则把负数挪到分子部分，如1/-2 == -1/2
//2、利用欧几里德算法（辗转求余原理）将分数进行简化：2/10 =》1/5
void Rational::normalize()
{
	//确保分母为正
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
 
	//欧几里德算法
	int a = abs(numerator);
	int b = abs(denominator);
 
	//求出最大公约数
	while (b > 0)
	{
		int t = a%b;
		a = b;
		b = t;
	}
 
	//分子、分母分别?最大公约数得到最简化分数
	numerator /= a;
	denominator /= a;
}
 
// a   c   a*d   c*b   a*d  + c*b
// - + - = --- + --- = ----------
// b   d   b*d   b*d       b*d
Rational Rational::operator+(Rational rhs)
{
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;
 
	int e = a*b + c*d;
	int f = b*d;
 
	return Rational(e,f);
}
 
// a   c   a   -c  
// - - - = - + ---
// b   d   b    d 
Rational Rational::operator-(Rational rhs)
{
	rhs.numerator = -rhs.numerator;
	
	return operator+(rhs);
}
 
 
// a   c   a*d
// - * - = ---
// b   d   b*d
Rational Rational::operator*(Rational rhs)
{
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;
 
	int e = a*c;
	int f = b*d;
	
	return  Rational(e,f);
}
 
// a   c   a   d
// - / - = - * -
// b   d   b   c
Rational Rational::operator/(Rational rhs)
{
	int t = rhs.numerator;
	rhs.numerator = rhs.denominator;
	rhs.denominator = t;
 
	return operator*(rhs);
}
 
void Rational::printf()
{
	if (numerator%denominator == 0)
		std::cout << numerator / denominator;
	else
		std::cout << numerator << "/" << denominator;
}
 
int main()
{
	Rational f1(2, 16);
	Rational f2(7, 8);
 
	//测试有理数加法
	Rational res = f1 + f2;
	f1.printf();
	std::cout << "+";
	f2.printf();
	std::cout << "=";
	res.printf();
	std::cout << "\n";
 
	//测试有理数减法
	res = f1 - f2;
	f1.printf();
	std::cout << '-';
	f2.printf();
	std::cout << '=';
	res.printf();
	std::cout << "\n";
 
	//测试有理数乘法
	res = f1 * f2;
	f1.printf();
	std::cout << "*";
	f2.printf();
	std::cout << "=";
	res.printf();
	std::cout << "\n";
 
	//测试有理数除法
	res = f1 / f2;
	f1.printf();
	std::cout << '/';
	f2.printf();
	std::cout << '=';
	res.printf();
	std::cout << "\n";
	return 0;
}