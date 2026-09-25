#include "mycode.h"

template<typename T>
concept CastableToString = requires(T a) {
	{a} -> convertible_to<T>;
};

template<typename T>
class ClassTest2 {
public:
	string to_string() const requires CastableToString<T>{
		return "ClassTest2<>";
	}
};

void test09() {
	ClassTest2<string> ct1;
	cout << ct1.to_string() << endl;
}



template<class T>
class ClassTest1 {
public:
	template<typename ToString = T>
	typename enable_if_t<is_convertible<ToString,string>::value,string>
		to_string() const {
		return "ClassTest1<>";
	}
};

void test08() {
	ClassTest1<size_t> ct1;
	//cout << ct1.to_string() << endl;

	ClassTest1<string> ct2;
	cout << ct2.to_string() << endl;

}

void test07() {


	cout << "numbers::e = " << numbers::e << "  " << numbers::e_v<double> << endl;
	cout << "numbers::log10e = " << numbers::log10e << "  " << numbers::log10e_v<double> << endl;
	

}

void getAnswertest(promise<int> intPromise) {
	this_thread::sleep_for(2s);
	intPromise.set_value(999);

}

void test06() {
	promise<int> answerPromise;
	auto fut = answerPromise.get_future();
	jthread productThread(getAnswertest, move(answerPromise));
	future_status status{};
	do {
		status = fut.wait_for(0.5s);
		std::cout << "结果未准备好！" << endl;
	} while (status != future_status::ready);
	std::cout << format("answer is {}\n",fut.get()) << endl;
}

void product(promise<int>&& intPromise, int v1, int v2) {
	intPromise.set_value(v1 * v2);
}

void test05() {
	int num1 = 200, num2 = 300;
	promise<int> productPromise;

	future<int> productResult = productPromise.get_future();
	jthread productThread(product, move(productPromise), num1, num2);

	cout << format("product is {}\n",productResult.get()) << endl;

}

void test04() {

	string s1 = "hello C++";
	cout << format("the string '{}' has {} characters",s1,s1.size()) << endl;
	cout << format("the string '{0}' has {1} characters", s1, s1.size()) << endl;
	cout << format("the string '{1}' has {0} characters", s1.size(),s1) << endl;
}

void test03() {
	//创建年
	auto y1 = year(2023);
	cout << y1 << endl;
	auto y2 = 2022y;
	cout << y2 << endl;

	//创建月
	auto m1 = month{ 12 };
	cout << m1 << endl;
	auto m2 = July;
	cout << m2 << endl;

	//创建日
	auto d1 = day{ 5 };
	auto d2 = 2d;
	cout << d1 << endl;
	cout << d2 << endl;


	year_month_day date1{ 2022y,July,12d };
	cout << date1 << endl;

	auto date2 = 2022y / July / 12d;
	cout << date2 << endl;

	year_month_day date3{ Monday[3] / July / 2022 };
	cout << date3 << endl;

}

void test02() {

	auto ints = views::iota(0, 10);
	auto even = [](int i) {return 0 == i % 2; };
	auto square = [](int i) {return i * i; };

	for (int i : ints | views::filter(even) | views::transform(square) ){
		cout << i << " ";
	}
}



void test01() {

	int num1 = 300, num2 = 200;
	if ((num1 <=> num2) < 0) {
		cout << "num1 < num2" << endl;
	}
	else if ((num1 <=> num2) > 0) {
		cout << "num1 > num2" << endl;
	}
	else {
		cout << "num1 = num2" << endl;
	}

}