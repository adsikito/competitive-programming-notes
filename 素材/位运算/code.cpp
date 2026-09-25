

#include <iostream>

using namespace std;

int main() {


	/*int num = 130;
	if ((num & 1)) {
		cout << "奇数" << endl;
	}
	else {
		cout << "偶数" << endl;
	}*/

	/*int num = 11;
	cout << (num << 2) << endl;*/

	/*int num = -11;
	cout << (num >> 1) << endl;*/

	int num1 = 100, num2 = 200;
	cout << "num1 = " << num1 << "  num2 = " << num2 << endl;
	num1 ^= num2;
	num2 ^= num1;
	num1 ^= num2;
	cout << "num1 = " << num1 << "  num2 = " << num2 << endl;

	return 0;
}

