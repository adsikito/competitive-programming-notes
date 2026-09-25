

#include <iostream>
#include <string>
using namespace std;

int main() {

	cout << "-------------------自助点餐系统-------------------" << endl;
	cout << "菜单：" << endl;
	cout << "1火锅 2回锅肉 3宫保鸡丁 4夫妻肺片 5毛血旺 6麻婆豆腐 7东坡肘子 8水煮牛肉" << endl;
	cout << "9龙抄手 10钟水饺 11串串香 12肥肠粉 13担担面" << endl;
	cout << "14可乐 15雪碧 16脉动 17果缤纷 18果粒橙 19营养快线" << endl;
	cout << "套餐A(优惠10)：火锅 回锅肉 东坡肘子，任选其一" << endl;
	cout << "龙抄手 钟水饺 串串香，任选其一" << endl;
	cout << "可乐 雪碧，任选其一" << endl;
	cout << "套餐B（优惠12）：火锅 回锅肉 东坡肘子 水煮牛肉，任选其一" << endl;
	cout << "肥肠粉 担担面，任选其一" << endl;
	cout << "脉动 果缤纷 果粒橙，任选其一" << endl;
	cout << "本店消费满100元，可加1元，换购一种饮料" << endl;

	char c = 0;// 接收输入字符
	int input = -1;
	int fp = 0; //优惠金额
	string arrmenu[19] = { "火锅","回锅肉","宫保鸡丁","夫妻肺片","毛血旺" ,"麻婆豆腐","东坡肘子","水煮牛肉","龙抄手","钟水饺","串串香","肥肠粉","担担面","可乐","雪碧","脉动","果缤纷","果粒橙","营养快线" };
	int price[19] = { 60,30,20,25,32,15,45,50,12,10,13,12,10,5,5,6,10,8,9 };
	int count[19] = { 0 ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int total = 0;
	while (1) {
		cout << "A单点  B套餐  C结账（输入字母确认)" << endl;
		cin >> c;
		if (c == 'A')
		{
			cout << "请输入数字确认点餐，输入0结束" << endl;
			while (1)
			{
				cin >> input;
				if (input == 0)
				{
					break;
				}
				switch (input) {
				case 1:
					count[0]++;
					break;
				case 2:
					count[1]++;
					break;
				case 3:
					count[2]++;
					break;
				case 4:
					count[3]++;
					break;
				case 5:
					count[4]++;
					break;
				case 6:
					count[5]++;
					break;
				case 7:
					count[6]++;
					break;
				case 8:
					count[7]++;
					break;
				case 9:
					count[8]++;
					break;
				case 10:
					count[9]++;
					break;
				case 11:
					count[10]++;
					break;
				case 12:
					count[11]++;
					break;
				case 13:
					count[12]++;
					break;
				case 14:
					count[13]++;
					break;
				case 15:
					count[14]++;
					break;
				case 16:
					count[15]++;
					break;
				case 17:
					count[16]++;
					break;
				case 18:
					count[17]++;
					break;
				case 19:
					count[18]++;
					break;
				}

			}
			total = 0;
			for (int i = 0; i < 19; i++)
			{
				if (count[i] != 0) {
					cout << arrmenu[i] << price[i] << "元,数量：" << count[i] << " 小计:" << count[i] * price[i] << endl;
					total += count[i] * price[i];
				}
			}
			cout << "总计：" << total - fp << "元,优惠" << fp << "元" << endl;
		}
		else if (c == 'B') {
			cout << "套餐A  套餐B （输入字母确认）" << endl;
			cin >> c;
			if (c == 'A') {
				fp += 10;
				cout << "1火锅 2回锅肉 7东坡肘子" << endl;
				cin >> input;
				switch (input) {
				case 1:
					count[0]++;
					break;
				case 2:
					count[1]++;
					break;
				case 7:
					count[6]++;
					break;
				}
				cout << "9龙抄手 10钟水饺 11串串香" << endl;
				cin >> input;
				switch (input) {
				case 9:
					count[8]++;
					break;
				case 10:
					count[9]++;
					break;
				case 11:
					count[10]++;
					break;
				}
				cout << "14可乐 15雪碧" << endl;
				cin >> input;
				switch (input) {
				case 14:
					count[13]++;
					break;
				case 15:
					count[14]++;
					break;

				}
			}
			else if (c == 'B') {
				fp += 12;
				cout << "1火锅 2回锅肉 7东坡肘子 8水煮牛肉" << endl;
				cin >> input;
				switch (input) {
				case 1:
					count[0]++;
					break;
				case 2:
					count[1]++;
					break;
				case 7:
					count[6]++;
					break;
				case 8:
					count[7]++;
					break;
				}
				cout << "12肥肠粉 13担担面" << endl;
				cin >> input;
				switch (input) {
				case 12:
					count[11]++;
					break;
				case 13:
					count[12]++;
					break;
				}
				cout << "16脉动 17果缤纷 18果粒橙" << endl;
				cin >> input;
				switch (input) {
				case 16:
					count[15]++;
					break;
				case 17:
					count[16]++;
					break;
				case 18:
					count[17]++;
					break;

				}
			}
			total = 0;
			for (int i = 0; i < 19; i++)
			{
				if (count[i] != 0) {
					cout << arrmenu[i] << price[i] << "元,数量：" << count[i] << " 小计:" << count[i] * price[i] << endl;
					total += count[i] * price[i];
				}
			}
			cout << "总计：" << total - fp << "元,优惠" << fp << "元" << endl;
			total -= fp;
		}
		else if (c == 'C') {
			if (total >= 100) {
				cout << "消费满100元，是否加1元换购(Y/N)" << endl;
				
				cin >> c;
				if (c == 'Y') {
					cout << "14可乐 15雪碧 16脉动" << endl;
					cin >> input;
					total += 1;
					
					switch (input)
					{
					case 14:
						fp += price[13] - 1;
						break;
					case 15:
						fp += price[14] - 1;
						break;
					case 16:
						fp += price[15] - 1;
						break;
					}
				}
				
				cout << "您已支付" << total << "元，优惠" << fp << "元" << endl;
				cout << "-----------------欢迎下次光临----------------" << endl;
			}
			break;
		}
		else {
			cout << "请重新输入字符确认" << endl;
		}

	}

	return 0;
}

