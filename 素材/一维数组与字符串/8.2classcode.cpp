

#include <iostream>

using namespace std;

int main() {

	/*
	const int N = 101;  //常变量
	//定义数组,定义输入数量m,待查找数据k
	int arr[N], m, k;
	cin >> m;
	//循环接收m个数据装入数组arr中
	for (int i = 1; i <= m; i++)
	{
		cin >> arr[i];
	}
	cin >> k;

	//定义左边下标left,右边下标right,中间下标mid
	int left = 0, right = m, mid = 0;
	while (left <= right) {  //当左边下标小于等于右边下标的时候，进行查找

		mid = (left + right) / 2; //求中间下标的值
		if (arr[mid] == k) {  //判断是否找到k
			cout << mid << endl;
			break;
		}
		else if(arr[mid] < k)  //证明查找的k,在mid右边，需要left往mid+1挪
		{
			left = mid + 1;
		}
		else {  //证明查找的k,在mid左边，需要right往mid-1挪
			right = mid - 1;
		}
	}

	if (left > right) {  //证明arr数组内没有k元素,输出-1
		cout << -1 << endl;
	}*/


	/*
	//查找最小下标
	const int N = 101;  //常变量
	//定义数组,定义输入数量m,待查找数据k
	int arr[N], m, k;
	cin >> m;
	//循环接收m个数据装入数组arr中
	for (int i = 1; i <= m; i++)
	{
		cin >> arr[i];
	}
	cin >> k;

	
	//定义左边下标left,右边下标right,中间下标mid
	int left = 0, right = m, mid = 0;
	while (left <= right) {  //当左边下标小于等于右边下标的时候，进行查找

		mid = (left + right) / 2; //求中间下标的值
		if (arr[mid] == k) {  //判断是否找到k
			//往mid的左边在顺序查找k
			while (mid - 1 >= 0 && arr[mid - 1] == k) {
				mid--;
			}
			cout << mid << endl;
			break;
		}
		else if (arr[mid] < k)  //证明查找的k,在mid右边，需要left往mid+1挪
		{
			left = mid + 1;
		}
		else {  //证明查找的k,在mid左边，需要right往mid-1挪
			right = mid - 1;
		}
	}

	if (left > right) {  //证明arr数组内没有k元素,输出-1
		cout << -1 << endl;
	}*/


	/*
	//查找最大下标
	const int N = 101;  //常变量
	//定义数组,定义输入数量m,待查找数据k
	int arr[N], m, k;
	cin >> m;
	//循环接收m个数据装入数组arr中
	for (int i = 1; i <= m; i++)
	{
		cin >> arr[i];
	}
	cin >> k;


	//定义左边下标left,右边下标right,中间下标mid
	int left = 0, right = m, mid = 0;
	while (left <= right) {  //当左边下标小于等于右边下标的时候，进行查找

		mid = (left + right) / 2; //求中间下标的值
		if (arr[mid] == k) {  //判断是否找到k
			//往mid的右边在顺序查找k
			while (mid + 1 <= m && arr[mid + 1] == k) {
				mid++;
			}
			cout << mid << endl;
			break;
		}
		else if (arr[mid] < k)  //证明查找的k,在mid右边，需要left往mid+1挪
		{
			left = mid + 1;
		}
		else {  //证明查找的k,在mid左边，需要right往mid-1挪
			right = mid - 1;
		}
	}

	if (left > right) {  //证明arr数组内没有k元素,输出-1
		cout << -1 << endl;
	}
	*/
	

	/*
	//查找k元素个数
	const int N = 101;  //常变量
	//定义数组,定义输入数量m,待查找数据k
	int arr[N], m, k,count = 0;
	cin >> m;
	//循环接收m个数据装入数组arr中
	for (int i = 1; i <= m; i++)
	{
		cin >> arr[i];
	}
	cin >> k;


	//定义左边下标left,右边下标right,中间下标mid
	int left = 0, right = m, mid = 0;
	while (left <= right) {  //当左边下标小于等于右边下标的时候，进行查找

		mid = (left + right) / 2; //求中间下标的值
		if (arr[mid] == k) {  //判断是否找到k
			count++;
			int leftd = mid - 1, rightd = mid + 1;
			//往mid的左边在顺序查找k
			while (leftd >= 0 && arr[leftd] == k) {
				leftd--;
				count++;
			}
			//往mid的右边在顺序查找k
			while (rightd <= m && arr[rightd] == k) {
				rightd++;
				count++;
			}
			
			break;
		}
		else if (arr[mid] < k)  //证明查找的k,在mid右边，需要left往mid+1挪
		{
			left = mid + 1;
		}
		else {  //证明查找的k,在mid左边，需要right往mid-1挪
			right = mid - 1;
		}
	}

	
	cout << count << endl;
	*/

	/*
	//蛋糕

	float arr[10000],m;  //小数数组，缺少重量m
	int n;  //n块蛋糕

	cin >> n;
	for (int i = 0; i < n; i++)  // 循环输入n块蛋糕重量
	{
		cin >> arr[i];
	}
	cin >> m;
	for (int i = 0; i < n; i++) //循环检测缺斤少两，并输出
	{
		if (i % 2 == 1)
			arr[i] += m;
		cout << arr[i] << " ";
	}*/

	/*
	//赛跑

	float arr_score[10];  //定义保存分数的数组
	int n;   //n个人参加

	cin >> n;
	for (int i = 0; i < n; i++) //循环输入n个人的成绩
	{
		cin >> arr_score[i];
	}

	float maxs = arr_score[0], mins = arr_score[0];  //最高分最低分初始化
	int maxi = 0, mini = 0;   //保存最高分，最低分的下标
	for (int i = 0; i < n; i++)
	{
		if (arr_score[i] > maxs) {
			maxs = arr_score[i];
			maxi = i;
		}
		if (arr_score[i] < mins) {
			mins = arr_score[i];
			mini = i;
		}
	}

	swap(arr_score[maxi], arr_score[mini]);

	for (int i = 0; i < n; i++) {
		cout << arr_score[i] << " ";
	}*/

	/*
	//塞车
	int arr[100],n,m;  //声明数组，声明前n辆，后m辆

	cin >> n;
	for (int i = 0; i < n; i++) {  //前n辆装入数组
		cin >> arr[i];
	}
	cin >> m;
	for (int i = n; i < n+m; i++)  //后m辆装入数组
	{
		cin >> arr[i];
	}
	for (int i = 0; i < n + m; i++) {//打印
		cout << arr[i] << " ";
	}*/


	/*
	//新同学
	
	int arr[60],n,m,k,p;  //定义数组，n个已有的同学，m插入的位置，k插入同学的编号

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	cin >> k;
	cin >> p >> m;

	int index = n - 1;  //保存最大下标
	if (p)
	{
		while (index >= m-1) {  //挪动位置
			arr[index+1] = arr[index];
			index--;
		}

		arr[index+1] = k;
	}
	else {


		while (index > m-1) {  //挪动位置
			arr[index+1] = arr[index];
			index--;
		}

		arr[index+1] = k;
	}

	for (int i = 0; i < n + 1; i++) {
		cout << arr[i] << " ";
	}*/

	/*
	//删除

	int arr[100], n,index = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		if (arr[i] < 0) {
			index = i;
		}
	}
	while (index < n -1) {
		arr[index] = arr[index + 1];
		index++;
	}

	for (int i = 0; i < n - 1; i++) {
		cout << arr[i] << " ";
	}*/


	//无序合并
	/*
	int arr1[100], arr2[100], arr3[200], n, m;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr1[i];
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> arr2[i];
	}

	for (int i = 0; i < n; i++)
	{
		arr3[i] = arr1[i];
	}
	
	for (int i = n,d=0; i < n + m; i++,d++)
	{
		arr3[i] = arr2[d];
	}

	for (int i = 0; i < n + m; i++) {
		cout << arr3[i] << " ";
	}*/

	/*
	//有序合并
	int arr1[100], arr2[100], arr3[200], n, m;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr1[i];
	}
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> arr2[i];
	}

	int i = 0, j = 0,index = 0;
	for (; i < n && j < m;) {
		if (arr1[i] > arr2[j]) {
			arr3[index++] = arr2[j++];
		}
		else if (arr1[i] < arr2[j]) {
			arr3[index++] = arr1[i++];
		}
		else {
			arr3[index++] = arr1[i++];
			j++;
		}
	}

	while (i < n) {
		arr3[index++] = arr1[i++];
	}
	while (j < m) {
		arr3[index++] = arr2[j++];
	}

	for (int i = 0; i < index; i++) {
		cout << arr3[i] << " ";
	}
	*/

	//课堂练习
	int arr[10],temp;
	for (int i = 0; i < 10; i++) {
		cin >> arr[i];
	}
	temp = arr[0];

	for (int i = 0; i < 9; i++) {
		arr[i] = arr[i + 1];
	}
	arr[9] = temp;

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}

