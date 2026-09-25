
#include "mycode.h"

int getCharNum(string s, char c) {
	int cnt = 0;
	for_each(s.begin(), s.end(), [&](char ch) {
		if (c == ch) {
			cnt++;
			}
		});
	return cnt;
}

void test28() {

	string s1;
	cin >> s1;
	char ch;
	cin >> ch;
	cout << getCharNum(s1, ch) << endl;
}

void test27() {

	unordered_multimap<string, int> umm1 = { {"aaa",111},{"bbb",222},{"ccc",333},{"aaa",111} };

	for (auto it = umm1.begin(); it != umm1.end(); it++) {
		cout << it->first << "  " << it->second << endl;
	}


}

void test26() {

	//空的map
	unordered_map<string, int> mp1;

	//列表初始化
	unordered_map<string, int> mp2 = { {"aa",1},{"bb",2},{"cc",3}};

	//拷贝构造函数
	unordered_map<string, int> mp3(mp2);

	//迭代器初始化
	unordered_map<string, int> mp4(mp2.begin(), mp2.end());



	cout << mp2.at("aa") << endl;

	for (auto it = mp2.begin(); it != mp2.end(); it++) {
		cout << it->first << "  " << it->second << endl;
	}
}

void test25() {

	unordered_multiset<int> um1 = { 11,33,11,22,55,66,99,33 };
	for (auto it = um1.begin(); it != um1.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	cout << um1.empty() << endl;
	cout << um1.max_size() << endl;
	cout << um1.size() << endl;

	um1.insert(200);
}


void test24() {

	//空的set
	unordered_set<int> set1;

	//通过拷贝构造函数
	unordered_set<int> set2(set1);


	//迭代构造
	unordered_set<int> set3(set1.begin(), set1.end());

	int arr[] = { 1,2,3,4,5 };
	unordered_set<int> set4(arr, arr + 5);

	unordered_set<int> set5(move(set2));


	unordered_set<int> set6 = { 11,22,55,33,88 };

	cout << set6.empty() << endl;

	cout << *(set6.find(11)) << endl;

	cout << set6.count(66) << endl;

	set6.insert(100);
	set6.insert({ 200,300,400,500 });
	set6.insert(set6.begin(), 999);
	set6.insert(set4.begin(), set4.end());

	for (auto it = set6.begin(); it != set6.end(); it++) {
		cout << *it << " ";
	}

}

void test23() {
	//创建一个空的单向链表
	forward_list<int> value1;

	//包含n个元素的单向链表
	forward_list<int> v2(10);


	//创一个包含n个元素的单向链表并指定初始值
	forward_list<int> v3(5, 11);

	//通过拷贝构造函数创建
	forward_list<int> v4(v3);


	//通过拷贝其他类型的容器
	int arr_num[] = { 1,2,3,4,5 };
	forward_list<int> v5(arr_num, arr_num + 5);

	array<int, 10> arr_num2 = { 66,55,11,22,33 };
	forward_list<int> v6(arr_num2.begin(), arr_num2.end());

	v6.push_front(100);
	v6.emplace_front(200);
	cout << v6.front() << endl;

	v6.sort();

	for (auto it = v6.begin(); it != v6.end(); it++) {
		cout << *it << " " << endl;
	}



}

void test22() {
	//固定的数据类型和长度
	array<int, 5> arr1;

	//给部分或者全部的初始值
	array<int, 10> arr2 = { 1,2,3 };

	int len = 3;
	//array<int, len> arr3 = { 11,2,33 };


	cout << arr2[0] << endl;
	cout << arr2.at(1) << endl;
	cout << get<2>(arr2) << endl;

	cout << arr2.front() << endl;
	cout << arr2.back() << endl;
}


class ClassTest {
private:
	int n;

public:
	ClassTest() = default;
	ClassTest(int num):n(num){}
	ClassTest(const ClassTest&) = delete;
	ClassTest& operator=(const ClassTest& ct);
};
ClassTest& ClassTest::operator=(const ClassTest& ct) = default;
void test21() {

	ClassTest ct1;

}
template<class T,class... U>
void funcName112(T first,U...args) {
	cout << "接收到的参数：" << first << endl;
	if constexpr (sizeof...(args) > 0) {
		funcName112(args...);
	}
}

void test20() {
	funcName112(11, 22, 33, 44, 55);
}

void funcName111() {
	cout << "递归函数终止" << endl;
}
template<class T,class... U>
void funcName111(T first,U... others) {
	cout << "接收到的参数:" << first << endl;
	funcName111(others...);
}


template<class...T>
void func11(T...args) {
	cout << sizeof...(args) << endl;
	cout << sizeof...(T) << endl;
}

void test19() {
	funcName111(11,22,33,44,55,66);

}
void test18() {
	func11(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}

class CB;
class CA {
private:
	weak_ptr<CB> m_ptr_b;
public:
	CA() {
		cout << "CA() called" << endl;
	}
	~CA() {
		cout << "~CA() called" << endl;
	}
	void set_ptr(shared_ptr<CB>& ptr) {
		m_ptr_b = ptr;
	}
	void b_use_count() {
		cout << "b use count:" << m_ptr_b.use_count() << endl;
	}
	void show() {
		cout << "this is class CA" << endl;
	}
};
class CB {
private:
	shared_ptr<CA> m_ptr_a;
public:
	CB() {
		cout << "CB() called" << endl;
	}
	~CB() {
		cout << "~CB() called" << endl;
	}

	void set_ptr(shared_ptr<CA>& ptr) {
		m_ptr_a = ptr;

	}
	void a_use_count() {
		cout << "a use count:" << m_ptr_a.use_count() << endl;
	}
	void show() {
		cout << "this is CB" << endl;
	}
};

void test17() {
	shared_ptr<CA> ptr_a(new CA());
	shared_ptr<CB> ptr_b(new CB());

	cout << "a use count:" << ptr_a.use_count() << endl;
	cout << "b use count:" << ptr_b.use_count() << endl;

	ptr_a->set_ptr(ptr_b);
	ptr_b->set_ptr(ptr_a);

	cout << "a use count:" << ptr_a.use_count() << endl;
	cout << "b use count:" << ptr_b.use_count() << endl;
}

void deleteInt(int* p) {
	delete[] p;
}

void  test16() {

	//指定 default_delete 作为释放规则
	shared_ptr<int> p1(new int[10], default_delete<int[]>());

	//自定义释放规则
	shared_ptr<int> p2(new int[10], deleteInt);


}

void test15() {
	shared_ptr<int> p1;
	shared_ptr<int> p2(nullptr);

	shared_ptr<int> p3(new int(3));
	shared_ptr<int> p4 = make_shared<int>(3);


	shared_ptr<int> p5(p4); // 
	shared_ptr<int> p6 = p5;

	shared_ptr<int> p7(move(p6));

}

struct Goods {
	string name;
	double price;
};

struct Compare
{
	bool operator()(const Goods& gl, const Goods& gr) {
		return  gl.price <= gr.price;
	}
};

void test14() {
	Goods gds[] = { {"苹果",10},{"香蕉",6.1},{"橙子",7},{"香梨",12}};
	//sort(gds, gds + sizeof(gds) / sizeof(gds[0]), Compare());

	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& gl, const Goods& gr) ->bool {return gl.price < gr.price; });
	for (int i = 0; i < 4; i++) {
		cout << gds[i].name << "   " << gds[i].price << endl;
	}
}

