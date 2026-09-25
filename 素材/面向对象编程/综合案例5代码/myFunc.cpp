#include "myFunc.h"
#include "chCal.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void quit()
{
	char select;
	cout << "确定退出吗？(Y/N)" << endl;
	cin >> select;
	if (select == 'Y' || select == 'y')
	{
		cout << "欢迎下次使用" << endl;
		// 退出
		exit(0);
	}
	else
		system("cls");
}

void menu()
{
	cout << "*******************************" << endl
		<< "******      1.加法       ******" << endl
		<< "******      2.减法       ******" << endl
		<< "******      3.乘法       ******" << endl
		<< "******      4.除法       ******" << endl
		<< "******      5.取余       ******" << endl
		<< "******      6.乘方       ******" << endl
		<< "******      7.开根       ******" << endl
		<< "******      8.次幂       ******" << endl
		<< "******      Q.退出       ******" << endl
		<< "*******************************" << endl;
}

void Add(double a, double b)
{
	cout << "请输入a和b的值" << endl;
	cin >> a >> b;
	AbstractCalculator* p = new AddCalculator;
	p->num1 = a;
	p->num2 = b;
	cout << a << " + " << b << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Sub(double a, double b)
{
	cout << "请输入a和b的值" << endl;
	cin >> a >> b;
	AbstractCalculator* p = new SubCalculator;
	p->num1 = a;
	p->num2 = b;
	cout << a << " - " << b << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Mul(double a, double b)
{
	cout << "请输入a和b的值" << endl;
	cin >> a >> b;
	AbstractCalculator* p = new MulCalculator;
	p->num1 = a;
	p->num2 = b;
	cout << a << " * " << b << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Div(double a, double b)
{
	cout << "请输入a和b的值" << endl;
	cin >> a >> b;
	AbstractCalculator* p = new DivCalculator;
	p->num1 = a;
	p->num2 = b;
	cout << a << " / " << b << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Sur(double a, double b)
{
	cout << "请输入a和b的值" << endl;
	cin >> a >> b;
	AbstractCalculator* p = new SurCalculator;
	p->num1 = a;
	p->num2 = b;
	cout << a << " % " << b << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Pow(double a)
{
	cout << "请输入a的值" << endl;
	cin >> a;
	AbstractCalculator* p = new PowCalculator;
	p->num1 = a;
	cout << a << " * " << a << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Sqrt(double a)
{
	cout << "请输入a的值" << endl;
	cin >> a;
	AbstractCalculator* p = new SqrtCalculator;
	p->num1 = a;
	cout << p->num1 << "开根 " << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}

void Powp(double a, double b)
{
	cout << "请输入a和b的值" << endl;
	cin >> a >> b;
	AbstractCalculator* p = new PowpCalculator;
	p->num1 = a;
	p->num2 = b;
	cout << a << " ^ " << b << " = " << p->getResult() << endl;
	delete p;
	cout << "按任意键继续" << endl;
	system("pause");
	system("cls");
}
