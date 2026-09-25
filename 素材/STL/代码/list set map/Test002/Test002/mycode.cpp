#include "mycode.h"
void test19() {
	multimap<int, int> m = { {1,11},{2,22},{3,33},{2,22},{2,23},{2,21},{2,22},{2,22},{2,234} };
	int pos = 0;
	for (auto i = m.begin(); i != m.find(2); i++, pos++);
	cout << pos+1 << endl;
	cout << m.count(2) << endl;

	auto p1 = m.lower_bound(2);
	cout << p1->first << "  " << p1->second << endl;
	auto p2 = m.upper_bound(2);
	cout << p2->first << " " << p2->second << endl;

	auto range = m.equal_range(2);
	for (auto i = range.first; i != range.second; i++) {
		cout << "键：" << i->first << "  值:" << i->second << endl;
	}

}

void test18() {
	multimap<int, int> m = { {1,11},{2,22},{3,33},{4,44},{5,55} };
	if (m.empty()) {
		cout << "m为空" << endl;
	}
	else {
		cout << "m不为空" << endl;
		cout << "m.size():" << m.size() << endl;
	}
	multimap<int, int> m2 = { {11,100},{22,200} };
	cout << "交换前:" << endl;
	printMulmap(m);
	printMulmap(m2);
	cout << "交换后:" << endl;
	printMulmap(m);
	printMulmap(m2);
}


void printMulmap(multimap<int, int>& m) {
	cout << "*****************" << endl;
	for (auto i = m.begin(); i != m.end(); i++) {
		cout << "key:" << i->first << "  value:" << i->second << endl;
	}
}
void test17() {
	multimap<int, int> m;
	m.insert(make_pair(1, 11));
	m.insert(make_pair(2, 22));
	m.insert(make_pair(3, 33));
	m.insert(make_pair(4, 44));
	m.insert(make_pair(5, 55));
	m.insert(make_pair(6, 66));
	m.insert(make_pair(7, 77));
	m.insert(make_pair(8, 88));
	m.insert(make_pair(9, 99));
	printMulmap(m);

	//1.指定值删除
	m.erase(4);
	printMulmap(m);
	//2.位置删除
	m.erase(m.begin());
	printMulmap(m);
	//区间删除
	auto pos = m.find(5);
	m.erase(m.begin(), ++pos);//m.clear()
	printMulmap(m);
}


void test16() {
	//默认构造函数
	multimap<int,int> m1;
	//赋值构造函数
	multimap<int,int> m2(m1);
	//重载 =
	multimap<int,int> m3 = m2;
}


void test15() {

	map<int, int> m = { {1,11},{2,22},{3,33} };
	//map<int, int>::iterator it = m.find(30);
	auto it = m.find(3);
	if (it != m.end()) {
		cout << it->first << "  " << it->second << endl;
	}
	else {
		cout << "未找到" << endl;
	}

	int pos = 0;
	for (auto i = m.begin(); i != m.find(2); i++, pos++);
	cout << pos + 1 << endl;


	int num = m.count(10);
	cout << num << endl;
}

void test14() {

	map<int, int> m1;
	//1.通过pair
	m1.insert(pair<int, int>(1, 11));
	printMap(m1);

	//2.make_pair
	m1.insert(make_pair(2,22));
	printMap(m1);

	//3.map<int,int>::value_type()
	m1.insert(map<int, int>::value_type(3,33));
	printMap(m1);

	//4. []
	m1[1] = 66; //key不存在就创建，存在就是修改value
	printMap(m1);

	//删除
	m1.erase(m1.begin());//通过迭代器位置
	printMap(m1);

	//根据key来删
	m1.erase(2);
	printMap(m1);

	//根据迭代区间
	m1.erase(m1.begin(), m1.end());//类似于m1.clear()
	cout << "************" << endl;
	printMap(m1);


}

void printMap(map<int, int>& m) {
	for (auto i = m.begin(); i != m.end(); i++) {
		cout << "key:" << i->first << "  value:" << i->second << endl;
	}
}
void test13() {
	map<int, int> m1 = { {6,600}, {1,100},{2,200},{3,300} };
	map<int, int> m2 = { {66,666}, {11,111},{22,222},{3,333} };
	printMap(m1);

	if (m1.empty()) {

		cout << "m1为空" << endl;

	}
	else {
		cout << "m1 不为空" << endl;
		cout << "m1.size()：" << m1.size() << endl;
	}

	cout << "交换前:" << endl;
	printMap(m1);
	cout << "----------" << endl;
	printMap(m2);

	m1.swap(m2);
	cout << "交换后:" << endl;
	printMap(m1);
	cout << "----------" << endl;
	printMap(m2);

}

void test12() {
	
	map<int, int> m = {pair<int,int>(1,10),pair<int,int>(2,20)};
	//map<int, int> m = { {1,10},{2,20} };

	//map<int, int> m;
	//m.insert(pair<int, int>(1, 10));
	//m.insert(pair<int, int>(2, 20));

	map<int, int> m2(m);
	auto mt2 = m2.begin();
	cout << mt2->first << "  " << mt2->second << endl;


	map<int, int> m3 = m2;
	auto mt3 = m3.begin();
	cout << mt3->first << "  " << mt3->second << endl;

}


