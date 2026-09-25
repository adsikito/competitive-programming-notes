#include "mycode.h"

void test21() {
	int n;
	vector<int> v;
	cin >> n;
	srand((unsigned)time(0));
	for (int i = 1; i <= n; i++) {
		v.push_back(rand() % 100 + 1);
	}
	int max = v[0], min = v.front();
	for (int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		if (max < v[i]) {
			max = v[i];
		}
		if (min > v[i]) {
			min = v[i];
		}
	}
	cout << "max = " << max << "   min = " << min << endl;
}


void test20() {
	//vector<int> v;
	//v.assign(10, 22);  //把v里面前10元素设置成22

	//for (auto i = v.begin(); i != v.end(); i++) {
	//	cout << *i << " ";
	//}

	vector<int> v1 = { 1,2,3,4 };
	vector<int> v2 = { 100,200,300 };
	//v2.assign(v1.begin(), v1.end());  //把v1的元素替换掉v2元素

	v1.swap(v2);  //v1和v2之进行交换

	for (auto i = v2.begin(); i != v2.end(); i++) {
			cout << *i << " ";
	}

	cout << endl;
	for (auto i = v1.begin(); i != v1.end(); i++) {
		cout << *i << " ";
	}


}

void test19() {
	vector<int> v = { 1,2,3,4,5,6 };

	cout << v.size() << endl;
	cout << v.capacity() << endl;
	cout << v.max_size() << endl;
}

void test18() {
	vector<int> v = { 1,2,3,4,5,6 };
	cout << v.empty() << endl;
	v.erase(v.begin() + 1);//删除2
	v.erase(v.begin() + 2, v.begin() + 4); //删除4，5
	v.pop_back(); //删除最后一个6
	//v.clear();  //删除所有元素
	cout << v.empty() << endl;
	for (auto i = v.begin(); i != v.end(); i++) {
		cout << *i << " ";
	}
}

void test17() {
	vector<int> v = { 1,2 };
	vector<int> v2 = { 111,222 };
	v.push_back(3); //2的后面添加3
	v.insert(v.begin(), 66);//在1的前面插入66
	v.insert(v.begin() + 1, 10, 99);//1和66之间插入10个99
	v.insert(v.begin(), v2.begin(), v2.end());//把v2的所有元素插入v的前面

	for (auto i = v.begin(); i != v.end(); i++) {
		cout << *i << " ";
	}

}

void test16() {

	vector <int> v = { 1,2,3,4,5,6 };
	cout << v.at(3) << endl; //取下标为3的元素 4
	cout << v.front() << endl;//输出首元素
	cout << v.back() << endl;//输出尾元素

	for (auto i = v.begin(); i != v.end(); i++) {//循环迭代打印所有元素
		cout << *i << " ";
	}
	cout << endl;

	for (auto i = v.rbegin(); i != v.rend(); i++) {
		//反向迭代打印所有元素
		cout << *i << " ";
	}

}

void test15() {
	vector<int> v1(10);  //定义一个含有10个变量的整型向量，默认值是0
	cout << v1[0] << endl;
	vector<int> v2(10, 6); //定义一个含有10个变量的整型向量，默认值是6
	cout << v2[0] << endl;
	vector<int> v3(v2);  //把v2赋值给v3
	cout << v3[1] << endl;
	vector<int> v4(v2.begin(), v2.begin() + 1); //把v2的[begin() ,begin() + 1)
	cout << v4.size() << endl;
}

void test14() {
	vector<int> v1 = { 1,2,3,4 };
	vector<char> v2 = { 'h','e','l','l','o' };
	vector<string> v3 = { "hello","abc","world" };
	cout << v1[0] << endl;
}

void test13() {
	string s;
	getline(cin, s);
	for (auto c : s) {
		if (!ispunct(c)) {
			cout << c;
		}
	}
}