void test13() {
	int array[] = { 2,4,1,5,3,9,8,7,0 };
	sort(array, array + sizeof(array) / sizeof(array[0]));

	for (int i = 0; i < 9; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());
	for (int i = 0; i < 9; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

class Rate {
private:
	double _rate;
public:
	Rate(double rate) :_rate(rate) {}
	double operator()(double money, int year) {
		return money * _rate * year;
	}
};

void test12() {
	double rate = 0.8;
	Rate r1(rate);
	double rd = r1(20000, 2);
	cout << rd << endl;


	//匿名函数的方式
	auto r2 = [=](double money, int year) ->double {return  money * rate * year; };
	double rd2 = r2(20000, 2);
	cout << rd2 << endl;
}


void(*FP)();//函数指针
void test11() {
	//最简单的lambda表达式，没有任何意义
	[] {};

	//省略掉参数列表和返回值类型，返回类型由编译器来推导
	int n1 = 100, n2 = 200;
	auto fun0 = [&n1, &n2] {return n1 + n2; };
	cout << fun0() << endl;

	//省略返回值类型，返回类型由编译器来推导
	auto fun1 = [&n1, &n2](int n3) {n2 = n1 + n3; };
	fun1(300);
	cout << n1 << "  " << n2 << endl;


	//捕获列表可以是lambda表达式
	auto fun2 = [fun1] {cout << "hello C++" << endl; };
	fun2();


	//各部分比较完善的lambda表达式
	auto fun3 = [=, &n1](int n3) ->int {return  n1 * n1+n3; };
	cout << fun3(11) << endl;

	//auto fun4 = [&n1, &n2](int n3) {n2 = n1 + n3; };
	//fun1 = fun4;

	//赋值捕获
	int v1 = 12;
	auto fun5 = [v1](int v2) mutable {v1 = v1 * 3; return v2 + v1; };
	cout << fun5(2) << endl;

	//允许使用一个lambda表示拷贝一构造一个新的副本
	auto fun6(fun5);
	fun6(11);

	//可以将lambda表示赋值给相同类型的函数指针

	auto fun7 = [] {};
	FP = fun7;
	FP();

}

void test10() {
	vector<int> v1 = { 1,1,3,4,5,6 };
	for (auto i : v1) {
		cout << i << " ";
	}
}

class ClassNum {
public:
	ClassNum(int n1=0,int n2 =0):_x(n1),_y(n2){}
	void printInfo() {
		cout << _x << "  " << _y << endl;
	}
private:
	int _x, _y;
};

void test09() {

	int num1 = { 200 };
	int num2{ 100 };
	cout << num1 << endl;
	cout << num2 << endl;

	//数组
	int ar1[] = { 1,2,3,4,5 };
	int ar2[]{ 2,3,4,5,6 };

	vector<int> {1, 2, 3, 4, 6};
	map<int, int> mp1{ {1,11},{2,22},{3,33} };

	ClassNum cn1{ 1,2 };
	cn1.printInfo();

}

int num1 = 100;
int& returnNum() {
	return num1;
}

void test08() {
	int num2 = 10;
	int num3 = num2;
	int* p1 = new int(10);


	const int num4 = 20;
	//num4 = num1;

	cout << &num4 << endl;
	//num2 + 100 = 300;

	returnNum() = 999;

 }


int func2(int v1, int v2) {
	return v1 + v2;
}
void test07() {
	const int&& num1 = 100;
	int&& num2 = func2(10, 20);
	cout << num1 << endl;
	cout << num2 << endl;
}









template<class R,class T,class U>
auto add(T t, U u) ->decltype(t + u) {
	return t + u;
}

void test06() {
	int v1 = 100;
	double v2 = 2.323;
	auto v3 = add<decltype(v1 + v2)>(v1,v2);
	cout << v3 << endl;
}

void test05() {
	auto num1 = 100, num2 = 200;
	decltype(num1 + num2) num3;
	cout << typeid(num3).name() << endl;
}

template<class T>
class Student {
private:
	//auto name;
	//auto age;
	int age;
};




void test04() {
	int ar[10] = { 1,2,3 };
	auto ar2 = ar;
	//auto ar3[1] = ar;

}


void test03() {

	Student<int> s1;
	//Student<auto> s2;
}
void test01() {
	vector<int> vc = { 1,2,3,4,51 };
	//for (vector<int>::iterator it = vc.begin(); it != vc.end(); it++) {
	for (auto it = vc.begin(); it != vc.end(); it++) {
		cout << *it << " ";
	}
}
auto func1(int v1, int v2) {
	return v1 + v2;
}
void test02() {
	cout << func1(100, 200) << endl;
}