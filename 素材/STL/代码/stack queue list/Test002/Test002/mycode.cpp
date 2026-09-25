#include "mycode.h"

//Person类
class Person {
public:
	int age;
	string name;
	float height;
public:
	Person(string name, int age, float height) {
		this->name = name;
		this->age = age;
		this->height = height;
	}
};
//自定义比较函数
bool compare(Person& p1, Person& p2) {
	if (p1.age == p2.age) {
		return p1.height > p2.height;
	}
	else {
		return p1.age < p2.age;
	}
}


void test20() {

	list<Person> lst;  //创建链表
	Person p1("唐僧", 500,199);  //创建person数据
	Person p2("孙悟空", 500,182);
	Person p3("猪八戒", 300,180);
	Person p4("沙僧", 500,186);

	//把person数据装入lst
	lst.push_back(p1);
	lst.push_back(p2);
	lst.push_back(p3);
	lst.push_back(p4);

	cout << "未排序状态：" << endl;
	for (auto p = lst.begin(); p != lst.end(); p++) {
		cout << "姓名:" << (*p).name << "  年龄:" << (*p).age << " 身高:" << (*p).height << endl;
	}

	lst.sort(compare);
	cout << "排序后状态：" << endl;
	for (auto p = lst.begin(); p != lst.end(); p++) {
		cout << "姓名:" << (*p).name << "  年龄:" << (*p).age << " 身高:" << (*p).height << endl;
	}

}


//降序排序的辅助函数
int cmp(const int& v1, const int& v2) {
	return v1 > v2;
}

void test19() {

	list<int> lst1 = { 11,2,5,3,1,9 };
	list<int> lst2(lst1);

	for (auto i = lst1.begin(); i != lst1.end(); i++) {
		cout << *i << " ";
	}
	lst1.sort();
	cout << endl<<"lst1 从小到大:";
	for (auto i = lst1.begin(); i != lst1.end(); i++) {
		cout << *i << " ";
	}

	lst1.reverse();
	cout << endl << "lst1.reverse() 从大到小:";
	for (auto i = lst1.begin(); i != lst1.end(); i++) {
		cout << *i << " ";
	}

	lst2.sort(cmp);
	cout << endl << "lst2:";
	for (auto i = lst2.begin(); i != lst2.end(); i++) {
		cout << *i << " ";
	}

}
void test18() {
	list<int> lst = { 1,2,3,4,5 };

	//删除指定位置的元素
	lst.erase(lst.begin());
	//删除某个区域的数据
	list<int>::iterator it = lst.end();
	it--;
	it--;
	lst.erase(lst.begin(), it);

	for (auto i = lst.begin(); i != lst.end(); i++) {
		cout << *i << " ";
	}
}

void test17() {
	list<int> lst = { 1,2,3 };
	//在指定位置插入一个固定元素
	lst.insert(lst.begin(), 100);
	//在指定位置，插入n个相同元素
	lst.insert(lst.begin(), 5, 200);

	list<int> lst2(2, 300);
	lst.insert(lst.begin(), lst2.begin(), lst2.end());//把lst2的所有元素插入到lst的前端

	for (auto i = lst.begin(); i != lst.end(); i++) {
		cout << *i << " ";
	}
}

