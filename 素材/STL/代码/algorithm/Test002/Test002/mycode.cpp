
#include "mycode.h"

void test22() {
	queue<int> q; //读入数据，int类型
	int n, m, num = 1; //n n个人, m 到m出圈，num 报数，从1开始

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		q.push(i); //填充数据
	}
	while (!q.empty()) {//队列非空的时候，模拟出队
		if (num == m) {
			cout << q.front() << " "; //输出数到第m的人
			q.pop(); //第m个人出队
			num = 1;//重新报数
		}
		else {
			num++;//往下报数
			q.push(q.front());  //将对首移到队尾
			q.pop();//对首出队
		}
	}

}

void test21() {

	vector<int> v1 = { 1,2,3,4,5 };
	vector<int> v2 = { 2,4,5,6,8 };
	vector<int> v3;

	v3.resize(max(v1.size(), v2.size()));

	cout << "v1 and v2  difference set is:" << endl;
	auto pos1 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	for_each(v3.begin(), pos1, print01);

	cout << endl << "v2 and v1 difference set is:" << endl;
	auto pos2 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin());
	for_each(v3.begin(), pos1, print01);
}

void test20() {

	vector<int> v1 = { 1,2,3,4 };
	vector<int> v2 = { 3,4,5,6 };
	vector<int> v3;
	v3.resize(v1.size() + v2.size());
	auto pos = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for_each(v3.begin(), pos, print01);
	cout << endl;


}

void test19() {

	vector<int> v1 = { 1,3,4,5,6,7,8 };
	vector<int> v2 = { 2,3,5,6,8 };
	vector<int> v3;

	v3.resize(min(v1.size(), v2.size()));

	auto pos = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	//for_each(v3.begin(), pos, print01);
	//for_each(v3.begin(), v3.end(), print01);


}

void test18() {

	vector<int> v = {1,2,3,4,5};
	//v.resize(10);
	fill(v.begin(), v.end(), 100);
	for_each(v.begin(), v.end(), print01);

}


void test17() {

	vector<int> v = { 1,2,3,4,5 };

	int total = accumulate(v.begin(), v.end(), 0);
	cout << total << endl;

}

void test16() {

	vector <int> v1 = { 1,2,3 }, v2 = { 5,6,7 };
	for_each(v1.begin(), v1.end(), print01);
	cout << endl;
	for_each(v2.begin(), v2.end(), print01);

	swap(v1, v2);

	cout << endl;
	for_each(v1.begin(), v1.end(), print01);
	cout << endl;
	for_each(v2.begin(), v2.end(), print01);

}

class Greater20 {
public:
	bool operator()(int v) {
		return v > 20;
	}
};
class Greater130 {
public:
	bool operator()(int v) {
		return v > 2;
	}
};
void test130() {
	vector<int> v1 = { 1,2,3,45,6,7,89 };
	vector <int> v2;
	v2.resize(v1.size());
	copy_if(v1.begin(), v1.end(), v2.begin(), Greater130());

	for_each(v2.begin(), v2.end(), print01);
}

void test15() {
	vector<int> v = { 1,20,31,1,20,41,1,20,51 };
	cout << "before  replace:" << endl;
	for_each(v.begin(), v.end(), print01);
	cout << endl;

	replace_if(v.begin(), v.end(), Greater20(), 9999);

	cout << "after  replace:" << endl;
	for_each(v.begin(), v.end(), print01);
	cout << endl;
}

void test14() {
	vector<int> v = { 1,2,3,1,2,4,1,2,5 };
	cout << "before  replace:" << endl;
	for_each(v.begin(), v.end(), print01);
	cout << endl;

	replace(v.begin(), v.end(), 1, 1111);
	cout << "after  replace:" << endl;
	for_each(v.begin(), v.end(), print01);
	cout << endl;
}


void test13() {

	vector<int> v1 = { 1,2,3,45,6,7,89 };
	vector <int> v2;
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());

	

	for_each(v2.begin(), v2.end(), print01);

}


void test12() {

	vector<int> v = { 1,3,5,8,9,12,16,20 };
	reverse(v.begin(), v.end());
	for_each(v.begin(), v.end(), print01);

}

void test11() {
	vector<int> v1 = { 1,2,5,6 };
	vector<int> v2 = { 3,4,7,9 };
	vector<int> vt;
	vt.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vt.begin());

	for_each(vt.begin(), vt.end(), print01);

}

void test10() {

	vector<int> v = { 1,2,3,4,5,6 };
	srand((unsigned)time(0));
	random_shuffle(v.begin(), v.end());

	for_each(v.begin(), v.end(), print01);
}

template<typename T>
class greater09 {
public:
	bool operator()(T& a, T& b) {
		return a > b;
	}
};

void test09() {

	vector<int> v = { 2,3,1,5,4,6 };
	sort(v.begin(), v.end());
	for_each(v.begin(), v.end(), print01);

	sort(v.begin(), v.end(), greater09<int>());
	cout << endl;
	for_each(v.begin(), v.end(), print01);
}

class Greater10 {
public:
	bool operator()(int v) {
		return v > 10;
	}
};

void test08() {
	vector<int> v = { 2,12,3,3,5,5,5,4,11,1,5,6,6,7,10 };
	int num = count_if(v.begin(), v.end(), Greater10());
	cout << num << endl;
}

void test07() {
	vector<int> v = { 2,2,3,3,5,5,5,4,1,1,5,6,6,7 };
	int num = count(v.begin(), v.end(), 6);
	cout << num << endl;
}

void test06() {
	vector<int> v = { 2,2,3,3,5,5,5,4,1,1,5,6,6,7 };
	
	bool res = binary_search(v.begin(), v.end(), 66);
	if (res) {
		cout << "找到了" << endl;
	}
	else {
		cout << "未找到" << endl;
	}

}

void test05() {
	vector<int> v = { 2,2,3,3,5,5,5,4,1,1,5,6,6,7 };

	vector<int> ::iterator pos = adjacent_find(v.begin(), v.end());
	if (pos == v.end()) {
		cout << "未找到" << endl;
	}
	else {
		cout << "找到了" << *pos << endl;
	}
}

class Five {
public:
	bool operator()(int v) {
		return v == 5;
	}
};

void test04() {
	vector<int> v = { 2,3,5,5,5,4,1,5,6,7 };

	auto pos = find_if(v.begin(), v.end(), Five());
	if (pos == v.end()) {
		cout << "未找到" << endl;
	}
	else {
		cout << "找到了：" << *pos << endl;
	}
}

void test03() {
	vector<int> v = { 2,3,4,1 };
	auto pos = find(v.begin(), v.end(), 11);
	if (pos == v.end()) {
		cout << "未找到" << endl;
	}
	else {
		cout << "找到了 " << *pos << endl;
	}
}

class Transform {
public:
	int operator()(int v) {
		return v+100;
	}
};

void test02() {
	vector<int> v = { 1,2,3,4,5 };
	vector<int> vTarget;
	vTarget.resize(v.size());
	transform(v.begin(), v.end(), vTarget.begin(), Transform());

	for_each(vTarget.begin(), vTarget.end(), print02());
}

void print02::operator()(int val) {
	cout << val << " ";
}

void print01(int val) {
	cout << val << " ";
}

void test01() {

	vector<int> v = { 2,1,3,4,5 };
	
	for_each(v.begin(), v.end(), print01);
	cout << endl << "下面是仿函数:" << endl;
	for_each(v.begin(), v.end(), print02());
	

}