

#include <iostream>

using namespace std;

char map[10][21] = {
	{"##################o#"},
	{"#    ############# #"},
	{"# ## ############  #"},
	{"# ##         ##    #"},
	{"# ########         #"},
	{"# ########### ######"},
	{"# ##          ######"},
	{"#             ######"},
	{"############      ##"},
	{"################# ##"},
};

char map2[10][21] = {
	{"##o#################"},
	{"#    ############# #"},
	{"# ## ############  #"},
	{"# ##         ##    #"},
	{"# ########         #"},
	{"# ##################"},
	{"# ##          ######"},
	{"#             ######"},
	{"#### #######      ##"},
	{"#### ###############"},
};

void showMap();
void showMenu();
void input();
void move();
int isSuccess();


bool gameOver = false;  //游戏结束的标记
char direction;  //接收方向字符



int currentpr = 0, currentpc = 18;  //当前入口位置记录
int newpr = currentpr, newpc = currentpc;  //走动的时候，辅助位置记录
int level = 1;

int rk[2][2] = { //入口
	{0,18}, //第一关的入口
	{0,2}  //第二关的入口
};
int js[2][2]{
	{9,17}, //第一关出口
	{9,4} //第二关出口
};

int flag1 = 1, flag2 = 1;//第一关第二关第一次进入的时候的标记变量


int main() {
	
	while (!gameOver)
	{
		if (level == 1 && flag1 == 1) {
			currentpr = rk[0][0];
			currentpc = rk[0][1];
			newpr = currentpr;
			newpc = currentpc;
			flag1 = 0;
		}
		else if (level == 2 && flag2 == 1) {
			currentpr = rk[1][0];
			currentpc = rk[1][1];
			newpr = currentpr;
			newpc = currentpc;
			flag2 = 0;
		}
		system("cls");//清屏
		showMap();
		showMenu();
		if (isSuccess()) {
			if (level == 1) {
				cout << "逃出成功！" << endl;
				cout << "下一关" << endl;
				cout << "是否继续游戏？（Y/N)" << endl;
				cin >> direction;
				if (direction == 'Y') {
					level++;
					continue;
				}
				else {
					cout << "欢迎下一次在来!" << endl;
					break;
				}
				
			}
			else if (level == 2) {
				cout << "逃出成功！" << endl;
				break;
			}
			
		}

		input();
		move();
		
		
	}

	
	return 0;
}

int isSuccess() {
	if (level == 1) { //第一关
		if (map[js[0][0]][js[0][1]] == 'o') {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (level == 2) {  //第二关
		if (map2[js[1][0]][js[1][1]] == 'o') {
			return 1;
		}
		else {
			return 0;
		}
	}
	
}

void move() {
	if (level == 1) {
		if (map[newpr][newpc] == ' ') {

			map[newpr][newpc] = 'o';
			map[currentpr][currentpc] = ' ';
			currentpr = newpr;
			currentpc = newpc;
		}
		else {
			newpr = currentpr;
			newpc = currentpc;
		}
	}
	else if (level == 2) {
		if (map2[newpr][newpc] == ' ') {

			map2[newpr][newpc] = 'o';
			map2[currentpr][currentpc] = ' ';
			currentpr = newpr;
			currentpc = newpc;
		}
		else {
			newpr = currentpr;
			newpc = currentpc;
		}
	}
	
}
void input() {
	cin >> direction;
	switch (direction)
	{
	case 'w':
		newpr--;
		break;
	case 's':
		newpr++;
		break;
	case 'a':
		newpc--;
		break;
	case 'd':
		newpc++;
		break;
	case 'q':
		cout << "你确定退出吗？（Y/N)" << endl;
		cin >> direction;
		if (direction == 'Y') {
			gameOver = true;
		}
		break;
	}
}

void showMenu() {
	cout << "up:w left:a down:s right:d eixt:q" << endl;
	cout << "请输入方向字符:" << endl;
}
void showMap() {
	if (level == 1) {
		for (int i = 0; i < 10; i++)
		{
			cout << map[i] << endl;
		}
	}
	else if (level == 2) {
		for (int i = 0; i < 10; i++)
		{
			cout << map2[i] << endl;
		}
	}
	
}

