

#include <iostream>

using namespace std;

int main() {

	const int N = 100;//数组长度
	int arr[N], m, k, index = -1;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> arr[i];
	}
	cin >> k;
	for (int i = 0; i < m; i++) {  //顺序查找
		if (k == arr[i]) {
			index = i + 1;
			break;
		}
	}
	cout << index << endl;



	return 0;
}

