
#include <iostream>

using namespace std;

int main() {

	
	//字符串数组定义与初始化
	/*char c1[100];
	char c2[100] = "abc";
	char c3[100] = { 'a','b','c' };
	char c4[100] = { "abc" };*/

	//字符数组与字符串的区别
	//char c1[10] = "abcde";
	//char c2[10] = { 'a','b','c','d','e','\0'};

	/*cout << (void*)c1 << endl;
	cout << (void*)&c1[0] << endl;
	cout << (void*)&c1[1] << endl;
	cout << (void*)&c1[2] << endl;*/

	//cout << c2 << endl;
	//cout << &c2[0] << endl;
	//cout << &c2[1] << endl;
	//cout << &c2[2] << endl;
	//cout << &c2[3] << endl;


	//字符数组的输入和输出
	//char c[100];

	//cin >> c;
	//cout << c;

	//gets_s(c);
	//puts(c);



	//字符数组元素个数
	/*char arr[10] = "abc";
	int len = strlen(arr);
	cout << len << endl;*/


	//复制
	//char arr1[100] = "abc";
	//char arr2[100] = "jkj";
	//arr1 = arr2;
	//strcpy_s(arr1, arr2);
	//cout << arr1 << endl;

	//strncpy_s(arr1, arr2, 2);
	//cout << arr1 << endl;

	//比较大小
	/*char arr1[100] = "abc";
	char arr2[100] = "bbc";

	int n = strncmp(arr1, arr2,2);
	cout << n << endl;*/


	//忽略大小写比较
	/*char c1[100] = "aBCDE";
	char c2[100] = "zbcde";

	int n = _stricmp(c1, c2);

	cout << n << endl;*/

	/*char c1[100] = "BCDE";
	char c2[100] = "bcde";

	int n = _strnicmp(c1, c2,3);

	cout << n << endl;*/


	//链接
	//char c1[100] = "aBCDE";
	//char c2[100] = "zbcde";

	////strcat_s(c1, c2);
	//strncat_s(c1, c2,4);

	//cout << c1 << endl;


	//查找
	/*char c1[100] = "aBCDBE";
	
	cout << strrchr(c1, 'B') << endl;*/


	//大小写转换

	//char c1[100] = "ajJHDbc";

	////_strlwr_s(c1);
	//_strupr_s(c1);
	//cout << c1 << endl;


	//memset
	/*char c1[10];
	memset(c1, 'a', sizeof(c1));
	for (int i = 0; i < 10; i++) {
		cout << c1[i];
	}*/

	/*int arr[10];
	memset(arr, 0, sizeof(arr));
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}*/


	//字符数组数值类型转换
	//char c1[100] = "131.343";
	//int n = atoi(c1);
	//cout << n << endl;
	//double n2 = atof(c1);
	//cout << n2 << endl;
	//long n3 = atol(c1);
	//cout << n3 << endl;


	//字符检测
	char c = ',';
	//cout << isalpha(c) << endl;
	//cout << isupper(c) << endl;
	//cout << islower(c) << endl;
	//cout << isdigit(c) << endl;
	//cout << isxdigit(c) << endl;

	//cout << iscntrl(c) << endl;

	//cout << ispunct(c) << endl;

	//cout << isalnum(c) << endl;



	//课堂练习
	char arrc[255];
	gets_s(arrc);
	int n = strlen(arrc);
	int count = 0;
	for (int i = 0; i < n; i++) {
		/*if (isdigit(arrc[i])) {
			count++;
		}*/
		if (arrc[i] >= 48 && arrc[i] <= 57) {
			count++;
		}
	}

	cout << count << endl;


	return 0;
}

