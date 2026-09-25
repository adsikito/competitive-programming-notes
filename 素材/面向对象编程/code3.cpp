

#include <iostream>

using namespace std;

////动物类
//class Animal {
//public:
//	string name;//名字
//	int age;//年龄
//public:
//	Animal(){}
//	Animal(string name, int age) {
//		this->name = name;
//		this->age = age;
//	}
//	//打印信息的方法
//	void printInfo() {
//		cout << "名字叫:" << this->name << "  年龄是:" << this->age << endl;
//	}
//};
////创建Dog类来继承Animal类
//class Dog : public Animal {
//public:
//	Dog() {}
//	Dog(string name,int age,char sex) {
//		this->name = name;
//		this->age = age;
//		this->sex = sex;
//	}
//
//public:
//	char sex;//性别
//};
//
//
//
//class Person {
//public:
//	string name;
//protected:
//	int age;
//private:
//	double height;
//public:
//
//	Person() {}
//
//	Person(string name, int age, double height):name(name),age(age),height(height) {}
//	/*Person(string name, int age,double height) {
//		this->name = name;
//		this->age = age;
//		this->height = height;
//	}*/
//
//
//	//通过setName方法给name成员变量赋值
//	void setName(string name) {
//		this->name = name;
//	}
//	//通过setAge方法给age成员变量赋值
//	void setAge(int age) {
//		this->age = age;
//	}
//	//通过setHeight方法给height成员变量赋值
//	void setHeight(double height) {
//		this->height = height;
//	}
//
//	//打印信息的方法
//	void printInfo() {
//		cout << "名字:" << this->name << " 年龄:" << this->age << " 身高:" << this->height << endl;
//	}
//};
//
//class Student :public Person {
//public:
//	using Person::Person;
//	Student() {}
//	Student(string name, int age, double height, double score) :Person(name, age, height), score(score) {}
//
//	void showInfo() {
//		cout << "名字 " << this->name << " 年龄" << this->age << "  身高 " << endl;
//	}
//public:
//	double score;
//};

//class Animal {
//public:
//	Animal() {
//		cout << "call Animal" << endl;
//	}
//	~Animal() {
//		cout << "call ~Animal" << endl;
//	}
//};
//
//class Monkey :public Animal{
//public:
//	Monkey() {
//		cout << "call Monkey" << endl;
//	}
//	~Monkey() {
//		cout << "call ~Monkey" << endl;
//	}
//};
//
//class GoldenMonkey :public Monkey {
//public:
//	GoldenMonkey() {
//		cout << "Call GoldenMonkey" << endl;
//	}
//};


//class Animal {
//protected:
//	string nickName;
//public:
//	Animal() {
//
//	}
//	Animal(string name):nickName(name) {}
//};
//class Person {
//protected:
//	string name;
//public:
//	Person(){}
//	Person(string name) :name(name) {}
//
//};
//class Xtq : public Animal, public Person {
//private:
//	char sex;
//public:
//	Xtq() {}
//	Xtq(string nickName, string name, char sex) :Animal(nickName), Person(name), sex(sex) {}
//	void printInfo() {
//		cout << this->nickName << "  " << this->name << "  " << this->sex << endl;
//	}
//};


//class Person {
//public:
//	Person() {
//		cout << "call Person" << endl;
//	}
//	void printInfo() {
//		cout << "Person info" << endl;
//	}
//};
//class Worker {
//public:
//	Worker() {
//		cout << "call Worker" << endl;
//	}
//	void printInfo() {
//		cout << "Worker info" << endl;
//	}
//};
//
//class Ai :public Worker,public Person {
//public:
//	Ai() :Person(), Worker() {
//		cout << "call Ai" << endl;
//	}
//	void info() {
//		Person::printInfo();
//		Worker::printInfo();
//	}
//};

//class A {
//protected:
//	int m_a;
//public:
//	A(int a):m_a(a){}
//	void printInfo() {
//		cout << this->m_a  << endl;
//	}
//};
//class B : virtual public A {
//protected:
//	int m_b;
//public:
//	B(int a, int b) :A(a), m_b(b) {}
//	void printInfo() {
//		cout << this->m_a << "  " << this->m_b << "  " << endl;
//	}
//};
//class C : virtual public A {
//protected:
//	int m_c;
//public:
//	C(int a,int c):A(a),m_c(c){}
//	void printInfo() {
//		cout << this->m_a << "  "  << this->m_c <<  endl;
//	}
//};
//class D :public B, public C {
//protected:
//	int m_d;
//public:
//	D(int a,int b,int c ,int d):A(a),B(90,b),C(100,c),m_d(d){}
//
//	void seta(int a) {
//		this->m_a = a;
//	}
//	void setb(int b) {
//		this->m_b = b;
//	}
//	void setc(int c){
//		this->m_c = c;
//	}
//	void setd(int d) {
//		this->m_d = d;
//	}
//
//	void printa() {
//		cout << this->m_a << endl;
//	}
//	void printInfo() {
//		cout << this->m_a << "  " << this->m_b << "  " << this->m_c << " " << this->m_d << endl;
//	}
//};

class Animal {
private:
	string name;
	int weight;
public:
	Animal(string name, int weight) :name(name), weight(weight) {}
	void who() {
		cout << "name is " << this->name << " weight is " << this->weight << endl;
	}
};

class Lion :public Animal {
public:
	Lion(string name, int weight) :Animal(name, weight) {}
};
class Aardvark :public Animal {
public:
	Aardvark(string name, int weight) :Animal(name, weight) {}
};

int main() {

	Lion lion("leo", 400);
	lion.who();
	Aardvark a1("djfj", 600);
	a1.who();


	/*A a1(111);
	a1.printInfo();
	B b1(112, 222);
	b1.printInfo();
	C c1(113, 333);
	c1.printInfo();
	D d1(114, 2223, 3333, 444);
	d1.printInfo();*/


	/*D d1;
	d1.seta(100);
	d1.printa();*/


	/*Ai a1;
	a1.info();*/


	/*Xtq x1("gg", "xtq", 'M');
	x1.printInfo();*/
	


	//GoldenMonkey gm1;
	
	//Monkey m1;















	/*Student s1;
	Student s2("xiaoming", 11, 1.5, 99);
	s2.printInfo();*/

	/*Person p1("zxx", 20,1.9);
	p1.printInfo();*/

	/*Student s1;
	
	s1.setName("xm");
	s1.setAge(20);
	s1.setHeight(1.7);
	s1.printInfo();*/
	

	/*Dog d1("wangcai", 3, 'F');
	d1.printInfo();*/

	return 0;
}

