#include <iostream>


using namespace std;


int main() {
	
	
	int n = 100;
	int g, s, b;
	do {
		g = n % 10;
		s = n / 10 % 10;
		b = n / 100;
		if (n == g * g * g + s * s * s + b * b * b) {
			cout << n << endl;
		}
		n++;
	} while (n < 1000);



	return 0;
}