void test16() {

	list<int> lst = { 1,2,3,4,5 };

	//在1的前面插入一个100
	lst.push_front(100);
	//删除链表头部的一个元素
	lst.pop_front();

	//在5的后面插入一个66
	lst.push_back(66);
	//删除链表尾部的一个元素
	lst.pop_back();



	cout << "lst.size():" << lst.size() << endl;

	if (lst.empty()) {
		cout << "lst为空" << endl;
	}
	else {
		cout << "lst不为空" << endl;
	}

	//不用auto
	for (list<int>::iterator it = lst.begin(); it != lst.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	//使用auto
	for (auto i = lst.begin(); i != lst.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
}

void test15() {

	//默认构造函数
	list<int> lst1;
	//带参数构造函数
	list<int> lst2(10); //链表长度为10个空元素
	
	//拷贝构造函数
	list<int> lst3(lst2);
	//指定长度和默认值
	list<int> lst4(10, 22);
	//迭代器的方式
	list<int> lst5(lst4.begin(), lst4.end());

	//赋值函数
	list<int> lst6 = lst5;
}



class Guest {
public:
	string name;
	bool vip;
public:
	Guest(string name, bool vip) {
		this->name = name;
		this->vip = vip;
	}
};
void test14() {
	Guest g1("小鹏", 0);
	Guest g2("小明", 0);
	Guest g3("小华", 1);
	Guest g4("小花", 1);
	deque<Guest> dq;
	dq.push_front(g3);
	dq.push_front(g4);
	dq.push_back(g2);
	dq.push_back(g1);

	for (Guest g : dq) {
		cout << g.name << " ";
	}
}

void test13() {
	deque<int> d1;
	d1.assign(3, 1);//d1的前三个元素赋值为1
	deque<int> d2;
	d2.assign(3, 2);

	for (auto i = d1.begin(); i != d1.end(); i++) {
		cout << *i << " ";
	}
	cout << endl << "----------------------" << endl;

	for (auto i = d2.begin(); i != d2.end(); i++) {
		cout << *i << " ";
	}

	d1.swap(d2);
	cout << endl << "----------------------" << endl;
	for (auto i = d1.begin(); i != d1.end(); i++) {
		cout << *i << " ";
	}
	cout << endl << "----------------------" << endl;

	for (auto i = d2.begin(); i != d2.end(); i++) {
		cout << *i << " ";
	}
}

void test12() {

	deque<int> d1 = { 1,2,3,4,5 };
	//元素个数
	cout << d1.size() << endl;
	cout << d1.max_size() << endl;

	d1.resize(0);//更改队列的元素个数多少

	cout << d1.size() << endl;


	if (d1.empty()) {
		cout << "没有元素了" << endl;
	}

}

void test11() {

	deque<int> d1 = { 1,2,3,4,5,6 };
	//通过下标访问
	cout << d1[2] << endl;
	for (int i = 0; i < d1.size(); i++) {
		cout << d1[i] << " ";
	}
	cout << endl;

	//通过at函数访问
	try {
		cout << d1.at(40) << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}


	//访问队头元素
	cout << d1.front() << endl;

	//访问队尾元素
	cout << d1.back() << endl;
}

void test10() {

	deque<int> d1;
	for (int i = 0; i < 10; i++) {//循环赋值
		d1.push_back(i);
	}

	//头部出队
	d1.pop_front(); //删除0
	//尾部出队
	d1.pop_back();//删除9

	deque<int>::iterator it = d1.begin();
	d1.erase(it); // 删除1

	d1.erase(d1.begin(), d1.begin() + 2);//删除2 ， 3

	for (auto i = d1.begin(); i != d1.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	d1.clear();
	for (auto i = d1.begin(); i != d1.end(); i++) {
		cout << *i << " ";
	}

}

void test09() {

	deque<int> d1;
	//队头添加元素
	d1.push_front(4);
	//队尾添加元素
	d1.push_back(5);

	deque<int>::iterator it = d1.begin();
	d1.insert(it, 2);//d1begin()的位置插入2

	d1.insert(d1.begin(), 3, 9);//在bein()的位置插入3个9

	deque<int> d2 = { 11,22 };
	d1.insert(d1.begin(), d2.end() - 1, d2.end());//在d1的bein()的位置插入d2的队尾元素

	//迭代输出d1的所有元素
	for (auto i = d1.begin(); i != d1.end(); i++) {
		cout << *i << " ";
	}






}

void test08() {

	deque<int> d1;// 默认构造函数

	deque<int> d2(10);//定义int类型的双端队列，并且初始化大小为10

	deque<int> d3(10, 1);//长度为10，每个元素值为1

	deque<int> d4(d3); //用d3来初始化d4

	deque<int> d5(d3.begin(), d3.begin() + 3);  //使用迭代器初始化

	for (auto i = d5.begin(); i != d5.end(); i++) {
		cout << *i << " ";
	}




}

void test07() {
	int n;//n 需要输入n张牌  
	char card;// card 每一张牌
	queue<char> q; //装牌的队列
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> card;
		q.push(card);
	}

	bool flag = 1;
	while (!q.empty()) {
		if (flag) {
			cout << q.front() << " ";
			q.pop();
		}
		else {
			q.push(q.front());
			q.pop();
		}
		flag = !flag;

	}

}

void test06() {
	queue<int> q;
	cout << "q.empty():" << q.empty() << endl;
	//入队操作
	q.push(11);
	q.push(22);
	q.push(33);
	q.push(44);
	q.push(55);
	cout << "q.empty():" << q.empty() << endl;
	cout << "q.size():" << q.size() << endl;//5

	//返回队头元素
	int n1 = q.front();
	cout << n1 << endl;
	//返回队尾元素
	int n2 = q.back();
	cout << n2 << endl;

	//pop出队队头元素11
	q.pop();
	int n3 = q.front();
	cout << n3 << endl;

	//循环出队
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
}


void test05() {
	//使用默认构造函数
	queue<int> q1;
	//使用拷贝构造函数
	queue<int> q2(q1);
	//使用赋值函数
	queue<int> q3 = q1;
}

void test04() {
	int n,temp;
	stack<char> s;
	cin >> n;

	while (n) {
		temp = n % 16;
		switch (temp) {
		case 0:
			s.push('0');
			break;
		case 1:
			s.push('1');
			break;
		case 2:
			s.push('2');
			break;
		case 3:
			s.push('3');
			break;
		case 4:
			s.push('4');
			break;
		case 5:
			s.push('5');
			break;
		case 6:
			s.push('6');
			break;
		case 7:
			s.push('7');
			break;
		case 8:
			s.push('8');
			break;
		case 9:
			s.push('9');
			break;
		case 10:
			s.push('A');
			break;
		case 11:
			s.push('B');
			break;
		case 12:
			s.push('C');
			break;
		case 13:
			s.push('D');
			break;
		case 14:
			s.push('E');
			break;
		case 15:
			s.push('F');
			break;
		}

		n /= 16;
	}
	while (!s.empty()) {
		cout << s.top();
		s.pop();
	}

}

void test03() {
	int n,temp,temp2; //输入的十进制n
	stack<int> s;  //装二进制01的栈
	cin >> n;

	while (n) {
		temp = n % 2;  //n对2取余数
		s.push(temp);
		n /= 2;
	}
	while (!s.empty()) {
		temp2 = s.top();
		cout << temp2;
		s.pop();
	}
}


void test02() {
	stack<int> s;

	cout << "s.empty():" << s.empty() << endl;

	s.push(11); //向栈顶添加元素11
	s.push(22);
	s.push(33);
	cout << "s.empty():" << s.empty() << endl;
	cout << "s.size():" << s.size() << endl;

	int n = s.top();//取到栈顶元素，但不删除栈顶
	cout << n << endl;
	cout << "s.size():" << s.size() << endl;

	s.pop();           //删除栈顶元素 33
	cout << "s.size():" << s.size() << endl;

	int n2 = s.top();
	cout << "s.size():" << s.size() << endl;

	cout << n2 << endl;

	/*stack<char> s1;
	s1.push('a');
	s1.top();*/
}




void test01() {
	stack<int> s1;  //采用默认构造函数实现
	stack<int> s2(s1);  //拷贝构造函数实现
	stack<int> s3 = s1;  //赋值函数
}



