
#include "mycode.h"

void test06() {

	int num = 100;
	string str;
	stringstream ss;

	ss << num;
	ss >> str;
	cout << str << endl;
	
	ss.clear();  //多次使用stringstream对象的时候，一定要先清空一下

	char c[10] = "abc";
	ss << c;
	ss >> str;
	cout << str << endl;

	string s2 = "200";

	ss.clear();

	ss << s2;
	ss >> num;
	cout << num << endl;

}

void test05() {
	//istringstream >>   ostringstream <<    stringstream  >>  << 

	stringstream  ss("china");
	stringstream ss2;
	ss2.str("beijing");

	cout << ss.str() << endl;
}

void test04() {

	ostringstream ostr("hello");
	ostringstream ostr2;
	ostr2.str("world");

	cout << ostr.str() << endl;
	cout << ostr2.str() << endl;

	ostr.put('a');
	cout << ostr.str() << endl;

	ostr2 << "abc";
	cout << ostr2.str() << endl;

}



void test03() {

	istringstream istr("100 3.15");
	int num;
	double num2;

	/*
	istr >> num;
	istr >> num2;
	cout << num << endl;
	cout << num2 << endl;
	*/

	istr >> num2 >> num;
	cout << num << "  " << num2 << endl;
}

void test02() {

	istringstream istr;

	istr.str("i love china");
	string s2;
	while (istr >> s2) {
		cout << s2 << endl;
	}

}

void test01() {

	string s1 = "i love china";

	istringstream istr(s1);

	string s2;
	while (istr >> s2) {
		cout << s2 << endl;
	}

}