void test12() {
	string s = "i very love china";
	const char* cp1 = "truly";
	const char* cp2 = "truly!!!!!";
	string str1 = "really";
	string str2 = "really";

	s.replace(2, 4, cp1);
	cout << s << endl;
	s.replace(2, 5, cp2, 5);
	cout << s << endl;
	s.replace(2, 5, str1);
	cout << s << endl;
	s.replace(2, 6, str2, 0, 6);
	cout << s << endl;
	s.replace(2, 6, 6, '*');
	cout << s << endl;
}

void test11() {
	string s1 = "C++";
	s1.append(" program");
	cout << s1 << endl;
}

void test10() {
	string s1 = "value";
	string s2 = "value";
	string s3 = "value";
	string s4 = "value";
	s1.erase();
	cout << s1 << endl;
	s2.erase(1, 2);
	cout << s2 << endl;
	s3.erase(s3.begin() + 1);
	cout << s3 << endl;
	s4.erase(s4.begin(), s4.begin() + 2);
	cout << s4 << endl;

}


void test09() {
	string s1 = "value";
	s1.insert(s1.begin(), 's');
	cout << s1 << endl;
	s1.insert(s1.begin(), 3, 'a');
	cout << s1 << endl;
	s1.insert(s1.begin(), s1.begin(), ++s1.begin());
	cout << s1 << endl;
	s1.insert(s1.end(), { 'e','f' });
	cout << s1 << endl;
}

void test08() {
	string s = "value";
	string s1 = s.substr();
	cout << s1 << endl;
	string s2 = s.substr(3);
	cout << s2 << endl;
	string s3 = s.substr(5);
	cout << s3 << endl;
	//string s4 = s.substr(10);
	//cout << s4 << endl;
	string s5 = s.substr(2, 3);
	cout << s5 << endl;
	//string s6 = s.substr(6, 2);
	//cout << s6 << endl;
	string s7 = s.substr(3, 10);
	cout << s7 << endl;
	string s8 = s.substr(5, 10);
	cout << s8 << endl;
}

void test07() {
	string s1 = "hello";
	string s2(s1,1);//ello
	cout << s2 << endl;
	//string s3(s1, 8);
	//cout << s3 << endl;
	string s4(s1, 5);//s4 0
	cout << s4 << endl;
	string s5(s1, 0, 3);//hel
	cout << s5 << endl;
	string s6(s1, 2, 10);
	cout << s6 << endl;
	string s7(s1, 5, 3);
	cout << s7 << endl;
	//string s8(s1, 6, 2);
	//cout << s8 << endl;
}

void test06() {
	string s1 = "abcdefghijk";
	//C++ 11 新特性
	for (auto c : s1) {
		cout << c << " ";
	}
	cout << endl;
	cout << s1[0] << endl;
	for (int i = 0; i < s1.size(); i++) {
		cout << s1[i] << " ";
	}
	cout << endl;
	//使用迭代器
	for (auto i = s1.begin(); i != s1.end(); i++) {
		cout << *i << " ";
	}
}

void test05() {//字符串链接
	string s1 = "23432", s2 = "abdjf", s3;
	s3 = s1 + s2;
	cout << s3 << endl;

	//string s4 = "xiaoming" + "china";
	//cout << s4 << endl;
}

void test04() {
	string s1 = "abc", s2 = "edf";
	if (s1 < s2) { // >  <=  >=   ==   != 
		cout << "s1 < s2" << endl;
	}
}

void test03() {
	string s1;
	getline(cin, s1); //可以接收带空格的字符串
	cout << s1 << endl;
}

void test02() {
	string s1;
	cin >> s1;  //遇到空格就结束
	cout << s1 << endl;
}

void test01() {
	string s1 = "abc";
	cout << s1 << endl;
	string s2(s1);
	cout << s2 << endl;
	string s3 = s1;
	cout << s3 << endl;
	string s4 = "hello";
	cout << s4 << endl;
	string s5("hello");
	cout << s5 << endl;
	string s6(11, 'a');
	cout << s6 << endl;
	string s7 = string("wolrd");
	cout << s7 << endl;
	string s8(string("kjlj"));
	cout << s8 << endl;
}