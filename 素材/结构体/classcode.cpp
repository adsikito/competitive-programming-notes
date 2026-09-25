
#include <iostream>

using namespace std;

struct student {
	string name{ "赵四" };
	int age{ 20 };
	double score=100;
	
	void printInfo() {
		cout << name <<"  " << age << "  " << score << endl;
		
	}
	
};// s1, s2, s3;

void printStudent(student s) {
	cout << s.name << " " << s.age << " " << s.score << endl;
}

void printStudent2(student* ps) {
	ps->printInfo();
}

void printStudent3(student s[], int len) {
	for (int i = 0; i < len; i++) {
		s[i].printInfo();
	}
}

union person {
	int age;
	double weight;
};



int main() {

	//student s1, s2, s3={"王五",19,90};// s3定义变量后，直接初始化成员

	//s1.name = "张三";
	//s1.age = 21;
	//s1.score = 99.5;

	//cout << s1.name << endl;
	//cout << s3.name << endl;
	//cout << s2.name << endl;



	/*student s1;
	s1.printInfo();*/


	//结构体指针
	/*student s1, * ps1;
	ps1 = &s1;

	ps1->age = 29;

	cout << ps1->name << endl;
	cout << ps1->age << endl;
	cout << (*ps1).score << endl;*/


	//结构体数组
	//student s[3];
	//for (int i = 0; i < 3; i++) {
	//	cin >> s[i].name >> s[i].age >> s[i].score;
	//}
	//for (int i = 0; i < 3; i++) {
	//	//cout << s[i].name << " " << s[i].age << " " << s[i].score << endl;
	//	s[i].printInfo();
	//}


	//结构体作为函数参数使用
	/*student s1 = { "王五",21,99 };
	printStudent(s1);*/


	//student s1 = { "王五",21,88 };
	//student* ps2 = &s1;
	//printStudent2(ps2);
	//printStudent2(&s1);


	//结构体数组作为函数参数
	/*student arrs[3] = { {"李四",20,100},{"王五",21,99},{"张三",22,91}};
	printStudent3(arrs, 3);*/



	//共用体
	/*person p1;
	p1.age = 20;
	p1.weight = 50.5;
	cout << p1.age << endl;
	cout << p1.weight << endl;*/


	//结构体和共用体字节数的查看
	//student s1;
	//person p1;

	//int lens = sizeof(s1);
	//int lenp = sizeof(p1);
	//cout << lens << endl;
	//cout << lenp << endl;


	//enum{a,b,c} m1,m2;
	//enum color { red, green, blue } c1,c2;
	//enum week{Sun=100,Mon,Tue=1,Wed,Thu,Fri,Sta};
	//week w1, w2; //w1，w2是week枚举型的变量
	//w1 = Sun;
	////w2 = 0; //整型是不能赋值给枚举型
	//w2 = Wed;

	////cin >> w2;  //枚举型不能输入赋值

	//if (w1 < w2) {
	//	cout << "w1 < w2" << endl;;
	//}
	//cout << w1 << endl;
	//cout << w2 << endl;

	//int num = w1 + w2;  //枚举型可以赋值给整型
	//cout << w1 + w2 << endl;


	//c1 = m1;  不同枚举类型之间是不能赋值的
	//m1 = m2;


	//typedef的使用

	//普通数据类型
	/*typedef int myint;

	myint num;
	num = 100;
	cout << num << endl;

	int num2 = 200;
	cout << num2;*/

	//结构体类型
	/*typedef student stu;
	stu s1;
	s1.name = "typedef";
	cout << s1.name << endl;*/

	//数组
	/*typedef int arr[10];
	arr a;
	a[0] = 100;
	cout << a[0];*/


	//枚举型
	/*enum week { Sun = 100, Mon, Tue = 1, Wed, Thu, Fri, Sta };
	typedef week w;

	w w1;
	w1 = Sun;
	cout << w1 << endl;*/


	//指针
	/*typedef const char* str;
	str s = "abcd";

	cout << s << endl;*/




	return 0;
}

