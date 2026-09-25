

#include <iostream>

using namespace std;
#define N 10
int main() {

	int arr[N] = { 99,11,2,3,4,6,9,7,100,1 };


	//趟数
	for (int i = 0; i < N-1; i++) {
		//比较次数
		for (int j = 0; j < N - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}



	return 0;
}

