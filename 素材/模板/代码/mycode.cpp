#include "mycode.h"

//练习题
template<class T>
void mathHelper(T num[], int size) {
	T max = num[0], min = num[0], total = 0;
	for (int i = 0; i < size; i++) {
		if (num[i] > max) {
			max = num[i];
		}
		if (num[i] < min) {
			min = num[i];
		}

		total += num[i];
	}
	cout << "Max = " << max << endl;
	cout << "min = " << min << endl;
	if (size == 0) {
		cout << "均值:" << 0 << endl;
	}
	else {
		cout << "均值:" << total / double(size) << endl;
	}
}

void test05() {
	int arr[5] = { 1,2,3,4,9 };
	double darr[5] = {1.1,2.2,3.1,4.3,5.5};
	mathHelper<int>(arr, sizeof(arr) / sizeof(arr[0]));
	cout << endl << " ------------------" << endl;
	mathHelper<double>(darr, sizeof(darr) / sizeof(darr[0]));
}




template<typename T>
class Test {
public:
	Test(){}
	void setData(const T& x) {
		num = x;
	}
	void showData() {
		cout << num << endl;
	}
private:
	T num;
};

//template<typename T>
//void Test<T>::setData(const T& x) {
//	num = x;
//}
//template<class T>
//void Test<T>::showData() {
//	cout << num << endl;
//}

//typedef Test<int> t;
template<class T>
using t = Test<T>;
void test04() {
	//Test<int> t1;
	//t t1;

	t<int> t1;

	t1.setData(999);
	t1.showData();
}










template <class T>
class Pair {
public:
	T values[2];

public:
	Pair(T first, T second) {
		values[0] = first;
		values[1] = second;
	}
};


void test03() {
	Pair<int> myInt(1, 2);
	cout << myInt.values[0] << "  " << myInt.values[1] << endl;

	Pair<double> myDouble(1.111, 2.342);
	cout << myDouble.values[0] << "  " << myDouble.values[1] << endl;
}




template <class T>
void change(T& n1, T& n2) {
	T temp;
	temp = n1;
	n1 = n2;
	n2 = temp;
}

void test02() {
	int v1 = 100, v2 = 200;
	cout << "v1 = " << v2 << "  v2=" << v2 << endl;
	change(v1, v2);
	cout << "v1 = " << v2 << "  v2=" << v2 << endl;

	double v3 = 1.1, v4 = 2.2;
	cout << "v3 = " << v3 << "  v4=" << v4 << endl;
	change(v3, v4);
	cout << "v3 = " << v3 << "  v4=" << v4 << endl;
}









template<typename T,class H>
T add(T& v1, H& v2) {
	return v1 + v2;
}

void test01() {
	int n1 = 100, n2 = 200;
	int n3 = add(n1, n2);
	cout << n3 << endl;

	double d1 = 1.234, d2 = 2.343;
	double d3 = add(d1, d2);
	cout << d3 << endl;

	//double d4 = add(n1, d2);//错误，在模板编译器一般不会进行类型转换
	double d4 = add(n1, d2);
	cout << d4 << endl;
}