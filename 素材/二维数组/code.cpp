

#include <iostream>


using namespace std;



//地图
char map[10][21] = {
	{"##################o#"},
	{"#    ############# #"},
	{"# ## ###########   #"},
	{"# ##          ## ###"},
	{"# ##########       #"},
	{"# ##################"},
	{"# ##      ##########"},
	{"#            #######"},
	{"############      ##"},
	{"################# ##"},

};

char direction;  //方向字符
int currentpr = 0, currentpc = 18;  //入口位置
int newpr = currentpr, newpc = currentpc;  //记录走动的位置
bool gameOver = false;



void showMap();
void showMenu();
bool isSuccess();



int main() {

	while (!gameOver)
	{
		system("cls");
		showMap();

		showMenu();

		if (isSuccess()) {
			cout <<"成功逃离!" <<endl;
			return 0;
		}

		cin >> direction;
		switch (direction)
		{
		case 'a':
			newpc--;
			break;
		case 'd':
			newpc++;
			break;
		case 'w':
			newpr--;
			break;
		case 's':
			newpr++;
			break;
		case 'q':
			cout <<"确定退出游戏吗？（Y/N)"  <<endl;
			cin >> direction;
			if (direction == 'Y')
				gameOver = 1; //游戏结束
		}

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



	return 0;
}


bool isSuccess() {
	if (map[9][17] == 'o') {
		return 1;
	}
	else {
		return 0;
	}
}
void showMenu() {
	cout  <<"up:w  down:s left:a right:d"<<  endl;
	cout  <<"请输入方向字符" << endl;
}
void showMap() {

	for (int i = 0; i < 10; i++) {
		cout << map[i] << endl;
	}
}