void test11() {
	pair<int, int> p1;
	p1 = make_pair(100, 200);
	cout << p1.first << " " << p1.second << endl;

	p1 = make_pair(1.342, 3.2343);
	cout << p1.first << " " << p1.second << endl;

	pair<double, double> p2;
	p2 = make_pair(1.232, 3.2342);
	cout << p2.first << "  " << p2.second << endl;

	pair<char, int> p3 = make_pair('c', 200);
	cout << p3.first << " " << p3.second << endl;

}

void test10() {

	pair<string, int> p1("诸葛亮", 300);
	cout << "名字叫:" << p1.first << "   年龄:" << p1.second << endl;

	pair<int, int> p2;
	p2.first = 10;
	p2.second = 20;
	cout << p2.first << endl;
	cout << p2.second << endl;

}

void test09() {

	pair<int, int> p1;
	pair<int, char> p2;

	pair<int, int> p3(10, 20);
}



void test08() {
	multiset<int> ms = { 3,1,4,5,4,2,1,3,9,11,4,5 };

	//count统计元素个数
	cout <<"5的个数:" <<  ms.count(5) << endl;

	//cout << *ms.find(50) << endl;

	int pos = 0;
	for (auto i = ms.begin(); i != ms.find(3); i++, pos++);

	cout << pos << endl;

	//lower_bound()  
	auto pos2 = ms.lower_bound(8);
	cout << *pos2 << endl;
	auto pos3 = ms.upper_bound(8);
	cout << *pos3 << endl;
}


void test07() {
	multiset<int> ms = { 2,3,1,5,4,2,1 };
	printMulset(ms);
	printMulset2(ms);

	//size() 元素个数
	cout << "ms.size():" << ms.size() << endl;
	//empty 是否为空
	if (ms.empty()) {
		cout << "ms为空" << endl;
	}
	else {
		cout << "ms 不为空" << endl;
	}
	multiset<int> ms2 = { 11,33,22,55,44 };
	ms.swap(ms2);
	cout << "ms:" << endl;
	printMulset(ms);
	cout << "ms2:" << endl;
	printMulset(ms2);
}




void printMulset(multiset<int>& ms) {
	for (auto i = ms.begin(); i != ms.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
}

void printMulset2(multiset<int>& ms) {
	for (auto i = ms.rbegin(); i != ms.rend(); i++) {
		cout << *i << " ";
	}
	cout << endl;
}

void test06() {

	multiset<int> ms;
	//1.insert操作
	ms.insert(3);
	ms.insert(1);
	ms.insert(4);
	ms.insert(2);
	ms.insert(5);
	ms.insert(3);
	ms.insert(1);
	printMulset(ms);
	multiset<int> ms2 = { 11,-3,-1,44,55 };
	ms.insert(ms2.begin(), ms2.end());

	ms.insert(ms.begin(), 999);

	printMulset(ms);
	//删除
	//ms.erase(ms.begin());
	//printMulset(ms);
	//ms.erase(ms.begin(), ++ms.begin());
	//printMulset(ms);
	//ms.erase(5);
	//printMulset(ms);
	//ms.clear(); // ms.erase(ms.begin(),ms.end())
	//printMulset(ms);
	
}

void test05() {

	//1.默认构造函数
	multiset<int> ms1;
	//2.拷贝构造函数
	multiset<int> ms2(ms1);
	//3.重载=
	multiset<int> ms3 = ms2;

}


void test04() {
	set<int> s = { 3,2,1,5,4 };

	//set<int>::iterator pos = s.find(30);
	auto pos = s.find(3);
	if (pos != s.end()) {
		cout << "找到了" << endl;
	}
	else {
		cout << "未找到" << endl;
	}

	//插入几个相同的元素进去
	s.insert(3);
	s.insert(3);
	int cnt = s.count(3);
	cout << cnt << endl;

}


void test03() {

	set<int> s = { 1,2,3,5,4,1 };
	if (s.empty()) {
		cout << "s.empty():" << s.empty() << endl;
	}
	else {
		cout << "s.empty():" << s.empty() << endl;
		cout << "s.size():" << s.size() << endl;
		printSet(s);
	}
	set<int> s2 = { 11,33,22,55,44 };
	cout << "交换之前:" << endl;
	printSet(s);
	printSet(s2);

	s.swap(s2);
	cout << "交换之后:" << endl;
	printSet(s);
	printSet(s2);


}



void printSet(set<int>& s) {
	for (auto i = s.begin(); i != s.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
}
void test02() {
	set<int> s;
	s.insert(20);
	s.insert(10);
	s.insert(50);
	s.insert(30);
	s.insert(40);
	s.insert(20);
	printSet(s);

	s.erase(s.begin());
	printSet(s);
	s.erase(40);
	printSet(s);
	s.erase(s.begin(), --s.end());
	printSet(s);
	s.clear();
	printSet(s);


}


void test01() {
	set<int> s1 = { 3,1,5,4,2,2,3,1 };
	for (auto i = s1.begin(); i != s1.end(); i++) {
		cout << *i << " ";
	}

	set<int> s2(s1);
	cout << endl;
	for (auto i = s2.begin(); i != s2.end(); i++) {
		cout << *i << " ";
	}

	set<int> s3 = s2;
	cout << endl;
	for (auto i = s3.begin(); i != s3.end(); i++) {
		cout << *i << " ";
	}
}