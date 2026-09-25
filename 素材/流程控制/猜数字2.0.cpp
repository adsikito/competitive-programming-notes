
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main() {

	//随机一个1-100之间整数
	srand((unsigned)time(NULL));
	int guess = rand() % 100 + 1;

	//玩家输入数字
	int num = 0;


	//不能确定多少次能猜对，用无限循环
	while (true)
	{
		cout << "请输入数字（1-100）：" << endl;
		cin >> num;
		if (num == guess)
		{
			cout << "恭喜你，猜对了" << endl;
			break;
		}
		else if (num > guess) {
			cout << "猜大了" << endl;
		}
		else {
			cout << "猜小了" << endl;
		}

	}
	

	return 0;
}

