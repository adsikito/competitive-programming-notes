

#include <iostream>

using namespace std;

////class  classname
//class Student {
//public://修饰符的后面是冒号;
//	Student() {
//		cout << "Student mm" << endl;
//	}
//	Student(string name,int age) {
//		this->name = name;
//		this->age = age;
//		cout << "Student method" << endl;
//	}
//	
//	~Student() {
//		cout << "call ~ Student()" << endl;
//	}
//	void printName(string name = "赵六") {
//		cout <<"printNam() ->" << name << endl;
//	}
//	void printName(string name, int age, char sex) {
//		cout << "name = " << name << "  age=" << age << " sex = " << sex << endl;
//	}
//	static void sayHello() {
//		cout << "this is sayHello()" << course << endl;
//	}
//	void sayHi()const {
//		cout << "sayHi()->" << course << endl;
//		cout << "sayHi()->" << this->name << endl;
//		cout << "sayHi()->" << this->age << endl;
//	}
//public:
//	string name;
//	int age;
//	static string course;
//};
//
//class Complex {
//public:
//	double m_real, m_imag;
//	Complex(double real, double imag) {
//		m_real = real;
//		m_imag = imag;
//	}
//	Complex(const Complex& c) {
//		m_real = c.m_real;
//		m_imag = c.m_imag;
//		cout << "我的调用了" << endl;
//	}
//};
//class Person {
//public:
//	Person() {
//		cout << "call Person()" << endl;
//	}
//	~Person() {
//		cout << "call ~Person()" << endl;
//	}
//};
//string Student::course = "c++";


class  Student {
public:
	Student(string name, int age) {
		this->name = name;
		this->age = age;
	}
	void show() {
		cout << "this ->" << this << endl;
	}
	string name;
	int age;
};

//创建矩形类
class Rect {
private:
	double width, height; //定义私有的成员变量宽和高
public:
	//构造函数
	Rect(double width, double height) {
		this->width = width;
		this->height = height;
	}
	//判断是否是正方形
	bool is_square() {
		return this->width == this->height; //长宽相等返回true，否则返回false
	}
	//输出矩形面积
	void area() {
		cout << this->width * this->height << endl;
	}
};
int main() {

	Rect r1(100,100);
	bool b = r1.is_square();
	if (b) {
		cout << "r1是正方形" << endl;
	}
	else {
		cout << "r1不是正方形" << endl;
	}
	r1.area();
	

	//Student s1("za", 21);
	//s1.show();
	//cout << "s1->" << &s1 << endl;
	//Student s2("ejj", 22);
	//s2.show();
	//cout << "s2 ->" << &s2 << endl;

	/*Student s1("zs", 21);
	s1.sayHi();*/

	/*Student::sayHello();
	Student s1;
	s1.sayHello();*/
	
	/*cout << "course=" << Student::course << endl;
	Student s1;
	cout << "s1 course = " << s1.course << endl;*/
	/*Student s1;
	s1.name = "张三";
	s1.age = 22;
	s1.printName();
	s1.printName("王五", 100, 'M');*/

	

	/*char* pc = new char[100];
	int* pi = new int[100];
	int* pi2 = new int [10] {1, 2, 3, 4, 5};*/

	//Student stu[] = { {"zs",20},{"ww",19}};
	/*Student* pstu = new Student[10];
	delete[] pstu;*/

	/*Person *p1 = new Person;

	delete p1;*/


	/*Student s1(30);
	Student stu(20);*/

	//Complex c1(1, 2);
	////Complex c2(c1);
	//Complex c2 = c1;
	//cout << c2.m_real << "  " << c2.m_imag << endl;

	return 0;
}

