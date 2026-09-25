

#include <iostream>

using namespace std;

#define PI 3.1415926
#define INC(x) x ++
#define DEC(x) x --

#define SQR(n) ((n) *( n))  //括号很重要，优先级的改变

#define DIGIT(c) ((c) >= '0' && (c) <= '9')

#define ADD(a,b) ((a) + (b))

#define ARRSIZE(arr) (sizeof((arr))/sizeof((arr[0])))

int main() {

	//double r;//定义圆的半径
	//cin >> r;

	//cout << PI * r * r << endl;


	/*int num = 100;
	INC(num);
	cout << num << endl;
	DEC(num);
	cout << num << endl;*/

	/*int num = 10;
	int r1 = SQR(num);
	cout << r1 << endl;
	int r2 = SQR(5 + 5);
	cout << r2 << endl;*/


	//char ch1 = 'a';
	//cout << DIGIT(ch1) << endl;
	////#undef  DIGIT  //取消宏定义
	//char ch2 = '9';
	//cout << DIGIT(ch2) << endl;


	/*int n1 = 10;
	int n2 = 20;
	cout << ADD(n1, n2) << endl;*/


//#define PRINT
//	cout << "条件编译测试1" << endl;
//#ifdef PRINT
//	cout << "PRINT has define" << endl;
//#else
//	cout << "PRINT no define" << endl;
//#endif

//#define PRINT
//	cout << "条件编译测试2" << endl;
//#ifndef PRINT
//	cout << "PRINT no define" << endl;
//
//#else
//	cout << "PRINT has define" << endl;
//#endif

//#define com 0
//#define com2 1
//
//#if com
//	cout << "start compile" << endl;
//#elif com2
//	cout << "2222" << endl;
//#else
//	cout << "else" << endl;
//
//	 
//#endif


//	cout << "条件编译测试3" << endl;
//#error compile error here！


	

	/*int ar_num[10];
	cout << ARRSIZE(ar_num) << endl;*/


	return 0;
}

