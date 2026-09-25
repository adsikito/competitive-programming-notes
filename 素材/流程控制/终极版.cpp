
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main() {

	//随机一个1-100之间整数
	srand((unsigned)time(NULL));
	int guess = 0; 

	//玩家输入数字
	int num = 0;

	while (1) {
		guess = rand() % 100 + 1;
		//等级选择

		int level = 0;
		char c = 0;
		cout << "等级选择：（容易a；中等b；困难c）" << endl;
		cin >> c;
		if (c == 'a') {
			level = 10;
		}
		else if (c == 'b') {
			level = 5;
		}
		else if (c == 'c') {
			level = 2;
		}


		//不能确定多少次能猜对，用无限循环
		//while (true)
		int i = 1;
		for (; i <= level; i++)
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

		if (i > level) {
			cout << "失败了,你才的数字是" << guess << endl;
		}

		cout << "你是否需要再玩一次，（Y/N）" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}

	return 0;
}

