
#include <iostream>
#include <cstdlib>
#include <ctime>

#define pi 3.1415

using namespace std;


int main() {

	//cout << RAND_MAX << endl;

	//srand(time(0));
	//cout << rand() << endl;   //rand() Î±Ëæ»úÊý

	//cout << time(0) << endl;

	/*srand(time(0));
	for (int i = 0; i < 5; i++)
	{
		
		cout << rand() % 100 << " ";
	}*/


	//cout << pi << endl;

	srand(time(0));
	cout << rand() % 10 / 10.0 << endl;

	return 0;
}

