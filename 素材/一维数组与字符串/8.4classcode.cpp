
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {

	//初始化
	/*string s1("hello world!");
	cout << s1 << endl;
	string s2(10, 's');
	cout << s2 << endl;

	string s3("dajl");
	string s4(s3);
	cout << s3 << " " << s4 << endl;

	string s5;
	s5 = "djskajk";
	cout << s5 << endl;*/



	//长度
	/*string s1 = "abcde";
	int len1 = s1.size();
	int len2 = s1.length();
	cout << len1 << " " << len2 << endl;*/



	//复制
	//string s1 = "hellow";
	//string s2 = s1;
	////s2 = s1;

	//cout << s1 << " " << s2 << endl;


	//拼接
	//string s1 = "abc";
	//string s2 = "edfd", s3;

	//s3 = s1 + s2;  //把s1和s2拼接之后，赋值给s3
	//cout << s3 << endl;
	//s1 +=  s2;
	//cout << s1 << endl;


	//string s1 = "abc";
	//string s2 = "123";
	//s1.append(s2); //在s1的后面追加字符串
	//cout << s1 << endl;
	//s1.append("jskaj");
	//cout << s1 << endl;

	//string s1 = "abc";
	//string s2 = "123";
	//s2.push_back('h');  //添加字符到字符串后面
	//cout << s2 << endl;

	
	//string s1 = "hello";
	//string s2 = "hello";
	/*if (s1 == s2)
	{
		cout << "s1 等于s2" << endl;
	}
	else if (s1 > s2) {
		cout << "s1 大于 s2" << endl;
	}
	else {
		cout << "s1 小于 s2" << endl;
	}*/

	/*int n1 = s1.compare(s2);
	cout << n1 << endl;
	int n2 = s1.compare(1, 3, s2);
	cout << n2 << endl;
	int n3 = s1.compare(1, 3, s2, 1, 3);
	cout << n3 << endl;*/


	//截取子串
	/*string s1 = "abcedfghijk";
	string s2 = s1.substr(3, 5);
	cout << s2 << endl;*/


	//字符访问
	//string s1 = "abcdef";
	//cout << s1[0] << " "<< s1[2] << endl;
	//cout << s1.at(0) << " " << s1.at(2) << endl;


	//查找
	//string s1 = "ab12c1523 kdjf ";
	/*int index = s1.find("123");
	cout << index << endl;*/

	/*int n = s1.find("123", 0, 2);
	cout << n << endl;*/

	/*int n2 = s1.find('z', 0);
	cout << n2 << endl;*/

	/*string s1 = "abkd12c kdjf ";

	int index = s1.rfind("kd");

	cout << index << endl;*/


	/*string s1 = "abkd12c kdjf ";
	cout << s1.find_first_of("jkn") << endl;
	cout << s1.find_first_not_of("jkn") << endl;
	cout << s1.find_last_of("jkn") << endl;
	cout << s1.find_last_not_of("jkn") << endl;*/



	//插入
	//string s1 = "abcde";
	/*cout << s1.insert(1, "123") << endl;;
	cout << s1 << endl;*/

	/*s1.insert(1, "123456", 2, 3);
	cout << s1 << endl;*/
	
	/*s1.insert(1, "123456", 2);
	cout << s1 << endl;*/



	/*s1.insert(2, 10,'z');
	cout << s1 << endl;*/

	/*s1.insert(s1.begin()+1,3,'H');
	cout << s1 << endl;*/

	/*s1.insert(s1.begin() + 3, 'N');
	cout << s1 << endl;*/


	//删除
	//string s1 = "abcdef";
	//s1.erase(1);
	//cout << s1 << endl;

	/*s1.erase(s1.begin() + 2);
	
	cout << s1 << endl;*/

	/*s1.erase(s1.begin(), s1.begin() + 3);
	cout << s1 << endl;*/

	//判断是否为空
	/*string s1 = "sdjfk";

	cout << s1.empty() << endl;*/


	//交换
	/*string s1 = "abc";
	string s2 = "123";
	s1.swap(s2);
	cout << s1 << endl;
	cout << s2 << endl;*/


	//输入输出
	//string s1;
	////cin >> s1;
	//
	//getline(cin, s1);  //需要头文件string
	//cout << s1;


	//替换
	//string s1 = "abc123edf";

	/*s1.replace(3, 3, "aaa");
	cout << s1 << endl;*/


	/*s1.replace(3, 3, "qwer", 2);

	cout << s1 << endl;*/

	//s1.replace(3, 3, "456", 1, 2);
	//cout << s1 << endl;

	/*s1.replace(1, 2, 10, 'H');
	cout << s1 << endl;*/




	//字符串反转
	/*string s1 = "abc";

	reverse(s1.begin(), s1.end());
	cout << s1 << endl;*/


	////课堂练习1
	//string s1, s2;
	//cin >> s1;

	//int len = s1.size();
	//for (int i = 0; i < len; i++) {
	//	if (s1[i] == 'z') {
	//		s2 += 'a';
	//	}
	//	else {
	//		s2 += s1[i] + 1;
	//	}
	//}

	//cout << s2 << endl;



	string s1;
	int c[26] = { 0 };
	cin >> s1;
	int len = s1.size();
	for (int i = 0; i < len; i++) {
		c[s1[i] - 'a'] ++;
	}
	for (int i = 0; i < len; i++) {
		if (c[s1[i] - 'a'] == 1) {
			cout << i << endl;
			return 0;
		}
	}

	cout << -1 << endl;
	


	return 0;
}

