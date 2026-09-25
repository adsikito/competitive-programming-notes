#include "mycode.h"
//外部类
class OuterClass {
public:
	class InnerClass {//嵌套类
	public:
		void func();//嵌套类的func方法
	};
public:
	InnerClass obj;
	//外部类func方法
	void func() {
		cout << "Outerclass func()" << endl;
		obj.func();
	}
};

void OuterClass::InnerClass::func() {
	cout << "InnerClass func()" << endl;
}

void func() {
	class LocalClass {//局部类
	public:
		int num;
		void setNum(int n) {
			num = n;
		}
		void showNum() {
			cout << "num = " << num << endl;
		}
	};

	LocalClass lc;
	lc.setNum(111);
	lc.showNum();
}

void  test03() {
	OuterClass oc1;
	oc1.func();
	cout << "**********************" << endl;
	OuterClass::InnerClass ic1;
	ic1.func();
	cout << "**********************" << endl;
	func();
}



enum index{underflow,overflow}; //枚举
int array_index(int* arr, int n, int index) {
	if (index < 0) throw underflow;
	if (index > n - 1) throw overflow;
	return arr[index];
}
void test02() {
	int* arr = new  int[5];
	for (int i = 0; i < 5; i++) {
		arr[i] = i + 11;
	}
	try {
		//cout << array_index(arr, 5, -2) << endl;
		//cout << array_index(arr, 5, 100) << endl;
		cout << array_index(arr, 5, 2) << endl;
	}
	catch (index e) {
		if (e == underflow) {
			cout << "下标太小了" << endl;
		}
		else if (e == overflow) {
			cout << "下标太大了" << endl;
		}
	}
	
}



class MyExcption :public exception {

public:
	const char* what() const throw() {
		return "my test exception";
	}
};

double mydiv(double v1, double v2) {
	if (v2 == 0) {
		throw "divsion by zero condition";
	}
	return v1 / v2;
}

double  add(double v1, double v2) {
	if (v1 > 0) {//加数v1如果大于0，就抛出自定义的异常MyException
		MyExcption myex;
		throw myex;
	}
	return v1 + v2;
}
void test01() {
	int num1 = 200, num2 = 0, num3;
	
	/*try {
		cout << mydiv(num1, num2) << endl;
	}
	catch (const char *msg) {
		cerr << msg << endl;
	}*/
	
	try {
		cout << add(num1, num2) << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	

	cout << 1111 << endl;
}