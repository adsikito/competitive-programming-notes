
#include <iostream>

using namespace std;

void func1(int v1) {
	v1++;
}
void func2(int* v1) {
	(*v1)++;
}

void func3(int& v1) {
	v1++;
}

void change(int* p1, int* p2) {
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}


int* test1(int* p) {
	
	return p;
}

int* test2() {
	int v1 = 1;
	cout << &v1 << endl;
	return &v1;
}


void checkMax(int* p1, int* p2, int *pMax) {
	if (*p1 > *p2) {
		*pMax = *p1;
	}
	else {
		*pMax = *p2;
	}
}

int main() {





	////定义数组
	//int arr[5] = { 1,2,3,4,5 };
	//for (int i = 0; i < 5; i++) {
	//	cout << "a[" << i << "]" << arr[i] << " ";
	//}
	//cout << endl;
	////通过指针的方式来访问元素
	//for (int i = 0; i < 5; i++) {
	//	cout << "a[" << i << "]" << *(arr + i) << " ";
	//	//cout << "a[" << i << "]" << *(arr ++) << " ";  //错误  arr常量，不能更改
	//}

	/*int arr[5] = { 1,2,3,4,5 };

	cout << arr << endl;
	cout << &arr[0] << endl;
	cout << &arr[1] << endl;
	cout << &arr[2] << endl;

	cout << arr << endl;
	cout << arr + 0 << endl;
	cout << arr + 1 << endl;
	cout << arr + 2 << endl;*/



	//int arr[5] = { 1,2,3,4,5 };

	////定义整型指针，指向数组arr
	//int* p = arr;
	//for (int i = 0; i < 5; i++) {
	//	cout << *p++ << endl;
	//}


	////定义普通变量num
	//int num = 100;
	////定义一级指针指向num
	//int* p1 = &num;
	////int* p2 = &p1;//如果一级指针变量的内存地址需要保存，是需要定义一个二级指针来保存的
	//int** p2 = &p1;


	//cout << "num=" << num << endl;
	//cout << "*p1=" << *p1 << endl;
	//cout << "**p2=" << **p2 << endl;

	//num = 111;
	//cout << "num=" << num << endl;
	//cout << "*p1=" << *p1 << endl;
	//cout << "**p2=" << **p2 << endl;

	//*p1 = 1212;
	//cout << "num=" << num << endl;
	//cout << "*p1=" << *p1 << endl;
	//cout << "**p2=" << **p2 << endl;

	//**p2 = 333;
	//cout << "num=" << num << endl;
	//cout << "*p1=" << *p1 << endl;
	//cout << "**p2=" << **p2 << endl;




	//定义一个普通变量，并且把它作为func1函数参数
	//int num = 100;
	///*
	//func1(num);
	//cout << num << endl;*/

	//func2(&num); //指针作为函数参数的时候，实参的时候不能直接写变量,要通过取地址符取地址
	//cout << num << endl;

	////参数是引用型
	//func3(num);
	//cout << num << endl;


	//通过指针作为参数来改变两个变量的值
	/*int num1 = 100, num2 = 200;
	cout << "num1 = " << num1 << "    num2 = " << num2 << endl;
	change(&num1, &num2);
	cout << "num1 = " << num1 << "    num2 = " << num2 << endl;*/


	/*int num = 100;
	int* p1 = test1(&num);
	cout << &num << endl;
	cout << p1 << endl;*/

	/*int* p2 = test2();
	cout << p2 << endl;*/




    //const char* pc1 = "abc";
	/*const char* pc1;
	pc1 = "abc";
	cout << pc1 << endl;
	cout << *pc1 << endl;
	*/


	//指针指向字符数组
	//char arr_str[100] = "hello world";
	//int len = strlen(arr_str);
	///*for (int i = 0; i < len; i++) {
	//	cout << *(arr_str + i);
	//}*/

	//char* pc = arr_str;
	//for (int i = 0; i < len; i++) {
	//	cout << *pc++;
	//}


	/*int* p = NULL;
	int* p2 = nullptr;*/


	/*int num = 100;
	
	void * p = &num;
	cout << p << endl;
	cout << *(int *)p << endl;*/

	//int* p;

	//int num1 = 100,num2 = 200;

	//int* const p = &num1;
	////p = &num2;
	//*p = 300;

	//int const* p2 = &num1;
	//p2 = &num2;
	////*p2 = 400;

	//int const* const p3 = &num1;
	////p3 = &num2;
	////*p3 = 500;


	int v1 = 900, v2 = 200, v3;
	checkMax(&v1, &v2, &v3);
	cout << v3 << endl;

	return 0;
}

