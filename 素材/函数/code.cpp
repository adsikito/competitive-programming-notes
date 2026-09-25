

#include <iostream>

using namespace std;


/*
void change(int &num) {

	num *= 2;
	
	
}
*/

/*
int& func(int& v1) {
	v1 *= 100;
	return v1;
}*/

/*
int mulSum(int n, ...) {
	va_list argptr;
	__crt_va_start(argptr, n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += __crt_va_arg(argptr, int);
	}
	__crt_va_end(argptr);

	return sum;

}*/



//默认参数
/*
void add(int v1, int v2 = 100) {
	cout << v1 + v2 << endl;
}*/


//交换两个变量的值
/*
int swap(int v1, int v2) {
	int v3 = v1;
	v1 = v2;
	v2 = v3;
	
}*/

//递归求n-1和

int func(int n) {
	if (n == 1) { //递归出口
		return 1;
	}
	else {
		return func(n - 1) + n;
	}
}

//递归求斐波那契额数列的前n项
int fibo(int n) {
	if (n <= 2)
		return 1;
	else
		return fibo(n - 1) + fibo(n - 2);
}

void hanoi(int num, char sou, char tar, char aux) {
	static int count = 1;
	if (num == 1) {//如果只有一个圆盘，直接挪到目标柱
		cout << "第" << count << "次：从" << sou << "移动到" << tar << endl;
		count++;
	}
	else {
		hanoi(num - 1, sou, aux, tar);
		cout << "第" << count << "次：从" << sou << "移动到" << tar << endl;
		count++;
		hanoi(num - 1, aux, tar, sou);
	}
}

//利用内联函数判断一个数是否是偶数
inline bool isEven(int num) {
	return num % 2 == 0;
}

//函数重载  求两个数的和

int sum(int v1, int v2) {
	cout << "int" << endl;
	return v1 + v2;
}
float sum(float v1, float v2) {
	cout << "float" << endl;
	return v1 + v2;
}
double sum(double v3, double v4) {
	cout << "double" << endl;
	return v3 + v4;
}


//判断一个数字是否是质数
bool isPrime(int num) {
	if (num == 1) {
		return false;
	}
	bool flag = true;
	for (int i = 2; i <= num / 2; i++)
	{
		if (num % i == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

void printPrime(int num1, int num2) {
	for (int i = num1; i <= num2; i++)
	{
		if (isPrime(i)) {
			cout << i << " ";
		}
	}
}


int main() {

	
	int num1, num2;
	cin >> num1 >> num2;
	printPrime(num1, num2);



	/*int n1 = 100, n2 = 200;
	cout << sum(n1, n2) <<endl;
	float n3 = 1.1, n4 = 1.2;
	cout << sum(n3, n4) << endl;
	double n5 = 12.31, n6 = 1.3232;
	cout << sum(n5, n6) << endl;*/

	//for (int i = 1; i < 10; i++) {
	//	cout << isEven(i) << endl;
	//}

	//hanoi(5, 'A', 'B', 'C');


	//cout << fibo(10) << endl;


	/*int total = func(5);
	cout << total << endl;*/



	/*int n1 = 100, n2 = 200;
	cout << swap(n1, n2) << endl;
	cout << n1 << " " << n2 << endl;*/


	//add(1,2);

	/*int total = mulSum(5, 1, 5, 9,20,30);
	cout << total << endl;*/


	
	/*int x = 100;
	change(x);
	cout << x << endl;*/

	//类型，个数，顺序都得对应上
	//change("abc", x);


	/*int num = 100;
	int &num2 = num;
	num += 100;
	num2 -= 50;
	cout << num << endl;
	cout << num2 << endl;*/


	/*int n = 100;
	cout << func(n) << endl;
	cout << n << endl;*/
	

	return 0;
}


