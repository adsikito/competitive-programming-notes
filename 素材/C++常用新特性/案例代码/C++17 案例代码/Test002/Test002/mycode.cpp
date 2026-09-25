#include "mycode.h"

void test21() {

	namespace fs = std::filesystem;
	auto testdir = fs::path("./testdir");

	if (!fs::exists(testdir)) {
		cout << "file or directory is not exists" << endl;
	}

	fs::directory_options opt(fs::directory_options::none);
	fs::directory_entry dir(testdir);

	//遍历当前目录
	cout << "show :\t" << dir.path().filename() << endl;
	for (fs::directory_entry const& entry : fs::directory_iterator(testdir, opt)) {
		if (entry.is_regular_file()) {
			cout << entry.path().filename() << " \t size:" << entry.file_size() << endl;
		}
		else if (entry.is_directory()) {
			cout << entry.path().filename() << "\t dir" << endl;
		}
	}
	cout << endl;

	//递归遍历所有文件
	cout << "show all:\t" << dir.path().filename() << endl;
	for (fs::directory_entry const& entry : fs::recursive_directory_iterator(testdir, opt)) {
		if (entry.is_regular_file()) {
			cout << entry.path().filename() << "\t size:" << entry.file_size() << "\t parent:" << entry.path().parent_path() << endl;
		}
		else if (entry.is_directory()) {
			cout << entry.path().filename() << "\t dir" << endl;
		}
	}
}

void test20() {
	string str = "C++ test";
	cout << is_const<decltype(str)>::value << endl;

	const string str_const = as_const(str);
	cout << is_const<decltype(str_const)>::value << endl;

}

void func123(string_view str) {
	cout << str << endl;
}

void test19() {

	const char* charStr = "hello C++";
	string str{ charStr };
	string_view str_v(charStr, (strlen(charStr)));

	cout << "str:" << str << endl;
	cout << "str_v:" << str_v << endl;
	func123(str_v);

}

class ClassTest4 {
public:
	string name;
	size_t age;
	ClassTest4(string name, size_t age) :name(name), age(age) {
		cout << "name=" << name << " age = " << age << endl;
	}
	
};

void test18() {

	auto param = make_tuple("xiaoming", 20);
	make_from_tuple<ClassTest4>(move(param));



}

int add(int a, int b) {
	return a + b;
}

void test17() {
	cout << apply(add, pair(100, 200)) << endl;

	auto add_lam = [](auto a, auto b, auto c) {return a + b + c; };
	cout << apply(add_lam, tuple(1, 2, 3)) << endl;
}

void test16() {
	//将bool值用 true 和false
	cout << boolalpha;

	//定义一个空的any
	any a1;
	cout << a1.has_value() << endl; //有值返回true，无值返回false
	cout << a1.type().name() << endl; //空返回void，其他的返回对象的数据类型


	//几种创建any的方式
	any a2 = 100;
	cout << a2.has_value() << endl;
	cout << a2.type().name() << endl;

	auto a3 = make_any<float>(3.2f);
	cout << a3.has_value() << endl;
	cout << a3.type().name() << endl;


	any a4(10.0);
	cout << a4.has_value() << endl;
	cout << a4.type().name() << endl;

	a4 = "hello";
	cout << a4.has_value() << endl;
	cout << a4.type().name() << endl;

	a4.reset(); //清空

	auto a5 = a4.emplace<int>(200);
	cout << a5 << endl;


	try {
		auto a6 = any_cast<int> (a5);
		cout << a6 << endl;
	}
	catch (const bad_any_cast& e) {
		cout << e.what() << endl;
	}


}

void test15() {

	optional<int> op1;
	optional<int> op2 = nullopt;
	optional<int> op3 = 100;
	optional<int> op4 = op3;
	//判断是否有值
	if (op1) {
		cout << "op1 has value" << endl;
	}

	if (op3) {
		cout << "op3 has value" << endl;
	}
	//也可以通过has_value() 来判断是否有值
	if (op3.has_value()) {
		cout << 111 << endl;
	}


	//取值1
	cout << *op3 << endl;

	//取值2
	cout << op3.value() << endl;

	//字符串取值
	optional<string> op5 = "hello";
	cout << op5->c_str() << endl;
	cout << op5.value() << endl;
	op5.reset();
	cout << op5.value().c_str() << endl;
}

