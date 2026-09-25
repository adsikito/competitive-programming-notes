
#include <iostream>
using namespace std;

int arr[100][100];
int arr2[100][100];
int main() {

	int n,m;
	cin >> n >> m;

	//接收数据
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin >> arr[i][j];
		}
	}
	
	//转置
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			arr2[j][i] = arr[i][j];
		}
	}
	
	//输出
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout << arr2[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

