

#include <iostream>

using namespace std;

int main() {

	int const N = 100;  //数组长度
	int arr[N];  //声明数组
	int m, k;    //m元素个数，k查找的元素
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> arr[i];
	}
	cin >> k;
	
	//left起始下标，right最大下标，mid保存中间下标
	int left = 0, right = m - 1, mid = 0;
	while (left <= right) {  //当left小于等于right时查找
		mid = (left + right) / 2;  //计算中间值mid
		if (k == arr[mid])   //查找到k
		{
			cout << mid + 1 << endl;
			break;
		}
		else if (k < arr[mid]) { //小于的情况，right挪到mid-1
			right = mid - 1;
		}
		else if (k > arr[mid]) { //大于的情况，left挪到mid+1
			left = mid + 1;
		}

	}
	if (left > right)  //当left <right ,k元素不在数组中
	{
		cout << -1 << endl;
	}



	return 0;
}