void test14() {

	variant<int, double, string> d; // int 0   double 1 string 2
	d = 100;
	cout << d.index() << endl;
	
	d = 3.1415;
	cout << d.index() << endl;

	d = "hello";
	cout << d.index() << endl;


	cout << holds_alternative<int>(d) << endl;
	cout << holds_alternative<double>(d) << endl;
	cout << holds_alternative<string>(d) << endl;
}

void test13() {
	//整数字符串转整数
	string s1 = "123456789";
	int val = 0;
	auto res = from_chars(s1.data(), s1.data() + 4, val);
	if (res.ec == errc()) {
		cout << "val:" << val << endl;
		cout << "distance:" << res.ptr - s1.data() << endl;
	}
	else if (res.ec == errc::invalid_argument) {
		cout << "invalid" << endl;
	}

	//小数字符串转小数
	s1 = "12.34";
	double val2 = 0;
	auto format = chars_format::general;
	res = from_chars(s1.data(), s1.data() + s1.size(), val2, format);
	cout << "val2:" << val2 << endl;

	//把整数字符串
	s1 = "xxxxxxxx";
	int val3 = 1234;
	auto res2 = to_chars(s1.data(), s1.data() + s1.size(), val3);
	cout << "str:" << s1 << endl;
	cout << "filled:" << res2.ptr - s1.data() << endl;

}

[[maybe_unused]] void func13() {
	cout << "test" << endl;
}

void test12() {
	[[maybe_unused]] int num = 100;


}

_NODISCARD auto fun12(int a,int b) {
	return a + b;
}

void test11() {
	
	int abc = fun12(1,2);

}
void test10() {
	int i = 1;
	int result;
	switch (i)
	{
	case 0:
		result = 1;

	case 1:
		result = 2;
		__fallthrough;
	default:
		break;
	}

}

void test09() {

#if __has_include("iostream")
	cout << "iosteam exist" << endl;
#endif // __has_include("iostream")


}

class ClassTest3 {
public:
	int num;
	void func2() {
		auto lamfun = [*this]() {cout << num << endl; };
		lamfun();
	}
};

void test08() {
	ClassTest3 ct1;
	ct1.num = 999;
	ct1.func2();

}

void test07() {
	//C++ 11
	unordered_map<string, int> stu1{ {"zhangsan",11},{"wangwu",12} };
	auto iter = stu1.find("wangwu");
	if (iter != stu1.end()) {
		cout << iter->second << endl;
	}

	//C++ 17
	if (auto iter = stu1.find("wangwu"); iter != stu1.end()) {
		cout << iter->second << endl;
	}
	

}

void test06() {
	auto stu2 = make_tuple(string{"shangsan"},20,string{"man"});
	auto [name, age, gender] = stu2;
	cout << name << "  " << age << "  " << gender << endl;
}

void test05() {

	auto stu1 = make_tuple(string{"zhangsan"},19,string{"man"});
	string name;
	size_t age;
	string gender;

	tie(name, age, gender) = stu1;
	cout << name << "  " << age << "  " << gender << endl;

}


class ClassTest2 {
	inline static int value2 = 200;
};

template<bool ok> 
constexpr void func2() {
	//在编译期进行判断，if和else语句不生成代码
	if constexpr (ok == true) {
		//当ok = true,下面的else不生成汇编代码
		cout << "ok" << endl;
	}
	else {
		//ok = false时，上面的if不生成汇编代码
		cout << "not ok" << endl;
	}
}

void test04() {
	func2<false>();
	func2<true>();
}

template<auto T>
void func1() {
	cout << T << endl;
}
void test03() {
	func1<100>();
	//func1<int>();

}

template<class T>
class ClassTest {
public:
	ClassTest(T, T) {}

};

void test02() {

	auto ct1 = new ClassTest(100, 200);
}


template<class... args>
bool all(args... ar) {
	return (...&&ar);
}

void test01() {

	bool b = all(true, true, true, false);
	cout << b << endl;

}