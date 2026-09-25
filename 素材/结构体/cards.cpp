
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
struct CARD {
	char suit[10];//花色
	char face[10];//牌面
}card[54];

const char* suit[] = { "diamonds","clubs","hearts","spades" };
const char* face[] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
void createCards();//产生54张牌
void shuffle(CARD* card); //洗牌
void dealCards(CARD* card); //发牌

int main() {

	createCards();
	shuffle(card);
	dealCards(card);

	return 0;
}
void dealCards(CARD* card) {
	CARD player[3][17], finalCards[3];
	int p1 = 0, p2 = 0, p3 = 0;
	for (int i = 0; i < 51; i++) {
		if (i % 3 == 0) {
			player[0][p1++] = card[i];
		}
		else if (i % 3 == 1) {
			player[1][p2++] = card[i];
		}
		else {
			player[2][p3++] = card[i];
		}

	}
	for (int i = 51, j = 0; i < 54; i++, j++) {
		finalCards[j] = card[i];
	}

	cout << "开始发牌>>>" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "玩家" << i + 1 << endl;
		for (int j = 0; j < 17; j++) {
			cout << player[i][j].suit << "  " << player[i][j].face << endl;
		}
	}
	cout << "底牌" << endl;
	for (int i = 0; i < 3; i++) {
		cout << finalCards[i].suit << "  " << finalCards[i].face << endl;
	}
	cout << "发牌结束>>>" << endl;
}
void shuffle(CARD* card) {
	cout << "洗牌开始>>>" << endl;
	int i = 0, j;
	CARD temp;
	srand(time(0));
	for (; i < 54; i++) {
		j = rand() % 54;
		temp = card[i];
		card[i] = card[j];
		card[j] = temp;
	}
	cout << "洗牌结束>>>" << endl;
}

void createCards() {
	cout << "开始生成54张牌>>>" << endl;
	int i = 0;
	for (; i < 52; i++) {
		strcpy_s(card[i].suit, suit[i / 13]);
		strcpy_s(card[i].face, face[i % 13]);
	}
	strcpy_s(card[52].suit, "red");
	strcpy_s(card[52].face, "joker");
	strcpy_s(card[53].suit, "black");
	strcpy_s(card[53].face, "joker");
	cout << "生成54张牌结束>>>" << endl;
}
