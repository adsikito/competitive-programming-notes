

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;





int main() {
	
	//直接定义没有初始值
	//int arr1[5];

	//定义的时候，带有初始值
	//int arr2[5] = {1,2,3,4,5};
	

	/*bool arr2[5] = {1,0,1,1,0};

	cout << &arr2[0] << endl;
	cout << &arr2[1] << endl;
	cout << &arr2[2] << endl;*/

	//定义数组，数据的个数和长度不匹配
	//int arr[5] = { 111,222 };

	//直接定义，不给初始值
	//int arr[5] = {};

	//不给长度，直接反推计算长度
	//int arr[] = { 1,2,3 };


	/*int arr[10];
	arr[0] = 111;
	cout << arr[0] << endl;
	cout << arr[1] << endl;*/

	//int arr[5] = { 1,2,3,4,5 };
	/*for (int i = 0; i < 5; i++)
	{
		cout << arr[i] << " ";
	}*/
	/*for (int i : arr) {
		cout << i << " ";
	}*/

	/*for (auto i : arr) {
		cout << i << " ";
	}*/


	//循环赋值
	//int arr[3];// = { 1,2,3 };
	//for (int i = 0; i < 3; i++)
	//{
	//	cin >> arr[i];
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	cout << arr[i] << " ";
	//}

	//cout << pi << endl;
	/*int a = 10;
	int arr[a];*/


	/*int const n = 100;
	int arr[n];
	cout << n << endl;*/

	







	//五只小猪体重
	//const int N = 5;  //数组长度
	//float arr_pig[N];  //定义一个N长度的小数类型数组
	//for (int i = 0; i < N; i++)  //循环输入数据
	//{
	//	cin >> arr_pig[i];
	//}
	//float max = arr_pig[0];  //保存最大值max
	//for (int i = 0; i < N; i++)  //循环检查最大值
	//{
	//	if (max < arr_pig[i]) //判断是否大于现在最大值，如果是，替换最大值
	//	{
	//		max = arr_pig[i];
	//	}
	//}

	//cout << max << endl;




	/*int arr[100], n,sum = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (int  i = 0; i < n; i++)
	{
		sum += arr[i];
	}
	cout << sum << endl << sum * 1.0 / n << endl;*/


	//判断数组是否相等

	//int arr1[5] = { 1,2,3,4,5 };
	//int arr2[5] = { 1,2,3,4,5 };
	////cout << arr << endl;
	////cout << &arr[0] << endl;

	//if (arr1 == arr2) {
	//	cout << "=" << endl;
	//}
	//else {
	//	cout << "!=" << endl;
	//}

	//int arr1[5] = { 1,2,3,4,5 };
	//int arr2[5] = { 1,2,3,4,5 };

	//int countarr1 = sizeof(arr1) / sizeof(arr1[0]); //计算数组arr1的长度
	//int countarr2 = sizeof(arr2) / sizeof(arr2[0]);

	//bool flag = true;
	//if (countarr1 != countarr2)
	//{
	//	cout << "arr1 != arr2" << endl;
	//	flag = false;
	//}
	//for (int i = 0; i < countarr1; i++)
	//{
	//	if (arr1[i] != arr2[i]) {
	//		cout << "arr1 != arr2" << endl;
	//		flag = false;
	//		break;
	//	}
	//}
	//if (flag)
	//{
	//	cout << "arr1 == arr2" << endl;
	//}
	//
	

	//交换数据
	//临时变量法
	/*int a = 1, b = 2, c = 0;
	c = a;
	a = b;
	b = c;
	cout << a << " " << b << endl;*/

	//加减法
	//int a = 1, b = 2;
	//a = a + b;  // a = 3
	//b = a - b;  // b = 1
	//a = a - b; // a = 2
	//

	//cout << a << " " << b << endl;

	//使用系统函数swap

	/*int a = 1, b = 2;
	swap(a, b);
	cout << a << " " << b << endl;*/



	//冒泡排序
	//const int n = 5;
	//bool flag = true;
	//int arr[n] = { 5,1,2,3,4 };
	//for (int i = 0; i < n-1; i++)  //比较趟数
	//{
	//	flag = true;
	//	for (int j = 0; j < n - i - 1; j++) { //比较次数
	//		if (arr[j] > arr[j+1])
	//		{
	//			swap(arr[j], arr[j + 1]);
	//			flag = false;
	//		}
	//	}
	//	if (flag) {
	//		break;
	//	}
	//}
	//for (int i = 0; i < n; i++)
	//{
	//	cout << arr[i] << " ";
	//}

	//int arr[6] = { 1,2,3,4,5,6 };
	//int index = 0;

	//while (index < 6) {

	//	cout << arr[index] << " ";
	//	index++;
	//}


	//课堂练习

	int n, arr[100];
	cin >> n;
	srand((unsigned)time(0));  //种种子
	for (int  i = 0; i < n; i++)  //循环随机
	{
		arr[i] = rand() % 100 + 1;  //随机数装入数组
	}
	 
	for (int i = 0; i < n - 1; i++)  //比较趟数
	{
		for (int j = 0; j < n - i -1; j++)
		{
			if (arr[j] < arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}

