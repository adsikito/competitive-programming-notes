#include "mycode.h"

void test11() {

	ifstream ifile;
	ifile.open("file.txt", ios::in | ios::binary);
	long start, end;
	start = ifile.tellg();
	ifile.seekg(0, ios::end);
	end = ifile.tellg();

	ifile.close();
	cout << end - start << "bytes" << endl;

}

void test10() {

	fstream iof;
	iof.open("file.txt", ios::out | ios::in | ios::trunc);
	iof << "测试fstream " << endl;
	iof << "123123123" << endl;

	cout << "写入完毕" << endl;
	iof.close();
	iof.open("file.txt", ios::in);
	string str;
	while (getline(iof, str)) {
		cout << str << endl;
	}

	cout << "读取完毕" << endl;
	iof.close();

}

class Student {
public:
	Student() {

	}
	/*Student(string name, int age) {
		this->age = age;
		this->name = name;
	}*/

	Student(string name, int age) :name(name), age(age) {}
	void printInfo() {
		cout << this->name << "  " << this->age << endl;
	}
protected:
	string name;
	int age;
};

void test09() {

	ifstream bif;
	bif.open("student.txt", ios::in | ios::binary);
	Student s;
	bif.read((char*)&s, sizeof(Student));
	bif.close();

	s.printInfo();
	//cout << s.name << "  " << s.age << endl;
}

void test08() {

	ofstream of;
	Student s1("王五", 22);
	of.open("student.txt", ios::out | ios::binary);
	of.write((const char *)&s1, sizeof(Student));
	of.close();

}

void test07() {
	//2.创建流对象
	ifstream infile;
	//3.打开文件
	infile.open("file.txt", ios::in);

	//判断文件是否打开
	if (!infile.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	//读取数据
	//4char []  + getline()
	char buf[1024];
	while (infile.getline(buf,sizeof(buf)))
	{
		cout << buf << endl;
	}

	infile.close();

}

void test06() {
	//2.创建流对象
	ifstream infile;
	//3.打开文件
	infile.open("file.txt", ios::in);

	//判断文件是否打开
	if (!infile.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	//读取数据
	//3 char []   >>
	char buf[1024] = { 0 };
	while (infile >> buf) {
		cout << buf << endl;
	}

	infile.close();

}


void test05() {
	//2.创建流对象
	ifstream infile;
	//3.打开文件
	infile.open("file.txt", ios::in);

	//判断文件是否打开
	if (!infile.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	//读取数据
	//2 string
	string str;
	while (getline(infile, str)) {
		cout << str << endl;
	}

	infile.close();

}

void test04() {
	//2.创建流对象
	ifstream infile;
	//3.打开文件
	infile.open("file.txt", ios::in);
	
	//判断文件是否打开
	if (!infile.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	//读取数据
	//1.效率较低，不建议使用
	char c;
	while ((c = infile.get()) != EOF) {
		cout << c;
	}

	infile.close();

}

void test03() {

	//char cf[1024];//保存读取内容的
	//string cf;

	char  cf;

	//2.创建流对象
	ifstream infile;
	//3.打开文件
	//infile.open("file.txt", ios::in);
	infile.open("file.txt");

	//4.读取文件
	while (!infile.eof()) {
		infile.get(cf);
		cout << cf;
	}

	//5.关闭文件
	infile.close();

}

void test02() {

	//char cf[1024];//保存读取内容的
	string cf;

	//2.创建流对象
	ifstream infile;
	//3.打开文件
	//infile.open("file.txt", ios::in);
	infile.open("file.txt");

	//4.读取文件
	infile >> cf;

	cout << cf << endl;
	
	//5.关闭文件
	infile.close();

}


void test01() {

	//2.创建流对象
	ofstream outf;
	//3.open方法打开文件
	//outf.open("file.txt");  //
	//outf.open("file.txt", ios::out);
	outf.open("file.txt", ios::app);

	//4.写入内容
	outf << "    山村咏怀" << endl;
	outf << "          邵雍" << endl;
	outf << "一去二三里，烟村四五家。" << endl;
	outf << "亭台六七座，八九十枝花。" << endl;

	//5.关闭文件
	outf.close();
}
