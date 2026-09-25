
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//int arr[100][100];
//int row[100], col[100];

//int arr2[100][100];

//char c[100];

char c[100][21];

int main() {


	//案例3 二维数组解决方案

	int row = 1;
	while (cin >> c[row++]);
	row--;
	while (--row) {
		cout << c[row] << " ";
	}

	//案例3 一维数组解决方案

	//gets_s(c);  //接收字符串
	//int len = strlen(c);  //求字符串长度
	//int begin = len - 1, end = len - 1;  //初始化begin和end 等于字符串最后一个小标
	//for (int i = len - 1; i >= 0; i--) { //从最后的下标开始循环
	//	if (c[i] == ' ' || i == 0) {   //是否遇到空格或者 下标为0
	//		end = i;  //记录空格位置
	//		int j = 0;
	//		if (i != 0) {  //如果不是开头,j = end + 1
	//			j = end + 1;
	//		}
	//		else { //到头了，j=end
	//			j = end;
	//		}
	//		for (; j <= begin; j++) { //循环打印字符串
	//			cout << c[j];
	//		}
	//		cout << " ";
	//		begin = end - 1;  //重新把begin赋值为前一个单词的最后一个下标
	//	}
	//	else {
	//		end--;  //如果没有到空格或者0的话，end--
	//	}
	//}


	//案例2 边缘元素之和
	//int n, m,total = 0;
	//cin >> n >> m;

	////接收数据
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++) {
	//		cin >> arr2[i][j];
	//	}
	//}

	////求和
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++) {
	//		if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
	//			total += arr2[i][j];
	//		}
	//	}
	//}
	////输出
	//cout << total << endl;

	//案例1
	/*int n, m;
	cin >> n >> m;
	srand((unsigned)time(0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = rand() % 100 + 1;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			row[i] += arr[i][j];
			col[j] += arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		cout << row[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		cout << col[i] << " ";
	}*/

	//声明一个5行3列的二维整型数组
	//int arr[5][3];

	//先声明，在赋值
	/*int arr[2][2];
	arr[1][1] = 100;
	arr[1][0] = 200;
	arr[0][0] = 0;
	arr[0][1] = 2;*/


	//声明即初始化
	//1.位置个数和值个数完全对应上
	//int arr1[2][2] = { 100,200,300,400 };

	//2.位置个数和值个数对应不上
	//int arr2[2][2] = { 111,222 };

	//3.用括号括起来
	//int arr3[2][2] = { {100,200},{300,400} };

	//4.用括号括起来，但元素个数可以不给全
	/*int arr4[2][2] = { 
		{100},
		{200,300}
	};*/

	// 5.行数可以省略
	//int  arr5[][2] = { {100,200} ,{300} };


	////循环赋值
	//int arr[10][5];
	//for (int i = 0; i < 10; i++) {  //行
	//	for (int j = 0; j < 5; j++) { //列
	//		arr[i][j] = i * 10 + j;
	//	}
	//}

	////循环取值
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		cout << arr[i][j] << " ";
	//	}
	//	cout << endl;
	//}


	//循环赋值取值案例1
	/*int arr[5][5];
	for (int i = 0; i < 5; i++) 
		
		for (int j = 0; j < 5; j++) 
			arr[i][j] = j+1;
		
	

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}*/

	//循环赋值取值案例2
	//int arr[7][6];
	//int num = 0;
	//for (int i = 0; i < 7; i++) {
	//	
	//	for (int j = 0; j < 6; j++) {
	//		arr[i][j] = num;
	//	}
	//	num++;
	//}

	//for (int i = 0; i < 7; i++) {
	//	for (int j = 0; j < 6; j++) {
	//		cout << arr[i][j] << " ";
	//	}
	//	cout << endl;
	//}


	//循环赋值取值案例3
	//int arr[6][6];
	//for (int i = 0; i < 6; i++) {
	//	for (int j = 0; j < 6; j++) {
	//		if (i == j || i + j == 5) {
	//			arr[i][j] = 1;
	//		}
	//		else {
	//			arr[i][j] = 0;
	//		}
	//	}
	//}

	////memset(arr, 0, sizeof(arr));

	//

	//for (int i = 0; i < 6; i++) {
	//	for (int j = 0; j < 6; j++) {
	//		cout << arr[i][j] << " ";
	//	}
	//	cout << endl;
	//}


	//二维字符数组
	//char arrc[10][20] = {"hello","C++","abc"};

	//arrc[0] = "hello";

	//cout << arrc[0];
	

	



	return 0;
}


